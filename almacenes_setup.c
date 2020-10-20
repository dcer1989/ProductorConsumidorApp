void Inicia_Almacen_Prod (Buffer_Circ *ptr_buff, Pieza *ptr_pieza, int size)
{
   ptr_buff->lleno = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
   ptr_buff->vacio = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
   pthread_mutex_init(&ptr_buff->m_state, NULL);

   ptr_buff->Num_Piezas = ptr_pieza;	
   ptr_buff->buff_size = size;
   ptr_buff->buff_contador = 0;
   ptr_buff->bufIN = 0;
   ptr_buff->bufOUT = 0;
   
   for (int i =0; i < ptr_buff->buff_size; i++)
   {
        ptr_buff->Num_Piezas[i].Id_Pieza=0;
        ptr_buff->Num_Piezas[i].Almacen_Actual=0;
        ptr_buff->Num_Piezas[i].Time_Tag=0;
        ptr_buff->Num_Piezas[i].Almacen_Origen=0;
        ptr_buff->Num_Piezas[i].Validez=0;
   }
}

void set_item (time_t *ttime, Pieza *ptr_pieza, int Alm_Act)
{
    ptr_pieza->Id_Pieza++;
    ptr_pieza->Production_date = ctime(ttime);
    ptr_pieza->Almacen_Origen = Alm_Act;
    ptr_pieza->Validez = 0;
}

void put_item (Pieza *ptr_pieza, Buffer_Circ *ptr_buff, int Alm_Act)
{
    pthread_mutex_lock(&ptr_buff->m_state);
        while (ptr_buff->buff_contador == ptr_buff->buff_size)
        {
            pthread_cond_wait(&ptr_buff->lleno, &ptr_buff->m_state);
        }
        ptr_buff->Num_Piezas[ptr_buff->bufIN].Id_Pieza = ptr_pieza->Id_Pieza;
        ptr_buff->Num_Piezas[ptr_buff->bufIN].Production_date = ptr_pieza->Production_date;
        ptr_buff->Num_Piezas[ptr_buff->bufIN].Time_Tag = getCurrentMicroseconds();
        ptr_buff->Num_Piezas[ptr_buff->bufIN].Almacen_Origen = ptr_pieza->Almacen_Origen;
        ptr_buff->Num_Piezas[ptr_buff->bufIN].Validez = ptr_pieza->Validez;
        ptr_buff->Num_Piezas[ptr_buff->bufIN].Almacen_Actual = Alm_Act;
        ptr_buff->buff_contador++;
        ptr_buff->bufIN = (ptr_buff->bufIN + 1)%(ptr_buff->buff_size);   
    pthread_cond_broadcast(&ptr_buff->vacio);    
    pthread_mutex_unlock(&ptr_buff->m_state);      
}

void get_item (Pieza *ptr_pieza, Buffer_Circ *ptr_buff)
{
    pthread_mutex_lock(&ptr_buff->m_state);
        while (ptr_buff->buff_contador == 0)
        {
            pthread_cond_wait(&ptr_buff->vacio,&ptr_buff->m_state);
        }        
        ptr_pieza->Id_Pieza = ptr_buff->Num_Piezas[ptr_buff->bufOUT].Id_Pieza;
        ptr_pieza->Production_date = ptr_buff->Num_Piezas[ptr_buff->bufOUT].Production_date;
        ptr_pieza->Time_Tag = ptr_buff->Num_Piezas[ptr_buff->bufOUT].Time_Tag;
        ptr_pieza->Almacen_Origen = ptr_buff->Num_Piezas[ptr_buff->bufOUT].Almacen_Origen;
        ptr_pieza->Almacen_Actual = ptr_buff->Num_Piezas[ptr_buff->bufOUT].Almacen_Actual;
        ptr_pieza->Validez = ptr_buff->Num_Piezas[ptr_buff->bufOUT].Validez;
        ptr_buff->buff_contador--;
        ptr_buff->bufOUT = (ptr_buff->bufOUT + 1)%(ptr_buff->buff_size);
    pthread_cond_broadcast(&ptr_buff->lleno);   
    pthread_mutex_unlock(&ptr_buff->m_state);

}

void Contenido_Almacen (Buffer_Circ *ptr_buff)
{
    int i = ptr_buff->bufIN;
    int j = ptr_buff->bufOUT;
    int k = ptr_buff->buff_contador;
    int s = ptr_buff->buff_size;
    if (k == 0)
    {
        printf ("El almacén está vacío\n");
    }
    else if (k == s)
    {
        printf ("\nEl almacén está lleno\n");
    }
    else
    {
        printf ("Total de piezas: %d\n", ptr_buff->buff_contador);
        printf ("ID_Pieza   Almacén de origen   Validez de la pieza\n");
        while (j != i)
        {
            printf ("%d%11d", ptr_buff->Num_Piezas[j].Id_Pieza, ptr_buff->Num_Piezas[j].Almacen_Origen );
            if (ptr_buff->Num_Piezas[j].Validez == 0)
            {
                printf ("                   válida\n");
            }
            else if (ptr_buff->Num_Piezas[j].Validez == 1)
            {
                printf ("                   no válida\n");
            }
            j = (j + 1)%(s);
        }
    }
}

long getCurrentMicroseconds()
{
    struct timespec currentTime;
    clock_gettime(CLOCK_MONOTONIC, &currentTime);
    return (currentTime.tv_sec)*1000000 + (currentTime.tv_nsec) / 1000;
}
