 .syntax unified
    .cpu cortex-m4
    .fpu softvfp
    .thumb

  .global HardFault_Handler
  .global HardFault_Handler_C
  .type HardFault_Handler, %function

  HardFault_Handler:
      tst     LR, #4
      ite     eq
      mrseq   R0, MSP     /* stacking was using MSP */
      mrsne   R0, PSP     /* stacking was using PSP */
      mov     R1, LR      /* second parameter */
      ldr     R2,=HardFault_Handler_C
      bx      R2
