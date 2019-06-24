/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:30:22 by rhealitt          #+#    #+#             */
/*   Updated: 2019/06/24 17:23:31 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

void	ft_string_insert(t_lstr *lstr, char *str, int index)
{
	int	len;

	if (lstr == NULL || str == NULL || index < 0 || index > lstr->length)
		return ;
	len = (int)ft_strlen(str);
	str[len] = '\n';
	len += 1;
	if (lstr->capacity < lstr->length + 1 + len)
		if (!ft_lstr_resize(lstr, lstr->length + len))
			return ;
	if (index != lstr->length)
		ft_memmove(lstr->str + index + len, lstr->str + index,
				   lstr->length - index);
	ft_memcpy(lstr->str + index, str, len);
	lstr->length += len;
	lstr->str[lstr->length] = 0;
	str[len - 1] = '\0';
}

int		ft_split_link(char *line, char **name1, char **name2)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '-')
		{
			*name1 = ft_strdup(line); // поправить лишний перебор
			(*name1)[i] = '\0';
			*name2 = ft_strdup(line + i + 1);
			if (*name1 == *name2)
				return (FT_WRONG_FORMAT);
			if (*name1 && *name2 && *name1[0] != '\0' && *name2[0] != '\0')
				return (FT_OK);
		}
		i++;
	}
	return (FT_WRONG_FORMAT);
}

int		ft_parse_name(t_lemin *li, char *name1, char *name2)
{
	t_room	*ptr1;
	t_room	*ptr2;
	t_room	*ptr3;

	ptr1 = NULL;
	ptr2 = NULL;
	ptr3 = li->rooms;

	while (ptr3)
	{
		if (!ft_strcmp(ptr3->name, name2))
			ptr2 = ptr3;
		if (!ft_strcmp(ptr3->name, name1))
			ptr1 = ptr3;
		if ((ptr1 && ptr2) || !ptr3->next)
			break;
		ptr3 = ptr3->next;
	}
	if (!ptr1 || !ptr2)
		return (FT_WRONG_FORMAT);
	ft_link_set(ptr1, ptr2);
	ft_link_set(ptr2, ptr1);
	return (FT_OK);
}

int		ft_parse_links(char *line, t_lemin *li)
{
	int		err;
	char	*name1;
	char	*name2;

	if (!li->rooms)
		return (FT_NO_ROOMS);
	if (!li->end_room)
		return (FT_NO_END);
	if (!li->start_room)
		return (FT_NO_START);
	err = ft_split_link(line, &name1, &name2);
	if (err == FT_OK)
		err = ft_parse_name(li, name1, name2);
	return (err);
}

/*
 рум-линк-рум не забыть поправить
 обработать дефисы в найме
 отрицательные координаты комнат проработать
 */
