
#include "Utils.h"

/*hilos*/
/*se encarga de recibir las respuestas asincronas*/
void *respuestaAsin(void *datos);
/*se encargar de recibir los comandos del usuario*/
void *manejoUsuario(void *datos);
/*se encarga de leer los datos del archivo*/
list_t *leerDatos(Orden *orden);
/*se encarga que los datos esten correctos para despues enviarlos
si son correctos retorna 1*/
Orden *validarEntrada(char *arch);
/*envia los datos al stockMarket*/
int enviarDatos(char *arch);
void printRespuesta(Respuesta respu);
void sig_handler(int sengnal);

Datos *datos;

int main(int argc, char const *argv[])
{
    signal(SIGUSR1, sig_handler);
    mode_t fifo_mode = S_IRUSR | S_IWUSR;
    char *comando;
    pthread_t thread1, thread2;
    int continuar;
    /*fin de variables*/

    if (argc < 5)
    {
        printf("\nUso incorrecto \n");
        printf("Uso: ./%s pipename recursos_iniciales monto \n", argv[0]);
        exit(1);
    }
    datos = Datos_t(atoi(argv[4]), (char*)(argv[1]), (char*)argv[2]);
    datos->empresas = leerDatos((char*)argv[3]);
    printf("Datos del broker cargados \n");
    /*creacion de pipe */
    unlink(datos->nombre);
    if (mkfifo(datos->nombre, fifo_mode) == -1)
    {
        perror("Client  mkfifo");
        exit(1);
    }

    printf("Datos ingresados correctamente\n");

    /*crear hilo recepcion respuesta  asincrona*/
    /* crear hilo para comandos */

    if (pthread_create(&thread1, NULL, respuestaAsin, (void *)&datos) != 0)
    {
        perror("Hilo : ");
        exit(2);
    }
    if (pthread_create(&thread2, NULL, manejoUsuario, (void *)&datos) != 0)
    {
        perror("Hilo : ");
        exit(2);
    }
}
void *respuestaAsin(void *datos)
{
}

void *manejoUsuario(void *Datos)
{
    int continuar;
    Orden *orden;
    char *comando = sizeof(char*) * TAMNOMBRE;
    continuar = 1;
    while (continuar)
    {
        printf("~$ ");
        fgets(comando, TAMNOMBRE, stdin);
        to_lowercase(comando);
        
            orden = validarEntrada(comando);
            if (orden != NULL)
            {
                enviarDatos(orden);
            }
        
    }
}
list_t *leerDatos(char *arch)
{
    // archivo
    FILE *archivo;
    char *linea;
    char *nomEmpr;
    Empresa *empresa;
    char *token;
    char s[2];
    int acciones;
    list_t *lista;
        // token
    s[2] = (char)" ";
    nomEmpr = malloc(sizeof(char*) * maxchar);
    linea = malloc(sizeof(char*) * maxchar);
    // corregir lamado a la linea
    lista = list();

    archivo = fopen(arch, "r");
    /*revisar perror*/
    if (archivo == NULL)
    {
        perror("Error: ");
        exit(1);
    }
    else
    {
        printf("\nEl contenido del archivo de prueba es \n\n");
        while (feof(archivo) == 0)
        {
            fgets(linea, maxchar, archivo);
            printf("%s", linea);
            //

            /* get the first token */
            token = strtok(linea, s);

            /* walk through other tokens */
            printf(" %s\n", token);
            strcpy(nomEmpr, token);
            token = strtok(NULL, s);
            acciones = atoi(token);
            empresa = Empresa_t(acciones, nomEmpr);
            // corregir agregar a la lista
            add_order(list, (const void *)(Empresa)empresa);
        }
    }
    fclose(archivo);
    return lista;
}

Orden *validarEntrada(char *comando)
{
    /*oden de llegada de datos
  -   tipo de operacion
  -   empresa
  -   acciones
  -   precio
  */
    const char s[2] = ":";
    char *tipo;
    char *empresa;
    char *acciones;
    char *precio;

    char *token;
    Orden *orden;
        printf("COM: %s \n", comando);
    /*se capturan los datos*/
    token = strtok(comando, s);
    if (token != NULL && strcmp(token, "\n") != 0)
    {
        tipo = malloc(sizeof(char) * TAMNOMBRE);
        strcpy(tipo, token);
    }
    else
        tipo = NULL;

    token = strtok(NULL, s);
    if (token != NULL && strcmp(token, "\n") != 0)
    {
        empresa = malloc(sizeof(char) * TAMNOMBRE);
        strcpy(empresa, token);
    }
    else
        empresa = NULL;

    token = strtok(NULL, s);
    if (token != NULL && strcmp(token, "\n") != 0)
    {
        acciones = malloc(sizeof(char) * TAMNOMBRE);
        strcpy(acciones, token);
    }
    else
        acciones = NULL;

    token = strtok(NULL, s);
    if (token != NULL && strcmp(token, "\n") != 0)
    {
        precio = malloc(sizeof(char) * 30);
        strcpy(precio, token);
    }
    else
        precio = NULL;

    /*validacion de datos
        los datos que el broker puede validar son
        el tipo de comando
        si va a vender que el nombre de la emrpesas exista
        si el tipo es monto se muestras de una ves
        para las demas validaciones lo hace el stockmarket*/
    if ((strcmp(tipo, "venta") == 0) || (strcmp(tipo, "compra") == 0) ||
        (strcmp(tipo, "consulta") == 0) || (strcmp(tipo, "monto") == 0))
    {
        if (strcmp(tipo, "monto") == 0)
        {
            estadoBroker();
            return NULL;
        }

        if (strcmp(tipo, "venta") == 0)
        {
            // existen dos tipos
            if (validarEmpresa(empresa) == 0)
            {
                printf("Error: no se puede realizar la venta\n");
                printf("no existe el nombre de la empresa\n");
                return NULL;
            }
            if (acciones == NULL && precio == NULL)
            {
                return Orden_t((char)tipo, empresa, acciones, NULL);
            }
            else
            {
                return Orden_t((char)tipo, empresa, atoi(acciones), atoi(precio));
            }
        }

        if (strcmp(tipo, "consulta") == 0 && empresa == NULL)
        {
            return(tipo, empresa, NULL, NULL);
        }

        if (strcmp(tipo, "compra") == 0)
        {
            return Orden_t((char)tipo, empresa, atoi(acciones), atoi(precio));
        }
    }
    else
    {
        printf("\tCOMANDO INVALIDO\n");
        printf("Comandos disponibles: \n");
        printf("    *) compra\n");
        printf("    *) venta\n");
        printf("    *) consulta\n");
        printf("    *) monto\n");
        return NULL;
    }
}
int enviarDatos(Orden *orden)
{
    Mensaje *mensaje;
    mensaje = Mensaje_t(orden,datos->pid,datos->nombre);
    int fd, creado;
    creado = 0;
    do
    {
        if ((fd = open(datos->pipename, O_RDONLY | O_NONBLOCK)) == -1)
        {
            perror(" Cliente  Abriendo el segundo pipe. Se volvera a intentar ");
            sleep(5);
        }
        else
        {
            creado = 1;
            printf("\n Eh abierto el pipe");
        }
    } while (creado == 0);
    write(fd,mensaje, sizeof(struct Mns));
    printf("Se ha enviado la orden al stock market \n");
    close(fd);
}

int validarEmpresa(char *empresa)
{
    int i;
    int tam;
    for(i=0; i< tam; tam++)
    {
        if(strcmp(datos->empresas[i],empresa) == 0)
        {
            return 1;
        }
    }
    return 0;
}
/*utlilzado cuando se escribe el comando monto*/
estadoBroker()
{
    printf("Su monto actual es: %d", datos->monto);
}

void sig_handler(int sengnal)
{
    int creado, fd,n;
    Respuesta *respuesta;

    creado = 0;
    do
    {
        fd = open(datos->pipename, O_RDONLY);
        if (fd == -1)
        {
            perror("pipe");
            printf(" Se volvera a intentar despues\n");
            //sleep(5);
        }
        else
            creado = 1;
    } while (creado == 0);
    do
    {
        n = read(fd, respuesta, sizeof(struct Resp));
    } while (n < 0);
    close(fd);

    prinRespuesta(respuesta);
}

void printRespuesta(Respuesta respu)
{

    if(strcmp(char)respu.tipo,"c") == 0)
    {
        printf("===============================================\n");
        printf("Se ha la compra exitosa de: \n");
        printf("Acciones de la empresa: %s \n", (char*)respu.empresa);
        printf("acciones compradas: %d \n",respu.acciones);
        printf("con un monto total de: %d \n",(respu.acciones * respu.monto));
        printf("por medio del broker: %s \n",(char*)respu.broker);
        printf("===============================================\n");
    }
    if (strcmp((char)respu.tipo, "v") == 0)
    {
        printf("===============================================\n");
        printf("se ha la compra exitosa de: \n");
        printf("acciones de la empresa: %s \n", (char*)respu.empresa);
        printf("acciones compradas: %d \n",respu.acciones);
        printf("con un monto total de: %d \n",(respu.acciones * respu.monto));
        printf("por medio del broker: %s \n", (char*)respu.broker);
        printf("===============================================\n");
    }
    if (strcmp((char)respu.tipo, "q") == 0)
    {
        printf("===============================================\n");
        printf("Se realizo la consulta: ,\n");
        printf("Precio de las acciones de la empresa: %s",(char*)respu.empresa);
        printf("El precio de la acciones es: %d", respu.monto);
        printf("===============================================\n");
    }
}
