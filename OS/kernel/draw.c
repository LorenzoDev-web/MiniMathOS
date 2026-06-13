/* Boot Splash*/
#include "panic.h"
#include "../drivers/vga.h"
#include "../drivers/io.h"
#include "../drivers/keyboard.h"
#include "idt.h"

#define TOTAL_MODULES 4

static int loaded_modules = 0;


void ksleep(unsigned int ticks)
{
    while (ticks--) {
        for (volatile unsigned int i = 0; i < 1000000U; i++) {
            __asm__ volatile("nop");
        }
    }
}


void draw_progress(void)
{
    int percent = (loaded_modules * 100) / TOTAL_MODULES;
    int bars = percent / 5;

    print("\r[");

    for (int i = 0; i < 20; i++) {
        if (i < bars)
            print("#");
        else
            print("-");
    }

    print("] ");

    print_int(percent);
    print("%");
}

void module_ok(const char* name)
{
    print("[OK] ");
    print(name);
    print("\n");

    loaded_modules++;

    draw_progress();
    print("\n");
}

void module_loading(const char* name)
{
    print("[..] ");
    print(name);
    print("\n");
}

void module_fail(const char* name)
{
    print("[FAIL] ");
    print(name);
    print("\n");

    panic("Boot failed");
}

void verify_err(void) {
    if(!idt_ready()) {
        module_fail("IDT");
    }
    if(!panic_ready()) {
        reboot();
    }
    if(!keyboard_ready()) {
        module_fail("KEYBOARD");
    }
}

void verify_pass(void) {
    if(idt_ready()) {
        module_ok("IDT");
    }
    ksleep(4);
    if(panic_ready()) {
        module_ok("PANIC");
    }
    ksleep(3);
    if(keyboard_ready()) {
        module_ok("KEYBOARD");
    }
    ksleep(5);
}
