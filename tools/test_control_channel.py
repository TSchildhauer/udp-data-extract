import socket
import struct

server_ip = "127.0.0.1" 
port = 4000 # control port UDP

# Construct the binary message
operation = 1  # read - 1, write - 2
object_id = 1
property_id = 1
value = 10

# Create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# Set a timeout for receiving responses
sock.settimeout(1)

def send_message(object_id, property_id, operation = 1, value = None):
    # Construct the message
    if operation == 1:
        message = struct.pack(">HHH", operation, object_id, property_id)
    elif operation == 2:
        message = struct.pack(">HHHH", operation, object_id, property_id, value)

    # Send the message
    sock.sendto(message, (server_ip, port))
    # print(f"Sent: {message.hex()}")

# Test lots of properties
# for object_id in range(1,4):
#     for property_id in range(1000):
#         print(f"Testing object {object_id}, property {property_id}")
#         send_message(object_id, property_id)

# Write a value
send_message(1, 170, 2, 8000)