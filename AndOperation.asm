global _andOperation

_andOperation:

    push ebp
    mov  ebp, esp

    mov eax, [ebp+8]
    mov ebx, [ebp+12]
    and eax, ebx 

    add esp, 8
    xor ebx, ebx

    mov esp, ebp
    pop ebp
    ret