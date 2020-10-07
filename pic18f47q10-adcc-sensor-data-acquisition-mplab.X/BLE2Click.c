// include files
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/BLE2_driver.h"
#include "mcc_generated_files/drivers/uart.h"

#include "BLE2Click.h"

void BLE2ClickGetstr(void) {
    unsigned int i;
    // read the data from the UART buffer and store it in buf array
    for(i=0;i<100;i++) {
        if((buf[i]=uart[BLE2].Read())=='\n') {
            break;
        }        
    }
    buf[i-1]='\0';
}

void BLE2ClickSetup () {
    // wake the BLE click from sleep
    BLE2_WakeModule();                              // Wake Module using GPIO
    BLE2ClickGetstr();                             // Wait for "CMD" Response
    // issue a factory reset
    BLE2_SendString(cmd_factoryreset);
    BLE2ClickGetstr();                             // Wait for "AOK" Response
    // select user defined profile as this application is for non standard BLE profile
    BLE2_SendString(cmd_userdefineprofile);
    BLE2ClickGetstr();                             // Wait for "AOK" Response
    // enable auto rescan when the BLE is disconnected
    BLE2_SendString(cmd_peripheral);
    BLE2ClickGetstr();                             // Wait for "AOK" Response
    // remove all previous private profiles
    BLE2_SendString(cmd_cleanprivateservice);
    BLE2ClickGetstr();                             // Wait for "AOK" Response
    // set the UUID for the profile
    BLE2_SendString(cmd_UUID);
    BLE2ClickGetstr();                             // Wait for "AOK" Response
    // add a private write characteristic
    BLE2_SendString(cmd_adc_write);
    BLE2ClickGetstr();                             // Wait for "AOK" Response
    // add a private indicate characteristic
    BLE2_SendString(cmd_adc_read);
    BLE2ClickGetstr();                             // Wait for "AOK" Response     
    // reboot BLE to make the configurations take effect
    BLE2_SendString(cmd_reboot);
    BLE2ClickGetstr();                             // Wait for "Reboot" Response
    uart[BLE2].Read();                              // Wait for NULL character
    BLE2ClickGetstr();                             // Wait for "CMD" Response
}
