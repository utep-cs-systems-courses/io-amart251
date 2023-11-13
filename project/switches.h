#ifndef switches_included
#define switches_included

#define SW1 BIT3                   // Switch1 is P1.3
#define SWITCHES SW1               // Only one switch on this board

void switch_init();
void switch_interrupt_handler();

extern char switch_state_down, switch_state_changed;

#endif // included
