/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:41:44 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/15 10:43:34 by abelarif         ###   ########.fr       */
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
# include "./libft/libft.h"
# include "./line_reader/get_next_line.h"

		/*	COLORS		*/
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

		/*	TOK TYPES	*/
# define CMD			9001	/*	command			*/
# define	ARG			9002	/*	arguments		*/
# define REDO0		9003	/*	>				*/
# define	REDO1		9004	/*	>>				*/
# define REDI0		9005	/*	<				*/
// #define REDI0		9006	/*	<<				*/
# define FILE		9007	/*	file			*/
# define ERROR		9008	/*	error			*/
# define PROTECTED0	9009	/*	protected arg	*/
# define PROTECTED1	9010	/*	protected arg	*/
# define SKIPED		9011	/*	skiped tok		*/

		/*	DBG TOOLS	*/
# define DBG		    while(1){printf("DBG\n");}
# define	SLEEP(A)	printf(A); sleep(5)

typedef struct s_quote
{
	bool            	s_quote;
	bool            	d_quote;
}               		t_quote;

typedef	struct s_env
{
	char	**env;		//free_exit
	char	**sorted;	//free_exit
	char	**history;
	int		size;
}						t_env;

typedef struct s_tokens
{
	int					nb;
	int					pipe;
	int					*type;
	char				**tokens;
	char				*abs_path;
}						t_tokens;

typedef struct s_separator
{
	int					*separator_index;
	int					nb_separator;
	char				**content;
}						t_separator;

t_env					g_env;

int						max_of(int i, int j);
int						count_bslash(char *line);
int						count_bs(char *line, int index);
int						*get_bslash_index(char *line, int nb);
int						ft_error(char *description, int exitstat);
int						count_tokens(char *line);
int						*set_tok_types(t_tokens tok);
int						bs_position(char **tokens);

void					prompt(int sig);
void					to_execution(void);
void					free_toks(t_tokens tok);
void					init_env(char **env);
void					clear_window(void);
void					extract_semicolon_line(char *line);
void					minishell(int argc, char *argv[], char *envp[]);
void					extract_tokens(char **commands);
void					set_separator_type(int *type, char **toks);

char					*read_line(void);
char					**split_tok(char *line, int nb);
char					*get_token(char *line, int flag);
char					**splitSep(char *line, int *sepIndex, int nbSep);

t_tokens				replace_dollar(t_tokens *tok);
t_quote					init_quote(void);
t_quote					set_quote_value(char quote_type, t_quote to_quote);
t_separator				get_separator_index(char *line, char separator_type);

#endif
