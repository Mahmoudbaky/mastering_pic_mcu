/*
 * mcal_eusart.c
 *
 *  Created on: april 13, 2024
*/

/* INCLUDS */

#include "mcal_eusart.h"


/************* randoms ****************/
#if EUSART_TX_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
static void (*TX_interrupt_handler)(void) = NULL;
#endif

#if EUSART_RX_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
static void (*RX_interrupt_handler)(void) = NULL;
static void (*framing_error_interrupt_handler)(void) = NULL;
static void (*overrun_error_interrupt_handler)(void) = NULL;
#endif


/************* helper functions declerations ****************/
static void EUSART_SetBaudRate_equation      (eusart_obj_t *eusart);
static void EUSART_Async_Tx_configurations   (eusart_obj_t *eusart);
static void EUSART_Async_Rx_configurations   (eusart_obj_t *eusart);

/************* main functions ****************/

Std_ReturnType EUSART_Async_Init  (const eusart_obj_t *eusart){
    Std_ReturnType ret = E_OK;
    if(NULL == eusart){
        ret = E_NOT_OK;
    }
    else{
        /* disable eusart module */
        RCSTAbits.SPEN = EUSART_DISABLE;

        /* pin configurations*/
        TRISCbits.RC7 = 1;
        TRISCbits.RC6 = 1;
        
        /* baud rate configuartions */
        EUSART_SetBaudRate_equation(eusart);

        /* TX configuartions */
        EUSART_Async_Tx_configurations(eusart);

        /* RX configuartions */
        EUSART_Async_Rx_configurations(eusart);

        /* enable eusart module */
        RCSTAbits.SPEN = EUSART_ENABLE;


    }

    return ret;
}

Std_ReturnType EUSART_Async_DeInit(const eusart_obj_t *eusart){
    Std_ReturnType ret = E_OK;
    if(NULL == eusart){
        ret = E_NOT_OK;
    }
    else{
        /* disable eusart module */
        RCSTAbits.SPEN = EUSART_DISABLE;
    }
    
    return ret;
}

// NOTE : "notice the defference between the blocking and nonblocking functions" 

Std_ReturnType EUSART_ReadByte_blocking (uint8 *data){
    Std_ReturnType ret = E_OK;
    if(NULL == data){
        ret = E_NOT_OK;
    }
    else{
        while(!PIR1bits.RCIF);
        *data = RCREG;
    }

    return ret;
}

Std_ReturnType EUSART_ReadByte_nonblocking (uint8 *data){
    Std_ReturnType ret = E_OK;
    if(NULL == data){
        ret = E_NOT_OK;
    }
    else{
        if(1 == PIR1bits.RCIF){
            *data = RCREG;
        }   
        else{
            ret = E_NOT_OK;
        }
    }

    return ret;
}

Std_ReturnType EUSART_Async_RX_Restart(void){
    Std_ReturnType ret = E_OK;
    RCSTAbits.CREN = EUSART_ASYNC_RX_DISABLE;   // disable the rx function
    RCSTAbits.CREN = EUSART_ASYNC_RX_ENABLE;    // enable the rx function
    return ret;

}

Std_ReturnType EUSART_WriteByte_blocking(uint8 data){
    Std_ReturnType ret = E_OK;
    while(!TXSTAbits.TRMT);
#if EUSART_TX_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
        EUSART_TX_InterruptEnable();
#endif
    TXREG = data;

    return ret;
}

Std_ReturnType EUSART_WriteString_blocking(uint8 *data, uint32 str_len){
    Std_ReturnType ret = E_OK;
    uint32 counter = ZERO_INIT;
    for(counter = ZERO_INIT ; counter < str_len ; counter++){
        EUSART_WriteByte_blocking(data[counter]);
    }

    return ret;
}



/************* helper functions ****************/

static void EUSART_SetBaudRate_equation(eusart_obj_t *eusart){
    float baudrate_value = 0.0;
    switch (eusart->eusart_baudrate_equation_select){
        case BUADRATE_ASYNC_8BIT_LOW_SPEED :
            TXSTAbits.SYNC    = EUSART_ASYNC_MODE;
            TXSTAbits.BRGH    = EUSART_ASYNC_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_REG_SIZE;
            baudrate_value = ((_XTAL_FREQ/(float)eusart->eusart_baudrate_value)/64) - 1;
            break;

        case BUADRATE_ASYNC_8BIT_HIGH_SPEED :
            TXSTAbits.SYNC    = EUSART_ASYNC_MODE;
            TXSTAbits.BRGH    = EUSART_ASYNC_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_REG_SIZE;
            baudrate_value = ((_XTAL_FREQ/(float)eusart->eusart_baudrate_value)/16) - 1;
            break;

        case BUADRATE_ASYNC_16BIT_LOW_SPEED:
            TXSTAbits.SYNC    = EUSART_ASYNC_MODE;
            TXSTAbits.BRGH    = EUSART_ASYNC_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_REG_SIZE;
            baudrate_value = ((_XTAL_FREQ/(float)eusart->eusart_baudrate_value)/16) - 1;
            break;

        case BUADRATE_ASYNC_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC    = EUSART_ASYNC_MODE;
            TXSTAbits.BRGH    = EUSART_ASYNC_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_REG_SIZE;
            baudrate_value = ((_XTAL_FREQ/(float)eusart->eusart_baudrate_value)/4) - 1;
            break;

        case BUADRATE_SYNC_8BIT:
            TXSTAbits.SYNC    = EUSART_SYNC_MODE;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_REG_SIZE;
            baudrate_value = ((_XTAL_FREQ/(float)eusart->eusart_baudrate_value)/4) - 1;
            break;

        case BUADRATE_SYNC_16BIT:
            TXSTAbits.SYNC    = EUSART_SYNC_MODE;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_REG_SIZE;
            baudrate_value = ((_XTAL_FREQ/(float)eusart->eusart_baudrate_value)/4) - 1;
            break;

        default:
            /* nothing */
            break;
    }

    SPBRG  = (uint8)((uint32)baudrate_value); 
    SPBRGH = (uint8)(((uint32)baudrate_value)>>8);
}

static void EUSART_Async_Tx_configurations(eusart_obj_t *eusart){
    if(EUSART_ASYNC_TX_ENABLE == eusart->eusart_tx_cfg.eusart_tx_enable){

        /* TX ENABLE */
        TXSTAbits.TXEN = EUSART_ASYNC_TX_ENABLE;

        /* interrupt configurations */
        TX_interrupt_handler = eusart->eusart_tx_isr;

        if (EUSART_ASYNC_TX_INTERRUPT_ENABLE == eusart->eusart_tx_cfg.eusart_tx_interrupt_enable){
            PIE1bits.TXIE = EUSART_ASYNC_TX_INTERRUPT_ENABLE;
#if EUSART_TX_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
            EUSART_TX_InterruptEnable();
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
            INTERRUPT_InterruptPriorityEnable();
            if(INTERRUPT_HIGH_PRIORITY == eusart->eusart_tx_cfg.eusart_tx_interrupt_priority){
                INTERRUPT_globalInterruptEnableHigh();
                EUSART_TX_InterruptPriorityHIGH();
            }
            else if(INTERRUPT_LOW_PRIORITY == eusart->eusart_tx_cfg.eusart_tx_interrupt_priority){
                INTERRUPT_globalInterruptEnableLow();
                EUSART_TX_InterruptPriorityLOW();
            }
            else{  /* nothing */  }
#else
            INTERRUPT_globalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();

#endif
#endif
        }
        else if(EUSART_ASYNC_TX_INTERRUPT_DISABLE == eusart->eusart_tx_cfg.eusart_tx_interrupt_enable){
            PIE1bits.TXIE = EUSART_ASYNC_TX_INTERRUPT_DISABLE;
        }
        else{    /* nothing */  }  

        /* 9-bit configurations */
        if (eusart->eusart_tx_cfg.eusart_tx_9bit_enable == EUSART_ASYNC_TX_9BIT_ENABLE){
            TXSTAbits.TX9 = EUSART_ASYNC_TX_9BIT_ENABLE;
        }
        else if(eusart->eusart_tx_cfg.eusart_tx_9bit_enable == EUSART_ASYNC_TX_9BIT_DISABLE){
            TXSTAbits.TX9 = EUSART_ASYNC_TX_9BIT_DISABLE;
        }
        else{  /* nothing */  }
    }
    else{  /* nothing */  }
}

static void EUSART_Async_Rx_configurations(eusart_obj_t *eusart){
    if(EUSART_ASYNC_RX_ENABLE == eusart->eusart_rx_cfg.eusart_rx_enable){

            /* RX ENABLE */
            RCSTAbits.CREN = EUSART_ASYNC_RX_ENABLE;

            /* interrupt configurations */
            RX_interrupt_handler = eusart->eusart_rx_isr;
            framing_error_interrupt_handler = eusart->eusart_framing_error_isr;
            overrun_error_interrupt_handler = eusart->eusart_overrun_error_isr;
            if (eusart->eusart_rx_cfg.eusart_rx_interrupt_enable == EUSART_ASYNC_RX_INTERRUPT_ENABLE){
                PIE1bits.RCIE = EUSART_ASYNC_RX_INTERRUPT_ENABLE;
#if EUSART_RX_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
                EUSART_RX_InterruptEnable();
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
                INTERRUPT_InterruptPriorityEnable();
                if(INTERRUPT_HIGH_PRIORITY == eusart->eusart_rx_cfg.eusart_rx_interrupt_priority){
                    INTERRUPT_globalInterruptEnableHigh();
                    EUSART_RX_InterruptPriorityHIGH();
                }
                else if(INTERRUPT_LOW_PRIORITY == eusart->eusart_rx_cfg.eusart_rx_interrupt_priority){
                    INTERRUPT_globalInterruptEnableLow();
                    EUSART_RX_InterruptPriorityLOW();
                }
                else{  /* nothing */  }
#else
                INTERRUPT_globalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
            }
            else if(eusart->eusart_rx_cfg.eusart_rx_interrupt_enable == EUSART_ASYNC_RX_INTERRUPT_DISABLE){
                PIE1bits.RCIE = EUSART_ASYNC_RX_INTERRUPT_DISABLE;
            }
            else{    /* nothing */  }  

            /* 9-bit configurations */
            if (eusart->eusart_rx_cfg.eusart_rx_9bit_enable == EUSART_ASYNC_RX_9BIT_ENABLE){
                RCSTAbits.RX9 = EUSART_ASYNC_RX_9BIT_ENABLE;
            }
            else if(eusart->eusart_rx_cfg.eusart_rx_9bit_enable == EUSART_ASYNC_RX_9BIT_DISABLE){
                RCSTAbits.RX9 = EUSART_ASYNC_RX_9BIT_DISABLE;
            }
            else{  /* nothing */  }
        }
        else{  /* nothing */  }
    
}

/************* isr function ****************/
void EUSART_TX_ISR(void){
    /* CLEAR FLAGE */
    // done by writing to TXREG

    /* CODE */
#if EUSART_TX_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
    EUSART_TX_InterruptDisable();
#endif

    /* call back */
    if(TX_interrupt_handler){ TX_interrupt_handler();}
    else{  /* nothing */  }
}

void EUSART_RX_ISR(void){
    /* CLEAR FLAGE */
    // done by reading RCREG

    /* CODE */

    /* call back */
    if(RX_interrupt_handler)            { RX_interrupt_handler();}
    else{  /* nothing */  }
    if(framing_error_interrupt_handler) { framing_error_interrupt_handler(); }
    else{  /* nothing */  }
    if(overrun_error_interrupt_handler) { overrun_error_interrupt_handler(); }
    else{  /* nothing */  }
}