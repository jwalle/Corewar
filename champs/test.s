.name "test"
.comment "test"

l2:		st r1, 6
		live %1

live:	live %1
		fork %-20

l3:		and r2, %1768515945, r2
