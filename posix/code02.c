/*
Nombre: Sebastian Angulo
Fecha: 29/10/2024
Profesor: John Corredor Franco
Tema: Sincronización de hilos
Descripción: Este programa implementa un modelo de productor-consumidor en el que múltiples hilos productores y consumidores
se sincronizan mediante el uso de mutex y variables de condición. Los productores incrementan un contador compartido cuando
este es menor que un valor límite, y los consumidores lo decrementan cuando es mayor a cero. Se usa `pthread_cond_wait`
y `pthread_cond_signal` para coordinar el acceso a los recursos de manera que los productores esperen cuando el contador
llega al límite y los consumidores cuando el contador es cero.
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int counter = 0;
int max = 4;

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condp_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condc_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condVarProd = PTHREAD_COND_INITIALIZER;
pthread_cond_t condVarCons = PTHREAD_COND_INITIALIZER;

void *consumidor();
void *productor();

int main(int argc, char *argv[]) {
    pthread_t prodHilo[max];            // Vector de hilos productor
    pthread_t consHilo[max];            // Vector de hilos consumidor
    for (int i = 0; i < max; i++) {
        // Creación de hilos y envío de función Productor o Consumidor
        pthread_create(&prodHilo[i], NULL, &productor, NULL);
        pthread_create(&consHilo[i], NULL, &consumidor, NULL);
    }
    for (int i = 0; i < max; i++) {
        pthread_join(prodHilo[i], NULL);
        pthread_join(consHilo[i], NULL);
    }
    return 0;
}

void *productor() {
    while (1) {
        pthread_mutex_lock(&condp_mutex);
        while (counter >= 10) {
            pthread_cond_wait(&condVarProd, &condp_mutex);
        }
        pthread_mutex_unlock(&condp_mutex);

        pthread_mutex_lock(&counter_mutex);
        counter++;
        pthread_cond_signal(&condVarCons);
        printf("Soy el PRODUCTOR %d || Contador = %d\n", (int)pthread_self(), counter);
        pthread_mutex_unlock(&counter_mutex);

        if (counter > 7) {
            sleep(4);
        }
    }
}

void *consumidor() {
    while (1) {
        sleep(1);
        pthread_mutex_lock(&condc_mutex);
        while (counter <= 0) {
            pthread_cond_signal(&condVarProd);
            pthread_cond_wait(&condVarCons, &condc_mutex);
        }
        pthread_mutex_unlock(&condc_mutex);

        pthread_mutex_lock(&counter_mutex);
        if (counter > 0) {
            printf("Soy el CONSUMIDOR %d || Contador = %d\n", (int)pthread_self(), counter);
            counter--;
            pthread_cond_signal(&condVarProd);
        }
        pthread_mutex_unlock(&counter_mutex);
    }
}

