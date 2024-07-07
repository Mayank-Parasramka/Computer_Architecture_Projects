.section .data
L1: .word 1000000, 0x00, 0x20

.section .text
.global main
main:
    la x3, L1
    li x4, 0x10012004  // Storing the base address

    lw x6, 4(x3)  // x6 stores the off value
    lw x7, 8(x3)  // x7 stores the on value
    lw x15, 0(x3)  // Stores the delay value

    sw x6, 0(x4)
    sw x7, 4(x4)
    ON:
        addi x5, x0, 0
        sw x7, 8(x4)
        TIME_ON:
            beq x5, x15, OFF
            addi x5 ,x5, 1
            jal x0, TIME_ON

    OFF:
        addi x5, x0, 0
        sw x6, 8(x4)
        TIME_OFF:
            beq x5, x15, ON
            addi x5 ,x5, 1
            jal x0, TIME_OFF

Lwhile1: j Lwhile1
