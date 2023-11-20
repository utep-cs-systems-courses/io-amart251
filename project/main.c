#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "switches.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (LED_RED | LED_GREEN)

#define SW1 BIT3                   // Switch is P1.3
#define SWITCHES SW1               // Only one switch on this board

// Function Prototypes
void initialize();
void init_led();
void init_buzzer();
void init_button();
void toggle_led();
void buzzer_set_period(short cycles);
void __interrupt_vec(WDT_VECTOR) WDT(); // Watchdog Timer interrupt
void __interrupt_vec(PORT1_VECTOR) Port_1(); // Button interrupt

// Global Variables
volatile int state = 0; // State variable

int main(void) {
    initialize();
    init_led();
    init_buzzer();
    init_button();

    __bis_SR_register(GIE); // Enable global interrupts

    while(1) {
        // Main loop - the work is done in interrupt handlers
    }
}

void initialize() {
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ; 
}

void init_led() {
    P1DIR |= LEDS; // Set LED pins as outputs
    P1OUT &= ~LEDS; // LEDs off
}

void init_buzzer() {
    // Buzzer initialization code here
    // Refer to the buzzer demo for details
}

void init_button() {
    P1REN |= SWITCHES; // Enable resistors for switches
    P1IE |= SWITCHES; // Enable interrupts from switches
    P1OUT |= SWITCHES; // Pull-ups for switches
    P1DIR &= ~SWITCHES; // Set switches' bits for input
}

void toggle_led() {
    // Toggle LED based on state
    if (state == 0) {
        P1OUT &= ~LED_GREEN;
        P1OUT |= LED_RED;
    } else {
        P1OUT &= ~LED_RED;
        P1OUT |= LED_GREEN;
    }
}

void buzzer_set_period(short cycles) {
    CCR0 = cycles; 
    CCR1 = cycles >> 1;		// one half cycle 
}

void __interrupt_vec(WDT_VECTOR) WDT() {
    // Watchdog Timer interrupt service routine
    // Change state or toggle LED/buzzer here
    toggle_led();
}

void __interrupt_vec(PORT1_VECTOR) Port_1() {
    if (P1IFG & SWITCHES) {
        P1IFG &= ~SWITCHES; // Clear interrupt flag
        state = !state; // Change state on button press
        toggle_led();
    }
}
