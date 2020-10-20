#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "main.h"
#include "almacenes_setup.h"
#include "almacenes_setup.c"
#include "f_threads.h"
#include "f_threads.c"


int main(int argc, char *argv[])
{
    Buffer_Circ Almacen_Prod[5];
    Pieza Num_Piezas_A1[SIZE_A1];
    Pieza Num_Piezas_A2[SIZE_A2];
    Pieza Num_Piezas_A3[SIZE_A3];
    Pieza Num_Piezas_A4[SIZE_A4];
    Pieza Num_Piezas_A5[SIZE_A5];
    
    Inicia_Almacen_Prod(&Almacen_Prod[0],Num_Piezas_A1,SIZE_A1);
    Inicia_Almacen_Prod(&Almacen_Prod[1],Num_Piezas_A2,SIZE_A2);
    Inicia_Almacen_Prod(&Almacen_Prod[2],Num_Piezas_A3,SIZE_A3);
    Inicia_Almacen_Prod(&Almacen_Prod[3],Num_Piezas_A4,SIZE_A4);
    Inicia_Almacen_Prod(&Almacen_Prod[4],Num_Piezas_A5,SIZE_A5);
    
    pthread_t P1, P2, P3, P4, P5, P6, P7, P8, Inventario;
    
    pthread_create(&P1, NULL, func_P1, &Almacen_Prod);
    pthread_create(&P2, NULL, func_P2, &Almacen_Prod);
    pthread_create(&P3, NULL, func_P3, &Almacen_Prod);
    pthread_create(&P4, NULL, func_P4, &Almacen_Prod);
    pthread_create(&P5, NULL, func_P5, &Almacen_Prod);
    pthread_create(&P6, NULL, func_P6, &Almacen_Prod);
    pthread_create(&P7, NULL, func_P7, &Almacen_Prod);
    pthread_create(&P8, NULL, func_P8, &Almacen_Prod);
    pthread_create(&Inventario, NULL, func_Inv, &Almacen_Prod);

    pthread_join(P1, (void **)(&ret_1));
    pthread_join(P2, (void **)(&ret_2));
    pthread_join(P3, (void **)(&ret_3));
    pthread_join(P4, (void **)(&ret_4));
    pthread_join(P5, (void **)(&ret_5));
    pthread_join(P6, (void **)(&ret_6));
    pthread_join(P7, (void **)(&ret_7));
    pthread_join(P8, (void **)(&ret_8));
    pthread_join(Inventario, (void **)(&ret_inv));
    
    printf("\nFIN DE LA APLICACION \n\n");
    return 0;

}
