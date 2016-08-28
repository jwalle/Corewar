# Corewar

In this game, computer programs (called "Champions") compete in a virtual arena for digital supremacy. Champions are written in an Assembly dialect called "Redcode".

[Wikipedia article](https://en.wikipedia.org/wiki/Core_War)

This is our implementation of the game Virtual Machine and assembler in the C language.

```
Usage:      ./corewar [-v -n -dump N] [-number N] <champion1.cor> <...>
	        -v		    : verbose (prints various informations about then game walkthrough.)
	        -n   	    : provide Ncurses visualisation of the game.
          	-dump N		: Dumps the memory after N cycles, then exit the game.
	        -number N	: give the next specified player the number N.
```

![plop](http://i.imgur.com/QRda96t.png)