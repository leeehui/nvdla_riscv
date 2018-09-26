
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
	addi sp, sp, -128 #8*16
  	sd ra, 120(sp)
  	call SAVE_TEMP_REGS //just for test, in this case call is equivalent to jal as this is short jump
  	jal ISR_WDT
  	jal RESTORE_TEMP_REGS
  	ld ra, 120(sp)
  	addi sp, sp, 128 #8*16
  	mret

ISR_TIMER_ASM:
	addi sp, sp, -128 #8*16
  	sd ra, 120(sp)
  	jal SAVE_TEMP_REGS
  	jal ISR_TIMER
  	jal RESTORE_TEMP_REGS
  	ld ra, 120(sp)
  	addi sp, sp, 128 #8*16
  	mret
  
ISR_NVDLA_ASM:
	addi sp, sp, -128 #8*16
	sd ra, 120(sp)
	#according to calling convention, 
	#jal offset is equivalent to jal ra, offset,
	#so ra will be repalced when executing following instruction, 
	#this is why we save ra first. 
	jal SAVE_TEMP_REGS 

  	jal ISR_NVDLA

  	jal RESTORE_TEMP_REGS
  	ld ra, 120(sp)
  	addi sp, sp, 128 #8*16
  	mret
  
SAVE_TEMP_REGS:
	sd t0, 112(sp)
  	sd t1, 104(sp)
  	sd t2, 96(sp)
  	sd t3, 88(sp)
  	sd t4, 80(sp)
  	sd t5, 72(sp)
  	sd t6, 64(sp)
  	sd a0, 56(sp) 
  	sd a1, 48(sp) 
  	sd a2, 40(sp) 
  	sd a3, 32(sp) 
  	sd a4, 24(sp) 
  	sd a5, 16(sp) 
  	sd a6, 8(sp) 
  	sd a7, 0(sp) 
	mret

RESTORE_TEMP_REGS:
	ld a7, 0(sp) 
  	ld a6, 8(sp) 
  	ld a5, 16(sp) 
  	ld a4, 24(sp) 
  	ld a3, 32(sp) 
  	ld a2, 40(sp) 
  	ld a1, 48(sp) 
  	ld a0, 56(sp) 
  	ld t6, 64(sp)
  	ld t5, 72(sp)
  	ld t4, 80(sp)
  	ld t3, 88(sp)
  	ld t2, 96(sp)
  	ld t1, 104(sp)
  	ld t0, 112(sp)
  	mret

