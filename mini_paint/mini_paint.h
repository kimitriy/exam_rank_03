/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:15:35 by rburton           #+#    #+#             */
/*   Updated: 2021/06/19 03:31:02 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int	g_exit;

typedef struct s_cnvs
{
	int		width;
	int		height;
	char	background;
} t_cnvs;

typedef struct s_fgr
{
	char	type;
	float	x;
	float	y;
	float	radius;
	char	color;
} t_fgr;

typedef struct s_img
{
	t_cnvs	cnvs;
	t_fgr	fgr;
	char	**image;
} t_img;

void		ft_bzero(void *s, size_t n);
int			err_message(char *error);
void		*ft_calloc(size_t count, size_t size);
int			ft_strlen(const char *s);
int 		free_all(FILE *file, t_img *img);
char 		**fill_cnvs(FILE *file, t_img *img);
int			is_rad(float x, float y, t_img *img);
void		fill_fgr_2(t_img *img);
int			fill_fgr_1(FILE *file, t_img *img);
void		print_image(t_img *img);
int 		main(int argc, char **argv);

#endif