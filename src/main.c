/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/13 14:15:12 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline t_point	rasterise(t_mlx *fdf, t_point p)
{
	double	cte;
	double	cte2;
	t_point	p2;
	int		z;

	p2 = p;
	z = fdf->map->board[p.y][p.x] * fdf->altitude;
	cte = 0.5;
	cte2 = 0.5;
	fdf->zoom = ft_max(fdf->zoom, 1);
	p.x = (p.x * fdf->zoom);
	p.y = (p.y * fdf->zoom);
	p.x = (double[2]){p.x + cte * z, cte * p.x - cte2 * p.y}[fdf->iso];
	p.y = (double[2]){p.y + (cte / 2.0) * z,
		-z + (cte / 2.0) * p.x + (cte2 / 2.0) * p.y}[fdf->iso];
	p.color = fdf->clr;
	return (p);
}

void					draw(t_mlx *m)
{
	int		i;
	int		j;
	t_point p1;
	t_point p2;

	j = -1;
	while (++j < m->map->y && !(i = 0))
		while (i < m->map->x)
		{
			p1 = (t_point){i, j, m->clr};
			p2 = (t_point){i == m->map->x - 1 ? i : i + 1, j, m->clr};
			p1 = rasterise(m, p1);
			p2 = rasterise(m, p2);
			put_line(m, p1, p2, 1);
			p2 = (t_point){i, j == m->map->y - 1 ? j : j + 1, m->clr};
			p2 = rasterise(m, p2);
			put_line(m, p1, p2, 1);
			i++;
		}
	m->is_border = 1;
	i = DRAW_W - 1;
	while (++i < WIN_W)
		put_line(m, (t_point){i, WIN_H - 1, 0x001942}, (t_point){i, 0, 0}, 0);
	m->is_border = 0;
}

static inline void		init_variables(t_mlx *fdf)
{
	fdf->img = NULL;
	fdf->zoom = 100;
	fdf->xo = 500;
	fdf->yo = 400;
	fdf->altitude = 1;
	fdf->is_border = 0;
	fdf->is_shift = 0;
	fdf->iso = 1;
	fdf->is_ok = 0;
	fdf->clr = (int[5]){RED1, YELLOW, GREEN3, BLUE_VIOLET, 0xff00c3}
		[ft_max((unsigned int)(&fdf->mlx) / 200 % 5, 0)];
	fdf->is_pressed = 0;
}

static t_mlx inline		*init(int fd)
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
	mlx_hook(fdf->win, MMOVE, 0, evt_live_mouse_move, fdf);
	mlx_hook(fdf->win, MCLICK, 0, evt_live_mouse_clicked, fdf);
	mlx_hook(fdf->win, MPRESS, 0, evt_live_mouse_pressed, fdf);
	mlx_hook(fdf->win, KEYRELEASE, 0, evt_live_key_released, fdf);
	init_variables(fdf);
	return (fdf);
}

int						main(int argc, char **argv)
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
