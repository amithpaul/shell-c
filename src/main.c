#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COM_LENGTH 1024

void checkType(char *input)
{ 
  char *path=strdup(getenv("PATH"));
  char *com_tocheck= input +5;

  if (strncmp("echo",com_tocheck,4)==0 || 
      strncmp("exit",com_tocheck,4)==0 ||
      strncmp("type",com_tocheck,4)==0 )
  {
    printf("%s is a shell builtin\n",input+5);
    return;
  }
  
  else if (path!=NULL)
  {
    char *dir =strtok(path,":");
    while (dir!=NULL)
    {
      char full_path[MAX_COM_LENGTH];
      //appends command to directory path
      snprintf(full_path,sizeof(full_path),"%s/%s",dir,com_tocheck);

      if (access(full_path,X_OK)==0) //access is linux system call used to check the acess of a process
      {
        printf("%s is %s\n",com_tocheck,full_path);
        free(path);
        return;
      }
      dir = strtok(NULL,":");
    }
    free(path);
  }    
  
  printf("%s: not found\n",input+5);
  return;     
}


int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);
  
  char input[MAX_COM_LENGTH];
  while (1)
  {
    // Uncomment this block to pass the first stage
    printf("$ ");
    // Wait for user input
    //empty check
    if(fgets(input, 100, stdin)==NULL)
    {
      break;
    }
    
    input[strlen(input)-1]='\0';
    char *path=strdup(getenv("PATH"));

    //exit condition
    if (strcmp(input,"exit 0")==0)
    {
      break;
    }

    //echo statement exec
    else if (strncmp("echo",input,4)==0)
    {
      printf("%s\n",input+5);
      continue;
    }
    
    //type check
    else if (strncmp("type",input,4)==0)
    {
      checkType(input);
      continue;
    }
    
    char *args[1024];
    int i = 0;
    
    char *tok = strtok(input," ");
    while (tok!=NULL)
    {
      args[i++]=tok;
      tok=strtok(NULL," ");
    }
    args[i]=NULL;

    // pid_t pid = fork();

    
      execvp(args[0],args);
      printf("%s: command not found\n", input); 
    
  }
  return 0;
}
