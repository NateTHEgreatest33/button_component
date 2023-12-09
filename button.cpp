
/*********************************************************************
*
*   NAME:
*       button.cpp
*
*   DESCRIPTION:
*       API for interfacing with the big red button
*
*   Copyright 2023 Nate Lenze
*
*********************************************************************/

/*--------------------------------------------------------------------
                              INCLUDES
--------------------------------------------------------------------*/
#include "button.hpp"
#include "hardware/gpio.h"
#include "hardware/timer.h"

/*--------------------------------------------------------------------
                          GLOBAL NAMESPACES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/
#define MICRO_TO_MS( micro_s )( (micro_s) / 1000 )
/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/
/*--------------------------------------------------------------------
component::button() 
--------------------------------------------------------------------*/
/*********************************************************************
*
*   PROCEDURE NAME:
*       component::button (constructor)
*
*   DESCRIPTION:
*       button class cons
*
*********************************************************************/
component::button::button( uint button_port, uint light_port, bool interruptDriven, gpio_irq_level edge = GPIO_IRQ_EDGE_RISE )
    {
    if( edge != GPIO_IRQ_EDGE_RISE && edge != GPIO_IRQ_EDGE_FALL )
        static_assert(true, "IRQ edge selected is not a valid edge and will result in IRQ being triggered repeatedly");

    p_pButton = button_port;
    p_pLight = light_port;
    this->p_interruptDriven = interruptDriven;

    gpio_init( p_pButton );
    gpio_init( p_pLight );
    gpio_set_dir( p_pLight, GPIO_OUT );
    gpio_set_dir( p_pButton, GPIO_IN );
    gpio_pull_up( p_pButton ); //when button is connected to GND
    // gpio_pull_down( p_pButton ); //when button is connected to 3.3v

    gpio_set_drive_strength( p_pLight, GPIO_DRIVE_STRENGTH_12MA );

    // gpio_set_input_hysteresis_enabled( p_pButton, true );
    gpio_set_slew_rate( p_pButton, GPIO_SLEW_RATE_SLOW);

    if( interruptDriven )
        gpio_set_irq_enabled( p_pButton, edge, true );


    

    }

/*********************************************************************
*
*   PROCEDURE NAME:
*       component::~button (deconstructor)
*
*   DESCRIPTION:
*       button class deconstructor
*
*********************************************************************/
component::button::~button(){}

/*********************************************************************
*
*   PROCEDURE NAME:
*       component::setLight()
*
*   DESCRIPTION:
*       sets the button light on or off
*
*********************************************************************/
void component::button::setLight( bool on )
    {
    gpio_put( p_pLight, on );
    }

/*********************************************************************
*
*   PROCEDURE NAME:
*       component::isPushed()
*
*   DESCRIPTION:
*       returns if button is currently pushed or not
*
*********************************************************************/
bool component::button::isPushed( void )
    {
    return gpio_get( p_pButton );
    }



void component::button::interruptHandler( void ){}


void component::button::int_pushed( void )
    {
    if( p_interruptDriven )
        p_wasPushed++;
    }

bool component::button::wasPushed( void )
    {
    
        static_assert( (p_interruptDriven != true), "wasPushed is only supported if interrupts are used");

    if( p_wasPushed < 1 )
        return false;
    
    uint32_t int_status = save_and_disable_interrupts();
    p_wasPushed = 0;

    restore_interrupts( int_status );

    return true;
    
    
    }