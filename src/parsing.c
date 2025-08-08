/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchaman <abchaman@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:01:28 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/08 17:17:33 by abchaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

int check_name(char *str)
{
    int i;
    int last;
    
    i = 0;
    last = -1;
    if (!str || !str[0])
        return (1);
    while (str[i])
    {
        if (str[i] == '.' && str[i + 1] == '.')
            return (1);
        if (str[i] == '.')
            last = i;
        i++;
    }
    if (last <= 0)
        return (1);
    if (ft_strncmp(&str[last], ".cub", 4))
            return (1);
    if (str[last + 4] != '\0')
        return (1);
    return (0);
}

static int count_lines(char *str)
{
    int     fd;
    int     count;
    char    *line;

    count = 0;
    fd = open(str, O_RDONLY);
    if (fd == -1)
        return (-1);
    while ((line = get_next_line(fd)) != NULL)
    {
        count++;
        free(line);
    }
    close(fd);
    return (count);
}
char **open_read(char *str)
{
    int     fd;
    char    **lines;
    char    *line;
    int     count;
    
    count = count_lines(str);
    if (count <= 0)
        return (printf("error: empty file or cannot read\n"), NULL);
    lines = malloc(sizeof(char *) * (count + 1));
    if (!lines)
        return (NULL);    
    fd = open(str, O_RDONLY);
    if (fd == -1)
    {
        free(lines);
        return (printf("error : cannot open file\n"), NULL);
    }
    count = 0;
    while ((line = get_next_line(fd)) != NULL)
        lines[count++] = line;
    lines[count] = NULL;
    close(fd);
    return (lines); 
}
