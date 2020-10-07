/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC18F47Q10
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.20 and above
        MPLAB 	          :  MPLAB X 5.40	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set BLE2_Conn aliases
#define BLE2_Conn_TRIS                 TRISAbits.TRISA0
#define BLE2_Conn_LAT                  LATAbits.LATA0
#define BLE2_Conn_PORT                 PORTAbits.RA0
#define BLE2_Conn_WPU                  WPUAbits.WPUA0
#define BLE2_Conn_OD                   ODCONAbits.ODCA0
#define BLE2_Conn_ANS                  ANSELAbits.ANSELA0
#define BLE2_Conn_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define BLE2_Conn_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define BLE2_Conn_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define BLE2_Conn_GetValue()           PORTAbits.RA0
#define BLE2_Conn_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define BLE2_Conn_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define BLE2_Conn_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define BLE2_Conn_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define BLE2_Conn_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define BLE2_Conn_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define BLE2_Conn_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define BLE2_Conn_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set sensor_click aliases
#define sensor_click_TRIS                 TRISAbits.TRISA2
#define sensor_click_LAT                  LATAbits.LATA2
#define sensor_click_PORT                 PORTAbits.RA2
#define sensor_click_WPU                  WPUAbits.WPUA2
#define sensor_click_OD                   ODCONAbits.ODCA2
#define sensor_click_ANS                  ANSELAbits.ANSELA2
#define sensor_click_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define sensor_click_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define sensor_click_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define sensor_click_GetValue()           PORTAbits.RA2
#define sensor_click_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define sensor_click_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define sensor_click_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define sensor_click_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define sensor_click_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define sensor_click_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define sensor_click_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define sensor_click_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set BLE2_Cmd_Mldp aliases
#define BLE2_Cmd_Mldp_TRIS                 TRISAbits.TRISA3
#define BLE2_Cmd_Mldp_LAT                  LATAbits.LATA3
#define BLE2_Cmd_Mldp_PORT                 PORTAbits.RA3
#define BLE2_Cmd_Mldp_WPU                  WPUAbits.WPUA3
#define BLE2_Cmd_Mldp_OD                   ODCONAbits.ODCA3
#define BLE2_Cmd_Mldp_ANS                  ANSELAbits.ANSELA3
#define BLE2_Cmd_Mldp_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define BLE2_Cmd_Mldp_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define BLE2_Cmd_Mldp_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define BLE2_Cmd_Mldp_GetValue()           PORTAbits.RA3
#define BLE2_Cmd_Mldp_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define BLE2_Cmd_Mldp_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define BLE2_Cmd_Mldp_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define BLE2_Cmd_Mldp_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define BLE2_Cmd_Mldp_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define BLE2_Cmd_Mldp_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define BLE2_Cmd_Mldp_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define BLE2_Cmd_Mldp_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set BLE2_Wake aliases
#define BLE2_Wake_TRIS                 TRISAbits.TRISA7
#define BLE2_Wake_LAT                  LATAbits.LATA7
#define BLE2_Wake_PORT                 PORTAbits.RA7
#define BLE2_Wake_WPU                  WPUAbits.WPUA7
#define BLE2_Wake_OD                   ODCONAbits.ODCA7
#define BLE2_Wake_ANS                  ANSELAbits.ANSELA7
#define BLE2_Wake_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define BLE2_Wake_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define BLE2_Wake_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define BLE2_Wake_GetValue()           PORTAbits.RA7
#define BLE2_Wake_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define BLE2_Wake_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define BLE2_Wake_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define BLE2_Wake_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define BLE2_Wake_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define BLE2_Wake_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define BLE2_Wake_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define BLE2_Wake_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()              PORTCbits.RC2
#define RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define RC2_SetPullup()             do { WPUCbits.WPUC2 = 1; } while(0)
#define RC2_ResetPullup()           do { WPUCbits.WPUC2 = 0; } while(0)
#define RC2_SetAnalogMode()         do { ANSELCbits.ANSELC2 = 1; } while(0)
#define RC2_SetDigitalMode()        do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set sensor_enable aliases
#define sensor_enable_TRIS                 TRISDbits.TRISD5
#define sensor_enable_LAT                  LATDbits.LATD5
#define sensor_enable_PORT                 PORTDbits.RD5
#define sensor_enable_WPU                  WPUDbits.WPUD5
#define sensor_enable_OD                   ODCONDbits.ODCD5
#define sensor_enable_ANS                  ANSELDbits.ANSELD5
#define sensor_enable_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define sensor_enable_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define sensor_enable_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define sensor_enable_GetValue()           PORTDbits.RD5
#define sensor_enable_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define sensor_enable_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define sensor_enable_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define sensor_enable_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define sensor_enable_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define sensor_enable_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define sensor_enable_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define sensor_enable_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/