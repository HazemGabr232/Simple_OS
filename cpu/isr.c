#include <stdint.h>
#include "isr.h"
#include "idt.h"
#include "ports.h"
#include "timer.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
#define PIC_EOI 	0x20


#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */



/*stores pointers to drivers handlers each one in the same index of it's number*/
isr_t interrupt_handlers[256];



void PIC_remap(u32 offset1, u32 offset2){ 

    u8 a1, a2;
 
    a1 = port_byte_in(PIC1_DATA);                        // save masks
    a2 = port_byte_in(PIC2_DATA);
 
    port_byte_out(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
    port_byte_out(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    port_byte_out(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
    port_byte_out(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
    port_byte_out(PIC1_DATA, 0x04);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    port_byte_out(PIC2_DATA, 0x02);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
    port_byte_out(PIC1_DATA, ICW4_8086);
    port_byte_out(PIC2_DATA, ICW4_8086);
 
    port_byte_out(PIC1_DATA, a1);   // restore saved masks.
    port_byte_out(PIC2_DATA, a2);
}

void isr_install() {
    set_idt_gate(0, (uintptr_t)isr0);
    set_idt_gate(1, (uintptr_t)isr1);
    set_idt_gate(2, (uintptr_t)isr2);
    set_idt_gate(3, (uintptr_t)isr3);
    set_idt_gate(4, (uintptr_t)isr4);
    set_idt_gate(5, (uintptr_t)isr5);
    set_idt_gate(6, (uintptr_t)isr6);
    set_idt_gate(7, (uintptr_t)isr7);
    set_idt_gate(8, (uintptr_t)isr8);
    set_idt_gate(9, (uintptr_t)isr9);
    set_idt_gate(10, (uintptr_t)isr10);
    set_idt_gate(11, (uintptr_t)isr11);
    set_idt_gate(12, (uintptr_t)isr12);
    set_idt_gate(13, (uintptr_t)isr13);
    set_idt_gate(14, (uintptr_t)isr14);
    set_idt_gate(15, (uintptr_t)isr15);
    set_idt_gate(16, (uintptr_t)isr16);
    set_idt_gate(17, (uintptr_t)isr17);
    set_idt_gate(18, (uintptr_t)isr18);
    set_idt_gate(19, (uintptr_t)isr19);
    set_idt_gate(20, (uintptr_t)isr20);
    set_idt_gate(21, (uintptr_t)isr21);
    set_idt_gate(22, (uintptr_t)isr22);
    set_idt_gate(23, (uintptr_t)isr23);
    set_idt_gate(24, (uintptr_t)isr24);
    set_idt_gate(25, (uintptr_t)isr25);
    set_idt_gate(26, (uintptr_t)isr26);
    set_idt_gate(27, (uintptr_t)isr27);
    set_idt_gate(28, (uintptr_t)isr28);
    set_idt_gate(29, (uintptr_t)isr29);
    set_idt_gate(30, (uintptr_t)isr30);
    set_idt_gate(31, (uintptr_t)isr31);

    // Remap the PIC
    PIC_remap(0x20, 0x28);

    // Install the IRQs
    set_idt_gate(32, (uintptr_t)irq0);
    set_idt_gate(33, (uintptr_t)irq1);
    set_idt_gate(34, (uintptr_t)irq2);
    set_idt_gate(35, (uintptr_t)irq3);
    set_idt_gate(36, (uintptr_t)irq4);
    set_idt_gate(37, (uintptr_t)irq5);
    set_idt_gate(38, (uintptr_t)irq6);
    set_idt_gate(39, (uintptr_t)irq7);
    set_idt_gate(40, (uintptr_t)irq8);
    set_idt_gate(41, (uintptr_t)irq9);
    set_idt_gate(42, (uintptr_t)irq10);
    set_idt_gate(43, (uintptr_t)irq11);
    set_idt_gate(44, (uintptr_t)irq12);
    set_idt_gate(45, (uintptr_t)irq13);
    set_idt_gate(46, (uintptr_t)irq14);
    set_idt_gate(47, (uintptr_t)irq15);


    set_idt(); // Load with ASM
}

/* To print the message which defines every exception */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t r) {
    kprint("received interrupt: ");
    char s[3];
    int_to_ascii(r.int_no, s);
    kprint(s);
    kprint("\n");
    kprint(exception_messages[r.int_no]);
    kprint("\n");
    
    /*TODO: handle CPU exceptions */
    /*if (interrupt_handlers[r.int_no] != 0) {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }*/
}

void add_interrupt_handler(u8 n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t r) {
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r.int_no >= 40) port_byte_out(PIC2_COMMAND, PIC_EOI); /* slave */
    port_byte_out(PIC1_COMMAND, PIC_EOI); /* master */

    /* Handle the interrupt in a more modular way */
    if (interrupt_handlers[r.int_no] != 0) {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }
}

void irq_install() {
    asm volatile("sti");
//    init_timer(50);
    init_keyboard();
}
