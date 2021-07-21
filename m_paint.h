#ifndef M_PAINT_H
# define M_PAINT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

typedef struct s_cnvs
{
	int			w;
	int			h;
	char		bgrnd;
}	t_cnvs;

/*circle*/
// typedef struct s_fgr
// {
// 	char		type;
// 	float		x;
// 	float		y;
// 	float		r;
// 	char		color;
// }	t_fgr;

/*rectangle*/
typedef struct s_fgr
{
	char		type;
	float		x;
	float		y;
	float		w;
	float		h;
	char		color;
}	t_fgr;

typedef struct s_img
{
	t_cnvs		cnvs;
	t_fgr		fgr;
	char		**image;
}	t_img;

#endif