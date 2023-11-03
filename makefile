
continuoussimtimer.o: objs
	g++ -c -o objs/continuoussimtimer.o src/continuoussimtimer.cpp

objs: 
	mkdir objs

clean:
	rm -r objs