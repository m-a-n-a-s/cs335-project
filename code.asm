.data
reservedspace: .space 1024
_newline: .asciiz "\n"

.text
main:
	
	# 9 :  =  func main begin : 
	sub $sp, $sp, 20
	la $fp, ($sp)
	sub $sp, $sp, 56
	# 10 : a = 2 = 
	li $s6, 0
	sub $s7, $fp, $s6
	lw $s0, 0($s7)
	addi$s0, $0, 2
	li $s6, 0
	sub $s7, $fp, $s6
	sw $s0, 0($s7)
	# 11 : b = 3 = 
	li $s6, 4
	sub $s7, $fp, $s6
	lw $s1, 0($s7)
	addi$s1, $0, 3
	li $s6, 4
	sub $s7, $fp, $s6
	sw $s1, 0($s7)
	# 12 : i = 0 = 
	li $s6, 8
	sub $s7, $fp, $s6
	lw $s2, 0($s7)
	addi$s2, $0, 0
	li $s6, 8
	sub $s7, $fp, $s6
	sw $s2, 0($s7)
	# 13 : j = 1 = 
	li $s6, 12
	sub $s7, $fp, $s6
	lw $s3, 0($s7)
	addi$s3, $0, 1
	li $s6, 12
	sub $s7, $fp, $s6
	sw $s3, 0($s7)
	Label13:
	# 14 :  = a param 
	li $s6, 0
	sub $s7, $fp, $s6
	lw $s4, 0($s7)
	move $a0, $s4
	li $s6, 0
	sub $s7, $fp, $s6
	sw $s4, 0($s7)
	# 15 :  = b param 
	li $s6, 4
	sub $s7, $fp, $s6
	lw $t1, 0($s7)
	move $a1, $t1
	li $s6, 4
	sub $s7, $fp, $s6
	sw $t1, 0($s7)
	# 16 : @temp2 =  return place 
	# 17 : @temp2 = max CALL 3
	jal max
	li $s6, 16
	sub $s7, $fp, $s6
	lw $t2, 0($s7)
	move $t2, $v0
	li $s6, 16
	sub $s7, $fp, $s6
	sw $t2, 0($s7)
	# 18 : @temp3 = i LE_OP @temp2
	li $s6, 16
	sub $s7, $fp, $s6
	lw $t3, 0($s7)
	li $s6, 8
	sub $s7, $fp, $s6
	lw $t4, 0($s7)
	li $s6, 20
	sub $s7, $fp, $s6
	lw $t0, 0($s7)
	sle $t0, $t4, $t3
	li $s6, 16
	sub $s7, $fp, $s6
	sw $t3, 0($s7)
	li $s6, 8
	sub $s7, $fp, $s6
	sw $t4, 0($s7)
	li $s6, 20
	sub $s7, $fp, $s6
	sw $t0, 0($s7)
	# 19 :  = IF GOTO @temp3
	li $s6, 20
	sub $s7, $fp, $s6
	lw $t5, 0($s7)
	bne $0, $t5, Label23
	li $s6, 20
	sub $s7, $fp, $s6
	sw $t5, 0($s7)
	# 20 :  =  GOTO 
	j Label27
	Label20:
	# 21 : @temp4 = i +int 1
	li $s6, 28
	sub $s7, $fp, $s6
	lw $s0, 0($s7)
	li $s6, 8
	sub $s7, $fp, $s6
	lw $s1, 0($s7)
	addi $t7, $0, 1
	add $s0, $s1, $t7
	li $s6, 28
	sub $s7, $fp, $s6
	sw $s0, 0($s7)
	li $s6, 8
	sub $s7, $fp, $s6
	sw $s1, 0($s7)
	# 22 : i = @temp4 = 
	li $s6, 8
	sub $s7, $fp, $s6
	lw $s2, 0($s7)
	li $s6, 28
	sub $s7, $fp, $s6
	lw $s3, 0($s7)
	move $s2, $s3
	li $s6, 8
	sub $s7, $fp, $s6
	sw $s2, 0($s7)
	li $s6, 28
	sub $s7, $fp, $s6
	sw $s3, 0($s7)
	# 23 :  =  GOTO 
	j Label13
	Label23:
	# 24 : @temp5 = j +int 1
	li $s6, 36
	sub $s7, $fp, $s6
	lw $s4, 0($s7)
	li $s6, 12
	sub $s7, $fp, $s6
	lw $t1, 0($s7)
	addi $t7, $0, 1
	add $s4, $t1, $t7
	li $s6, 36
	sub $s7, $fp, $s6
	sw $s4, 0($s7)
	li $s6, 12
	sub $s7, $fp, $s6
	sw $t1, 0($s7)
	# 25 : @temp6 = j *int @temp5
	li $s6, 44
	sub $s7, $fp, $s6
	lw $t2, 0($s7)
	li $s6, 12
	sub $s7, $fp, $s6
	lw $t3, 0($s7)
	li $s6, 36
	sub $s7, $fp, $s6
	lw $t4, 0($s7)
	mult $t3, $t4
	mflo $t2
	li $s6, 44
	sub $s7, $fp, $s6
	sw $t2, 0($s7)
	li $s6, 12
	sub $s7, $fp, $s6
	sw $t3, 0($s7)
	li $s6, 36
	sub $s7, $fp, $s6
	sw $t4, 0($s7)
	# 26 : j = @temp6 = 
	li $s6, 12
	sub $s7, $fp, $s6
	lw $t0, 0($s7)
	li $s6, 44
	sub $s7, $fp, $s6
	lw $t5, 0($s7)
	move $t0, $t5
	li $s6, 12
	sub $s7, $fp, $s6
	sw $t0, 0($s7)
	li $s6, 44
	sub $s7, $fp, $s6
	sw $t5, 0($s7)
	# 27 :  =  GOTO 
	j Label20
	Label27:
	# 28 :  = j param 
	li $s6, 12
	sub $s7, $fp, $s6
	lw $s0, 0($s7)
	move $a0, $s0
	li $s6, 12
	sub $s7, $fp, $s6
	sw $s0, 0($s7)
	# 29 : @temp7 =  return place 
	# 30 : @temp7 = print_int CALL 2
	li $v0, 1
	syscall
	# 31 :  = 0 RETURN 
	li $a0, 0
	li $v0, 10
	syscall
	# 32 :  =  func end 

max:
	# 1 :  =  func max begin : 
	sub $sp, $sp, 72
	sw $t0, 12($sp)
	sw $t1, 16($sp)
	sw $t2, 20($sp)
	sw $t3, 24($sp)
	sw $t4, 28($sp)
	sw $t5, 32($sp)
	sw $t6, 36($sp)
	sw $t7, 40($sp)
	sw $t8, 44($sp)
	sw $t9, 48($sp)
	sw $s0, 52($sp)
	sw $s1, 56($sp)
	sw $s2, 60($sp)
	sw $s3, 64($sp)
	sw $s4, 68($sp)
	sw $ra, 0($sp)
	sw $fp, 4($sp)
	la $fp, 72($sp)
	sub $sp, $sp, 20
	sub $s7, $fp, 76
	sw $a0, 0($s7)
	sub $s7, $fp, 80
	sw $a1, 0($s7)
	# 2 : @temp1 = x > y
	li $s6, 80
	sub $s7, $fp, $s6
	lw $t1, 0($s7)
	li $s6, 76
	sub $s7, $fp, $s6
	lw $t2, 0($s7)
	li $s6, 84
	sub $s7, $fp, $s6
	lw $t3, 0($s7)
	sgt $t3, $t2, $t1
	li $s6, 80
	sub $s7, $fp, $s6
	sw $t1, 0($s7)
	li $s6, 76
	sub $s7, $fp, $s6
	sw $t2, 0($s7)
	li $s6, 84
	sub $s7, $fp, $s6
	sw $t3, 0($s7)
	# 3 :  = IF GOTO @temp1
	li $s6, 84
	sub $s7, $fp, $s6
	lw $t4, 0($s7)
	bne $0, $t4, Label4
	li $s6, 84
	sub $s7, $fp, $s6
	sw $t4, 0($s7)
	# 4 :  =  GOTO 
	j Label6
	Label4:
	# 5 :  = x RETURN 
	li $s6, 76
	sub $s7, $fp, $s6
	lw $t0, 0($s7)
	move $v0, $t0
	b maxend
	li $s6, 76
	sub $s7, $fp, $s6
	sw $t0, 0($s7)
	# 6 :  =  GOTO 
	j Label8
	Label6:
	# 7 :  = y RETURN 
	li $s6, 80
	sub $s7, $fp, $s6
	lw $t5, 0($s7)
	move $v0, $t5
	b maxend
	li $s6, 80
	sub $s7, $fp, $s6
	sw $t5, 0($s7)
	# 8 :  =  func end 
	maxend:
	addi $sp, $sp, 20
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	lw $a0, 8($sp)
	lw $t0, 12($sp)
	lw $t1, 16($sp)
	lw $t2, 20($sp)
	lw $t3, 24($sp)
	lw $t4, 28($sp)
	lw $t5, 32($sp)
	lw $t6, 36($sp)
	lw $t7, 40($sp)
	lw $t8, 44($sp)
	lw $t9, 48($sp)
	lw $s0, 52($sp)
	lw $s1, 56($sp)
	lw $s2, 60($sp)
	lw $s3, 64($sp)
	lw $s4, 68($sp)
	addi $sp, $sp, 72
	jr $ra
	Label8:

