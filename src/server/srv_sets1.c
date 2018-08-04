/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_sets1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:13:36 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/18 00:16:49 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "server.h"

#define TEAM ((g_servenv->teams)[(i - 1)])

static inline __attribute__((always_inline))int32_t	get_nteams(char *str)
{
	int32_t	i;
	int32_t	nteams;

	i = 0;
	if (!(nteams = ft_atoi(str)))
	{
		while (*str == '0')
			str++;
		if (*str)
		{
			ft_printf("Invalid parameter: %s\n", str);
			return (EXIT_FAILURE);
		}
	}
	SRV_GENV.nteams = nteams;
	return (EXIT_SUCCESS);

}

int32_t		srv_setteams(char **argv, t_opts *opt)
{
	int32_t	i;

	i = 0;
	if (get_nteams(argv[i++]) == EXIT_FAILURE
		|| !(SRV_GENV.nteams))
		return (EXIT_FAILURE);
	opt->nparams += SRV_GENV.nteams;
	if (!(g_servenv->teams = (t_team *)ft_memalloc(sizeof(t_team) * SRV_GENV.nteams)))
		return (EXIT_FAILURE);
	while (argv[i] && (i <= SRV_GENV.nteams))
	{
		if (!(TEAM.name = (char *)ft_memalloc(ft_strlen(argv[i]) + 1))
			|| (!(ft_strcpy(TEAM.name, argv[i]))))
			return (EXIT_FAILURE);
		TEAM.nplayers = 1;
		TEAM.teamindex = (i - 1);
		i++;
	}
	if (i != opt->nparams)
	{
		ft_printf("Only %d team name(s) provided out of %d\n", (i - 1), SRV_GENV.nteams);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int32_t		srv_setboardx(char **argv, __attribute__((unused))t_opts *opt)
{
	int32_t	i;
	int32_t	width;

	i = 0;
	if (!(width = ft_atoi(*argv)))
	{
		while ((*argv)[i] == '0')
			i++;
		if ((*argv)[i])
		{
			ft_printf("Invalid parameter: %s\n", *argv);
			return (EXIT_FAILURE);
		}
	}
	g_servenv->board.x = width - 1;
	return (EXIT_SUCCESS);
}

int32_t		srv_setboardy(char **argv, __attribute__((unused))t_opts *opt)
{
	int32_t	i;
	int32_t	height;

	i = 0;
	if (!(height = ft_atoi(*argv)))
	{
		while ((*argv)[i] == '0')
			i++;
		if ((*argv)[i])
		{
			ft_printf("Invalid parameter: %s\n", *argv);
			return (EXIT_FAILURE);
		}
	}
	g_servenv->board.y = height - 1;
	return (EXIT_SUCCESS);
}
