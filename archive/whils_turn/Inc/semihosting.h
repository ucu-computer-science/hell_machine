/**
 ******************************************************************************
 * @file      semihosting.h
 * @author    Coocox
 * @version   V1.0
 * @date      09/10/2011
 * @brief     Semihosting Low Layer GetChar/SendChar API.
 *
 *******************************************************************************
 */
#ifndef __SEMIHOSTTING_IMPL
#define __SEMIHOSTTING_IMPL
/** @addtogroup SEMIHOSTING
  * @{
  */
  
/** @addtogroup semihost
  * @{
  */ 
/********************************************************************************************************//**
 * Semihosting functions prototype
************************************************************************************************************/
extern int SH_DoCommand(int n32In_R0, int n32In_R1, int *pn32Out_R0);
void SH_SendChar(int ch);
void SH_SendString(const char *str);
char SH_GetChar(void);


#endif
/**
  * @}
  */
/**
  * @}
  */

