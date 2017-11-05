
#include "Utils.h"

/*hilos*/
/*se encarga de recibir las respuestas asincronas*/
void *respuestaAsin(void *datos);
/*se encargar de recibir los comandos del usuario*/
void *manejoUsuario(void *datos);
/*se encarga de leer los datos del archivo*/
list_t *leerDatos(char *arch);
/*se encarga que los datos esten correctos para despues enviarlos
si son correctos retorna 1*/
int validarEntrada(char *arch);
/*envia los datos al stockMarket*/
int enviarDatos(char *arch);
char *recibirDatos();

Datos datos;

int main(int argc, char const *argv[])
{
    char *comando;
    pthread_t thread1, thread2;
    int continuar;
    /*fin de variables*/
    /*corregir creacion datos*/
    datos.nombre = malloc(sizeof(char) * TAMNOMBRE);
    datos.pipename = malloc(sizeof(char) *TAMNOMBRE);

    if (argc < 5)
    {
        printf("faltan datos \n");
        printf("Orden de datos: nombre pipename recursos_iniciales monto \n");
        exit(1);
    }

    strcpy(datos.nombre, argv[1]);
    strcpy(datos.pipename, argv[2]);
    datos.monto = atoi(argv[4]);
    datos.empresas = leerDatos(argv[3]);

    printf("Datos ingresados correctamente\n");

    /*crear hilo recepcion respuesta  asincrona*/
    /* crear hilo para comandos */

    if (pthread_create(&thread1, NULL, respuestaAsin, (void *)&datos) != 0)
    {
        perror("ERROR\n");
        exit(2);
    }
    if (pthread_create(&thread2, NULL, manejoUsuario, (void *)&datos) != 0)
    {
        perror("ERROR\n");
        exit(2);
    }

}
void *respuestaAsin(void *datos)
{
}

void *manejoUsuario(void *Datos)
{
    int continuar;

    char *comando = sizeof(char) * TAMNOMBRE;
    continuar = 1;
    while (continuar)
    {
        fgets(comando, TAMNOMBRE, stdin);
        if (strcmp(comando, "salir") == 0)
        {
            /*antes de cerrar se muestra con que saldo quedo y el numero de acciones de cadaempresa*/
            exit(1);
        }
        else
        {
            validarEntrada(comando);
            enviarDatos(comando);
            prinf(recibirDatos(comando));
        }
    }
}
list_t *leerDatos(char *arch)
{
    // archivo
    FILE *archivo;
    char *linea = malloc(sizeof(char) * maxchar);
    // token
    const char s[2] = " ";
    char *token;
    // otros
    Empresa *empresa;
    char *nomEmpr = malloc(sizeof(char) * maxchar);
    int acciones;
    // corregir lamado a la linea
    list_t lista = list();

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
            fgets(linea, max, archivo);
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

int validarEntrada(char *comando)
{
    /*oden de llegada de datos
    -   tipo de operacion
    -   empresa
    -   acciones
    -   precio
    */
    const char s[2] = ":";
    char* tipo;
    char* empresa;
    char* acciones;
    char* precio;

    char *token;
    Orden* orden = Orden_t()
    printf("COM: %s \n", comando);
    /*se capturan los datos*/
    token = strtok(comando, s);
    token = strtok(NULL, s);
    if(token != NULL && strcmp(token,"\n")!=0)
    {
        tipo = malloc(sizeof(char) * TAMNOMBRE);
        strcpy(tipo, token);
    }
    else
        tipo = NULL;
    token = strtok(NULL, s);
    if(token != NULL && strcmp(token,"\n")!=0)
    {
        tipo = malloc(sizeof(char) * TAMNOMBRE);
        strcpy(tipo, token);
    }
    else
        tipo = NULL;
    token = strtok(NULL, s);
    if(token != NULL && strcmp(token,"\n")!=0)
    {
        tipo = malloc(sizeof(char) * TAMNOMBRE);
        strcpy(tipo, token);
    }
    else
        tipo = NULL;
    /*validacion de datos*/
    if ((strcmp(tipo, "venta") == 0) || (strcmp(tipo, "compra") == 0) ||
        (strcmp(tipo, "consulta") == 0) || (strcmp(tipo, "monto") == 0))
        {

        }
        else
        {
            printf("COMANDO INVALIDO\n");
            printf("Comando disponibles: \n");
            printf("    compra\n");
            printf("    venta\n");
            printf("    consulta\n");
            printf("    monto\n");
        }
}
int enviarDatos(char *arch)
{
}
char *recibirDatos()
{
}
int validarEmpresa(char* empresa)
{

}
