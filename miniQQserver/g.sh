#!/bin/bash

g++ -g ./jsoncpp-master/dist/jsoncpp.cpp ./jsoncpp-master/dist/json/json-forwards.h ./jsoncpp-master/dist/json/json.h main.cpp SOCKET.h SOCKET.cpp USER.h USER.cpp -o a.out
