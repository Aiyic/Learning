import socket
import threading

# 代理客户端的监听地址和端口
PROXY_HOST = '127.0.0.1'
PROXY_PORT = 12345

# 代理服务器的地址和端口
SERVE_HOST = '127.0.0.1'
SERVE_PORT = 23456

def handle_client(client_socket):
    # 连接目标服务器
    serve_socket = socket.create_connection((SERVE_HOST, SERVE_PORT))

    # 启动两个线程，分别进行双向转发
    thread1 = threading.Thread(target=forward_data, args=(client_socket, serve_socket))
    thread2 = threading.Thread(target=forward_data, args=(serve_socket, client_socket))

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
    proxy_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    proxy_client.bind((PROXY_HOST, PROXY_PORT))
    proxy_client.listen(5)

    print(f"Proxy client listening on {PROXY_HOST}:{PROXY_PORT}")

    while True:
        client_socket, addr = proxy_client.accept()
        print(f"Accepted connection from {addr[0]}:{addr[1]}")
        
        client_handler = threading.Thread(target=handle_client, args=(client_socket,))
        client_handler.start()

if __name__ == "__main__":
    main()

# 方式二
# 需要支持proxy
# export http_proxy="http://127.0.0.1:12345"
# export https_proxy="http://127.0.0.1:12345"
