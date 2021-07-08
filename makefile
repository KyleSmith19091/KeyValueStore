run:
	g++ ./src/*.cpp -I ./include -o main
	./main

clean:
	rm -f main