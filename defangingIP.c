#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Verifica se o octeto é um número entre 0 e 255
int checkOctet(char *octet){
    int isValid = 1;
    int octetAux = atoi(octet);

    if(strcmp(octet, "0") && !octetAux)      isValid = 0;
    else if(octetAux < 0 || octetAux > 255)  isValid = 0;

    return isValid;
}

//Verifica se o endereço de IP é válido
//Se possui 4 octetos e se o separador entre eles é o ponto.
int isAValidIpAddress(char *ip){
    char *octet, *p, *p2, *aux;
    int octetCnt, isValid;
    octetCnt = isValid = 0;

    p = strdup(ip);
    aux = p;
    while((p2 = strchr(p, '.'))){
        if(!octetCnt)   isValid = 1;
        *p2 = '\0';
        octet = strdup(p);
        isValid = checkOctet(octet);
        if(!isValid)    break;
        p2++;
        p = p2;
        free(octet);
        octetCnt++;

        if(octetCnt == 3){
            octet = strdup(p2);
            isValid = checkOctet(octet);
            if(!isValid)    break;
            free(octet);
            octetCnt++;
        }
    }
    free(aux);

    if(octetCnt < 4)    isValid = 0;

    return isValid;
}

void printResult(char *ip, int result){
    printf("IP Address: %s -> ", ip);
    if(result)  printf("It's valid.\n");
    else        printf("It's not valid.\n");
}

int main(){
    char *ip = "125.100.200.300";
    printResult(ip, isAValidIpAddress(ip));

    ip = "192.168.0.1";
    printResult(ip, isAValidIpAddress(ip));

    ip = "10.0.0.0";
    printResult(ip, isAValidIpAddress(ip));

    ip = "";
    printResult(ip, isAValidIpAddress(ip));

    ip = "123.256";
    printResult(ip, isAValidIpAddress(ip));

    ip = "127.0.0.1";
    printResult(ip, isAValidIpAddress(ip));

    ip = "a21.120.-250.wxz";
    printResult(ip, isAValidIpAddress(ip));

    ip = "127;0;0;1";
    printResult(ip, isAValidIpAddress(ip));

    ip = "0.0.0.0";
    printResult(ip, isAValidIpAddress(ip));

    ip = "255.255.255.255";
    printResult(ip, isAValidIpAddress(ip));

    return 0;
}
