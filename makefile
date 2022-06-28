VPATH = src include $(OUT) lib
OUT = build
SDIR = src
PARAM = -I ./include -L ./lib  -lopenblas -lpthread -lgfortran

all: main.out

main.out: main.o network.o
	gcc -o $@ $^ $(PARAM) 

main.o: main.c
	gcc -c -o $(OUT)/$@ $^ $(PARAM)

network.o: network.c
	gcc -c -o $(OUT)/$@ $^ $(PARAM)



clean:
	rm build/main.o build/network.o main.out

# gcc -o test_cblas_open ./src/main.c -I ./include/ -L./lib -lopenblas -lpthread -lgfortran
