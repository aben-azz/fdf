/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:26:14 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/24 02:05:30 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <stdio.h>
#include "fdf.h"

int		rect(t_mlx m, t_point from, t_point l, int color)
{
	ligne(m, (t_point){.x = from.x + l.x, .y = from.y},
		(t_point){.x = from.x + l.x, .y =from.y + l.y}, color);
	ligne(m, (t_point){.x = from.x, .y = from.y},
		(t_point){.x = from.x + l.x, .y = from.y}, color);
	ligne(m, (t_point){.x = from.x, .y = from.y},
		(t_point){.x = from.x, .y = from.y + l.y}, color);
	ligne(m, (t_point){.x = from.x, .y = from.y + l.y},
		(t_point){.x = from.x + l.x, .y = from.y + l.y}, color);
	return (0);
}

int		fill_rect(t_mlx m, t_point from, t_point l, int color)
{
	int i;

	i = 0;
	while (i++ < l.y)
		ligne(m, (t_point){.x = from.x, .y = from.y + i},
			(t_point){.x = from.x + l.x, .y = from.y + l.y}, color);
	return (0);
}

int		rectangle(t_mlx m, t_point from, t_point l, int color)
{
	rect(m, from, l, color);
	fill_rect(m, from, l, color);
	return (0);
}

int		clear(t_mlx m)
{
	mlx_clear_window(m.i, m.w);
	return (menu(m));
}

int		menu(t_mlx m)
{
	(void)m;
	circle_midpoint(m, (t_point){.x = 200, .y = 800 - 100}, 70, GREEN);
	return (0);
}
