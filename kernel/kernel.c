#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"

void main() {
    isr_install();
    /* Test the interrupts */

    asm volatile("sti");
    init_timer(50);
}
