#ifndef DBG_HEADER_H
#define DBG_HEADER_H

/*************************************
 * 
 *        AX8052 Debugging Header
 * 
 * CPU: AX8052
 * FREQ: 26MHz
 * 
 * ***********************************
*/
#include <ax8052.h>
#include <libmf.h>

void dbglink_irq(void) __interrupt(21) __naked
{
    // Add your code here
}

#endif // DBG_HEADER_H