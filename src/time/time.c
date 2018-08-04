/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 10:53:55 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/20 00:21:52 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "time.h"
#include "events.h"
#include "death.h"

static int32_t	compare(t_timeval *relative, t_timeval *time2);
static void		settimer(t_timeval **timer);
static void		setalarm(t_timeval *alarm, float factor);

__attribute__((constructor))void	construct_time(void)
{
	time.compare = &compare;
	time.settimer = &settimer;
	time.setalarm = &setalarm;
}

static int32_t	compare(t_timeval *relative, t_timeval *time2)
{
	printf("[TIME]\n  -- Compare --\n  time2 <%ld> seconds & <%d> microseconds\n  vs\n to relative-><%ld> seconds & <%d> microseconds\n", time2->tv_sec, time2->tv_usec, relative->tv_sec, relative->tv_usec);
	if ((relative->tv_sec > time2->tv_sec)
		|| (time2->tv_sec == relative->tv_sec && (relative->tv_usec >= time2->tv_usec)))
		return (1);
	return (0);
}

static t_timeval	*nearestalarm(void)
{
	printf("  %sFIND THE NEAREST ALARM%s\n", "\033[48;2;50;48;12m", "\033[0m"); 
	if (!(event.queue.data->first)
		&& !(death.track.eggs->first))
		return (NULL);
	if (!(event.queue.data->first))
	{
		printf("%sNOTHING on the queue??%s\n", "\033[48;2;50;48;12m", "\033[0m"); 
		return (&(((t_egg *)(death.track.eggs->first->data))->alarm));
	}
	if (!(death.track.eggs->first))
	{
		printf("  Event queue alarm, nothing on deathtrack\n");
		return (&(((t_event *)(event.queue.data->first->data))->alarm));
	}
	if (time.compare(&(((t_event *)(event.queue.data->first->data))->alarm),
					&(((t_egg *)(death.track.eggs->first->data))->alarm)))
	{
		printf("  Egg death event\n");
		return (&(((t_egg *)(death.track.eggs->first->data))->alarm));
	}
	else
	{
		printf("  Event queue alarm\n");
		return (&(((t_event *)(event.queue.data->first->data))->alarm));
	}
	return (NULL);
}

static void		settimer(t_timeval **timer)
{
	t_timeval	temp;
	t_timeval	*alarm;

	gettimeofday(&temp, NULL);
	if (!(alarm = nearestalarm()))
	{
		if (*timer)
			ft_memdel((void **)timer);
		printf("  No events to check\n");
		return ;
	}
	if (!(*timer))
		(*timer) = (t_timeval *)calloc(1, sizeof(t_timeval));
	printf("  Alarm pulled : <%ld> seconds & <%d> microseconds\n",
		alarm->tv_sec, alarm->tv_usec);
	(*timer)->tv_sec = alarm->tv_sec - temp.tv_sec;
	if ((*timer)->tv_sec < 0
		|| ((((*timer)->tv_usec = alarm->tv_usec - temp.tv_usec) < 0)
		&& !(*timer)->tv_sec))
		bzero((*timer), sizeof(t_timeval));
	else if ((*timer)->tv_usec < 0)
	{
		(*timer)->tv_usec = 1000000 + (*timer)->tv_usec;
		(*timer)->tv_sec ? (*timer)->tv_sec-- : 0;
	}
	printf("  Timer set for <%ld> seconds & <%d> microseconds\n",
	(*timer)->tv_sec, (*timer)->tv_usec);
}

static void		setalarm(t_timeval *alarm, float factor)
{
	t_timeval	temp;
	double		interval;
	int64_t		i_interval;
	double		integer;
	int64_t		i_integer;

	gettimeofday(&temp, NULL);
	printf("[TIME]\n  -- Set Alarm --\n  It is <%ld> seconds & <%d> microseconds\n", temp.tv_sec, temp.tv_usec);
	interval = factor/SRV_GENV.timeinterval;
	integer = 0;
	if (interval > 1)
		interval = modf(interval, &integer);
	interval = (interval * 1000000);
	i_integer = (int64_t)integer;
	i_interval = (int64_t)interval;
	printf("  This is the interval now : %lld\n  This is the integer : %lld\n",
			i_interval, i_integer);
	alarm->tv_sec = temp.tv_sec + i_integer;
	if ((alarm->tv_usec = temp.tv_usec + i_interval) >= 1000000)
	{
		alarm->tv_usec = i_interval - (1000000 - temp.tv_usec);
		alarm->tv_sec++;
	}
	printf("  Alarm at <%ld> seconds & <%d> microseconds\n",
			alarm->tv_sec, alarm->tv_usec);
}
