#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct s_cnvs
{
	int width;
	int height;
	char background;
} t_cnvs;

typedef struct s_fgr
{
	char type;
	float x;
	float y;
	float radius;
	char color;
} t_fgr;

typedef struct s_img
{
	
};
