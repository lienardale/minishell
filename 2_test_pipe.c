  #include <stdio.h>
  #include <memory.h>
  #include <unistd.h>
  #include<sys/wait.h> 
 
  int main( int argc, char ** argv, char **env)
  {
	  (void)argc;
	  (void)argv;
	  pid_t	wpid;
	int		status;
   /* create the pipe */
   int pfd[2];
   if (pipe(pfd) == -1)
     {
       printf("pipe failed\n");
       return 1;
     }
  char *str[3];
  str[0] = "grep";
  str[1] = ".sh";
  str[2] = NULL;
   /* create the child */
   int pid;
   if ((pid = fork()) < 0)
     {
       printf("fork failed\n");
       return 1;
     }
 
   if (pid == 0)
     {
	   /* child */
	   printf("child goes BRAAA\n\n");
       close(pfd[0]); /* close the unused read side */
       dup2(pfd[1], 1); /* connect the write side with stdout */
       close(pfd[1]); /* close the write side */
       /* execute the process (ls command) */
       execlp("ls", "ls", (char *)0);
	//    str[0] = "ls";
	//     str[1] = NULL;
	//    execve("/usr/bin/ls", str, env);
       printf("ls failed"); /* if execlp returns, it's an error */
       return 0;
     }
   else
     {
      
	    wpid = waitpid(pid, &status, WUNTRACED);
	   printf("parent goes YIIIIII\n\n");
       /* parent */
       close(pfd[1]); /* close the unused write side */
       dup2(pfd[0], 0); /* connect the read side with stdin */
       close(pfd[0]); /* close the read side */
       /* execute the process (wc command) */
       execlp("grep", "grep", str[1], (char *)0);
	//    str[0] = "grep";
	   (void)env;
		// execve("/usr/bin/", str, env);
       printf("child failed\n\n"); /* if execlp returns, it's an error */
       return 0;
     }
   return 0;
  }