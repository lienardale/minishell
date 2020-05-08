/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 08:15:47 by cdai              #+#    #+#             */
/*   Updated: 2020/05/08 10:40:06 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split2(char *s, char c)
{
	char	**r;
	int		nb;
	int		i[3];

	i[2] = -1;
	while (++(i[2]) < 2)
	{
		i[0] = 0;
		nb = 0;
		while (s[i[0]])
		{
			while (s[i[0]] && s[i[0]] == c)
				(i[0])++;
			i[1] = i[0];
			while (s[i[0]] && s[i[0]] != c)
				(i[0])++;
			if (i[2] && s[i[1]] && !(r[nb] = ft_substr(s, i[1], i[0] - i[1])))
				return (ft_free_split(r));
			nb++;
		}
		if (!i[2] && !(r = ft_calloc(nb + 1, sizeof(char*))))
			return (ft_free_split(r));
	}
	return (r);
}
