#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_function
{
	void *(*w)(int x, char a);
    void *(*c)(int x, char a);
    void *(*r)(int x, char a);

}		t_fun;


typedef struct main_s{
	t_fun current;

}	t_s;


#endif
