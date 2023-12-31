#ifndef BUTTON_HPP
#define BUTTON_HPP
/*********************************************************************
*
*   HEADER:
*       header file for Button Component
*
*   Copyright 2023 Nate Lenze
*
****************a*****************************************************/
/*--------------------------------------------------------------------
                              INCLUDES
--------------------------------------------------------------------*/
#include "pico/stdlib.h"
/*--------------------------------------------------------------------
                          GLOBAL NAMESPACES
--------------------------------------------------------------------*/
namespace component {

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
                               CLASSES
--------------------------------------------------------------------*/
class button 
    {
    public:
        button( uint button_port, uint light_port, bool interruptDriven, gpio_irq_level edge = GPIO_IRQ_EDGE_RISE );
        ~button();

        void setLight( bool mode );
        bool isPushed( void );
        bool wasPushed( void );
        void int_pushed( void );

        button (const button&) = delete;
        button& operator= (const button&) = delete;

    private:
        uint p_pButton;
        uint p_pLight;
        bool p_interruptDriven;
        uint8_t p_wasPushed;
        uint32_t p_prevTime;

    };




} /* component namespace */
#endif