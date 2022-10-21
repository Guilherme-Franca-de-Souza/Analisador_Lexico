#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <string.h>

#include "Analex.h" 

#define TAM_LEXEMA 50 
#define TAM_NUM 20 

 
void error(char msg[]) { 
    printf("%s\n", msg); 
    exit(1); 
} 

TOKEN AnaLex(FILE *fd) { 

    int estado; 
    char lexema[TAM_LEXEMA] = ""; 
    int tamL = 0; 
    char digitos[TAM_NUM] = ""; 
    int tamD = 0; 

    TOKEN t; 

    estado = 0; 


/*
            // SINAL DE ATRIBUIÇÃO
            ATRIB = 1,

            //OPERADORES ARITMETICOS 
            ADICAO, SUBTRACAO, MULTIPLIC,
            DIVISAO,
            
            //SINAIS DE PRECEDÊNCIA
            ABRE_PAR, FECHA_PAR, ABRE_COL,
            FECHA_COL, ABRE_CHA, FECHA_CHA,

            //OPERADORES RELACIONAIS
            IGUAL, DIFERENTE, NAO, MENOR_IGUAL,
            MENOR, MAIOR_IGUAL, MAIOR,   

            //OPERADORES LÓGICOS
            AND, OR

            //CHAR
            CHAR

            //STRING
            STRING
*/



    while (1) { 
        char c = fgetc(fd); 
        switch (estado) {
            case 0: if (c == ' ' || c == '\t' || c == '\n') estado = 0; 

                    else if (c >= 'a' && c <= 'z') {  // inicio de identificador - inicializa lexema 
                        estado = 1; 
                        lexema[tamL] = c;  
                        lexema[++tamL] = '\0'; 
                    } 

                    else if (c >= '1' && c <= '9') {  // inicio de constante inteira ou real- inicializa digitos 
                        estado = 3; 
                        digitos[tamD] = c;  
                        digitos[++tamD] = '\0';        
                    } 

                    else if (c == '+') {    // sinal de adicao - monta e devolve token 
                        estado = 8; 
                        t.cat = SN; 
                        t.codigo = ADICAO; 
                        return t; 

                    }

                    else if (c == '-') {    // sinal de subtracao - monta e devolve token 
                        estado = 8; 
                        t.cat = SN; 
                        t.codigo = SUBTRACAO; 
                        return t; 

                    }

                    else if (c == '*') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 10; 
                        t.cat = SN; 
                        t.codigo = MULTIPLICACAO; 
                        return t; 

                    }

                    else if (c == '/') {    // sinal de barra - inicializa divisão, mas também pode ser comentário
                        estado = 11; 
                    }

                    else if (c == '(') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 34; 
                        t.cat = SN; 
                        t.codigo = ABRE_PAR; 
                        return t; 

                    }
                    else if (c == ')') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 35; 
                        t.cat = SN; 
                        t.codigo = FECHA_PAR; 
                        return t; 

                    }

                    else if (c == '[') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 36; 
                        t.cat = SN; 
                        t.codigo = ABRE_COL; 
                        return t; 

                    }
                    else if (c == ']') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 37; 
                        t.cat = SN; 
                        t.codigo = FECHA_COL; 
                        return t; 

                    }

                    else if (c == '{') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 38; 
                        t.cat = SN; 
                        t.codigo = ABRE_CHA; 
                        return t; 

                    }
                    else if (c == '}') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 39; 
                        t.cat = SN; 
                        t.codigo = FECHA_CHA; 
                        return t; 

                    }

                    else if (c == '=') {    // sinal de igual pode ser sinal de atribuição ou sinal de igual
                        estado = 12; 
                    }

                    else if (c == '!') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 15; 
                    }

                    else if (c == '<') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 18; 
                    }

                    else if (c == '>') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 21; 
                    }

                    else if (c == '&') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 24; 
                    }

                    else if (c == '|') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 26; 
                    }

                    else if (c == '\'') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 28; 
                    }

                    else if (c == '"') {    // sinal de multiplicacao - monta e devolve token 
                        estado = 31; 
                    }

                    else if (c == EOF) {    // fim da expressao encontrado 
                           t.cat = FIM_ARQ; 
                           return t; 

                    } 
                    else   
                        error("Caracter invalido na expressao! estado 0");    // sem transicao valida no AFD 
                    break; 

            case 1: if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '_')) {    
                        estado = 1; 
                        lexema[tamL] = c;      // acumula caracteres lidos em lexema 
                        lexema[++tamL] = '\0'; 

                    } 

                    else {                     // transicao OUTRO* do estado 1 do AFD 
                        estado = 2;            // monta token identificador e retorna 
                        ungetc(c, fd); 
                        t.cat = ID; 
                        strcpy(t.lexema, lexema); 
                        return t; 

                    } 

                    break; 

            case 3:
                    if (c >= '0' && c <= '9') {
                        estado = 3; 
                        digitos[tamD] = c;       // acumula digitos lidos na variaavel digitos 
                        digitos[++tamD] = '\0'; 

                    }else if (c == '.'){
                        estado = 4;
                        digitos[tamD] = c;       // acumula digitos lidos na variaavel digitos 
                        digitos[++tamD] = '\0';    
                    }

                    else {                       // transicao OUTRO* do estado 10 do AFD 
                        estado = 6;             // monta token constante inteira e retorna 
                        ungetc(c, fd); 
                        t.cat = CT_I; 
                        t.valInt = atoi(digitos); 
                        return t; 
                    }
                    break; 
            case 4:
                    if(c >= '0' && c <= '9'){
                        estado = 5;
                        digitos[tamD] = c;       // acumula digitos lidos na variaavel digitos 
                        digitos[++tamD] = '\0'; 
                    }
                    else{   
                        error("Caracter invalido na expressao! estado 4");    // sem transicao valida no AFD
                    }
                    break;   
            case 5:
                    if(c >= '0' && c <= '9'){
                            estado = 5;
                            digitos[tamD] = c;       // acumula digitos lidos na variaavel digitos 
                            digitos[++tamD] = '\0'; 
                    }
                    else {                     // transicao OUTRO* do estado 1 do AFD 
                        estado = 7;            // monta token identificador e retorna 
                        ungetc(c, fd); 
                        t.cat = CT_R; 
                        t.valFloat = atof(digitos); 
                        return t; 
                    }
                    break;
            case 11:
                    if(c == '*'){
                        estado = 41;
                    }
                    else{
                        estado = 40; 
                        t.cat = SN; 
                        t.codigo = DIVISAO; 
                        return t; 
                    }
                    break;
            case 12:
                   if(c == '='){
                        estado = 13; 
                        t.cat = SN; 
                        t.codigo = IGUAL; 
                        return t; 
                    }
                    else{
                        estado = 14;
                        ungetc(c, fd); 
                        t.cat = SN; 
                        t.codigo = ATRIB; 
                        return t; 
                    }
                    break;
            case 15:
                   if(c == '='){
                        estado = 16; 
                        t.cat = SN; 
                        t.codigo = DIFERENTE; 
                        return t; 
                    }
                    else{
                        estado = 17;
                        ungetc(c, fd); 
                        t.cat = SN; 
                        t.codigo = NAO; 
                        return t; 
                    }
                    break;
            case 18:
                   if(c == '='){
                        estado = 19; 
                        t.cat = SN; 
                        t.codigo = MENOR_IGUAL; 
                        return t; 
                    }
                    else{
                        estado = 20;
                        ungetc(c, fd); 
                        t.cat = SN; 
                        t.codigo = MENOR; 
                        return t; 
                    }
                    break;
            case 21:
                   if(c == '='){
                        estado = 22; 
                        t.cat = SN; 
                        t.codigo = MAIOR_IGUAL; 
                        return t; 
                    }
                    else{
                        estado = 23; 
                        ungetc(c, fd);
                        t.cat = SN; 
                        t.codigo = MAIOR; 
                        return t; 
                    }
                    break;
            case 24:
                   if(c == '&'){
                        estado = 25; 
                        t.cat = SN; 
                        t.codigo = AND; 
                        return t; 
                    }
                    else{
                        error("Caracter invalido na expressao! estado 24");    // sem transicao valida no AFD 
                    }      
                    break;
            case 26:
                   if(c == '|'){
                        estado = 27; 
                        t.cat = SN; 
                        t.codigo = OR; 
                        return t; 
                    }
                    else{
                        error("Caracter invalido na expressao! estado 26");    // sem transicao valida no AFD 
                    } 
                    break;

            case 28:
                    if (c == '\'') {
                        estado = 29;
                        lexema[++tamL] = '\0';  
                        t.cat = CHAR; 
                        strcpy(t.lexema, lexema); 
                        return t; 
                    }else if (c >= ' ' && c <= '~'){
                        estado = 30;
                        lexema[tamL] = c;
                        lexema[++tamL] = '\0';   
                    }
                    break;
            case 30:
                    if (c == '\''){
                        estado = 29;
                        t.cat = CHAR; 
                        strcpy(t.lexema, lexema);
                        return t; 
                    }else{
                        error("Caracter invalido na expressao! estado 30");    // sem transicao valida no AFD 
                    }   
                        
                    break;
            
            case 31:
                    if (c == '"') {
                        estado = 33;
                        lexema[++tamL] = '\0';  
                        t.cat = STRING; 
                        strcpy(t.lexema, lexema); 
                        return t; 
                    }else if (c >= ' ' && c <= '~'){
                        estado = 32;
                        lexema[tamL] = c;
                        lexema[++tamL] = '\0';   
                    }
                    break;
            case 32:
                    if (c == '"'){
                        estado = 33;
                        t.cat = STRING; 
                        strcpy(t.lexema, lexema);
                        return t; 
                    }else{
                        estado = 32;
                        lexema[tamL] = c;
                        lexema[++tamL] = '\0'; 
                    }
                    break;
            case 41:
                    if (c == '*'){
                        estado = 42;
                    
                    }else if (c == EOF) {    // fim da expressao encontrado 
                           t.cat = FIM_ARQ; 
                           return t; 

                    }else{
                        estado = 41;
                    }
                    break;
            case 42:
                    if (c == '/'){
                        estado = 0;
                    }else if (c == EOF) {    // fim da expressao encontrado 
                           t.cat = FIM_ARQ; 
                           return t; 
                    } 
                    else{
                        estado = 41;
                    }
    
        }                     
    } 
} 

 

 

int main() { 

 
    FILE *fd; 

    TOKEN tk; 

 
    if ((fd=fopen("expressao.dat", "r")) == NULL) 

        error("Arquivo de entrada da expressao nao encontrado!"); 

    
    while (1) { 

        tk = AnaLex(fd); 

        switch (tk.cat) {

            case ID: printf("<ID, %s> ", tk.lexema); 
                     break;

            case CHAR: printf("<CHAR, %s> ", tk.lexema); 
                     break; 

            case STRING: printf("<STRING, %s> ", tk.lexema); 
                     break;

            case SN: switch (tk.codigo) { 

                        case ADICAO: printf("<SN, ADICAO> "); 
                        break; 

                        case SUBTRACAO: printf("<SN, SUBTRACAO> "); 
                        break; 

                        case MULTIPLICACAO: printf("<SN, MULTIPLICACAO> "); 
                        break; 

                        case DIVISAO: printf("<SN, DIVISAO> "); 
                        break;

                        case ATRIB: printf("<SN, ATRIBUICAO> "); 
                        break; 

                        case ABRE_PAR: printf("<SN, ABRE_PARENTESES> "); 
                        break; 

                        case FECHA_PAR: printf("<SN, FECHA_PARENTESES> "); 
                        break;

                        ///
                        case ABRE_COL: printf("<SN, ABRE_COLCHETES> "); 
                        break;

                        case FECHA_COL: printf("<SN, FECHA_COLCHETES> "); 
                        break;

                        case ABRE_CHA: printf("<SN, ABRE_CHAVES> "); 
                        break;

                        case FECHA_CHA: printf("<SN, FECHA_CHAVES> "); 
                        break;

                        case IGUAL: printf("<SN, IGUAL> "); 
                        break;

                        case DIFERENTE: printf("<SN, DIFERENTE> "); 
                        break;

                        case NAO: printf("<SN, NAO> "); 
                        break;

                        case MENOR_IGUAL: printf("<SN, MENOR OU IGUAL> "); 
                        break;

                        case MENOR: printf("<SN, MENOR> "); 
                        break;

                        case MAIOR_IGUAL: printf("<SN, MAIOR OU IGUAL> "); 
                        break;

                        case MAIOR: printf("<SN, MAIOR> "); 
                        break;

                        case AND: printf("<SN, AND> "); 
                        break;

                        case OR: printf("<SN, OR> "); 
                        break;     

                     } 

                     break; 

            case CT_I: printf("<CT_I, %d> ", tk.valInt); 

                       break;

            case CT_R: printf("<CT_R, %f> ", tk.valFloat); 

                       break; 

            case FIM_ARQ: printf("\nFim da expressao encontrado.\n"); 
        } 
        if (tk.cat == FIM_ARQ) break; 
    } 

    fclose(fd); 

    return 0; 
} 