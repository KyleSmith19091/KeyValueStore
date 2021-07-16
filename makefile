run:
	g++ -std=c++11 ./src/*.cpp -I ./include -o ./build/main
	./build/main

clean:
	rm -f ./build/main