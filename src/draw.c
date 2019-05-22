/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:57:11 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/22 15:01:46 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

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

t_point			put_pixel_img(t_mlx *fdf, t_point p, t_point i[3], int *j)
{
	int offset;
	int color;

	offset = ((p.x + p.y * WIN_W) * fdf->img->bpp);
	color = mlx_get_color_value(fdf->mlx, p.color);
	if (fdf->is_border || (p.x < DRAW_W && p.x > 0 && p.y < WIN_H && p.y > 0))
		*(int *)(fdf->img->data + offset) = color;
	i && (j[1] = max(i[2].x, i[2].y) / 2);
	i && (j[0] = 1);
	return (p);
}

void			put_line(t_mlx *fdf, t_point p1, t_point p2, int offset)
{
	int		j[2];
	t_point i[3];

	offset && (p2.x += fdf->xo);
	offset && (p1.x += fdf->xo);
	offset && (p2.y += fdf->yo);
	offset && (p1.y += fdf->yo);
	i[2] = (t_point){.x = abs(p2.x - p1.x), .y = abs(p2.y - p1.y)};
	(p1.color = ft_get_color_from_percent(p1.color, i[2].x > i[2].y ?
		ft_percent(p1.x, p2.x, p1.x) : ft_percent(p1.y, p2.y, p1.y)));
	i[1] = put_pixel_img(fdf, p1, i, j);
	i[0] = (t_point){.x = p2.x - p1.x > 0 ? 1 : -1,
			.y = p2.y - p1.y > 0 ? 1 : -1};
	while (j[0]++ <= (max(i[2].x, i[2].y)) && (j[1] += (min(i[2].x, i[2].y))))
	{
		(i[2].x > i[2].y) && (i[1].x += i[0].x);
		(i[2].x > i[2].y) && ((j[1] >= i[2].x) && (i[1].y += i[0].y));
		(i[2].x > i[2].y) && ((j[1] >= i[2].x) && (j[1] -= i[2].x));
		(i[2].x > i[2].y) || (i[1].y += i[0].y);
		(i[2].x > i[2].y) || ((j[1] >= i[2].y) && (i[1].x += i[0].x));
		(i[2].x > i[2].y) || ((j[1] >= i[2].y) && (j[1] -= i[2].y));
		(i[1].color = ft_get_color_from_percent(p1.color, i[2].x > i[2].y ?
		ft_percent(p1.x, p2.x, i[1].x) : ft_percent(p1.y, p2.y, i[1].y)));
		put_pixel_img(fdf, i[1], 0, NULL);
	}
}

void			put_rainbow(t_mlx *fdf, int x, int y, int f)
{
	int i;
	int color[3];

	i = 0;
	color[0] = 0;
	color[1] = 255;
	color[2] = 0;
	while (i++ < 499)
	{
		(color[1] == 0 && color[2] == 255) && (color[0] -= 5);
		(color[1] == 255 && color[2] == 0) && (color[0] += 5);
		(color[1] == 0 && color[0] == 255) && (color[2] += 5);
		(color[1] == 255 && color[0] == 0) && (color[2] -= 5);
		(color[0] == 0 && color[2] == 255) && (color[1] += 5);
		(color[0] == 255 && color[2] == 0) && (color[1] -= 5);
		fdf->is_border = 1;
		put_line(fdf, (t_point){DRAW_W + i, WIN_H - 25,
			rgb2dec(color[0], color[1], color[2])},
			(t_point){DRAW_W + i, WIN_H - 5, 0}, 0);
		fdf->is_border = 0;
		if (499 - i == WIN_W - x && ((y >= WIN_H - 20 && y <= WIN_H - 5) || !f))
			fdf->clr = rgb2dec(color[0], color[1], color[2]);
	}
}
