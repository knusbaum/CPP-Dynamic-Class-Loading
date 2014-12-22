
all:
	g++ -shared -fPIC square.cpp -o square.so
	g++ -shared -fPIC triangle.cpp -o triangle.so
	g++ -std=c++11 main.cpp -ldl -o dltest

clean:
	-@rm *~ *.o dltest *.so
