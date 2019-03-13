/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:57:11 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/13 14:15:12 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int				ft_get_color(int color1, int color2, double percentage)
{
	int		red;
	int		green;
	int		blue;

	red = get_light((color1 >> 16) & 0xFF,
			(color2 >> 16) & 0xFF, percentage);
	green = get_light((color1 >> 8) & 0xFF,
			(color2 >> 8) & 0xFF, percentage);
	blue = get_light(color1 & 0xFF, color2 & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

double		ft_percent(int start, int end, int curr)
{
	double placement;
	double distance;

	placement = curr - start;
	distance = end - start;
	return (!distance ? 1.0 : (placement / distance));
}


static void		put_legend(t_mlx *fdf)
{
	int i;

	i = 10;
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i, WHITE,
	"FdF Legend: ");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"(Lshift/Rshift) + scroll  - change altitude");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"scroll                    - zoom");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"scroll click              - toggle projection");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"Space                     - reset values");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"arrow or A/D/W/S           - move");
}

static int		put_pixel_img(t_mlx *fdf, t_point p)
{
	int offset;
	int color;

	offset = ((p.x + p.y * WIN_W) * fdf->img->bpp);
	color = mlx_get_color_value(fdf->mlx, p.color);
	if (fdf->is_border || (p.x < DRAW_W && p.x > 0 && p.y < WIN_H && p.y > 0))
		*(int *)(fdf->img->data + offset) = color;
	return (0);
}

void			process(t_mlx *fdf)
{
	mlx_clear_window(fdf->mlx, fdf->win);
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img->ptr);
	if (!(fdf->img = (t_image *)malloc(sizeof(t_image))))
		exit(1);
	fdf->img->ptr = mlx_new_image(fdf->mlx, WIN_W, WIN_H);
	if (!(fdf->img->ptr))
		exit(1);
	fdf->img->data = mlx_get_data_addr(fdf->img->ptr,
			&fdf->img->bpp, &fdf->img->sizeline, &fdf->img->endian);
	fdf->img->bpp /= 8;
	draw(fdf);
	put_rainbow(fdf, 0, 0, 1);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->ptr, 0, 0);
	put_legend(fdf);
}


static void		put_hor(t_mlx *fdf, t_point p1, t_point p2, t_point d)
{
	int		j;
	int		var;
	t_point i;
	t_point curr;

	curr = (t_point){.x = p1.x, .y = p1.y, .color = p1.color};
	i = (t_point){.x = p2.x - p1.x > 0 ? 1 : -1, .y = p2.y - p1.y > 0 ? 1 : -1};
	j = 1;
	var = (d.x > d.y ? d.x : d.y) / 2;
	while (j++ <= d.x && (var += d.y))
	{
		curr.x += i.x;
		(var >= d.x) && (curr.y += i.y);
		(var >= d.x) && (var -= d.x);
		(curr.color = ft_get_color(p1.color, p2.color, d.x > d.y ?
		ft_percent(p1.x, p2.x, curr.x) : ft_percent(p1.y, p2.y, curr.y)));
		put_pixel_img(fdf, curr);
	}
}

static void		put_ver(t_mlx *fdf, t_point p1, t_point p2, t_point d)
{
	int		j;
	int		var;
	t_point i;
	t_point curr;

	curr = (t_point){.x = p1.x, .y = p1.y, .color = p1.color};
	i = (t_point){.x = p2.x - p1.x > 0 ? 1 : -1, .y = p2.y - p1.y > 0 ? 1 : -1};
	j = 1;
	var = (d.x > d.y ? d.x : d.y) / 2;
	while (j++ <= d.y && (var += d.x))
	{
		curr.y += i.y;
		(var >= d.y) && (curr.x += i.x);
		(var >= d.y) && (var -= d.y);
		(curr.color = ft_get_color(p1.color, p2.color, d.x > d.y ?
		ft_percent(p1.x, p2.x, curr.x) : ft_percent(p1.y, p2.y, curr.y)));
		put_pixel_img(fdf, curr);
	}
}

void			put_line(t_mlx *fdf, t_point p1, t_point p2, int offset)
{
	t_point d;

	d = (t_point){.x = p2.x - p1.x, .y = p2.y - p1.y};
	d = (t_point){.x = abs(d.x), .y = abs(d.y)};
	p1.x += (offset ? fdf->xo : 0);
	p1.y += (offset ? fdf->yo : 0);
	p2.x += (offset ? fdf->xo : 0);
	p2.y += (offset ? fdf->yo : 0);
	(p1.color = ft_get_color(p1.color, p2.color, d.x > d.y ?
		ft_percent(p1.x, p2.x, p1.x) : ft_percent(p1.y, p2.y, p1.y)));
	put_pixel_img(fdf, p1);
	if (d.x > d.y)
		put_hor(fdf, p1, p2, d);
	else
		put_ver(fdf, p1, p2, d);
}

void			put_rainbow(t_mlx *fdf, int x, int y, int focus)
{
	int i;
	int color[3];

	i = 0;
	color[0] = 255;
	color[1] = 0;
	color[2] = 0;
	while (i++ < 499)
	{
		(color[1] == 0 && color[0] == 255) && (color[2] += 5);
		(color[1] == 255 && color[0] == 0) && (color[2] -= 5);
		(color[1] == 0 && color[2] == 255) && (color[0] -= 5);
		(color[1] == 255 && color[2] == 0) && (color[0] += 5);
		(color[0] == 0 && color[2] == 255) && (color[1] += 5);
		(color[0] == 255 && color[2] == 0) && (color[1] -= 5);
		if (i == WIN_W - x && ((y >= WIN_H - 20 && y <= WIN_H - 5) || !focus))
			fdf->clr = rgb2dec(color[0], color[2], color[1]);
		fdf->is_border = 1;
		put_line(fdf, (t_point){DRAW_W + i, WIN_H - 25, rgb2dec(color[0], color[2], color[1])}, (t_point){
			DRAW_W + i, WIN_H - 5, 0}, 0);
		fdf->is_border = 0;
	}
}
