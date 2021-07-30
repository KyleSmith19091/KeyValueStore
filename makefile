run:
	g++ -std=c++11 ./src/*.cpp -I ./include -O3 -o ./build/main
	./build/main

clean:
	rm -f ./build/main
