VPATH = src include $(OUT) lib
OUT = build
SDIR = src
PARAM = -I ./include -L ./lib  -lopenblas -lpthread -lgfortran -ggdb

all: main.out

main.out: $(OUT)/main.o $(OUT)/network.o
	gcc -o $@ $^ $(PARAM) 

$(OUT)/main.o: main.c
	gcc -c -o $@ $^ $(PARAM)

$(OUT)/network.o: network.c
	gcc -c -o $@ $^ $(PARAM)

clean:
	rm build/main.o build/network.o main.out

# gcc -o test_cblas_open ./src/main.c -I ./include/ -L./lib -lopenblas -lpthread -lgfortran
