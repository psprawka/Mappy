/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 15:30:42 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/19 23:16:02 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H


typedef struct		s_playerpool
{
	t_queue			*data;
	int32_t			(*new)(void);
	t_dblist		*(*pop)(void);
	void			(*add)(t_player *add);
}					t_playerpool;

typedef struct		s_playerplace
{
	void			(*onboard)(t_player *);
	void			(*onegg)(t_player *);
	void			(*advance)(t_player *);
}					t_playerplace;

typedef struct		s_playerdeath
{
	void			(*soon)(t_player *);
	void			(*now)(void);
}					t_playerdeath;

typedef struct		s_player_methods
{
	t_playerpool	pool;
	t_playerplace	place;
	t_playerdeath	death;
	int32_t			(*new)(int32_t);
	void			(*eats)(t_player *);
	int32_t			(*command)(t_player *);
}					t_player_methods;

t_player_methods	player;

#endif
