#Exerc�cio 2 - Por Rafael de Mattia & Gabriel Alff Ramires

.data
a: .word 3                            # 0x10010000
b: .word 1                            # 0x10010004
c: .word 2                            # 0x10010008
.text

	# Acessando os dados da mem�ria a partir do Label e colocando nos registradores t0-t2
		
	lw $t0 a
	lw $t1 b
	lw $t2 c
	
	lui $t4, 0x1001
	add $t4, $t4, 12
	
	# Testes de Mediana | g = Greater Than (ou seja, AgB = A Greather Than B)
	
	bgt $t0, $t1, AgB		
	j BgA
	
		AgB:				
		bgt $t1, $t2, B 
		j AgB_CgB
			
			AgB_CgB:
			bgt $t0, $t2, C
			j A
	
	BgA:
	bgt $t0, $t2, A
	j BgA_CgA
	
		BgA_CgA:
		bgt $t1, $t2, C
		j B
	
	
	A:
	sw $t0, ($t4) # Mediana A salva em 0x1001000C
	j FIM
	
	B:
	sw $t1, ($t4) # Mediana B salva em 0x1001000C
	j FIM
	
	C: 
	sw $t2, ($t4) # Mediana C salva em 0x1001000C
	j FIM
	
	
	FIM:
	
