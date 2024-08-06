import socket

def handle_request():
    try:
        # 创建 socket 监听请求
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.bind(('127.0.0.1', 23456))
        server_socket.listen(1)

        print("[***]Server listening on port 23456")

        while True:
            # 接受连接
            client_socket, addr = server_socket.accept()
            print(f"[***]Accepted connection from {addr}")

            # 接收请求
            request_data = client_socket.recv(4096)

            # 解析自定义字段
            user_dest_ip = None
            user_dest_port = None

            headers = request_data.split(b'\r\n\r\n', 1)[0].split(b'\r\n')[1:]
            for header in headers:
                if header.startswith(b'User-Dest-IP'):
                    user_dest_ip = header.split(b':', 1)[1].strip().decode('utf-8')
                elif header.startswith(b'User-Dest-Port'):
                    user_dest_port = header.split(b':', 1)[1].strip().decode('utf-8')

            print(f"[***]User Dest IP: {user_dest_ip}, User Dest Port: {user_dest_port}")
            
            data = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title>My Proxy</title>\r\n</head>\r\n<body>\r\n<!-- Your modified content here -->\r\n</body>\r\n</html>\r\n\r\n"
            client_socket.send(data.encode())

    except KeyboardInterrupt:
        print("[***]terminated.")
    finally:
        server_socket.close()



if __name__ == "__main__":
    handle_request()
