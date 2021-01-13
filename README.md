# MyReferenceCodes

This repository is containing some the reference codes, which helps me revising on some important topics. Total object in this repository is 9.

## CPP > winsock-codes

### tcpip-simple-server.cpp
[Code](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/CPP/winsock-codes/tcpip-simple-server.cpp)
>This code was built with VS2017 community edition. Purpose of this code is to create a simple web server using C++ Winsock library. On receiving a message, it will be bounced back to the original client. This server can receive a message from a single client only. Make sure to check [tcpip-simple-client.cpp](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/CPP/winsock-codes/tcpip-simple-client.cpp) for client side code.

### tcpip-simple-client.cpp
[Code](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/CPP/winsock-codes/tcpip-simple-client.cpp)
>This code was built with VS2017 community edition and purpose of this code is to create a simple client using C++ Winsock library which can connect to the same server, created with [tcpip-simple-server.cpp](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/CPP/winsock-codes/tcpip-simple-server.cpp) and it can also send message to the server, and in return, it receives the same message.

### tcp-server-1thread-nclinet.cpp
[Code](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/CPP/winsock-codes/tcp-server-1thread-nclinet.cpp)
>This code was built with VS2017 and creates a simple tcp server, which accepts multiple client in the same session, but using a single thread only.

## Python > Flask

### Before_Request_Decorator_Ex
[Code](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/Python/Flask/Before_Request_Decorator_Ex/before_request_dec_ex.py)
>This code, along with blueprint, demonstrates, how `before_request` and `before_app_request` decorators from flask module works. Similary `after_request` and `teardown_request` works.

## Python > Advance

### singletons
[Code 1](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/Python/Advance/singletons/method1.py)
[Code 2](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/Python/Advance/singletons/method2.py)
>These codes demonstates, how to create a singletone class in python. The first code overrides the magic method called `__new__` which runs before `__init__` runs, and creates the object. The second method uses a decorator to create a SingleTon class.

## Python > BeautifulSoup

### weather_dotcom_scrapping.py
[Code](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/Python/BeautifulSoup/weather_dotcom_scrapping.py)
>This code utilizes the power of `BeautifulSoup 4` to scrap the web page data. In this example code I fetched the web page from [weather.com](https://weather.com/en-IN/weather/today/l/22.57,88.36?par=google&temp=c) using `requests` module and on success, I did a data scrapping with `beautifulsoup4`. Finally I took out various weather data from the response.

## Python > PyPi-Package-Release

### twine-upload.md
[Doc](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/Python/PyPi-Package-Release/twine-upload.md)
>This document provides a brief introduction, on how to upload a python package to [PyPi](https://pypi.org/) or Python Package Index.

## C > DataStructure

### hash_table.c
[Code](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/C/DataStructure/hash_table.c)
>This code will let us create hash table, which will have keys of type `char*` and values of type `int`. With this, we can store a key-value pair, we can read them either as a pair or as array of key and array of value only.

## Javascript > redux-tutorial-basic

### index.js
[Code](https://github.com/antaripchatterjee/MyReferenceCodes/blob/master/Javascript/redux-tutorial-basic/index.js)
>This is a basic illustration of redux functionality in javascript application. Redux is a state management library in a predictable way for javascript applications. Everytime a `dispatch` function is called, the state is managed and updated, which can be viewed with `getState` method. Before testing this code, one musy install redux inside the folder `/MyReferenceCodes/Javascript/redux-tutorial-basic` folder by running the command, `npm install redux`.
