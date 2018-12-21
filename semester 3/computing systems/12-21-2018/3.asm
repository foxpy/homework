; assume every port is empty before execution
MOV P1, #00H
MOV P2, #00H
MOV P3, #00H
; ... except for P0, which is our input source
; it should be filled with data before execution

; stage 1
MOV C, P0.0
ORL C, P0.1
CPL C
MOV 0H, C
MOV C, P0.2
ANL C, P0.3
CPL C
MOV 1H, C
MOV C, P0.4
ORL C, P0.5
MOV 2H, C

; stage 2
MOV C, 0H
ANL C, 1H
ORL C, 2H
CPL C

; answer
MOV P1.0, C

; clean up
CLR C
