all:	avl_driver

avl_driver:	avl_driver.o
	g++ -o avl_driver avl_driver.o

avl_driver.o:	avl_driver.cpp
	g++ -c -Wall -g -std=c++0x avl_driver.cpp

clean:
	rm *.o avl_driver