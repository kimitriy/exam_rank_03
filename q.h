#ifndef MINI/MICRO_PAINT_H
# define MINI/MICRO_PAINT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

typedef struct s_cnvs
{
	int			width;
	int			height;
	char		backgrnd;
}	t_cnvs;

typedef struct s_circl
{
	char		type;
	float		x;
	float		y;
	float		radius;
	char		color;
}	t_circl;

typedef struct s_rctngl
{
	char		type;
	float		x;
	float		y;
	float		w;
	float		h;
	char		color;
}	t_rctngl;

typedef struct s_img
{
	t_cnvs		cnvs;
	t_circl		circl;
	t_rctngl	t_rctngl;
	char		**image;
}	t_img;

int				ft_strlen(char *str);
int				err_message(char *error);
int				free_all(FILE *file, t_img *img);
char			**fill_cnvs(FILE *file, t_img *img);
int				is_in_circl(float x, float y, t_img *img);
int				is_in_rctngl(float x, float y, t_img *img);
void			fill_circl_2(t_img *img);
void			fill_rctngl_2(t_img *img);
void			fill_circl_1(FILE *file, t_img *img);
void			fill_rctngl_1(FILE *file, t_img *img);
void			print_image(t_img *img);
int				main(int argc, char **argv);

#endif