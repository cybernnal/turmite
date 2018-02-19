/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:46:15 by tbillard          #+#    #+#             */
/*   Updated: 2016/06/19 20:28:40 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "turmite.h"
#include <sys/time.h>

static  t_env        *sig(void)
{
    static t_env env;

    return (&env);
}

static void     get_pos(t_env *env, char *str)
{
    char **tab;

    tab = ft_strsplit(str, ',');
    if (!tab)
        ft_error("arg split error");
    if (!env->first)
    {
        env->ant = (t_ant*)ft_memalloc(sizeof(t_ant));
        env->ant->next = NULL;
        env->first = env->ant;
    }
    else
    {
        env->ant->next = (t_ant*)ft_memalloc(sizeof(t_ant));
        env->ant = env->ant->next;
        env->ant->next = NULL;
    }
    if (tab[0])
        env->ant->pos.x = ft_atoi(tab[0]);
    if (tab[1])
        env->ant->pos.y = ft_atoi(tab[1]);
    env->ant->direction = 0;

    ft_freetab(&tab);
}

static Uint32   random_color()
{
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;

    printf("r: %d, g: %d g: %d\n", r, g, b);
    r = (r + 255) / 2;
    g = (g + 255) / 2;
    b = (b + 255) / 2;
    return ((Uint32)((r << 16) + (g << 8) + b));
}


static void     get_rule(t_env *env, const char *str)
{
    t_color *lst;
    t_color *first;
    int i = 0;

    lst = (t_color*)ft_memalloc(sizeof(t_color));
    first = lst;
    while (str[i])
    {
        if (str[i] == 'L' || str[i] == 'l')
            lst->dir = 0;
        else if (str[i] == 'R' || str[i] == 'r')
            lst->dir = 1;
        else
            ft_error("bad rules's string");
        if (i == 0)
            lst->color = 0;
        else
            lst->color = random_color();
        i++;
        if (str[i])
        {
            lst->next = (t_color*)ft_memalloc(sizeof(t_color));
            lst = lst->next;
        }
    }
    lst->next = first;
    env->first_color = first;
}

static void     get_rule_col(t_env *env, const char *str)
{
    t_color *lst;
    t_color *first;
    int i = 0;
    char **tab;
    
    tab = ft_strsplit(str, ',');
    lst = (t_color*)ft_memalloc(sizeof(t_color));
    first = lst;
    while (tab[i])
    {
        if (tab[i][0] == 'L' || tab[i][0] == 'l')
            lst->dir = 0;
        else if (tab[i][0] == 'R' || tab[i][0] == 'r')
            lst->dir = 1;
        else
            ft_error("bad rules's string");
        i++;
        if (tab[i])
            lst->color = (Uint32)ft_atoi(tab[i]);
        i++;
        printf("dir: %d, col: %u\n", lst->dir, lst->color);
        if (tab[i])
        {
            lst->next = (t_color*)ft_memalloc(sizeof(t_color));
            lst = lst->next;
        }
    }
    lst->next = first;
    env->first_color = first;
}

static void     get_arg(int argc, char **argv, t_env *env)
{
    int i = 1;

    if (argc < 1)
        ft_error("not enoght arg");
    while (argv[i])
    {
        if (!ft_strcmp("-x", argv[i]) && argv[i + 1])
            env->max.x = ft_atoi(argv[++i]);
        else if (!ft_strcmp("-y", argv[i]) && argv[i + 1])
            env->max.y = ft_atoi(argv[++i]);
        else if (!ft_strcmp("-s", argv[i]) && argv[i + 1])
            get_pos(env, argv[++i]);
        else if (!ft_strcmp("-u", argv[i]) && argv[i + 1])
            env->update = ft_atoi(argv[++i]);
        else if (!ft_strcmp("-r", argv[i]) && argv[i + 1])
            get_rule(env, argv[++i]);
        else if (!ft_strcmp("-R", argv[i]) && argv[i + 1])
            get_rule_col(env, argv[++i]);

        i++;
    }
    if (env->update < 1)
    {
        ft_putendl_fd("update/frame error, set to 1", 2);
        env->update = 1;
    }
    if (env->max.x < 2 || env->max.y < 2)
        ft_error("bad size");

    env->ant = env->first;
    while (env->ant)
    {
        if (env->ant->pos.x < 0 || env->ant->pos.x > env->max.x  || env->ant->pos.y < 0 || env->ant->pos.y > env->max.y)
            ft_error("bad start point");
        env->ant = env->ant->next;
    }
    env->ant = env->first;

}

static void prep_map(t_env *env)
{
    int y = 0;
    int x = 0;

    env->map = (t_color ***)ft_memalloc(sizeof(Uint32**) * env->max.y + 1);
    while (y < env->max.y)
    {
        env->map[y] = (t_color**)ft_memalloc(sizeof(t_color*) * env->max.x + 1);
        while (x < env->max.x)
        {
            env->map[y][x] = env->first_color;
            x++;
        }
        x = 0;
        y++;
    }
}

int		main(int argc, char  **argv)
{
	t_env	*env;
    int  i = 1;

    srand((unsigned int)time(NULL));
    env = sig();
    ft_bzero(env, sizeof(t_env));
    get_arg(argc, argv, env);
    prep_map(env);
    while (env)
    {
        render(env);
        turmite_comput(env);
    }
    return (0);
}
