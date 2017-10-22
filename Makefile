PREFIX=/usr/lib
bin=/usr/local/bin
LIB_NAME=libmatrix.so


all: Main.cpp so
	g++ Main.cpp -L. -lmatrix -o mat

clean:
	rm -rf mat $(LIB_NAME)

so: Matrix.h Matrix.cpp
	g++ -shared -fPIC Matrix.cpp -o $(LIB_NAME) && \
sudo cp $(LIB_NAME) $(PREFIX)
