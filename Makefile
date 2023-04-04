CC= gcc        # compilateur
CFLAGS= -Wall  # options de compilation pour les sources C

sources= test_paillier.c paillierCles.c paillierDecryptage.c paillierEncryptage.c paillierParametre.c base.c
objets= $(sources:.c=.o)

client: client.c helper.c
	$(CC) $^ -o $@ -lm -lgmp

server: server.c helper.c
	$(CC) $^ -o $@ -lm -lgmp

test: $(objets)
	$(CC) -o $@ $^ -lm -lgmp

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -lgmp



.PHONY: clean

clean: 
	rm -f test *.o
