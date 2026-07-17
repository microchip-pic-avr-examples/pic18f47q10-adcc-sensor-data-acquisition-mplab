// include files
#include "mcc_generated_files/system/system.h"
#include "ble2driver.h"
#include <string.h>
#include "mcc_generated_files/uart/eusart1.h"

void BLE2_EnterCommand_Mode(void)
{
    //LATAbits.LATA3 = 1; /* set BLE2_Cmd_Mldp output high */
    BLE_CMD_SetHigh(); 
    DELAY_milliseconds(20);
   // LATAbits.LATA3 = 0; /* set BLE2_Cmd_Mldp output low */
    BLE_CMD_SetLow(); 
    DELAY_milliseconds(20);
}
void BLE2_ExitCommand_Mode(void)
{
   // LATAbits.LATA3 = 1; /* set BLE2_Cmd_Mldp output high */
    BLE_CMD_SetHigh(); 
}
void BLE2_EnterMicrochipLowEnergyDataProfile_Mode(void)
{
   // LATAbits.LATA3 = 0; /* set BLE2_Cmd_Mldp output low */
    BLE_CMD_SetLow();
}

void BLE2_DeepSleepModule(void)
{
   // LATAbits.LATA7 = 0; /* set BLE2_Wake output low */
    BLE_WAKE_SetLow();
}
void BLE2_WakeModule(void)
{
    TRISAbits.TRISA7 = 0;
    BLE_WAKE_SetHigh(); /* set BLE2_Wake output high */
}

bool BLE2_isConnected(void)
{
    return PORTAbits.RA0 /* get BLE2_Conn value */;
}

void BLE2_SendString(const char* command)
{
    BLE2_SendBuffer((uint8_t *)command, strlen(command));
}

void BLE2_SendBuffer(uint8_t *buffer, uint16_t length)
{
    while(length--)
    {
        BLE2_SendByte(*buffer++);
    }
        
}
void BLE2_SendByte(uint8_t byte)
{    
    while(!(BLE_UART.IsTxReady()));
    BLE_UART.Write(byte); 
}

uint8_t BLE2_ReceiveByte(void)
{    
    while(!(BLE_UART.IsRxReady()));
    return (BLE_UART.Read()); 
}
