# math_protocol
This repository contains a custom protocol designed using C programming language over UDP client-server platform. The UDP clinet contains the client information to send to the server. The client can send 3 bytes of data where the first byte is an operator (+,-) and the second and third bytes are the values needs to operated. The UDP server receives the bytes from the client and performs the operation according to the operator defined in the client and returns the result to the client. The header file contains the original structure for the math protocol. 

Please use linux environment for this operation.

On the Server:
• $ make udpserver << this compiles the source, links the modules, and creates an executable
• $ ./udpserver << this runs the server

On the Client:
• $ make udpclient << this compiles the source, links the modules, and creates an executable
• $ ./udpclient <server IP> 3000 << this runs the client, directing it to the server at port 3000
