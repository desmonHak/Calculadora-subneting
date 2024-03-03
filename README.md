# Calculadora-subneting

----
 Calculadora de subneting creada en C.

----
### Compilar en Windows con:

```batch 
nasm -f elf -o AndOperation.o AndOperation.asm
gcc -m32 -o calc.exe calc.c AndOperation.o
```
y ejecutar con
```batch 
.\calc.exe
```
### Compilar en Linux con:

```bash
nasm -f elf -o AndOperation.o AndOperation.asm
gcc -m32 -o calc.bin calc.c AndOperation.o
```
y ejecutar con
```bash
./calc.bin
```
