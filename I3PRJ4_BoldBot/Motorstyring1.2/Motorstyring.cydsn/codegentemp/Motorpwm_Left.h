/*******************************************************************************
* File Name: Motorpwm_Left.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_Motorpwm_Left_H)
#define CY_PWM_Motorpwm_Left_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Motorpwm_Left_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Motorpwm_Left_Resolution                     (8u)
#define Motorpwm_Left_UsingFixedFunction             (0u)
#define Motorpwm_Left_DeadBandMode                   (0u)
#define Motorpwm_Left_KillModeMinTime                (0u)
#define Motorpwm_Left_KillMode                       (0u)
#define Motorpwm_Left_PWMMode                        (0u)
#define Motorpwm_Left_PWMModeIsCenterAligned         (0u)
#define Motorpwm_Left_DeadBandUsed                   (0u)
#define Motorpwm_Left_DeadBand2_4                    (0u)

#if !defined(Motorpwm_Left_PWMUDB_genblk8_stsreg__REMOVED)
    #define Motorpwm_Left_UseStatus                  (1u)
#else
    #define Motorpwm_Left_UseStatus                  (0u)
#endif /* !defined(Motorpwm_Left_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Motorpwm_Left_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Motorpwm_Left_UseControl                 (1u)
#else
    #define Motorpwm_Left_UseControl                 (0u)
#endif /* !defined(Motorpwm_Left_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Motorpwm_Left_UseOneCompareMode              (1u)
#define Motorpwm_Left_MinimumKillTime                (1u)
#define Motorpwm_Left_EnableMode                     (0u)

#define Motorpwm_Left_CompareMode1SW                 (0u)
#define Motorpwm_Left_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Motorpwm_Left__B_PWM__DISABLED 0
#define Motorpwm_Left__B_PWM__ASYNCHRONOUS 1
#define Motorpwm_Left__B_PWM__SINGLECYCLE 2
#define Motorpwm_Left__B_PWM__LATCHED 3
#define Motorpwm_Left__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Motorpwm_Left__B_PWM__DBMDISABLED 0
#define Motorpwm_Left__B_PWM__DBM_2_4_CLOCKS 1
#define Motorpwm_Left__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Motorpwm_Left__B_PWM__ONE_OUTPUT 0
#define Motorpwm_Left__B_PWM__TWO_OUTPUTS 1
#define Motorpwm_Left__B_PWM__DUAL_EDGE 2
#define Motorpwm_Left__B_PWM__CENTER_ALIGN 3
#define Motorpwm_Left__B_PWM__DITHER 5
#define Motorpwm_Left__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Motorpwm_Left__B_PWM__LESS_THAN 1
#define Motorpwm_Left__B_PWM__LESS_THAN_OR_EQUAL 2
#define Motorpwm_Left__B_PWM__GREATER_THAN 3
#define Motorpwm_Left__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Motorpwm_Left__B_PWM__EQUAL 0
#define Motorpwm_Left__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Motorpwm_Left_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!Motorpwm_Left_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!Motorpwm_Left_PWMModeIsCenterAligned) */
        #if (Motorpwm_Left_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Motorpwm_Left_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Motorpwm_Left_DeadBandMode == Motorpwm_Left__B_PWM__DBM_256_CLOCKS || \
            Motorpwm_Left_DeadBandMode == Motorpwm_Left__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Motorpwm_Left_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Motorpwm_Left_KillModeMinTime) */

        /* Backup control register */
        #if(Motorpwm_Left_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Motorpwm_Left_UseControl) */

    #endif /* (!Motorpwm_Left_UsingFixedFunction) */

}Motorpwm_Left_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Motorpwm_Left_Start(void) ;
void    Motorpwm_Left_Stop(void) ;

#if (Motorpwm_Left_UseStatus || Motorpwm_Left_UsingFixedFunction)
    void  Motorpwm_Left_SetInterruptMode(uint8 interruptMode) ;
    uint8 Motorpwm_Left_ReadStatusRegister(void) ;
#endif /* (Motorpwm_Left_UseStatus || Motorpwm_Left_UsingFixedFunction) */

#define Motorpwm_Left_GetInterruptSource() Motorpwm_Left_ReadStatusRegister()

#if (Motorpwm_Left_UseControl)
    uint8 Motorpwm_Left_ReadControlRegister(void) ;
    void  Motorpwm_Left_WriteControlRegister(uint8 control)
          ;
#endif /* (Motorpwm_Left_UseControl) */

#if (Motorpwm_Left_UseOneCompareMode)
   #if (Motorpwm_Left_CompareMode1SW)
       void    Motorpwm_Left_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Motorpwm_Left_CompareMode1SW) */
#else
    #if (Motorpwm_Left_CompareMode1SW)
        void    Motorpwm_Left_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Motorpwm_Left_CompareMode1SW) */
    #if (Motorpwm_Left_CompareMode2SW)
        void    Motorpwm_Left_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Motorpwm_Left_CompareMode2SW) */
#endif /* (Motorpwm_Left_UseOneCompareMode) */

#if (!Motorpwm_Left_UsingFixedFunction)
    uint8   Motorpwm_Left_ReadCounter(void) ;
    uint8 Motorpwm_Left_ReadCapture(void) ;

    #if (Motorpwm_Left_UseStatus)
            void Motorpwm_Left_ClearFIFO(void) ;
    #endif /* (Motorpwm_Left_UseStatus) */

    void    Motorpwm_Left_WriteCounter(uint8 counter)
            ;
#endif /* (!Motorpwm_Left_UsingFixedFunction) */

void    Motorpwm_Left_WritePeriod(uint8 period)
        ;
uint8 Motorpwm_Left_ReadPeriod(void) ;

#if (Motorpwm_Left_UseOneCompareMode)
    void    Motorpwm_Left_WriteCompare(uint8 compare)
            ;
    uint8 Motorpwm_Left_ReadCompare(void) ;
#else
    void    Motorpwm_Left_WriteCompare1(uint8 compare)
            ;
    uint8 Motorpwm_Left_ReadCompare1(void) ;
    void    Motorpwm_Left_WriteCompare2(uint8 compare)
            ;
    uint8 Motorpwm_Left_ReadCompare2(void) ;
#endif /* (Motorpwm_Left_UseOneCompareMode) */


#if (Motorpwm_Left_DeadBandUsed)
    void    Motorpwm_Left_WriteDeadTime(uint8 deadtime) ;
    uint8   Motorpwm_Left_ReadDeadTime(void) ;
#endif /* (Motorpwm_Left_DeadBandUsed) */

#if ( Motorpwm_Left_KillModeMinTime)
    void Motorpwm_Left_WriteKillTime(uint8 killtime) ;
    uint8 Motorpwm_Left_ReadKillTime(void) ;
#endif /* ( Motorpwm_Left_KillModeMinTime) */

void Motorpwm_Left_Init(void) ;
void Motorpwm_Left_Enable(void) ;
void Motorpwm_Left_Sleep(void) ;
void Motorpwm_Left_Wakeup(void) ;
void Motorpwm_Left_SaveConfig(void) ;
void Motorpwm_Left_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Motorpwm_Left_INIT_PERIOD_VALUE          (255u)
#define Motorpwm_Left_INIT_COMPARE_VALUE1        (0u)
#define Motorpwm_Left_INIT_COMPARE_VALUE2        (63u)
#define Motorpwm_Left_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Motorpwm_Left_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Motorpwm_Left_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Motorpwm_Left_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Motorpwm_Left_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Motorpwm_Left_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Motorpwm_Left_CTRL_CMPMODE2_SHIFT)
#define Motorpwm_Left_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Motorpwm_Left_CTRL_CMPMODE1_SHIFT)
#define Motorpwm_Left_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Motorpwm_Left_UsingFixedFunction)
   #define Motorpwm_Left_PERIOD_LSB              (*(reg16 *) Motorpwm_Left_PWMHW__PER0)
   #define Motorpwm_Left_PERIOD_LSB_PTR          ( (reg16 *) Motorpwm_Left_PWMHW__PER0)
   #define Motorpwm_Left_COMPARE1_LSB            (*(reg16 *) Motorpwm_Left_PWMHW__CNT_CMP0)
   #define Motorpwm_Left_COMPARE1_LSB_PTR        ( (reg16 *) Motorpwm_Left_PWMHW__CNT_CMP0)
   #define Motorpwm_Left_COMPARE2_LSB            (0x00u)
   #define Motorpwm_Left_COMPARE2_LSB_PTR        (0x00u)
   #define Motorpwm_Left_COUNTER_LSB             (*(reg16 *) Motorpwm_Left_PWMHW__CNT_CMP0)
   #define Motorpwm_Left_COUNTER_LSB_PTR         ( (reg16 *) Motorpwm_Left_PWMHW__CNT_CMP0)
   #define Motorpwm_Left_CAPTURE_LSB             (*(reg16 *) Motorpwm_Left_PWMHW__CAP0)
   #define Motorpwm_Left_CAPTURE_LSB_PTR         ( (reg16 *) Motorpwm_Left_PWMHW__CAP0)
   #define Motorpwm_Left_RT1                     (*(reg8 *)  Motorpwm_Left_PWMHW__RT1)
   #define Motorpwm_Left_RT1_PTR                 ( (reg8 *)  Motorpwm_Left_PWMHW__RT1)

#else
   #if (Motorpwm_Left_Resolution == 8u) /* 8bit - PWM */

       #if(Motorpwm_Left_PWMModeIsCenterAligned)
           #define Motorpwm_Left_PERIOD_LSB      (*(reg8 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define Motorpwm_Left_PERIOD_LSB_PTR  ((reg8 *)   Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define Motorpwm_Left_PERIOD_LSB      (*(reg8 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define Motorpwm_Left_PERIOD_LSB_PTR  ((reg8 *)   Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (Motorpwm_Left_PWMModeIsCenterAligned) */

       #define Motorpwm_Left_COMPARE1_LSB        (*(reg8 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define Motorpwm_Left_COMPARE1_LSB_PTR    ((reg8 *)   Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define Motorpwm_Left_COMPARE2_LSB        (*(reg8 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define Motorpwm_Left_COMPARE2_LSB_PTR    ((reg8 *)   Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define Motorpwm_Left_COUNTERCAP_LSB      (*(reg8 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define Motorpwm_Left_COUNTERCAP_LSB_PTR  ((reg8 *)   Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define Motorpwm_Left_COUNTER_LSB         (*(reg8 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define Motorpwm_Left_COUNTER_LSB_PTR     ((reg8 *)   Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define Motorpwm_Left_CAPTURE_LSB         (*(reg8 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define Motorpwm_Left_CAPTURE_LSB_PTR     ((reg8 *)   Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Motorpwm_Left_PWMModeIsCenterAligned)
               #define Motorpwm_Left_PERIOD_LSB      (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define Motorpwm_Left_PERIOD_LSB_PTR  ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define Motorpwm_Left_PERIOD_LSB      (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define Motorpwm_Left_PERIOD_LSB_PTR  ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (Motorpwm_Left_PWMModeIsCenterAligned) */

            #define Motorpwm_Left_COMPARE1_LSB       (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define Motorpwm_Left_COMPARE1_LSB_PTR   ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define Motorpwm_Left_COMPARE2_LSB       (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define Motorpwm_Left_COMPARE2_LSB_PTR   ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define Motorpwm_Left_COUNTERCAP_LSB     (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define Motorpwm_Left_COUNTERCAP_LSB_PTR ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define Motorpwm_Left_COUNTER_LSB        (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define Motorpwm_Left_COUNTER_LSB_PTR    ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define Motorpwm_Left_CAPTURE_LSB        (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define Motorpwm_Left_CAPTURE_LSB_PTR    ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(Motorpwm_Left_PWMModeIsCenterAligned)
               #define Motorpwm_Left_PERIOD_LSB      (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define Motorpwm_Left_PERIOD_LSB_PTR  ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Motorpwm_Left_PERIOD_LSB      (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define Motorpwm_Left_PERIOD_LSB_PTR  ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Motorpwm_Left_PWMModeIsCenterAligned) */

            #define Motorpwm_Left_COMPARE1_LSB       (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define Motorpwm_Left_COMPARE1_LSB_PTR   ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define Motorpwm_Left_COMPARE2_LSB       (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define Motorpwm_Left_COMPARE2_LSB_PTR   ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define Motorpwm_Left_COUNTERCAP_LSB     (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define Motorpwm_Left_COUNTERCAP_LSB_PTR ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define Motorpwm_Left_COUNTER_LSB        (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define Motorpwm_Left_COUNTER_LSB_PTR    ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define Motorpwm_Left_CAPTURE_LSB        (*(reg16 *) Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define Motorpwm_Left_CAPTURE_LSB_PTR    ((reg16 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Motorpwm_Left_AUX_CONTROLDP1          (*(reg8 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define Motorpwm_Left_AUX_CONTROLDP1_PTR      ((reg8 *)   Motorpwm_Left_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Motorpwm_Left_Resolution == 8) */

   #define Motorpwm_Left_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define Motorpwm_Left_AUX_CONTROLDP0          (*(reg8 *)  Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define Motorpwm_Left_AUX_CONTROLDP0_PTR      ((reg8 *)   Motorpwm_Left_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Motorpwm_Left_UsingFixedFunction) */

#if(Motorpwm_Left_KillModeMinTime )
    #define Motorpwm_Left_KILLMODEMINTIME        (*(reg8 *)  Motorpwm_Left_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Motorpwm_Left_KILLMODEMINTIME_PTR    ((reg8 *)   Motorpwm_Left_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Motorpwm_Left_KillModeMinTime ) */

#if(Motorpwm_Left_DeadBandMode == Motorpwm_Left__B_PWM__DBM_256_CLOCKS)
    #define Motorpwm_Left_DEADBAND_COUNT         (*(reg8 *)  Motorpwm_Left_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Motorpwm_Left_DEADBAND_COUNT_PTR     ((reg8 *)   Motorpwm_Left_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Motorpwm_Left_DEADBAND_LSB_PTR       ((reg8 *)   Motorpwm_Left_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Motorpwm_Left_DEADBAND_LSB           (*(reg8 *)  Motorpwm_Left_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Motorpwm_Left_DeadBandMode == Motorpwm_Left__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Motorpwm_Left_UsingFixedFunction)
        #define Motorpwm_Left_DEADBAND_COUNT         (*(reg8 *)  Motorpwm_Left_PWMHW__CFG0)
        #define Motorpwm_Left_DEADBAND_COUNT_PTR     ((reg8 *)   Motorpwm_Left_PWMHW__CFG0)
        #define Motorpwm_Left_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Motorpwm_Left_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Motorpwm_Left_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Motorpwm_Left_DEADBAND_COUNT         (*(reg8 *)  Motorpwm_Left_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Motorpwm_Left_DEADBAND_COUNT_PTR     ((reg8 *)   Motorpwm_Left_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Motorpwm_Left_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Motorpwm_Left_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Motorpwm_Left_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Motorpwm_Left_UsingFixedFunction) */
#endif /* (Motorpwm_Left_DeadBandMode == Motorpwm_Left__B_PWM__DBM_256_CLOCKS) */



#if (Motorpwm_Left_UsingFixedFunction)
    #define Motorpwm_Left_STATUS                 (*(reg8 *) Motorpwm_Left_PWMHW__SR0)
    #define Motorpwm_Left_STATUS_PTR             ((reg8 *) Motorpwm_Left_PWMHW__SR0)
    #define Motorpwm_Left_STATUS_MASK            (*(reg8 *) Motorpwm_Left_PWMHW__SR0)
    #define Motorpwm_Left_STATUS_MASK_PTR        ((reg8 *) Motorpwm_Left_PWMHW__SR0)
    #define Motorpwm_Left_CONTROL                (*(reg8 *) Motorpwm_Left_PWMHW__CFG0)
    #define Motorpwm_Left_CONTROL_PTR            ((reg8 *) Motorpwm_Left_PWMHW__CFG0)
    #define Motorpwm_Left_CONTROL2               (*(reg8 *) Motorpwm_Left_PWMHW__CFG1)
    #define Motorpwm_Left_CONTROL3               (*(reg8 *) Motorpwm_Left_PWMHW__CFG2)
    #define Motorpwm_Left_GLOBAL_ENABLE          (*(reg8 *) Motorpwm_Left_PWMHW__PM_ACT_CFG)
    #define Motorpwm_Left_GLOBAL_ENABLE_PTR      ( (reg8 *) Motorpwm_Left_PWMHW__PM_ACT_CFG)
    #define Motorpwm_Left_GLOBAL_STBY_ENABLE     (*(reg8 *) Motorpwm_Left_PWMHW__PM_STBY_CFG)
    #define Motorpwm_Left_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Motorpwm_Left_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Motorpwm_Left_BLOCK_EN_MASK          (Motorpwm_Left_PWMHW__PM_ACT_MSK)
    #define Motorpwm_Left_BLOCK_STBY_EN_MASK     (Motorpwm_Left_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Motorpwm_Left_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Motorpwm_Left_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Motorpwm_Left_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Motorpwm_Left_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Motorpwm_Left_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Motorpwm_Left_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Motorpwm_Left_CTRL_ENABLE            (uint8)((uint8)0x01u << Motorpwm_Left_CTRL_ENABLE_SHIFT)
    #define Motorpwm_Left_CTRL_RESET             (uint8)((uint8)0x01u << Motorpwm_Left_CTRL_RESET_SHIFT)
    #define Motorpwm_Left_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Motorpwm_Left_CTRL_CMPMODE2_SHIFT)
    #define Motorpwm_Left_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Motorpwm_Left_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Motorpwm_Left_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Motorpwm_Left_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Motorpwm_Left_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Motorpwm_Left_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Motorpwm_Left_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Motorpwm_Left_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Motorpwm_Left_STATUS_TC_INT_EN_MASK_SHIFT            (Motorpwm_Left_STATUS_TC_SHIFT - 4u)
    #define Motorpwm_Left_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Motorpwm_Left_STATUS_CMP1_INT_EN_MASK_SHIFT          (Motorpwm_Left_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Motorpwm_Left_STATUS_TC              (uint8)((uint8)0x01u << Motorpwm_Left_STATUS_TC_SHIFT)
    #define Motorpwm_Left_STATUS_CMP1            (uint8)((uint8)0x01u << Motorpwm_Left_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Motorpwm_Left_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Motorpwm_Left_STATUS_TC >> 4u)
    #define Motorpwm_Left_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Motorpwm_Left_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Motorpwm_Left_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Motorpwm_Left_RT1_MASK              (uint8)((uint8)0x03u << Motorpwm_Left_RT1_SHIFT)
    #define Motorpwm_Left_SYNC                  (uint8)((uint8)0x03u << Motorpwm_Left_RT1_SHIFT)
    #define Motorpwm_Left_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Motorpwm_Left_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Motorpwm_Left_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Motorpwm_Left_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Motorpwm_Left_SYNCDSI_SHIFT)


#else
    #define Motorpwm_Left_STATUS                (*(reg8 *)   Motorpwm_Left_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Motorpwm_Left_STATUS_PTR            ((reg8 *)    Motorpwm_Left_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Motorpwm_Left_STATUS_MASK           (*(reg8 *)   Motorpwm_Left_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Motorpwm_Left_STATUS_MASK_PTR       ((reg8 *)    Motorpwm_Left_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Motorpwm_Left_STATUS_AUX_CTRL       (*(reg8 *)   Motorpwm_Left_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Motorpwm_Left_CONTROL               (*(reg8 *)   Motorpwm_Left_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Motorpwm_Left_CONTROL_PTR           ((reg8 *)    Motorpwm_Left_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Motorpwm_Left_CTRL_ENABLE_SHIFT      (0x07u)
    #define Motorpwm_Left_CTRL_RESET_SHIFT       (0x06u)
    #define Motorpwm_Left_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Motorpwm_Left_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Motorpwm_Left_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Motorpwm_Left_CTRL_ENABLE            (uint8)((uint8)0x01u << Motorpwm_Left_CTRL_ENABLE_SHIFT)
    #define Motorpwm_Left_CTRL_RESET             (uint8)((uint8)0x01u << Motorpwm_Left_CTRL_RESET_SHIFT)
    #define Motorpwm_Left_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Motorpwm_Left_CTRL_CMPMODE2_SHIFT)
    #define Motorpwm_Left_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Motorpwm_Left_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Motorpwm_Left_STATUS_KILL_SHIFT          (0x05u)
    #define Motorpwm_Left_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Motorpwm_Left_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Motorpwm_Left_STATUS_TC_SHIFT            (0x02u)
    #define Motorpwm_Left_STATUS_CMP2_SHIFT          (0x01u)
    #define Motorpwm_Left_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Motorpwm_Left_STATUS_KILL_INT_EN_MASK_SHIFT          (Motorpwm_Left_STATUS_KILL_SHIFT)
    #define Motorpwm_Left_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Motorpwm_Left_STATUS_FIFONEMPTY_SHIFT)
    #define Motorpwm_Left_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Motorpwm_Left_STATUS_FIFOFULL_SHIFT)
    #define Motorpwm_Left_STATUS_TC_INT_EN_MASK_SHIFT            (Motorpwm_Left_STATUS_TC_SHIFT)
    #define Motorpwm_Left_STATUS_CMP2_INT_EN_MASK_SHIFT          (Motorpwm_Left_STATUS_CMP2_SHIFT)
    #define Motorpwm_Left_STATUS_CMP1_INT_EN_MASK_SHIFT          (Motorpwm_Left_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Motorpwm_Left_STATUS_KILL            (uint8)((uint8)0x00u << Motorpwm_Left_STATUS_KILL_SHIFT )
    #define Motorpwm_Left_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Motorpwm_Left_STATUS_FIFOFULL_SHIFT)
    #define Motorpwm_Left_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Motorpwm_Left_STATUS_FIFONEMPTY_SHIFT)
    #define Motorpwm_Left_STATUS_TC              (uint8)((uint8)0x01u << Motorpwm_Left_STATUS_TC_SHIFT)
    #define Motorpwm_Left_STATUS_CMP2            (uint8)((uint8)0x01u << Motorpwm_Left_STATUS_CMP2_SHIFT)
    #define Motorpwm_Left_STATUS_CMP1            (uint8)((uint8)0x01u << Motorpwm_Left_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Motorpwm_Left_STATUS_KILL_INT_EN_MASK            (Motorpwm_Left_STATUS_KILL)
    #define Motorpwm_Left_STATUS_FIFOFULL_INT_EN_MASK        (Motorpwm_Left_STATUS_FIFOFULL)
    #define Motorpwm_Left_STATUS_FIFONEMPTY_INT_EN_MASK      (Motorpwm_Left_STATUS_FIFONEMPTY)
    #define Motorpwm_Left_STATUS_TC_INT_EN_MASK              (Motorpwm_Left_STATUS_TC)
    #define Motorpwm_Left_STATUS_CMP2_INT_EN_MASK            (Motorpwm_Left_STATUS_CMP2)
    #define Motorpwm_Left_STATUS_CMP1_INT_EN_MASK            (Motorpwm_Left_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Motorpwm_Left_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Motorpwm_Left_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Motorpwm_Left_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Motorpwm_Left_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Motorpwm_Left_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Motorpwm_Left_UsingFixedFunction */

#endif  /* CY_PWM_Motorpwm_Left_H */


/* [] END OF FILE */
