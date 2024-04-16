/*
 * mcal_eusart.h
 *
 *  Created on: april 13, 2024
*/


/* INCLUDS */

#include "mcal_eusart_cfg.h"
#include "../mcal_std_types.h"
#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
#include "pic18f4620.h"


/* MACRO DECLARATIONS */

// EUSART ENABLE / DISABLE :-
#define EUSART_ENABLE  1
#define EUSART_DISABLE 0

// EUSART configuartions :-
// EUSART mode :
#define EUSART_SYNC_MODE  1
#define EUSART_ASYNC_MODE 0
// EUSART baudrate equation :
#define EUSART_ASYNC_HIGH_SPEED  1
#define EUSART_ASYNC_LOW_SPEED   0
// EUSART baudrate equation :
#define EUSART_16BIT_BAUDRATE_REG_SIZE   1
#define EUSART_08BIT_BAUDRATE_REG_SIZE   0

// TX configuartions :-
// TX enable :
#define EUSART_ASYNC_TX_ENABLE  1
#define EUSART_ASYNC_TX_DISABLE 0
// TX interrupt enable :
#define EUSART_ASYNC_TX_INTERRUPT_ENABLE  1
#define EUSART_ASYNC_TX_INTERRUPT_DISABLE 0
// TX 9bit enable :
#define EUSART_ASYNC_TX_9BIT_ENABLE  1
#define EUSART_ASYNC_TX_9BIT_DISABLE 0

// RX configuartions :-
// RX enable :
#define EUSART_ASYNC_RX_ENABLE  1
#define EUSART_ASYNC_RX_DISABLE 0
// RX interrupt enable :
#define EUSART_ASYNC_RX_INTERRUPT_ENABLE  1
#define EUSART_ASYNC_RX_INTERRUPT_DISABLE 0
// RX 9bit enable :
#define EUSART_ASYNC_RX_9BIT_ENABLE  1
#define EUSART_ASYNC_RX_9BIT_DISABLE 0

// Error status :-
// framing error detected :
#define EUSART_FRAMING_ERROR_DETECTED  1
#define EUSART_FRAMING_ERROR_CLEARD    0
// overrun error detected :
#define EUSART_OVERRUN_ERROR_DETECTED  1
#define EUSART_OVERRUN_ERROR_CLEARD    0

/* MACRO FUNTIONS DECLARATIONS */


/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */

typedef enum {
    BUADRATE_ASYNC_8BIT_LOW_SPEED = 0,
    BUADRATE_ASYNC_8BIT_HIGH_SPEED,
    BUADRATE_ASYNC_16BIT_LOW_SPEED,
    BUADRATE_ASYNC_16BIT_HIGH_SPEED,
    BUADRATE_SYNC_8BIT,
    BUADRATE_SYNC_16BIT
}eusart_baudrate_equation_t;


typedef union {
    struct {
        uint8                 eusart_reserved      : 6;
        uint8                 eusart_ferr          : 1;
        uint8                 eusart_oerr          : 1;
    };
    uint8                     eusart_error_status;
}eusart_error_status_t;



typedef struct {
    interrupt_priority_cfg  eusart_tx_interrupt_priority;
    uint8                   eusart_tx_reserved          : 5;
    uint8                   eusart_tx_enable            : 1;
    uint8                   eusart_tx_interrupt_enable  : 1;
    uint8                   eusart_tx_9bit_enable       : 1;
}eusart_Tx_cfg_t;


typedef struct {
    interrupt_priority_cfg  eusart_rx_interrupt_priority;
    uint8                   eusart_rx_reserved          : 5;
    uint8                   eusart_rx_enable            : 1;
    uint8                   eusart_rx_interrupt_enable  : 1; 
    uint8                   eusart_rx_9bit_enable       : 1;
}eusart_Rx_cfg_t;


typedef struct {
    uint32                         eusart_baudrate_value;
    eusart_baudrate_equation_t     eusart_baudrate_equation_select;
    eusart_Tx_cfg_t                eusart_tx_cfg;
    eusart_Rx_cfg_t                eusart_rx_cfg;
    eusart_error_status_t          eusart_error_status;
    void (*eusart_tx_isr)(void);
    void (*eusart_rx_isr)(void);
    void (*eusart_framing_error_isr)(void);
    void (*eusart_overrun_error_isr)(void);
}eusart_obj_t;

/* FUNTIONS DECLARATIONS */

Std_ReturnType EUSART_Async_Init  (const eusart_obj_t *eusart);
Std_ReturnType EUSART_Async_DeInit(const eusart_obj_t *eusart);

Std_ReturnType EUSART_ReadByte_blocking    (uint8 *data);
Std_ReturnType EUSART_ReadByte_nonblocking (uint8 *data);
Std_ReturnType EUSART_Async_RX_Restart(void);              // restart the RX module to clear the OERR flae
// FERR flage is celared by reading the RCREG flage

Std_ReturnType EUSART_WriteByte_blocking     (uint8 data);
Std_ReturnType EUSART_WriteString_blocking   (uint8 *data, uint32 str_len);
Std_ReturnType EUSART_WriteByte_Nonblocking  (uint8 data);
Std_ReturnType EUSART_WriteString_Nonblocking(uint8 *data, uint32 str_len);

