.data
reservedspace: .space 1024
_newline: .asciiz "\n"
DataString0: .asciiz "\n"

.text
main:
	
	# 1 :  =  func main begin : 
	sub $sp, $sp, 200
	la $fp, ($sp)
	sub $sp, $sp, 36
	# 2 : n = 2 = 
	li $s6, 0
	sub $s7, $fp, $s6
	lw $t1, 0($s7)
	addi $t1, $0, 2
	li $s6, 0
	sub $s7, $fp, $s6
	sw $t1, 0($s7)
	# 3 : n = 0 = 
	li $s6, 0
	sub $s7, $fp, $s6
	lw $t2, 0($s7)
	addi $t2, $0, 0
	li $s6, 0
	sub $s7, $fp, $s6
	sw $t2, 0($s7)
	Label3:
	# 4 : @temp1 = n < 2
	addi $t6, $0, 2
	li $s6, 0
	sub $s7, $fp, $s6
	lw $t3, 0($s7)
	li $s6, 4
	sub $s7, $fp, $s6
	lw $t4, 0($s7)
	slt $t4, $t3, $t6
	li $s6, 0
	sub $s7, $fp, $s6
	sw $t3, 0($s7)
	li $s6, 4
	sub $s7, $fp, $s6
	sw $t4, 0($s7)
	# 5 :  = IF GOTO @temp1
	li $s6, 4
	sub $s7, $fp, $s6
	lw $t0, 0($s7)
	bne $0, $t0, Label9
	li $s6, 4
	sub $s7, $fp, $s6
	sw $t0, 0($s7)
	# 6 :  =  GOTO 
	j Label16
	Label6:
	# 7 : @temp2 = n +int 1
	li $s6, 12
	sub $s7, $fp, $s6
	lw $t5, 0($s7)
	li $s6, 0
	sub $s7, $fp, $s6
	lw $s0, 0($s7)
	addi $t7, $0, 1
	add $t5, $s0, $t7
	li $s6, 12
	sub $s7, $fp, $s6
	sw $t5, 0($s7)
	li $s6, 0
	sub $s7, $fp, $s6
	sw $s0, 0($s7)
	# 8 : n = @temp2 = 
	li $s6, 0
	sub $s7, $fp, $s6
	lw $s1, 0($s7)
	li $s6, 12
	sub $s7, $fp, $s6
	lw $s2, 0($s7)
	move $s1, $s2
	li $s6, 0
	sub $s7, $fp, $s6
	sw $s1, 0($s7)
	li $s6, 12
	sub $s7, $fp, $s6
	sw $s2, 0($s7)
	# 9 :  =  GOTO 
	j Label3
	Label9:
	# 10 :  = n param 
	li $s6, 0
	sub $s7, $fp, $s6
	lw $s3, 0($s7)
	move $a0, $s3
	li $s6, 0
	sub $s7, $fp, $s6
	sw $s3, 0($s7)
	# 11 : @temp3 =  return place 
	# 12 : @temp3 = print_int CALL 2
	li $v0, 1
	syscall
	# 13 :  = "\n" param 
	la $a0, DataString0
	# 14 : @temp4 =  return place 
	# 15 : @temp4 = print_string CALL 2
	li $v0, 4
	syscall
	# 16 :  =  GOTO 
	j Label6
	Label16:
	# 17 :  = 0 RETURN 
	li $a0, 0
	li $v0, 10
	syscall
	# 18 :  =  func end 

