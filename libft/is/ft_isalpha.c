/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:50:17 by alienard          #+#    #+#             */
/*   Updated: 2019/10/07 18:41:21 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')))
		return (1);
	else
		return (0);
}
