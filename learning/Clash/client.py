import socket
import struct
import threading

class Proxy:
    def __init__(self, listen_port, target_ip, target_port):
        self.listen_port = listen_port
        self.target_ip = target_ip
        self.target_port = target_port
        self.connection_table = {}

    def parse_ip_header(self, data):
        ip_header = struct.unpack('!BBHHHBBH4s4s', data[:20])
        version_ihl = ip_header[0]
        version = version_ihl >> 4
        ihl = (version_ihl & 0xF) * 4
        ttl = ip_header[5]
        protocol = ip_header[6]
        src_ip = socket.inet_ntoa(ip_header[8])
        dest_ip = socket.inet_ntoa(ip_header[9])

        return version, ihl, ttl, protocol, src_ip, dest_ip

    def parse_tcp_header(self, data):
        tcp_header = struct.unpack('!HHLLBBHHH', data[:20])
        src_port = tcp_header[0]
        dest_port = tcp_header[1]
        sequence_number = tcp_header[2]
        ack_number = tcp_header[3]
        data_offset_reserved_flags = tcp_header[4]
        data_offset = (data_offset_reserved_flags >> 4) * 4
        flags = tcp_header[5]
        window_size = tcp_header[6]
        checksum = tcp_header[7]
        urgent_pointer = tcp_header[8]

        return src_port, dest_port, sequence_number, ack_number, data_offset, flags, window_size, checksum, urgent_pointer





    def handle_client(self, client_socket):
        # 接收来自用户的请求
        request = client_socket.recv(4096)


        # 解析 IP 包头
        version, ihl, ttl, protocol, src_ip, dest_ip = self.parse_ip_header(request)
        print(f"IP Header - Version: {version}, IHL: {ihl}, TTL: {ttl}, Protocol: {protocol}, Src IP: {src_ip}, Dest IP: {dest_ip}")

        # 解析 TCP 包头
        ip_data = request[ihl:]  # 截取 IP 包头后的数据，即 TCP 包头和数据部分
        src_port, dest_port, sequence_number, ack_number, data_offset, flags, window_size, checksum, urgent_pointer = self.parse_tcp_header(ip_data)
        print(f"TCP Header - Src Port: {src_port}, Dest Port: {dest_port}, Sequence Number: {sequence_number}, Ack Number: {ack_number}, Data Offset: {data_offset}, Flags: {flags}, Window Size: {window_size}, Checksum: {checksum}, Urgent Pointer: {urgent_pointer}")

        # 解析用户请求的头部
        headers = request.split(b'\r\n\r\n', 1)
        if len(headers) == 2:
            request_headers, body = headers
        else:
            request_headers, body = headers[0], b''

        # 获取用户原始目的 IP 和端口
        user_dest_ip = None
        user_dest_port = None

        request_lines = request_headers.split(b'\r\n')
        for line in request_lines:
            if line.startswith(b'Host: '):
                host_value = line.split(b'Host: ')[1].strip()
                user_dest_ip, _, user_dest_port = host_value.partition(b':')
                user_dest_ip, user_dest_port = user_dest_ip.decode(), user_dest_port.decode()

        # 修改请求中的目标 IP 为实际目标 IP
        modified_request = request.replace(b'Host: localhost', f'Host: {self.target_ip}'.encode())

        # 添加自定义字段到请求头部
        modified_request = modified_request.replace(b'\r\n\r\n', 
            f'\r\nUser-Dest-IP: {user_dest_ip}\r\nUser-Dest-Port: {user_dest_port}\r\n\r\n'.encode())

        # 创建新的连接到实际目标服务器
        target_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        target_socket.connect((self.target_ip, self.target_port))

        # 发送修改后的请求到目标服务器
        target_socket.send(modified_request)

        # 接收来自目标服务器的响应
        response = target_socket.recv(4096)

        # 发送响应给用户
        client_socket.send(response)

        # 关闭连接
        target_socket.close()
        client_socket.close()

    def start(self):
        try:
            server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            server.bind(('localhost', self.listen_port))
            server.listen(5)
            print(f"[***]Proxy listening on port {self.listen_port}")

            while True:
                client_socket, addr = server.accept()
                print(f"[***]Accepted connection from {addr}")

                # 处理用户请求的线程
                client_handler = threading.Thread(target=self.handle_client, args=(client_socket,))
                client_handler.start()

        except KeyboardInterrupt:
            print("[***]Proxy terminated.")
        finally:
            server.close()

if __name__ == "__main__":
    # 创建代理实例，监听本地 12345 端口，转发到目标服务器的 23456 端口
    proxy = Proxy(listen_port=12345, target_ip='192.168.1.112', target_port=23456)
    proxy.start()



# 方式一
# 系统层面，转发所有的包

# 允许流量转发
# sudo sysctl -w net.ipv4.ip_forward=1

# 转发所有目的端口为80的包到本地12345代理端口
# sudo iptables -t nat -A OUTPUT -p tcp --dport 80 -j REDIRECT --to-port 12345
# sudo iptables -t nat -A OUTPUT -p tcp --dport 443 -j REDIRECT --to-port 12345

# 删除转发规则
# sudo iptables -t nat -D OUTPUT 1

# 查看所有转发规则
# sudo iptables -t nat -L -n -v


# 方式二
# 需要支持proxy
# export http_proxy="http://127.0.0.1:12345"
# export https_proxy="http://127.0.0.1:12345"

