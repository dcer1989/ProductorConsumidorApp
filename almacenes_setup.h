#ifndef ALMACENES_SETUP_H
#define ALMACENES_SETUP_H

typedef struct Pieza 
{
    int Almacen_Actual;
    int Almacen_Origen;
    int Id_Pieza;
    char *Production_date;  
    long Time_Tag;
    int Validez;
}Pieza;

typedef struct Buffer_Circ 
{
    int buff_size, buff_contador, bufIN, bufOUT;
    Pieza *Num_Piezas;
    pthread_cond_t lleno;
    pthread_cond_t vacio;
    pthread_mutex_t m_state;
    
}Buffer_Circ;

void Inicia_Almacen_Prod(Buffer_Circ *ptr_buff, Pieza *ptr_pieza, int size);
void set_item(time_t *ttime, Pieza *ptr_pieza, int Origen);
void put_item(Pieza *ptr_pieza, Buffer_Circ *ptr_buff, int Alm_Act);
void get_item(Pieza *ptr_pieza, Buffer_Circ *ptr_buff);
void Contenido_Almacen (Buffer_Circ *ptr_buff);
long getCurrentMicroseconds();

#endif
