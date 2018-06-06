/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 09:41:17 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/05 17:18:01 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "client.h"
#include "communication.h"

/* method function prototypes */
static int32_t	outgoing(int32_t cl, char *str);
static int32_t	incoming(t_player *p);

t_communicate communicate = {
	/* methods */
	{
		&outgoing
	},
	{
		&incoming
	}
};

/*
**	srv_toclient
*/

static int32_t	outgoing(int32_t cl, char *str)
{
	if (send(cl, str, strlen(str), 0) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
**	client_toserver
*/

static int32_t	incoming(t_player *p)
{
	int32_t	ret;

	printf("Recieving message from client <%d>\n", p->c_fd);
	ret = 0;
	bzero(p->buf, 513);
	if ((ret = recv(p->c_fd, p->buf, 512, 0)) < 0)
		return (EXIT_FAILURE);
	else if (!ret)
	{
		client.del(p->c_fd);
		return (-1);
	}
	p->buf[(ret - 1)] = '\0';
	return (EXIT_SUCCESS);
}
