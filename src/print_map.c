//
// Created by tom billard on 13/12/2016.
//

#include <turmite.h>

void    print_map(t_env *env)
{
    int x = 0;
    int y = 0;

    while (y < env->max.y)
    {
        while (x < env->max.x)
        {
            int hit = 0;

            env->ant = env->first;
            while (env->ant)
            {
                if (x == env->ant->pos.x && y == env->ant->pos.y)
                {
                    hit = 1;
                    break ;
                }
                env->ant = env->ant->next;
            }
            if (hit == 1)
                ft_putchar('#');
            else
                ft_putnbr(env->map[y][x]->color);
            ft_putchar(' ');
            x++;
        }
        ft_putendl("");
        x = 0;
        y++;
    }
    env->ant = env->first;
}