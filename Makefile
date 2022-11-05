SRC := src/py_hfst_ospell

.DEFAULT_GOAL := ${SRC}/_py_hfst_ospell.so

${SRC}/_py_hfst_ospell.so : ${SRC}/py_hfst_ospell.o ${SRC}/py-hfst-ospell_wrap.o
	gcc -shared ${SRC}/py-hfst-ospell ${SRC}/py-hfst-ospell_wrap.o -o ${SRC}/_py_hfst_ospell.so -lpython3.7m

${SRC}/py-hfst-ospell : ${SRC}/py-hfst-ospell.cpp
	gcc -c -fPIC -I/usr/include/python3.5m ${SRC}/py-hfst-ospell.cpp -o ${SRC}/py-hfst-ospell

${SRC}/py-hfst-ospell_wrap.o : ${SRC}/py-hfst-ospell_wrap.c
	gcc -c -fPIC -I/usr/include/python3.5m ${SRC}/py-hfst-ospell_wrap.c -o ${SRC}/py-hfst-ospell_wrap.o

${SRC}/py-hfst-ospell_wrap.c ${SRC}/py_hfst_ospell.py : ${SRC}/py-hfst-ospell ${SRC}/py-hfst-ospell
	swig -python ${SRC}/py-hfst-ospell

clean:
	rm -f ${SRC}/*.o ${SRC}/*.so ${SRC}/py-hfst-ospell_wrap.* ${SRC}/py_hfst_ospell.py*

.PHONY: clean
