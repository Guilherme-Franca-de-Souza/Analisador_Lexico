#ifndef ANALEX      
#define ANALEX 
#define TAM_MAX_LEXEMA 31 

enum TOKEN_CAT {
    // IDENTIFICADOR
    ID=1,

    // SINAIS
    SN,

    // CONSTANTES
    CT_I, CT_R

    // FIM DO ARQUIVO  
    FIM_ARQ
    }; 

/* Onde: ID: Identificador, SN: Sinal; CT_I: Constante numérica inteira; CT_R: Constante numérica real*/ 

 

enum SINAIS {
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


}; // Sinais válidos da linguagem 

 

typedef 
    struct {  
        enum TOKEN_CAT cat;    // deve receber uma das constantes de enum TOKEN_CAT 
        union {     // parte variável do registro 
            int codigo;  // para tokens das categorias SN 
            char lexema[TAM_MAX_LEXEMA];  // cadeia de caractares que corresponde o nome do token da cat. ID 
            int valInt; // valor da constante ineira em tokens da cat. CT_I 
        }; 
    } TOKEN;    // Tipo TOKEN 
    
#endif 