/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 02:17:29 by jyim              #+#    #+#             */
/*   Updated: 2014/03/27 16:32:40 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <libft.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "lists.h"
# include "list_norme.h"

# define RED		"31"
# define GREEN		"32"
# define YELLOW		"33"
# define BLUE		"34"
# define PINK		"35"
# define GRBL		"36"
# define GREY		"37"
# define NO			"0"
# define THE_CREED "_=,~,@creeddishonnored#/"

t_glob			g_glob;

int			add_tree(t_tree **tree, int bol, char *cmd, int x);
char		**splits(char **tabou, int start, int end);
t_l			*add_end(t_l *list, char **tabou);
char		**subs(char **tabou);
char		**change_tab(char **tabou, int pos);

char		*delete_spaces(char *str);
char		*delete_chars(char *str, char c);
char		**ft_strsplit_spec(char *str);
t_tree		*parser(char *line);
void		aff_tab(char **array);
char		**make_env(t_env **count, char **environ);
t_env		*reset_count(char **env, t_env *count);
int			ft_unsetenv(char **line2, char **env, t_env *count, int *bin);
int			ft_setenv(char **line2, char **env, int *bin);
char		*create_path(char *command, char **env, t_env *count);

char		*ft_cd(char *pwd, char *line, int *bin);
char		*fn_appel(char *line, char **env, t_env *count, int *bol);
char		*ft_direct_chdir(char *str, char *pwd, int *bin);
char		*ft_chg_home(char *str, int *bin);
char		**fn_commande(char *str, char **env, t_env *count);
char		*fn_pwd_2(char *pwd, int *i, int x);
char		*fn_pwd_1(char *pwd, int *i);
char		*ft_clear_pwd(char *pwd);
void		pipex2(t_tree **father, char **env, t_env *count);

char		*fn_delete(char *str, int i);
void		free_list(t_l *list);
void		free_tab(char ***array);
void		free_tree(t_tree **tree);
int			ft_occ_nb(const char *str, char c);

char		**work_on(t_tree *tree, char **env, t_env *count);
void		ft_execve(char **line2, char **env, int *bin, char *cmd);
char		**fn_last_visit(char **env, char **pwd, t_env *count);
char		*ft_quote(char *line);
char		*ft_parentheses(char *line, char *str);
void		ft_echo(char *str, int *bin);
void		ft_fuck(char *str, int *bin);
void		pipex(t_tree **father, char **env, t_env *count);
void		chevron(t_tree **tree, char **env, t_env *count);

char		**gestion_erreur(char **array);
int			priority(char *str);
int			high_prio_pos(char **array, int p);
int			high_prio(char **array, int p);
int			occ_prio(char **array, int p);
int			nb_word_occ(char *s1, char *s2);

void		aff_tab(char **array);
void		aff_list(t_l *list);
int			count_tab(char **array);

char		*ft_and_or(char *line);
void		chevron_left(t_tree **tree, char **env, t_env *count, int vec);
char		**adds(char **array);
char		*line_to_verif(char *line);
void		fn_chev_2(t_tree *t, char **e, t_env *c);
void		fn_double_chev(t_tree *t, char **e, t_env *c);
t_tree		*verif_chev(t_tree *t);

void		ft_the_env(char *str, char **env, t_env *ct, int *bin);
char		**others(t_others *s, t_env *count);
char		**ft_set_modif(char **env, char *str);
char		**ft_strsplit_spaces(char const *s, char c, int x);
void		binaire_exec(t_tree **tree);
char		deserve(char *str);
char		*the_quotes(char *line);
int			verif_token(char c, int q, char *qt);
char		*del_quotes(char *str);
char		*decale_word(char *s, int i);
void		skip_parent(t_tree **father, char **env, t_env *count);
char		*delete_bs(char *str, char c);
char		**ft_trait(char **cmd);
int			find_word(char *str, char **ch, char c);
char		*match_compare(char *word);
char		*find_match(DIR *directory, char *pattern, char *path, int x);
int			match(char *s1, char *s2);

void		*ft_seek(char *buf, t_term *term);
void		(*g_ft_list[9])(t_term *term);
char		**ft_init_tab(void);
void		ft_init_fn(void);
char		*ft_termcaps(int prompt);

void		ft_larrow(t_term *term);
void		ft_rarrow(t_term *term);
void		ft_uarrow(t_term *term);
void		ft_darrow(t_term *term);

void		ft_ctrl_d(t_term *term);
void		ft_ctrl_l(t_term *term);
void		ft_ctrl_c(int c);

void		ft_other(t_term *term);
void		ft_delete(t_term *term);
int			ft_return(char **str, char **buf);

void		ft_get_term(void);
void		ft_init_term(int sig_number);
char		*ft_trans(char *str);
void		ft_def_term(int i);

char		*ft_realloc_one(char *str);
char		*ft_dup_char(char c);

void		ft_signal(void);
void		ft_sigtstp(int c);

char		*the_star(char *str);
char		*pathing(char *str, int *i);
void		ft_free_str(char *str);
char		*fn_delete_word(char *str, int i, int length);

char		**ft_create_history(void);
void		ft_add_history(char *str);
void		ft_history_up(void);
void		ft_history_down(void);

int			verif_bq(char *cmd);
char		*bq(char *cmd, char **e, t_env *c);
char		**fn_commande(char *s, char **e, t_env *c);
char		*ft_all_strjoin(char **tabou);

int			search_exp(char *str, char **tabou);
char		**ft_exports(char **env, char **tabou);
void		aff_tab_e(char **tabou);
void		aff_env(char **tabou);
void		aff_tab_export(char **export, char **things);
char		*decale_word3(char *str, int x);
char		**decale_deb(char **tabou, int pos, char *str);
char		**decale_tab(char **tabou, int i);

char		*fn_put3(char *str, int *i);
char		*fn_put2(char *str, int *i);
char		*fn_put(char *str, int *i);

void		ft_recup_tree(t_tree **tree, char **env, t_env *count);
void		exec_proc1(t_tree **left, int *fd, char **env, t_env *count);
void		exec_proc2(int *fd, t_tree **right, char **env, t_env *count);

char		**tri_tab_ascii(char **env);
char		**ft_strdup_tab(char **tabl, int nb);
char		**fill_tab_why(char *word);
void		fill_tmp(char *word, t_tmp *e, int bol);

void		ft_argc(t_tree *t, char **env, t_env *count);
void		fill_oth(t_in_other *e, t_others *s, t_env *count);
char		**begin_oth(t_in_other *e, t_others *s, t_env *count);
char		**cd_less(t_in_other *e, t_others *s, t_env *count);
char		**cd_space(t_in_other *e, t_others *s, t_env *count);

char		**get_env(char **env);
t_env		*get_count(t_env *count);
int			get_prompt(char **env, t_env *count);
int			ft_strisint(char *str);
int			is_word(char *str);
char		*dollar(char *line, int *i, char **env);

void		ft_term_resize(int c);
char		*variables(char *line, char **env, t_env *count);
void		ft_multi_line(t_term *term);
char		*decale_word2(char *s, char c);
void		ft_completion(t_term *term);
char		*whole_search(t_complete *s);
char		*vars_tab(t_complete *s);
char		*pathing2(char *str, int *i);
int			find_word2(char *str, char **ch, int c);
int			first_word(int b, char *str);
int			find_word3(char *str, char **ch, char c, char d);

char		*c(char *x);

int			left_if(t_tree **tree);
int			left_else(t_tree **tree);
int			pipe_right_chd(t_tree **right);
int			special_split(t_spec s, char *str);
int			split_spaces(t_dlspaces s, const char *str, char c);

int			split_sp_tok(t_dlspaces s, const char *str, char c);
int			delete_spaces_2(t_spaces s, char *str);
int			work_chd(t_tree **tree);
int			work_chl(t_tree **tree);
int			the_work(t_tree *tree);

int			match_2(char *s1, char *s2);
int			other_cd(t_in_other *e);
int			why_chr(char *word);
int			ltv(t_ltverif v);

int			path_maker(char **env, t_paths s);
int			back_line(char *str, int i);

#endif
