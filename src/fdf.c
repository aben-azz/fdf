/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:26:14 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/06 07:23:01 by aben-azz         ###   ########.fr       */
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

void	ligne(t_mlx m, t_xy o, t_xy f)
{
	int		i;
	t_xy	inc;
	int		var;

	f = (t_xy){.x = f.x - o.x, .y =f.y - o.y};
	inc = (t_xy){.x = (f.x > 0) ? 1 : -1, .y = (f.y > 0) ? 1 : -1};
	f = (t_xy){.x = abs(f.x), .y = abs(f.y)};
	p(m, o, 0x00FF00) && (i = 1);
	var = ft_round((f.x > f.y ? f.x : f.y) / 2, 0);
	if (f.x > f.y)
		while (i++ <= f.x && (o.x += inc.x) && (var += f.y))
		{
			(var >= f.x) && (var -= f.x);
			(var >= f.x) && (o.y += inc.y);
			p(m, o, 0x00FF00);
		}
	else
		while (i++ <= f.y && (o.y += inc.y) && (var += f.x))
		{
			(var >= f.y) && (o.x += inc.x);
			(var >= f.y) && (var -= f.y);
			p(m, o, 0x00FF00);
		}
}

void	circle_points(t_mlx m, t_xy c, t_xy o, int color)
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

void	circle_midpoint(t_mlx m, t_xy c, int radius, int color)
{
	t_xy	o;
	int		p;

	o.x = 0;
	o.y = radius;
	p = (5 - radius * 4) / 4;
	circle_points(m, c, o, color);
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
		circle_points(m, c, o, color);
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
	circle_midpoint(m, (t_xy){.x = 600, .y = 600}, 300, 0x00FF00);
	l(m, (t_xy){.x = 600, .y = 600}, (t_xy){.x = 600 + 300, .y = 600});
	l(m, (t_xy){.x = 600, .y = 600}, (t_xy){.x = 600 + 300, .y = 600 + 300});
	l(m, (t_xy){.x = 600, .y = 600}, (t_xy){.x = 600 + 300, .y = 600 - 300});
	l(m, (t_xy){.x = 600, .y = 600}, (t_xy){.x = 600 - 300, .y = 600});
	l(m, (t_xy){.x = 600, .y = 600}, (t_xy){.x = 600 - 300, .y = 600 + 300});
	l(m, (t_xy){.x = 600, .y = 600}, (t_xy){.x = 600 - 300, .y = 600 - 300});
	mlx_loop(m.i);
	return (18);
}
