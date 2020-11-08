
#define EVB

#ifdef EVB
	#define PCC_CLOCK	PCC_PORTE_CLOCK
	#define LED0_PORT PTE
	#define LED0_PIN  21
	#define LED1_PORT PTE
	#define LED1_PIN  22
#else
	#define PCC_CLOCK	PCC_PORTC_CLOCK
	#define LED0_PORT PTC
	#define LED0_PIN  0
	#define LED1_PORT PTC
	#define LED1_PIN  1
#endif



#include "S32K148.h" /* include peripheral declarations S32K148 */
#include "clocks_and_modes.h"
#include "LPUART.h"
#include <string.h>
#include <stdio.h>
char data=0;
void PORT_init (void) {
PCC->PCCn[PCC_PORTC_INDEX ]|=PCC_PCCn_CGC_MASK; /* Enable clock for PORTC */
PORTC->PCR[6]|=PORT_PCR_MUX(2); /* Port C6: MUX = ALT2,UART1 TX */
PORTC->PCR[7]|=PORT_PCR_MUX(2); /* Port C7: MUX = ALT2,UART1 RX */
}
void WDOG_disable (void){
WDOG->CNT=0xD928C520; /* Unlock watchdog */
WDOG->TOVAL=0x0000FFFF; /* Maximum timeout value */
WDOG->CS = 0x00002100; /* Disable watchdog */
}



int main(void)
{
  /* Write your local variable definition here */
	status_t error;
	  /* Configure clocks for PORT */
	  error = CLOCK_DRV_Init(&clockMan1_InitConfig0);
	  DEV_ASSERT(error == STATUS_SUCCESS);
	  /* Set pins as GPIO */
	  error = PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
	  DEV_ASSERT(error == STATUS_SUCCESS);
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/
WDOG_disable(); /* Disable WDGO*/
SOSC_init_8MHz(); /* Initialize system oscillator for 8 MHz xtal */
SPLL_init_160MHz(); /* Initialize SPLL to 160 MHz with 8 MHz SOSC */
//RUNmode_80MHz(); /* Init clocks: 80 MHz SPLL & core, 40 MHz bus, 20 MHz flash */
NormalRUNmode_80MHz(); /* Init clocks: 80 MHz SPLL & core, 40 MHz bus, 20 MHz flash */
PORT_init(); /* Configure ports */
LPUART1_init(); /* Initialize LPUART @ 9600*/
LPUART1_transmit_string("Running LPUART\n\r"); /* Transmit char string */
LPUART1_transmit_string("Tx_Rx_Bluetooth\n\r"); /* Transmit char string */
LPUART1_transmit_string("Press r for Red LED \n\r Press g for Green LED \n\r");

for(;;) {
//		void usartTextIn (char* str, int length);

LPUART1_transmit_char('>'); /* Transmit prompt character*/

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   char str1[20];  // declaration of char array
//   char str2[20] = "on red led";  // declaration of char array
//   char str3[20] = "on green led";  // declaration of char array
//   int value; // declaration of integer variable

//   scanf("%s",str1);

   // comparing both the strings using strcmp() function
//   if(value==strcmp(str1,str2) && value==0)
//   	   {
//	   printf("Red LED is on");
//   	   }
//   else if (value==strcmp(str1,str3) && value==0)
//         {
//          printf("Green LED is on");
//         }
//   else
//   	   {
//	   printf("Invalid input");
//   	   }

   //return 0;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


LPUART1_receive_and_echo_char();/* Wait for input char, receive & echo it*/







}
}
