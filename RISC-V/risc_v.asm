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