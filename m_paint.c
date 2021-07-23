#include "m_paint_test.h"

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	err_message(char *error)
{
	write(1, "Error: ", 7);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	return (1);
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

int	free_all(FILE *file, t_img *img)
{
	int	i;

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

/*fill_cnvs*/
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

/*circle*/
int		is_in_crcl(float x, float y, t_img *img)
{
	float	dist;

	dist = sqrt((x - img->fgr.x) * (x - img->fgr.x) + (y - img->fgr.y) * (y - img->fgr.y));
	if (dist <= img->fgr.r)
	{
		if ((img->fgr.r - dist) < 1)
			return (2);
		return (1);
	}
	else
		return (0);
}

/*rctngl*/
int		is_in_rect(float x, float y, t_img *img)
{
	if ((img->fgr.x <= x && x <= (img->fgr.x + img->fgr.w)) && (img->fgr.y <= y && y <= (img->fgr.y + img->fgr.h)))
	{
		if ((x - img->fgr.x) < 1 || (img->fgr.x + img->fgr.w - x) < 1 || (y - img->fgr.y) < 1 || (img->fgr.y + img->fgr.h - y) < 1)
			return (2);
		return (1);
	}
	else
		return (0);
}

/*circle*/
void	fill_fgr_2(t_img *img)
{
	int		iy;
	int		ix;
	int		in_crcl;

	iy = 0;
	while (iy < img->cnvs.h)
	{
		ix = 0;
		while (ix < img->cnvs.w)
		{
			in_crcl = is_in_crcl((float)ix, (float)iy, img);
			if ((in_crcl == 2 && img->fgr.type == 'c') || ((in_crcl == 1 || in_crcl == 2) && img->fgr.type == 'C'))
				img->image[iy][ix] = img->fgr.col;
			ix++;
		}
		iy++;
	}
}

/*rctngl*/
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
			in_rect = is_in_rect((float)ix, (float)iy, img);
			if ((in_rect == 2 && img->fgr.type == 'r') || ((in_rect == 1 || in_rect == 2) && img->fgr.type == 'R'))
				img->image[iy][ix] = img->fgr.col;
			ix++;
		}
		iy++;
	}
}

/*circle*/
int	fill_fgr_1(FILE *file, t_img *img)
{
	int		scan_count;

	while ((scan_count = fscanf(file, "%c %f %f %f %c\n", &img->fgr.type, &img->fgr.x, &img->fgr.y, &img->fgr.r, &img->fgr.col)) == 5)
	{
		if (img->fgr.r <= 0 || (img->fgr.type != 'c' && img->fgr.type != 'C'))
			return (0);
		fill_fgr_2(img);
	}
	if (scan_count != -1)
		return (0);
	return (1);
}

/*rctngl*/
int	fill_fgr_1(FILE *file, t_img *img)
{
	int		scan_count;

	while ((scan_count = fscanf(file, "%c %f %f %f %f %c\n", &img->fgr.type, &img->fgr.x, &img->fgr.y, &img->fgr.w, &img->fgr.h, &img->fgr.col)) == 6)
	{
		if ((img->fgr.w <= 0 || img->fgr.h <= 0) || (img->fgr.type != 'r' && img->fgr.type != 'R'))
			return (0);
		fill_fgr_2(img);
	}
	if (scan_count != -1)
		return (0);
	return (1);
}

/*main*/
int	main(int argc, char **argv)
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