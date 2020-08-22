# include "rt.h"

void print_png_file(t_tex *t) 
{
	int	i;
	int	j;

	i = -1;
	while (++i < t->height)
	{
		j = -1;
		while (++j < t->width)
			printf("(%d, %d) -> R = %d, G = %d, B = %d\n", i, j,
			*((unsigned char *)(t->data_t + i * t->width + j) + 2),
			*((unsigned char *)(t->data_t + i * t->width + j) + 1),
			*((unsigned char *)(t->data_t + i * t->width + j)));
	}
	printf("width=%d height=%d ori={%f,%f,%f} hori={%f,%f,%f}\n", t->width, t->height, t->ori[0], t->ori[1], t->ori[2], t->hori[0], t->hori[1], t->hori[2]);
}

static void read_png_file(t_png *p, char *filename) 
{
	FILE *fp;
	png_structp png;
	png_infop info; 

	if (!(fp = fopen(filename, "rb")))
		ft_error("probleme dans l'ouverture d'un .png -> ", filename);
	png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png) 
		exit(0);
	info = png_create_info_struct(png);
	if(!info) 
		exit(0);

	if(setjmp(png_jmpbuf(png))) abort();

	png_init_io(png, fp);

	png_read_info(png, info);

	p->width      = png_get_image_width(png, info);
	p->height     = png_get_image_height(png, info);
	p->color_type = png_get_color_type(png, info);
	p->bit_depth  = png_get_bit_depth(png, info);

	// Read any color_type into 8bit depth, RGBA format.
	// See http://www.libpng.org/pub/png/libpng-manual.txt

	if(p->bit_depth == 16)
		png_set_strip_16(png);

	if(p->color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);

	// PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
	if(p->color_type == PNG_COLOR_TYPE_GRAY && p->bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png);

	if(png_get_valid(png, info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png);

	// These color_type don't have an alpha channel then fill it with 0xff.
	if(p->color_type == PNG_COLOR_TYPE_RGB ||
			p->color_type == PNG_COLOR_TYPE_GRAY ||
			p->color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

	if(p->color_type == PNG_COLOR_TYPE_GRAY ||
			p->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png);

	png_read_update_info(png, info);

	p->row_pointers = (unsigned char **)malloc(sizeof(unsigned char *) * p->height);

	int 	i;
	i = -1;
	while (++i < p->height)
		p->row_pointers[i] = (unsigned char *)malloc(png_get_rowbytes(png, info));
	png_read_image(png, p->row_pointers);
	png_destroy_read_struct (&png, &info, NULL);
	fclose(fp);
}

t_tex		*load_png(char *path) 
{
	t_png	*p;
	t_tex	*t;
	int	i;
	int	j;

	p = (t_png *)malloc(sizeof(t_png));
	read_png_file(p, path);
	t = (t_tex *)malloc(sizeof(t_tex));
	t->height = p->height;
	t->width = p->width;
	t->data_t = (int *)malloc(sizeof(int) * t->height * t->width);
	i = -1;
	while (++i < t->height)
	{
		j = -1;
		while (++j < t->width)
			*(t->data_t + i * t->width + j) =
				p->row_pointers[i][j * 4] * pow(256, 2)
				+ p->row_pointers[i][j * 4 + 1] * pow(256, 1)
				+ p->row_pointers[i][j * 4 + 2];
	}
	i = -1;
	while (++i < p->height)
		free(p->row_pointers[i]);
	free(p->row_pointers);
	free(p);
	return (t);
}
