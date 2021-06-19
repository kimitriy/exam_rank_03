#include "micro_paint.h"

int	ft_strlen(const char *s)
{
	int		i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	err_message(char *error)
{
	write(1, "Error: ", 7);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	return(1);
}

int free_all(FILE *file, t_img *img)
{
	int		i;

	i = 0;
	fclose(file);
	if (img)
	{
		while (i < img->cnvs.height)
		{
			free(img->image[i]);
			i++;
		}
		free(img->image);
		free(img);
	}
	return (1);
}

char **fill_cnvs(FILE *file, t_img *img)
{
	int		il;
	int		is;
	char	**cnvs;

	if ((il = fscanf(file, "%d %d %c\n", &img->cnvs.width, &img->cnvs.height, &img->cnvs.background)) != 3)
		return (NULL);
	if (img->cnvs.width <= 0 || img->cnvs.width > 300 || img->cnvs.height <= 0 || img->cnvs.height > 300)
		return (NULL);
	if (!(cnvs = (char **)malloc(img->cnvs.height * sizeof(char *))))
		return (NULL);
	il = 0;
	while (il < img->cnvs.height)
	{
		if (!(cnvs[il] = (char *)malloc(img->cnvs.width * sizeof(char))))
			return (NULL);
		is = 0;
		while (is < img->cnvs.width)
		{
			cnvs[il][is] = img->cnvs.background;
			is++;
		}
		il++;
	}
	return (cnvs);
}

int	is_in_rctngl(float x, float y, t_img *img)
{
	if ((x < img->fgr.x) || (x > img->fgr.x + img->fgr.w) || (y < img->fgr.y) || (y > img->fgr.y + img->fgr.h))
		return (0);
	if ((x - img->fgr.x < 1) || ((img->fgr.x + img->fgr.w) - x < 1) || (y - img->fgr.y < 1) || ((img->fgr.y + img->fgr.h) - y < 1))
		return (2);
	return (1);
}

void	fill_fgr_2(t_img *img)
{
	int		il;
	int		is;
	int		in_rect;

	il = 0;
	while (il < img->cnvs.height)
	{
		is = 0;
		while (is < img->cnvs.width)
		{
			in_rect = is_in_rctngl((float)is, (float)il, img);
			if ((in_rect == 2 && img->fgr.type == 'r') || (in_rect > 0 && img->fgr.type == 'R'))
				img->image[il][is] = img->fgr.color;
			is++;	
		}
		il++;
	}
}

int	fill_fgr_1(FILE *file, t_img *img)
{
	int		scn_count;

	while ((scn_count = fscanf(file, "%c %f %f %f %f %c\n", &img->fgr.type, &img->fgr.x, &img->fgr.y, &img->fgr.w, &img->fgr.h, &img->fgr.color)) == 6)
	{
		if (img->fgr.w <= 0 && (img->fgr.type != 'c' || img->fgr.type != 'C'))
			return (0);
		fill_fgr_2(img);
	}
	if (scn_count >= 0)
		return (0);
	return (1);
}

void	print_image(t_img *img)
{
	int		il;
	int		is;

	il = 0;
	while (il < img->cnvs.height)
	{
		is = 0;
		while (is < img->cnvs.width)
		{
			write(1, &img->image[il][is], 1);
			is++;
		}
		write(1, "\n", 1);
		il++;
	}
}

int main(int argc, char **argv)
{
	t_img *img;
	FILE *file;

	if (!(img = (t_img *)malloc(1 * sizeof(t_img))))
		return (err_message("memory not allocated"));
	if (argc != 2) //wrong number of arguments
		return (err_message("argument"));
	if (!(file = fopen(argv[1], "r"))) //opens file, "r" - for reading only
		return (err_message("Operation file corrupted"));
	if (!(img->image = fill_cnvs(file, img)))
		return (free_all(file, img) && err_message("Operation file corrupted"));
	if (!(fill_fgr_1(file, img)))
		return (free_all(file, img) && err_message("Operation file corrupted"));
	print_image(img);
	free_all(file, img);
}