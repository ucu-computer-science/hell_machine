#include <stdint.h>
#include "gpio.h"


typedef struct
{
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r12;
  uint32_t lr;
  uint32_t pc;
  uint32_t psr;
#if (__CORTEX_M >= 0x04U)  /* only for Cortex-M4 and above */
  uint32_t s[16];
  uint32_t fpscr;
#endif
} exception_stack_frame_t;

//void HardFault_Handler_C(exception_stack_frame_t* frame, unsigned int lr_value)
//{
// if( *(uint16_t*)(frame->pc) == 0xBEAB)
// {
////  HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, 1);
//  frame->r0 = 0; // Simulate successful semihosting call
//          // -- not always correct!
//  frame->pc += 2; // Skip bkpt
//  SCB->HFSR = SCB_HFSR_DEBUGEVT_Msk; // Sticky bit -- reset by writing 1
//  return;
// }
// //! Hang for all other hard faults
// while (1){}
//}
