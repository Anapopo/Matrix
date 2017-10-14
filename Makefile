all: Main.cpp
	g++ Main.cpp -L. -lmatrix -o mat
test:
	./mat
clean:
	rm -rf ./mat
so: Matrix.h Matrix.cpp
	g++ -shared -fPIC Matrix.cpp -o libmatrix.so
