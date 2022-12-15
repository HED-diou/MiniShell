/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:08:36 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/11 12:10:25 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_env {
	char			*title;
	char			*val;
	int				sw;
	int				index;
	struct s_env	*next;
}t_env;

// >>> minishell.c <<
typedef struct mini {
	int			a;
	char		*cmd;
	int			fd[2];
	char		operater;
	char		**option;
	char		**herdog;
	char		**rederct;
	char		**temp;
	struct mini	*next;
}t_mini;

typedef struct data {
	int	flag[2];
	int	sig;
	int	a;
	int	exitcode;
}t_data;

t_data	g_data;

//void		print_pipe(t_mini *mini);

void		flag_rest(char **str, int a);
int			count_param(char *str, int a);
char		*ft_strchr(const char *str, int c);

// >>> utils.c <<<

void		ft_realloc(char **str, int size);
int			ft_strlen(const char *str);
int			is_space(char c);
int			is_param(char c);

// >>> utils2.c <<< 

void		fprint(char *str);
char		**ft_split(const char *s, char c);
int			read_line(int fd, char **str);
void		lst_add_back(t_mini **mini, t_mini *lst);
char		*ft_strdup(char *t1);

// >>> utils3.c <<<

void		set_struct(t_mini *struc, char *str);
void		search_str(t_mini *var, char *s2, int *a, int *b);
void		delete_str(t_mini *var, char **s1, char *s2);
void		fill_temp(char **temp, char *str, int b);
void		insert_str(t_mini *var, char **str, char *s1, char *s2);

// >>> utils4.c <<<
char		*ft_itoa(int num);
void		herdoc_sig(int sig);
void		check_sig(int fd, char *c);
// >>> ft_error.c <<<

int			ft_errors(char *str, t_env *env);
void		null_line(char *line);

// >>> parce_errors.c //

int			check_next_normal(t_mini *mini, int a);
int			check_next_double(t_mini *mini, int a);
int			check_first(void);
int			check_pipe(t_mini *mini, int a);
int			check_errors(t_mini *mini);

// >>> open_pipe.c <<<

void		open_pipe(char **str, t_env *env);

// >>>prep_exec.c <<<

char		**convert_env(t_env *envp);
void		ft_env(char **env, t_env **envp);
void		prep_exec(t_mini *mini, t_env **envp);

// >>> herdoc_fun.c <<<

void		ixit(int key);
void		excute_hedoc_2(t_mini *mini, t_env *env);
void		fill_herdoc(t_mini *mini, t_env *env);
void		herdoc_sig(int sig);
int			save_sig(t_mini *mini);

// >>> start_parce.c <<<

void		fill_list(char **str, t_mini **mini, t_env *env);
void		ft_essentials(t_mini *mini, t_env *env, char **str);
void		global_copy(t_mini **mini, t_mini **lst);

// >>> pipe_fun.c <<<

int			valid_pipe(char *str, int c);
void		valid_pipes(t_mini *mini);

//>>> expand_var.c <<<

int			allowed_chars(char c);
void		simple_all(char **str, t_env *env);

// >>> delete_var.c <<<

char		*get_env(t_env *env, char *str);
void		delete_invalid_vars(t_mini *mini, t_env *env, char **str);

// >> history_func.c <<

void		charge_history(void);
void		record_history(char *str);

// >>> duplicat_quote.c <<

void		flag_quotes(t_mini *mini, int a, int i);
void		delete_quote(t_mini *mini, char **line);
int			serach_quote(t_mini *mini, int a);

// >>> single_quote_error <<<

void		shift_str(t_mini *mini, int a, int c);
int			single_quote_error(t_mini *mini);
void		strcpy_adres(char **str, char *s);
void		strcat_adres(char **str, char *s);
char		*remove_quote(char *str);
// >>> set_space.c <<

void		set_space(t_mini *mini);

// >>> cut_outfile.c <<< //

int			get_input_file(t_mini *mini, int a, int b);
int			count_them(t_mini *mini);
void		get_simple_input(t_mini *mini);

// >>> cut_infile.c <<< 

void		get_simple_output(t_mini *mini);
// >>> cut_herdog.c <<<

void		get_simple_herdog(t_mini *mini);
// >>> cut_catfile.c <<

void		get_simple_catfile(t_mini *mini);
// >>> simple_cmd.v <<<
//
void		get_simple_cmd(t_mini *mini);
void		simple_qoute(t_mini *mini, char **str);
void		get_simple_option(t_mini *mini);
void		print_everthing(t_mini *mini);

// >>> valid_opertaors.c <<<

void		valid_opertors(t_mini *mini);

// >>> parce_errors.c <<<

void		free_temps(t_mini *mini);
void		free_all(t_mini *mini);
void		free_list(t_mini **mini);
int			pipe_error(char *str);
void		fill_par(t_mini *par, char *str);

// >>env_var.c <<<

void		valid_var(t_mini *mini);
void		check_sig(int fd, char *c);

//      	>> EXECUTION <<
void		execution(t_mini *mini, t_env **envp, char **env);
void		print_pwd(t_env *envp);
void		ft_envp(t_env *envp, t_mini *mini);
void		ft_cd(char *cd, t_env *envp);
char		*ft_home(t_env *envp);
void		ft_echo(char **cmd);
void		ft_unset(t_env **envp, char **line);
void		ft_lstdelone(t_env *lst, void (*del)(void*));
void		ft_export(t_env **envp, char **c);
t_env		*ft_envnew(char *title, char *content, int i);
int			ft_lstsize(t_env *lst);
int			ft_lstsize1(t_mini *lst);
void		ft_envadd_back(t_env **alst, t_env *new);
t_env		*ft_lstlast(t_env *lst);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char *s1, char *set);
char		*ft_strdup(char *str);
void		exec_builtins(t_mini *mini, t_env **envp);
int			is_builtins(char *cmd);
void		exec_herdog(t_mini *mini);
long long	ft_atoi(char *str);
void		ft_exit(t_mini *mini);
int			ft_isdigit(int arg);
char		*ft_strnstr( const char *big, const char *little, size_t len );

void		join_val(t_env **envp, char *title, char *option, int a);
int			valid_title(char *var);
char		*ft_strcher(char *str, int ch);
int			char_chr(char *line, char c);
void		join_val_helper_plus(t_env **envp, char *title, \
		char *tmp, char *val);
void		join_val_help(t_env **envp, char *title, char *val, char *tmp);
void		set_zero(t_env **node);
void		set_index_helper(t_env **st, t_env *temp1, t_env *temp2);
void		set_index(t_env **st);
int			exist_node(t_env *envp, char *title);
void		replache_node(t_env *envp, char *title, char *val);
int			ft_isdigit(int arg);
int			ft_isalpha(int chr);
void		print_export_line(t_env *envp);
void		ft_print_export(t_env **head);
t_env		*ft_getnode(t_env *node);
void		ft_put_err(char *cmd, char *str, int fd);

// >>> 

void		duplicate_line(t_mini *mini, char *str);
void		edit_comp(char **str);
void		expand_var(t_mini *var, t_env *env, char **str);
void		lst_add_back(t_mini **mini, t_mini *lst);
void		expand_all_vars(t_mini **mini, t_env *evp);
int			ft_strcmp(char *s1, char *s2);
void		empty_herdoc(t_mini *mini, t_env *env);

//ececution funcs

void		exec_it(t_mini *mini, int fd2, t_env **envp, char **temp);
void		close_fd(int n, int *fd);
char		*get_path(char *cmd, t_env *envp);
char		**cmd_option(t_mini *mini);
void		error_exeption(char *error);
void		her_signal(int sig);
void		ft_pipes(t_mini *mini, int *fd, int i, int n);
void		close_fds(void);
void		error_managment(char *cmd, char *func);
int			is_builtins(char *cmd);
void		exec_builtins(t_mini *mini, t_env **envp);
int			is_new_line(char *s);
char		*ft_pathindex(t_env *envp);
void		ft_put_err1(char *err, char *cmd, char *str, int fd);
void		ft_redirection(t_mini *mini, int i);
void		ft_put_err1(char *err, char *cmd, char *str, int fd);
void		ft_put_err(char *cmd, char *str, int fd);
void		close_fds(void);
void		exec_builtins2(t_mini *mini, t_env **envp);
void		free_strs(char **str);

// debug functions
void		print_two_d(char *s1, char **str);

#endif
