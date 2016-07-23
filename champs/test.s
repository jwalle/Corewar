.name "test"
.comment "test"


l2:		sti r1, %:live, %1
		and r1, %0, r1

l4:		and r3, %1768515945, r3

live:	live %1
		fork %:l4

l3:		and r2, %1768515945, r2
