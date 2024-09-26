/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_tables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:39:55 by joao              #+#    #+#             */
/*   Updated: 2024/09/26 17:55:32 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to calculate the sin of angles and store them in a table
// allocates memory for the table and assigns it to the struct t_lookup
void trig_table_sin(w_data *data)
{
    int i;
    float *sin_tab;

    sin_tab = (float *)malloc(sizeof(float) * DEGREE_MAX);
    if (!sin_tab)
        return;

    i = 0;
    while (i < DEGREE_MAX)
    {
        sin_tab[i] = (float)(sin(i * PI / 180) * SCALE_TRIG);
        i++;
    }
    data->lookup->sin_table = sin_tab;
}

// function to calculate the cos of angles and store them in a table
// allocates memory for the table and assigns it to the struct t_lookup

void trig_table_cos(w_data *data)
{
    int i;
    float *cos_tab;

    cos_tab = (float *)malloc(sizeof(float) * DEGREE_MAX);
    if (!cos_tab)
        return;

    i = 0;
    while (i < DEGREE_MAX)
    {
        cos_tab[i] = (float)(cos(i * PI / 180) * SCALE_TRIG);
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

void init_lookup(w_data *data)
{
	data->lookup = (t_lookup *)malloc(sizeof(t_lookup));
	if (!data->lookup)
		return;
	trig_table_sin(data);
	trig_table_cos(data);
}
