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

#ifndef BLE2CLICK_H
#define	BLE2CLICK_H

#ifdef	__cplusplus
extern "C" {
#endif

char buf[64];
const char cmd_factoryreset[] = "SF,1\r\n";
const char cmd_userdefineprofile[] = "SS,00000001\r\n";
const char cmd_peripheral[] = "SR,20000000\r\n";
const char cmd_cleanprivateservice[] = "PZ\r\n";
const char cmd_UUID[] = "PS,00112233445566778899AABBCCDDEEFF\r\n";
const char cmd_adc_write[] =   "PC,012301234567456789AB89ABCDEFCDEF,08,08\r\n";
const char cmd_adc_read[] =   "PC,012345670123456789ABCDEF89ABCDEF,20,08\r\n";
const char cmd_serialized_name[] = "S-,BLE2Click\r\n";
const char cmd_name[]="SN,BLE2Click\r\n";
const char cmd_reboot[] = "R,1\r\n";
const char cmd_advertise[] = "A\r\n";
const char cmd_adc_value_send[] =   "SUW,012345670123456789ABCDEF89ABCDEF,";
const char resp_cmd[]="CMD";
const char resp_AOK[]="AOK";
const char resp_conn[]="Connected";
const char resp_conn_param[]="ConnParam";
const char resp_conn_data[]="WV";
const char resp_conn_notification[]="WC";
const char resp_conn_end[]="Connection End";

void BLE2ClickSetup (void) ;
void BLE2ClickGetstr (void);


#ifdef	__cplusplus
}
#endif

#endif	/* BLE2CLICK_H */

