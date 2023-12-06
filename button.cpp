
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
component::button::button( uint button_port, edge direction, uint light_port, bool interruptDriven )
    {
    uint32_t edge_selected = ( direction == component::edge::rising_edge ) ? GPIO_IRQ_EDGE_RISE : GPIO_IRQ_EDGE_FALL;

    p_pButton = button_port;
    p_pLight = light_port;
    this->p_interruptDriven = interruptDriven;



    gpio_init( p_pButton );
    gpio_init( p_pLight );

    
    // gpio_set_pulls( pButton, true, false );
    // gpio_set_pulls( pButton, false, true );

    gpio_set_dir( p_pLight, GPIO_OUT );
    gpio_set_dir( p_pButton, GPIO_IN );

    gpio_pull_up( p_pButton );
    // gpio_set_pulls( pButton, true, false ); //when connected to groun
    // gpioSetPullUpDown( pButton, PI_PUD_UP); 

    gpio_set_drive_strength( p_pLight, GPIO_DRIVE_STRENGTH_12MA );

    if( interruptDriven )
        gpio_set_irq_enabled( p_pButton, edge_selected, true );

    

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

    if( !p_interruptDriven )
        return not( gpio_get( p_pButton ) );

    return false;
    }




void component::button::interruptHandler( void ){}