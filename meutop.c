#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int readSignal(pid_t *pid, int *action) {
  fprintf(stdout, "> ");
  if(scanf("%d", pid) != 1) {
    fprintf(stdout, "Invalid pid\n");
    return 1;
  } else {
    if(scanf("%d", action) != 1) {
      fprintf(stdout, "Invalid signal action\n");
      return 1;
    }
  } 
  return 0;
}

void handleSignal() {
  int action;
  pid_t pid;
  
  while(readSignal(&pid, &action) == 0) {
    if(kill(pid, action) == 0) {
      printf("Signal sent! :)\n");
    } else {
      printf("Signal not sent :(\n");
    }
	};
}

int main(){
  printf("PID    | User    | PROCNAME | Estado |\n");
  printf("-------|---------|----------|--------|\n");

  DIR * dir = opendir("/proc/");
  struct dirent *ent;
  if(dir != NULL){
    // print all files within directory
    int pid, count = 0;
    while((ent = readdir(dir)) != NULL && count < 4000){
	  pid = atoi(ent->d_name);
      if(pid){
        printf("%7d\n", atoi(ent->d_name));
        count++;
      }
    }
    closedir(dir);
    handleSignal();
  }
  else{
    printf("Error opening directory\n");
    return 1;
  }
  return 0;
}
