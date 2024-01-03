
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
#include "hardware/sync.h"

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
*       button::button (constructor)
*
*   DESCRIPTION:
*       button class cons
*
*********************************************************************/
component::button::button
    (
    uint button_port, 
    uint light_port, 
    bool interruptDriven, 
    gpio_irq_level edge 
    )
{
/*----------------------------------------------------------
Assert if edge level is incorrectly setup
----------------------------------------------------------*/
if( edge != GPIO_IRQ_EDGE_RISE && edge != GPIO_IRQ_EDGE_FALL )
    static_assert(true, "IRQ edge selected is not a valid edge and will result in IRQ being triggered repeatedly");

/*----------------------------------------------------------
Set local variables up
----------------------------------------------------------*/
p_pButton               = button_port;
p_pLight                = light_port;
this->p_interruptDriven = interruptDriven;

/*----------------------------------------------------------
Setup in/out ports
----------------------------------------------------------*/
gpio_init( p_pButton );
gpio_init( p_pLight );
gpio_set_dir( p_pLight, GPIO_OUT );
gpio_set_dir( p_pButton, GPIO_IN );

/*----------------------------------------------------------
Enable a pull up resister on the button input. It is assumed
the button is connected to GND
----------------------------------------------------------*/
gpio_pull_up( p_pButton );

/*----------------------------------------------------------
Set light output strength to 12ma
----------------------------------------------------------*/
gpio_set_drive_strength( p_pLight, GPIO_DRIVE_STRENGTH_12MA );

/*----------------------------------------------------------
If interrupt driven is selected, enable the IRQ on the
GPIO input
----------------------------------------------------------*/
if( interruptDriven )
    gpio_set_irq_enabled( p_pButton, edge, true );

} /* button::button() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       button::~button (deconstructor)
*
*   DESCRIPTION:
*       button class deconstructor
*
*********************************************************************/
component::button::~button
    (
    void
    )
{
} /* button::~button() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       button::setLight()
*
*   DESCRIPTION:
*       sets the button light on or off
*
*********************************************************************/
void component::button::setLight
    (
    bool mode 
    )
{
/*----------------------------------------------------------
Set light on/off depending on input
----------------------------------------------------------*/
gpio_put( p_pLight, mode );

} /* button::setLight() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       button::isPushed()
*
*   DESCRIPTION:
*       returns if button is currently pushed or not
*
*********************************************************************/
bool component::button::isPushed
    ( 
    void 
    )
{
return gpio_get( p_pButton );

} /*button::isPushed() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       button::int_pushed()
*
*   DESCRIPTION:
*       interrupt handler for button.
*
*   NOTE: this is only used when interrupts have been selected on
*
*********************************************************************/
void component::button::int_pushed
    ( 
    void 
    )
{
/*----------------------------------------------------------
Only process if interrupts are enabled
----------------------------------------------------------*/
if( p_interruptDriven )
    p_wasPushed++;

} /*button::int_pushed() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       button::was_pushed()
*
*   DESCRIPTION:
*       user call to detect if an interrupt button push has occoured
*
*   NOTE: this is only used when interrupts have been selected on
*
*********************************************************************/
bool component::button::wasPushed
    (
    void 
    )
{
/*----------------------------------------------------------
local variables
----------------------------------------------------------*/
uint32_t int_status;

/*----------------------------------------------------------
Exit if no button pushes have been recorded
----------------------------------------------------------*/
if( p_wasPushed < 1 )
    return false;

/*----------------------------------------------------------
Disable/Re-enable interrupts while reseting value
----------------------------------------------------------*/
int_status = save_and_disable_interrupts();
p_wasPushed = 0;
restore_interrupts( int_status );

/*----------------------------------------------------------
return true since prevously button push was reported
----------------------------------------------------------*/
return true;

} /* button::wasPushed() */