#!/bin/sh

	./corewar -dump $1 champs/helltrain.cor > test/test1.txt
	./goinfre/corewar -d $1 champs/helltrain.cor > test/test2.txt
	diff test/test1.txt test/test2.txt
exit 0
