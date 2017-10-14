all:
	g++ Main.cpp -o mat
test:
	./mat
clean:
	rm -rf ./mat
