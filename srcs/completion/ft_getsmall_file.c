/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getsmall_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 20:16:12 by rcarette          #+#    #+#             */
/*   Updated: 2017/06/29 22:09:50 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

char		*ft_getsmall_file(t_list *list)
{
	char	*small_file;

	small_file = list->file;
	while (list)
	{
		if (ft_strlen(small_file) > ft_strlen(list->file))
			small_file = list->file;
		list = list->next;
	}
	return (small_file);
}
