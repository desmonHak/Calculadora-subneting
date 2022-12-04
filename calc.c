#include <stdio.h>
#include <stdint.h>
//#include <stdbool.h>
//#include <stdlib.h>
#include <math.h>
// nasm -f elf -o AndOperation.o AndOperation.asm
// gcc -m32 -o calc.exe calc.c AndOperation.o

extern uint32_t andOperation(uint32_t a, uint32_t b);

/*
#define CALC_SIZE_TYPE_DATA(TypeBin) sizeof(TypeBin)*8
#define CREATE_BINARY_VAR(NameVar, TypeBin) bool NameVar[CALC_SIZE_TYPE_DATA(TypeBin)];

void *PrintBinaryNumber(bool *number, uint8_t TypeBin)
{
    for (uint8_t i = 0; i < TypeBin; i++)
    {
        if (number[i] != 0b0 && number[i] != 0b1)
        {
            number[i] = 0b0;
        }
        printf("%hhd", number[i]);
    }
    return 0;
}

void *clearBinaryVar(bool *Var, uint8_t TypeBin){
    for (uint8_t i = 0; i < TypeBin; i++)
    {
        Var[i] = 0b0;
    }
    
}

void *decToBinary(uint8_t value, bool *output, uint8_t i)
{
    if (value == 0b0)
    {
        return 0;
    }
    //printf("->%d\n", value % 2);
    output[i-1] = value % 2;
    //printf("%hhd:%hhd, ", value, i);
    decToBinary(value / 2, output, i - 1);
}
*/
typedef struct IPv4
{
    uint8_t octeto[4];
    uint8_t netMask;
} IPv4;

int main()
{
    /*
        IP Address:	32.10.10.10
        Network Address:	32.10.10.0
        Usable Host IP Range:	32.10.10.1 - 32.10.11.254
        Broadcast Address:	32.10.11.255
        Total Number of Hosts:	512
        Number of Usable Hosts:	510
        Subnet Mask:	255.255.254.0
        Wildcard Mask:	0.0.1.255
        Binary Subnet Mask:	11111111.11111111.11111110.00000000
        IP Class:	B
        CIDR Notation:	/23
        IP Type:	Public
        
        Short:	32.10.10.10 /23
        Binary ID:	00100000000010100000101000001010
        Integer ID:	537528842
        Hex ID:	0x200a0a0a
        in-addr.arpa:	10.10.10.32.in-addr.arpa
        IPv4 Mapped Address:	::ffff:200a.0a0a
        6to4 Prefix:	2002:200a.0a0a::/48
    */
    // 32.10.10.10/23 
    // 0010 0000.0000 1010.0000 1010.0000 1010
    // 1111 1111 1111 1111 1111 1110 0000 0000
    IPv4 HostCalc; //= { {0,0,0,0}, 0x00 };

    printf("Ingrese una direcion Ip: ");
    scanf("%hhd.%hhd.%hhd.%hhd/%hhd", HostCalc.octeto, HostCalc.octeto + 1,
          HostCalc.octeto + 2, HostCalc.octeto + 3, &HostCalc.netMask);

    printf("\t Direcion ip ingresada -> %d.%d.%d.%d/%d\n", HostCalc.octeto[0],
           HostCalc.octeto[1], HostCalc.octeto[2], HostCalc.octeto[3], HostCalc.netMask);


    uint32_t CantidadDeIPs = pow(2, (32-HostCalc.netMask));

    uint32_t NetMask =  pow(2, 32)-(CantidadDeIPs);
    printf ("Mascara de red en valor decimal: %hhd\n", NetMask);

    IPv4 NetMaskIP;
    NetMaskIP.octeto[3] = (NetMask >> 24);
    NetMaskIP.octeto[2] = (NetMask >> 16);
    NetMaskIP.octeto[1] = (NetMask >> 8);
    NetMaskIP.octeto[0] = (NetMask >> 0);
    printf("Direcion IP de la mascara de red: %hhd.%hhd.%hhd.%hhd\n",NetMaskIP.octeto[3], NetMaskIP.octeto[2],NetMaskIP.octeto[1], NetMaskIP.octeto[0]);
    
    uint8_t bytesNetMask = HostCalc.netMask/8;
    uint8_t BitsResultNetMask = HostCalc.netMask-(bytesNetMask*8);
    printf ("Cantidad total de octetos con valor 0xff: %hhd\n", bytesNetMask);
    printf ("Cantidad de bits restantes de con valor 1: %hhd\n", BitsResultNetMask);
    printf ("Cantidad de bits restantes de con valor 0: %hhd\n", 32-BitsResultNetMask-(bytesNetMask*8));

    uint32_t addr = (uint32_t) ((HostCalc.octeto[0] << 24) | (HostCalc.octeto[1] << 16) | (HostCalc.octeto[2] << 8) | HostCalc.octeto[3]); 
    printf ("Valor decimal de la direcion IP identicador de red: %d\n", addr);

    uint32_t DirecionDeRed = andOperation(addr, NetMask);
    printf("Aplicando la operacion AND: %d\n", DirecionDeRed);

    IPv4 DirecionDeRedIP;
    DirecionDeRedIP.octeto[3] = (DirecionDeRed >> 24);
    DirecionDeRedIP.octeto[2] = (DirecionDeRed >> 16);
    DirecionDeRedIP.octeto[1] = (DirecionDeRed >> 8);
    DirecionDeRedIP.octeto[0] = (DirecionDeRed >> 0);
    printf("Direcion IP despues de aplicar AND a la direcion ip de identificador de red: %hhd.%hhd.%hhd.%hhd\n",DirecionDeRedIP.octeto[3], DirecionDeRedIP.octeto[2],DirecionDeRedIP.octeto[1], DirecionDeRedIP.octeto[0]);

    uint32_t broadcast = DirecionDeRed + CantidadDeIPs-1;
    printf ("Valor decimal de la direcion IP bdroadcast: %d\n", addr);

    IPv4 broadcastIP;
    broadcastIP.octeto[3] = (broadcast >> 24);
    broadcastIP.octeto[2] = (broadcast >> 16);
    broadcastIP.octeto[1] = (broadcast >> 8);
    broadcastIP.octeto[0] = (broadcast >> 0);
    printf("Direcion IP de broadcast: %hhd.%hhd.%hhd.%hhd\n",broadcastIP.octeto[3], broadcastIP.octeto[2],broadcastIP.octeto[1], broadcastIP.octeto[0]);
    printf("Rango Ip disponible:  %hhd.%hhd.%hhd.%hhd-%hhd.%hhd.%hhd.%hhd\n",broadcastIP.octeto[3], broadcastIP.octeto[2],broadcastIP.octeto[1], broadcastIP.octeto[0]-1, DirecionDeRedIP.octeto[3], DirecionDeRedIP.octeto[2],DirecionDeRedIP.octeto[1], DirecionDeRedIP.octeto[0]+1);
    printf("Cantidad maxima de dispositivos para la red: %d", CantidadDeIPs-2);

    //uint32_t broadcast = addr & ;
    //IPv4 broadcastIP

    /*
    CREATE_BINARY_VAR(num, uint8_t);
    for (uint8_t i = 0; i < 4; i++){
        printf("-> 0x%x -> 0x%x\n",HostCalc.octeto[i], andOperation(HostCalc.octeto[i], 0b11110000));
        decToBinary(HostCalc.octeto[i], num, CALC_SIZE_TYPE_DATA(uint8_t));
        PrintBinaryNumber(num, CALC_SIZE_TYPE_DATA(uint8_t));
        putchar('\n');
        clearBinaryVar(num, CALC_SIZE_TYPE_DATA(uint8_t));
    }
    printf("/");
    decToBinary(HostCalc.netMask, num, CALC_SIZE_TYPE_DATA(uint8_t));
    PrintBinaryNumber(num, CALC_SIZE_TYPE_DATA(uint8_t));
    clearBinaryVar(num, CALC_SIZE_TYPE_DATA(uint8_t));
    printf("\n");
    */

    return 0;
}