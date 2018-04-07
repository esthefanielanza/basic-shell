#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#define clear() printf("\033[H\033[J")

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

void * handleSignal() {
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


void printTopProcess(int top){
  printf("PID  | User     | PROCNAME      | Estado |\n");
  printf("-----|----------|---------------|--------|\n");

  DIR * dir = opendir("/proc/");
  struct dirent *ent;
  char file_name[50], line[500], p_name[20], p_state[20], char_trash[500];
  int  p_uid;
  if(dir != NULL){
    // print all files within directory
    int pid, count = 0;
    while((ent = readdir(dir)) != NULL && count < top){
      pid = atoi(ent->d_name);
      if(pid){
        printf("%5d|", atoi(ent->d_name));

        int i = 0;
        sprintf(file_name, "/proc/%s/status", ent->d_name);
        FILE * file = fopen(file_name, "r");
        while(fgets(line, sizeof(line), file)){
          if(i == 0){
            sscanf(line, "%s %s", char_trash, p_name);
          } else if(i == 1){
            sscanf(line, "%s %s", char_trash, p_state);
          }
          else if(i == 7){
            sscanf(line, "%s %d", char_trash, &p_uid);
            break;
          }
          i++;
        }
        struct passwd *pw = getpwuid(p_uid);
        if(pw) printf("%10s|", pw->pw_name);
        p_name[14] = '\0';
        printf("%15s|", p_name); // name
        printf("%8s|\n", p_state); // state
        fclose(file);
        count++;
      }
    }
    closedir(dir);
    handleSignal();
  }
  else{
    printf("Error opening directory\n");
    exit(1);
  }
}

void * top(){
  int n_refresh = 0;
  while(1){
    clear();
    printf("Numero de refreshs: %d\n", n_refresh);
    printTopProcess(30);
    sleep(1);
  }
}

int main(){
  pthread_t a, b;
  pthread_create(&a, NULL, top, NULL);
  pthread_create(&b, NULL, handleSignal, NULL);
  pthread_join(a, NULL);
  pthread_join(b, NULL);
  return 0;
}

//getent passwd 1008 | cut -d: -f1
