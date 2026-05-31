#include "../drivers/vga.h"
#include "../drivers/io.h"
#include "../drivers/keyboard.h"

extern void keyboard_poll();

void kernel_main() {

    clear();

    print("Mini Math OS\n");
    print("> ");

    while (1) {
        keyboard_poll();
    }
}
