#ifndef M_PAINT_TEST
# define M_PAINT_TEST

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

typedef struct s_cnvs
{
	int			w;
	int			h;
	int			bckgrnd;
}	t_cnvs;

/*circle*/
typedef struct s_fgr
{
	char		type;
	int			x;
	int			y;
	int			r;
	char		color;
}	t_fgr;

/*rectangle*/
typedef struct s_fgr
{
	char		type;
	int			x;
	int			y;
	int			w;
	int			wh;
	char		color;
}	t_fgr;

typedef struct s_img
{
	t_cnvs		cnvs;
	t_fgr		fgr;
	char		**image;
}	t_img;

#endif