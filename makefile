all: build/main

build/main: server.o utils/write_http.o
	clang server.o utils/write_http.o -o build/main

server.o: server.c utils/write_http.h
	clang -Iutils -c server.c -o server.o

utils/create_http.o: utils/write_http.c utils/write_http.h
	clang -Iutils -c utils/write_http.c -o utils/write_http.o
