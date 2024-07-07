.data
#The following line defines the 15 values present in the memory.
# We would use different values in our evaluation and
# hence you should try various combinations of these values in your testing.
.dword 1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 523, 524, 525, 533, 512
#(dword stands for doubleword)

.text
    #The following line initializes register x3 with 0x10000000 
    #so that you can use x3 for referencing various memory locations. 
    lui x3, 0x10000
    #code starts here    
    ld x11, 0(x3)
    add x10,x0,x0
    add x10,x10,x11
    ld x12,8(x3)
    add x10,x10,x12
    ld x13,16(x3)
    add x10,x10,x13
    ld x14,24(x3)
    add x10,x10,x14
    ld x15,32(x3)
    add x10,x10,x15
    ld x16,40(x3)
    add x10,x10,x16
    ld x17,48(x3)
    add x10,x10,x17
    ld x18,56(x3)
    add x10,x10,x18
    ld x19,64(x3)
    add x10,x10,x19
    ld x20,72(x3)
    add x10,x10,x20
    ld x21,80(x3)
    sub x10,x10,x21
    ld x22,88(x3)
    sub x10,x10,x22
    ld x23,96(x3)
    sub x10,x10,x23
    ld x24,104(x3)
    sub x10,x10,x24
    ld x25,112(x3)
    sub x10,x10,x25
    
    #The final result should be in register x10
    #end of the code