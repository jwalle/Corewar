clear ; make ; rm champs/bee_gees.cor ; ./asm champs/bee_gees.s
mv champs/bee_gees.cor champs/bee_gees.cor1
./real_asm champs/bee_gees.s
hexdump -vC champs/bee_gees.cor > them
hexdump -vC champs/bee_gees.cor1 > me
diff champs/bee_gees.cor*

#bee_gees
#bigzork
#fluttershy
#helltrain
#turtle
#zork
#test
#ins
#void
