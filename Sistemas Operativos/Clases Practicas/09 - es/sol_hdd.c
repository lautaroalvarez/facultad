/* DISCLAIMER: Tener en cuenta las restricciones charladas en clase y cosas a tener en cuenta del protocolo del dispositivo */

#define SECTOR_SIZE 512
int sector;

int driver_seek(int offset) {
    sector = offset; /* Validar offsets válidos, etc */
}

int driver_write(int * data) {
    int * datos;
    copy_from_user(data, datos, sizeof(data));
    
    while(IN(HDD_STATUS) != HDD_STAT_RDY )   
    sleep(1);

    OUT(HDD_SECTOR, sector);
    OUT(HDD_COUNT, 1);
    OUT(HDD_OPERATION, HDD_OP_WRITE);
 
    while(IN(HDD_STATUS) != HDD_STAT_BSY)  
        sleep(1);

    while(IN(HDD_STATUS) != HDD_STAT_RDY)
        sleep(1);

    for (int i = 0; i < SECTOR_SIZE/4 * sizeof(data); i++) {
        OUT(HDD_DATA, datos[i]);
    }

    return IO_OK;
}

int driver_read(int * data) {
    int datos[SECTOR SIZE/4];
    while(IN(HDD_STATUS) != HDD_STAT_RDY ); 
    OUT(HDD_SECTOR, sector);
    OUT(HDD_COUNT, 1);
    OUT(HDD_OPERATION, HDD_OP_READ);
    
    while(IN(HDD_STATUS) != HDD_STAT_BSY); 

    while(IN(HDD_STATUS) != HDD_STAT_RDY );

    for (int i = 0; i < SECTOR_SIZE/4; i++) {
        datos[i] = IN(HDD_DATA);
    }
    //     put_user(*(msg_Ptr++), buffer++);
    copy_to_user(datos, data, sizeof(datos));

    return IO_OK;
}

//========================================
// SOLUCION CON IRQ

mutex access = 1;
mutex transfer = 1;
sem ready = 0;

int datos[SECTOR SIZE/4];
int etapa;
int nro_dato;

int driver_seek(int offset) {
    sector = offset; /* Validar offsets válidos, etc */
}

int driver_init() {
    if(request_irq(3, next) == IRQ_ERROR)
        return IO_ERROR;
    return IO_OK;
}

int driver_remove() {
    free_irq(3);
    return IO_OK;
}

int driver_open() {
    access.wait();
}

int driver_close() {
    access.signal();
}

int driver_write(int * data) {
// Tarea
    return IO_OK;
}

int driver_read(int * data) {
    transfer.wait();
    reading = 1;
    etapa = 0;
    ready.wait();
    OUT(HDD_SECTOR, sector);
    OUT(HDD_COUNT, 1);
    etapa = 1;
    OUT(HDD_OPERATION, HDD_OP_READ);
    ready.wait();
    etapa = 0;
    ready.wait();
    for (int i = 0; i < SECTOR_SIZE/4; i++) {
        datos[i] = IN(HDD_DATA);
    }

    copy_to_user_data(datos, data, sizeof(datos));
    transfer.signal()
    return IO_OK;
}

void next() {
    if (reading){
        //LLego una lectura
        switch(etapa) {
            case 0:
                if(IN(HDD_STATUS) != HDD_STAT_RDY)
                    return;
                ready.signal()
                break;
            case 1:
                if(IN(HDD_STATUS) != HDD_STAT_BSY)
                    return;
                ready.signal()
                break;
	}
    }
}
