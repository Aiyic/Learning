import socket
import threading

# 代理服务器的地址和端口
SERVE_HOST = '127.0.0.1'
SERVE_PORT = 23456


def handle_client(proxy_socket):

    # 接收 CONNECT 请求
    connect_data = proxy_socket.recv(4096)
    
    # 解析 CONNECT 请求，获取目标主机和端口
    TARGET_HOST = connect_data.split(b' ')[1].split(b':')[0]
    TARGET_PORT = int(connect_data.split(b' ')[1].split(b':')[1])

    # 连接目标服务器
    target_socket = socket.create_connection((TARGET_HOST, TARGET_PORT))

    # 响应客户端的 CONNECT 成功
    proxy_socket.sendall(b'HTTP/1.1 200 Connection Established\r\n\r\n')

    # 启动两个线程，分别进行双向转发
    thread1 = threading.Thread(target=forward_data, args=(proxy_socket, target_socket))
    thread2 = threading.Thread(target=forward_data, args=(target_socket, proxy_socket))

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
    proxy_server.bind((SERVE_HOST, SERVE_PORT))
    proxy_server.listen(5)

    print(f"Proxy server listening on {SERVE_HOST}:{SERVE_PORT}")

    while True:
        proxy_socket, addr = proxy_server.accept()
        print(f"Accepted connection from {addr[0]}:{addr[1]}")
        
        proxy_client_handler = threading.Thread(target=handle_client, args=(proxy_socket,))
        proxy_client_handler.start()

if __name__ == "__main__":
    main()
