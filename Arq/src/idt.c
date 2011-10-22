#include <defs.h>


DESCR_INT[256] idt;
IDTR idtr;

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}

/* This exists in 'start.asm', and is used to load our IDT */
extern void idt_load();

