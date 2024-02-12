import socket
import time

HOST = '127.0.0.1'
PORT = 8000
server_addr = (HOST, PORT)

send_base = 0
next_seq_num = 0

cwnd_size = 3
num_pkt = 10

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    while next_seq_num < num_pkt and next_seq_num - send_base < cwnd_size:
        clientMessage = str(next_seq_num)
        client.sendto(clientMessage.encode(), server_addr)
        print('base ', send_base, ' send ', next_seq_num)
        next_seq_num += 1
        
    client.settimeout(5)
    try:
        serverMessage, addr = client.recvfrom(1024)
        print('ACK = ', serverMessage)
        if (send_base == int(serverMessage)):
            send_base += 1
        if send_base == num_pkt:
            break

    except Exception as e:
        print('timeout')
        next_seq_num = send_base