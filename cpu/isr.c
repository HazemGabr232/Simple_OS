#include <stdint.h>
#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../kernel/util.h"

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
}
