#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main(){
  printf("PID    | User    | PROCNAME | Estado |\n");
  printf("-------|---------|----------|--------|\n");

  DIR * dir = opendir("/proc/");
  struct dirent *ent;
  if(dir != NULL){
    // print all files within directory
    int pid, count = 0;
    while((ent = readdir(dir)) != NULL && count < 20){
      pid = atoi(ent->d_name);
      if(pid){
        printf("%7d\n", atoi(ent->d_name));
        count++;
      }
    }
    closedir(dir);
  }
  else{
    printf("Error opening directory\n");
    return 1;
  }
  return 0;
}
