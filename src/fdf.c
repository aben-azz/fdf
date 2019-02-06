/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:26:14 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/06 06:56:00 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <stdio.h>
#include "fdf.h"

int		p(t_mlx m, t_xy i, int color)
{
	mlx_pixel_put(m.i, m.w, i.x, i.y, color);
	return (1);
}

int		string(t_mlx m, t_xy i, int color, char *string)
{
	mlx_string_put(m.i, m.w, i.x, i.y, color, string);
	return (1);
}

void ligne(t_mlx m, int xi,int yi,int xf,int yf) {
	int dx,dy,i,xinc,yinc,cumul,x,y;
	x = xi;
	y = yi;
	dx = xf - xi;
	dy = yf - y;
	xinc = (dx > 0) ? 1 : -1;
	yinc = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	p(m, (t_xy){.x = x, .y = y}, 0x00FF00);
	if (dx > dy)
	{
		cumul = ft_round(dx / 2, 0);
		i = 1;
		while (i++ <= dx)
		{
			x += xinc;
			cumul += dy;
			if (cumul >= dx)
			{
				cumul -= dx;
				y += yinc;
			}
			p(m,(t_xy){.x = x, .y = y}, 0x00FF00);
		}
	}
	else
	{
		cumul = ft_round(dy / 2, 0);
		i = 1;
		while (i++ <= dy)
		{
			y += yinc;
			cumul += dx;
			if (cumul >= dy)
			{
				cumul -= dy;
				x += xinc;
			}
			p(m, (t_xy){.x = x, .y = y}, 0x00FF00);
		}
	}
}

void	circlePoints(t_mlx m, t_xy c, t_xy o, int color)
{
	(o.x == 0) && p(m, (t_xy){.x = c.x, .y = c.y + o.y}, color);
	(o.x == 0) && p(m, (t_xy){.x = c.x, .y = c.y - o.y }, color);
	(o.x == 0) && p(m, (t_xy){.x = c.x + o.y, .y = c.y }, color);
	(o.x == 0) && p(m, (t_xy){.x = c.x - o.y, .y = c.y }, color);
	(o.x == o.y) && p(m, (t_xy){.x = c.x + o.x, .y = c.y + o.y }, color);
	(o.x == o.y) && p(m, (t_xy){.x = c.x - o.x, .y = c.y + o.y }, color);
	(o.x == o.y) && p(m, (t_xy){.x = c.x + o.x, .y = c.y - o.y }, color);
	(o.x == o.y) && p(m, (t_xy){.x = c.x - o.x, .y = c.y - o.y }, color);
	(o.x < o.y) && p(m, (t_xy){.x = c.x + o.x, .y = c.y + o.y }, color);
	(o.x < o.y) && p(m, (t_xy){.x = c.x - o.x, .y = c.y + o.y }, color);
	(o.x < o.y) && p(m, (t_xy){.x = c.x + o.x, .y = c.y - o.y }, color);
	(o.x < o.y) && p(m, (t_xy){.x = c.x - o.x, .y = c.y - o.y }, color);
	(o.x < o.y) && p(m, (t_xy){.x = c.x + o.y, .y = c.y + o.x }, color);
	(o.x < o.y) && p(m, (t_xy){.x = c.x - o.y, .y = c.y + o.x }, color);
	(o.x < o.y) && p(m, (t_xy){.x = c.x + o.y, .y = c.y - o.x }, color);
	(o.x < o.y) && p(m, (t_xy){.x = c.x - o.y, .y = c.y - o.x }, color);
}

void	circleMidpoint(t_mlx m, t_xy c, int radius, int color)
{
	t_xy	o;
	int		p;

	o.x = 0;
	o.y = radius;
	p = (5 - radius * 4) / 4;
	circlePoints(m, c, o, color);
	while (o.x < o.y)
	{
		o.x++;
		if (p < 0)
			p += 2 * o.x + 1;
		else
		{
			o.y--;
			p += 2 * (o.x - o.y) + 1;
		}
		circlePoints(m, c, o, color);
	}
}

int		gere_souris(int x, int y, int z, int o)
{
	printf("{%d, %d, %d, %d}\n", x, y, z, o);
	return (0);
}

int		fdf(void)
{
	t_mlx m;

	m.i = mlx_init();
	m.w = mlx_new_window(m.i, 2000, 2000, "GROS DELIRES");
	string(m, (t_xy){.x = 250, .y = 200}, 0xFFFF00, "Gros delire ca");
	string(m, (t_xy){.x = 300, .y = 200}, 0xFF00FF, "mec je suis ou");
	string(m, (t_xy){.x = 200, .y = 250}, 0x00FF00, "PTDR JFKOI LA");
	string(m, (t_xy){.x = 200, .y = 300}, 0x2F2F2F, "JFK LA OSSI XD");
	mlx_mouse_hook(m.w, gere_souris, m.w);
	circleMidpoint(m, (t_xy){.x = 600, .y = 600}, 300, 0x00FF00);
	mlx_loop(m.i);
	return (18);
}
