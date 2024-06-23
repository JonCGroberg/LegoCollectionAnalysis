run_and_build: clean build run
build:
	mkdir -p build
	g++ -std=c++11 src/main.cpp -o build/main
run:
	build/main
clean:
	rm -r build
