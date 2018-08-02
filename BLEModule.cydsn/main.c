/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include "tiny_printf.h"

CYBLE_CONN_HANDLE_T connectionHandle;
uint8_t isConnected = 0;
uint8_t notificationsEnabled = 0;
uint8_t compareValue=0;
uint8_t isButtonPressed=0;
uint16_t delayValue=200;

CY_ISR(switch_interrupt_handler)
{
    tiny_printf("Button pressed");
    if (!isButtonPressed)
    {
        //DebounceTimer_TriggerCommand(DebounceTimer_MASK, DebounceTimer_CMD_START);
        isButtonPressed=1;
        tiny_printf("Button pressed");
    }
    else
    {
        //DebounceTimer_TriggerCommand(DebounceTimer_MASK, DebounceTimer_CMD_STOP);
        //tiny_printf("Capture Value %d\n", DebounceTimer_ReadCapture());
        //DebounceTimer_TriggerCommand(DebounceTimer_MASK, DebounceTimer_CMD_RELOAD);
        isButtonPressed=0;
        tiny_printf("Button released");
    }
//    uint8_t toggledVal = LED_Read();
//    LED_Write(!toggledVal);
//    tiny_printf("Button Pressed %d\n", compareValue++);
//    CyDelay(200);
    /*
    if (isConnected == 0x01 && notificationsEnabled == 0x01)
    {
        CYBLE_GATTS_HANDLE_VALUE_NTF_T ledHandle;
        ledHandle.attrHandle = CYBLE_HOMEAUTOMATION_LED_CHAR_HANDLE;
        ledHandle.value.val = &toggledVal;
        ledHandle.value.len = 1;
        CyBle_GattsWriteAttributeValue(&ledHandle, 0, &connectionHandle, 0);
        CyBle_GattsNotification(connectionHandle, &ledHandle);
    }*/
    input_sw_ClearInterrupt();
}

CY_ISR(debounceTimerInterruptHandler)
{
    tiny_printf("Interrupt reached");
}


void Stack_Handler(uint32 eventCode, void *eventParam)
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReq;
    
    switch(eventCode)
    {
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            isConnected = 0;
            notificationsEnabled = 0;
            tiny_printf("Disconnected\n");
            break;
        case CYBLE_EVT_GATT_CONNECT_IND:
            connectionHandle = *(CYBLE_CONN_HANDLE_T*)eventParam;
            tiny_printf("Device Connected\n");
            isConnected = 1;
            break;
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReq = (CYBLE_GATTS_WRITE_REQ_PARAM_T*)eventParam;
            if(wrReq->handleValPair.attrHandle == CYBLE_HOMEAUTOMATION_LED_CHAR_HANDLE)
            {
                CyBle_GattsWriteAttributeValue(&wrReq->handleValPair, 0, &connectionHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                
                uint8_t receivedValue = wrReq->handleValPair.value.val[0];
                
                uint16_t compareValue = ((float)receivedValue / (float)255) * 12000;
                
                compareValue = 12000 - compareValue;
                
                
                //ledDimmer_WriteCompare(compareValue);
                tiny_printf((wrReq->handleValPair.value.val[0] == 0) ? "LED OFF\n" : "LED ON\n");
            }
            else if(wrReq->handleValPair.attrHandle == CYBLE_HOMEAUTOMATION_LED_CCCD_DESC_HANDLE)
            {
                CyBle_GattsWriteAttributeValue(&wrReq->handleValPair, 0, &connectionHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                notificationsEnabled = wrReq->handleValPair.value.val[0];
            
                tiny_printf((notificationsEnabled == 1) ? "N ON\n" : "N OFF\n");
                
            }
            CyBle_GattsWriteRsp(connectionHandle);
            break;
    }
}


int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CyGlobalIntEnable;
    //ledDimmer_Start();
    //sw_interrupt_StartEx(switch_interrupt_handler);
    //DebounceTimer_Init();
    //DebounceTimer_SetMode(DebounceTimer_MODE_TIMER_CAPTURE);
    //DebounceTimer_SetPrescaler(DebounceTimer_PRESCALE_DIVBY1);
    //DebounceTimer_SetInterrupt(DebounceTimer_INTR_MASK_CC_MATCH);
    //DebounceTimer_SetOneShot(0);
    //debounceTimerIntr_StartEx(debounceTimerInterruptHandler);
    //DebounceTimer_Enable();
    //button_interrupt_StartEx(button_interrupt);
    
    console_Start();
    uint8_t introMessage[13] = {'H', 'E', '\r', '\n'};
    //CYBLE_API_RESULT_T result = CyBle_Start(Stack_Handler);
    for(;;)
    {
        LED_Write(!LED_Read());
        console_SpiUartPutArray(introMessage, 4);
        tiny_printf("Hello world");
        CyDelay(500);
        //CyBle_ProcessEvents();
    }
}

/* [] END OF FILE */
