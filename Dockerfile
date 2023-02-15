FROM ubuntu:latest
RUN apt-get update
RUN apt-get install nasm -y
RUN apt-get install gcc -y
RUN apt-get install make -y
WORKDIR /app
