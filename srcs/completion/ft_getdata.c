/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdata.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:01:38 by rcarette          #+#    #+#             */
/*   Updated: 2017/10/16 18:52:56 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		init_data(t_completion *data_compl)
{
	data_compl->path = NULL;
	data_compl->string = NULL;
	data_compl->buff_cursor = NULL;
	data_compl->after_cursor = NULL;
}

static int		manage_data_current(t_completion *data_compl, DIR **rep)
{
	char	*temporary;

	temporary = ft_strrchr(data_compl->path, '/');
	data_compl->string = ft_strdup(temporary + 1);
	*(temporary + 1) = '\0';
	(*rep != NULL) ? closedir(*rep) : 0;
	return (1);
}

void			ft_getdata(t_completion *data_compl, t_tc *tool)
{
	char	*temp_data;
	int		size_to;
	int		nbr;
	int		i;

	nbr = 0;
	i = -1;
	init_data(data_compl);
	ft_putnbr2("calc_pos", ft_calc_position(tool));
	data_compl->after_cursor = ft_strdup(&tool->buff[ft_calc_position(tool)]);
	//temp_data = ft_strndup(tool->buff, ft_calc_position(tool));
	temp_data = ft_strsub(tool->buff, 0, ft_calc_position(tool));
	(!temp_data) ? temp_data = ft_strnew(1) : 0; //s+c
	nbr = (ft_rstrlen(temp_data));
	size_to = (ft_rstrlen(temp_data));
//	while (temp_data[--size_to] != ' ' || size_to == (int)tool->nbr_prompt)
//		++nbr;
	if (nbr == 0)
	{
		data_compl->path = ft_strdup(" ");
		free(temp_data);
		return ;
	}
	if (!(data_compl->path = (char *)malloc(sizeof(char) * (nbr + 1))))
		exit(EXIT_FAILURE);
	ft_memset(data_compl->path, '\0', (nbr + 1));
	while (temp_data[++size_to])
		data_compl->path[++i] = temp_data[size_to];
	//ft_putendl2_fd("\npath titi = ", data_compl->path, 1);
	//ft_putchar('\n');
	free(temp_data);
}

int				ft_getdata_dir(t_completion *data_compl)
{
	DIR		*rep;
	char	*temporary;

	rep = NULL;
	if (ft_rstrlen(data_compl->path) == 1)
		return (1);
	else if ((rep = opendir(data_compl->path)) &&
		data_compl->path[ft_rstrlen(data_compl->path) - 1] == '/')
		return (closedir(rep));
	else if (data_compl->path[0] == '.')
	{
		if (ft_strchr(data_compl->path, '/'))
			return (manage_data_current(data_compl, &rep));
		temporary = ft_strchr(data_compl->path, '.');
		data_compl->string = ft_strdup(temporary + 1);
		*(temporary + 1) = '\0';
	}
	else if ((temporary = ft_strrchr(data_compl->path, '/')))
	{
		data_compl->string = ft_strdup(temporary + 1);
		*(temporary + 1) = '\0';
	}
	(rep != NULL) ? closedir(rep) : 0;
	//if (data_compl->string == NULL)
	//	ft_putendl("string est NULL");
	//else
	//	ft_putendl("TOTO");
	return (1);
}
