/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 19:32:24 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/11 05:46:51 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>

# include "leaks_destroyer.h"

# define TRUE 1
# define SUCCESS 1
# define FALSE 0
# define ERROR -1

# define INT_MAX "2147483647"
# define INT_MIN "-2147483648"

/* ************************************************************************** */
/* 								  CLEANER									  */
/* ************************************************************************** */

void		ft_clean_strs(char **strs);

/* ************************************************************************** */
/* 								  CONVERT									  */
/* ************************************************************************** */

int			ft_atoi(char *s);
char		*ft_itoa(int n);

/* ************************************************************************** */
/* 								  PARSING									  */
/* ************************************************************************** */

int			ft_cmp_extension(char *file, char *ext);

int			ft_isnumber(char *str);
int			ft_isdigit(char c);
int			ft_isalpha(char c);
int			ft_isalnum(char c);
int			ft_iswhitespace(char c);

int			ft_strchr(char *str, char c);
int			ft_strchr_num(char *str, char c);

/* ************************************************************************** */
/* 								  STRING									  */
/* ************************************************************************** */

char		*ft_strnstr(char *str, char *to_find, size_t n);

char		*ft_substr(char *s, int start, int len);
char		*ft_strnew(char *str);
char		*ft_strcat(char *dst, char *src);
char		*ft_strcpy(char *dst, char *src);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, int n);
int			ft_strlen(char *s);
int			ft_end_word(char *str, int start);

char		*ft_merge(char *s1, char *s2);
char		*ft_merge_space(char *s1, char *s2);
char		*ft_merge_slash(char *s1, char *s2);
char		*ft_first_word(char *line);
char		*ft_first_word_dollar(char *line);

char		**ft_split(char *str, char c);
char		*ft_strsjoin(char **strs, int len);

int			ft_strslen(char **strs);

char		*ft_absolute_line(char **line);
void		ft_neglastchar(char **line, char c);
void		ft_negchar(char **line, char c);

/* ************************************************************************** */
/* 								  OTHER										  */
/* ************************************************************************** */
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
int			get_next_line(int fd, char **line);

#endif
