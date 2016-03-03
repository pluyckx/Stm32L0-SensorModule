.section .isr_vector
	.word __cstack               /* 0x000 */
	.word NVIC_ResetHandler      /* 0x004 */
	.word NVIC_NMIHandler        /* 0x008 */
	.word NVIC_HardFaultHandler  /* 0x00c */
	.word NVIC_MemManageHandler  /* 0x010 */
	.word NVIC_BusFaultHandler   /* 0x014 */
	.word NVIC_UsageFaultHandler /* 0x018 */
	.word 0x00000000             /* 0x01c */
	.word 0x00000000             /* 0x020 */
	.word 0x00000000             /* 0x024 */
	.word 0x00000000             /* 0x028 */
	.word NVIC_SVCHandler        /* 0x02c */
	.word NVIC_DebugMonHandler   /* 0x030 */
	.word 0x00000000             /* 0x034 */
	.word NVIC_PendSVHandler     /* 0x038 */
	.word NVIC_SysTickHandler    /* 0x03c */

	.word NVIC_WWDGHandler       /* 0x040 */
	.word NVIC_PVDHandler        /* 0x044 */
	.word NVIC_RtcHandler        /* 0x048 */
	.word NVIC_FLASHHandler      /* 0x04c */
	.word NVIC_RCCHandler        /* 0x050 */
	.word NVIC_EXTI0Handler      /* 0x054 */
	.word NVIC_EXTI1Handler      /* 0x058 */
	.word NVIC_EXTI2Handler      /* 0x05c */
	.word 0x0000000              /* 0x060 */
	.word NVIC_DMA1Chan1Handler  /* 0x064 */
	.word NVIC_DMA1Chan2_3Handler/* 0x068 */
	.word NVIC_DMA1Chan4_7Handler/* 0x06c */
	.word NVIC_ADCCompHandler    /* 0x070 */
	.word NVIC_LPTIM1Handler     /* 0x074 */
	.word NVIC_Usart4_5Handler   /* 0x078 */
	.word NVIC_Tim2Handler       /* 0x07c */
	.word NVIC_Tim3Handler       /* 0x080 */
	.word NVIC_Tim6Handler       /* 0x084 */
	.word NVIC_Tim7Handler       /* 0x088 */
	.word 0x00000000             /* 0x08c */
	.word NVIC_Tim21Handler      /* 0x090 */
	.word NVIC_I2C3Handler       /* 0x094 */
	.word NVIC_Tim22Handler      /* 0x098 */
	.word NVIC_I2C1Handler       /* 0x09c */
	.word NVIC_I2C2Handler       /* 0x0a0 */
	.word NVIC_Spi1Handler       /* 0x0a4 */
	.word NVIC_Spi2Handler       /* 0x0a8 */
	.word NVIC_Usart1Handler     /* 0x0ac */
	.word NVIC_Usart2Handler     /* 0x0b0 */
	.word NVIC_LpUart1_AesHandler/* 0x0b4 */

.section .text

_reset:
	ldr r0, =main
	bx r0
	b _hang

_hang:
	b .


_hang_nmi:
	b .

_hang_hard:
	b .


_hang_mem:
	b .

_hang_bus:
	b .

_hang_usage:
	b .

_hang_svc:
	b .

.weak NVIC_ResetHandler
.thumb_set NVIC_ResetHandler,_reset

.weak NVIC_NMIHandler
.thumb_set NVIC_NMIHandler,_hang_nmi

.weak NVIC_HardFaultHandler
.thumb_set NVIC_HardFaultHandler,_hang_hard

.weak NVIC_MemManageHandler
.thumb_set NVIC_MemManageHandler,_hang_mem

.weak NVIC_BusFaultHandler
.thumb_set NVIC_BusFaultHandler,_hang_bus

.weak NVIC_UsageFaultHandler
.thumb_set NVIC_UsageFaultHandler,_hang_usage

.weak NVIC_SVCHandler
.thumb_set NVIC_SVCHandler,_hang_svc

.weak NVIC_DebugMonHandler
.thumb_set NVIC_DebugMonHandler,_hang

.weak NVIC_PendSVHandler
.thumb_set NVIC_PendSVHandler,_hang

.weak NVIC_SysTickHandler
.thumb_set NVIC_SysTickHandler,_hang


.weak NVIC_WWDGHandler
.thumb_set NVIC_WWDGHandler,_hang
.weak NVIC_PVDHandler
.thumb_set NVIC_PVDHandler,_hang
.weak NVIC_RtcHandler
.thumb_set NVIC_RtcHandler,_hang
.weak NVIC_FLASHHandler
.thumb_set NVIC_FLASHHandler,_hang
.weak NVIC_RCCHandler
.thumb_set NVIC_RCCHandler,_hang
.weak NVIC_EXTI0Handler
.thumb_set NVIC_EXTI0Handler,_hang
.weak NVIC_EXTI1Handler
.thumb_set NVIC_EXTI1Handler,_hang
.weak NVIC_EXTI2Handler
.thumb_set NVIC_EXTI2Handler,_hang
.weak NVIC_DMA1Chan1Handler
.thumb_set NVIC_DMA1Chan1Handler,_hang
.weak NVIC_DMA1Chan2_3Handler
.thumb_set NVIC_DMA1Chan2_3Handler,_hang
.weak NVIC_DMA1Chan4_7Handler
.thumb_set NVIC_DMA1Chan4_7Handler,_hang
.weak NVIC_ADCCompHandler
.thumb_set NVIC_ADCCompHandler,_hang
.weak NVIC_LPTIM1Handler
.thumb_set NVIC_LPTIM1Handler,_hang
.weak NVIC_Usart4_5Handler
.thumb_set NVIC_Usart4_5Handler,_hang
.weak NVIC_Tim2Handler
.thumb_set NVIC_Tim2Handler,_hang
.weak NVIC_Tim3Handler
.thumb_set NVIC_Tim3Handler,_hang
.weak NVIC_Tim6Handler
.thumb_set NVIC_Tim6Handler,_hang
.weak NVIC_Tim7Handler
.thumb_set NVIC_Tim7Handler,_hang
.weak NVIC_Tim21Handler
.thumb_set NVIC_Tim21Handler,_hang
.weak NVIC_I2C3Handler
.thumb_set NVIC_I2C3Handler,_hang
.weak NVIC_Tim22Handler
.thumb_set NVIC_Tim22Handler,_hang
.weak NVIC_I2C1Handler
.thumb_set NVIC_I2C1Handler,_hang
.weak NVIC_I2C2Handler
.thumb_set NVIC_I2C2Handler,_hang
.weak NVIC_Spi1Handler
.thumb_set NVIC_Spi1Handler,_hang
.weak NVIC_Spi2Handler
.thumb_set NVIC_Spi2Handler,_hang
.weak NVIC_Usart1Handler
.thumb_set NVIC_Usart1Handler,_hang
.weak NVIC_Usart2Handler
.thumb_set NVIC_Usart2Handler,_hang
.weak NVIC_LpUart1_AesHandler
.thumb_set NVIC_LpUart1_AesHandler,_hang

