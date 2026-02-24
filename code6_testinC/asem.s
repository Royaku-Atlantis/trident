.global _start
.intel_syntax noprefix

_start:
        //sys exit
        mov rax, 60
        mov rdi, 69
        syscall