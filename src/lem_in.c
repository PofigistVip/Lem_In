/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:52:15 by rhealitt          #+#    #+#             */
/*   Updated: 2019/06/27 15:41:50 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_lem_in.h"

static int	ft_creation(t_lemin **li, t_lstr **lstr)
{
	if ((*li = (t_lemin*)ft_memalloc(sizeof(t_lemin))) == NULL)
		return (FT_MEMORY);
	if (((*li)->collisions =
		(t_collision*)ft_memalloc(sizeof(t_collision))) == NULL)
		return (FT_MEMORY);
	if ((*lstr = ft_lstr_new_empty()) == NULL)
		return (FT_MEMORY);
	return (FT_OK);
}

static void	ft_output(int error_state, t_lstr *lstr)
{
	if (error_state == FT_OK)
		ft_lstr_put(lstr);
	else
		ft_putstr("ERROR\n");
}

static void	ft_free(t_lemin **li, t_lstr **lstr)
{
	t_path		*path;
	t_path		*path_next;
	t_collision	*collision;

	if (li && *li)
	{
		path = (*li)->paths;
		while (path)
		{
			path_next = path->next;
			free(path);
			path = path_next;
		}
		collision = (*li)->collisions;
		while (collision->prev)
		{
			collision = collision->prev;
			free(collision->next);
		}
		free(collision);
		ft_room_full_free(&(*li)->rooms);
		free(*li);
		*li = NULL;
	}
	lstr ? ft_lstr_destroy(lstr) : NULL;
}

int			main(void)
{
	int		err;
	t_lemin	*li;
	t_lstr	*lstr;

	li = NULL;
	lstr = NULL;
	err = ft_creation(&li, &lstr);
	if (err == FT_OK)
		err = ft_validation(0, li, lstr);
	if (err == FT_OK)
		err = ft_solution(li);
	if (err == FT_OK)
		err = ft_migration(li, lstr);
	ft_output(err, lstr);
	ft_free(&li, &lstr);
	return (0);
}
