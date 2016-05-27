UdpServer: main.o test1.o server.o
	${CC} ${CFLAGS}  main.o test1.o server.o -o UdpServer 
test1.o: test1.h head.h test1.cpp
	${CC} ${CFLAGS} -c test1.cpp
main.o:	test1.h   main.cpp
	${CC} ${CFLAGS} -c main.cpp
server.o: head.h server.cpp
	${CC} ${CFLAGS} -c server.cpp
	    	
CC= g++
CFLAGS= -pg  -g

clean:
	rm -f *.o UdpServer
