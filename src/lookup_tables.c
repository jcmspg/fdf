/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_tables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:39:55 by joao              #+#    #+#             */
/*   Updated: 2024/08/28 19:02:43 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to calculate the sin of angles and store them in a table
// allocates memory for the table and assigns it to the struct t_lookup
void trig_table_sin(w_data *data)
{
    int i;
    int *sin_tab;

    sin_tab = (int *)malloc(sizeof(int) * DEGREE_MAX);
    if (!sin_tab)
        return;

    i = 0;
    while (i < DEGREE_MAX)
    {
        sin_tab[i] = (int)(sin(i * PI / 180) * SCALE_TRIG);
        i++;
    }
    data->lookup->sin_table = sin_tab;
}

// function to calculate the cos of angles and store them in a table
// allocates memory for the table and assigns it to the struct t_lookup

void trig_table_cos(w_data *data)
{
    int i;
    int *cos_tab;

    cos_tab = (int *)malloc(sizeof(int) * DEGREE_MAX);
    if (!cos_tab)
        return;

    i = 0;
    while (i < DEGREE_MAX)
    {
        cos_tab[i] = (int)(cos(i * PI / 180) * SCALE_TRIG);
        i++;
    }
    data->lookup->cos_table = cos_tab;
}
//functions to lookup the sin and cos values of an angle
int lookup_sin(w_data *data, int angle)
{
    return (data->lookup->sin_table[angle]);
}
int lookup_cos(w_data *data, int angle)
{
    return (data->lookup->cos_table[angle]);
}