all: build
	g++ src/tcp_echo_client.cc -o build/client
	g++ src/tcp_echo_server.cc -o build/server
assemb: build
	g++ -S src/tcp_echo_client.cc -o build/client.s
	g++ -S src/tcp_echo_server.cc -o build/server.s

build:
	mkdir -p build
clean:
	rm -f build/client build/server
	rm -d build