
#include "pico/stdlib.h"

// GPIO pin for the button
#define BUTTON_PIN 15
// GPIO pin for the LED
#define LED_PIN 14

int main() {
    // Initialize the GPIO subsystem
    stdio_init_all();

    // Configure the LED pin as an output
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Configure the button pin as an input with a pull-up resistor
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);  // Enable internal pull-up resistor

    bool last_button_state = gpio_get(BUTTON_PIN); // Read initial button state
    bool button_present = false; // Flag to detect button presence

    printf("Detecting button presence...\n");

    while (true) {
        // Read the button state
        bool button_pressed = !gpio_get(BUTTON_PIN);  // Button is pressed when pin is LOW

        // If the state has changed, we assume the button is connected
        if (button_pressed != last_button_state) {
            button_present = true;
            printf("Button detected! State changed to: %s\n", button_pressed ? "PRESSED" : "RELEASED");
            last_button_state = button_pressed; // Update the last state
        }

        // Show a message if the button is pressed (low due to pull-up resistor)
        if (button_pressed) {
            printf("Button pin is LOW (pressed).\n");
            gpio_put(LED_PIN, 1);  // LED on
            printf("Button pressed, LED on.\n");
        } else {
            gpio_put(LED_PIN, 0);  // LED off
            printf("Button released, LED off.\n");
        }

        // If the button was never detected after several loops, assume it's missing
        if (!button_present) {
            printf("No button detected yet.\n");
        }

        // Small delay to debounce the button and avoid multiple state changes
        sleep_ms(200);
    }

    return 0;
}

