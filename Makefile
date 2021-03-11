# Makefile
# Reseni IJC-DU1, 20.3. 2019
# Autor: Dominik Nejedly, FIT
# Slouzi pro preklad danych souboru

# prekladac
CC = gcc

# parametry prekladu
CFLAGS = -O2 -std=c11 -Wall -Wextra -pedantic

all: primes primes-i steg-decode

primes: error.o eratosthenes.o primes.o
	$(CC) $(CFLAGS) -lm error.o eratosthenes.o primes.o -o primes

primes-i: error.o eratosthenes-i.o primes-i.o bit_array.o
	$(CC) $(CFLAGS) -lm error.o eratosthenes-i.o bit_array.o primes-i.o -o primes-i

steg-decode: error.o eratosthenes.o ppm.o steg-decode.o
	$(CC) $(CFLAGS) -lm error.o eratosthenes.o ppm.o steg-decode.o -o steg-decode

primes.o: primes.c
	$(CC) $(CFLAGS) primes.c -c

primes-i.o: primes.c
	$(CC) $(CFLAGS) -DUSE_INLINE primes.c -c -o primes-i.o

eratosthenes.o: eratosthenes.c
	$(CC) $(CFLAGS) eratosthenes.c -c

eratosthenes-i.o: eratosthenes.c
	$(CC) $(CFLAGS) -DUSE_INLINE eratosthenes.c -c -o eratosthenes-i.o

error.o: error.c
	$(CC) $(CFLAGS) error.c -c

bit_array.o: bit_array.c
	$(CC) $(CFLAGS) -DUSE_INLINE bit_array.c -c

steg-decode.o: steg-decode.c
	$(CC) $(CFLAGS) steg-decode.c -c

ppm.o: ppm.c
	$(CC) $(CFLAGS) ppm.c -c

run: primes
	ulimit -s 200000
	time ./primes
	time ./primes-i

clean:
	rm -f primes primes-i steg-decode *.o
