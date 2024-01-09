#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

#define BLOCK_SIZE 20

int readFile(int fd, char* buf, int size){
    // Implementation
    return -1;
}

char* getBlock(int fd) {
    char* buf = (char*) malloc(BLOCK_SIZE);
    if (!buf) {
        return NULL;
    }
    if (readFile(fd, buf, BLOCK_SIZE) != BLOCK_SIZE) {
        return NULL;
    }
    return buf;
}

struct shared_ptr{
    int *ptr;
    int *count;
};

struct shared_ptr create_shared_ptr(int *ptr, int *cnt){
    struct shared_ptr sptr;
    sptr.ptr = ptr;
    *cnt = *cnt + 1;
    return sptr;
}
void delete_shared_ptr(struct shared_ptr sptr, int *cnt){
    //This will not decrease cnt value, the resource will never be deleted.
    *cnt - 1;
    if(*cnt == 0){
        free(sptr.ptr);
    }
}
void use_shared_ptr(){
    int count = 0;
    int *ptr = malloc(sizeof(int));
    int *cnt = &count;
    struct shared_ptr sptr1 = create_shared_ptr(ptr, cnt);
    struct shared_ptr sptr2 = create_shared_ptr(ptr, cnt);
    delete_shared_ptr(sptr1, cnt);
    delete_shared_ptr(sptr2, cnt);
}

int main(int argc, char** argv) {
  char cmd[256] = "/usr/bin/cat ";
  strcat(cmd, argv[1]);
  system(cmd);
  return 0;
}

void file_range_error() {
  // Open the file for reading
  FILE* fp = fopen("myfile.txt", "r");
  char buf[111];

  // Read 100 bytes from the file at an offset of 200
  fseek(fp, 200, SEEK_SET);
  fread(buf, 1, 100, fp);

  // Close the file
  fclose(fp);

  // if the file has only 100 bytes, it will cause error
}

void classic_buffer_overflow() {
  char last_name[20];
  printf ("Enter your last name: ");
  // Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')
  scanf ("%s", last_name);
}

#define SIZE 20
void double_free(int abrt) {
    char* ptr = (char*)malloc (SIZE);
    // ...
    if (abrt) {
        free(ptr);
    }
    // ...
    free(ptr);
}

char* buffer;
void handler(int sigNum) { buffer = (char*)malloc(10 * sizeof(char)); }
int handleSignal() {
  signal(SIGUSR1, handler);
  signal(SIGUSR2, handler);
  sleep(5);
}

pthread_mutex_t mutex;
void func1(){
    pthread_mutex_lock(&mutex);
    pthread_mutex_unlock(&mutex);
    // double unlock
    pthread_mutex_unlock(&mutex);
}

void func2(){
    pthread_mutex_init(&mutex, NULL);
    // double unlock event
    pthread_mutex_unlock(&mutex);
}
