#include "mini_paint.h"

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

char **fill_cnvs(FILE *file, t_img *img)
{
	int		il; //indx line
	int		is; //indx symb
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

/*circle*/
int	is_in_circl(float x, float y, t_img *img)
{
	float	dist;

	dist = sqrt(((x - img->fgr.x) * (x - img->fgr.x)) + ((y - img->fgr.y) * (y - img->fgr.y)));
	if (dist <= img->fgr.radius) //если точка находится в пределах окружности
	{
		if ((img->fgr.radius - dist) < 1) //если точка находится на краю окружности
			return (2);
		return (1);
	}
	return (0);
}

/*circle*/
/*
важо сочетание 2х факторов:
in_crcl == 2 && img->fgr.type == 'c'
или
in_crcl == 1 && img->fgr.type == 'C'
если например
in_crcl > 0 && img->fgr.type == 'c' то не заходим в тело if => пиксель не закрашивается
*/
void	fill_fgr_2(t_img *img)
{
	int		il;
	int		is;
	int		in_crcl;

	il = 0;
	while (il < img->cnvs.h)
	{
		is = 0;
		while (is < img->cnvs.w)
		{
			in_crcl = is_in_circl((float)is, (float)il, img);
			if ((in_crcl == 2 && img->fgr.type == 'c') || ((in_crcl == 1 || in_crcl == 2) && img->fgr.type == 'C'))
				img->image[il][is] = img->fgr.color;
			is++;	
		}
		il++;
	}
}

/*circle*/
int	fill_fgr_1(FILE *file, t_img *img)
{
	int		scn_count;

	while ((scn_count = fscanf(file, "%c %f %f %f %c\n", &img->fgr.type, &img->fgr.x, &img->fgr.y, &img->fgr.radius, &img->fgr.color)) == 5)
	{
		if (img->fgr.radius <= 0 || (img->fgr.type != 'c' && img->fgr.type != 'C'))
			return (0);
		fill_fgr_2(img);
	}
	if (scn_count >= 0) //если считалось не верное кол-во аргументов => что то не так с operation file
		return (0);
	return (1);
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

int main(int argc, char **argv)
{
	t_img *img;
	FILE *file;

	if (!(img = (t_img *)malloc(1 * sizeof(t_img))))
		return (err_message("memory not allocated"));
	if (argc != 2)
		return (err_message("wrong number of arguments"));
	if (!(file = fopen(argv[1], "r"))) //opens file, "r" - for reading only
		return (err_message("Operation file corrupted"));
	if ((img->image = fill_cnvs(file, img)) == NULL)
		return (free_all(file, img) && err_message("Operation file corrupted"));
	if (!(fill_fgr_1(file, img))) //если fill_fgr_1(file, img) вернула 0 т.е. не истину, наоборот если функция вернула 1 т.е. истину то идем дальше в print_image()
		return (free_all(file, img) && err_message("Operation file corrupted"));
	print_image(img);
	free_all(file, img);
	return (0);
}