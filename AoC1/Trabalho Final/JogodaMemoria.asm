#Trabalho Final - Por Ulian Gabriel Alff Ramires & Rafael de Mattia

.data
	array: .space 40         # 32 Bytes (4x10) 
	BoasVindas: .asciiz "Bem Vindo ao Jogo da Memoria dos Guris\nOs numeros serao mostrados 1 a 1, e a cada acerto, sera adicionado mais um\n"
	win: .asciiz "Parabens, voce venceu"
 	loose: .asciiz "Voce errou! Boa sorte na proxima!"
	space: .asciiz " "
	newLine: .asciiz "\n"
	space2: .asciiz "----------------------------------------------------------------\n"
	novaRodada: .asciiz "\nNova rodada!!\n"
    
	# Indice
	# $t7 = Rodada Atual    
	# $t6 = Indice J para iterar entre as rodadas
	# $t5 = Indice Auxiliar para acesso ao vetor (J x 4 Bytes)
	# $t4 e $t3 = Temporarios
	# $t2 = Numero de rodadas MAXIMAS
.text
main:
	add $t2, $zero, 10      # Numero de rodadas MAXIMAS, modifique aqui o numero de rodadas maximas
	add $s0, $zero, 30     # Numero de Walls (Clear Screen), modifique aqui o numero de walls
		
	la $a0, BoasVindas
	jal imprimeString
	
continua:
	beqz $t7, pulaNovaRodada
	la, $a0, novaRodada
	jal imprimeString
	
pulaNovaRodada:
	jal gerador
	jal addvetor
	add $t7, $t7, 1     # Incrementa a Rodada atual
	jal imprimeVetor
		
	li $a0, 4000       # Milissegundos do "SLEEP"
	li $v0, 32
	syscall
	
	add $t0, $zero, 0
	
loop:			# Loop para impressao do Clear Screen (walls)
	la $a0, space2
	jal imprimeString
	add $t0, $t0, 1
	bne $t0, $s0, loop
	add $t5, $zero, 0
		
loopRodada:		# Insersao e checagem de valores inseridos com os valores do vetor
	beq $t7, $t6, continua
	jal jogadorDigita
	lw  $t4, array($t5)
	add $t5, $t5, 4
	bne $a1, $t4, errou # Checagem do numero inserido com o numero gerado
	add $t6, $t6, 1
	bne $t7, $t6, loopRodada
	
	# Final da RODADA (apos usuario acertar todos os numeros da rodada ATUAL)
	add $t6, $zero, 0 # Zera o J	
	beq $t7, $t2, venceu  
	beq $t1, $zero continua #Caso nao seja a ULTIMA RODADA, pula para a PROXIMA
		
errou:
	la $a0, loose
	jal imprimeString
	li $v0, 10
	syscall

venceu:
	la $a0, win
	jal imprimeString
	li $v0, 10
	syscall

jogadorDigita:
	li $v0, 5              
	syscall 
	move $a1, $v0
	jr $ra
	
gerador: 
	li $a0, 1
	li $a1, 100
	li $v0, 42
	syscall               
	move $a1, $a0	
	jr $ra 
	
imprimeString:
	li $v0, 4
	syscall
	jr $ra
	
addvetor:
	mul $t4, $t7, 4
	sw $a1, array($t4)
	jr $ra
	
imprimeVetor:
	li $v0, 1
	add $t3, $zero, 0
	add $t4, $zero, 0
	
	loopImprime:
		li $v0, 1
		lw $a0, array($t3)
		syscall
		
		li $v0, 4
		la $a0, space
		syscall
		
		addi $t3, $t3, 4
		beq $t7, $t4, final # Apos imprimir o ultimo numero do vetor, sai do loopImprime
		addi $t4, $t4, 1
		bne  $t7, $t4, loopImprime
		
		final:
		li $v0, 4
		la $a0, newLine
		syscall
		
		jr $ra
