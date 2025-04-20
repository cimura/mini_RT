/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_register.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:30:00 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 15:58:54 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*remove_double_quotes(char *str)
{
	char	*result;
	char	len;
	int		i;

	len = ft_strlen(str);
	if (str[0] != '\"' || str[len - 1] != '\"' || len < 3)
		return (print_err_msg(INV_PARAM, str), NULL);
	result = malloc(len - 1);
	if (result == NULL)
		return (NULL);
	str++;
	i = 0;
	while (*str != '\"' && i < len)
	{
		result[i] = *str;
		str++;
		i++;
	}
	result[i] = '\0';
	return (result);
}

t_texture	*init_new_texture(char *filename)
{
	t_texture	*tex;
	int			identifier;
	char		*no_quotes;

	if (ft_strncmp(filename, "N:", 2) == 0)
		identifier = NORMAL;
	else if (ft_strncmp(filename, "C:", 2) == 0)
		identifier = COLOR;
	else
		return (print_err_msg(INV_PARAM, filename), NULL);
	if (ft_strlen(filename) <= ft_strlen("S:\"\""))
		return (print_err_msg(INV_PARAM, filename), NULL);
	no_quotes = remove_double_quotes(&filename[ft_strlen("S:")]);
	if (no_quotes == NULL)
		return (NULL);
	tex = malloc(sizeof(t_texture));
	if (tex == NULL)
		return (NULL);
	if (load_texture(tex, no_quotes, identifier) != 0)
		return (print_err_msg(FILE_NOT_FOUND, no_quotes),
			free(tex), free(no_quotes), NULL);
	free(no_quotes);
	return (tex);
}

int	texture_register(char **filenames, t_list **lst)
{
	t_texture	*tex;
	t_list		*node;
	int			i;

	*lst = NULL;
	i = 0;
	while (filenames[i] != NULL)
	{
		tex = init_new_texture(filenames[i]);
		if (tex == NULL)
			return (1);
		node = ft_lstnew(tex);
		if (node == NULL)
			return (free(tex), 1);
		ft_lstadd_front(lst, node);
		i++;
	}
	return (0);
}
