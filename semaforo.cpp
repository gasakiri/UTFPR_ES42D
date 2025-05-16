/*Exemplo simples e comentado de como utilizar semáforos POSIX em C++ 
para sincronizar o acesso a uma variável compartilhada entre múltiplas threads. 
Este exemplo simula um contador que é incrementado por várias threads, 
utilizando um semáforo para garantir que apenas uma thread acesse a variável por vez.​


Exemplo em C++ com Semáforos POSIX
*/

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Variável compartilhada
int contador = 0;

// Semáforo para controlar o acesso à variável compartilhada
sem_t semaforo;

// Função que será executada pelas threads
void* incrementar(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < 5; ++i) {
        sem_wait(&semaforo); // Aguarda o semáforo (P)
        // Início da seção crítica
        int temp = contador;
        std::cout << "Thread " << id << " leu contador: " << temp << std::endl;
        temp += 1;
        contador = temp;
        std::cout << "Thread " << id << " incrementou contador para: " << contador << std::endl;
        // Fim da seção crítica
        sem_post(&semaforo); // Libera o semáforo (V)
        sleep(1); // Simula trabalho
    }
    return nullptr;
}

int main() {
    // Inicializa o semáforo com valor 1 (semáforo binário)
    sem_init(&semaforo, 0, 1);

    const int NUM_THREADS = 3;
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    // Cria as threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        ids[i] = i + 1;
        pthread_create(&threads[i], nullptr, incrementar, &ids[i]);
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], nullptr);
    }

    // Destroi o semáforo
    sem_destroy(&semaforo);

    std::cout << "Valor final do contador: " << contador << std::endl;
    return 0;
}
/*
Explicação
sem_init(&semaforo, 0, 1); Inicializa o semáforo com valor 1, indicando que apenas uma thread pode acessar a seção crítica por vez.​

sem_wait(&semaforo); Decrementa o valor do semáforo. Se o valor for zero, a thread é bloqueada até que o semáforo seja liberado.​

sem_post(&semaforo); Incrementa o valor do semáforo, permitindo que outra thread acesse a seção crítica.​
Delft Stack

pthread_create(...) Cria novas threads que executam a função incrementar.​

pthread_join(...) Aguarda que todas as threads terminem sua execução.​

sem_destroy(&semaforo); Libera os recursos alocados para o semáforo.​
*/
