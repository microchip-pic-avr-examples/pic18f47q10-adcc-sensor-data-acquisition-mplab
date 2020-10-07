/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#ifdef	__cplusplus
extern "C" {
#endif

// include files
#include "main.h"
#include <string.h>
#include <stdlib.h>

#include "mcc_generated_files/BLE2_driver.h"
#include "mcc_generated_files/drivers/uart.h"
    
// definitions     
#define CHECKSUM_HIGHBYTE           0
#define CHECKSUM_LOWBYTE            1
#define ADDRESS_POINTER_HIGHBYTE    2
#define ADDRESS_POINTER_LOWBYTE     3  
#define IS_MEMORY_ERASED            4
    
#define START_ADDR 0x4000
#define STOP_ADDR  0x41FF
#define XOR_VALUE  0x0000
    
#define ADC_STATE       1
#define ADC_MODE        2
#define ADC_INTERVAL    3
    
#define ADC_REAL_DATA  1
#define ADC_LOG_DATA   2
    
#define ADC_BURST_MODE 1 
#define ADC_BASIC_MODE 2   
    
#define INTERVAL_01  1
#define INTERVAL_02  2
#define INTERVAL_04  3
#define INTERVAL_08  4    
#define INTERVAL_16  5
    
#define TIMER1_01s   0xF0DD
#define TIMER1_02s   0xE1BA
#define TIMER1_04s   0xC374
#define TIMER1_08s   0x86E8
#define TIMER1_16s   0x0DD0
    
#define ADC_POT_PIN     0x0
#define ADC_CLICK_1_PIN 0x1
#define ADC_CLICK_2_PIN 0x2
   
#define READ_ERROR  2000
#define WRITE_ERROR 3000
#define CRC_ERROR   4000
    
#define MAX_ADC_VALUE   676
    
// global variables
volatile bool connection_status;
volatile bool adcReadyFlag;
volatile bool burstMode;
volatile bool isCRCPeekEnabled;
volatile bool tmr0InterruptFlag;
volatile uint8_t flashCrcErrorStatus;
volatile uint16_t crcValPeek;
volatile uint16_t crcValBurst;
volatile uint16_t currentAdcValuePtr;
extern volatile uint16_t timer1ReloadVal;

typedef struct {
    uint8_t ADC_CHARACTERISTIC;
    uint8_t ADC_VALUE;
} ADC_data;

/**
   @Param
    ASCII character
   @Returns
    hex value of character
   @Description
    returns the hex value of the character
   @Example
    ch = getHexValue('A');
 */
uint8_t getHexValue(char);

/**
   @Param
    none
   @Returns
    8 bit ADCCharacteristic
   @Description
    get the command type
   @Example
    data.ADC_CHARACTERISTIC = getADCCharacteristic();
 */
uint8_t getADCCharacteristic(void);

/**
   @Param
    none
   @Returns
    8 bit ADCMode
   @Description
    get the ADC mode type
   @Example
    data.ADC_VALUE = getADCMode();
 */
uint8_t getADCMode(void);

/**
   @Param
    none
   @Returns
    8 bit ADCCommand
   @Description
    get the ADC command
   @Example
    ADC_data data = getADCCommand(); 
 */
ADC_data getADCCommand(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    process ADC command
   @Example
    processADCCommand();
 */
void processADCCommand(void);

/**
   @Param
    adc value
   @Returns
    none
   @Description
    store the data in PFM
   @Example
    LogDataToPFM(adcValue);
 */
void LogDataToPFM(uint16_t adcValue);

/**
   @Param
    flash address and data
   @Returns
    none
   @Description
    stores 1 word to the PFM
   @Example
    FLASHWriteWordSingle(currentAdcValuePtr,adcValue);
 */
void FLASHWriteWordSingle(uint32_t flashAddr, uint16_t word);

/**
   @Param
    adc value
   @Returns
    none
   @Description
    send the ADC value to BLE
   @Example
    sendADCCValueBLE(adcValue);
 */
void sendADCCValueBLE(uint16_t adcValue);

/**
   @Param
    none
   @Returns
    none
   @Description
    initialize ADC in BURST mode
   @Example
    ADCCBurstModeInitialize();
 */
void ADCCBurstModeInitialize (void);

/**
   @Param
    none
   @Returns
    none
   @Description
    initialize ADC in BASIC mode
   @Example
    ADCCBasicModeInitialize();
 */
void ADCCBasicModeInitialize(void);

/**
   @Param
    ADC pin number
   @Returns
    none
   @Description
    set the desired ADC pin for sensing
   @Example
    ADCCSetSensorPin(ADC_CLICK_2_PIN);
 */
void ADCCSetSensorPin(uint8_t adcPin);

/**
   @Param
    none
   @Returns
    none
   @Description
    initialize CRC in PEEK mode
   @Example
    CRCInitializePeekMode();
 */
void CRCInitializePeekMode(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    initialize CRC in BURST mode
   @Example
    CRCInitializeBurstMode();
 */
void CRCInitializeBurstMode(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    start CRC in PEEK mode
   @Example
    StartCRCPeekMode();
 */
void StartCRCPeekMode(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    start CRC in BURST mode
   @Example
    CRCBurstMode();
 */
void CRCBurstMode(void);

/**
   @Param
    16 bit checksum
   @Returns
    none
   @Description
    write the checksum value to EEPROM
   @Example
    writeChecksum(checksum);
 */
void writeChecksum(uint16_t checksum);

/**
   @Param
    none
   @Returns
    16 bit checksum
   @Description
    read the checksum value from EEPROM
   @Example
    checksum = readChecksum();
 */
uint16_t readChecksum(void);


/**
   @Param
    16 bit pointer representing the current data address
   @Returns
    none
   @Description
    write the data address pointer to EEPROM
   @Example
    writeDataPtr(dataPtr);
 */
void writeDataPtr(uint16_t checksum);

/**
   @Param
    none
   @Returns
    16 bit pointer representing the current data address
   @Description
    read the data address pointer from EEPROM
   @Example
    dataPtr = readDataPtr();
 */
uint16_t readDataPtr(void);

/**
   @Param
    none
   @Returns
   none
   @Description
     Timer interrupt handler function , 
 */
void TMR0_UserInterruptHandler(void);

/**
   @Param
    none
   @Returns
   none
   @Description
   ADC interrupt handler function , 
 */
void ADCC_UserInterruptHandler(void);


#ifdef	__cplusplus
}
#endif

#endif	/* APPLICATION_H */

