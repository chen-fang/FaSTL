GCC=g++
GFLAGS=-Wall -g -std=c++11 -O3
FLAGS=-D ET_TEST
DUMP=-D DUMP_FREELIST

SRC=./*.cpp

OUT= *.out


g:
	$(GCC) $(GFLAGS) $(FLAGS) $(DUMP) $(SRC) -o $(OUT)

clean:
	rm -rf $(OUT) ./*~ ./*.o
