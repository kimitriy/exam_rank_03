#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_cnvs
{
	int			w;
	int			h;
	char		bgrnd;
}	t_cnvs;

typedef struct s_fgr
{
	char		type;
	float		x;
	float		y;
	float		w;
	float		h;
	char		col;
}	t_fgr;

typedef struct s_img
{
	t_cnvs		cnvs;
	t_fgr		fgr;
	char		**image;
}	t_img;

int		ft_strlen(const char *str)
{
	int		i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		err_message(char *str)
{
	write(1, "Error: ", 7);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (1);
}

char	**fill_cnvs(FILE *file, t_img *img)
{
	int		ix;
	int		iy;
	char	**cnvs;

	if (fscanf(file, "%d %d %c\n", &img->cnvs.w, &img->cnvs.h, &img->cnvs.bgrnd) != 3)
		return (NULL);
	if ((img->cnvs.w <= 0 || img->cnvs.w > 300) || (img->cnvs.h <= 0 || img->cnvs.h > 300))
		return (NULL);
	if (!(cnvs = (char **)malloc(img->cnvs.h * sizeof(char *))))
		return (NULL);
	iy = 0;
	while (iy < img->cnvs.h)
	{
		if (!(cnvs[iy] = (char *)malloc(img->cnvs.w * sizeof(char))))
			return (NULL);
		ix = 0;
		while (ix < img->cnvs.w)
		{
			cnvs[iy][ix] = img->cnvs.bgrnd;
			ix++;
		}
		iy++;
	}
	return (cnvs);
}

void	print_image(t_img *img)
{
	int	iy;
	int	ix;

	iy = 0;
	while (iy < img->cnvs.h)
	{
		ix = 0;
		while (ix < img->cnvs.w)
		{
			write(1, &img->image[iy][ix], 1);
			ix++;
		}
		write(1, "\n", 1);
		iy++;
	}
}

int		free_all(FILE *file, t_img *img)
{
	int		i;

	i = 0;
	fclose(file);
	if (img->image != NULL)
	{
		while (i < img->cnvs.h)
		{
			free(img->image[i]);
			i++;
		}
		free(img->image);
		free(img);
	}
	return (1);
}

int	is_in_rect(int x, int y, t_img *img)
{
	int		xi;
	int		yi;
	int		wi;
	int		hi;

	xi = ceil(img->fgr.x);
	yi = ceil(img->fgr.y);
	wi = floor(img->fgr.w);
	hi = floor(img->fgr.h);
	if ((xi <= x && x <= (xi + wi - 1)) && (yi <= y && y <= (yi + hi - 1)))
	{
		if ((xi == x || x == (xi + wi - 1)) || (yi == y || y == (yi + hi - 1)))
			return (2);
		return (1);
	}
	else
		return (0);
}

void	fill_fgr_2(t_img *img)
{
	int		iy;
	int		ix;
	int		in_rect;

	iy = 0;
	while (iy < img->cnvs.h)
	{
		ix = 0;
		while (ix < img->cnvs.w)
		{
			in_rect = is_in_rect(ix, iy, img);
			if ((in_rect == 2 && img->fgr.type == 'r') || ((in_rect == 1 || in_rect == 2) && img->fgr.type == 'R'))
				img->image[iy][ix] = img->fgr.col;
			ix++;
		}
		iy++;
	}
}

int		fill_fgr_1(FILE *file, t_img *img)
{
	int		scan_count;

	while ((scan_count = fscanf(file, "%c %f %f %f %f %c\n", &img->fgr.type, &img->fgr.x, &img->fgr.y, &img->fgr.w, &img->fgr.h, &img->fgr.col)) == 6)
	{
		if ((img->fgr.w <= 0 || img->fgr.h <= 0) || (img->fgr.type != 'r' && img->fgr.type != 'R'))
			return (0);
		fill_fgr_2(img);
	}
	if (scan_count >= 0)
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	FILE	*file;
	t_img	*img;

	if (!(img = (t_img *)malloc(1 * sizeof(t_img))))
		return (err_message("Memory allocation error"));
	if (argc != 2)
		return (err_message("Wrong number of arguments"));
	if (!(file = fopen(argv[1], "r")))
		return (err_message("Operation file corrupted"));
	if (!(img->image = fill_cnvs(file, img)))
		return (free_all(file, img) && err_message("Operation file corrupted"));
	if (!(fill_fgr_1(file, img)))
		return (free_all(file, img) && err_message("Operation file corrupted"));
	print_image(img);
	free_all(file, img);
	return (0);
}