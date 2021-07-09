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
typedef struct s_fgr
{
	char		type;
	float		x;
	float		y;
	float		radius;
	char		color;
}	t_fgr;

/*rectangle*/
/*
typedef struct s_fgr
{
	char		type;
	float		x;
	float		y;
	float		w;
	float		h;
	char		color;
}	t_fgr;
*/

typedef struct s_img
{
	t_cnvs		cnvs;
	t_fgr		fgr;
	char		**image;
}	t_img;

int				ft_strlen(char *str);
int				err_message(char *error);
int				free_all(FILE *file, t_img *img);
char			**fill_cnvs(FILE *file, t_img *img);

int				is_in_circl(float x, float y, t_img *img);
int				is_in_rctngl(float x, float y, t_img *img);
void			fill_fgr_2(t_img *img);
void			fill_fgr_1(FILE *file, t_img *img);

void			print_image(t_img *img);
int				main(int argc, char **argv);

#endif