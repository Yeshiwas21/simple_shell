#include "shell.h"

/**
 * help_for_all - Displays help info all possible builtin commands
 */
void help_for_all(void)
{
	char *msg = "Shellby\n"
		    "These shell commands are defined internally.\n"
		    "Type 'help' to see this list.\n"
		    "Type 'help name' to find out more about the function 'name'.\n\n"
		    "  alias    \talias [NAME[='VALUE'] ...]\n"
		    "  cd       \tcd [DIRECTORY]\n"
		    "  exit     \texit [STATUS]\n"
		    "  env      \tenv\n"
		    "  setenv   \tsetenv [VARIABLE] [VALUE]\n"
		    "  unsetenv \tunsetenv [VARIABLE]\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_for_cd - Displays help info on the 'cd' builtin command
 */
void help_for_cd(void)
{
	char *msg = "cd: cd [DIRECTORY]\n"
		    "\tChanges the current directory of the process to DIRECTORY.\n\n"
		    "\tIf no argument is given, the command is interpreted as cd $HOME. "
		    "If the argument '-' is given, the command is interpreted as cd $OLDPWD.\n\n"
		    "\tThe environment variables PWD and OLDPWD are updated after a change of directory.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_for_exit - Displays information on the shellby builtin command 'exit'.
 */
void help_for_exit(void)
{
	char *msg = "exit: exit [STATUS]\n"
		    "\tExits the shell.\n\n"
		    "\tThe STATUS argument is the integer used to exit the shell. "
		    "If no argument is given, the command is interpreted as exit 0.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_for_alias - Displays help info on the command 'alias'.
 */
void help_for_alias(void)
{
	char *msg = "alias: alias [NAME[='VALUE'] ...]\n"
		    "\tHandles aliases.\n"
		    "\n\talias: Prints a list of all aliases, one per line, in "
		    "the format NAME='VALUE'.\n"
		    "\talias name [name2 ...]: Prints the aliases name, name2, etc. one per line, in the form "
		    "NAME='VALUE'.\n"
		    "\talias NAME='VALUE' [...]: Defines an alias for each NAME whose VALUE is given. "
		    "If NAME is already an alias, replace its value with VALUE.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_for_help - Displays information on the shellby builtin command 'help'.
 */
 
void help_for_help(void)
{
	char *msg = "help: help\n"
		    "\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\n      help [BUILTIN NAME]\n"
		    "\tSee specific information on each builtin command.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}
