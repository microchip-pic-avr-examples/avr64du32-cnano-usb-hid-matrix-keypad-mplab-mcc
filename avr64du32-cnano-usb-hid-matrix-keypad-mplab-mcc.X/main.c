 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
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
#include "mcc_generated_files/system/system.h"
#include "usb_core.h"
#include <usb_hid_keycodes.h>
#include "usb_hid_keyboard.h"

#define CONSECUTIVE_EQUAL_PIT_INTERRUPTS 5
#define KEY_PRESSES_PER_SECOND 5
#define KEY_PRESS_TIME_INTERVAL_MS 1000/KEY_PRESSES_PER_SECOND
#define NUM_COLUMNS 3
#define NUM_ROWS 4

// Button debounce variables
uint64_t milliSeconds = 0;
uint64_t lastInterruptTime[NUM_ROWS] = {0};

// USB connection handlers
void CheckUSBConnection(void);
void HandleUSBConnection(void);

// USB connection variables
RETURN_CODE_t status;
uint8_t prevVbusState = 0;
volatile uint8_t vbusFlag = false;

// USB SOF callback functions, called every 1 ms
void USB_IterateColumns(void);
void USB_KeyPressHandler(uint8_t currentColumn);

// Row Interrupt Service Routines
void ROW0_InterruptHandler(void);
void ROW1_InterruptHandler(void);
void ROW2_InterruptHandler(void);
void ROW3_InterruptHandler(void);

// HID Keypad Message IDs
uint8_t keypad[] = {
    HID_1, HID_2, HID_3, 
    HID_4, HID_5, HID_6, 
    HID_7, HID_8, HID_9, 
    HID_KEYPAD_ASTERISK, HID_0, HID_3,
};
        
// Flags to keep track of key presses
volatile bool keyPressFlag = false;
volatile bool rowFlags[NUM_ROWS] = {false};

int main(void)
{
    USBDevice_StartOfFrameCallbackRegister(USB_IterateColumns); // Called every 1 ms
    SYSTEM_Initialize();
    RTC_SetPITIsrCallback(CheckUSBConnection);
    
    //Defines interrupt callback functions
    ROW0_SetInterruptHandler(ROW0_InterruptHandler);
    ROW1_SetInterruptHandler(ROW1_InterruptHandler);
    ROW2_SetInterruptHandler(ROW2_InterruptHandler);
    ROW3_SetInterruptHandler(ROW3_InterruptHandler);

    while(1)
    {
        HandleUSBConnection();
    }    
}

void USB_IterateColumns(void)   // Iterates columns to measure key presses at every Start of Frame
{
    static volatile uint8_t activeColumn = 0;
    // Increase de-bounce counter
    milliSeconds++;
    // Handle key presses in the activeColumn
    USB_KeyPressHandler(activeColumn);
    // Next column
    activeColumn = (activeColumn+1)%NUM_COLUMNS; 
    
    cli();  // Deactivate interrupts
    switch(activeColumn) {
        case 0:
            // Measure button presses on Column 0
            COL1_SetHigh();
            COL2_SetHigh();

            COL0_SetLow();
            break;
        case 1:
            // Measure button presses on Column 1
            COL0_SetHigh();
            COL2_SetHigh();

            COL1_SetLow();
            break;
        case 2:
            // Measure button presses on Column 2            
            COL0_SetHigh();
            COL1_SetHigh();

            COL2_SetLow();
            break;
        default:
            break;
    }
    sei();  // Activate interrupts

    return;
}

void USB_KeyPressHandler(uint8_t currentColumn) // Handles key presses
{
    static volatile bool keyDownFlag = true;
    static volatile uint8_t keypadIndex = -1;
    static volatile bool modifierFlag = false;
    // Detects any key presses
    if (keyPressFlag)
    {
        cli(); // Deactivate interrupts
        // Checks if we need the key press down event
        if (keyDownFlag)
        {
            if (modifierFlag == false)
            {
                // Finds the message_index corresponding to the pressed key
                for (uint8_t currentRow = 0; currentRow < NUM_ROWS; currentRow++) {
                    if (rowFlags[currentRow]) {
                        keypadIndex = currentColumn + currentRow*NUM_COLUMNS;
                        rowFlags[currentRow] = false;
                        break;
                    }
                }
            }
           
            if (SUCCESS == status)
            {
                // Used to make exclamation mark at the end of the message
                if ((keypadIndex == 11) && (modifierFlag == false))
                {
                    status = USB_HIDKeyModifierDown(HID_MODIFIER_LEFT_SHIFT);
                    modifierFlag = true;
                }
                else
                {
                    // Sends the keypress down event
                    status = USB_HIDKeyPressDown(keypad[keypadIndex]);
                    keyDownFlag = false;
                    modifierFlag = false;
                }
            }
        }
        else
        {
            if (SUCCESS == status)
            {
                // Sends the keypress up event
                status = USB_HIDKeyPressUp(keypad[keypadIndex]);
                
                // Releases the shift key modifier if enabled
                USB_HIDKeyModifierUp(HID_MODIFIER_LEFT_SHIFT);

                // Resets flags
                keyDownFlag = true;
                keyPressFlag = false;
            }
        }
        sei(); // Activate interrupts

    }
}

void ROW0_InterruptHandler(void) {
    uint64_t currentTime = milliSeconds;
    // Checks if there has been enough time between two equal key presses, to avoid bouncing and fast spamming
    if (currentTime - lastInterruptTime[0] >= KEY_PRESS_TIME_INTERVAL_MS)
    {
        lastInterruptTime[0] = currentTime;
        keyPressFlag = true;
        rowFlags[0] = true;
    }
    return;
}
void ROW1_InterruptHandler(void) {
    uint64_t currentTime = milliSeconds;
    // Checks if there has been enough time between two equal key presses, to avoid bouncing and fast spamming
    if (currentTime - lastInterruptTime[1] >= KEY_PRESS_TIME_INTERVAL_MS)
    {
        lastInterruptTime[1] = currentTime;
        keyPressFlag = true;
        rowFlags[1] = true;
    }
    return;
}
void ROW2_InterruptHandler(void) {
    uint64_t currentTime = milliSeconds;
    // Checks if there has been enough time between two equal key presses, to avoid bouncing and fast spamming
    if (currentTime - lastInterruptTime[2] >= KEY_PRESS_TIME_INTERVAL_MS)
    {
        lastInterruptTime[2] = currentTime;
        keyPressFlag = true;
        rowFlags[2] = true;

    }
    return;
}
void ROW3_InterruptHandler(void) {
    uint64_t currentTime = milliSeconds;
    // Checks if there has been enough time between two equal key presses, to avoid bouncing and fast spamming
    if (currentTime - lastInterruptTime[3] >= KEY_PRESS_TIME_INTERVAL_MS)
    {
        lastInterruptTime[3] = currentTime;
        keyPressFlag = true;
        rowFlags[3] = true;
    }
    return;
}

void HandleUSBConnection(void) {
    // Check if VBUS was true last check, indicating that USB was connected
    if (prevVbusState == true)
    {
        // Handle USB Transfers
        status = USBDevice_Handle();
    }
    // Get current status of VBUS
    uint8_t currentVbusState = vbusFlag;
    // If changes to USB VBUS state
    if (currentVbusState != prevVbusState)
    {
        // If USB has been connected
        if (currentVbusState == true)
        {
            // Start USB operations
            status = USB_Start();
        }
        else
        {
            //Stop USB operations
            status = USB_Stop();
        }
        //Save state
        prevVbusState = currentVbusState;
    }
    // If USB error detected, blink LED indicating fault
    if (SUCCESS != status)
    {
        LED0_Toggle();
    }
}
void CheckUSBConnection(void) {
    // Helper variables for PIT and AC
    static volatile uint8_t PIT_Counter = 0;
    static volatile uint8_t AC_prevState = 0;

    uint8_t AC_currentState = AC0_Read(); // Saves the current state of the AC status register ('1' means above threshold)

    // Makes sure that the AC state has been the same for a certain number of PIT interrupts
    if (PIT_Counter == CONSECUTIVE_EQUAL_PIT_INTERRUPTS)
    {
        if (AC_currentState) // When CMPSTATE is high, the AC output is high which means the VBUS is above the threshold and the pull-up on data+ should be enabled.
        {
            vbusFlag = true;
        }
        else
        {
            vbusFlag = false;
        }
        PIT_Counter++; // Increment the counter to not run start/stop multiple times without an actual state change
    }
    // Increments a counter if the AC has been in the same state for a certain number of PIT interrupts
    else if (AC_currentState == AC_prevState)
    {
        if (PIT_Counter <= CONSECUTIVE_EQUAL_PIT_INTERRUPTS + 1)
        {
            PIT_Counter++;
        }
        else
        {
            ; // Stops counting if the AC has been in the same state for a while.
        }
    }
    else
    {
        PIT_Counter = 0; // Resets the PIT counter if a state change has occurred.
    }
    AC_prevState = AC_currentState;
}

