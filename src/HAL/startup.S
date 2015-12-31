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
	.word NVIC_TamperSamperHandler /* 0x048 */
	.word NVIC_RTCWkUpHandler    /* 0x04c */
	.word NVIC_FlashHandler      /* 0x050 */
	.word NVIC_RCCHandler        /* 0x054 */
	.word NVIC_EXTI0             /* 0x058 */
	.word NVIC_EXTI1             /* 0x05c */
	.word NVIC_EXTI2             /* 0x060 */
	.word NVIC_EXTI3             /* 0x064 */
	.word NVIC_EXTI4             /* 0x068 */
	.word NVIC_DMA1Ch1Handler    /* 0x06c */
	.word NVIC_DMA1Ch2Handler    /* 0x070 */
	.word NVIC_DMA1Ch3Handler    /* 0x074 */
	.word NVIC_DMA1Ch4Handler    /* 0x078 */
	.word NVIC_DMA1Ch5Handler    /* 0x07c */
	.word NVIC_DMA1Ch6Handler    /* 0x080 */
	.word NVIC_DMA1Ch7Handler    /* 0x084 */
	.word NVIC_ADC1Handler       /* 0x088 */
	.word NVIC_USBHPHandler      /* 0x08c */
	.word NVIC_USBLPHandler      /* 0x090 */
	.word NVIC_DACHandler        /* 0x094 */
	.word NVIC_COMPCAHandler     /* 0x098 */
	.word NVIC_EXTI9_5Handler    /* 0x09c */
	.word NVIC_LCDHandler        /* 0x0a0 */
	.word NVIC_Timer9Handler     /* 0x0a4 */
	.word NVIC_Timer10Handler    /* 0x0a8 */
	.word NVIC_Timer11Handler    /* 0x0ac */
	.word NVIC_Timer2Handler     /* 0x0b0 */
	.word NVIC_Timer3Handler     /* 0x0b4 */
	.word NVIC_Timer4Handler     /* 0x0b8 */
	.word NVIC_I2C1_EVHandler    /* 0x0bc */
	.word NVIC_I2C1_ERHandler    /* 0x0c0 */
	.word NVIC_I2C2_EVHandler    /* 0x0c4 */
	.word NVIC_I2C2_ERHandler    /* 0x0c8 */
	.word NVIC_SPI1Handler       /* 0x0cc */
	.word NVIC_SPI2Handler       /* 0x0d0 */
	.word NVIC_USART1Handler     /* 0x0d4 */
	.word NVIC_USART2Handler     /* 0x0d8 */
	.word NVIC_USART3Handler     /* 0x0dc */
	.word NVIC_EXTI15_10Handler  /* 0x0e0 */
	.word NVIC_RTCAlarmHandler   /* 0x0e4 */
	.word NVIC_USBFSWkUpHandler  /* 0x0e8 */
	.word NVIC_Timer6Handler     /* 0x0ec */
	.word NVIC_Timer7Handler     /* 0x0f0 */
	.word 0x00000000             /* 0x0f4 */
	.word NVIC_Timer5Handler     /* 0x0f8 */
	.word NVIC_SPI3Handler       /* 0x0fc */
	.word 0x00000000             /* 0x100 */
	.word 0x00000000             /* 0x104 */
	.word NVIC_DMA2Ch1Handler    /* 0x108 */
	.word NVIC_DMA2Ch2Handler    /* 0x10c */
	.word NVIC_DMA2Ch3Handler    /* 0x110 */
	.word NVIC_DMA2Ch4Handler    /* 0x114 */
	.word NVIC_DMA2Ch5Handler    /* 0x118 */
	.word NVIC_AESHandler        /* 0x11c */
	.word NVIC_CompAcaHandler    /* 0x120 */

.section .text

_reset:
	ldr r0, =main
	bx r0
	b _hang

_hang:
	b .

.weak NVIC_ResetHandler
.thumb_set NVIC_ResetHandler,_reset

.weak NVIC_NMIHandler
.thumb_set NVIC_NMIHandler,_hang

.weak NVIC_HardFaultHandler
.thumb_set NVIC_HardFaultHandler,_hang

.weak NVIC_MemManageHandler
.thumb_set NVIC_MemManageHandler,_hang

.weak NVIC_BusFaultHandler
.thumb_set NVIC_BusFaultHandler,_hang

.weak NVIC_UsageFaultHandler
.thumb_set NVIC_UsageFaultHandler,_hang

.weak NVIC_SVCHandler
.thumb_set NVIC_SVCHandler,_hang

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

.weak NVIC_TamperSamperHandler
.thumb_set NVIC_TamperSamperHandler,_hang

.weak NVIC_RTCWkUpHandler
.thumb_set NVIC_RTCWkUpHandler,_hang

.weak NVIC_FlashHandler
.thumb_set NVIC_FlashHandler,_hang

.weak NVIC_RCCHandler
.thumb_set NVIC_RCCHandler,_hang

.weak NVIC_EXTI0
.thumb_set NVIC_EXTI0,_hang

.weak NVIC_EXTI1
.thumb_set NVIC_EXTI1,_hang

.weak NVIC_EXTI2
.thumb_set NVIC_EXTI2,_hang

.weak NVIC_EXTI3
.thumb_set NVIC_EXTI3,_hang

.weak NVIC_EXTI4
.thumb_set NVIC_EXTI4,_hang

.weak NVIC_DMA1Ch1Handler
.thumb_set NVIC_DMA1Ch1Handler,_hang

.weak NVIC_DMA1Ch2Handler
.thumb_set NVIC_DMA1Ch2Handler,_hang

.weak NVIC_DMA1Ch3Handler
.thumb_set NVIC_DMA1Ch3Handler,_hang

.weak NVIC_DMA1Ch4Handler
.thumb_set NVIC_DMA1Ch4Handler,_hang

.weak NVIC_DMA1Ch5Handler
.thumb_set NVIC_DMA1Ch5Handler,_hang

.weak NVIC_DMA1Ch6Handler
.thumb_set NVIC_DMA1Ch6Handler,_hang

.weak NVIC_DMA1Ch7Handler
.thumb_set NVIC_DMA1Ch7Handler,_hang

.weak NVIC_ADC1Handler
.thumb_set NVIC_ADC1Handler,_hang

.weak NVIC_USBHPHandler
.thumb_set NVIC_USBHPHandler,_hang

.weak NVIC_USBLPHandler
.thumb_set NVIC_USBLPHandler,_hang

.weak NVIC_DACHandler
.thumb_set NVIC_DACHandler,_hang

.weak NVIC_COMPCAHandler
.thumb_set NVIC_COMPCAHandler,_hang

.weak NVIC_EXTI9_5Handler
.thumb_set NVIC_EXTI9_5Handler,_hang

.weak NVIC_LCDHandler
.thumb_set NVIC_LCDHandler,_hang

.weak NVIC_Timer9Handler
.thumb_set NVIC_Timer9Handler,_hang

.weak NVIC_Timer10Handler
.thumb_set NVIC_Timer10Handler,_hang

.weak NVIC_Timer11Handler
.thumb_set NVIC_Timer11Handler,_hang

.weak NVIC_Timer2Handler
.thumb_set NVIC_Timer2Handler,_hang

.weak NVIC_Timer3Handler
.thumb_set NVIC_Timer3Handler,_hang

.weak NVIC_Timer4Handler
.thumb_set NVIC_Timer4Handler,_hang

.weak NVIC_I2C1_EVHandler
.thumb_set NVIC_I2C1_EVHandler,_hang

.weak NVIC_I2C1_ERHandler
.thumb_set NVIC_I2C1_ERHandler,_hang

.weak NVIC_I2C2_EVHandler
.thumb_set NVIC_I2C2_EVHandler,_hang

.weak NVIC_I2C2_ERHandler
.thumb_set NVIC_I2C2_ERHandler,_hang

.weak NVIC_SPI1Handler
.thumb_set NVIC_SPI1Handler,_hang

.weak NVIC_SPI2Handler
.thumb_set NVIC_SPI2Handler,_hang

.weak NVIC_USART1Handler
.thumb_set NVIC_USART1Handler,_hang

.weak NVIC_USART2Handler
.thumb_set NVIC_USART2Handler,_hang

.weak NVIC_USART3Handler
.thumb_set NVIC_USART3Handler,_hang

.weak NVIC_EXTI15_10Handler
.thumb_set NVIC_EXTI15_10Handler,_hang

.weak NVIC_RTCAlarmHandler
.thumb_set NVIC_RTCAlarmHandler,_hang

.weak NVIC_USBFSWkUpHandler
.thumb_set NVIC_USBFSWkUpHandler,_hang

.weak NVIC_Timer6Handler
.thumb_set NVIC_TIMER6Handler,_hang

.weak NVIC_Timer7Handler
.thumb_set NVIC_TIMER7Handler,_hang

.weak NVIC_Timer5Handler
.thumb_set NVIC_TIMER5Handler,_hang

.weak NVIC_SPI3Handler
.thumb_set NVIC_SPI3Handler,_hang

.weak NVIC_DMA2Ch1Handler
.thumb_set NVIC_DMA2Ch1Handler,_hang

.weak NVIC_DMA2Ch2Handler
.thumb_set NVIC_DMA2Ch2Handler,_hang

.weak NVIC_DMA2Ch3Handler
.thumb_set NVIC_DMA2Ch3Handler,_hang

.weak NVIC_DMA2Ch4Handler
.thumb_set NVIC_DMA2Ch4Handler,_hang

.weak NVIC_DMA2Ch5Handler
.thumb_set NVIC_DMA2Ch5Handler,_hang

.weak NVIC_AESHandler
.thumb_set NVIC_AESHandler,_hang

.weak NVIC_CompAcaHandler
.thumb_set NVIC_CompAcaHandler,_hang
