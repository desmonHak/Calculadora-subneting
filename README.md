# Calculadora-subneting

----
 Calculadora de subneting creada en C.

----
### Compilar en Windows con:

```batch bach
nasm -f elf -o AndOperation.o AndOperation.asm
gcc -m32 -o calc.exe calc.c AndOperation.o
```
y ejecutar con
```batch bach
.\calc.exe
```
### Compilar en Linux con:

```batch bach
nasm -f elf -o AndOperation.o AndOperation.asm
gcc -m32 -o calc.bin calc.c AndOperation.o
```
y ejecutar con
```batch bach
./calc.bin
```