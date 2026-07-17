// include files
#include "application.h"  

// global variables
volatile bool connectionStatus = false;
volatile bool adcReadyFlag = false;     
volatile bool burstMode = false;
volatile bool isCRCPeekOngoing = false;
volatile bool tmr0InterruptFlag = false;
volatile uint8_t flashCrcErrorStatus = NO_ERROR; 
volatile uint16_t crcValBurst = 0;
volatile uint24_t currentAdcValuePtr = 0; 
volatile uint16_t timer1ValueReload; 

void InitialSetup(void) 
{
    // select the analog channel 
    ADC_ChannelSelect(SENSOR_CLICK_AN);
    // enable the sensor
    SENSOR_ENABLE_SetHigh();         
    // setup BLE
    BLE2ClickSetup();  
    // check if PFM and EEPROM are erased
    if(EEPROM_Read(IS_MEMORY_ERASED_ADDR) == 0xFF) 
    {
        NVM_UnlockKeySet(UNLOCK_KEY_WORD_BYTE_WRITE);
        EEPROM_Write(IS_MEMORY_ERASED_ADDR,1);
        NVM_UnlockKeyClear();
        CRCBurstModeInitialize();
        CRCBurstModeCalculate();
        // store the initial value of checksum       
        crcValBurst = CRC_GetCalculatedResult( NORMAL_CRC , CRC_FINAL_XOR_VALUE);        
        ChecksumWrite(crcValBurst);
        // store the initial value of data buffer
        currentAdcValuePtr = SCAN_START_ADDR;
        DataPtrWrite(currentAdcValuePtr);
    }
    else 
    {
        // get the checksum and data pointer from the EEPROM        
        crcValBurst = ChecksumRead();
        currentAdcValuePtr = DataPtrRead();
    }    
    // start the timer and CRC in peek mode
    CRCPeriodicStart();
    isCRCPeekOngoing = true;
}

bool CRC_IsCalculationComplete(void)
{  
    bool busyStatus = 0;
    busyStatus = !(CRC_IsCrcBusy() || CRC_IsScannerOngoing());
    return(busyStatus);
}

inline bool CRC_IsScannerOngoing(void)
{
    return(SCANCON0bits.SCANGO);
}

void ApplicationTask(void) 
{
    volatile uint16_t crcValPeek = 0;
    // local variables to know the status of BLE connection and data
    bool connectionData = false;
    bool connectionEnd = false;
    uint16_t adcValue = 0;  // ADC result variable
    // check if any data is received on UART 
    if(BLE_UART.IsRxReady())
    {
        // get the Response
        BLE2ClickGetstr();
        // if not connected , check if the received data is for new connection. If yes, update the status flag to connected
        if(!connectionStatus)
        {
            connectionStatus = strcmp(buf,RESP_CONN) ? 0 : 1;
        }
        // if device is connected, check for various response received by the BLE and process it 
        if(connectionStatus) 
        {
            connectionEnd = strcmp(buf,RESP_CONN_END) ? 0 : 1;
            connectionData = strncmp(buf,RESP_CONN_DATA,2) ? 0 : 1;
            // if disconnect message is received, make the connection status flag as false
            if(connectionEnd) 
            { 
                // start timer to trigger ADC in every 2sec
//                timer1ValueReload = TIMER1_02s;
                TMR1_CounterSet(TIMER1_02s);
                TMR1_Start(); 
                connectionStatus = false;               
            }
            else if(connectionData)
            {
                //valid data is received, process it
                ADCCommandProcess(); 
            }
        }  
    
    }
    // check if BLE is connected  
    if(connectionStatus )
    {  
        // check if new ADC value is ready for transmit
        if(adcReadyFlag)
        {
           adcReadyFlag = false;
           if(burstMode) 
           {
             // get the averaged data 
             adcValue = ADC_FilterValueGet();
           } 
           else 
           {
              // get the raw data
              adcValue = ADC_ConversionResultGet();
           }  
           adcValue = (uint16_t)((float)adcValue / MAX_ADC_VALUE * 100.0);
           BLEDataSend(adcValue);
        }           
       // check if there is any errors in Flash or CRC
       if(flashCrcErrorStatus) 
        {        
           if(flashCrcErrorStatus == READ_ERROR_STATUS_CODE)
           {
              BLEDataSend(READ_ERROR_DATA); // Error when checking the data read 
           } 
           else if(flashCrcErrorStatus == WRITE_ERROR_STATUS_CODE)
           {
              BLEDataSend(WRITE_ERROR_DATA); // Error when writing data into Flash
           }   
           else if(flashCrcErrorStatus == CRC_ERROR_STATUS_CODE)
           {
              BLEDataSend(CRC_ERROR_DATA); // CRC checksum mismatch error
           }        
           flashCrcErrorStatus = 0;
        }
    }

   // if BLE is not connected , log the data in PFM
   else
   {
        if(adcReadyFlag) 
       {
           adcReadyFlag = false;
           if(burstMode) 
           {
              adcValue = ADC_FilterValueGet();
           } 
           else 
           {
              adcValue = ADC_ConversionResultGet();
           }
           //stop timer running for CRC in peek mode as new value is being updated
           CRCPeriodicStop();
           CRCCON0bits.CRCGO = 0;
           CRCCON0bits.CRCGO = 1;
           isCRCPeekOngoing = false; 
           FlashDataLog(adcValue);
           CRCBurstModeInitialize();
           CRCBurstModeCalculate();
           // store the new checksum value
           crcValBurst = CRC_GetCalculatedResult( NORMAL_CRC , CRC_FINAL_XOR_VALUE);
           ChecksumWrite(crcValBurst);            
           //start the timer and CRC in peek mode
           CRCPeriodicStart();
           isCRCPeekOngoing = true;          
        }
    }
    // start the CRC in peek mode periodically 
    if(tmr0InterruptFlag) 
    {
        tmr0InterruptFlag = false; 
        if(!isCRCPeekOngoing)
        {    
            CRCPeekModeInitialize();
            ScannerSetupAndStart(); 
            isCRCPeekOngoing = true; 
        }
    }
    //Check if CRC calculation is completed
    if (CRC_IsCalculationComplete())
    {        
        crcValPeek = CRC_GetCalculatedResult( NORMAL_CRC , CRC_FINAL_XOR_VALUE);
        if (crcValBurst != crcValPeek) 
        {
            //Critical Error, CRC mismatch has occurred
            flashCrcErrorStatus = CRC_ERROR_STATUS_CODE;
        }
        isCRCPeekOngoing = false; 
    }
}

uint8_t HexValueGet(char x) 
{
    uint8_t hexvalue;    
   // converts the ASCII value to the Hex value.
    if (x >= '0' && x <= '9') 
    {
      hexvalue = x - '0';  
    }
   else if (x >= 'A' && x <= 'F')
    {
      hexvalue = 10 + (x - 'A'); 
    } 
   return hexvalue;
}

uint8_t ADCModeGet(void)
{    
    uint8_t ch = ((uint8_t)(HexValueGet(buf[10]) << 4)) | HexValueGet(buf[11]);
    uint8_t num = (ch<='9') ? (ch-'0') : (ch-'A'+10) ;
    return num;
}

uint8_t ADCCharacteristicGet(void) 
{    
    uint8_t ch = ((uint8_t)(HexValueGet(buf[8]) << 4)) | HexValueGet(buf[9]);
    uint8_t num = (ch<='9') ? (ch-'0') : (ch-'A'+10) ;
    return num;
}

ADC_data ADCCommandGet(void)
{    
    ADC_data data;
    data.ADC_CHARACTERISTIC = ADCCharacteristicGet();
    data.ADC_VALUE = ADCModeGet();
    return data;
}

void ADCCommandProcess(void) 
{   
    uint16_t dataRead;
    ADC_data data = ADCCommandGet();
    uint24_t lcurrentAdcValuePtr = currentAdcValuePtr;
    
    switch(data.ADC_CHARACTERISTIC) 
    {
        case DATA_STATE:
            switch(data.ADC_VALUE)
            {
                case REALTIME_DATA:
                    // send the real time data to phone by enabling the timer
                    TMR1_Start();
                    break;
                case LOG_DATA:
                    // send the logged data to phone
                    TMR1_Stop();
                    while(lcurrentAdcValuePtr < SCAN_STOP_ADDR) 
                    {
                        //read the ADC value that is stored in FLASH
                        dataRead = FLASH_Read(lcurrentAdcValuePtr+1);           
                        dataRead = ( dataRead<<8)|FLASH_Read(lcurrentAdcValuePtr);
                        if(dataRead != 0xFFFF) 
                        {
                            dataRead = (uint16_t)((float)dataRead / MAX_ADC_VALUE * 100);
                            BLEDataSend(dataRead);
                            __delay_ms(100);    
                        }
                        lcurrentAdcValuePtr += 2;
                    }
                    lcurrentAdcValuePtr = SCAN_START_ADDR;
                    while(lcurrentAdcValuePtr < currentAdcValuePtr) 
                    {
                        //read the ADC value that is stored in FLASH
                        dataRead = FLASH_Read(lcurrentAdcValuePtr+1);          
                        dataRead = ( dataRead<<8)|FLASH_Read(lcurrentAdcValuePtr);
                        if(dataRead != 0xFFFF) 
                        {
                            dataRead = (uint16_t)((float)dataRead / MAX_ADC_VALUE * 100.0);
                            BLEDataSend(dataRead);
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
            switch(data.ADC_VALUE)
            {
                case ADC_BURST_MODE:
                    ADCBurstModeInitialize();
                    burstMode = true;
                    break;
                case ADC_BASIC_MODE:
                    ADCBasicModeInitialize();
                    burstMode = false;
                    break;            
                default:
                    break;
            }        
            break;
        case SENSING_INTERVAL:
            switch(data.ADC_VALUE)
            {
                case SENSING_INTERVAL_01:
                    //ADC sampling interval is 1s
                    TMR1_CounterSet(TIMER1_01s);
                    break;
                case SENSING_INTERVAL_02:
                    //ADC sampling interval is 2s
                    TMR1_CounterSet(TIMER1_02s);
                    break;
                case SENSING_INTERVAL_04:
                    //ADC sampling interval is 4s
                    TMR1_CounterSet(TIMER1_04s);
                    break;
                case SENSING_INTERVAL_08:
                    //ADC sampling interval is 8s
                    TMR1_CounterSet(TIMER1_08s);
                    break;
                case SENSING_INTERVAL_16:
                    //ADC sampling interval is 16s
                   TMR1_CounterSet(TIMER1_16s);
                    break;             
                default:
                    break;
            }         
            break;
        default:
            break;
    }
}

void BLEDataSend(uint16_t data) 
{
    uint8_t result[2];
    BLE2_SendString(CMD_DATA_SEND);
    sprintf((char*)result, "%02X", (uint8_t)data);
    BLE2_SendString((const char*)result);
    sprintf((char*)result, "%02X", (uint8_t)(data >> 8));
    BLE2_SendString((const char*)result);
    BLE2_SendString("\r\n");
}

void ADCBurstModeInitialize(void)
{
    ADCON2bits.ADMD = 0b011;
}

void ADCBasicModeInitialize(void) 
{
    ADCON2bits.ADMD = 0b000;
}

void CRCBurstModeInitialize(void)
{
    CRCACCL = 0x00;
    CRCACCH = 0x00;
    SCANCON0bits.MODE = 0x1;
}

void CRCBurstModeCalculate(void)
{     
    ScannerSetupAndStart();   
    // Wait for scan and CRC calculation to complete
    while (!CRC_IsCalculationComplete());   
}

void CRCPeekModeInitialize(void) 
{
    CRCACCL = 0x00;
    CRCACCH = 0x00;
    SCANCON0bits.MODE = 0x2;
}

void ScannerSetupAndStart(void)
{
    CRC_SetScannerAddressLimit(SCAN_START_ADDR, SCAN_STOP_ADDR);
    CRC_StartScanner();
}
void CRCPeriodicStart(void)
{
    TMR0_Start();
    CRCPeekModeInitialize();
    ScannerSetupAndStart(); 
}

void CRCPeriodicStop(void) 
{      
    TMR0_Stop(); 
    TMR0_Write(0x00);
    CRC_StopScanner();
}

void FlashWordWrite(uint24_t flashAddr, uint16_t word) 
{
    uint16_t readWord; 
    nvm_status_t errorStatus;
    NVM_UnlockKeySet(UNLOCK_KEY_WORD_BYTE_WRITE);
    errorStatus = FLASH_Write(flashAddr,word); 
    NVM_UnlockKeyClear();    
    if(errorStatus == NVM_ERROR)
    {
        NVM_StatusClear();
        flashCrcErrorStatus = WRITE_ERROR_STATUS_CODE;       
    }
    else 
    {
        readWord = FLASH_Read(flashAddr);        
        if(readWord != word) 
        {
            flashCrcErrorStatus = READ_ERROR_STATUS_CODE;
        }
    }
}

void FlashDataLog(uint16_t adcValue)
{
    if(currentAdcValuePtr > SCAN_STOP_ADDR) 
    {
        currentAdcValuePtr = SCAN_START_ADDR;
    }
    if(!(currentAdcValuePtr & 0x00FF))
    {
       NVM_UnlockKeySet(UNLOCK_KEY_PAGE_ERASE);
       FLASH_PageErase(currentAdcValuePtr);
       NVM_UnlockKeyClear();
    }
    FlashWordWrite(currentAdcValuePtr,adcValue);
    currentAdcValuePtr += 2;
    DataPtrWrite(currentAdcValuePtr);
}

void ChecksumWrite(uint16_t checksum)
{
    NVM_UnlockKeySet(UNLOCK_KEY_WORD_BYTE_WRITE);
    // Store the checksum in EEPROM
    EEPROM_Write(CHECKSUM_HIGHBYTE_ADDR,(checksum >> 8));
    EEPROM_Write(CHECKSUM_LOWBYTE_ADDR,(uint8_t)checksum);
    NVM_UnlockKeyClear();
}

uint16_t ChecksumRead(void)
{
    // Read the checksum from EEPROM
    uint8_t checkSumHighByte = EEPROM_Read(CHECKSUM_HIGHBYTE_ADDR);
    uint8_t checkSumLowByte = EEPROM_Read(CHECKSUM_LOWBYTE_ADDR);
    return(((uint16_t)checkSumHighByte << 8) | checkSumLowByte);
}

void DataPtrWrite(uint24_t dataPtr)
{
    NVM_UnlockKeySet(UNLOCK_KEY_WORD_BYTE_WRITE);
    // Store the current address pointer in EEPROM
    EEPROM_Write(CHECKSUM_POINTER_HIGHBYTE_ADDR,((uint8_t)dataPtr >> 8));
    EEPROM_Write(CHECKSUM_POINTER_LOWBYTE_ADDR,(uint8_t)dataPtr);
    NVM_UnlockKeyClear();
}

uint16_t DataPtrRead(void) 
{
    // Read the current address pointer from EEPROM
    uint8_t addressHighByte = EEPROM_Read(CHECKSUM_POINTER_HIGHBYTE_ADDR);
    uint8_t addressLowByte = EEPROM_Read(CHECKSUM_POINTER_LOWBYTE_ADDR);
    return(((uint16_t)addressHighByte << 8) | addressLowByte);
 } 
  
void TMR0_UserInterruptHandler(void)
{
    //Timer interrupt  handler function
    tmr0InterruptFlag = true;
}

void ADC_UserInterruptHandler(void)
{
    //ADC interrupt handler function
    adcReadyFlag = true;
}