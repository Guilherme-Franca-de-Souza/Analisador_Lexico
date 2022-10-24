#ifndef ANALEX      
#define ANALEX 
#define TAM_MAX_LEXEMA 31 


enum TOKEN_CAT {
    // IDENTIFICADOR
    ID=1,

    //PALAVRA RESERVADA
    PR,

    // SINAIS
    SN,

    // CONSTANTES NUMÉRICAS
    CT_I, CT_R,

    //CHAR
    CT_C,

    //STRING    
    CT_L,

    // FIM DO ARQUIVO  
    FIM_ARQ
    }; 

/* Onde: ID: Identificador, SN: Sinal; CT_I: Constante numérica inteira; CT_R: Constante numérica real*/ 

enum PAL_RESERV {BOOL= 1,CHAR,CLASS,
                CODE,DATA,DELETE,
                ELSE,FLOAT,FOR,
                IF,INT,INTERN,
                MAIN,NEW,RETURN,
                VOID,WHILE, }; 

enum SINAIS {
            // SINAL DE ATRIBUIÇÃO
            ATRIB = 1,
            
            //SINAIS ESPECIAIS
            DOIS_PONTOS, PONTO_VIRGULA, CIRCUNFLEXO,
            //OPERADORES ARITMETICOS 
            ADICAO, SUBTRACAO, MULTIPLICACAO,
            DIVISAO,
            
            //SINAIS DE PRECEDÊNCIA
            ABRE_PAR, FECHA_PAR, ABRE_COL,
            FECHA_COL, ABRE_CHA, FECHA_CHA,

            //OPERADORES RELACIONAIS
            IGUAL, DIFERENTE, NAO, MENOR_IGUAL,
            MENOR, MAIOR_IGUAL, MAIOR,   

            //OPERADORES LÓGICOS
            AND, OR

}; // Sinais válidos da linguagem 

 

typedef 
    struct {  
        enum TOKEN_CAT cat;    // deve receber uma das constantes de enum TOKEN_CAT 
        union {     // parte variável do registro 
            int codigo;  // para tokens das categorias SN 
            char lexema[TAM_MAX_LEXEMA];  // cadeia de caractares que corresponde o nome do token da cat. ID, CHAR, ou STRING
            int valInt; // valor da constante ineira em tokens da cat. CT_I
            float valFloat; // valor da constante ineira em tokens da cat. CT_I  
        }; 
    } TOKEN;    // Tipo TOKEN 
    
#endif 