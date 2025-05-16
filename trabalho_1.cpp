/*
 Aluno: Gabriel Augusto Morisaki Rita   RA: 2268191
*/

/**
 * Problema do Produtor-Consumidor
 * Na memória do sistema o produtor quer sempre escrever as informações
 * já o consumidor quer ler as informações na memória
 * deve-se encontrar uma maneira de que não aja um acesso simultâneo na
 * memória para que não ocorra erros de acesso
 */

/**
 * <iostream> básico input/output
 * <pthread.h> para criação de threads
 * <mutex> controle das threads
 * <semaphore.h> controle das threads
 * <unistd.h> acesso API para sistemas POSIX
 * <cstdlib> gerar números aleatórios
 */
#include <iostream>
#include <pthread.h>
#include <mutex>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>

// Tamanho do buffer
constexpr int BUFFER_SIZE = 5;

// Buffer e variáveis de controle
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semáforo para controlar o acesso à escrita/leitura
sem_t vazio, cheio;

// Mutex para controle de acesso ao buffer
std::mutex buffer_mutex;

bool encerrar_thread = false;

void *produtor(void *arg)
{
    int id = *(int *)arg;

    while (!encerrar_thread)
    {
        // Gerando números
        int rnum = std::rand() % 100;

        // Aguarda o semáforo
        sem_wait(&vazio);

        buffer_mutex.lock();

        if(encerrar_thread) 
        {
            buffer_mutex.unlock();
            break;
        }

        buffer[in] = rnum;
        in = (in + 1) % BUFFER_SIZE;

        std::cout << "Produtor " << id << " produziu " << rnum 
                  << " (Posição: " << in << ")" << std::endl;

        buffer_mutex.unlock();

        // Libera o semáforo
        sem_post(&cheio);

        usleep(300000);
    }

    return nullptr;
}

void *consumidor(void *arg) 
{
    int id = *(int *)arg;

    while(!encerrar_thread) 
    {
        // Aguarda o semáforo
        sem_wait(&cheio);

        buffer_mutex.lock();

        if(encerrar_thread) 
        {
            buffer_mutex.unlock();
            break;
        }

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        std::cout << "Consumidor " << id << " consumiu: " << item 
             << " (Posição: " << out << ")" << std::endl;

        buffer_mutex.unlock();

        // Libera o semáforo
        sem_post(&vazio);

        usleep(450000);
    }

    return nullptr;
}

int main()
{

    sem_init(&vazio, 0, BUFFER_SIZE);
    sem_init(&cheio, 0, 0);

    constexpr int QTD_PRODUTORES = 5;
    constexpr int QTD_CONSUMIDORES = 3;

    int produtor_id[QTD_PRODUTORES];
    int consumidor_id[QTD_CONSUMIDORES];

    // id para os produtores
    for(int i = 0; i < QTD_PRODUTORES; ++i) 
    {
        produtor_id[i] = i + 1;
    }

    // id para os consumidores
    for(int i = 0; i < QTD_CONSUMIDORES; ++i) 
    {
        consumidor_id[i] = i + 1;
    }

    pthread_t produtores[QTD_PRODUTORES];
    pthread_t consumidores[QTD_CONSUMIDORES];

    // Cria as threads
    for(int i = 0; i < QTD_PRODUTORES; ++i) 
    {
        pthread_create(&produtores[i], nullptr, produtor, &produtor_id[i]);
    }

    // Cria as threads
    for(int i = 0; i < QTD_CONSUMIDORES; ++i) 
    {
        pthread_create(&consumidores[i], nullptr, consumidor, &consumidor_id[i]);
    }

    sleep(5);
    encerrar_thread = true;

    for (int i = 0; i < QTD_CONSUMIDORES; ++i) {
        sem_post(&cheio);  // Desbloqueia consumidores
    }

    for (int i = 0; i < QTD_PRODUTORES; ++i) {
        sem_post(&vazio);  // Desbloqueia produtores
    }

    // Aguarda todas as threads terminarem
    for(int i = 0; i < QTD_PRODUTORES; ++i) 
    {
        pthread_join(produtores[i], nullptr);
    }

    for(int i = 0; i < QTD_CONSUMIDORES; ++i) 
    {
        pthread_join(consumidores[i], nullptr);
    }
    
    // Destroi os semáforos
    sem_destroy(&vazio);
    sem_destroy(&cheio);

    std::cout << "Fim do programa" << std::endl;
}