#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);
  while (1)
  {
    // Uncomment this block to pass the first stage
    printf("$ ");

    // Wait for user input
    char input[512];

    if(fgets(input, 100, stdin)==NULL)
    {
      break;
    }

    input[strlen(input)-1]='\0';
    
    if (strcmp(input,"exit 0")==0)
    {
      break;
    }

    else if (strncmp("echo",input,4)==0)
    {
      printf("%s\n",input+5);
    }

    else if (strncmp("type",input,4)==0)
    {
      //strtok used to split the whole string into tokens
      char *comTok = strtok(input," "); 
      
      while (comTok!=NULL)
      {
        comTok=strtok(NULL," ");

        if (strncmp("echo",comTok,4)==0)
        {
          printf("echo is a shell builtin\n");
          break;
        }
        else if (strncmp("exit",comTok,4)==0)
        {
          printf("exit is a shell builtin\n");
          break;
        }
        else if (strncmp("type",comTok,4)==0)
        {
          printf("type is a shell builtin\n");
          break;
        }
        else
        {
          printf("%s: not found\n",comTok);
          break;
        }
         
      }
      
    }

    else
    {
      printf("%s: command not found\n", input);
    }
    
  }
  return 0;
}
