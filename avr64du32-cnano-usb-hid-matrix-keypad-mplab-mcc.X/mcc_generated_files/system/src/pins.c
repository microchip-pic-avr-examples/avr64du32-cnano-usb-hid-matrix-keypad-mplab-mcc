/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 1.1.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../pins.h"

static void (*VBUS_InterruptHandler)(void);
static void (*ROW0_InterruptHandler)(void);
static void (*ROW1_InterruptHandler)(void);
static void (*ROW2_InterruptHandler)(void);
static void (*ROW3_InterruptHandler)(void);
static void (*COL0_InterruptHandler)(void);
static void (*COL1_InterruptHandler)(void);
static void (*COL2_InterruptHandler)(void);
static void (*LED0_InterruptHandler)(void);

void PIN_MANAGER_Initialize()
{

  /* OUT Registers Initialization */
    PORTA.OUT = 0x7F;
    PORTC.OUT = 0x0;
    PORTD.OUT = 0x0;
    PORTF.OUT = 0x4;

  /* DIR Registers Initialization */
    PORTA.DIR = 0x70;
    PORTC.DIR = 0x0;
    PORTD.DIR = 0x0;
    PORTF.DIR = 0x4;

  /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0xB;
    PORTA.PIN1CTRL = 0xB;
    PORTA.PIN2CTRL = 0xB;
    PORTA.PIN3CTRL = 0xB;
    PORTA.PIN4CTRL = 0x8;
    PORTA.PIN5CTRL = 0x8;
    PORTA.PIN6CTRL = 0x8;
    PORTA.PIN7CTRL = 0x0;
    PORTC.PIN0CTRL = 0x0;
    PORTC.PIN1CTRL = 0x0;
    PORTC.PIN2CTRL = 0x0;
    PORTC.PIN3CTRL = 0x4;
    PORTC.PIN4CTRL = 0x0;
    PORTC.PIN5CTRL = 0x0;
    PORTC.PIN6CTRL = 0x0;
    PORTC.PIN7CTRL = 0x0;
    PORTD.PIN0CTRL = 0x0;
    PORTD.PIN1CTRL = 0x0;
    PORTD.PIN2CTRL = 0x0;
    PORTD.PIN3CTRL = 0x0;
    PORTD.PIN4CTRL = 0x0;
    PORTD.PIN5CTRL = 0x0;
    PORTD.PIN6CTRL = 0x0;
    PORTD.PIN7CTRL = 0x0;
    PORTF.PIN0CTRL = 0x0;
    PORTF.PIN1CTRL = 0x0;
    PORTF.PIN2CTRL = 0x0;
    PORTF.PIN3CTRL = 0x0;
    PORTF.PIN4CTRL = 0x0;
    PORTF.PIN5CTRL = 0x0;
    PORTF.PIN6CTRL = 0x0;
    PORTF.PIN7CTRL = 0x0;

  /* PORTMUX Initialization */
    PORTMUX.CCLROUTEA = 0x0;
    PORTMUX.EVSYSROUTEA = 0x0;
    PORTMUX.SPIROUTEA = 0x0;
    PORTMUX.TCAROUTEA = 0x0;
    PORTMUX.TCBROUTEA = 0x0;
    PORTMUX.TWIROUTEA = 0x0;
    PORTMUX.USARTROUTEA = 0x0;

  // register default ISC callback functions at runtime; use these methods to register a custom function
    VBUS_SetInterruptHandler(VBUS_DefaultInterruptHandler);
    ROW0_SetInterruptHandler(ROW0_DefaultInterruptHandler);
    ROW1_SetInterruptHandler(ROW1_DefaultInterruptHandler);
    ROW2_SetInterruptHandler(ROW2_DefaultInterruptHandler);
    ROW3_SetInterruptHandler(ROW3_DefaultInterruptHandler);
    COL0_SetInterruptHandler(COL0_DefaultInterruptHandler);
    COL1_SetInterruptHandler(COL1_DefaultInterruptHandler);
    COL2_SetInterruptHandler(COL2_DefaultInterruptHandler);
    LED0_SetInterruptHandler(LED0_DefaultInterruptHandler);
}

/**
  Allows selecting an interrupt handler for VBUS at application runtime
*/
void VBUS_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    VBUS_InterruptHandler = interruptHandler;
}

void VBUS_DefaultInterruptHandler(void)
{
    // add your VBUS interrupt custom code
    // or set custom function using VBUS_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for ROW0 at application runtime
*/
void ROW0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    ROW0_InterruptHandler = interruptHandler;
}

void ROW0_DefaultInterruptHandler(void)
{
    // add your ROW0 interrupt custom code
    // or set custom function using ROW0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for ROW1 at application runtime
*/
void ROW1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    ROW1_InterruptHandler = interruptHandler;
}

void ROW1_DefaultInterruptHandler(void)
{
    // add your ROW1 interrupt custom code
    // or set custom function using ROW1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for ROW2 at application runtime
*/
void ROW2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    ROW2_InterruptHandler = interruptHandler;
}

void ROW2_DefaultInterruptHandler(void)
{
    // add your ROW2 interrupt custom code
    // or set custom function using ROW2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for ROW3 at application runtime
*/
void ROW3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    ROW3_InterruptHandler = interruptHandler;
}

void ROW3_DefaultInterruptHandler(void)
{
    // add your ROW3 interrupt custom code
    // or set custom function using ROW3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for COL0 at application runtime
*/
void COL0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    COL0_InterruptHandler = interruptHandler;
}

void COL0_DefaultInterruptHandler(void)
{
    // add your COL0 interrupt custom code
    // or set custom function using COL0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for COL1 at application runtime
*/
void COL1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    COL1_InterruptHandler = interruptHandler;
}

void COL1_DefaultInterruptHandler(void)
{
    // add your COL1 interrupt custom code
    // or set custom function using COL1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for COL2 at application runtime
*/
void COL2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    COL2_InterruptHandler = interruptHandler;
}

void COL2_DefaultInterruptHandler(void)
{
    // add your COL2 interrupt custom code
    // or set custom function using COL2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for LED0 at application runtime
*/
void LED0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    LED0_InterruptHandler = interruptHandler;
}

void LED0_DefaultInterruptHandler(void)
{
    // add your LED0 interrupt custom code
    // or set custom function using LED0_SetInterruptHandler()
}
ISR(PORTA_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTA.INTFLAGS & PORT_INT0_bm)
    {
       ROW0_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT1_bm)
    {
       ROW1_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT2_bm)
    {
       ROW2_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT3_bm)
    {
       ROW3_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT4_bm)
    {
       COL0_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT5_bm)
    {
       COL1_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT6_bm)
    {
       COL2_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

ISR(PORTC_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTC.INTFLAGS & PORT_INT3_bm)
    {
       VBUS_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

ISR(PORTD_PORT_vect)
{ 
    /* Clear interrupt flags */
    VPORTD.INTFLAGS = 0xff;
}

ISR(PORTF_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTF.INTFLAGS & PORT_INT2_bm)
    {
       LED0_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

/**
 End of File
*/