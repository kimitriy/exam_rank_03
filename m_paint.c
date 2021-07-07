#include "m_paint.h"

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

int	err_message(char *error)
{
	write(1, "Error: ", 7);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	return (1);
}

int free_all(FILE *file, t_img *img)
{
	int		i;

	i = 0;
	fclose(file);
	if (img)
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

char	**fill_cnvs(FILE *file, t_img *img)
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

}

/*rctngl*/
int	is_in_rctngl(float x, float y, t_img *img)
{

}

/*circle*/
void	fill_fgr_2(t_img *img)
{

}

/*rctngl*/
void	fill_fgr_2(t_img *img)
{

}

/*circle*/
void	fill_fgr_1(FILE *file, t_img *img)
{

}

/*rctngl*/
void	fill_fgr_1(FILE *file, t_img *img)
{

}

void	print_image(t_img *img)
{

}

int	main(int argc, char **argv)
{
	
}