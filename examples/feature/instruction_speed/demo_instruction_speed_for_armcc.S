
                PRESERVE8
                THUMB

                AREA    |.text|, CODE, READONLY
                
excute_subto_zero   PROC
                    EXPORT  excute_subto_zero
                
                    CMP     R0, #0
                    BEQ     %F2
1
                    ADD     R1, R1, #1
                    ADD     R2, R2, #1
                    ADD     R3, R3, #1
                    ADD     R1, R1, #1
                    ADD     R2, R2, #1
                    ADD     R3, R3, #1
                    SUBS    R0, R0, #1
                    BNE     %B1
2
                    BX      LR
                    ENDP
                
                    END

