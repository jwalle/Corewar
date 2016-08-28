
.name		"tests"


.comment	"batterie

;
#

# de test"

test1:
test2:
test3:
test:
test:
#	st		r17, 6
#	st		r-1, 6
;	st		r0, 6
;	st		r1, -2147483648
;	st		r1, 2147483647
;	live	%-2147483648
;	live	%2147483647
;	st		r1, :ardeftgt
;	fork	%:ardeftgt
	sti		r1,%:entry,%1
;	wat		%:ardeftgt

entry:
	fork	%:ardeftgt
	st		r1, 6
	live	%42
	fork	%:test
	st		r1, 6
	live	%42
	fork	%:ardefgen

ardeftgt:

ardefgeni:
	st 		r1, 6

ardefgen:
	live 	%213904
	fork 	%:ardefgen

test:
	sti		r1, %:ardefgen, %1
	st		r1, 6
	live	%43123
	sti		r1, %:ardeftgt, %1
	ld		%-6, r2
	ld		%-6, r3
	ld		%150994953, r4
	ld		%-186, r5

avdeftgt:
sou:
test:
