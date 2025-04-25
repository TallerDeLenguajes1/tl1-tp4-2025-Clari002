#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
};

typedef struct Tarea Tarea;

struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
};

typedef struct Nodo Nodo;

Nodo * crearListaVacia();
Nodo * crearNodo(Tarea tarea);
void insertarTareaALista(Nodo ** start, Nodo * nuevoNodo);
void mostrarTarea(Nodo * start);
void mostrarLista(Nodo * start);
void buscarTareaPorID(Nodo * tareasPendientes, Nodo * tareasRealizadas, int IDBuscado);
void liberarMemoria(Nodo * start);

int main()
{
    Nodo * TareasPendiendes = crearListaVacia();
    Nodo * TareasRealizadas = crearListaVacia();
    int respuesta=0, i=0, duracion;
    char *Buff;
    Buff=(char *)malloc(100*sizeof(char));

    printf("-------------CARGAR TAREA/S A LISTA PENDIENTE-------------");
    printf("\nCargar una tarea Si(1) No(0): ");
    scanf("%d",&respuesta);


    while (respuesta==1)
    {
            Tarea tarea;
            tarea.TareaID= 1000 + i;

            printf("\nIngrese una descripcion: ");
            fflush(stdin);
            fgets(Buff, 100, stdin);
            Buff[strcspn(Buff, "\n")] = '\0';
            tarea.Descripcion=(char *)malloc((strlen(Buff)+1)*sizeof(char));
            strcpy(tarea.Descripcion,Buff);
        
            printf("Ingrese la duracion (entre 10 y 100): ");
            scanf("%d",&duracion);
            tarea.Duracion=duracion;
            while(getchar() != '\n'); 
            
            sscanf(Buff, "%d", &tarea.Duracion);
            i++;
            insertarTareaALista(&TareasPendiendes, crearNodo(tarea));
            printf("\n-------------CARGAR TAREA/S A LISTA PENDIENTE-------------");
            printf("\nCargar una tarea Si(1) No(0): ");
            scanf("%d", &respuesta);
    }

    // mostrarLista(TareasPendiendes);

int resp;
Nodo * nodoAuxiliar;
    do
    {
        printf("\n\n-----------CUESTIONARIO-------------------");
        printf("\n(1)Clasificar de Pendiente a Realizada");
        printf("\n(2)Listar tareas Pendientes");
        printf("\n(3)Listar tareas Realizadas");
        printf("\n(4)Consultar tarea por ID");
        printf("\n(0)Salir");
        printf("\nInsertar valor: ");
        scanf("%d", &resp);
        switch (resp)
        {
        case 1:
            if (TareasPendiendes!= NULL)
            {
                Nodo *prev = NULL;
                Nodo * auxi = TareasPendiendes;
                while (auxi!=NULL)
                {
                    mostrarTarea(auxi);
                    printf("\nTarea Realizada  Si(1) No(0): ");
                    scanf("%d", &respuesta);
                    if (respuesta==1)
                    {
                        if (prev == NULL)
                        {
                            TareasPendiendes = auxi->Siguiente;
                        }
                        else{
                            prev->Siguiente=auxi->Siguiente;
                        }
                        nodoAuxiliar=auxi;
                        auxi=auxi->Siguiente;
                        nodoAuxiliar->Siguiente=NULL;
                        insertarTareaALista(&TareasRealizadas, nodoAuxiliar);
                    }
                    else{
                        prev = auxi;
                        auxi = auxi->Siguiente;
                    }       
                }   
           }
            break;
        case 2:
            printf("\n\n-----------TAREAS PENDIENTES-------------------");
            if (TareasPendiendes!=NULL)
            {
                mostrarLista(TareasPendiendes);
            }else{
                printf("\nNo hay tareas pendientes");
            }
            break;
        case 3:
            printf("\n\n-----------TAREAS REALIZADAS-------------------");
            if (TareasRealizadas!=NULL)
            {
                mostrarLista(TareasRealizadas);
            }else{
                printf("\nNo hay tareas realizadas");
            }
            break;
        case 4:
            printf("\n\n-----------BUSCAR TAREA POR ID-------------------");
            int IDBuscado;
            printf("\nIngrese el ID a buscar: ");
            scanf("%d",&IDBuscado);
            buscarTareaPorID(TareasPendiendes,TareasRealizadas,IDBuscado);
        
            break;
        default:
            break;
        }
    } while (resp != 0);
    
    liberarMemoria(TareasPendiendes);
    liberarMemoria(TareasRealizadas);
    free(Buff);
    return 0;
}

//inicializar lista vacia
Nodo * crearListaVacia()
{
    return NULL;
}

//crear nodo
Nodo * crearNodo(Tarea tarea)
{
    Nodo * nuevoNodo =(Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->T=tarea;
    nuevoNodo->Siguiente=NULL;
    return nuevoNodo;
}

void insertarTareaALista(Nodo ** start, Nodo * nuevoNodo)
{
     nuevoNodo->Siguiente= *start;
    *start = nuevoNodo;
}

void mostrarTarea(Nodo * start)
{
    printf("\n-------------TAREA ID%d-------------", start->T.TareaID);
    printf("\nDescripcion: ");
    puts(start->T.Descripcion);
    printf("Duracion: %d", start->T.Duracion);
}

void mostrarLista(Nodo * start)
{
    Nodo * aux = start;
    while (aux != NULL)
    {
        mostrarTarea(aux);
        aux = aux->Siguiente;
    }
}

void buscarTareaPorID(Nodo * tareasPendientes, Nodo * tareasRealizadas, int IDBuscado)
{
    Nodo * auxTp = tareasPendientes;
    int encontrado = 0;
    while (auxTp!=NULL)
    {
        if (auxTp->T.TareaID==IDBuscado)
        {
            printf("\nLa tarea ID=%d corresponde a TAREAS PENDIENTES", IDBuscado);
            mostrarTarea(auxTp);
            encontrado=1;
            break;
        }
        auxTp=auxTp->Siguiente;
    }
    if (!encontrado)
    {
        auxTp=tareasRealizadas;
        while (auxTp!=NULL)
        {
            if (auxTp->T.TareaID==IDBuscado)
            {
                printf("\nLa tarea ID=%d corresponde a TAREAS REALIZADAS", IDBuscado);
                mostrarTarea(auxTp);
                encontrado=1;
                break;
            }
            auxTp=auxTp->Siguiente;       
        }   
    }
    if (!encontrado)
    {
        printf("\nEl ID= %d no fue encontrado", IDBuscado);
    }   
}

void liberarMemoria(Nodo * start)
{
    Nodo * aux;
    while (start!=NULL)
    {
        aux = start;
        start=start->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
}