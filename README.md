
# Productor-Consumidor en C

Este proyecto implementa un modelo de **Productor-Consumidor** utilizando hilos en C, con el objetivo de demostrar la sincronización de múltiples hilos mediante el uso de **mutex** y **variables de condición** de la biblioteca `pthread`.

## Descripción del Código

El código consta de un único archivo principal `code02.c`, que contiene la implementación del modelo de productor-consumidor. A continuación, se detallan las principales secciones del código:

- **Variables Globales**: Se definen variables globales que incluyen un contador compartido, mutex para la protección del acceso y variables de condición para la sincronización entre hilos.
  
- **Funciones**:
  - `void *productor()`: Función que simula el comportamiento del productor. Incrementa el contador y utiliza `pthread_cond_wait` para esperar cuando el contador alcanza el límite y `pthread_cond_signal` para notificar a los consumidores.
  - `void *consumidor()`: Función que simula el comportamiento del consumidor. Decrementa el contador y espera cuando el contador es cero, notificando a los productores cuando hay espacio disponible.

- **Función `main`**: Crea hilos para productores y consumidores, y espera a que todos los hilos terminen su ejecución.
