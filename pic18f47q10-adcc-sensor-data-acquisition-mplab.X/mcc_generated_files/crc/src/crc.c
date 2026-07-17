/**
 * CRC Generated Driver File.
 * 
 * @file crc.c
 * 
 * @ingroup  crc
 * 
 * @brief This file contains the API implementation for the CRC driver.
 *
 * @version CRC Driver Version 1.0.1
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "../crc.h"



void CRC_Initialize(void)
{
    //CRC Configurations
    //CRCDLEN 7; CRCPLEN 15; 
    CRCCON1 = 0x7F;

    //CRCXORH 128; 
    CRCXORH = 0x80;
    //CRCXORL 5; 
    CRCXORL = 0x5;

    //CRCACCH 0; 
    CRCACCH = 0x0;
    //CRCACCL 0; 
    CRCACCL = 0x0;

    //CRCDATH 0; 
    CRCDATH = 0x0;
    //CRCDATL 0; 
    CRCDATL = 0x0;

    //Scanner Configurations
    //
    SCANHADRH = 0xFF;
    //
    SCANHADRL = 0xFF;
    //
    SCANLADRH = 0x0;
    //
    SCANLADRL = 0x0;
    //SCANTSEL LFINTOSC; 
    SCANTRIG = 0x0;

    // Clearing CRC IF flag
    PIR7bits.CRCIF = 0;
    // Disabled CRCI CRC interrupt
    PIE7bits.CRCIE = 0;

    // Clearing Scanner IF flag.
    PIR7bits.SCANIF = 0;
    // Disabled SCANI CRC interrupt
    PIE7bits.SCANIE = 0;

    //CRCEN enabled; CRCGO disabled; CRCACCM data augmented with 0's; CRCSHIFTM shift left; 
    CRCCON0 = 0x90;
    //SCANEN enabled; SCANGO disabled; SCANINTM not affected; SCANMODE Burst mode; 
    SCANCON0 = 0x81;
}

inline void CRC_StartCrc(void)
{
    // Start the serial shifter
    CRCCON0bits.CRCGO = 1;
}

bool CRC_WriteData(uint16_t data)
{
    if(!CRCCON0bits.FULL)
    {
        CRCDATH = (uint8_t)((data >> 8) & 0xFF);
        CRCDATL = (uint8_t)(data & 0xFF);
        return true;
    } 
    else 
    {
        return false;
    }
}

static uint16_t CRC_ReverseValue(uint16_t crc)
{
    uint16_t mask;
    uint16_t reverse;

    mask = 1;
    mask <<= CRCCON1bits.PLEN;
    reverse = 0;

    while(crc)
    {
        if(crc & 0x01)
        {
            reverse |= mask;
        }
        mask >>= 1;
        crc >>= 1;
    }
    return reverse;
}

uint16_t CRC_GetCalculatedResult(bool reverse, uint16_t xorValue)
{
    uint16_t result = 0x00;
    result = (uint16_t)CRCACCL;
    result = result | ((uint16_t)CRCACCH << 8);
    if(reverse)
    {
        result = CRC_ReverseValue(result);
    }
    result ^= xorValue;
    return (result & 0xFFFF);
}

inline bool CRC_IsCrcBusy(void)
{
    return(CRCCON0bits.BUSY);
}

inline void CRC_StartScanner(void)
{
    // Start the serial shifter
    CRCCON0bits.CRCGO = 1;
    // Start the scanner
    SCANCON0bits.SCANGO = 1;
}

inline void CRC_StopScanner(void)
{
    // Stop the serial shifter
    CRCCON0bits.CRCGO = 0;
    // Stop the scanner
    SCANCON0bits.SCANGO = 0;
}

void CRC_SetScannerAddressLimit(uint24_t startAddr, uint24_t endAddr)
{
    SCANHADRU = (uint8_t)((endAddr >> 16) & 0xFF);
    SCANHADRH = (uint8_t)((endAddr >> 8) & 0xFF);
    SCANHADRL = (uint8_t)(endAddr & 0xFF);
    SCANLADRU = (uint8_t)((startAddr >> 16) & 0xFF);
    SCANLADRH = (uint8_t)((startAddr >> 8) & 0xFF);
    SCANLADRL = (uint8_t)(startAddr & 0xFF);
}

inline bool CRC_IsScannerBusy(void)
{
    return(SCANCON0bits.SCANBUSY);
}


