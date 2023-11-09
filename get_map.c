/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 09:26:46 by himejjad          #+#    #+#             */
/*   Updated: 2023/11/09 16:47:34 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_face(t_args *args)
{
     int j;
    int i;

    j = 0;
    i = 0;
    int n = 0;
            int count = 0;
    while(args->argv[j])
    {
        i = 0;
        while(args->argv[j][i])
        {
        
            if ( args->argv[j][i] == 'N' && args->argv[j][i+1] == 'O'  && 
            args->argv[j][i+2] == ' ')
                count++;
            if ( args->argv[j][i] == 'S' && args->argv[j][i+1] == 'O' &&
                args->argv[j][i+2] == ' ')
                count++;
            if ( args->argv[j][i] == 'W' && args->argv[j][i+1] == 'E' &&
                args->argv[j][i+2] == ' ')
                count++;
            if ( args->argv[j][i] == 'E' && args->argv[j][i+1] == 'A' &&
                args->argv[j][i+2] == ' ')
                count++;
            if ( args->argv[j][i] == 'F' && args->argv[j][i+1] == ' ')
                count++;
            if ( args->argv[j][i] == 'C' && args->argv[j][i+1] == ' ')
                count++;
        i++;
        }
    j++;
    }
    if(count != 6)
        error();
}

int skip_space_2(t_args *args, int j, int i)
{
    // int i = 0;
    // int j = 0;
    int n = 0;

    // while(args->argv[j])
    // {
        // i = 0;
            i+=2;
        while (args->argv[j][i] == ' ')
        {
            // if (args->argv[j][i] != ' ')
            //     error();
            i++;
        }
    //     j++;
    // }
    return (i);
}

void get_deriction(t_args *args)
{
    int j;
    int i;

    j = 0;
    i = 0;
    while(args->argv[j])
    {
        i = 0;
        while(args->argv[j][i])
        {
             if ( args->argv[j][i] == 'N' && args->argv[j][i+1] == 'O')
                    args->no = ft_substr(args->argv[j], skip_space_2(args, j, i), ft_strlen(args->argv[j]));
             if ( args->argv[j][i] == 'S' && args->argv[j][i+1] == 'O')    
                    args->so = ft_substr(args->argv[j], skip_space_2(args, j, i), ft_strlen(args->argv[j]));
             if ( args->argv[j][i] == 'W' && args->argv[j][i+1] == 'E')
                    args->we = ft_substr(args->argv[j], skip_space_2(args, j, i), ft_strlen(args->argv[j]));
             if ( args->argv[j][i] == 'E' && args->argv[j][i+1] == 'A')
                    args->ea = ft_substr(args->argv[j], skip_space_2(args, j, i), ft_strlen(args->argv[j]));
             if ( args->argv[j][i] == 'F')
                    args->floor = ft_substr(args->argv[j], skip_space_2(args, j, i-1), ft_strlen(args->argv[j]));
            if ( args->argv[j][i] == 'C')
                    args->cell = ft_substr(args->argv[j], skip_space_2(args, j, i-1), ft_strlen(args->argv[j]));
            i++;
        }
    j++;
    }
}

	int	ft_isalnum(int c)
{
    if (c == ' ')
        return (1);
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// void cell_floor(t_args *args)
// {
//     int j;
//     int i;
//     int count = 0;

//     j = 0;
//     i = 0;
//     while(args->argv[j])
//     {
//         i = 0;
//         while(args->argv[j][i])
//         {
//             if (args->argv[j][i] == 'F' || args->argv[j][i] == 'C')
//                 count++;
//             if(args->argv[j][i] == 'F')
//             {
//                 if (args->argv[j][i] == ' ' && args->argv[j][i+1] != ' ')
//                   args->floor = ft_substr(args->argv[4], i+1, ft_strlen(args->argv[4]));
//             }
//             if(args->argv[j][i] == 'C')
//             {
//                 if (args->argv[j][i] == ' ' && args->argv[j][i+1] != ' ')
//                   args->cell = ft_substr(args->argv[5], i+1, ft_strlen(args->argv[5])); 
//             }
//             i++;
//         }
//     j++;
//     }
//     // if (count != 3)
//     //     error();
// }

void skip_norm_n(t_args *args, int j, int i, char c)
{
    args->copy[args->height] = malloc(sizeof(char *));
    args->copy[args->height] = ft_strdup("");
    if(args->copy[j][i + 1] == '0' || args->copy[j][i + 1] == c)
        error();
    else if (args->copy[j][i - 1] == '0' || args->copy[j][i - 1] == c)
        error();
    else if (args->copy[j + 1][i] == '0' || args->copy[j + 1][i] == c )
        error();
    if (j == 0)
        j--;
    else if (args->copy[j - 1][i] == '0' || args->copy[j - 1][i] == c)
        {
                // printf("-=-=-=%s=-=-=\n", args->copy2[j-2]);
                error();
            }
    // else if (is_digit(args) == 0)
    //     error();
  
        
}

void skip_space(t_args *args)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(args->copy[j])
    {
        i = 0;
        while(args->copy[j][i])
        {
            if (args->copy[j][i] == '\t')
                i++;
            if (!ft_isalnum(args->copy[j][i]))
                error();
             if( args->copy[j][i] >= '2' && args->copy[j][i] <= '9')
                    error();
            if (args->copy[j][i] >= 'a' && args->copy[j][i] <= 'z')
                error();
            if (args->copy[j][i] >= 'A' && args->copy[j][i] <= 'Z')
                {
                    if (args->copy[j][i] == 'W' || args->copy[j][i] == 'S' || 
                        args->copy[j][i] == 'E' || args->copy[j][i] == 'N')
                        i++;
                    else
                    error();
                }
            if(args->copy[j][i] == ' ')
            {
                skip_norm_n(args, j, i, 'N');
                skip_norm_n(args, j, i, 'W');
                skip_norm_n(args, j, i, 'E');
                skip_norm_n(args, j, i, 'S');
                // else 
                i++;
            }
            i++;
        }
        j++;
    }
}

void check_n_w_s_e(t_args *args)
{
    int j;
    int i;
    int count = 0;

    j = 0;
    i = 0;
    while(args->copy[j])
    {
        i = 0;
        while(args->copy[j][i])
        {
             if (args->copy[j][i] == 'W' || args->copy[j][i] == 'N' ||
                args->copy[j][i] == 'S' || args->copy[j][i] == 'E')
                    count++;
            i++;
        }
    j++;
    }
    if(count != 1)
        error();
}

int check_coma(char *args)
{
    int i;
    int count = 0;

    i = 0;
    while(args[i])
    {
        if(args[i] == ',')
            count++;
        i++;
    }
    if (count != 2)
        error();
    return (count);
}

void check_max_rgb(t_args *args)
{
    int i;
    int j;
    j = 0;
    i = 0;
    if (args->rgb == NULL)
        error();
    while(args->rgb[i])
    {
       j  = 0;
       while(args->rgb[i][j])
       {
                if (!isdigit(args->rgb[i][j]))
                {
                    // if (args->rgb[i][j] == ',')
                    //     j++;
                    // printf("=-=-=-=-=-=->%s\n", args->rgb[i]);
                    error();

                }
        j++;
       }
            
        if (atoi(args->rgb[i]) > 255 || atoi(args->rgb[i]) < 0)
            error();
        i++;
    }
    // printf("%d\n", i);
    if (i != 3)
        error();
}
void check_espa(char *args)
{
    int i;

    i = 0;
    while(args[i])
    {
        if (args[i] == ' ')
                error();
        // if (args[0] != '.' && args[1] != '/')
        //         error();
        i++;
    }
    // i = 0;
    // while(args[i])
    // {
    //     if (args[i] == '/')
    //     {
    //     if (args[i - 1] != '.')
    //     {

    //         error();
    //     }

    //     }
    //     i++;
    // }
}

void get_rgb(t_args *args)
{
    check_espa(args->floor);
    check_espa(args->cell);
    check_coma(args->floor);
    check_coma(args->cell);
    check_espa(args->so);
    check_espa(args->we);
    check_espa(args->ea);
    check_espa(args->no);
    

    // printf
    args->rgb =  ft_split(args->floor, ',');
    check_max_rgb(args);
    args->floor_r = atoi(args->rgb[0]);
    args->floor_g = atoi(args->rgb[1]);
    args->floor_b = atoi(args->rgb[2]);
    args->rgb = NULL;
    args->rgb =  ft_split(args->cell, ',');
    check_max_rgb(args);
    args->cell_r = atoi(args->rgb[0]);
    args->cell_g = atoi(args->rgb[1]);
    args->cell_b = atoi(args->rgb[2]);
}



t_args * get_map(t_args *args)
{
    char *stock;

    stock = get_next_line(args->fd);
    if (!stock)
        error();
    args->str = NULL;
    while(stock)
    {
        args->str =  ft_strjoin(args->str, stock);
        free(stock);
        stock = get_next_line(args->fd);
    }
    args->argv = ft_split(args->str, '\n');
     args->copy = ft_split(args->str, '\n');
    // args->copy = malloc(sizeof(char**) * 46);
    args->copy = args->copy + 6;
    args->copy2 = args->copy;
    args->width = ft_strlen(args->copy[0]);
    check_face(args);
    check_n_w_s_e(args);
    int j = 0 - 1;
    j--;
    // printf("-=-=-=->%s\n", args->copy[j]);
    get_deriction(args);
    // printf("=-=-=-=->%s\n", args->ea);
    args->height = count_lines(args->copy);
   skip_space(args);
//    cell_floor(args);
   get_rgb(args);
//    printf("-=-=-=->%s\n", args->argv[5]);
//    printf("-=-=-=->%s\n", args->cell);
    // int i = 0;
    return(args);
}
