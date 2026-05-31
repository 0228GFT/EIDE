#ifndef __STC89_DEF_H__
#define __STC89_DEF_H__

/////////////////////////////////////////////////

#include "stc89c5xrc.h"
#include "def.h"

/////////////////////////////////////////////////

#define EnableGlobalInt()               (EA = 1)
#define DisableGlobalInt()              (EA = 0)

#define INT0_EnableInt()                (EX0 = 1)
#define INT0_DisableInt()               (EX0 = 0)

#define INT1_EnableInt()                (EX1 = 1)
#define INT1_DisableInt()               (EX1 = 0)

#define INT2_EnableInt()                (EX2 = 1)
#define INT2_DisableInt()               (EX2 = 0)

#define INT3_EnableInt()                (EX3 = 1)
#define INT3_DisableInt()               (EX3 = 0)

#define TIMER0_EnableInt()              (ET0 = 1)
#define TIMER0_DisableInt()             (ET0 = 0)

#define TIMER1_EnableInt()              (ET1 = 1)
#define TIMER1_DisableInt()             (ET1 = 0)

#define TIMER2_EnableInt()              (ET2 = 1)
#define TIMER2_DisableInt()             (ET2 = 0)

#define UART1_EnableInt()               (ES = 1)
#define UART1_DisableInt()              (ES = 0)

#define INT0_LowLevelInt()              (IT0 = 0)
#define INT0_FallingInt()               (IT0 = 1)

#define INT1_LowLevelInt()              (IT1 = 0)
#define INT1_FallingInt()               (IT1 = 1)

#define INT2_LowLevelInt()              (IT2 = 0)
#define INT2_FallingInt()               (IT2 = 1)

#define INT3_LowLevelInt()              (IT3 = 0)
#define INT3_FallingInt()               (IT3 = 1)

#define INT0_CheckFlag()                (IE0)
#define INT0_ClearFlag()                (IE0 = 0)

#define INT1_CheckFlag()                (IE1)
#define INT1_ClearFlag()                (IE1 = 0)

#define INT2_CheckFlag()                (IE2)
#define INT2_ClearFlag()                (IE2 = 0)

#define INT3_CheckFlag()                (IE3)
#define INT3_ClearFlag()                (IE3 = 0)

#define TIMER0_CheckFlag()              (TF0)
#define TIMER0_ClearFlag()              (TF0 = 0)

#define TIMER1_CheckFlag()              (TF1)
#define TIMER1_ClearFlag()              (TF1 = 0)

#define TIMER2_CheckFlag()              (TF2)
#define TIMER2_ClearFlag()              (TF2 = 0)

#define EXF2_CheckFlag()                (EXF2)
#define EXF2_ClearFlag()                (EXF2 = 0)

#define UART1_CheckRxFlag()             (RI)
#define UART1_CheckTxFlag()             (TI)
#define UART1_ClearRxFlag()             (RI = 0)
#define UART1_ClearTxFlag()             (TI = 0)
#define UART1_SetRxFlag()               (RI = 1)
#define UART1_SetTxFlag()               (TI = 1)

#define IPH_PX0H_MSK                    BIT0
#define INT0_SetIntPriority(n)          PX0 = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PX0H_MSK, ((((n) >> 1) & 1) << 0))

#define IPH_PX1H_MSK                    BIT2
#define INT1_SetIntPriority(n)          PX1 = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PX1H_MSK, ((((n) >> 1) & 1) << 2))

#define IPH_PX2H_MSK                    BIT6
#define INT2_SetIntPriority(n)          PX2 = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PX2H_MSK, ((((n) >> 1) & 1) << 6))

#define IPH_PX3H_MSK                    BIT7
#define INT3_SetIntPriority(n)          PX3 = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PX3H_MSK, ((((n) >> 1) & 1) << 7))

#define IPH_PT0H_MSK                    BIT1
#define TIMER0_SetIntPriority(n)        PT0 = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PT0H_MSK, ((((n) >> 1) & 1) << 1))

#define IPH_PT1H_MSK                    BIT3
#define TIMER1_SetIntPriority(n)        PT1 = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PT1H_MSK, ((((n) >> 1) & 1) << 3))

#define IPH_PT2H_MSK                    BIT5
#define TIMER2_SetIntPriority(n)        PT2 = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PT2H_MSK, ((((n) >> 1) & 1) << 5))

#define IPH_PSH_MSK                     BIT4
#define UART1_SetIntPriority(n)         PS = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PSH_MSK, ((((n) >> 1) & 1) << 4))

/////////////////////////////////////////////////

#define WDTCONTR_EN_MSK                 BIT5
#define WDTCONTR_CLR_MSK                BIT4
#define WDTCONTR_IDL_MSK                BIT3
#define WDTCONTR_PS_MSK                 (BIT2 | BIT1 | BIT0)

#define WDT_Enable()                    SET_REG_BIT(WDT_CONTR, WDTCONTR_EN_MSK)
#define WDT_Clear()                     SET_REG_BIT(WDT_CONTR, WDTCONTR_CLR_MSK)
#define WDT_IdlePause()                 CLR_REG_BIT(WDT_CONTR, WDTCONTR_IDL_MSK)
#define WDT_IdleContinue()              SET_REG_BIT(WDT_CONTR, WDTCONTR_IDL_MSK)

#define WDT_SetPrescale(n)              MODIFY_REG(WDT_CONTR, WDTCONTR_PS_MSK, ((n) << 0))
#define WDT_SetPrescale2()              WDT_SetPrescale(0)
#define WDT_SetPrescale4()              WDT_SetPrescale(1)
#define WDT_SetPrescale8()              WDT_SetPrescale(2)
#define WDT_SetPrescale16()             WDT_SetPrescale(3)
#define WDT_SetPrescale32()             WDT_SetPrescale(4)
#define WDT_SetPrescale64()             WDT_SetPrescale(5)
#define WDT_SetPrescale128()            WDT_SetPrescale(6)
#define WDT_SetPrescale256()            WDT_SetPrescale(7)

/////////////////////////////////////////////////

#define TIMER0_Run()                    (TR0 = 1)
#define TIMER0_Stop()                   (TR0 = 0)

#define TIMER0_SetReload8(n)            (TH0 = LOBYTE(n), TL0 = LOBYTE(n))
#define TIMER0_SetReload16(n)           (TH0 = HIBYTE(n), TL0 = LOBYTE(n))
#define TIMER0_SetReload13(n)           (TH0 = HIBYTE((n) * 8), TL0 = LOBYTE(n) & 0x1f)

#define TMOD_T0M_MSK                    (BIT1 | BIT0)
#define TIMER0_Mode0()                  MODIFY_REG(TMOD, TMOD_T0M_MSK, ((0) << 0))
#define TIMER0_Mode1()                  MODIFY_REG(TMOD, TMOD_T0M_MSK, ((1) << 0))
#define TIMER0_Mode2()                  MODIFY_REG(TMOD, TMOD_T0M_MSK, ((2) << 0))
#define TIMER0_Mode3()                  MODIFY_REG(TMOD, TMOD_T0M_MSK, ((3) << 0))

#define TMOD_T0CT_MSK                   BIT2
#define TIMER0_TimerMode()              CLR_REG_BIT(TMOD, TMOD_T0CT_MSK)
#define TIMER0_CounterMode()            SET_REG_BIT(TMOD, TMOD_T0CT_MSK)

#define TMOD_T0GATE_MSK                 BIT3
#define TIMER0_EnableGateINT0()         SET_REG_BIT(TMOD, TMOD_T0GATE_MSK)
#define TIMER0_DisableGateINT0()        CLR_REG_BIT(TMOD, TMOD_T0GATE_MSK)

////////////////////////

#define TIMER1_Run()                    (TR1 = 1)
#define TIMER1_Stop()                   (TR1 = 0)

#define TIMER1_SetReload8(n)            (TH1 = LOBYTE(n), TL1 = LOBYTE(n))
#define TIMER1_SetReload16(n)           (TH1 = HIBYTE(n), TL1 = LOBYTE(n))
#define TIMER1_SetReload13(n)           (TH1 = HIBYTE((n) * 8), TL1 = LOBYTE(n) & 0x1f)

#define TMOD_T1M_MSK                    (BIT5 | BIT4)
#define TIMER1_Mode0()                  MODIFY_REG(TMOD, TMOD_T1M_MSK, ((0) << 4))
#define TIMER1_Mode1()                  MODIFY_REG(TMOD, TMOD_T1M_MSK, ((1) << 4))
#define TIMER1_Mode2()                  MODIFY_REG(TMOD, TMOD_T1M_MSK, ((2) << 4))

#define TMOD_T1CT_MSK                   BIT6
#define TIMER1_TimerMode()              CLR_REG_BIT(TMOD, TMOD_T1CT_MSK)
#define TIMER1_CounterMode()            SET_REG_BIT(TMOD, TMOD_T1CT_MSK)

#define TMOD_T1GATE_MSK                 BIT7
#define TIMER1_EnableGateINT1()         SET_REG_BIT(TMOD, TMOD_T1GATE_MSK)
#define TIMER1_DisableGateINT1()        CLR_REG_BIT(TMOD, TMOD_T1GATE_MSK)

////////////////////////

#define TIMER2_Run()                    (TR2 = 1)
#define TIMER2_Stop()                   (TR2 = 0)

#define TIMER2_SetReload16(n)           (RCAP2H = TH2 = HIBYTE(n), RCAP2L = TL2 = LOBYTE(n))
#define TIMER2_ReadCapture()            MAKEWORD(RCAP2L, RCAP2H)

#define TIMER2_TimerMode()              (C_T2 = 0, CP_RL2 = 0)
#define TIMER2_CounterMode()            (C_T2 = 1, CP_RL2 = 0)
#define TIMER2_CaptureMode()            (CP_RL2 = 1)

#define TIMER2_EnableExternal()         (EXEN2 = 1)
#define TIMER2_DisableExternal()        (EXEN2 = 0)

#define T2MOD_T2OE_MSK                  BIT1
#define TIMER2_EnableCLKO()             SET_REG_BIT(T2MOD, T2MOD_T2OE_MSK)
#define TIMER2_DisableCLKO()            CLR_REG_BIT(T2MOD, T2MOD_T2OE_MSK)

#define T2MOD_DCEN_MSK                  BIT0
#define TIMER2_EnableDownCount()        SET_REG_BIT(T2MOD, T2MOD_DCEN_MSK)
#define TIMER2_DisableDownCount()       CLR_REG_BIT(T2MOD, T2MOD_DCEN_MSK)

/////////////////////////////////////////////////

#define SCON_SM_MSK                     (BIT7 | BIT6)
#define UART1_SetMode(n)                MODIFY_REG(SCON, SCON_SM_MSK, ((n) << 6))
#define UART1_Mode0()                   UART1_SetMode(0)
#define UART1_Mode1()                   UART1_SetMode(1)
#define UART1_Mode2()                   UART1_SetMode(2)
#define UART1_Mode3()                   UART1_SetMode(3)

#define UART1_EnableRx()                (REN = 1)
#define UART1_DisableRx()               (REN = 0)
#define UART1_SetTB8(b)                 (TB8 = (b))
#define UART1_ReadRB8()                 (RB8)

#define UART1_SendData(d)               (SBUF = (d))
#define UART1_ReadData()                (SBUF)

#define PCON_SMOD_MSK                   BIT7
#define UART1_BaudrateX2()              SET_REG_BIT(PCON, PCON_SMOD_MSK)

#define UART1_Timer1BRT()               (RCLK = 0, TCLK = 0)
#define UART1_Timer2BRT()               (RCLK = 1, TCLK = 1)

/////////////////////////////////////////////////

#define IAPCON_IAPEN_MSK                BIT7
#define IAP_Enable()                    SET_REG_BIT(ISP_CONTR, IAPCON_IAPEN_MSK)
#define IAP_Disable()                   CLR_REG_BIT(ISP_CONTR, IAPCON_IAPEN_MSK)

#define IAP_SetData(d)                  (ISP_DATA = (d))
#define IAP_ReadData()                  (ISP_DATA)

#define IAP_SetAddress(n)               ISP_ADDRL = BYTE0(n); \
                                        ISP_ADDRH = BYTE1(n)

#define IAP_Trigger()                   ISP_TRIG = 0x46; \
                                        ISP_TRIG = 0xb9; \
                                        _nop_();         \
                                        _nop_();         \
                                        _nop_();         \
                                        _nop_()

#define IAP_Idle()                      ISP_CMD = 0
#define IAP_TriggerRead()               ISP_CMD = 1; IAP_Trigger()
#define IAP_TriggerProgram()            ISP_CMD = 2; IAP_Trigger()
#define IAP_TriggerErase()              ISP_CMD = 3; IAP_Trigger()

#define IAPCON_WT_MSK                  (BIT2 | BIT1 | BIT0)
#define IAP_SetWaitTime(n)              MODIFY_REG(ISP_CONTR, IAPCON_WT_MSK, ((n) << 0))
#define IAP_SetTimeBase()               IAP_SetWaitTime((SYSCLK) <=  5000000UL ? 3 : \
                                                        (SYSCLK) <= 10000000UL ? 2 : \
                                                        (SYSCLK) <= 20000000UL ? 1 : 0)

/////////////////////////////////////////////////
//Interrupt Vector
/////////////////////////////////////////////////

#define     INT0_VECTOR             0       //0003H
#define     TMR0_VECTOR             1       //000BH
#define     INT1_VECTOR             2       //0013H
#define     TMR1_VECTOR             3       //001BH
#define     UART1_VECTOR            4       //0023H
#define     TMR2_VECTOR             5       //002BH
#define     INT2_VECTOR             6       //0033H
#define     INT3_VECTOR             7       //003BH

/////////////////////////////////////////////////

#define NOP1()  _nop_()
#define NOP2()  NOP1(),NOP1()
#define NOP3()  NOP2(),NOP1()
#define NOP4()  NOP3(),NOP1()
#define NOP5()  NOP4(),NOP1()
#define NOP6()  NOP5(),NOP1()
#define NOP7()  NOP6(),NOP1()
#define NOP8()  NOP7(),NOP1()
#define NOP9()  NOP8(),NOP1()
#define NOP10() NOP9(),NOP1()
#define NOP11() NOP10(),NOP1()
#define NOP12() NOP11(),NOP1()
#define NOP13() NOP12(),NOP1()
#define NOP14() NOP13(),NOP1()
#define NOP15() NOP14(),NOP1()
#define NOP16() NOP15(),NOP1()
#define NOP17() NOP16(),NOP1()
#define NOP18() NOP17(),NOP1()
#define NOP19() NOP18(),NOP1()
#define NOP20() NOP19(),NOP1()
#define NOP21() NOP20(),NOP1()
#define NOP22() NOP21(),NOP1()
#define NOP23() NOP22(),NOP1()
#define NOP24() NOP23(),NOP1()
#define NOP25() NOP24(),NOP1()
#define NOP26() NOP25(),NOP1()
#define NOP27() NOP26(),NOP1()
#define NOP28() NOP27(),NOP1()
#define NOP29() NOP28(),NOP1()
#define NOP30() NOP29(),NOP1()
#define NOP31() NOP30(),NOP1()
#define NOP32() NOP31(),NOP1()
#define NOP33() NOP32(),NOP1()
#define NOP34() NOP33(),NOP1()
#define NOP35() NOP34(),NOP1()
#define NOP36() NOP35(),NOP1()
#define NOP37() NOP36(),NOP1()
#define NOP38() NOP37(),NOP1()
#define NOP39() NOP38(),NOP1()
#define NOP40() NOP39(),NOP1()
#define NOP(N)  NOP##N()

/////////////////////////////////////////////////


#endif

