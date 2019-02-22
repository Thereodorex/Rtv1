/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:34:16 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/21 20:48:30 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void					gnl(int fd, char **line)
{
	if (*line)
		free(*line);
	if ((get_next_line(fd, line)) == -1)
		STOP;
}

char					*get_word(char *line)
{
	while (*line && *line != ' ')
		line++;
	while (*line == ' ')
		*line++ = '\0';
	return (line);
}

static unsigned long	get_full(char **line, int *sign)
{
	unsigned long	full;

	full = 0;
	*sign = 0;
	if (**line == '-')
	{
		++(*line);
		*sign = 1;
	}
	while (ft_isdigit(**line))
	{
		if ((full = full * 10 + **line - '0') > 1000000)
			STOP;
		++(*line);
	}
	return (full);
}

double					get_double(char *line)
{
	double			num;
	double			prec;
	int				sign;

	num = get_full(&line, &sign) * 1.0;
	if (*line++ != '.')
		STOP;
	prec = 0.1;
	while (ft_isdigit(*line))
	{
		if (prec < 0.0001)
			STOP;
		num += (*line++ - '0') * prec;
		prec *= 0.1;
	}
	if (*line != '\0' && *line != ',' && *line != ')')
		STOP;
	return (sign ? num * -1.0 : num);
}

t_vec					get_vec(char *line)
{
	t_vec	new;
	char	*num2;
	char	*num3;

	if (*line++ != '(')
		STOP;
	num2 = get_word(line);
	num3 = get_word(num2);
	new.x = get_double(line);
	new.y = get_double(num2);
	new.z = get_double(num3);
	return (new);
}
