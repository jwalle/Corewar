.name "test"
.comment "test"

# plop:
# 	ld %1, r2
# 	# fork %:plop
# 	aff r2
# 	zjmp %16

# 	sti r1, %:plop, %1
# 	and r1, %0, r1

# f2:		zjmp %:plop


plop:
		st r2, -265
		st r2, -276
		st r2, -287
		st r2, -298
		st r2, -309
		st r2, -318
		st r2, -327
		st r2, -336
		st r2, -345
		st r2, -276
		st r2, -287
		st r2, -298
		st r2, -309
		st r2, -318
		st r2, -327
		st r2, -336
		st r2, -345	
		st r2, -276
		st r2, -287
		st r2, -298
		st r2, -309
		st r2, -318
		st r2, -327
		st r2, -336
		st r2, -345	
		st r2, -276
		st r2, -287
		st r2, -298
		st r2, -309
		st r2, -318
		st r2, -327
		st r2, -336
		st r2, -345	
		st r2, -276
		st r2, -287
		st r2, -298
		st r2, -309
		st r2, -298
		st r2, -309
		st r2, -318
		st r2, -327
		zjmp %:plop2

plop2:
		st r2, -336
		st r2, -345
		st r2, -276
		st r2, -287
		st r2, -298
		st r2, -309
		st r2, -318
		st r2, -327
		st r2, -336
		st r2, -345	
		st r2, -276
		st r2, -287
		st r2, -298
		st r2, -309
		st r2, -318
		st r2, -327
		st r2, -336
		st r2, -345	
		st r2, -276
		st r2, -287
		st r2, -298
		st r2, -309
		st r2, -318
		st r2, -327
		st r2, -336
		st r2, -345	
		st r2, -276
		st r2, -287
		st r2, -298
		st r2, -309
		st r2, -318
		st r2, -327
		st r2, -318
		st r2, -327
		st r2, -336
		st r2, -345
		st r2, -354
		fork %:plop2
