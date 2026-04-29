# RISC-V(64-bits) GCC
p64:
        addi    sp,sp,-32    # 栈指针下移 32 字节（申请空间）
        sd      ra,24(sp)    # [64位特有] 将返回地址 ra (8字节) 存入栈
        sd      s0,16(sp)    # [64位特有] 将帧指针 s0 (8字节) 存入栈
        addi    s0,sp,32     # 设置新 s0 
        li      a5,42        # a5 = 42
        sw      a5,-28(s0)   # 将 42 存入局部变量（int 是 32 位，所以用 sw）
        addi    a5,s0,-28    # a5 = 刚才那个 42 的内存地址 (这是一个 64 位的指针)
        sd      a5,-24(s0)   # [64位特有] 将指针 a5 (8字节) 存入栈
        li      a5,0         # a5 = 0 (返回值)
        mv      a0,a5        # a0 = a5
        ld      ra,24(sp)    # 从栈恢复 8 字节的 ra
        ld      s0,16(sp)    # 从栈恢复 8 字节的 s0
        addi    sp,sp,32     # 释放栈空间
        jr      ra           # 返回

# RISC-V(32-bits) GCC
p32:
        addi    sp,sp,-32
        sw      ra,28(sp)    # [32位] 将 ra (4字节) 存入栈
        sw      s0,24(sp)    # [32位] 将 s0 (4字节) 存入栈
        addi    s0,sp,32
        li      a5,42
        sw      a5,-24(s0)   # 存 42 (4字节)
        addi    a5,s0,-24    # a5 = 42 的地址 (这是一个 32 位的指针)
        sw      a5,-20(s0)   # [32位] 将指针 a5 (4字节) 存入栈
        li      a5,0         # a5 = 0 (返回值)
        mv      a0,a5        # a0 = a5
        lw      ra,28(sp)    # 从栈恢复 4 字节的 ra
        lw      s0,24(sp)    # 从栈恢复 4 字节的 s0
        addi    sp,sp,32     # 释放栈空间
        jr      ra           # 返回

# 这是一个生成悬空指针的函数(32-bits GCC)
get_ptr:
        addi    sp,sp,-32    # 申请 32 字节的空间
        sw      ra,28(sp)    # ra 压栈
        sw      s0,24(sp)    # s0 压栈
        addi    s0,sp,32     # 令 s0 指向当前栈的顶部
        li      a5,42        # 将 42 赋值给 a5
        sw      a5,-20(s0)   # 将 a5 压栈
        addi    a0,s0,-20    # 计算这个局部变量的地址，存入返回值寄存器 a0  <-
        mv      a0,a5        # 将 a5 的值复制到 a0
        lw      ra,28(sp)    # 恢复 ra
        lw      s0,24(sp)    # 恢复 s0
        addi    sp,sp,32     # 释放栈空间
        jr      ra           # 返回

# Compute and print the smallest number
compute_and_print:

.data   # data at 0x10010000
        n:      .word   6
        x:      .word   5, 8, 12, 0, 4, 4

.text
        addi    sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        addi    s0,sp,32
        lw      s0,n
        la      s1,x
        addi    t1,zero,1
        lw      a0,0(s1)
LOOP:
        bge     t1,s0,DONE
        slli    t2,t1,2
        addi    t2,t2,s0
        lw      t3,0(t2)
        bge     t3,a0,NEXT
        addi    a0,zero,t3
NEXT:
        addi    t1,t1,1
        jal     zero,LOOP
DONE:
        addi    a7,zero,1
        ecall
        lw      ra,28(sp)
        lw      s0,24(sp)
        addi    sp,sp,32
        jal     zero,ra

# Count how many times y appear in x
count_y_in_x:
.data
        y:      .word   4
        n:      .word   6
        x:      .word   5, 8, 12, 0, 4, 4

.text
        addi    sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        lw      s0,y  
        lw      s1,n
        la      s2,x
        addi    t1,zero,1
        addi    a0,zero,0
LOOP:
        bge     t1,s0,DONE
        slli    t2,t1,2
        addi    t2,t2,s0
        lw      t3,0(t2)
        bne     t3,y,NEXT
        addi    a0,a0,1
NEXT:
        addi    t1,t1,1
        jal     zero,LOOP
DONE:
        addi    a7,zero,1
        ecall
        lw      ra,28(sp)
        lw      s0,24(sp)
        addi    sp,sp,32
        jal     zero,ra

void count(int res, int a, std::vector<int>& vec){
    for(auto n : vec) if(n == int) ++res;
}

# Print 1 if x == y 
is_x_eqaul_to_y:
.data
        n:      .word   6
        x:      .word   5,8,12,0,4,4
        y:      .word   5,8,12,0,4,4

.text
        addi    sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        la      s0,n
        lw      s0,0(s0)
        la      s1,x 
        la      s2,y 
        addi    t0,zero,0
        lw      t1,0(s1)
        lw      t2,0(s2)
        addi    a0,zero,1
LOOP:
        blt     s0,t0,DONE
        slli    t3,t0,2
        add     t1,s1,t3
        lw      t1,0(t1)
        add     t2,s2,t3
        lw      t2,0(t2)
        bne     t1,t2,SET 
        jal     zero,LOOP
SET:
        addi    a0,zero,0
        jal     zero,DONE
DONE:
        addi    a7,zero,1
        ecall
        lw      ra,28(sp)
        lw      s0,24(sp)
        addi    sp,sp,32
        jal     zero,ra

# Print x[i]
print_xi:
.data
        i:      .word   3
        n:      .word   6
        x:      .word   50,8,12,0,4,4

.text
        addi    sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        la      s0,i
        lw      s1,0(s0)
        addi    t0,s0,8
        slli    t1,s1,2
        add     t0,t0,t1
        lw      a0,0(t0)
        addi    a7,zero,1
        ecall
        lw      ra,28(sp)
        lw      s0,24(sp)
        addi    sp,sp,32
        jal     zero,ra

# Is the number odd
is_odd:
.data
        i:      .word   3

.text
        addi    sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        addi    s0,sp,32
        la      s1,i
        lw      t1,0(s1)    
        andi    a0,t1,1
        addi    a7,zero,1
        ecall
        lw      ra,28(sp)
        lw      s0,24(sp)
        addi    sp,sp,32
        jal     zero,ra

# Count the number of ones in the binary representation of x 
count_1:
.data
        x:      .word   379
.text  
        la      t0,i
        lw      s0,0(t0)
        addi    s1,zero,32
        addi    t0,zero,0
        addi    a0,zero,0
LOOP:
        bge     t0,s1,DONE
        srai    t1,s0,1
        andi    t1,t1,1
        add     a0,a0,t1
DONE:
        addi    a7,zero,1
        ecall
        addi    a7,zero,10
        ecall