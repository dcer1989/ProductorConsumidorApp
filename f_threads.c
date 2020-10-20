void *func_P1(void *ptr_buff)
{
    int Alm_Act = 1;
    Buffer_Circ *buff = (Buffer_Circ *)ptr_buff;
    static Pieza temp;
    time_t ttime;
    long Time_prove;
    long Production_Start_Time = getCurrentMicroseconds();
    while (Time_prove/1000000 - TPROD <= 0)
    {
        set_item(&ttime, &temp, Alm_Act);
        sleep(Tg1);
        put_item(&temp, (buff+0), Alm_Act);
        Time_prove = getCurrentMicroseconds() - Production_Start_Time;
    }
    pthread_exit(&ret1);
}

void *func_P2(void *ptr_buff)
{
    int Alm_Act = 2;
    Buffer_Circ *buff = (Buffer_Circ *)ptr_buff;
    static Pieza temp;
    time_t ttime;
    long Time_prove;
    long Production_Start_Time = getCurrentMicroseconds();
    while (Time_prove/1000000 - TPROD <= 0)
    {
        set_item(&ttime, &temp, Alm_Act);
        sleep(Tg2);
        put_item(&temp, (buff+1), Alm_Act);
        Time_prove = getCurrentMicroseconds() - Production_Start_Time;
    }
    pthread_exit(&ret2);
}

void *func_P3(void *ptr_buff)
{
    int Alm_Act = 3;
    Buffer_Circ *buff = (Buffer_Circ *)ptr_buff;
    int permanencia;
    static Pieza temp;
    while ((ret_1 != &ret1) || ((buff+0)->buff_contador != 0))
    {
        if ((buff+0)->buff_contador != 0)
        {
            permanencia = (getCurrentMicroseconds() - (buff+0)->Num_Piezas[(buff+0)->bufOUT].Time_Tag)/1000000 - Tp1;
            if (permanencia < 0) 
            {
                sleep(-permanencia);
            }
            else if(permanencia >= 0)
            {
                if (permanencia <= 2)
                {
                    get_item(&temp, (buff+0));
                    put_item(&temp, (buff+2), Alm_Act);
                }
                else 
                {
                    (buff+0)->Num_Piezas[(buff+0)->bufOUT].Validez = 1;
                    get_item(&temp, (buff+0));
                    put_item(&temp, (buff+2), Alm_Act);
                }
            }
        }
    }
    pthread_exit(&ret3);
}

void *func_P4(void *ptr_buff)
{
    int Alm_Act = 3;
    Buffer_Circ *buff = (Buffer_Circ *)ptr_buff;
    int permanencia;
    static Pieza temp;
    while ((ret_2 != &ret2) || ((buff+1)->buff_contador != 0))
    {
        if ((buff+1)->buff_contador != 0)
        {
            permanencia = (getCurrentMicroseconds() - (buff+1)->Num_Piezas[(buff+1)->bufOUT].Time_Tag)/1000000 - Tp2;
            if (permanencia < 0)
            {
                sleep(-permanencia);
            }
            else if(permanencia >= 0)
            {
                if (permanencia <= 2)
                {
                    get_item(&temp, (buff+1));
                    put_item(&temp, (buff+2), Alm_Act);
                }
                else 
                {
                    (buff+1)->Num_Piezas[(buff+1)->bufOUT].Validez = 1;
                    get_item(&temp, (buff+1));
                    put_item(&temp, (buff+2), Alm_Act);
                }
            }
        }
    }
    pthread_exit(&ret4);
}

void *func_P5(void *ptr_buff)
{
    int Alm_Act = 4;
    Buffer_Circ *buff = (Buffer_Circ *)ptr_buff;
    int permanencia;
    static Pieza temp;
    while ((ret_3 != &ret3) || ((buff+2)->buff_contador != 0))
    {
        if ((buff+2)->buff_contador != 0)
        {
            permanencia = (getCurrentMicroseconds() - (buff+2)->Num_Piezas[(buff+2)->bufOUT].Time_Tag)/1000000 - Tp3;
            if ((permanencia >= 0)&&((buff+2)->Num_Piezas[(buff+2)->bufOUT].Almacen_Origen == 1))
            {
                if (permanencia <= 4)
                {
                    get_item(&temp, (buff+2));
                    put_item(&temp, (buff+3), Alm_Act);
                }
                else 
                {
                    (buff+2)->Num_Piezas[(buff+2)->bufOUT].Validez = 1;
                    get_item(&temp, (buff+2));
                    put_item(&temp, (buff+3), Alm_Act);
                }
            }
            else if ((permanencia < 0)&&((buff+2)->Num_Piezas[(buff+2)->bufOUT].Almacen_Origen == 1))
            {
                sleep(-permanencia);
            }
        }
    }
    pthread_exit(&ret5);
}

void *func_P6(void *ptr_buff)
{
    int Alm_Act = 5;
    Buffer_Circ *buff = (Buffer_Circ *)ptr_buff;
    int permanencia;
    static Pieza temp;
    while ((ret_4 != &ret4) || ((buff+2)->buff_contador != 0))
    {
        if ((buff+2)->buff_contador != 0)
        {
            permanencia = (getCurrentMicroseconds() - (buff+2)->Num_Piezas[(buff+2)->bufOUT].Time_Tag)/1000000 - Tp3;
            if((permanencia >= 0)&&((buff+2)->Num_Piezas[(buff+2)->bufOUT].Almacen_Origen == 2))
            {
                if (permanencia <= 4)
                {
                    get_item(&temp, (buff+2));
                    put_item(&temp, (buff+4), Alm_Act);
                }
                else 
                {
                    (buff+2)->Num_Piezas[(buff+2)->bufOUT].Validez = 1;
                    get_item(&temp, (buff+2));
                    put_item(&temp, (buff+4), Alm_Act);
                }
            }
            else if ((permanencia < 0)&&((buff+2)->Num_Piezas[(buff+2)->bufOUT].Almacen_Origen == 2))
            {
                sleep(-permanencia);
            }
        }
    }
    pthread_exit(&ret6);
}

void *func_P7(void *ptr_buff)
{
    Buffer_Circ *buff = (Buffer_Circ *)ptr_buff;
    int permanencia;
    static Pieza temp;
    while ((ret_5 != &ret5) || ((buff+3)->buff_contador != 0))
    {
        if ((buff+3)->buff_contador != 0)
        {
            permanencia = (getCurrentMicroseconds() - (buff+3)->Num_Piezas[(buff+3)->bufOUT].Time_Tag)/1000000 - Tp4;
            if(permanencia >= 0)
            {
                if (permanencia <= 6)
                {
                    get_item(&temp, (buff+3));
                }
                else
                {
                    (buff+3)->Num_Piezas[(buff+3)->bufOUT].Validez = 1;
                    get_item(&temp, (buff+3));
                }
            }
            else if (permanencia < 0)
            {
                sleep(-permanencia);
            }
        }
    }
    pthread_exit(&ret7);
}

void *func_P8(void *ptr_buff)
{
    Buffer_Circ *buff = (Buffer_Circ *)ptr_buff;
    int permanencia;
    static Pieza temp;
    while ((ret_6 != &ret6) || ((buff+4)->buff_contador != 0))
    {
        if ((buff+4)->buff_contador != 0)
        {
            permanencia = (getCurrentMicroseconds() - (buff+4)->Num_Piezas[(buff+4)->bufOUT].Time_Tag)/1000000 - Tp5;
            if(permanencia >= 0)
            {
                if (permanencia <= 6)
                {
                    get_item(&temp, (buff+4));
                }
                else 
                {
                    (buff+4)->Num_Piezas[(buff+4)->bufOUT].Validez = 1;
                    get_item(&temp, (buff+4));
                }
            }
            else if (permanencia < 0)
            {
                sleep(-permanencia);
            }
        }
    }
    pthread_exit(&ret8);
}

void *func_Inv(void *ptr_buff)
{
    Buffer_Circ *buff = (Buffer_Circ *)ptr_buff;
    printf("\ec");//limpio la salida de la terminal utilizando codigo de escape ANSI
    while ((ret_7 != &ret7) || (ret_8 != &ret8))
    {
        printf("\ec");
        printf ("Almacen_1\n");
        Contenido_Almacen ((buff+0));
        printf ("\nAlmacen_2\n");
        Contenido_Almacen ((buff+1));
        printf ("\nAlmacen_3\n");
        Contenido_Almacen ((buff+2));
        printf ("\nAlmacen_4\n");
        Contenido_Almacen ((buff+3));
        printf ("\nAlmacen_5\n");
        Contenido_Almacen ((buff+4));
        printf("\ec");
        printf("\e[;f");//doy formato a la salida de la terminal utilizando codigo de escape ANSI (movimiento del cursor)
        sleep(1);
    }
    printf ("Almacen_1\n");
    Contenido_Almacen ((buff+0));
    printf ("\nAlmacen_2\n");
    Contenido_Almacen ((buff+1));
    printf ("\nAlmacen_3\n");
    Contenido_Almacen ((buff+2));
    printf ("\nAlmacen_4\n");
    Contenido_Almacen ((buff+3));
    printf ("\nAlmacen_5\n");
    Contenido_Almacen ((buff+4));
    pthread_exit(&retInv);
}
