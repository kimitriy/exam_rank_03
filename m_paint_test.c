#include "m_paint_test.h"

int	ft_strlen(char *str)
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

int		free_all(FILE *file, t_img * img)
{
	int		i;

	fclose(file);
	if (img)
	{
		i = 0;
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

char	**fill_cnvs(FILE *file, t_img *img)
{
	int		il;
	int		is;
	char	**cnvs;

	if ((il = fscanf(file, "%d %d %c\n", &img->cnvs.w, &img->cnvs.h, &img->cnvs.bgrnd)) != 3)
		return (NULL);
	if (img->cnvs.w <= 0 || img->cnvs.w > 300 || img->cnvs.h <= 0 || img->cnvs.h > 300)
		return (NULL);
	if (!(cnvs = (char **)malloc(img->cnvs.h * sizeof(char *))))
		return (NULL);
	il = 0;
	while (il < img->cnvs.h)
	{
		if (!(cnvs[il] = (char *)malloc(img->cnvs.w * sizeof(char))))
			return (NULL);
		is = 0;
		while (is < img->cnvs.w)
		{
			cnvs[il][is] = img->cnvs.bgrnd;
			is++;
		}
		il++;
	}
	return (cnvs);
}

int		is_in_circl(float x. float y, t_img *img)
{

}

void	fill_fgr_2(t_img *img)
{

}

int		fill_fgr_1(FILE *file, t_img *img)
{
	int		scn_count;

	while ((scn_count = fscanf(file, "%c %f %f %f %c", &img->fgr.type, &img->fgr.x, &img->fgr.y, &img->fgr.r, &img->fgr.clr)) == 5)
	{
		if (img->fgr.r <= 0 &&)
	}
	
}

void	print_image(t_img *img)
{
	int		il;
	int		is;

	il = 0;
	while (il < img->cnvs.h)
	{
		is = 0;
		while (is < img->cnvs.w)
		{
			write(1, &img->image[il][is], 1);
			is++;
		}
		write(1, "\n", 1);
		il++;
	}
	
}

int		main(int argc, char **argv)
{
	t_img	*img;
	FILE	*file;

	if (!(img = (t_img *)malloc(1 * sizeof(t_img))))
		return (err_message("memory allocation error"));
	if (argc != 2)
		return (err_message("wrong number of arguments"));
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