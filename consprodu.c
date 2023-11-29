#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 1

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t empty_slots, full_slots;

void *producer(void *arg) {
    int item;

    while (1) {
        item = rand() % 100; // Generate a random item

        sem_wait(&empty_slots); // Wait for an empty slot in the buffer
        pthread_mutex_lock(&mutex);

        // Produce item and add it to the buffer
        printf("Producer produced item %d\n", item);
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full_slots); // Signal that a slot in the buffer is now full

        usleep(rand() % 1000000); // Simulate some processing time
    }

    return NULL;
}

void *consumer(void *arg) {
    int item;

    while (1) {
        sem_wait(&full_slots); // Wait for a full slot in the buffer
        pthread_mutex_lock(&mutex);

        // Consume item from the buffer
        item = buffer[out];
        printf("Consumer consumed item %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty_slots); // Signal that a slot in the buffer is now empty

        usleep(rand() % 1000000); // Simulate some processing time
    }

    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    // Initialize semaphores
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    // Wait for threads to finish (which will never happen in this example)
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(consumers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);

    return 0;
}
