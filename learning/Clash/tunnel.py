import socket
import threading

# 代理服务器的监听地址和端口
PROXY_HOST = '127.0.0.1'
PROXY_PORT = 12345

# 目标服务器的地址和端口
TARGET_HOST = 'www.baidu.com'
TARGET_PORT = 80

def handle_client(client_socket):

    # 接收 CONNECT 请求
    connect_data = client_socket.recv(4096)
    
    # 解析 CONNECT 请求，获取目标主机和端口
    target_host = connect_data.split(b' ')[1].split(b':')[0]
    target_port = int(connect_data.split(b' ')[1].split(b':')[1])

    # 连接目标服务器
    target_socket = socket.create_connection((target_host, target_port))

    # 响应客户端的 CONNECT 成功
    client_socket.sendall(b'HTTP/1.1 200 Connection Established\r\n\r\n')

    # 启动两个线程，分别进行双向转发
    thread1 = threading.Thread(target=forward_data, args=(client_socket, target_socket))
    thread2 = threading.Thread(target=forward_data, args=(target_socket, client_socket))

    thread1.start()
    thread2.start()

def forward_data(source, destination):
    data = source.recv(4096)
    while data:
        try:
            destination.sendall(data)
            data = source.recv(4096)
        except ConnectionResetError :
            print(f"Disconnect")


def main():
    proxy_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    proxy_server.bind((PROXY_HOST, PROXY_PORT))
    proxy_server.listen(5)

    print(f"Proxy server listening on {PROXY_HOST}:{PROXY_PORT}")

    while True:
        client_socket, addr = proxy_server.accept()
        print(f"Accepted connection from {addr[0]}:{addr[1]}")
        
        client_handler = threading.Thread(target=handle_client, args=(client_socket,))
        client_handler.start()

if __name__ == "__main__":
    main()
