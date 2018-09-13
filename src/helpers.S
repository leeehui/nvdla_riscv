
.text
.globl __STACKS_END__
.globl __BSS_START__
.globl __BSS_END__

.globl runtime_clear
.type runtime_clear , @function
.globl clear_gprs
.type clear_gprs , @function
.globl clear_bss
.type clear_bss , @function
.globl irq_enable 
.type irq_enable , @function
.globl irq_disable 
.type irq_disable , @function


.globl ISR_NVDLA_ASM
.type ISR_NVDLA_ASM , @function
.globl ISR_WDT_ASM
.type ISR_WDT_ASM , @function
.globl ISR_TIMER_ASM
.type ISR_TIMER_ASM , @function


.globl lcc_state_info
.equ IEU_REG_BASE, 0x1A104000
.equ CLEAR_PENDING, 0x0c




clear_bss:
  la a4, __BSS_START__
  la a5, __BSS_END__
  li a6, 0
bss_init:
  sw a6, 0(a4) 
  addi a4, a4, 4
  bleu a4, a5, bss_init
  jr ra


clear_gprs:
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


runtime_clear:
  jal clear_bss
  la sp, __STACKS_END__
  jal clear_gprs
  //disable interrupt
  csrci mstatus, 0x08 //mie
  jal main

irq_enable:
  csrsi mstatus, 0x08 //mie
  ret

irq_disable:
  csrci mstatus, 0x08 //mie
  ret

   	
ISR_WDT_ASM:
  addi sp, sp, -16
  sw ra, 12(sp)
  sw a3, 8(sp) 
  sw a4, 4(sp) 
  sw a5, 0(sp) 
  jal ISR_WDT
  lw a5, 0(sp)
  lw a4, 4(sp)
  lw a3, 8(sp)
  lw ra, 12(sp)
  addi sp, sp, 16
  mret

ISR_TIMER_ASM:
  addi sp, sp, -12
  sw ra, 8(sp)
  sw a4, 4(sp) 
  sw a5, 0(sp) 
  jal ISR_TIMER
  lw a5, 0(sp)
  lw a4, 4(sp)
  lw ra, 8(sp)
  addi sp, sp, 12
  mret
  
ISR_NVDLA_ASM:
  addi sp, sp, -16
  sw ra, 12(sp)
  sw a3, 8(sp) 
  sw a4, 4(sp) 
  sw a5, 0(sp) 
  jal ISR_NVDLA
  lw a5, 0(sp)
  lw a4, 4(sp)
  lw a3, 8(sp)
  lw ra, 12(sp)
  addi sp, sp, 16
  mret
  


