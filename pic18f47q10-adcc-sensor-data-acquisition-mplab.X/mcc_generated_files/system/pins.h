/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.1
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 aliases
#define BLE_CONNECTION_TRIS                 TRISAbits.TRISA0
#define BLE_CONNECTION_LAT                  LATAbits.LATA0
#define BLE_CONNECTION_PORT                 PORTAbits.RA0
#define BLE_CONNECTION_WPU                  WPUAbits.WPUA0
#define BLE_CONNECTION_OD                   ODCONAbits.ODCA0
#define BLE_CONNECTION_ANS                  ANSELAbits.ANSELA0
#define BLE_CONNECTION_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define BLE_CONNECTION_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define BLE_CONNECTION_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define BLE_CONNECTION_GetValue()           PORTAbits.RA0
#define BLE_CONNECTION_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define BLE_CONNECTION_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define BLE_CONNECTION_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define BLE_CONNECTION_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define BLE_CONNECTION_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define BLE_CONNECTION_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define BLE_CONNECTION_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define BLE_CONNECTION_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set RA2 aliases
#define SENSOR_CLICK_AN_TRIS                 TRISAbits.TRISA2
#define SENSOR_CLICK_AN_LAT                  LATAbits.LATA2
#define SENSOR_CLICK_AN_PORT                 PORTAbits.RA2
#define SENSOR_CLICK_AN_WPU                  WPUAbits.WPUA2
#define SENSOR_CLICK_AN_OD                   ODCONAbits.ODCA2
#define SENSOR_CLICK_AN_ANS                  ANSELAbits.ANSELA2
#define SENSOR_CLICK_AN_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define SENSOR_CLICK_AN_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define SENSOR_CLICK_AN_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define SENSOR_CLICK_AN_GetValue()           PORTAbits.RA2
#define SENSOR_CLICK_AN_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define SENSOR_CLICK_AN_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define SENSOR_CLICK_AN_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define SENSOR_CLICK_AN_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define SENSOR_CLICK_AN_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define SENSOR_CLICK_AN_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define SENSOR_CLICK_AN_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define SENSOR_CLICK_AN_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set RA3 aliases
#define BLE_CMD_TRIS                 TRISAbits.TRISA3
#define BLE_CMD_LAT                  LATAbits.LATA3
#define BLE_CMD_PORT                 PORTAbits.RA3
#define BLE_CMD_WPU                  WPUAbits.WPUA3
#define BLE_CMD_OD                   ODCONAbits.ODCA3
#define BLE_CMD_ANS                  ANSELAbits.ANSELA3
#define BLE_CMD_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define BLE_CMD_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define BLE_CMD_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define BLE_CMD_GetValue()           PORTAbits.RA3
#define BLE_CMD_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define BLE_CMD_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define BLE_CMD_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define BLE_CMD_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define BLE_CMD_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define BLE_CMD_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define BLE_CMD_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define BLE_CMD_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set RA7 aliases
#define BLE_WAKE_TRIS                 TRISAbits.TRISA7
#define BLE_WAKE_LAT                  LATAbits.LATA7
#define BLE_WAKE_PORT                 PORTAbits.RA7
#define BLE_WAKE_WPU                  WPUAbits.WPUA7
#define BLE_WAKE_OD                   ODCONAbits.ODCA7
#define BLE_WAKE_ANS                  ANSELAbits.ANSELA7
#define BLE_WAKE_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define BLE_WAKE_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define BLE_WAKE_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define BLE_WAKE_GetValue()           PORTAbits.RA7
#define BLE_WAKE_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define BLE_WAKE_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define BLE_WAKE_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define BLE_WAKE_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define BLE_WAKE_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define BLE_WAKE_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define BLE_WAKE_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define BLE_WAKE_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set RC2 aliases
#define IO_RC2_TRIS                 TRISCbits.TRISC2
#define IO_RC2_LAT                  LATCbits.LATC2
#define IO_RC2_PORT                 PORTCbits.RC2
#define IO_RC2_WPU                  WPUCbits.WPUC2
#define IO_RC2_OD                   ODCONCbits.ODCC2
#define IO_RC2_ANS                  ANSELCbits.ANSELC2
#define IO_RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define IO_RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define IO_RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define IO_RC2_GetValue()           PORTCbits.RC2
#define IO_RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define IO_RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define IO_RC2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define IO_RC2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define IO_RC2_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define IO_RC2_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define IO_RC2_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define IO_RC2_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 aliases
#define IO_RC3_TRIS                 TRISCbits.TRISC3
#define IO_RC3_LAT                  LATCbits.LATC3
#define IO_RC3_PORT                 PORTCbits.RC3
#define IO_RC3_WPU                  WPUCbits.WPUC3
#define IO_RC3_OD                   ODCONCbits.ODCC3
#define IO_RC3_ANS                  ANSELCbits.ANSELC3
#define IO_RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_RC3_GetValue()           PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_RC3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define IO_RC3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define IO_RC3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define IO_RC3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define IO_RC3_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RD5 aliases
#define SENSOR_ENABLE_TRIS                 TRISDbits.TRISD5
#define SENSOR_ENABLE_LAT                  LATDbits.LATD5
#define SENSOR_ENABLE_PORT                 PORTDbits.RD5
#define SENSOR_ENABLE_WPU                  WPUDbits.WPUD5
#define SENSOR_ENABLE_OD                   ODCONDbits.ODCD5
#define SENSOR_ENABLE_ANS                  ANSELDbits.ANSELD5
#define SENSOR_ENABLE_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define SENSOR_ENABLE_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define SENSOR_ENABLE_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define SENSOR_ENABLE_GetValue()           PORTDbits.RD5
#define SENSOR_ENABLE_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define SENSOR_ENABLE_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define SENSOR_ENABLE_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define SENSOR_ENABLE_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define SENSOR_ENABLE_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define SENSOR_ENABLE_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define SENSOR_ENABLE_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define SENSOR_ENABLE_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/