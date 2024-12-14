import socket
import struct

server_ip = "127.0.0.1" 
port = 4000 # control port UDP

# Construct the binary message
operation = 1  # read - 1, write - 2
object_id = 1
property_id = 0

message = struct.pack(">HHH", operation, object_id, property_id)

# Send the message
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(message, (server_ip, port))
print(f"Sent: {message.hex()}")
