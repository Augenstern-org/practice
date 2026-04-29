.data  
        list:   .word   n1
        n2:     .word   8,  n3
        n4:     .word   12, 0
        n1:     .word   6,  n2
        n3:     .word   5,  n4
        x:      .word   2

.text
        la      t1,list
        lw      t1,0(t1)    # t1 指向 n1 地址
        lw      t1,4(t1)    # t1 指向 n2 地址
        lw      s1,x
        addi    t0,zero,0
LOOP:
        addi    t0,t0,1
        lw      t1,4(t1)    # t1 替换为下一个节点的地址
                            # 此时 t1 已经是 n2 了
        beq     t0,s1,DONE
        jal     zero,LOOP
DONE:
        addi    a7,zero,1
        lw      a0,0(t1)
        ecall

