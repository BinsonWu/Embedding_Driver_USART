/**
  ******************************************************************************
  * @file    	my_stm32f4xx_usart.h
  * @author  	BinsonWu
  * @date	14-April-2017
  * @purpose	driver practice
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

// 30.6.1 Status register (USART_SR)
// Address offset: 0x00
#define USART_SR_CTS		((uint16_t)0x0200)			// Clear To Send 清除發送 ***This bit is not available for UART4 & UART5.***
#define USART_SR_LBD		((uint16_t)0x0100)			// LIN break detection flag 
#define USART_SR_TXE		((uint16_t)0x0080)			// Transmit data register empty
#define USART_SR_TC		((uint16_t)0x0040)			// Transmission complete
#define USART_SR_RXNE		((uint16_t)0x0020)			// Read data register not empty
#define USART_SR_IDLE		((uint16_t)0x0010)			// IDLE line detected
#define USART_SR_ORE		((uint16_t)0x0008)			// Overrun error
#define USART_SR_NF		((uint16_t)0x0004)			// Noise detected flag
#define USART_SR_FE		((uint16_t)0x0002)			// Framing error
#define USART_SR_PE		((uint16_t)0x0001)			// Parity error

// 30.6.2 Data register (USART_DR)
// Address offset: 0x04
#define USART_DR_DR		((uint16_t)0x0001)			// DR[8:0] 		: Data value

// 30.6.3 Baud rate register (USART_BRR)
// Address offset: 0x08
#define USART_BRR_DIV_Mantissa	((uint16_t)0x0010)			// DIV_Mantissa[11:0]	: mantissa of USARTDIV	尾數
#define USART_BRR_DIV_Fractio	((uint16_t)0x0001)			// DIV_Fraction[3:0]	: fraction of USARTDIV	分數

// 30.6.4 Control register 1 (USART_CR1)
// Address offset: 0x0C
#define USART_CR1_OVER8		((uint16_t)0x8000)			// Oversampling mode				0: oversampling by 16				
							//						1: oversampling by 8
#define USART_CR1_UE		((uint16_t)0x2000)			// USART enable					0: USART prescaler and outputs disabled		
							//						1: USART enabled
#define USART_CR1_M		((uint16_t)0x1000)			// Word length					0: 1 Start bit, 8 Data bits, n Stop bit		
							//						1: 1 Start bit, 9 Data bits, n Stop bit
#define USART_CR1_WAKE		((uint16_t)0x0800)			// Wakeup method				0: Idle Line					
							//						1: Address Mark
#define USART_CR1_PCE		((uint16_t)0x0400)			// Parity control enable			0: Parity control disabled			
							//						1: Parity control enabled
#define USART_CR1_PS		((uint16_t)0x0200)			// Parity selection				0: Even parity					
							//  						1: Odd parity
#define USART_CR1_PEIE		((uint16_t)0x0100)			// PE interrupt enable				0: Interrupt is inhibited			
							// 						1: An USART interrupt is generated whenever PE=1 in the USART_SR register
#define USART_CR1_TXEIE		((uint16_t)0x0080)			// TXE interrupt enable				0: Interrupt is inhibited			 
							//						1: An USART interrupt is generated whenever TXE=1 in the USART_SR register
#define USART_CR1_TCIE		((uint16_t)0x0040)			// Transmission complete interrupt enable	0: Interrupt is inhibited
							// 						1: An USART interrupt is generated whenever TC=1 in the USART_SR register
#define USART_CR1_RXNEIE	((uint16_t)0x0020)			// RXNE interrupt enable			0: Interrupt is inhibited
							//						1: An USART interrupt is generated whenever ORE=1 or RXNE=1 
							//						   in the USART_SR register
#define USART_CR1_IDLEIE	((uint16_t)0x0010)			// IDLE interrupt enable			0: Interrupt is inhibited
							//						1: An USART interrupt is generated whenever IDLE=1 in the USART_SR register
#define USART_CR1_TE		((uint16_t)0x0008)			// Transmitter enable				0: Transmitter is disabled
							//						1: Transmitter is enabled
#define USART_CR1_RE		((uint16_t)0x0004)			// Receiver enable				0: Receiver is disabled
							// 						1: Receiver is enabled and begins searching for a start bit
#define USART_CR1_RWU		((uint16_t)0x0002)			// Receiver wakeup				0: Receiver in active mode
							//						1: Receiver in mute mode
#define USART_CR1_SBK		((uint16_t)0x0001)			// Send break 					0: No break character is transmitted
							// 						1: Break character will be transmitted

// 30.6.5 Control register 2 (USART_CR2)
// Address offset: 0x10
#define USART_CR2_LINEN		((uint16_t)0x4000)			// LIN mode enable				0: LIN mode disabled
							// 						1: LIN mode enabled
#define USART_CR2_STOP		((uint16_t)0x1000)			// STOP bits[2:0] These bits are used for programming the stop bits.
							// 00: 1 Stop bit
							// 01: 0.5 Stop bit		*** The 0.5 Stop bit and 1.5 Stop bit are ***
							// 10: 2 Stop bits		*** not available for UART4 & UART5.	  ***
							// 11: 1.5 Stop bit	 
#define USART_CR2_CLKEN		((uint16_t)0x0800)			// Clock enable					0: CK pin disabled 
							// 						1: CK pin enabled
							// *** This bit is not available for UART4 & UART5. ***
#define USART_CR2_CPOL		((uint16_t)0x0400)			// Clock polarity				0: Steady low value on CK pin outside transmission window.
							// 						1: Steady high value on CK pin outside transmission window.
							// *** This bit is not available for UART4 & UART5. ***
#define USART_CR2_CPHA		((uint16_t)0x0200)			// Clock phase					0: The first clock transition is the first data capture edge
							// 						1: The second clock transition is the first data capture edge
							// *** This bit is not available for UART4 & UART5. ***
#define USART_CR2_LBCL		((uint16_t)0x0100)			// Last bit clock pulse				0: The clock pulse of the last data bit is not output to the CK pin
							//						1: The clock pulse of the last data bit is output to the CK pin
							// *** This bit is not available for UART4 & UART5. & 最後一個 Bit 決定於 Word Length 為 8 還 9 ***
#define USART_CR2_LBDIE		((uint16_t)0x0040)			// LIN break detection interrupt enable		0: Interrupt is inhibited
							// 						1: An interrupt is generated whenever LBD=1 in the USART_SR register
#define USART_CR2_LBDL		((uint16_t)0x0020)			// lin break detection length			0: 10-bit break detection
							// 						1: 11-bit break detection
#define USART_CR2_ADD		((uint16_t)0x0001)			// ADD[3:0]: Address of the USART node

// 30.6.6 Control register 3 (USART_CR3)
// Address offset: 0x14
#define USART_CR3_ONEBIT	((uint16_t)0x0800)			// One sample bit method enable			0: Three sample bit method
							// 						1: One sample bit method
#define USART_CR3_CTSIE		((uint16_t)0x0400)			// CTS interrupt enable				0: Interrupt is inhibited
							// 						1: An interrupt is generated whenever CTS=1 in the USART_SR register
							// *** This bit is not available for UART4 & UART5. ***
#define USART_CR3_CTSE		((uint16_t)0x0200)			// CTS enable			0: CTS hardware flow control disabled
							//				1: CTS mode enabled, data is only transmitted when the CTS input is asserted (tied to 0).
							// *** This bit is not available for UART4 & UART5. ***
#define USART_CR3_RTSE		((uint16_t)0x0100)			// RTS enable			0: RTS hardware flow control disabled
							// 				1: RTS interrupt enabled, data is only requested when there is space in the receive buffer.
							// *** This bit is not available for UART4 & UART5. ***
// This two bits DMAT & DMAR are set/reset by software
#define USART_CR3_DMAT		((uint16_t)0x0080)			// DMA enable transmitter			1: DMA mode is enabled for transmission.
							// 						0: DMA mode is disabled for transmission.
#define USART_CR3_DMAR		((uint16_t)0x0040)			// DMA enable receiver				1: DMA mode is enabled for reception
							// 						0: DMA mode is disabled for reception
#define USART_CR3_SCEN		((uint16_t)0x0020)			// Smartcard mode enable			0: Smartcard Mode disabled
							// 						1: Smartcard Mode enabled
							// *** This bit is not available for UART4 & UART5. ***
#define USART_CR3_NACK		((uint16_t)0x0010)			// Smartcard NACK enable			0: NACK transmission in case of parity error is disabled
							// 						1: NACK transmission during parity error is enabled
							// *** This bit is not available for UART4 & UART5. ***
#define USART_CR3_HDSEL		((uint16_t)0x0008)			// Half-duplex selection			0: Half duplex mode is not selected
							// 						1: Half duplex mode is selected
#define USART_CR3_IRLP		((uint16_t)0x0004)			// IrDA low-power				0: Normal mode
							// 						1: Low-power mode
#define USART_CR3_IREN		((uint16_t)0x0002)			// IrDA mode enable				0: IrDA disabled
							// 						1: IrDA enabled
#define USART_CR3_EIE		((uint16_t)0x0001)			// Error interrupt enable			0: Interrupt is inhibited
							// 1: An interrupt is generated whenever DMAR=1 in the USART_CR3 register and FE=1 or ORE=1 or NF=1 in the USART_SR register.

// 30.6.7 Guard time and prescaler register (USART_GTPR)
// Address offset: 0x18
#define USART_GTPR_GT		((uint16_t)0x0100)			// Guard time value
							// *** This bit is not available for UART4 & UART5. ***
#define USART_GTPR_PSC		((uint16_t)0x0001)			// Prescaler value
							// *** This bit is not available for UART4 & UART5. ***
// 不太知道這兩個做什麼用


// Define Array opt
// For CR1
#define USART_OVER8_by16		((uint16_t)0x0000)
#define USART_OVER8_by8			((uint16_t)0x8000)

#define USART_WAKE_Idle_Line		((uint16_t)0x0000)
#define USART_WAKE_Address_Mark		((uint16_t)0x0800)

#define USART_Word_Length_8bits		((uint16_t)0x0000)
#define USART_Word_Length_9bits		((uint16_t)0x1000)

#define USART_Parity_Even		((uint16_t)0x0000)		
#define USART_Parity_Odd		((uint16_t)0x0200)		

#define USART_RWU_active_mode		((uint16_t)0x0000)
#define USART_RWU_mute_mode		((uint16_t)0x0002)

#define USART_SBK_N			((uint16_t)0x0000)
#define USART_SBK_Y			((uint16_t)0x0001)

// Foe CR2
#define USART_Stop_Bits_1		((uint16_t)0x0000)
#define USART_Stop_Bits_0_5		((uint16_t)0x1000)
#define USART_Stop_Bits_2		((uint16_t)0x2000)
#define USART_Stop_Bits_1_5		((uint16_t)0x3000)

#define USART_CPOL_L			((uint16_t)0x0000)
#define USART_CPOL_H			((uint16_t)0x0400)

#define USART_CPHA_L			((uint16_t)0x0000)
#define USART_CPHA_H			((uint16_t)0x0200)

#define USART_LBCL_noOutput		((uint16_t)0x0000)
#define USART_LBCL_Output		((uint16_t)0x0100)

#define USART_LBDL_10bits		((uint16_t)0x0000)
#define USART_LBDL_11bits		((uint16_t)0x0020)

// For CR3
#define USART_HDSEL_N			((uint16_t)0x0000)
#define USART_HDSEL_Y			((uint16_t)0x0008)

#define USART_IRLP_Normal_mode		((uint16_t)0x0000)
#define USART_IRLP_Low-power_mode	((uint16_t)0x0004)

// Array Not Give Value
// USART_DR_DR
// USART_BRR_DIV_Mantissa
// USART_BRR_DIV_Fractio
// USART_CR2_ADD

// 30.6.8 USART register map
typedef struct {
	__IO uint16_t USART_SR;		// Status register
	__IO uint16_t Reserved0;		// Reserved
	__IO uint16_t USART_DR;		// Data register
	__IO uint16_t Reserved1;		// Reserved
	__IO uint16_t USART_BRR;		// Baud rate register
	__IO uint16_t Reserved2;		// Reserved
	__IO uint16_t USART_CR1;		// Control register 1
	__IO uint16_t Reserved3;		// Reserved
	__IO uint16_t USART_CR2;		// Control register 2
	__IO uint16_t Reserved4;		// Reserved
	__IO uint16_t USART_CR3;		// Control register 3
	__IO uint16_t Reserved5;		// Reserved
	__IO uint16_t USART_GTPR;		// Guard time and prescaler register
	__IO uint16_t Reserved6;		// Reserved
}USART_RM;

// USART_CR1_PCE 	= 0 => USART_CR1_PS						Not Work
// USART_CR2_CLKEN 	= 0 => USART_CR2_CPOL , USART_CR2_CPHA , USART_CR2_LBCL		Not Work
#define USART_Parity_Disable		((uint16_t)0x0000)
#define USART_Parity_Enable		((uint16_t)0x0400)
#define USART_Clock_Disable		((uint16_t)0x0000)
#define USART_Clock_Enable		((uint16_t)0x0800)
typedef struct {
	// BRR
	uint32_t USART_Baud_Rate;			// Baud Rate
	// CR1
	uint16_t USART_OVER8;			// Oversampling mode
	uint16_t USART_WAKE;			// Word length
	uint16_t USART_Word_Length;		// Wakeup method
	uint16_t USART_Parity_IfEnable;	// Enable PCE
	uint16_t USART_Parity;		// Parity selection		*** Need USART_CR1_PCE ***
	uint16_t USART_RWU;			// Receiver wakeup
	uint16_t USART_SBK;			// Send break
	// CR2
	uint16_t USART_Stop_Bits;		// These bits are used for programming the stop bits.
	uint16_t USART_Clock_IfEnable;	// Enable CLKEN
	uint16_t USART_CPOL;			// Clock polarity		*** Need USART_CR2_CLKEN ***
	uint16_t USART_CPHA;			// Clock phase			*** Need USART_CR2_CLKEN ***
	uint16_t USART_LBCL;			// Last bit clock pulse		*** Need USART_CR2_CLKEN ***
	uint16_t USART_LBDL;			// lin break detection length
	// CR3	
	uint16_t USART_HDSEL;			// Half-duplex selection
	uint16_t USART_IRLP;			// IrDA low-power
}USART_STRUCTURE;

// 依第幾個暫存器設置第五個 Bit 為 1, 2, 3.
#define USART_IT_PE                         	((uint16_t)0x0018)
#define USART_IT_TXE                         	((uint16_t)0x0017)
#define USART_IT_TC                          	((uint16_t)0x0016)
#define USART_IT_RXNE                        	((uint16_t)0x0015)
#define USART_IT_ORE_RX                      	((uint16_t)0x0015)
#define USART_IT_IDLE                       	((uint16_t)0x0014)
#define USART_IT_LBD                        	((uint16_t)0x0026)
#define USART_IT_CTS                        	((uint16_t)0x003A)
#define USART_IT_ERR                        	((uint16_t)0x0030)
#define USART_IT_ORE_ER				((uint16_t)0x0030)
#define USART_IT_NE                          	((uint16_t)0x0030)
#define USART_IT_FE                          	((uint16_t)0x0030)

// Configure Define
#define 

void USART_Init( USART_TypeDef* USARTx , USART_STRUCTURE* USARTx_STRUCTURE );			// Init
void USART_DeInit();										// DeInit
void USART_Structure_Init( USART_STRUCTURE* USARTx_STRUCTURE );					// Init Structure
void USART_RecieveData(USART_TypeDef* USARTx);							// RX
void USART_TransmitData(USART_TypeDef* USARTx);							// TX
int  Is_In_USART_1236( USART_TypeDef* USARTx );							// Check if this USART is 4 , 5 , 7 or 8

// Selection Mode
void USART_OVER8_Mode( 		USART_TypeDef *USARTx , uint16_t Mode );		// About Baud Rate
void USART_WAKE_Mode( 		USART_TypeDef *USARTx , uint16_t Mode );		// About USART Wake Up Mode
void USART_Word_Length_Mode( 	USART_TypeDef *USARTx , uint16_t Mode );		// About R / T Format
int  USART_Parity_Mode( 	USART_TypeDef *USARTx , uint16_t Mode );		// About Parity Return If Succeed
void USART_RWU_Mode( 		USART_TypeDef *USARTx , uint16_t Mode );		// About Reciever Wake Up Mode
void USART_SBK_Mode( 		USART_TypeDef *USARTx , uint16_t Mode );		// 
void USART_Stop_Bits_Mode( 	USART_TypeDef *USARTx , uint16_t Mode );		// About R / T Format
int  USART_CPOL_Mode( 		USART_TypeDef *USARTx , uint16_t Mode );		// About Clock Return If Succeed
int  USART_CPHA_Mode( 		USART_TypeDef *USARTx , uint16_t Mode );		// About Clock Return If Succeed
int  USART_LBCL_Mode( 		USART_TypeDef *USARTx , uint16_t Mode );		// About Clock Return If Succeed
void USART_LBDL_Mode( 		USART_TypeDef *USARTx , uint16_t Mode );		// About LIN
void USART_HDSEL_Mode( 		USART_TypeDef *USARTx , uint16_t Mode );		// About Half-duplex
void USART_IRLP_Mode( 		USART_TypeDef *USARTx , uint16_t Mode );		// About IrDA

// Command
void USART_Cmd( 		USART_TypeDefM *USARTx , int EnableVal );			// About Enable UE make USART start.
void USART_Parity_Cmd( 		USART_TypeDef *USARTx , int EnableVal );			// About Parity
void USART_LIN_Cmd( 		USART_TypeDef *USARTx , int EnableVal );			// About LIN
void USART_Clock_Cmd( 		USART_TypeDef *USARTx , int EnableVal );			// About Clock
void USART_OneSampleBit_Cmd( 	USART_TypeDef *USARTx , int EnableVal );			// About OneSampleBit
void USART_CTS_Cmd( 		USART_TypeDef *USARTx , int EnableVal );			//
void USART_RTS_Cmd( 		USART_TypeDef *USARTx , int EnableVal );			//
void USART_DMAT_Cmd( 		USART_TypeDef *USARTx , int EnableVal );			// About DMA
void USART_DMAR_Cmd( 		USART_TypeDef *USARTx , int EnableVal );			// About DMA
void USART_Smartcard_Cmd( 	USART_TypeDef *USARTx , int EnableVal );			// About SmartCard
void USART_Smartcard_NACK_Cmd( 	USART_TypeDef *USARTx , int EnableVal );			// About SmartCard
void USART_IrDA_Cmd( 		USART_TypeDef *USARTx , int EnableVal );			// About IrDA
void USART_IT_Cmd( 		USART_TypeDef* USARTx , int USART_IT , int EnableVal );		// About Enable Interrupt

void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime);			// About SmartCard


// Equation 1: Baud rate for standard USART (SPI mode included)
//			    f CK
// Tx/Rx baud = -----------------------------
//		8 × ( 2 – OVER8 ) × USARTDIV

// Equation 2: Baud rate in Smartcard, LIN and IrDA modes
//			    f CK
// Tx/Rx baud = -----------------------------
//			16 × USARTDIV

// How to derive USARTDIV from USART_BRR register values when OVER8=0
// Example 1:
// If 	DIV_Mantissa 		= 0d27 
// and 	DIV_Fraction 		= 0d12 	(USART_BRR = 0x1BC), 
// then
// Mantissa (USARTDIV) 		= 0d27
// Fraction (USARTDIV) 		= 12/16 	= 0d0.75
// Therefore USARTDIV 		= 0d27.75

// How to derive USARTDIV from USART_BRR register values when OVER8=1
// Example 1:
// If 	DIV_Mantissa 		= 0x27 
// and 	DIV_Fraction[2:0]	= 0d6 	(USART_BRR = 0x1B6),
// then
// Mantissa (USARTDIV) 		= 0d27
// Fraction (USARTDIV) 		= 6/8 		= 0d0.75
// Therefore USARTDIV 		= 0d27.75
