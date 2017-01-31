/* Ross Baehr
   R@M 2017
   ross.baehr@gmail.com
*/

#include "include/configure.h"

void configureUART(void)
{
  // UART0:
  //
  // Enable the GPIO Peripheral used by the UART.
  //
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  //
  // Enable UART0
  //
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

  //
  // Configure GPIO Pins for UART mode.
  //
  ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
  ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
  ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  //
  // Use the internal 16MHz oscillator as the UART clock source.
  //
  ROM_UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

  // Disable the sending interrupt
  ROM_UARTIntDisable(UART0_BASE,UART_INT_TX);
  // Enable UART1 receive and receive timeout
  ROM_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);


  // -----------------------------------------------------------
  // UART1:

  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

  //
  // Enable port PC4 for UART1 U1RX
  //
  ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4);
  ROM_GPIOPinConfigure(GPIO_PC4_U1RX);

  //
  // Enable port PC5 for UART1 U1TX
  //
  ROM_GPIOPinConfigure(GPIO_PC5_U1TX);
  ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_5);

  //
  // Use the internal 16MHz oscillator as the UART clock source.
  //
  ROM_UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);

  // Disable the sending interrupt
  ROM_UARTIntDisable(UART1_BASE,UART_INT_TX);
  // Enable UART1 receive and receive timeout
  ROM_UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);

  #ifdef DEBUG
  //
  // Initialize the UART for console I/O.
  //
  UARTStdioConfig(0, 115200, 16000000);
  #endif
}

void configureGPIO(void) {

  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

  //
  // Configure the GPIO port for the LED operation.
  //
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

}

void configureI2C(void) {
  //
  // Enable the peripherals used by this example.
  //
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);


  //
  // Configure the pin muxing for I2C0 functions on port B2 and B3.
  // This step is not necessary if your part does not support pin muxing.
  // TODO: change this to select the port/pin you are using.
  //
  ROM_GPIOPinConfigure(GPIO_PB2_I2C0SCL);
  ROM_GPIOPinConfigure(GPIO_PB3_I2C0SDA);

  // Select the I2C function for these pins.
  ROM_GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
  ROM_GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);


  //
  // Initialize the I2C master.
  //
  ROM_I2CMasterInitExpClk(I2C0_BASE, ROM_SysCtlClockGet(), false);

  //
  // Enable the I2C interrupt.
  //
  ROM_IntEnable(INT_I2C0);

  //
  // Enable the I2C master interrupt.
  //
  ROM_I2CMasterIntEnable(I2C0_BASE);
}
