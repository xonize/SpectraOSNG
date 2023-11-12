#include <hardware/keyboard.h>
#include <stddef.h>
#include <serial/serial.h>
#include <kernel/kernel.h>
#include <qemu/output.h>

key_status keyboard_buffer[MAX_KEYB_BUFFER_SIZE];

// The array below contains the mappings of the hardware scancode into the kernel one.
// The kernel scancodes for now are the same of the scancode set 1 (but they can change in future)
key_codes scancode_mappings[] = {
0, ESCAPE, D1, D2, D3, D4, D5, D6, D7, D8, D9, D0, MINUS, EQUALS, BACKSPACE,
TAB, Q, W, E, R, T, Y, U, I, O, P, SQBRACKET_OPEN, SQBRACKET_CLOSE, ENTER,
LEFT_CTRL, A, S, D, F, G, H, J, K, L, SEMICOLON, SINGLE_QUOTE, BACK_TICK,
LEFT_SHIFT, SLASH, Z, X, C, V, B, N, M, COMMA, DOT, BACKSLASH, RIGHT_SHIFT,
KEYPAD_STAR, LEFT_ALT, SPACE, CAPS_LOCK,
F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, 
F11, F12, NUM_LOCK, SCROLL_LOCK,
KEYPAD_D7, KEYPAD_D8, KEYPAD_D9, KEYPAD_MINUS, KEYPAD_D4, KEYPAD_D5, KEYPAD_D6, KEYPAD_PLUS, KEYPAD_D1, KEYPAD_D2, KEYPAD_D3, KEYPAD_D0, KEYPAD_DOT,
};

// We are mapping the ascii symbols to the kernel scancodes
char keymap[] = {
0, ESCAPE, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
0, 'a', 's', 'd', 'f', 'g', 'h', 'j' , 'k', 'l', ';', '\'', '`',
0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
0, 0, ' ', 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0,
'7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.',
};

size_t buf_position;
uint8_t current_modifiers;
bool extended_read;

void init_keyboard() {
    // read keyboard to make sure its empty
    inb(KEYBOARD_ENCODER_PORT);
    // will read the scancode set used by the keyboard
    outb(KEYBOARD_ENCODER_PORT, 0xF0);
    outb(KEYBOARD_ENCODER_PORT, 0x00);
    current_modifiers = no_keys;
    uint8_t status_read = inb(KEYBOARD_ENCODER_PORT);

    if (status_read == KEYBOARD_ACK_BYTE) {
        status_read = inb(KEYBOARD_ENCODER_PORT);
        qemu_puts("Got scancode set\n");
        kernel_settings.keyboard.scancode_set = status_read;
    } else {
        qemu_puts("Unable to read from keyboard\n");
    }
}

void handle_keyboard_interrupt() {
    
}

char kgetch(key_status) {
    
}

key_codes translate(uint8_t) {

}