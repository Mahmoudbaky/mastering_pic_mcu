/* 
 * File:   mcal_external_interrupt.c
 * Author: houda
 *
 * Created on February 26, 2024, 6:15 PM
 */

#include "mcal_external_interrupt.h"

/* FUNTIONS DECLARATIONS */

static Std_ReturnType Interrupt_INTx_Enable       (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable      (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init    (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init     (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag   (const interrupt_INTx_t *int_obj);

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
        /* Configure External interrupt I/O pin */
        ret = Interrupt_INTx_Pin_Init(int_obj);
        /* Configure Default Interrupt CallBack */
        
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

/***************helper functions for INTx**************/

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; 
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptEnable();
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptEnable();
                break;       
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
                EXT_INT0_InterruptDisable();
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT0_InterruptDisable();
                break;  
        }
    }
    return ret;
}

#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE_FEATURE
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
                if     (INTERRUPT_LOW_PRIORITY  == int_obj->edge){EXT_INT1_FallingEdgeSet();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->edge){EXT_INT1_RisingEdgeSet();}
                else                                                 {/* nothing */}
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                if     (INTERRUPT_LOW_PRIORITY  == int_obj->edge){EXT_INT2_FallingEdgeSet();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->edge){EXT_INT2_RisingEdgeSet();}
                else                                                 {/* nothing */}
                break;   
        }
    }
}

static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        ret = gpio_pin_direction_initialization(&(int_obj->mcu_pin));
    }
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
        }
    }
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
