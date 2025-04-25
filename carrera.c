#include <stdio.h>
#include <string.h>

int main() {
    char nombres[5][30];
    int salida[5];
    float tiempo[5];
    int datos_ingresados = 0;
    int opcion, i, j;

    do {
        printf("\n===== MENU DE OPCIONES - CARRERA F1 =====\n");
        printf("1. Ingresar datos de los corredores\n");
        printf("2. Mostrar podio (Top 3)\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Error: ingrese un numero valido.\n");
            while (getchar() != '\n');
            continue;
        }

        switch(opcion) {
            case 1:
                for(i = 0; i < 5; i++) {
                    printf("\nCorredor %d:\n", i + 1);

                    // Nombre único
                    do {
                        int nombreRepetido = 0;
                        printf("Nombre: ");
                        fflush(stdin);
                        fgets(nombres[i], 30, stdin);
                        nombres[i][strcspn(nombres[i], "\n")] = 0;

                        for(j = 0; j < i; j++) {
                            if(strcmp(nombres[i], nombres[j]) == 0) {
                                nombreRepetido = 1;
                                printf("Error: el nombre ya ha sido ingresado.\n");
                                break;
                            }
                        }

                        if (!nombreRepetido) break;
                    } while (1);

                    // Posición de salida única
                    do {
                        int posicionRepetida = 0;
                        printf("Posicion de salida (1 a 5): ");
                        if (scanf("%d", &salida[i]) != 1 || salida[i] < 1 || salida[i] > 5) {
                            printf("Error: posicion invalida.\n");
                            while (getchar() != '\n');
                            continue;
                        }

                        for(j = 0; j < i; j++) {
                            if(salida[i] == salida[j]) {
                                posicionRepetida = 1;
                                printf("Error: esa posicion de salida ya ha sido ocupada.\n");
                                break;
                            }
                        }

                        if (!posicionRepetida) break;

                    } while (1);

                    // Tiempo
                    do {
                        printf("Tiempo de llegada (en segundos): ");
                        if (scanf("%f", &tiempo[i]) != 1 || tiempo[i] <= 0) {
                            printf("Error: tiempo invalido.\n");
                            while (getchar() != '\n');
                        } else {
                            break;
                        }
                    } while (1);
                }
                datos_ingresados = 1;
                break;

            case 2:
                if (!datos_ingresados) {
                    printf("\nPrimero debe ingresar los datos de los corredores.\n");
                    break;
                }

                // Ordenar por tiempo y en caso de empate por mayor posición de salida
                for(i = 0; i < 4; i++) {
                    for(j = i + 1; j < 5; j++) {
                        if(tiempo[i] > tiempo[j] || (tiempo[i] == tiempo[j] && salida[i] < salida[j])) {
                            // Intercambio de tiempo
                            float tempTiempo = tiempo[i];
                            tiempo[i] = tiempo[j];
                            tiempo[j] = tempTiempo;

                            // Intercambio de posición
                            int tempSalida = salida[i];
                            salida[i] = salida[j];
                            salida[j] = tempSalida;

                            // Intercambio de nombres
                            char tempNombre[30];
                            strcpy(tempNombre, nombres[i]);
                            strcpy(nombres[i], nombres[j]);
                            strcpy(nombres[j], tempNombre);
                        }
                    }
                }

                // Mostrar podio
                printf("\n--- PODIO DE LA CARRERA ---\n");
                for(i = 0; i < 3; i++) {
                    printf("%d° Lugar: %s | Tiempo: %.2f s | Posicion de salida: %d\n",
                        i + 1, nombres[i], tiempo[i], salida[i]);
                }
                break;

            case 3:
                printf("\nFin del programa. ¡Gracias por usar el sistema!\n");
                break;

            default:
                printf("\nOpción no válida. Intente de nuevo.\n");
        }

    } while(opcion != 3);

    return 0;
}
