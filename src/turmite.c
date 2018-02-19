//
// Created by tom billard on 16/02/2018.
//

#include <turmite.h>

void turmite_comput(t_env *env)
{
    int u = env->update;

    while (u > 0)
    {
        env->ant = env->first;
        while (env->ant)
        {
            if (env->map[env->ant->pos.y][env->ant->pos.x]->dir == 0)
                    env->ant->direction = (env->ant->direction + 3) % 4;
            else
                env->ant->direction = (env->ant->direction + 1) % 4;
            env->map[env->ant->pos.y][env->ant->pos.x] = env->map[env->ant->pos.y][env->ant->pos.x]->next;
            switch (env->ant->direction)
            {

                case 0:
                {
                    env->ant->pos.x = (env->ant->pos.x + (env->max.x - 1)) % env->max.x;
                    break;
                }
                case 1:
                {
                    env->ant->pos.y = (env->ant->pos.y + (env->max.y - 1)) % env->max.y;
                    break;
                }
                case 2:
                {
                    env->ant->pos.x = (env->ant->pos.x + 1) % env->max.x;
                    break;
                }
                case 3:
                {
                    env->ant->pos.y = (env->ant->pos.y + 1) % env->max.y;
                    break;
                }
                default:
                    ft_error("defaillance general, aucune direction a prendre {turmite.c}");

            }

//        env->map[env->ant->pos.y][env->ant->pos.x] = RED; // TODO fix it can't print the color of ant {ant color}
            env->ant = env->ant->next;
        }
        u--;
    }
    env->ant = env->first;
}