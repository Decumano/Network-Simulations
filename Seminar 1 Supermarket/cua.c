/*
 * Programa exemple del funcionament d'una simulacio orientada en events
 * basada en el codi donat en el llibre Jorba, Capitol 2
 * 
 * LLibreria de funcions del sistema de cues
 * 
 * File:   cua.c
 * Author: Dolors Sala
 */

#include "./sev.h"
#include "./cua.h"

#define DEBUGcua 0  // Bandera per fer seguiment de la cua

static el_cua **cua; //cua cicular amb assignacio dinamica de memoria
static int max_cua; // capacitat maxima d'elements a la cua
static int max_cues; // capacitat maxima de cues
static int ini_cua[CUA_NUM]; // Primer element de la cua
static int fin_cua[CUA_NUM]; // ultim element de la cua
static int lon_cua[CUA_NUM]; // Quantitat d'elements a la cua

// Imprimeix element i de la cua circular
void imprimir_element_cua(el_cua *cua, int i){
    printf("%7.4lf ",cua[i].tar);
}
// Imprimeix la cua circular
void imprimir_cua(el_cua **cua){
    int i, f, j;
#if DEBUGcua == 1
    for (i = 0; i < max_cues; i++)
    {
        printf("Cua %d (I %2d,F %2d, L %2d): ", i+1, ini_cua[i], fin_cua[i], lon_cua[i]);
        if (fin_cua[i] >= ini_cua[i])
            f = fin_cua[i];
        else
            f = CUA_MAX-1;
    
        if(lon_cua[i] > 0){
            for (j = ini_cua[i]; j <= f; j++){
                printf("%7.4lf ",cua[i][j].tar);
            }
            if(f != fin_cua[i]){
                for (j = 0; j <= fin_cua[i]; j++){
                    imprimir_element_cua(cua[i], j);
                }
            }
        }
        
        printf("\n");
    }
#endif
}

// Crea un element de la cua
el_cua crea_element_cua(float tar){
    el_cua c;
    
    c.tar = tar;
    return(c);
}//crea_element_cua

// Crea una cua circular buida de capacitat per max_cua elements
void crea_cua(int max, int cues){
    max_cua = max;
    max_cues = cues;
    cua = (el_cua**) malloc( max_cues*sizeof(el_cua*));
    if (cua == NULL){
        puts("Crea cua : No hi ha prou memoria per crear cua buida");
        exit(-1);
    }
    for (int i = 0; i < max_cues; i++)
    {
        cua[i] = (el_cua*)malloc(max_cua*sizeof(el_cua));
        if(cua[i] == NULL)
        {
            puts("Crea cua : No hi ha memoria per crear totes les cues buides");
            exit(-1);
        }
        ini_cua[i] = -1;
        fin_cua[i] = -1;
        lon_cua[i] = 0;
    }
    imprimir_cua(cua);
}//crea_cua

//Inserta un valor "c" a la cua circular
// El ta és el temps actual per imprimir en les traces de seguiment.
int posa_cua(float ta, el_cua c, int ci){
    if (lon_cua[ci] == max_cua) {
        puts("ERROR CUA: No hi ha espai a la cua. Incrementa max_cua");
        exit(-1);
    }
    ++fin_cua[ci];
    if(fin_cua[ci] == max_cua) fin_cua[ci] = 0; // Primer element a la cua
    if(lon_cua[ci] == 0) ini_cua[ci] = fin_cua[ci];
    ++lon_cua[ci];
  
    cua[ci][fin_cua[ci]] = c;

#if DEBUGcua == 1
    printf("%.4lf POSA CUA... pos %2d elem %7.4lf\n",ta,fin_cua[ci],c.tar);
#endif
        
    imprimir_cua(cua);
    return (1);
}// posa_cua

// Treure el seguent element de la cua circular
// El ta és el temps actual per imprimir en les traces de seguiment.
int treu_cua(float ta, el_cua *c, int ci){
    int ret = 1; 
    
    if(lon_cua[ci] == 0) {
        ret = 0;
    }
    else { // si hi ha elements a la cua
#if DEBUGcua == 1
        printf("%.4lf TREU CUA... pos %2d\n",ta,ini_cua[ci]);
        if(lon_cua[ci] > 0) imprimir_element_cua(cua[ci], ini_cua[ci]);
        printf("(long %d) ", lon_cua[ci]);
#endif
        *c = cua[ci][ini_cua[ci]];
        ++ini_cua[ci];
        if (ini_cua[ci] == max_cua) ini_cua[ci] = 0;
        --lon_cua[ci];
        if(lon_cua == 0) ini_cua[ci] = fin_cua[ci] = -1;
        imprimir_cua(cua);
    }
    return(ret);
}// treu_cua

// Retorna quants elements te la cua circula
int long_cua(int ci){
    return(lon_cua[ci]);
}

//Allibera l'espai de la cua circular "cua"
void elim_cua(void){
    for(int i = 0; i < max_cues;  i++)
    {
        free(cua[i]);
    }
    free(cua);
}


