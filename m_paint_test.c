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
	int	il;
	int	is;

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

void	free_all(FILE *file, t_img *img)
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
}

char	**fill_cnvs(FILE *file, t_img *img)
{
	int		il;
	int		is;
	char	**cnvs;

	if (fscanf(file, "%d %d %c\n", &img->cnvs.w, &img->cnvs.h, &img->cnvs.bckgrnd) != 3)
		return (NULL);
	if (img->cnvs.w <= 0 || img->cnvs.w > 300)
		return (NULL);
	if ()
		return (NULL);
	il = 0;
	while (/* condition */)
	{
		if ()
			return (NULL);
		is = 0;
		while ()
		{
			
			is++;
		}
		il++;
	}
	return (cnvs);
}

/*circle*/
int	is_in_circl()
{

}

/*rctngl*/
int	is_in_rctngl()
{
	
}

/*circle*/
void	fill_fgr_2()
{

}

/*rctngl*/
void	fill_fgr_2()
{

}

/*circle*/
int	fill_fgr_1()
{

}

/*rctngl*/
int	fill_fgr_1()
{
	
}

int	main(int argc, char **argv)
{
	t_img	*img;
	FILE	*file;

	if ()
		return ();
	if ()
		return ();
	if ()
		return ()
	if ()
		return ();
	if ()
		return ();
	print_image();
	free_all();
	return (0);
}