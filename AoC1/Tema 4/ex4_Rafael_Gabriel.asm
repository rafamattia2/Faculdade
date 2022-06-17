#Exercício 13 - Por Ulian Gabriel Alff Ramires & Rafael de Mattia

.data
	pergunta: .asciiz "\nEscreve sua frase que deseja inverter o tamanho das letras: "
	resposta: .asciiz "\nAqui esta sua frase invertida: "

.text

main:
	la $a0, pergunta
	jal imprimeString
	li $v0, 8
	la $a0, 0x10010000
	li $a1, 256
	syscall

loop:
	lb $t1, 0x10010000($t0)
	beq $t1, 0, exit
	blt $t1, 'a', grande
	bgt $t1, 'z', grande
	jal letraMinuscula
	addi $t0, $t0, 1
	j loop

grande:
	blt $t1, 'A', naoLetra
	jal letraMaiuscula
	addi $t0, $t0, 1
	j loop

naoLetra:
	addi $t0, $t0, 1
	j loop

exit:
	la $a0, resposta
	jal imprimeString
	li $v0, 4
	la $a0, 0x10010000
	syscall

	li $v0, 10
	syscall

letraMaiuscula:
	add $t1, $t1, 32
	sb $t1, 0x10010000($t0)
	
	jr $ra

letraMinuscula:
	sub $t1, $t1, 32
	sb $t1, 0x10010000($t0)

	jr $ra
	
imprimeString:

	li $v0, 4
	syscall
	jr $ra
