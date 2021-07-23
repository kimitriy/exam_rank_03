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

#ifndef MINI_PAINT_H
# define MINI_PAINT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct s_cnvs
{
	int			w;
	int			h;
	char		bgrnd;
} t_cnvs;

typedef struct s_fgr
{
	char	type;
	float	x;
	float	y;
	float	r;
	char	col;
} t_fgr;

typedef struct s_img
{
	t_cnvs	cnvs;
	t_fgr	fgr;
	char	**image;
} t_img;

#endif