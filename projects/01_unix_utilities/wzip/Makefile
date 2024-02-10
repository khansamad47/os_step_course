binaries = wzip wunzip

.PHONY: wzip wunzip

wzip:
	gcc -Werror -Wall -g -o wzip wzip.c
wunzip:
	gcc -Werror -Wall -o wunzip wunzip.c
clean:
	rm -rf *.o $(binaries)
