#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

 int main(){
   int READ = 0;
   int WRITE = 1;
   int child;
   int fds1[2];//parent->child
   int fds2[2];//child->parent
   int buffer;
   
   pipe(fds1);
   pipe(fds2);
   child = fork();
   if(!child){//if child1...
     printf("[child] reading from pipe...\n");
     read(fds1[READ], &buffer, sizeof(buffer));
     printf("[child] got %d...sending %d+25...\n", buffer);
     buffer += 25;
     write(fds2[WRITE], &buffer, sizeof(buffer)); 
     exit(1);
   }
   int msg = 12;
   printf("[parent] sending: %d\n", msg);
   write(fds1[WRITE], &msg, sizeof(msg));
   printf("[parent] reading from pipe...\n");
   read(fds2[READ], &buffer, sizeof(buffer));
   printf("[parent] got %d\n", buffer);
   return 0;
 }
