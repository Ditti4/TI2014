CC?="cc"
all: aufg1 aufg2 aufg3 aufg4 aufg5 aufg6 aufg7 aufg7_2 aufg8_1 aufg8_2
.PHONY: all

%: %.c
	$(CC) -o $@ $^

aufg7_2: result.o aufg7_2.o
	gcc -o $@ $^
		
result.o: ../result.c
	gcc -o $@ -c $^

aufg7_2.o: aufg7_2.c
	gcc -o $@ -c $^

.PHONY: clean
clean:
	rm -f aufg1 aufg2 aufg3 aufg4 aufg5 aufg6 aufg7 aufg7_2 aufg8_1 aufg8_2
	rm -f *.o
	rm -f *~
