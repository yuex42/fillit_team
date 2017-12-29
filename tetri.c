/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   T1.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 03:02:55 by ablin             #+#    #+#             */
/*   Updated: 2017/12/18 21:44:50 by ablin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"
#include <stdio.h>

void	ft_show1(char **arr)
{
	int i;
	int j;
	i = 0;
	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			ft_putchar(arr[i][j]);
			j++;
		}
		i++;
	}
}

char	**ft_set_map(char **map, char **board, int line)
{
	int		i;
	int		j;

	i = 0;
	while (i < line)
	{
		j = 0;
		while (j < line)
		{
			map[i][j] = board[i][j];
			j++;
		}
		map[i][j] = '\n';
		map[i][j + 1] = '\0';
		i++;
	}
	map[i] = NULL;
	ft_show1(map);
	return (map);
}

char	**ft_first_map(int line, int col, char **board)
{
	char	**map;
	int		i;

	i = 0;
	if (line < col)
		line = col;
	if ((map = (char **)malloc(sizeof(char *) * (line + 1))) == NULL)
		return (0);
	while (i < line)
	{
		if ((map[i] = (char *)malloc(sizeof(char) * (line + 1))) == NULL)
			return (0);
		i++;
	}
	map = ft_set_map(map, board, line);
	return (map);
}

int		ft_first_tetri(char **board)
{
	tetri_struct	tetri;

	tetri.i = 0;
	tetri.column = 0;
	tetri.total = 0;
	while (board[tetri.i] != NULL && tetri.total != 4)
	{
		tetri.count = 0;
		tetri.j = 0;
		while (board[tetri.i][tetri.j] != '\0')
		{
			if (board[tetri.i][tetri.j] == '#')
			{
				board[tetri.i][tetri.j] = 'A';
				tetri.count = tetri.j + 1;
				tetri.total++;
			}
			tetri.j++;
		}
		if (tetri.column < tetri.count)
			tetri.column = tetri.count;
		tetri.i++;
	}
	ft_first_map(tetri.i, tetri.column, board);
	return (1);
}

char	**ft_set()
{
	char	**map;
	int		line;
	int		col;

	if ((map = (char **)malloc(sizeof(char *) * (2 + 1))) == NULL)
		return (0);
	line = 0;
	while (line < 2)
	{
		col = 0;
		map[line] = ft_strnew(3);
		while (col < 2)
		{
			map[line][col] = '.';
			col++;
		}
		map[line][col] = '\n';
		map[line][col + 1] = '\0';
		line++;
	}
	map[line] = NULL;
	return (map);
}

s_pos	ft_getpos(char **board, int call)
{
	s_pos	pos;
	int		line;
	int		col;
	int		count;

	line = 0;
	count = 0;
	
	pos.x = 0;//////
	pos.y = 0;//////
	while (board[line] != NULL)
	{
		col = 0;
		while (board[line][col] != '\0')
		{
			if (board[line][col] == '#')//can probably omit the first #
				count++;
			if (count == call)
			{
				pos.x = line;
				pos.y = col;
				return (pos);
			}
			col++;
		}
		line++;
	}
	return (pos); //check if old pos and pos returned are the same, if it's the case, abort
}

int		ft_fit(char **map, char **board, int size)
{
	//free each line of the board then the board itself after copying the tetriminos
	//same for the map when expanding itself
	int		line;
	int		col;
	int		call;
	s_pos	pos;
	
	line = 0;
	while (map[line] != NULL)
	{
		col = 0;
		while (map[line][col] != '\0')
		{
			call = 2; //on check direct pour la pos du 2e hashtagd
			if (map[line][col] == '.')
			{
				pos = ft_getpos(board, call);
				call++;
				while ((line + pos.x) < size && (col + pos.y) < size &&  map[line + pos.x][col + pos.y] == '.' && call != 4)
				{
					pos = ft_getpos(board, call);
					call++;
				}
				if ((line + pos.x) < size && (col + pos.y) < size && map[line + pos.x][col + pos.y] == '.' && call == 4)
				{
				ft_putstr("fits");
				//	ft_insert(map, board);
					return (1);
				}
			}
			col++;
		}
		line++;
	}
	return (0);
}

char	**ft_map(char **map, int size)//should free the old map
{
	char	**newmap;
	int		line;
	int		col;

	if ((newmap = (char **)malloc(sizeof(char *) * (size + 2))) == NULL)//size + 2 cause we send the size of the board w/o counting the \0
		return (0);
	line = 0;
	while (map[line] != NULL)
	{
		col = -1;
		newmap[line] = ft_strnew(size + 2);//see above why size + 2
		while (map[line][++col] != '\n')
			newmap[line][col] = map[line][col];
		newmap[line][col] = '.';
		newmap[line][col + 1] = '\n';
		newmap[line][col + 2] = '\0';
		line++;
	}
	col = -1;
	newmap[line] = ft_strnew(size + 1);
	while (col++ < size)
		newmap[line][col] = '.';
	newmap[line][col] = '\n';
	newmap[line][col + 1] = '\0';
	newmap[line + 1] = NULL;
	ft_show1(newmap);
	ft_putchar('\n');
	return (newmap);
}

void	ft_test(char **board)
{
	char **map;
	map = ft_strsplit("#...\n .#..\n ..#.\n ...#\n ", ' ');
	ft_show1(map);
	if (ft_fit(map, board, 4) == 0)
		ft_putstr("cant fit\n");
	return;
	/*
	map = ft_set();
	if (ft_fit(map, board, 2) == 0)
	{
		map = ft_map(map, 2);
		if (ft_fit(map, board, 3) == 0)
		{
			map = ft_map(map, 3);
			ft_fit(map, board, 4);
		}
	}*/
}
/*
int	main()
{
	return (0);
}*/
