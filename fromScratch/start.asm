; This is the kernel's entry point. We could either call main here,
; or we can use this to setup the stack or other nice stuff, like
; perhaps setting up the GDT and segments. Please note that interrupts
; are disabled at this point: More on interrupts later!
[BITS 32]
global start
start:
    mov esp, _sys_stack     ; This points the stack to our new stack area
    jmp stublet
    

; This part MUST be 4byte aligned, so we solve that issue using 'ALIGN 4'
ALIGN 4
mboot:
    ; Multiboot macros to make a few lines later more readable
    MULTIBOOT_PAGE_ALIGN	equ 1<<0
    MULTIBOOT_MEMORY_INFO	equ 1<<1
    MULTIBOOT_AOUT_KLUDGE	equ 1<<16
    MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
    EXTERN code, bss, end

    ; This is the GRUB Multiboot header. A boot signature
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM
    
    ; AOUT kludge - must be physical addresses. Make a note of these:
    ; The linker script fills in the data for these ones!
    dd mboot
    dd code
    dd bss
    dd end
    dd start

; This is an endless loop here. Make a note of this: Later on, we
; will insert an 'extern _main', followed by 'call _main', right
; before the 'jmp $'.
stublet:
	extern _main
    call _main
    jmp $


; Shortly we will add code for loading the GDT right here!


; In just a few pages in this tutorial, we will add our Interrupt
; Service Routines (ISRs) right here!



; Here is the definition of our BSS section. Right now, we'll use
; it just to store the stack. Remember that a stack actually grows
; downwards, so we declare the size of the data before declaring
; the identifier '_sys_stack'
SECTION .bss
    resb 8192               ; This reserves 8KBytes of memory here
_sys_stack:

; This will set up our new segment registers. We need to do
; something special in order to set CS. We do what is called a
; far jump. A jump that includes a segment as well as an offset.
; This is declared in C as 'extern void gdt_flush();'
global _gdt_flush     ; Allows the C code to link to this
extern _gp            ; Says that '_gp' is in another file
_gdt_flush:
    lgdt [_gp]        ; Load the GDT with our '_gp' which is a special pointer
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2   ; 0x08 is the offset to our code segment: Far jump!
flush2:
    ret               ; Returns back to the C code!

; Loads the IDT defined in '_idtp' into the processor.
; This is declared in C as 'extern void idt_load();'
global _idt_load
extern _idtp
_idt_load:
    lidt [_idtp]
    ret
; In just a few pages in this tutorial, we will add our Interrupt
; Service Routines (ISRs) right here!
global _isr0
global _isr1
global _isr2
...                ; Fill in the rest here!
global _isr30
global _isr31

;  0: Divide By Zero Exception
_isr0:
    cli
    push byte 0    ; A normal ISR stub that pops a dummy error code to keep a
                   ; uniform stack frame
    push byte 0
    jmp isr_common_stub

;  1: Debug Exception
_isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub
    
...                ; Fill in from 2 to 7 here!

;  8: Double Fault Exception (With Error Code!)
_isr8:
    cli
    push byte 8        ; Note that we DON'T push a value on the stack in this one!
                   ; It pushes one already! Use this type of stub for exceptions
                   ; that pop error codes!
    jmp isr_common_stub

...                ; You should fill in from _isr9 to _isr31 here. Remember to
                   ; use the correct stubs to handle error codes and push dummies!

; We call a C function in here. We need to let the assembler know
; that '_fault_handler' exists in another file
extern _fault_handler

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack
    push eax
    mov eax, _fault_handler
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!
; In just a few pages in this tutorial, we will add our Interrupt
; Service Routines (ISRs) right here!
global _isr0
global _isr1
global _isr2
...                ; Fill in the rest here!
global _isr30
global _isr31

;  0: Divide By Zero Exception
_isr0:
    cli
    push byte 0    ; A normal ISR stub that pops a dummy error code to keep a
                   ; uniform stack frame
    push byte 0
    jmp isr_common_stub

;  1: Debug Exception
_isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub
    
_isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub
    
_isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_stub
    
_isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_stub
    
_isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_stub
    
_isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_stub
    
_isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub

;  8: Double Fault Exception (With Error Code!)
_isr8:
    cli
    push byte 8        ; Note that we DON'T push a value on the stack in this one!
                   ; It pushes one already! Use this type of stub for exceptions
                   ; that pop error codes!
    jmp isr_common_stub

_isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_stub

_isr10:
    cli

    push byte 10
    jmp isr_common_stub

_isr11:
    cli

    push byte 11
    jmp isr_common_stub

_isr12:
    cli

    push byte 12
    jmp isr_common_stub

_isr13:
    cli

    push byte 13
    jmp isr_common_stub

_isr14:
    cli

    push byte 14
    jmp isr_common_stub

_isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_stub

_isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_stub

_isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common_stub

_isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_stub

_isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_stub

_isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_stub

_isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_stub

_isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_stub

_isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_stub

_isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_stub

_isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_stub

_isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_stub

_isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_stub

_isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_stub

_isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_stub

_isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_stub

_isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub


; We call a C function in here. We need to let the assembler know
; that '_fault_handler' exists in another file
extern _fault_handler

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack
    push eax
    mov eax, _fault_handler
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!
