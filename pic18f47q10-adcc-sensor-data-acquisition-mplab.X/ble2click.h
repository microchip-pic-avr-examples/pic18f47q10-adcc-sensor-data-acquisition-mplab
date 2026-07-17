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

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BLE2CLICK_H
#define	BLE2CLICK_H

#ifdef	__cplusplus
extern "C" {
#endif

extern char buf[64];
extern const char CMD_FACTORYRESET[];
extern const char CMD_USERDEFINEPROFILE[];
extern const char CMD_PERIPHERAL[];
extern const char CMD_CLEANPRIVATESERVICE[];
extern const char CMD_UUID[];
extern const char CMD_ADC_WRITE[];
extern const char CMD_ADC_READ[];
extern const char CMD_SERIALIZED_NAME[];
extern const char CMD_NAME[];
extern const char CMD_REBOOT[];
extern const char CMD_ADVERTISE[];
extern const char CMD_DATA_SEND[];
extern const char CMD_STATUS[];
extern const char RESP_CMD[];
extern const char RESP_AOK[];
extern const char RESP_CONN[];
extern const char RESP_CONN_PARAM[];
extern const char RESP_CONN_DATA[];
extern const char RESP_CONN_NOTIFICATION[];
extern const char RESP_CONN_END[];

void BLE2ClickSetup(void) ;
void BLE2ClickGetstr(void);


#ifdef	__cplusplus
}
#endif

#endif	/* BLE2CLICK_H */

