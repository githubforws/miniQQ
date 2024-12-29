#!/bin/bash

netstat -tulpn

lsof -i:$1

#netstat -tulpn
