/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 09:41:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/15 09:41:38 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		*rotate(t_point a, t_point b, double angle)
{
	int			mid[2][2];
	t_point		*xy;

	if (!(xy = malloc(sizeof(t_point) * 2)))
		return (NULL);
	mid[0][0] = a.x - (a.x + b.x) / 2;
	mid[0][1] = a.y - (a.y + b.y) / 2;
	mid[1][0] = b.x - (a.x + b.x) / 2;
	mid[1][1] = b.y - (a.y + b.y) / 2;
	angle *= 3.14 / 180;
	xy[0].x = cos(angle) * mid[0][0] - sin(angle) * mid[0][1] + (a.x + b.x) / 2;
	xy[0].y = sin(angle) * mid[0][0] + cos(angle) * mid[0][1] + (a.y + b.y) / 2;
	xy[1].x = cos(angle) * mid[1][0] - sin(angle) * mid[1][1] + (a.x + b.x) / 2;
	xy[1].y = sin(angle) * mid[1][0] + cos(angle) * mid[1][1] + (a.y + b.y) / 2;
	return (xy);
}
