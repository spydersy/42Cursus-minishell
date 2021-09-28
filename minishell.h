/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:41:44 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/22 08:23:55 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include "./line_reader/get_next_line.h"

#include <readline/readline.h>
#include <readline/history.h>

		/*	COLORS		*/
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

# define STDIN  0
# define STDOUT 1
# define STDERR 2


/*	>				*/
/*	>>				*/
/*	<				*/
/*	<<				*/



void    print_toks(char **str, int nb);

# define CMD        9001 /*	arguments		*/
# define ARG        9002
# define REDO0		9003
# define REDO1		9004
# define REDI0		9005
# define REDI1		9006
# define FILE		9007 /*	file			*/
# define ERROR		9008 /*	error			*/
# define PROTECTED0	9009 /*	protected arg	*/
# define PROTECTED1	9010 /*	protected arg	*/
# define SKIPED		9011 /*	skiped tok		*/
# define HEREDOC	9012 /*	heredocs		*/
# define EOFHEREDOC	9013 /*	EOF Heredocs	*/

typedef struct s_quote
{
	bool				s_quote;
	bool				d_quote;
}						t_quote;

typedef struct s_env
{
	char				**env;
	char				**sorted;
	int					exit_status;
}						t_env;

typedef struct s_tokens
{
	int					nb;
	int					pipe;
	int					*type;
	char				**tokens;
	char				*exec_path;
}						t_tokens;

typedef struct s_separator
{
	int					*separator_index;
	int					nb_separator;
	char				**content;
}						t_separator;

typedef struct s_execution
{
    int                 nb_pipelines;		// DONE
	
    char                **args;				// DONE
	int					*args_type;			// DONE

	char                **files;			// DONE
	int					*files_type;		// DONE
	int					*fds;				

	char                *exec_path;			// DONE
	char				*command;			

	int					*exit_status;
}                       t_execution;


t_env					g_env;

int                     is_arg(int type);
int                     is_cmd(int type);
int						max_of(int i, int j);
int                     is_protected(int type);
int						count_bslash(char *line);
int						count_tokens(char *line);
int						bs_position(char **tokens);
int						*set_tok_types(t_tokens tok);
int						count_bs(char *line, int index);
int						*get_bslash_index(char *line, int nb);
int						ft_error(char *description, int exitstat);
int                     grammar_checker(char **commands, t_tokens *tokens);
int						empty_line(char *line);
int						count_arr(char **arr);
int abs_value(int nb);

int        			builtin_exit(char **args, int is_a_child_process);
int					builtin_env(void);
void					sort_env(void);
void					clear_window(void);
void					init_env(char **env);
void					free_toks(t_tokens tok);
void					execution(t_tokens *tokens);
void					extract_tokens(char **commands);
void					extract_semicolon_line(char *line);
void                	dollar_handling(char **tok, int index);
void					expand_quotes_dollar(t_tokens *tokens);
void					set_separator_type(int *type, char **toks);
void					minishell(int argc, char *argv[], char *envp[]);
int        			builtin_cd(char **path);
int			        builtin_echo(char **args, int *types);
void					free_arr(char **arr);
int					builtin_unset(char **args);
void					heredocs_parsing(t_execution *execution);

char					*prompt(void);
char					*read_line(void);
char        			**get_paths(void);
char					*builtin_pwd(int descriptor);
char					**split_tok(char *line, int nb);
char					*get_token(char *line, int flag);
char					**set_env(char *variable, char *value);
char        			*get_exec_path(t_tokens token, char **paths);
char					**splitSep(char *line, int *sepIndex, int nbSep);

t_quote					init_quote(void);
t_tokens				replace_dollar(t_tokens *tok);
t_quote					set_quote_value(char quote_type, t_quote to_quote);
t_separator				get_separator_index(char *line, char separator_type);
int	simple_builtin(t_execution *execution, int exit_flag);
t_execution    input_output_duplication(int index, int *pipes, t_execution *execution);


t_execution	*execute_line(t_execution *execution);
void	create_childs(t_execution *execution);
int get_fd(int index, t_execution *execution, int i);



void	print_types(int *types, int nb, char **tokens);
void	print_args2(char **args, int *types, char **files, int *files_type, int *fds);

#endif
