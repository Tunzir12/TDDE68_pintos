#include "userprog/syscall.h"

#include "threads/interrupt.h"
#include "threads/thread.h"
#include "devices/shutdown.h"
#include "devices/timer.h"
#include "filesys/filesys.h"
#include "filesys/file.h"

#include <stdio.h>
#include <syscall-nr.h>

static void syscall_handler(struct intr_frame*);
void sleep(int millis);//test7
void halt(void) NO_RETURN; // in every error print 
bool create (const char *file, unsigned initial_size); //test 2
int open (const char *fileName); //test3
void close (int fd); //test3
bool remove (const char *file_name); //test6
void seek (int fd, unsigned position); //test9
unsigned tell (int fd); //test9
int filesize (int fd); //test8
int write (int fd, const void *buffer, unsigned size); //test4, test1
int read (int fd, void *buffer, unsigned size); //test5, test10
void exit (int status); //test10

void syscall_init(void)
{
	intr_register_int(0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void syscall_handler(struct intr_frame* f UNUSED)
{
	int syscall_handler_index = *((int *)(f->esp));

	switch (syscall_handler_index)
    {
    case SYS_SLEEP:
            {
              int milli = *((int*)(f->esp + 4));
              //printf("the milliseconds %d\n", millis);

              sleep(milli);
              printf("the milliseconds %d\n", milli);
              break;
            }
    case SYS_HALT:
            {
              halt();
              break;
            }
    case SYS_EXIT: 
             {
               int status = *((int*)(f->esp + 4));
               exit(status);
               break;
             }
    // case SYS_EXEC: // not in lab2
    //         {
    //           const char *fileName =  *(char**)(f->esp + 4);
    //           return exec(*fileName);
    //           break;
    //         }
    // case SYS_WAIT: // not in lab2
    //         {
    //           tid_t child_tid = *(tid_t*)(f->esp+4);
    //           break;

    //         }
    case SYS_CREATE:
            {
              const char *fileName =  *(char**)(f->esp + 4);
              unsigned fileSize = *((unsigned*)(f->esp + 8));
              f->eax = create(fileName, fileSize);
              break;
            }
    case SYS_REMOVE:
            {
              const char *fileName =  *(char**)(f->esp + 4);
              remove(fileName);
              break;
            }

    case SYS_OPEN:
            {
              const char *fileName =  *(char**)(f->esp + 4);
              f->eax = open(fileName);
              break;
            }
    case SYS_FILESIZE:
            {
              int fd = *((int*)(f->esp + 4));
              f->eax = filesize(fd);
              break;
            }
    case SYS_READ:
            {
              int fd = *((int*)(f->esp + 4));
              void *buffer = *(void**)(f->esp + 8);
              unsigned size = *((unsigned*)(f->esp + 12));
              f->eax = read(fd, buffer, size);
              break;
            }
    case SYS_WRITE:
            { 
              int fd = *((int*)(f->esp + 4));
              void *buffer = *(void**)(f->esp + 8);
              unsigned size = *((unsigned*)(f->esp + 12));
              f->eax = write(fd, buffer, size);
              break;
            }
    case SYS_SEEK:
            {
              int fd = *((int*)(f->esp + 4));
              unsigned position = *((unsigned*)(f->esp + 8));
              seek(fd, position);
              break;

            }
    case SYS_TELL:
            { 
              int fd = *((int*)(f->esp + 4));
              f->eax = tell(fd);
              break;
            }
    case SYS_CLOSE:
            { 
              printf("\nclose\n");
              int fd = *((int*)(f->esp + 4));
              close(fd);
              break;
            } 
}   

}

void sleep(int millis){
  timer_msleep(millis);
}

void halt(void){
    shutdown_power_off();
}

bool create (const char *file, unsigned initial_size){
  return filesys_create(file, initial_size);
}

int open(const char *fileName){

    struct file * file = filesys_open(fileName);
    struct thread* thread = thread_current();

    if(file == NULL){
      return -1;
    }

    for (int i = 2; i < 130; i++) {
        if(thread->file_id[i] == NULL) {
          thread->file_id[i] = file;
          return i;
        }
  }
  
  return -1;

}

void close (int fd){
    struct thread* thread = thread_current();
    struct file * file = thread->file_id[fd];
  
    thread->file_id[fd] = NULL;
    file_close(file);
}

bool remove (const char *file_name){
  if(filesys_remove(file_name)) return true;
  else return false ;
}

void seek (int fd, unsigned position){
  struct thread* thread = thread_current();
  struct file* file = thread -> file_id[fd] ;
  if (file == NULL){
    printf("operation failed : SEEK\n");
  }
  if (position < 0){
        position = 0;
  }
  file_seek(file, position);
}

unsigned tell(int fd){
  struct thread* thread = thread_current();
  struct file* file = thread -> file_id[fd];
  return file_tell(file);
}

int filesize (int fd){
    struct thread* thread = thread_current();
    struct file *file = thread->file_id[fd];

    if (file == NULL) {
        // Handle invalid file descriptor (return -1 or appropriate error code)
        return -1;
    }
    // Get the file size from the file structure
    int size = file_length(file); 
#include "devices/timer.h"
    return size;
}

int write (int fd, const void *buffer, unsigned size){
    if(fd == 0){
      return 0;
    }
    if(fd == 1){
      putbuf(buffer, size);
      return size;
    }
    
    struct thread* thread = thread_current();
    struct file * file = thread->file_id[fd];
    return file_write(file, buffer, size);

}

int read (int fd, void *buffer, unsigned size){
    struct thread* thread = thread_current();
    struct file * file = thread->file_id[fd];

    if (fd == 0) {
      for (int i = 0; i < size; i++) {
          *((uint8_t*)buffer + i) = input_getc();
        }
        return size;
    }

    if(file != NULL){
      return file_read(file, buffer, size);
    }
    else{
      return -1;
    }
}

void exit (int status){
    struct thread* thread = thread_current();
    // int fd = status ;
    // close(fd);
    // printf("file closed before exit\n");

    thread_exit();
    if(is_thread(thread)){
      status = -1;
    }
    else{
      status = 0;
    }

}
