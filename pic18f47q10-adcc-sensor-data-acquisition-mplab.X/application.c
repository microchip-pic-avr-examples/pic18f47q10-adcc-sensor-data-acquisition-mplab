// include files
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/BLE2_driver.h"

#include "application.h"
#include "BLE2Click.h"

void InitialSetup(void) {
    // clear the NVM register bits 
    NVMCON0 = 0x00;
    // select the analog channel 
    ADCCSetSensorPin(ADC_CLICK_2_PIN);
    // enable the UV sensor
    sensor_enable_SetHigh();    
    // setup BLE
    BLE2ClickSetup();  
    // check if PFM and EEPROM are erased
    if(DATAEE_ReadByte(IS_MEMORY_ERASED) == 0xFF) {
        DATAEE_WriteByte(IS_MEMORY_ERASED,1);
        // initialize CRC in burst mode
        CRCInitializeBurstMode();
        // start CRC
        CRCBurstMode();
        //calculate and store the initial value of checksum
        crcValBurst = CRC_CalculatedResultGet(NORMAL, XOR_VALUE);
        writeChecksum(crcValBurst);
        // store the initial value of data buffer
        currentAdcValuePtr = START_ADDR;
        writeDataPtr(currentAdcValuePtr);
    } else {
        // get the checksum and data pointer from the EEPROM        
        crcValBurst = readChecksum();
        currentAdcValuePtr = readDataPtr();
    }    
    //enable the timer for CRC in peek mode
    TMR0_StartTimer();
}

void ApplicationTask(void) {
    // local variables to handle various BLE operations
    bool connection_data = false;
    bool connection_end = false;
    // ADC result variable
    uint16_t adcValue;    
    
    // check if any data is received on UART 
    if(uart[BLE2].DataReady()) {
        // get the Response
        BLE2ClickGetstr();
        // if not connected , check if the received data is for new connection. If yes, update the status flag to connected
        if(!connection_status) {
            connection_status=strcmp(buf,resp_conn) ? 0 : 1;
        }
        // if device is connected, check for various response received by the BLE and process it 
        if(connection_status) {
            connection_end=strcmp(buf,resp_conn_end) ? 0 : 1;
            connection_data=strncmp(buf,resp_conn_data,2) ? 0 : 1;
            // received disconnect message, make the connection status flag as false
            if(connection_end) { 
                // start logging to PFM every 2s as BLE is disconnected
                timer1ReloadVal = TIMER1_02s;
                TMR1_Reload();
                TMR1_StartTimer();
                connection_status=false;
            // valid data received, process it
            }else if(connection_data){
                processADCCommand(); 
            }
        }  
    }
    // check if new ADCC value is ready for transmit
    if(connection_status && adcReadyFlag) {
        adcReadyFlag = false;
        if(burstMode) {
            // get the averaged data 
            adcValue = ADCC_GetFilterValue();
        } else {
            // get the raw data
            adcValue = ADCC_GetConversionResult();
        }  
        adcValue = (float)adcValue / MAX_ADC_VALUE * 100;
        sendADCCValueBLE(adcValue);
    }
    // check if there is any errors in Flash or CRC
    if(connection_status && flashCrcErrorStatus) {
        // clear the NVMERR bit
        NVMCON0bits.NVMERR = 0;
        if(flashCrcErrorStatus == 1) {
            sendADCCValueBLE(READ_ERROR);
        } else if(flashCrcErrorStatus == 3) {
            sendADCCValueBLE(WRITE_ERROR);
        } else if(flashCrcErrorStatus == 5) {
            sendADCCValueBLE(CRC_ERROR);
        }
    }
    // if BLE is not connected , log the data in PFM
    if((!connection_status) && adcReadyFlag) {
        adcReadyFlag = false;
        if(burstMode) {
            adcValue = ADCC_GetFilterValue();
        } else {
            adcValue = ADCC_GetConversionResult();
        }
        //stop timer running for CRC in peek mode as new value is being updated
        TMR0_StopTimer();
        TMR0_WriteTimer(0x00);
        CRC_SCAN_StopScanner();
        isCRCPeekEnabled = false;            
        LogDataToPFM(adcValue);
        //initialize CRC in burst mode
        CRCInitializeBurstMode();
        // start CRC
        CRCBurstMode();
        //calculate the new checksum
        crcValBurst = CRC_CalculatedResultGet(NORMAL, XOR_VALUE);
        writeChecksum(crcValBurst);
        //re enable the timer for CRC in peek mode
        TMR0_StartTimer();
    }
    // check the CRC value periodically
    if(tmr0InterruptFlag) {
        tmr0InterruptFlag = false;
        if(!isCRCPeekEnabled) {
        CRCInitializePeekMode();
        StartCRCPeekMode();
        isCRCPeekEnabled = true;
        }
        //Check if CRC Scan is completed
        if (CRC_SCAN_HasScanCompleted()) {  
            //Stop Scanner
            CRC_SCAN_StopScanner();         
            crcValPeek = CRC_CalculatedResultGet(NORMAL, XOR_VALUE);
            if (crcValBurst != crcValPeek) {
                //Critical Error, CRC mismatch has occurred
                flashCrcErrorStatus = 0x05; 
            }
            isCRCPeekEnabled = false;
        }
    }
}

uint8_t getHexValue(char x) {
    uint8_t hexvalue;    
    if(x=='0') {
        hexvalue = 0;
    }
    if(x=='1') {
        hexvalue = 1;
    }
    if(x=='2') {
        hexvalue = 2;
    }
    if(x=='3') {
        hexvalue = 3;
    }
    if(x=='4') {
        hexvalue = 4;
    }
    if(x=='5') {
        hexvalue = 5;
    }
    if(x=='6') {
        hexvalue = 6;
    }
    if(x=='7') {  
        hexvalue = 7; 
    }
    if(x=='8') {
        hexvalue = 8;
    }
    if(x=='9') {
        hexvalue = 9;
    }     
    if(x=='A') {
        hexvalue = 0x0A;
    }
    if(x=='B') {
        hexvalue = 0x0B;
    }
    if(x=='C') {
        hexvalue = 0x0C;
    }
    if(x=='D') {
        hexvalue = 0x0D;
    }
    if(x=='E') {
        hexvalue = 0x0E;
    }
    if(x=='F') {
        hexvalue = 0x0F;
    } 
    return hexvalue;
}

uint8_t getADCMode(void) {    
    uint8_t ch = (getHexValue(buf[10]) << 4) | getHexValue(buf[11]);
    uint8_t num = (ch<='9') ? (ch-'0') : (ch-'A'+10) ;
    return num;
}

uint8_t getADCCharacteristic(void) {    
    uint8_t ch = (getHexValue(buf[8]) << 4) | getHexValue(buf[9]);
    uint8_t num = (ch<='9') ? (ch-'0') : (ch-'A'+10) ;
    return num;
}

ADC_data getADCCommand(void) {    
    ADC_data data;
    data.ADC_CHARACTERISTIC = getADCCharacteristic();
    data.ADC_VALUE = getADCMode();
    return data;
}

void processADCCommand(void) {    
    ADC_data data = getADCCommand();
    uint16_t lcurrentAdcValuePtr = currentAdcValuePtr;
    switch(data.ADC_CHARACTERISTIC) {
        case ADC_STATE:
            switch(data.ADC_VALUE) {
                case ADC_REAL_DATA:
                    // send real time data to phone by enabling the timer
                    TMR1_StartTimer();
                    break;
                case ADC_LOG_DATA:
                    // send logged data to phone
                    TMR1_StopTimer();
                    while(lcurrentAdcValuePtr < STOP_ADDR) {
                        uint16_t dataRead = FLASH_ReadWord(lcurrentAdcValuePtr);
                        if(dataRead != 0xFFFF) {
                            dataRead = (float)dataRead / MAX_ADC_VALUE * 100;
                            sendADCCValueBLE(dataRead);
                            __delay_ms(100);
                        }
                        lcurrentAdcValuePtr += 2;
                    }
                    lcurrentAdcValuePtr = START_ADDR;
                    while(lcurrentAdcValuePtr < currentAdcValuePtr) {
                        uint16_t dataRead = FLASH_ReadWord(lcurrentAdcValuePtr);
                        if(dataRead != 0xFFFF) {
                            dataRead = (float)dataRead / MAX_ADC_VALUE * 100;
                            sendADCCValueBLE(dataRead);
                            __delay_ms(100);
                        }                        
                        lcurrentAdcValuePtr += 2;                    
                    }
                    break;
                default:
                    break;
            }
            break;
        case ADC_MODE:
            switch(data.ADC_VALUE) {
                case ADC_BURST_MODE:
                    //ADC in burst mode
                    ADCCBurstModeInitialize();
                    burstMode = true;
                    break;
                case ADC_BASIC_MODE:
                    //ADC in basic mode
                    ADCCBasicModeInitialize();
                    burstMode = false;
                    break;            
                default:
                    break;
            }        
            break;
        case ADC_INTERVAL:
            switch(data.ADC_VALUE) {
                case INTERVAL_01:
                    //ADC sampling interval is 1s
                    timer1ReloadVal = TIMER1_01s;
                    TMR1_Reload();
                    break;
                case INTERVAL_02:
                    //ADC sampling interval is 2s
                    timer1ReloadVal = TIMER1_02s;
                    TMR1_Reload();
                    break;
                case INTERVAL_04:
                    //ADC sampling interval is 4s
                    timer1ReloadVal = TIMER1_04s;
                    TMR1_Reload();
                    break;
                case INTERVAL_08:
                    //ADC sampling interval is 8s
                    timer1ReloadVal = TIMER1_08s;
                    TMR1_Reload();
                    break;
                case INTERVAL_16:
                    //ADC sampling interval is 16s
                    timer1ReloadVal = TIMER1_16s;
                    TMR1_Reload();
                    break;             
                default:
                    break;
            }         
            break;
        default:
            break;
        }
}

void FLASHWriteWordSingle(uint32_t flashAddr, uint16_t word) {
    
    uint8_t GIEBitValue = INTCONbits.GIE;
    uint16_t data_check;    
    
    // Load 22-bit address
    NVMADRL = 0xFF & (flashAddr);
    NVMADRH = 0xFF & (flashAddr >> 8);
    NVMADRU = 0xFF & (flashAddr >> 16);
    
    // Load the 16 bit data
    NVMDAT = word;
    
    // Unlock and launch the transfer from SECRAM to PFM
    INTCONbits.GIE = 0;
    // Enable NVM access
    NVMCON0bits.NVMEN = 1;  
    // unlock sequence
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
    
    if(NVMCON0bits.NVMERR) {
        flashCrcErrorStatus = 0x03; 
    } else {
        data_check = FLASH_ReadWord(flashAddr);
        if(data_check != word) {
            flashCrcErrorStatus = 0x01;
        }
    }
    
    NVMCON0bits.NVMEN = 0;    // Disable NVM access
    INTCONbits.GIE = GIEBitValue; 
}

void LogDataToPFM(uint16_t adcValue) {
    if(currentAdcValuePtr > STOP_ADDR) {
        currentAdcValuePtr = START_ADDR;
    }
    if(!(currentAdcValuePtr & 0x00FF)) {
        FLASH_EraseBlock(currentAdcValuePtr);
    }
    FLASHWriteWordSingle(currentAdcValuePtr,adcValue);
    currentAdcValuePtr += 2;
    writeDataPtr(currentAdcValuePtr);
}

void sendADCCValueBLE(uint16_t adcValue) {    
    uint8_t result[2];
    BLE2_SendString(cmd_adc_value_send);
    sprintf((char*)result, "%02X", (uint8_t)adcValue);
    BLE2_SendString((const char*)result);
    sprintf((char*)result, "%02X", (uint8_t)(adcValue >> 8));
    BLE2_SendString((const char*)result);
    BLE2_SendString("\r\n");
}

void ADCCBurstModeInitialize(void) {
    ADCON2bits.ADMD = 0b011;
}

void ADCCBasicModeInitialize(void) {
    ADCON2bits.ADMD = 0b000;
}

void ADCCSetSensorPin(uint8_t adcPin) {
    ADPCH = adcPin;
}

void CRCInitializePeekMode() {
    CRCACCL = 0x00;
    CRCACCH = 0x00;

    SCANCON0bits.MODE = 0x2;
}

void CRCInitializeBurstMode() {
    CRCACCL = 0x00;
    CRCACCH = 0x00;

    SCANCON0bits.MODE = 0x1;
}

void StartCRCPeekMode() {
    // Sets SCAN address limit
    CRC_SCAN_SetAddressLimit(START_ADDR, STOP_ADDR);

    // Start Scanner - Peek Mode
    CRC_SCAN_StartScanner();
}

void CRCBurstMode() {
    // Sets SCAN address limit
    CRC_SCAN_SetAddressLimit(START_ADDR, STOP_ADDR);

    // Start Scanner - Burst Mode
    CRC_SCAN_StartScanner();

    // Wait for scan to complete
    while (!CRC_SCAN_HasScanCompleted());

    // Stop Scanner
    CRC_SCAN_StopScanner();
}

void writeChecksum(uint16_t checksum) {
    // store the checksum in EEPROM
    DATAEE_WriteByte(CHECKSUM_HIGHBYTE,(checksum >> 8));
    DATAEE_WriteByte(CHECKSUM_LOWBYTE,(uint8_t)checksum);
}

uint16_t readChecksum(void) {
    // read the checksum from EEPROM
    uint8_t checkSumHighByte = DATAEE_ReadByte(CHECKSUM_HIGHBYTE);
    uint8_t checkSumLowByte = DATAEE_ReadByte(CHECKSUM_LOWBYTE);
    return(((uint16_t)checkSumHighByte << 8) | checkSumLowByte);
}

void writeDataPtr(uint16_t dataPtr) {
    // store the current address pointer in EEPROM
    DATAEE_WriteByte(ADDRESS_POINTER_HIGHBYTE,(dataPtr >> 8));
    DATAEE_WriteByte(ADDRESS_POINTER_LOWBYTE,(uint8_t)dataPtr);
}

uint16_t readDataPtr(void) {
    // read the current address pointer from EEPROM
    uint8_t addressHighByte = DATAEE_ReadByte(ADDRESS_POINTER_HIGHBYTE);
    uint8_t addressLowByte = DATAEE_ReadByte(ADDRESS_POINTER_LOWBYTE);
    return(((uint16_t)addressHighByte << 8) | addressLowByte);
}


void TMR0_UserInterruptHandler(void)
{
     //timer interrupt  handler function
     tmr0InterruptFlag = true;
}

void ADCC_UserInterruptHandler(void)
{
    //adc interrupt handler function
     adcReadyFlag = true;
}

