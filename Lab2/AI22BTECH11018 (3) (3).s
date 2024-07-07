.data
.dword 0b0010111
.word 51,19,3,103,115,35,99,111,55,23
.text
 lui x1, 0x10000
    li x4, 0x00000000FCD186a3

 
    li x5, 0x7F
    and x5, x4, x5
    and x5, x4, x5
    lw x11, 0(x1)
    lw x12, 4(x1)  #I
    lw x13, 8(x1) #B
    lw x14, 12(x1)  #S
    lw x15, 16(x1)  #JU
    lw x16, 20(x1)  #U
    lw x17, 24(x1)  #I
    lw x18, 28(x1)  #I
    lw x19, 32(x1)  #I
    lw x20, 36(x1)  #U
    
    beq x5, x11, L2
    beq x5, x12, L3
    beq x5, x17, L3
    beq x5, x18, L3
    beq x5, x19, L3
    beq x5, x20, L7
    beq x5, x13, L4
    beq x5, x14, L5
    beq x5, x15, L6
    beq x5, x16, L7
    beq x0, x0, exit

L2:
    addi x10, x0, 1
    beq x21, x21, exit

L3:
    addi x10, x0, 2
    beq x21, x21, exit

L4:
    addi x10, x0, 3
    beq x21, x21, exit

L5:
    addi x10, x0, 4
    beq x21, x21, exit

L6:
    addi x10, x0, 5
    beq x21, x21, exit

L7:
    addi x10, x0, 6
    beq x21, x21, exit

exit:
    add x0, x0, x0