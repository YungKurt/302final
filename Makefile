TARGET=my_arp
OBJ=my_arp.o arp_functions.o arp_main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc -o $@ $^

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
