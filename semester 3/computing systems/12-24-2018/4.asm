	MOV	SP,#2FH

	MOV	A,#10H
	ANL	A,#20H
	MOV	R0,A
	ACALL	CALC_C
	ORL	A,R0
	ANL	A,#30H
	JMP EXIT

CALC_C:	MOV	A,#25H
	ORL	A,#16H
	ANL	A,#17H
	RET

EXIT:	MOV	P0,A
	END
