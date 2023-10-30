# Minishell

	A Unix Shell designed to resemble the functionality of Bash.

## More details

The shell handles the following functionality:

* **Built-in functions**
	* `echo` Displays the line of text that is passed in as an argument.
	* `cd` Changes current working directory.
	* `pwd` Displays the current working directory.
	* `export` Is used to make a variable or function available to child processes.
	* `unset` Is used to remove a variable or function, making it no longer accessible or defined.
	* `env` Displays a list of environment variables and their values for the current session.
	* `exit` Exits the shell.

* **Redirections**
	* `<` Input redirection.
	* `>` Output redirection.
	* `>>` Output redirection in append mode.
	* `<<` Heredoc.
	* `Pipe` The output of each command in the pipeline is connected to the input of the next command.

* **Signals**
	* `ctrl-C` Cancels the current state and displays a new prompt on a new line.
	* `ctrl-D` If inside of a child process, it kills it, otherwise it exits the shell.
	* `ctrl-\` Is blocked.

* **Special characters**
	* `Single quote` Prevents the shell from interpreting the metacharacters in the quoted sequence.
	* `Double quote` Prevents the shell from interpreting the metacharacters in the quoted sequence except for `$`.
	* `Dollar sign` Finds the environment variable and expands to its value.
	* `$?` Expands to the exit status of the most recently executed foreground pipeline.

* **Other executables**
	* If a key is typed that doesn't match any of the above commands, the shell will search for an existing executable on the system based on the PATH variable of the environment or using a relative or an absolute path.

## How?

The shell was written in C.
An abstract syntax tree was implemented to make the following things easier:

* Analyze and manipulate the command input.
* Error handling, and providing meaningful error messages when dealing with complex or malformed commands.
* Hierarchical representation of the commands.
* Modularity, making the shell more extensible, allowing us to add new features with ease.

For those reasons, implementing an AST was well worth it, despite the added complexity in the development process.
It was also a great learning experience, giving us a good understanding of tree data structures.