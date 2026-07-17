// include files
#include "mcc_generated_files/system/system.h"
#include "ble2driver.h"
#include "mcc_generated_files/uart/eusart1.h"
#include "ble2click.h"


char buf[64];
const char CMD_FACTORYRESET[] = "SF,1\r\n";
const char CMD_USERDEFINEPROFILE[] = "SS,00000001\r\n";
const char CMD_PERIPHERAL[] = "SR,20000000\r\n";
const char CMD_CLEANPRIVATESERVICE[] = "PZ\r\n";
const char CMD_UUID[] = "PS,00112233445566778899AABBCCDDEEFF\r\n";
const char CMD_ADC_WRITE[] =   "PC,012301234567456789AB89ABCDEFCDEF,08,08\r\n";
const char CMD_ADC_READ[] =   "PC,012345670123456789ABCDEF89ABCDEF,20,08\r\n";
const char CMD_SERIALIZED_NAME[] = "S-,BLE2Click\r\n";
const char CMD_NAME[]="SN,BLE2Click\r\n";
const char CMD_REBOOT[] = "R,1\r\n";
const char CMD_ADVERTISE[] = "A\r\n";
const char CMD_DATA_SEND[] =   "SUW,012345670123456789ABCDEF89ABCDEF,";
const char CMD_STATUS[] ="AT+STATE?\r\n";
const char RESP_CMD[]="CMD";
const char RESP_AOK[]="AOK";
const char RESP_CONN[]="Connected";
const char RESP_CONN_PARAM[]="ConnParam";
const char RESP_CONN_DATA[]="WV";
const char RESP_CONN_NOTIFICATION[]="WC";
const char RESP_CONN_END[]="Connection End";

void BLE2ClickGetstr(void) 
{
    unsigned int i;
    // read the data from the UART buffer and store it in buf array
    for(i=0;i<100;i++) {
        if((buf[i]=  BLE2_ReceiveByte())=='\n') 
        {
            break;
        }        
    }
    buf[i-1]='\0';
}

void BLE2ClickSetup () 
{
    // wake the BLE click from sleep
    BLE2_WakeModule();                             // Wake Module using GPIO
    BLE2ClickGetstr();     
    // issue a factory reset
    BLE2_SendString(CMD_FACTORYRESET);
    BLE2ClickGetstr();                             // Wait for "AOK" Response
    // select user defined profile as this application is for non standard BLE profile
    BLE2_SendString(CMD_USERDEFINEPROFILE);
    BLE2ClickGetstr();                             // Wait for "AOK" Response
    // enable auto rescan when the BLE is disconnected
    BLE2_SendString(CMD_PERIPHERAL);
    BLE2ClickGetstr();                             // Wait for "AOK" Response
    // remove all previous private profiles
    BLE2_SendString(CMD_CLEANPRIVATESERVICE);
    BLE2ClickGetstr();                             // Wait for "AOK" Response
    // set the UUID for the profile
    BLE2_SendString(CMD_UUID);
    BLE2ClickGetstr();                             // Wait for "AOK" Response
    // add a private write characteristic
    BLE2_SendString(CMD_ADC_WRITE);
    BLE2ClickGetstr();                             // Wait for "AOK" Response
    // add a private indicate characteristic
    BLE2_SendString(CMD_ADC_READ);
    BLE2ClickGetstr();                             // Wait for "AOK" Response     
    // reboot BLE to make the configurations take effect
    BLE2_SendString(CMD_REBOOT);
    BLE2ClickGetstr();                             // Wait for "Reboot" Response
    BLE2_ReceiveByte();                            // Wait for NULL character
    BLE2ClickGetstr();                             // Wait for "CMD" Response
    
}
