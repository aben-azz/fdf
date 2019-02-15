/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/15 09:32:18 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <math.h>

int	to(int o[11][40], t_mlx m, int hauteur, int largeur, int profondeur)
{
	(void)o;
	(void)profondeur;
	//printf("[%d]\n", i[4][3]);
	int x = 300;
	int y = 300;
	//int multi = 10;
	//
	int y_offset = 20;
	int x_offset = 20;
	int i = 0;
	while (i++ < hauteur){
		ligne(m, (t_point){.x = x, .y = y + (i * y_offset)}, (t_point){.x = x + (y_offset * largeur), .y = y}, RED4);
	}
	i = -1;
	printf("{%d, %d}\n", x, y);

	while (i++ < largeur){
		ft_putstr("\n boucle");
		t_point depart;
		t_point destination;

		depart.x = x + (i * x_offset);
		depart.y = y + (y_offset);

		destination.x = x + (i * x_offset);
		destination.y = y + (hauteur * y_offset);
		ligne(m, depart, destination, RED4);

	}
	return (0);
}



void call(t_mlx m){
	int  a[11][40] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 10, 10, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 10, 10, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0},
		{0, 0, 0, 10, 10, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0},
		{0, 0, 0, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	to(a, m, 11, 40, 0);
	return ;
}

t_point		*rotate(t_point a, t_point b, double angle)
{
	int			mid[2][2];
	t_point		xy[2];
	t_point		*points;

	if (!(points = malloc(sizeof(t_point) * 2)))
		return (NULL);
	mid[0][0] = a.x - (a.x + b.x) / 2;
	mid[0][1] = a.y - (a.y + b.y) / 2;
	mid[1][0] = b.x - (a.x + b.x) / 2;
	mid[1][1] = b.y - (a.y + b.y) / 2;
	angle *= 3.14 / 180;
	xy[0].x = cos(angle) * mid[0][0] - sin(angle) * mid[0][1];
	xy[0].y = sin(angle) * mid[0][0] + cos(angle) * mid[0][1];
	xy[1].x = cos(angle) * mid[1][0] - sin(angle) * mid[1][1];
	xy[1].y = sin(angle) * mid[1][0] + cos(angle) * mid[1][1];
	xy[0].x = xy[0].x + (a.x + b.x) / 2;
	xy[0].y = xy[0].y + (a.y + b.y) / 2;
	xy[1].x = xy[1].x + (a.x + b.x) / 2;
	xy[1].y = xy[1].y + (a.y + b.y) / 2;
	points[0] = xy[0];
	points[1] = xy[1];
	return (points);
}

int		main(int ac, char **av)
{

	(void)ac;
	(void)av;
	//clear(m);
	t_mlx m;
	
	m.i = mlx_init();
	m.w = mlx_new_window(m.i, 2500, 1500, "GROS DELIRES");
	clear(m);
	//call(m);
	t_point depart = {.x = 300, .y = 400};
	t_point destination = {.x = 300, .y = 500};
	ligne(m, depart, destination, RED4);
	double angle = 30.0;
	t_point *retour = rotate(depart, destination, angle);
	double angle_ = -30.0;
	t_point *retour_ = rotate(depart, destination, angle_);
	ligne(m, retour[0], retour[1], RED4);
	ligne(m, retour_[0], retour_[1], RED4);

	mlx_loop(m.i);
	return (0);
}
