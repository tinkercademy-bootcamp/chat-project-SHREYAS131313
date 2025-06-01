CXX_FLAGS := g++ -O2 -Wall -g -std=c++20
LD_FLAGS := -fsanitize=address

all: build
	$(CXX_FLAGS) $(LD_FLAGS) shared.cc class-main-client.cc class/client.cc -o build/class_client
	$(CXX_FLAGS) $(LD_FLAGS) shared.cc class-main-server.cc class/server.cc -o build/class_server

build:
	mkdir -p build
clean:
	rm -f build/class_client build/class_server
	rm -d build