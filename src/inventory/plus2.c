/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 16:23:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/16 16:45:50 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "inventory.h"

static void		mend(uint64_t *);
static void		phir(uint64_t *);
static void		thys(uint64_t *);

__attribute__((constructor))void		construct_invplustwo(void)
{
	inventory.plus.mend	= &mend;
	inventory.plus.phir = &phir;
	inventory.plus.thys = &thys;
}

static void		mend(uint64_t *items)
{
	uint64_t	item;

	item = MENDIANE(*items);
	if (item <= 255)
	{
		item++;
		*items = MENDIANE_INS(*items, item);
	}
}

static void		phir(uint64_t *items)
{
	uint64_t	item;

	item = PHIRAS(*items);
	if (item <= 255)
	{
		item++;
		*items = PHIRAS_INS(*items, item);
	}
}

static void		thys(uint64_t *items)
{
	uint64_t	item;

	item = THYSTAME(*items);
	if (item <= 255)
	{
		item++;
		*items = THYSTAME_INS(*items, item);
	}
}
