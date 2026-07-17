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
#include "stdbool.h" 
#include <stdio.h>
#include "ble2driver.h"
#include "ble2click.h"
#include "mcc_generated_files/system/system.h"
    
// definitions     
#define CHECKSUM_HIGHBYTE_ADDR               0  // EEPROM address of Checksum High byte
#define CHECKSUM_LOWBYTE_ADDR                1  // EEPROM address of Checksum Low byte 
#define CHECKSUM_POINTER_HIGHBYTE_ADDR       2  // EEPROM address of Checksum Pointer High byte
#define CHECKSUM_POINTER_LOWBYTE_ADDR        3  // EEPROM address of Checksum Pointer Low byte 
#define IS_MEMORY_ERASED_ADDR                4  // EEPROM address to check if memory is erased
    
#define SCAN_START_ADDR 0x1FE00                 //  Flash address to begin scan of the data
#define SCAN_STOP_ADDR  0x1FFFF                 //  Flash address to stop the scan of the data
#define CRC_FINAL_XOR_VALUE  0x0000
    
#define DATA_STATE          1
#define ADC_MODE            2
#define SENSING_INTERVAL    3
    
#define REALTIME_DATA  1
#define LOG_DATA       2
    
#define ADC_BURST_MODE 1 
#define ADC_BASIC_MODE 2   
    
#define SENSING_INTERVAL_01  1U
#define SENSING_INTERVAL_02  2U
#define SENSING_INTERVAL_04  3U
#define SENSING_INTERVAL_08  4U   
#define SENSING_INTERVAL_16  5U
    
    
//crc timer clock     
#define TIMER1_01s   0xF0DD
#define TIMER1_02s   0xE1BA
#define TIMER1_04s   0xC374
#define TIMER1_08s   0x86E8
#define TIMER1_16s   0x0DD0
   
#define READ_ERROR_DATA  2000
#define WRITE_ERROR_DATA 3000
#define CRC_ERROR_DATA   4000
#define NO_ERROR         0000    
    
#define MAX_ADC_VALUE   1015

#define  NORMAL_CRC  0
#define  REVERSE_CRC 1
    
#define READ_ERROR_STATUS_CODE  1
#define WRITE_ERROR_STATUS_CODE 3
#define CRC_ERROR_STATUS_CODE   5
    

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
    returns the hex value of the character. 
   eg: if x = '2', returns 0x02 
 *     if x = 'C', returns 0x0c
   @Example
    ch = HexValueGet('A');
 */
uint8_t HexValueGet(char);

/**
   @Param
    none
   @Returns
    8 bit ADCharacteristic
   @Description
    get the command type
   @Example
    data.ADC_CHARACTERISTIC = ADCharacteristicGet();
 */
uint8_t ADCCharacteristicGet(void);

/**
   @Param
    none
   @Returns
    8 bit ADCMode
   @Description
    get the ADC mode type
   @Example
    data.ADC_VALUE = ADCModeGet();
 */
uint8_t ADCModeGet(void);

/**
   @Param
    none
   @Returns
    8 bit ADCommand
   @Description
    get the ADC command
   @Example
    ADC_data data = ADCommandGet(); 
 */
ADC_data ADCCommandGet(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    process ADC command
   @Example
    ADCommandProcess();
 */
void ADCCommandProcess(void);

/**
   @Param
    adc value
   @Returns
    none
   @Description
    store the data in PFM
   @Example
    FlashDataLog(adcValue);
 */
void FlashDataLog(uint16_t adcValue);

/**
   @Param
    flash address and data
   @Returns
    none
   @Description
    stores 1 word to the PFM
   @Example
    FlashWordWrite(currentAdcValuePtr,adcValue);
 */
void FlashWordWrite(uint24_t flashAddr, uint16_t word);

/**
   @Param
    adc value
   @Returns
    none
   @Description
    send the ADC value to BLE
   @Example
    BLEDataSend(adcValue);
 */
void BLEDataSend(uint16_t adcValue);

/**
   @Param
    none
   @Returns
    none
   @Description
    initialize ADC in BURST mode
   @Example
    ADCBurstModeInitialize();
 */
void ADCBurstModeInitialize (void);

/**
   @Param
    none
   @Returns
    none
   @Description
    initialize ADC in BASIC mode
   @Example
    ADCBasicModeInitialize();
 */
void ADCBasicModeInitialize(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    initialize CRC in PEEK mode
   @Example
    CRCPeekModeInitialize();
 */
void CRCPeekModeInitialize(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    initialize CRC in BURST mode
   @Example
    CRCBurstModeInitialize();
 */
void CRCBurstModeInitialize(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    setup and start CRC, Scanner in PEEK mode
   @Example
    ScannerSetupAndStart();
 */
void ScannerSetupAndStart(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    calculate CRC value in BURST mode
   @Example
    CRCBurstModeCalculate();
 */
void CRCBurstModeCalculate(void);
/**
   @Param
    none
   @Returns
    none
   @Description
    start CRC in PEEK mode
   @Example
    CRCPeriodicStart();
 */
void CRCPeriodicStart(void);
/**
   @Param
    none
   @Returns
    none
   @Description
    stop CRC in PEEK mode
   @Example
    CRCPeriodicStop();
 */
void CRCPeriodicStop(void);
/**
   @Param
    16 bit checksum
   @Returns
    none
   @Description
    write the checksum value to EEPROM
   @Example
    ChecksumWrite(checksum);
 */
void ChecksumWrite(uint16_t checksum);

/**
   @Param
    none
   @Returns
   SCANGO bit value in SCANCON0 register
   @Description
   returns the status of scanner
   @Example
    CRC_IsScannerOngoing();
 */
inline bool CRC_IsScannerOngoing(void);

/**
   @Param
    none
   @Returns
    busy status of the CRC and Scanner 
   @Description
   checks if the calculation of CRC is completed or not.
   @Example
    CRC_IsCalculationComplete();
 */
bool  CRC_IsCalculationComplete(void);
/**
   @Param
    none
   @Returns
    16 bit checksum
   @Description
    read the checksum value from EEPROM
   @Example
    checksum = ChecksumRead();
 */
uint16_t ChecksumRead(void);

/**
   @Param
    16 bit pointer representing the current data address
   @Returns
    none
   @Description
    write the data address pointer to EEPROM
   @Example
    DataPtrWrite(dataPtr);
 */
void DataPtrWrite(uint24_t dataPtr);

/**
   @Param
    none
   @Returns
    16 bit pointer representing the current data address
   @Description
    read the data address pointer from EEPROM
   @Example
    dataPtr = DataPtrRead();
 */
uint16_t DataPtrRead(void);

/**
   @Param
    none
   @Returns
   none
   @Description
    Timer interrupt handler function 
 */
void TMR0_UserInterruptHandler(void);

/**
   @Param
    none
   @Returns
   none
   @Description
   ADC interrupt handler function 
 */
void ADC_UserInterruptHandler(void);


#ifdef	__cplusplus
}
#endif

#endif	/* APPLICATION_H */

