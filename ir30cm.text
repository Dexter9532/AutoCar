#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// 🛠 UART settings for serial output
void uart_init(void) {
    uint16_t baud_rate = 103; // 9600 baud for 16 MHz clock
    UBRR0H = (uint8_t)(baud_rate >> 8); // Set high byte of baud rate
    UBRR0L = (uint8_t)baud_rate; // Set low byte of baud rate
    UCSR0B = (1 << TXEN0); // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Set frame format: 8 data bits, 1 stop bit
}

// 🛠 Function to send a character via UART
int uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar('\r', stream); // Fix for new line
    }
    while (!(UCSR0A & (1 << UDRE0))); // Wait until buffer is empty
    UDR0 = c; // Send character
    return 0;
}

// 🛠 Create standard output to UART
FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

// 🛠 Initialize ADC (Analog to Digital Converter)
void adc_init(void) {
    ADMUX = (1 << REFS0); // Use AVCC (5V) as reference
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, set prescaler to 128
}

// 🛠 Function to read from ADC
uint16_t adc_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Select channel
    ADCSRA |= (1 << ADSC); // Start conversion
    while (ADCSRA & (1 << ADSC)); // Wait until conversion is complete
    return ADC; // Return ADC value
}

// 🛠 Function to convert ADC value to distance (example conversion)
float adc_to_distance(uint16_t adc_value) {
    // Example conversion: assuming a linear relationship between ADC value and distance
    // Adjust the conversion formula based on your sensor's characteristics
    float voltage = adc_value * (5.0 / 1023.0); // Convert ADC value to voltage
    float distance = voltage * 10; // Example conversion: 1V = 10 meters (adjust as needed)
    return distance;
}

// 🛠 Setup function (like `void setup()` in Arduino)
void setup() {
    uart_init();
    stdout = &uart_output; // Set standard output to UART
    adc_init();
}

// 🛠 Main program
int main(void) {
    setup();

    while (1) {
        uint16_t sensorValue = adc_read(4); // Read from A4 (PC4)
        printf("ADC Value: %d\n", sensorValue); // Debug print for ADC value

        float voltage = sensorValue * (5.0 / 1023.0); // Convert ADC value to voltage
        printf("Voltage: %.2f V\n", voltage); // Debug print for voltage

        float distance = adc_to_distance(sensorValue); // Convert ADC value to distance
        printf("Distance: %.2f meters\n", distance); // Print distance to Serial Monitor

        _delay_ms(500); // Wait 500ms before next measurement
    }

    return 0;
}
