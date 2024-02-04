binaries = wcat wgrep

.PHONY: wcat wgrep

wcat:
	gcc -Werror -Wall -o wcat wcat.c
wgrep:
	gcc -Werror -Wall -o wgrep wgrep.c
clean:
	rm -rf *.o $(binaries)
