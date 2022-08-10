#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"

/**
 * main - calls two custom functions
 * first function - prints prompt string
 * second function - reads the next line of imput
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *cmd;

	do
	{
		print_prompt1();

		cmd = read_cmd();

		if(!cmd)
		{
			exit(EXIT_SUCCESS);
		}

		if(cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
		{
			free(cmd);
			break;
		}

		printf("%s\n", cmd);

		free(cmd);

	} while(1);

	exit(EXIT_SUCCESS);
}

/**
 * stdin - 1024-byte chunks and store the input in a buffer
 * print_prompt2 - s printed by the shell when you enter a multi-line command
 *
 * Reurn: Always 0
 */
char *read_cmd(void)
{
	char buf[1024];
	char *ptr = NULL;
	char ptrlen = 0;

	 while(fgets(buf, 1024, stdin))
	 {
		 int buflen = strlen(buf);

		 if(!ptr)
		 {
			 ptr = malloc(buflen+1);
		 }
		 else
		 {
			 char *ptr2 = realloc(ptr, ptrlen+buflen+1);

			 if(ptr2)
			 {
				 ptr = ptr2;
			 }
			 else
			 {
				 free(ptr);
				 ptr = NULL;
			 }
		 }

		 if(!ptr)
		 {
			 fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
			 return NULL;
		 }

		 strcpy(ptr+ptrlen, buf);

		 if(buf[buflen-1] == '\n' )
		 {
			 if(buflen == 1 || buf[buflen-2] != '\\')
			 {
				 return ptr;
			 }

			 ptr[ptrlen+buflen-2] = '\0';
			 buflen -= 2;
		 }

		 ptrlen += buflen;
	 }

	 return ptr;
}
