.name "test"
.comment "test"

	sti r1, %:plop, %1
	and r1, %0, r1

plop:   live %1
		zjmp %:plop
