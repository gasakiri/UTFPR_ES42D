#include <iostream>
#include <pthread.h>
#include <mutex>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

// Tamanho do buffer compartilhado
const int BUFFER_SIZE = 5;

// Buffer compartilhado e variáveis de controle
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Mutex para controle de acesso ao buffer
mutex buffer_mutex;

// Semáforos para controle de slots vazios e ocupados
sem_t empty_slots;
sem_t full_slots;

// Flag para encerrar as threads
bool done = false;

// Função do produtor
void* producer(void* arg) {
    int id = *(int*)arg;
    
    while (!done) {
        // Gerar um item (simplificado)
        int item = rand() % 100;
        
        // Aguardar slot vazio
        sem_wait(&empty_slots);
        
        // Adquirir lock para acessar o buffer
        buffer_mutex.lock();
        
        // Inserir item no buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        
        cout << "Produtor " << id << " produziu: " << item 
             << " (Posição: " << in << ")" << endl;
        
        // Liberar lock
        buffer_mutex.unlock();
        
        // Sinalizar que há um slot ocupado
        sem_post(&full_slots);
        
        // Dormir por um tempo aleatório
        usleep(rand() % 300000); // 0-300ms
    }
    return nullptr;
}

// Função do consumidor
void* consumer(void* arg) {
    int id = *(int*)arg;
    
    while (!done) {
        // Aguardar slot ocupado
        sem_wait(&full_slots);
        
        // Adquirir lock para acessar o buffer
        buffer_mutex.lock();
        
        // Remover item do buffer
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        
        cout << "Consumidor " << id << " consumiu: " << item 
             << " (Posição: " << out << ")" << endl;
        
        // Liberar lock
        buffer_mutex.unlock();
        
        // Sinalizar que há um slot vazio
        sem_post(&empty_slots);
        
        // Dormir por um tempo aleatório
        usleep(rand() % 300000); // 0-300ms
    }
    return nullptr;
}

int main() {
    // Inicializar semáforos
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);
    
    // Número de produtores e consumidores
    const int NUM_PRODUCERS = 3;
    const int NUM_CONSUMERS = 3;
    
    // IDs das threads
    int producer_ids[NUM_PRODUCERS] = {1, 2, 3};
    int consumer_ids[NUM_CONSUMERS] = {1, 2, 3};
    
    // Threads
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    
    // Criar threads produtoras
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_create(&producers[i], nullptr, producer, &producer_ids[i]);
    }
    
    // Criar threads consumidoras
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_create(&consumers[i], nullptr, consumer, &consumer_ids[i]);
    }
    
    // Executar por 10 segundos
    sleep(10);
    
    // Sinalizar para encerrar as threads
    done = true;
    
    // Aguardar threads produtoras
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_join(producers[i], nullptr);
    }
    
    // Aguardar threads consumidoras
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(consumers[i], nullptr);
    }
    
    // Destruir semáforos
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    
    cout << "Simulação concluída. Itens restantes no buffer: " 
         << (in - out + BUFFER_SIZE) % BUFFER_SIZE << endl;
    
    return 0;
}