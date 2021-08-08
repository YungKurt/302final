TARGET=my_lswitch
OBJ=my_lswitch.o lswitch_functions.o lswitch_main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc -g -o $@ $^

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
