all:
	gcc -g client.c -o client
	gcc -g server.c -o server

clean:
	rm -fv client server
