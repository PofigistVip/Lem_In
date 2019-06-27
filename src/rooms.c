/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:52:59 by rhealitt          #+#    #+#             */
/*   Updated: 2019/06/27 13:32:48 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_lem_in.h"

/*
** Create new room in room's array and return it
** Room index will set automatically
*/

t_room	*ft_room_new(t_lemin *li, t_room **rooms)
{
	t_room	*room;
	t_room	*last;

	if (rooms == NULL)
		return (NULL);
	if ((room = (t_room*)ft_memalloc(sizeof(t_room))) == NULL)
		return (NULL);
	if (*rooms == NULL)
		*rooms = room;
	else
	{
		last = *rooms;
		while (last->next != NULL)
			last = last->next;
		last->next = room;
	}
	++li->rooms_count;
	return (room);
}

/*
** Return room from room's array by room index
*/

// t_room	*ft_room_get(t_room *rooms, int index)
// {
// 	if (rooms == NULL)
// 		return (NULL);
// 	/* rooms->index != index можно заменить index-- != 0
// 	если  последовательность индексов никогда не будет нарушаться (без удаления комнат?)*/
// 	while (rooms && rooms->index != index)
// 		rooms = rooms->next;
// 	/* Если rooms->index != index, а список комнат закончился вернется null
// 	т.к. rooms = rooms->next на последней итерации запишет в rooms NULL*/
// 	return (rooms);
// }

/*
** Frees an array of rooms
*/

void	ft_room_full_free(t_room **rooms)
{
	t_room	*current;
	t_room	*next;
	t_link	*lnk;
	t_link	*next_lnk;

	if (rooms == NULL)
		return ;
	current = *rooms;
	while (current)
	{
		next = current->next;
		current->name ? free(current->name) : NULL;
		lnk = current->links;
		while (lnk)
		{
			next_lnk = lnk->next;
			free(lnk);
			lnk = next_lnk;
		}
		free(current);
		current = next;
	}
	*rooms = NULL;
}

void	ft_rooms_reset(t_room *rooms)
{
	while (rooms)
	{
		rooms->closed = 0;
		if (rooms->lock != -1)
		{
			rooms->weight = 0;
			rooms->lock = 0;
			rooms->path_prev = NULL;
		}
		else
			rooms->lock = 1;
		rooms = rooms->next;
	}
}
