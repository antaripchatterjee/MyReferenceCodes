# MyReferenceCodes

This repository is containing some the reference codes, which helps me revising on some important topics. Total file count in this repository is 2.

## CPP > winsock-codes

### tcpip-simple-server.cpp
[Code](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/CPP/winsock-codes/tcpip-simple-server.cpp)
>This code was built with VS2017 community edition. Purpose of this code is to create a simple web server using C++ Winsock library. On receiving a message, it will be bounced back to the original client. This server can receive a message from a single client only. Make sure to check [tcpip-simple-client.cpp](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/CPP/winsock-codes/tcpip-simple-client.cpp) for client side code.

### tcpip-simple-client.cpp
[Code](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/CPP/winsock-codes/tcpip-simple-client.cpp)
>This code was built with VS2017 community edition and purpose of this code is to create a simple client using C++ Winsock library which can connect to the same server, created with [tcpip-simple-server.cpp](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/CPP/winsock-codes/tcpip-simple-server.cpp) and it can also send message to the server, and in return, it receives the same message.

### before_request_dec_ex.py
[Code](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/Python/Flask/Before_Request_Decorator_Ex/before_request_dec_ex.py)
>This code, along with blueprint, demonstrates, how `before_request` and `before_app_request` decorators from flask module works. Similary `after_request` and `teardown_request` works. 