#Exerc�cio 3 - Por Rafael de Mattia & Gabriel Alff Ramires

.data
	msgUser: .asciiz "Este programa calcula a media entre tres valores"
	first: .asciiz "\nDigite o primeiro valor: "
	second: .asciiz "\nDigite o segundo valor: "
	third: .asciiz "\nDigite o terceiro valor: "
	msgUser2: .asciiz "\nA media entre os tres valores �: "
	

.text
main:
	la $a0, msgUser    #print msgUser
	jal imprimeString
	
	jal readValues
	
	jal calcMedia
   
	la $a0, msgUser2		#print msgUser2
	jal imprimeString

	la $a0, ($t5)
	jal imprimeInt

	li $v0, 10
	syscall


readValues:
	la $a0, first  		#print first
	li $v0, 4
	syscall 

	li $v0, 5           #le o primeiro valor e armazena em a1    
	syscall 
	move $a1, $v0
             
	la $a0, second	      #print second
	li $v0, 4
	syscall

	li $v0, 5            #le o segundo valor e armazena em a2   
	syscall 
	move $a2, $v0
         
	la $a0, third		#print third
	li $v0, 4
	syscall

	li $v0, 5            #le o terceiro valor e armazena em a3   
	syscall 
	move $a3, $v0
	
	jr $ra

calcMedia:
	add $t5, $a1, $a2
	add $t5, $t5, $a3
	add $a3, $zero, 3
	div $t5, $a3
	mflo $t5
	jr $ra

imprimeString:
	li $v0, 4
	syscall
	jr $ra

imprimeInt:
	li $v0, 1
	syscall
	jr $ra
	
