#include "../minishell.h"

int lsh_execute(t_headers *header)
{
	t_cmds *ncmd;

	ncmd = header->cmd_h;
  int i;

  if (ncmd->args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(ncmd->args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(ncmd->args);
    }
  }

  return lsh_launch(ncmd->args);
}