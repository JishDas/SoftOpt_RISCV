// rdcycle.h
#ifndef RDCYCLE_H
#define RDCYCLE_H

static inline unsigned long long rdcycle() {
    unsigned long long cycles;
    asm volatile ("rdcycle %0" : "=r"(cycles));
    return cycles;
}

#endif