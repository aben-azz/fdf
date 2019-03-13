/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:57:11 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/13 08:13:30 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		put_legend(t_mlx *fdf)
{
	int i;

	i = 10;
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 100, WHITE,
	"(Lshift/Rshift) + scroll  - change altitude");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 100, WHITE,
	"scroll                    - zoom");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 100, WHITE,
	"scroll click              - toggle projection");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 100, WHITE,
	"Space                     - reset values");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 100, WHITE,
	"left arrow or A           - move left");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 100, WHITE,
	"right arrow or D          - move right");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 100, WHITE,
	"up arrow or W             - move up");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 100, WHITE,
	"down arrow or S           - move down");
}

int				put_pixel_img(t_mlx *fdf, t_point p, int couleur)
{
	int offset;
	int color;

	offset = ((p.x + p.y * WIN_W) * fdf->img->bpp);
	color = mlx_get_color_value(fdf->mlx, couleur);
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
	put_rainbow(fdf, 0, 0, 1);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->ptr, 0, 0);
	put_legend(fdf);
}

void		put_hor(t_mlx *fdf, t_points p, t_point d, int color)
{
	int		j;
	int		var;
	t_point i;
	t_point curr;

	curr = (t_point){p.p1.x, p.p1.y};
	i = (t_point){p.p2.x - p.p1.x > 0 ? 1 : -1, p.p2.y - p.p1.y > 0 ? 1 : -1};
	j = 1;
	var = (d.x > d.y ? d.x : d.y) / 2;
	while (j++ <= d.x && (var += d.y))
	{
		curr.x += i.x;
		(var >= d.x) && (curr.y += i.y);
		(var >= d.x) && (var -= d.x);
		(put_pixel_img(fdf, curr, color));
	}
}

void		put_ver(t_mlx *fdf, t_points p, t_point d, int color)
{
	int		j;
	int		var;
	t_point i;
	t_point curr;

	curr = (t_point){p.p1.x, p.p1.y};
	i = (t_point){p.p2.x - p.p1.x > 0 ? 1 : -1, p.p2.y - p.p1.y > 0 ? 1 : -1};
	j = 1;
	var = (d.x > d.y ? d.x : d.y) / 2;
	while (j++ <= d.y && (var += d.x))
	{
		curr.y += i.y;
		(var >= d.y) && (curr.x += i.x);
		(var >= d.y) && (var -= d.y);
		(put_pixel_img(fdf, curr, color));
	}
}

void			put_line(t_mlx *fdf, t_points p, int offset, int color)
{
	t_point d;

	d = (t_point){p.p2.x - p.p1.x, p.p2.y - p.p1.y};
	d = (t_point){abs(d.x), abs(d.y)};
	p.p1.x += (offset ? fdf->xoffset : 0);
	p.p1.y += (offset ? fdf->yoffset : 0);
	p.p2.x += (offset ? fdf->xoffset : 0);
	p.p2.y += (offset ? fdf->yoffset : 0);
	(put_pixel_img(fdf, p.p1, color));
	if (d.x > d.y)
		put_hor(fdf, p, d, color);
	else
		put_ver(fdf, p, d, color);
}
