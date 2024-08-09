import socket
import struct

def intercept_data(interface):
    # 创建原始套接字
    raw_socket = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.ntohs(3))

    # 绑定到指定网络接口
    raw_socket.bind((interface, 0))

    try:
        while True:
            # 读取数据包
            packet, _ = raw_socket.recvfrom(65536)

            # 解析以太网头部
            ethernet_header = packet[:14]
            ethertype = struct.unpack('!H', ethernet_header[12:14])[0]

            # 如果是IP数据包（IPv4）
            if ethertype == 0x0800:
                ip_header = packet[14:34]

                # 解析IP头部
                version_ihl = struct.unpack('!B', ip_header[0:1])[0]
                version = version_ihl >> 4
                ihl = (version_ihl & 0xF) * 4

                source_ip = socket.inet_ntoa(ip_header[12:16])
                dest_ip = socket.inet_ntoa(ip_header[16:20])

                # 如果是TCP数据包
                if ip_header[9] == 6:
                    tcp_header = packet[14 + ihl:14 + ihl + 20]

                    source_port = struct.unpack('!H', tcp_header[0:2])[0]
                    dest_port = struct.unpack('!H', tcp_header[2:4])[0]

                    data = packet[14 + ihl + 20:]

                    # 输出数据包信息
                    print()
                    print(f"[***]Received TCP data from {source_ip}:{source_port} to {dest_ip}:{dest_port}")
                    # print(f"Hex data: {data.hex()}")
                    print(f"[***]Hex data: {':'.join(format(x, '02x') for x in packet)}")
                    print(f"[***]Data: {data.decode('utf-8', 'replace')}")
                    print()


    except KeyboardInterrupt:
        print("Monitoring terminated.")

    finally:
        raw_socket.close()

if __name__ == "__main__":
    # 指定网络接口，如 eth0
    network_interface = "eth0"

    intercept_data(network_interface)
