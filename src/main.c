/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/13 11:54:59 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
//
// t_point		rasterise(t_mlx *fdf, t_point p)
// {
// 	double cte;
// 	double cte2;
// 	t_point p2 = p;
// 	int z;
// 	int *other;
//
// 	z = fdf->map->board[p.y][p.x] * fdf->altitude;
// 	other = (int[4]){fdf->map->board[p2.y][p2.x - 1] * fdf->altitude,
// 		fdf->map->board[ft_max(p2.y - 1, 0)][p2.x] * fdf->altitude};
// 	cte = 0.5;
// 	cte2 = 0.5;
// 	fdf->zoom = ft_max(fdf->zoom, 1);
// 	p.x = (p.x * fdf->zoom);
// 	p.y = (p.y * fdf->zoom);
// 	p.x = (double[2]){p.x + cte * z, cte * p.x - cte2 * p.y}[fdf->iso];
// 	p.y = (double[2]){p.y + (cte / 2.0) * z,
// 		-z + (cte / 2.0) * p.x + (cte2 / 2.0) * p.y}[fdf->iso];
// 	if ((abs(z) > 0 || (abs(other[0]) > 0)) && p2.x)
// 		fdf->color = PURPLE4;
// 	else
// 		fdf->color = RED1;
// 	return (p);
// }

t_point		rasterise(t_mlx *fdf, t_point p, int x)
{
	double	cte;
	double	cte2;
	t_point	p2;
	int		z_c[2];
	int		*alt;

	p2 = p;
	z_c[0] = fdf->map->board[p.y][p.x] * fdf->altitude;
	alt = (int[2]){fdf->map->board[p2.y][p2.x - 1] * fdf->altitude,
			fdf->map->board[ft_max(p2.y - 1, 0)][p2.x] * fdf->altitude};
	cte = 0.5;
	cte2 = 0.5;
	fdf->zoom = ft_max(fdf->zoom, 1);
	p.x = (p.x * fdf->zoom);
	p.y = (p.y * fdf->zoom);
	p.x = (double[2]){p.x + cte * z_c[0], cte * p.x - cte2 * p.y}[fdf->iso];
	p.y = (double[2]){p.y + (cte / 2.0) * z_c[0],
		-z_c[0] + (cte / 2.0) * p.x + (cte2 / 2.0) * p.y}[fdf->iso];
	if (abs(z_c[0]) || (((x && abs(alt[0])) && p2.x) || (!x && abs(alt[1]))))
		fdf->color = PURPLE4;
	else
		fdf->color = RED1;
	return (p);
}

void		put_borders(t_mlx *fdf)
{
	int i;

	fdf->is_border = 1;
	i = DRAW_W - 1;
	while (++i < WIN_W)
		put_line(fdf, (t_points){(t_point){i, WIN_H - 1}, (t_point){i, 0}}, 0, PURPLE4);
	fdf->is_border = 0;
}

void		draw(t_mlx *fdf)
{
	int		i;
	int		j;
	t_point p1;
	t_point p2;
	j = -1;
	while (++j < fdf->map->y && !(i = 0))
		while (i < fdf->map->x)
		{
			p1 = (t_point){i, j};
			p2 = (t_point){i == fdf->map->x - 1 ? i : i + 1, j};
			p1 = rasterise(fdf, p1, 1);
			p2 = rasterise(fdf, p2, 1);
				put_line(fdf, (t_points){p1, p2}, 1, fdf->color);
			p2 = (t_point){i, j == fdf->map->y - 1 ? j : j + 1};
			p2 = rasterise(fdf, p2, 0);
				put_line(fdf, (t_points){p1, p2}, 1, fdf->color);
			i++;
		}
	put_borders(fdf);
}

void	print_map(t_map *map)
{
	int i;
	int j;

	j = 0;
	while (j < map->y)
	{
		i = 0;
		while (i < map->x)
		{
			printf("%*d", !i ? 0 : 3, map->board[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

t_mlx	*init(int fd)
{
	t_mlx	*fdf;

	if (!(fdf = (t_mlx *)malloc(sizeof(t_mlx))))
		exit(1);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIN_W, WIN_H, "fdf");
	fdf->map = create_map(fd);
	if (!fdf->mlx || !fdf->win || close(fd))
		exit(1);
	mlx_hook(fdf->win, KPRESS, 0, evt_live_key_pressed, fdf);
	mlx_hook(fdf->win, KCLICK, 0, evt_live_key_clicked, fdf);
	mlx_hook(fdf->win, MMOVE, 0, evt_live_mouse_move, fdf);
	mlx_hook(fdf->win, MCLICK, 0, evt_live_mouse_clicked, fdf);
	mlx_hook(fdf->win, MPRESS, 0, evt_live_mouse_pressed, fdf);
	mlx_hook(fdf->win, KEYRELEASE, 0, evt_live_key_released, fdf);
	fdf->img = NULL;
	fdf->zoom = 100;
	fdf->xoffset = 500;
	fdf->yoffset = 400;
	fdf->altitude = 1;
	fdf->is_border = 0;
	fdf->is_shift = 0;
	fdf->iso = 1;
	fdf->is_ok = 0;
	fdf->color = (int[4]){RED1, YELLOW, GREEN3, BLUE_VIOLET}
		[ft_max((unsigned int)(&fdf->mlx) / 200 % 4, 0)];
	fdf->is_pressed = 0;
	fdf->angle_x = 0;
	fdf->angle_y = 0;
	fdf->angle_z = 0;
	return (fdf);
}

int				main(int argc, char **argv)
{
	int		fd;
	t_mlx	*m;

	if (argc != 2)
	{
		ft_dprintf(2, "usage: fdf input_file");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		perror("error");
	m = init(fd);
	process(m);
	mlx_loop(m->mlx);
	return (0);
}
