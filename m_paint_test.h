#ifndef M_PAINT_TEST_H
# define M_PAINT_TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

typedef struct s_cnvs
{
	int			w;
	int			h;
	int			bgrnd;
}	t_cnvs;

typedef struct s_fgr
{
	char		type;
	float		x;
	float		y;
	float		r;
	char		clr;
}	t_fgr;

// typedef struct s_fgr
// {
// 	char		type;
// 	float		x;
// 	float		y;
// 	float		w;
// 	float		h;
// 	char		clr;
// }	t_fgr;

typedef struct s_img
{
	t_cnvs		cnvs;
	t_fgr		fgr;
	char		**image;
}	t_img;

#endif