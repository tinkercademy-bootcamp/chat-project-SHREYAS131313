CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++20 -O3

all: build server client  

server: build server.cc ./class/server_class.cc  ./shared/shared.cc
	$(CXX) $(CXXFLAGS) -o build/server server.cc ./class/server_class.cc  ./shared/shared.cc

client: build client.cc ./class/client_class.cc ./shared/shared.cc
	$(CXX) $(CXXFLAGS) -o build/client client.cc ./class/client_class.cc ./shared/shared.cc

build: 
	mkdir -p build

clean:
	rm -f build/server build/client
	rm -d build
