all:	red_black_driver

red_black_driver:	red_black_driver.o
	g++ -o red_black_driver red_black_driver.o

red_black_driver.o:	red_black_driver.cpp
	g++ -c -Wall -g red_black_driver.cpp

clean:
	rm red_black_driver{,.o}