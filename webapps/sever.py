import socket

server_ip = '192.168.35.77'
server_port = 12345

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((server_ip, server_port))
server_socket.listen(1)

print("서버 대기 중...")

client_socket, client_address = server_socket.accept()
print("클라이언트가 연결되었습니다:", client_address)

while True:
    data = client_socket.recv(1024)
    if not data:
        break
    print("수신한 데이터:", data.decode())
    client_socket.send("데이터 수신 완료".encode())

client_socket.close()
server_socket.close()