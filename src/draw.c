/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:57:11 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/07 07:06:45 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		menu(t_mlx m)
{
	(void)m;
	return (0);
}

int				put_pixel_img(t_mlx *fdf, t_point p)
{
	int offset;
	int color;

	offset = ((p.x + p.y * WIN_W) * fdf->img->bpp);
	color = mlx_get_color_value(fdf->mlx, RED1);
	if (fdf->is_border || (p.x < DRAW_W && p.x > 0 && p.y < WIN_H && p.y > 0))
		*(int *)(fdf->img->data + offset) = color;
	return (1);
}

void		create_image(t_mlx *fdf)
{

	if (!(fdf->img = (t_image *)malloc(sizeof(t_image))))
		exit(1);
	fdf->img->ptr = mlx_new_image(fdf->mlx, WIN_W, WIN_H);
	if (!(fdf->img->ptr))
		exit(1);
	fdf->img->data = mlx_get_data_addr(fdf->img->ptr,
			&fdf->img->bpp, &fdf->img->sizeline, &fdf->img->endian);
	fdf->img->bpp /= 8;
}

void			process(t_mlx *fdf)
{
	mlx_clear_window(fdf->mlx, fdf->win);
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img->ptr);
	create_image(fdf);
	draw(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->ptr, 0, 0);
}

void		put_hor(t_mlx *fdf, t_point p1, t_point p2, t_point d)
{
	int		j;
	int		var;
	t_point i;
	t_point curr;

	curr = (t_point){p1.x, p1.y};
	i = (t_point){p2.x - p1.x > 0 ? 1 : -1, p2.y - p1.y > 0 ? 1 : -1};
	j = 1;
	var = (d.x > d.y ? d.x : d.y) / 2;
	while (j++ <= d.x && (var += d.y))
	{
		curr.x += i.x;
		(var >= d.x) && (curr.y += i.y);
		(var >= d.x) && (var -= d.x);
		(put_pixel_img(fdf, curr));
	}
}

void		put_ver(t_mlx *fdf, t_point p1, t_point p2, t_point d)
{
	int		j;
	int		var;
	t_point i;
	t_point curr;

	curr = (t_point){p1.x, p1.y};
	i = (t_point){p2.x - p1.x > 0 ? 1 : -1, p2.y - p1.y > 0 ? 1 : -1};
	j = 1;
	var = (d.x > d.y ? d.x : d.y) / 2;
	while (j++ <= d.y && (var += d.x))
	{
		curr.y += i.y;
		(var >= d.y) && (curr.x += i.x);
		(var >= d.y) && (var -= d.y);
		(put_pixel_img(fdf, curr));
	}
}

void			put_line(t_mlx *fdf, t_point p1, t_point p2, int offset)
{
	t_point d;
	d = (t_point){p2.x - p1.x, p2.y - p1.y};
	d = (t_point){abs(d.x), abs(d.y)};
	p1.x += (offset ? fdf->xoffset : 0);
	p1.y += (offset ? fdf->yoffset : 0);
	p2.x += (offset ? fdf->xoffset : 0);
	p2.y += (offset ? fdf->yoffset : 0);
	(put_pixel_img(fdf, p1));
	if (d.x > d.y)
		put_hor(fdf, p1, p2, d);
	else
		put_ver(fdf, p1, p2, d);
}
