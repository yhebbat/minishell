#include "../minishell.h"

void	dup2_in_out(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
}

int	fork_last_process(int in, int *pipefd, t_cmds *cmd_h)
{
	(void)in;
	(void)pipefd;
	g_variables.pid = fork();
	if (g_variables.pid == 0)
	{
		 if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (pipefd[1] > 2)
			close(pipefd[1]); 


		// redirection part
		if ( cmd_h->file_h  && cmd_h->file_h->filename != NULL)
		redirection(cmd_h);


		// execute
		if (execvp(cmd_h->args[0], cmd_h->args) == -1)
		{
			printf("%s\n", strerror(errno));
			exit(0);
		}
	}
	return (EXIT_SUCCESS);
}

int	fork_process(int in, int *pipefd, t_cmds *cmd_h)
{
	(void)in;
	(void)pipefd;
	g_variables.pid = fork();
	if (g_variables.pid == 0)
	{
		dup2_in_out(in, pipefd[1]);


		// redirection part
		if (cmd_h->file_h && cmd_h->file_h->filename != NULL)
		redirection(cmd_h);


		// execute
		if (execvp(cmd_h->args[0], cmd_h->args) == -1)
		{
			printf("%s\n", strerror(errno));
			exit(0);
		}
	}
	return (EXIT_SUCCESS);
}

int launch(t_headers *header)
{
	int status;
	int	pipefd[2];
	int	in = 0;
	t_cmds *cmd;

	cmd = header->cmd_h;
	// THIS IS MY MAIN LOOP IN CASE WE HAVE PIPES
	while (cmd->next != NULL)
	{
		 pipe(pipefd); 

		// TO-DO : WRITE A FUNCTION THAT WILL EXECUTE AND DO A FORK
		fork_process(in, pipefd, cmd);


 		if (pipefd[1] > 2)
			close(pipefd[1]);
		if (in != STDIN_FILENO)
			close(in);
		in = pipefd[0]; 
		cmd = cmd->next;
	}

	// TO-DO : EXECUTE LAST COMMAND
	fork_last_process(in, pipefd, cmd);


	// THIS IS THE PARENT PROCESS
 	if (in != STDIN_FILENO)
		close(in); 
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_variables.exit_status = WEXITSTATUS(status);
}
