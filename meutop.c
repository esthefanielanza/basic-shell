#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
int main(){
  DIR * dir = opendir("/proc/");
  struct dirent *ent;
  if(dir != NULL){
    // print all files within directory
    while((ent = readdir(dir)) != NULL)
      printf("%s\n", ent->d_name);
    closedir(dir);
  }
  else{
    printf("Error opening directory\n");
    return 1;
  }
  return 0;
}
