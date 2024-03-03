/* 
 * File:   mcal_external_interrupt.c
 * Author: houda
 *
 * Created on February 26, 2024, 6:15 PM
 */

#include "mcal_external_interrupt.h"

/* FUNTIONS DECLARATIONS */

static void (*INT0_InterruptHandler)(void) = NULL;
static void (*INT1_InterruptHandler)(void) = NULL;
static void (*INT2_InterruptHandler)(void) = NULL;

static Std_ReturnType Interrupt_INTx_Enable       (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable      (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init    (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init     (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag   (const interrupt_INTx_t *int_obj);

static Std_ReturnType Interrupt_Choose_Handler(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INT0_MoveAddressFromStruct (void (*InterruptHandler)(void));
static Std_ReturnType Interrupt_INT1_MoveAddressFromStruct (void (*InterruptHandler)(void));
static Std_ReturnType Interrupt_INT2_MoveAddressFromStruct (void (*InterruptHandler)(void));

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);



/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init  (const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; 
    }
    else{
        /* Disable the External interrupt */
        ret = Interrupt_INTx_Disable(int_obj);
        /* Clear Interrupt Flag : External interrupt did not occur */
        ret = Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure External interrupt edge */
        ret = Interrupt_INTx_Edge_Init(int_obj);
        
        #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
        /* Configure External interrupt Priority */
        ret = Interrupt_INTx_Priority_Init(int_obj);
        #endif

        /* Configure External interrupt I/O pin */
        ret = Interrupt_INTx_Pin_Init(int_obj);
        /* Configure Default Interrupt CallBack */
        ret = Interrupt_Choose_Handler(int_obj);
        /* Enable the External interrupt */ 
        ret = Interrupt_INTx_Enable(int_obj);
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret;
}


void INT0_ISR (void){
    /* The INT0 external interrupt occurred (must be cleared in software) */
    EXT_INT0_InterruptFlagClear();
    /*   code    */
    
    /* Application Callback function gets called every time this ISR executes */
    if(INT0_InterruptHandler){ INT0_InterruptHandler(); }
    else{ /* Nothing */ }
}

void INT1_ISR (void){
    /* The INT1 external interrupt occurred (must be cleared in software) */
    EXT_INT1_InterruptFlagClear();
    /*   code    */
    
    /* Application Callback function gets called every time this ISR executes */
    if(INT1_InterruptHandler){ INT1_InterruptHandler(); }
    else{ /* Nothing */ }
}

void INT2_ISR (void){
    /* The INT2 external interrupt occurred (must be cleared in software) */
    EXT_INT2_InterruptFlagClear();
    /*   code    */
    
    /* Application Callback function gets called every time this ISR executes */
    if(INT2_InterruptHandler){ INT2_InterruptHandler(); }
    else{ /* Nothing */ }
}

/***************helper functions for INTx**************/

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; 
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                INTERRUPT_globalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                EXT_INT0_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                INTERRUPT_globalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                EXT_INT1_InterruptEnable();
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                INTERRUPT_globalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                EXT_INT2_InterruptEnable();
                break;
            default : ret = E_NOT_OK ;
        }
    }
    return ret;
}    

static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptDisable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptDisable();
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptDisable();
                break; 
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT1:
                if     (INTERRUPT_LOW_PRIORITY  == int_obj->priority){EXT_INT1_LowPrioritySet();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT1_HighPrioritySet();}
                else                                                 {/* nothing */}
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                if     (INTERRUPT_LOW_PRIORITY  == int_obj->priority){EXT_INT2_LowPrioritySet();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT2_HighPrioritySet();}
                else                                                 {/* nothing */}
                break;   
        }
    }
    return ret;
}
#endif

static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
    switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                if     (INTERRUPT_FALLING_EDGE  == int_obj->edge){EXT_INT0_FallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE   == int_obj->edge){EXT_INT0_RisingEdgeSet();}
                else                                                 {/* nothing */}
                break;    
            case INTERRUPT_EXTERNAL_INT1:
                if     (INTERRUPT_FALLING_EDGE   == int_obj->edge){EXT_INT1_FallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT1_RisingEdgeSet();}
                else                                                 {/* nothing */}
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                if     (INTERRUPT_FALLING_EDGE  == int_obj->edge){EXT_INT2_FallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT2_RisingEdgeSet();}
                else                                                 {/* nothing */}
                break;   
            default : ret = E_NOT_OK ;
        }
    }
    return ret ;
}

static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        ret = gpio_pin_direction_initialization(&(int_obj->mcu_pin));
    }
    return ret;
} 

static Std_ReturnType Interrupt_INTx_Clear_Flag   (const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptFlagClear();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptFlagClear();
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptFlagClear();
                break;
            default : ret = E_NOT_OK ;    
        }
    }
    return ret;
}

static Std_ReturnType Interrupt_INT0_MoveAddressFromStruct (void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        INT0_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType Interrupt_INT1_MoveAddressFromStruct (void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        INT1_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType Interrupt_INT2_MoveAddressFromStruct (void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        INT2_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType Interrupt_Choose_Handler(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                ret = Interrupt_INT0_MoveAddressFromStruct(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1:
                ret = Interrupt_INT1_MoveAddressFromStruct(int_obj->EXT_InterruptHandler);
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                ret = Interrupt_INT2_MoveAddressFromStruct(int_obj->EXT_InterruptHandler);
                break;
            default : ret = E_NOT_OK ;
        }
    }
    return ret;
}

/***************helper functions for INTx**************/

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init   (const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit (const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        
    }
    return ret;
}


/***************helper functions for RBx**************/

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj){

}

static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj){

}

static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj){

}

static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj){
}

/***************helper functions for RBx**************/
