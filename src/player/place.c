/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:58:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/19 23:56:21 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "player.h"
#include "egg.h"
#include "board.h"

static void		onboard(t_player *pl);
static void		onegg(t_player *pl);
static void		advance(t_player *pl);

__attribute__((constructor))void	construct_playerplace(void)
{
	player.place.onboard = &onboard;
	player.place.onegg = &onegg;
	player.place.advance = &advance;
}

static void		onboard(t_player *pl)
{
	pl->location.x = arc4random_uniform((uint32_t)SRV_BORD.x);
	pl->location.y = arc4random_uniform((uint32_t)SRV_BORD.y);
	pl->location.orientation = 1 << (arc4random_uniform((uint32_t)3));
	board.setplayer(pl);
}

static void		onegg(t_player *pl)
{
	t_dblist	*temp;
	t_team		*tm;
	t_egg		*eg;

	tm = pl->team;
	temp = ft_popfirst(&(tm->eggqueue));
	eg = (t_egg *)temp->data;
	memcpy(&(pl->location), &(eg->location), sizeof(t_location));
	egg.pool.add(eg);
}

static void		advance(t_player *pl)
{
	board.removeplayer(pl);
	if (pl->location.orientation & NORTH)
		(pl->location.y == 0) ? pl->location.y = SRV_BORD.y :
			(pl->location.y)--;
	else if (pl->location.orientation & SOUTH)
		(pl->location.y == SRV_BORD.y) ? pl->location.y = 0 :
			(pl->location.y)++;
	else if (pl->location.orientation & WEST)
		(pl->location.x == 0) ? pl->location.x = SRV_BORD.x :
			(pl->location.x)--;
	else if (pl->location.orientation & EAST)
		(pl->location.x == SRV_BORD.x) ? pl->location.x = 0 :
			(pl->location.x)++;
	board.setplayer(pl);
}
