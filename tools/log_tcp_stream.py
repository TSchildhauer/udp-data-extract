import socket
import argparse

# Parse command-line arguments
parser = argparse.ArgumentParser(description="Log TCP stream data")
parser.add_argument("-p", "--port", type=int, default=4001, help="TCP port to connect to")
args = parser.parse_args()

server_ip = "127.0.0.1"  # Replace with the actual server IP if not local
tcp_port = args.port  # Use the port from the command-line argument

# Create a TCP client socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect to the server
    sock.connect((server_ip, tcp_port))
    print(f"Connected to {server_ip}:{tcp_port}")

    # Read data continuously
    while True:
        data = sock.recv(1024)
        if not data:
            print("Connection closed by server")
            break
        print(f"Received data: {data.decode(errors='replace')}")
finally:
    sock.close()
    print("Socket closed")