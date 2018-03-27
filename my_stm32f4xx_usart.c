/**
  ******************************************************************************
  * @file    	my_stm32f4xx_usart.c
  * @author  	BinsonWu
  * @date	14-April-2017
  * @purpose	driver practice
  ******************************************************************************
  */

#include "stm32f4xx_rcc.h"
#include "USART_Functional.h"

#define Disable	0
#define Enable 	1

/**
  * @brief  Deinitializes the USARTx peripheral registers to their default reset values.
  * @param  USARTx: where x can be 1, 2, 3, 4, 5, 6, 7 or 8 to select the USART or 
  *         UART peripheral.
  * @retval None
  */
void USART_DeInit(USART_TypeDef* USARTx)
{
	/* Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(USARTx));

	if (USARTx == USART1)
	{
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
	}
	else if (USARTx == USART2)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
	}
	else if (USARTx == USART3)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
	}    
	else if (USARTx == UART4)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, DISABLE);
	}
	else if (USARTx == UART5)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, DISABLE);
	}  
	else if (USARTx == USART6)
	{
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART6, ENABLE);
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART6, DISABLE);
	}
	else if (USARTx == UART7)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART7, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART7, DISABLE);
	}     
	else
	{
		if (USARTx == UART8)
		{ 
			RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART8, ENABLE);
			RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART8, DISABLE);
		}
	}
}

void USART_Init( USART_RM* USARTx , USART_STRUCTURE* USARTx_STRUCTURE ){
	// Structure to Register
	uint32_t tempregister = ((uint32_t)0x00);
	// BRR
	tempregister  = USARTx->BRR;
	USARTx->BRR   = (uint16_t)tempregister;
	// CR1
	tempregister  = USARTx->CR1;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_OVER8;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_WAKE;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_Word_Length;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_Parity_IfEnable;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_Parity;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_RW;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_SBK;
	USARTx->CR1   = (uint16_t)tempregister;
	// CR2
	tempregister  = USARTx->CR2;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_Stop_Bits;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_Clock_IfEnable;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_CPOL;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_CPHA;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_LBCL;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_LBDL;
	USARTx->CR2   = (uint16_t)tempregister;
	// CR3
	tempregister  = USARTx->CR3;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_HDSEL;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_IRLP;
	USARTx->CR3   = (uint16_t)tempregister;	

	// Enable RX TX
	tempregister  = USARTx->CR1;
	tempregister |= (uint32_t)USART_CR1_TE;
	tempregister |= (uint32_t)USART_CR1_RE;
	USARTx->CR1   = (uint16_t)tempregister;

	// Baud Rate
	// USARTDIV = fck / ( 8*(2-OVER8)*(uint32_t)USARTx_STRUCTURE->USART_Baud_Rate )
	RCC_GetClocksFreq(&RCC_ClocksStatus);
	uint32_t apbclock = ((uint32_t)0x00);
	if ((USARTx == USART1) || (USARTx == USART6))
	{
		apbclock = RCC_ClocksStatus.PCLK2_Frequency;
	}
	else
	{
		apbclock = RCC_ClocksStatus.PCLK1_Frequency;
	}

	uint32_t USARTDIV = ((uint32_t)0x00);
	if( (USARTx->CR1 & USART_CR1_OVER8) == 0){
		// Ori : USARTDIV = (100*apbclock)/( 8*(2-0)*(uint32_t)USARTx_STRUCTURE->USART_Baud_Rate );
		// Simplification =>
		USARTDIV = (25 * apbclock) / (4 * (uint32_t)USARTx_STRUCTURE->USART_Baud_Rate);
	}
	else if( (USARTx->CR1 & USART_CR1_OVER8) == 1){
		// Ori : USARTDIV = (100*apbclock)/( 8*(2-1)*(uint32_t)USARTx_STRUCTURE->USART_Baud_Rate );
		// Simplification =>
		USARTDIV = (25 * apbclock) / (2 * (uint32_t)USARTx_STRUCTURE->USART_Baud_Rate);		
	}

	uint32_t Mantissa = ((uint32_t)0x00);
	uint32_t Fraction = ((uint32_t)0x00);
	// Before Point
	Mantissa 	= (USARTDIV/100) << 4;
	tempregister 	= Mantissa;
	// After Point
	Fraction 	= USARTDIV - (Mantissa >> 4)*100 ;
	
	// +50 For Rounded to an Integer
	if( (USARTx->CR1 & USART_CR1_OVER8) == 0){
		// DIV_fraction[3:0] Need After two decimal places
		tempregister |= (((Fraction * 16) + 50) / 100) & ((unsigned char)0x0F);
	}
	else if( (USARTx->CR1 & USART_CR1_OVER8) == 1){	
		// DIV_fraction[2:0] Need After two decimal places
		tempregister |= (((Fraction * 8) + 50) / 100) & ((unsigned char)0x07);
	}
	USARTx->BRR = (uint16_t)tempregister;
}

void USART_Structure_Init(USART_STRUCTURE *USARTx_STRUCTURE){
	// BRR
	USARTx_STRUCTURE->USART_Baud_Rate 	= 9600;				// Baud Rate
	// CR1
	USARTx_STRUCTURE->USART_OVER8		= USART_OVER8_by16;		// Oversampling mode
	USARTx_STRUCTURE->USART_WAKE		= USART_WAKE_Idle_Line;		// Word length
	USARTx_STRUCTURE->USART_Word_Length	= USART_Word_Length_8bits;	// Wakeup method
	USARTx_STRUCTURE->USART_Parity_IfEnable	= USART_Parity_Disable;		// Parity If Enable
	USARTx_STRUCTURE->USART_Parity		= USART_Parity_Even;		// Parity selection
	USARTx_STRUCTURE->USART_RWU		= USART_RWU_active_mode;	// Receiver wakeup
	USARTx_STRUCTURE->USART_SBK		= USART_SBK_N;			// Send break
	// CR2
	USARTx_STRUCTURE->USART_Stop_Bits	= USART_Stop_Bits_1;		// These bits are used for programming the stop bits.
	USARTx_STRUCTURE->USART_Clock_IfEnable	= USART_Clock_Disable;		// Clock If Enable
	USARTx_STRUCTURE->USART_CPOL		= USART_CPOL_L;			// Clock polarity
	USARTx_STRUCTURE->USART_CPHA		= USART_CPHA_L;			// Clock phase
	USARTx_STRUCTURE->USART_LBCL		= USART_LBCL_noOutput;		// Last bit clock pulse
	USARTx_STRUCTURE->USART_LBDL		= USART_LBDL_10bits;		// lin break detection length
	// CR3
	USARTx_STRUCTURE->USART_HDSEL		= USART_HDSEL_N;		// Half-duplex selection
	USARTx_STRUCTURE->USART_IRLP		= USART_IRLP_Normal_mode;	// IrDA low-power
}

/*void USART_Configurable_stop_bits( USART_RM* USARTx , USART_STRUCTURE* USARTx_STRUCTURE ){
	uint32_t tempregister = ((uint32_t)0x00);
	// 1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	tempregister  = USARTx->CR1;
	tempregister |= (uint32_t)USART_CR1_UE;
	USARTx->CR1   = (uint16_t)tempregister;
	// 2. Program the M bit in USART_CR1 to define the word length.
	tempregister  = USARTx->CR2;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_Word_Length;
	// 3. Program the number of stop bits in USART_CR2.
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_Stop_Bits;
	USARTx->CR2   = (uint16_t)tempregister;
	// 4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take place. Configure the DMA register as explained in multibuffer communication. 
	tempregister  = USARTx->CR3;
	tempregister |= (uint32_t)USART_CR3_DMAT;
	USARTx->CR3   = (uint16_t)tempregister;
	// 5. Select the desired baud rate using the USART_BRR register.
	tempregister  = USARTx->BRR;
	// *************************************************
	USARTx->BRR   = (uint16_t)tempregister;
	// 6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
	tempregister  = USARTx->CR1;
	tempregister |= (uint32_t)USART_CR1_TE;
	USARTx->CR1   = (uint16_t)tempregister;
	// 7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this for each data to be transmitted in case of single buffer.
	
	// 8. After writing the last data into the USART_DR register, wait until TC=1. 
	//    This indicates that the transmission of the last frame is complete. 
	//    This is required for instance when the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.

}*/

/*void USART_Character_reception( USART_RM* USARTx , USART_STRUCTURE* USARTx_STRUCTURE ){
	uint32_t tempregister = ((uint32_t)0x00);
	// 1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	tempregister  = USARTx->CR1;
	tempregister |= (uint32_t)USART_CR1_UE;
	USARTx->CR1   = (uint16_t)tempregister;
	// 2. Program the M bit in USART_CR1 to define the word length.
	tempregister  = USARTx->CR2;
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_Word_Length;
	// 3. Program the number of stop bits in USART_CR2.
	tempregister |= (uint32_t)USARTx_STRUCTURE->USART_Stop_Bits;
	USARTx->CR2 = (uint16_t)tempregister;
	// 4. Select DMA enable (DMAR) in USART_CR3 if multibuffer communication is to take place. Configure the DMA register as explained in multibuffer communication. STEP 3
	tempregister  = USARTx->CR3;
	tempregister |= (uint32_t)USART_CR3_DMAR;
	USARTx->CR3   = (uint16_t)tempregister;
	// 5. Select the desired baud rate using the baud rate register USART_BRR
	tempregister  = USARTx->BRR;
	// *************************************************
	USARTx->BRR   = (uint16_t)tempregister;
	// 6. Set the RE bit USART_CR1. This enables the receiver which begins searching for a start bit.
	tempregister  = USARTx->CR1;
	tempregister |= (uint32_t)USART_CR1_RE;
	USARTx->CR1   = (uint16_t)tempregister;
}*/

void USART_RecieveData( USART_RMf* USARTx){
	return (uint16_t)(USARTx->DR & (uint16_t)0x01FF);
}
void USART_TransmitData(USART_RMf* USARTx){
	USARTx->DR = (Data & (uint16_t)0x01FF);
}

int Is_In_USART_1236( USART_TypeDef* USARTx ){
	if(USARTx == USART1 || USARTx == USART2 || USARTx == USART3 || USARTx == USART6 )
		return 1;
	else
		return 0;
}

// Selection Mode
// CR1
void USART_OVER8_Mode( USART_RM *USARTx, uint16_t Mode ){
	uint32_t tempregister = ((uint32_t)0x00);
	tempregister  = USARTx->CR1;
	tempregister |= (uint32_t)Mode;
	USARTx->CR1   = (uint16_t)tempregister;
}
void 	USART_WAKE_Mode( 	USART_RM *USARTx , uint16_t Mode ){
	uint32_t tempregister = ((uint32_t)0x00);
	tempregister  = USARTx->CR1;
	tempregister |= (uint32_t)Mode;
	USARTx->CR1   = (uint16_t)tempregister;
}
void 	USART_Word_Length_Mode( USART_RM *USARTx , uint16_t Mode ){
	uint32_t tempregister = ((uint32_t)0x00);
	tempregister  = USARTx->CR1;
	tempregister |= (uint32_t)Mode;
	USARTx->CR1   = (uint16_t)tempregister;
}
int 	USART_Parity_Mode( 	USART_RM *USARTx , uint16_t Mode ){
	if( ~( (uint16_t)USARTx->CR1 && USART_CR1_PCE ) )
		return 0;
	uint32_t tempregister = ((uint32_t)0x00);
	tempregister  = USARTx->CR1;
	tempregister |= (uint32_t)Mode;
	USARTx->CR1   = (uint16_t)tempregister;
	return 1;
}
void 	USART_RWU_Mode( 	USART_RM *USARTx , uint16_t Mode ){
	uint32_t tempregister = ((uint32_t)0x00);
	tempregister  = USARTx->CR1;
	tempregister |= (uint32_t)Mode;
	USARTx->CR1   = (uint16_t)tempregister;
}
void 	USART_SBK_Mode( 	USART_RM *USARTx , uint16_t Mode ){
	uint32_t tempregister = ((uint32_t)0x00);
	tempregister  = USARTx->CR1;
	tempregister |= (uint32_t)Mode;
	USARTx->CR1   = (uint16_t)tempregister;
}
// CR2
void 	USART_Stop_Bits_Mode( 	USART_RM *USARTx , uint16_t Mode ){
	uint32_t tempregister = ((uint32_t)0x00);
	tempregister  = USARTx->CR2;
	tempregister |= (uint32_t)Mode;
	USARTx->CR2   = (uint16_t)tempregister;
}
int 	USART_CPOL_Mode(	USART_RM *USARTx , uint16_t Mode ){
	if( (uint16_t)USARTx->CR2 && USART_CR2_CLKEN == 0)
		return 0;
	uint32_t tempregister = ((uint32_t)0x00);
	tempregister  = USARTx->CR2;
	tempregister |= (uint32_t)Mode;
	USARTx->CR2   = (uint16_t)tempregister;
	return 1;
}
int 	USART_CPHA_Mode( 	USART_RM *USARTx , uint16_t Mode ){
	if( (uint16_t)USARTx->CR2 && USART_CR2_CLKEN == 0)
		return 0;
	uint32_t tempregister = ((uint32_t)0x00);
	tempregister  = USARTx->CR2;
	tempregister |= (uint32_t)Mode;
	USARTx->CR2   = (uint16_t)tempregister;
	return 1;
}
int 	USART_LBCL_Mode( 	USART_RM *USARTx , uint16_t Mode ){
	if( (uint16_t)USARTx->CR2 && USART_CR2_CLKEN == 0 )
		return 0;
	uint32_t tempregister = ((uint32_t)0x00);
	tempregister  = USARTx->CR2;
	tempregister |= (uint32_t)Mode;
	USARTx->CR2   = (uint16_t)tempregister;
	return 1;
}
void 	USART_LBDL_Mode( 	USART_RM *USARTx , uint16_t Mode ){
	uint32_t tempregister = ((uint32_t)0x00);
	tempregister  = USARTx->CR2;
	tempregister |= (uint32_t)Mode;
	USARTx->CR2   = (uint16_t)tempregister;
}
// CR3
void 	USART_HDSEL_Mode( 	USART_RM *USARTx , uint16_t Mode ){
	uint32_t tempregister = ((uint32_t)0x00);
	tempregister  = USARTx->CR3;
	tempregister |= (uint32_t)Mode;
	USARTx->CR3   = (uint16_t)tempregister;
}
void 	USART_IRLP_Mode( 	USART_RM *USARTx , uint16_t Mode ){
	uint32_t tempregister = ((uint32_t)0x00);
	tempregister  = USARTx->CR3;
	tempregister |= (uint32_t)Mode;
	USARTx->CR3   = (uint16_t)tempregister;
}

// Command
// CR1
void USART_Cmd( 		USART_RM *USARTx , int EnableVal ){
	if(EnableVal)
		USARTx->CR1 |= USART_CR1_UE;
	else
		USARTx->CR1 &= (uint16_t)~((uint16_t)USART_CR1_UE);
}

void USART_Parity_Cmd( 		USART_RM *USARTx , int EnableVal ){
	if(EnableVal)
		USARTx->CR1 |= USART_CR1_PCE;
	else
		USARTx->CR1 &= (uint16_t)~((uint16_t)USART_CR1_PCE);
}

// CR2
void USART_LIN_Cmd( 		USART_RM *USARTx , int EnableVal ){
	if(EnableVal)
		USARTx->CR2 |= USART_CR2_LINEN;
	else
		USARTx->CR2 &= (uint16_t)~((uint16_t)USART_CR2_LINEN);
}

void USART_Clock_Cmd( 		USART_RM *USARTx , int EnableVal ){
	if( Is_In_USART_1236(USARTx) != 1 )
		return;
	if(EnableVal)
		USARTx->CR2 |= USART_CR2_CLKEN;
	else
		USARTx->CR2 &= (uint16_t)~((uint16_t)USART_CR2_CLKEN);
}

// CR3
void USART_OneSampleBit_Cmd( 	USART_RM *USARTx , int EnableVal ){
	if(EnableVal)
		USARTx->CR3 |= USART_CR3_ONEBIT;
	else
		USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_ONEBIT);
}

void USART_CTS_Cmd( 		USART_RM *USARTx , int EnableVal ){
	if( Is_In_USART_1236(USARTx) != 1 )
		return;
	if(EnableVal)
		USARTx->CR3 |= USART_CR3_CTSE;
	else
		USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_CTSE);
}

void USART_RTS_Cmd( 		USART_RM *USARTx , int EnableVal ){
	if( Is_In_USART_1236(USARTx) != 1 )
		return;
	if(EnableVal)
		USARTx->CR3 |= USART_CR3_RTSE;
	else
		USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_RTSE);
}

void USART_DMAT_Cmd( 		USART_RM *USARTx , int EnableVal ){
	if(EnableVal)
		USARTx->CR3 |= USART_CR3_DMAT;
	else
		USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_DMAT);
}

void USART_DMAR_Cmd( 		USART_RM *USARTx , int EnableVal ){
	if(EnableVal)
		USARTx->CR3 |= USART_CR3_DMAR;
	else
		USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_DMAR)
}

void USART_Smartcard_Cmd( 	USART_RM *USARTx , int EnableVal ){
	if( Is_In_USART_1236(USARTx) != 1 )
		return;
	if(EnableVal)
		USARTx->CR3 |= USART_CR3_SCEN;
	else
		USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_SCEN);
}

void USART_Smartcard_NACK_Cmd( 	USART_RM *USARTx , int EnableVal ){
	if( Is_In_USART_1236(USARTx) != 1 )
		return;
	if(EnableVal)
		USARTx->CR3 |= USART_CR3_NACK;
	else
		USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_NACK);
}

void USART_IrDA_Cmd( 		USART_RM *USARTx , int EnableVal ){
	if(EnableVal)
		USARTx->CR3 |= USART_CR3_IREN;
	else
		USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_IREN);
}

void USART_IT_Cmd( USART_TypeDef* USARTx , uint16_t USART_IT ){
	uint16_t CRnth=((uint16_t)0x0000),Shiftnum=((uint16_t)0x0000);
	// 看在第幾個暫存器
	CRnth 		= (USART_IT >> 4);
	// 看要位移幾個 Bit 才會到對的位置
	// EX：	USART_CR1_PEIE		0x0100
	// 	USART_IT_PE		((uint16_t)0x0018)
	// =>	1			8
	//	即為在 第1個 暫存器	1 要向左位移 8個 BIt
	Shiftnum	= (USART_IT & ((uint16_t)0x000F));
	if(CRnth == ((uint16_t)0x0001)){
		USARTx->CR1 |= (1 << Shiftnum);
	}
	else if(CRnth == ((uint16_t)0x0002)){
		USARTx->CR2 |= (1 << Shiftnum);
	}
	else if(CRnth == ((uint16_t)0x0003)){
		USARTx->CR3 |= (1 << Shiftnum);
	}
}

void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime){
	if( Is_In_USART_1236(USARTx) != 1 )
		return;
	/* Clear the USART Guard time */
  	USARTx->GTPR &= USART_GTPR_PSC;
  	/* Set the USART guard time */
 	USARTx->GTPR |= (uint16_t)((uint16_t)USART_GuardTime << 0x08);
}
