/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ngn_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-oliv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 19:54:13 by rde-oliv          #+#    #+#             */
/*   Updated: 2020/07/25 18:58:51 by rde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ngn_int.h"

t_ngn		*ngn_init(char *path)
{
	t_ngn	*ngn;
	int		fd;

	if ((!ft_strchr(path, '.') || ft_strcmp(ft_strrchr(path, '.'), ".cub")) &&
			(g_ngnerr = NGN_FILERR))
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0 && (g_ngnerr = NGN_OPENERR))
		return (NULL);
	if ((ngn = (t_ngn *)ft_calloc(1, sizeof(t_ngn))) == NULL)
	{
		g_ngnerr = NGN_MEMERR;
		close(fd);
		return (NULL);
	}
	if (ngn_int_config_header(fd, ngn) == EXIT_FAILURE ||
		ngn_int_config_map(fd, ngn) == EXIT_FAILURE ||
		ngn_int_sprites_init(ngn) == EXIT_FAILURE)
	{
		close(fd);
		ngn_destroy(ngn);
		return (NULL);
	}
	close(fd);
	return (ngn);
}
