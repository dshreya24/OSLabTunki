#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

pthread_mutex_t read_mutex = PTHREAD_MUTEX_INITIALIZER; //mutex is used to control access to the readers_count variable
pthread_mutex_t write_mutex = PTHREAD_MUTEX_INITIALIZER; //write_mutex is used to ensure exclusive access to the shared resource (shared_data)

int shared_data = 0; //shared_data is the data being read/written
int readers_count = 0; //readers_count keeps track of the number of active readers.

void *reader(void *arg) {
    int reader_id = *((int *)arg);

    while (1) {
        pthread_mutex_lock(&read_mutex);
        readers_count++;
        if (readers_count == 1) {
            pthread_mutex_lock(&write_mutex);  // First reader locks the write_mutex
        }
        pthread_mutex_unlock(&read_mutex);

        // Reading the shared resource
        printf("Reader %d is reading: %d\n", reader_id, shared_data);

        pthread_mutex_lock(&read_mutex);
        readers_count--;
        if (readers_count == 0) {
            pthread_mutex_unlock(&write_mutex);  // Last reader unlocks the write_mutex
        }
        pthread_mutex_unlock(&read_mutex);

        // Simulating some processing time for reading
        usleep(rand() % 1000000);
    }
    return NULL;
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);

    while (1) {
        pthread_mutex_lock(&write_mutex);

        // Writing to the shared resource
        shared_data++;
        printf("Writer %d is writing: %d\n", writer_id, shared_data);

        pthread_mutex_unlock(&write_mutex);

        // Simulating some processing time for writing
        usleep(rand() % 1000000);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    // Create reader threads
    for (int i = 0; i < NUM_READERS; ++i) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for threads to finish (which will never happen in this example)
    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writers[i], NULL);
    }

    return 0;
}
