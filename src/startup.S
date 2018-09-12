  .align 6
  .globl reset_handler
  .globl main
  .globl tohost
  .globl fromhost
  .globl read_mcycle
  .globl enable_PCER
  .globl enable_MMU
  .globl __STACKS_END__
  .globl __BSS_START__
  .globl __BSS_END__

  .section .text

//_start:
//  j reset_handler

reset_handler:
1:
  la sp, __STACKS_END__
  jal clear_grps

  la a4, __DATA_RAM_START__
  la a5, __DATA_ROM_START__
  la a6, __DATA_SIZE__
  beq a6, x0, data_init_exit
  #add a6, a6, a5
  li a2, 0
data_init:
  lw a3, 0(a5)
  sw a3, 0(a4)
  addi a4, a4, 4
  addi a5, a5, 4
  addi a2, a2, 4
  bltu a2, a6, data_init
  #bleu a5, a6, data_init
data_init_exit:

clear_bss:
  la a4, __BSS_START__
  la a5, __BSS_END__
  li a6, 0
bss_init:
  sw a6, 0(a4)
  addi a4, a4, 4
  bleu a4, a5, bss_init
  
  jal main
  #li t3, 1
  #li t4, 0
  #sw t3,tohost,t4 
2:
  j 2b

clear_grps:
  li s0, 0
  li s1, 0
  li s2, 0
  li s3, 0
  li s4, 0
  li s5, 0
  li s6, 0
  li s7, 0
  li s8, 0
  li s9, 0
  li s10, 0
  li s11, 0
  li a0, 0
  li a1, 0
  li a2, 0
  li a3, 0
  li a4, 0
  li a5, 0
  li a6, 0
  li a7, 0
  jr ra

enable_PCER:
  csrsi mcounteren, 0x01
  jr ra

read_mcycle:
  csrr a0, mcycle
  jr ra

enable_MMU:
  li a0, 0xf0000000
  csrw satp, a0
  sfence.vma
  li a0, 0xf00
  csrw pmpcfg0, a0
  li a0, 0x40000
  csrw pmpaddr0, a0
  li a0, 0x41000
  csrw pmpaddr1, a0
  jr ra


  .section .vectors, "ax"
  .option norvc;

  .org 0x00
  .rept 20
  nop
  .endr

  //reset handler
  .org 0x80
  jal x0, reset_handler



 
