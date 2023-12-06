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
enum struct edge {
    rising_edge,
    lowering_edge,
};
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
        button( uint button_port, edge direction, uint light_port, bool interruptDriven );
        ~button();
        //delete copy constructor
        void setLight( bool on );
        bool isPushed( void );
    private:
        uint pButton;
        uint pLight;
        bool interruptDriven;
        void interruptHandler( void );
    };




} /* component namespace */
#endif