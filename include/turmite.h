/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turmite.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 15:40:53 by tbillard          #+#    #+#             */
/*   Updated: 2016/06/19 20:13:54 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TURMITE_H
# define TURMITE_H

# include "../libft/libft.h"
#include <errno.h>
#include <stdbool.h>

#include <SDL.h>

#define WIN_X   1075
#define WIN_Y   1075

# define L_C(X, x1, x2, y1, y2) ((int)(((X - x1) * (y2 - y1)) / (x2 - x1)) + y1)
# define L_CF(X, x1, x2, y1, y2) ((float)(((float)((X - x1) * (y2 - y1))) / (float)(x2 - x1)) + y1)
#define WHITE   (Uint32) ((255 << 16) + (255 << 8) + 255)
#define RED     (Uint32) ((255 << 16) + (0 << 8) + 0)
#define GREEN   (Uint32) ((0 << 16) + (255 << 8) + 0)
#define BLUE    (Uint32) ((0 << 16) + (0 << 8) + 255)
#define PURPUL  (Uint32) ((108 << 16) + (2 << 8) + 119)
#define ORANGE  (Uint32) ((250 << 16) + (164 << 8) + 1)
#define MAGENTA (Uint32) ((255 << 16) + (0 << 8) + 255)
#define CYAN    (Uint32) ((0 << 16) + (255 << 8) + 255)
#define BROWN   (Uint32) ((139 << 16) + (69 << 8) + 19)

#define STATE_0	0
#define STATE_1	GREEN
#define STATE_2	BLUE
#define STATE_3	RED
#define STATE_4	PURPUL
#define STATE_5	ORANGE
#define STATE_6	MAGENTA
#define STATE_7	CYAN
#define STATE_8	BROWN
#define STATE_9	WHITE

typedef struct                  s_window
{
    SDL_Window              *window;
    SDL_Event               event;
    SDL_Renderer            *renderer;
    SDL_Texture             *image;
    Uint32                  *img_ptr;
    int                     is_init;
}                           t_window;

typedef struct		s_coor
{
	int				x;
	int 			y;
}					t_coor;

typedef struct		s_ant
{
    t_coor			pos;
    int             direction;
    struct s_ant    *next;
}					t_ant;

typedef struct		s_color
{
    Uint32          color;
    char            dir;
    struct s_color  *next;
}					t_color;


typedef struct		s_env
{
    int 			update;
    t_color         *first_color;
    t_color			***map;
    t_coor          max;
    t_ant			*ant;
    t_ant			*first;
}					t_env;

//void                edit_menu(t_env *env, t_window *w);
//void    			get_arg(t_env *env, char **argv, int i);

void                init_window(t_window *window);
int                 render(t_env *env);
int					ft_error(char *str);
void                turmite_comput(t_env *env);
void    print_map(t_env *env);

#endif
