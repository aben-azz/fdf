/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/24 01:24:33 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

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
float cte = 0.5;
float cte2 = 0.5;

int		evt_live_key_pressed(int key, t_mlx *m)
{
	(void)m;
	if (key == HAUT) {
		cte += 0.01;
	} else if(key == BAS){
		cte -= 0.01;
	} else if(key == GAUCHE){
		cte2 -= 0.01;
	} else if(key == DROITE){
		cte2 += 0.01;
	}
	return (0);
}


void call(t_mlx m){
	int  a[11][19] = {
	{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0,  0, 10, 10,  0,  0, 10, 10,  0,  0,  0, 10, 10, 10, 10, 10,  0,  0,  0},
	{0,  0, 10, 10,  0,  0, 10, 10,  0,  0,  0,  0,  0,  0,  0, 10, 10,  0,  0},
	{0,  0, 10, 10,  0,  0, 10, 10,  0,  0,  0,  0,  0,  0,  0, 10, 10,  0,  0},
	{0,  0, 10, 10, 10, 10, 10, 10,  0,  0,  0,  0, 10, 10, 10, 10,  0,  0,  0},
	{0,  0,  0, 10, 10, 10, 10, 10,  0,  0,  0, 10, 10,  0,  0,  0,  0,  0,  0},
	{0,  0,  0,  0,  0,  0, 10, 10,  0,  0,  0, 10, 10,  0,  0,  0,  0,  0,  0},
	{0,  0,  0,  0,  0,  0, 10, 10,  0,  0,  0, 10, 10, 10, 10, 10, 10,  0,  0},
	{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
};
	int i = -1;
	int j = -1;

	while (++i < 19)
	{
		j = -1;
		while (++j < 11)
		{
			int x = 400+ (i * 20),
				y = 400 + (j * 20),
				z = a[j][i];

			//destination = [depart[0] + 20, depart[1]]// - z];
			//~~main.map[j][i] ? stroke(255, 0, 0) : stroke(255);
			x = (cte * x - cte2 * y) + 400;
			y = (z + (cte / 2) * x + (cte2/2) * y) + 400;
			printf("{%d, %d, %d, %d, %d}\n", x, y ,z, j, i);
			//x = (x + main.cte * z ) + main.points[0];
			//y = (z * (main.cte/2) + y) + main.points[1];
			p(m, (t_point){.x = x, .y = y}, a[j][i] ? RED1 : WHITE);
			//line(...depart, ...destination);
			//destination = [depart[0], depart[1] + 20]// - z];
			//line(...depart, ...destination);
		}
	}
	return ;
}

int		evt_live(int key, t_mlx *m)
{
	(void)key;
	(void)m;
	return (0);
}



int		fdf(void)
{
	t_mlx m;
	m.i = mlx_init();
	m.w = mlx_new_window(m.i, 2000, 2000, "GROS DELIRES");
	//clear(m);
	mlx_hook(m.w, KPRESS, 0, evt_live_key_pressed, &m);
	mlx_hook(m.w, KCLICK, 0, evt_live_key_clicked, &m);
	mlx_hook(m.w, MMOVE, 0, evt_live_mouse_move, &m);
	mlx_hook(m.w, MCLICK, 0, evt_live_mouse_clicked, &m);
	mlx_hook(m.w, MPRESS, 0, evt_live_mouse_pressed, &m);
	//mlx_loop_hook(m.w, evt_live, &m);
	menu(m);

	//call(m);

	printf("{%f}\n", M_PI);
	mlx_loop(m.i);
	return (18);
}

int		main(int ac, char **av)
{

	(void)ac;
	(void)av;
	//clear(m);

	fdf();


	return (0);
}
