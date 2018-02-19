//
// Created by tom billard on 16/12/2016.
//

#include <fcntl.h>
#include "turmite.h"

static void key_handler(SDL_Event event, t_env *env, t_window *w, int *s)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            exit(EXIT_SUCCESS);
        if (event.key.keysym.sym == SDLK_q)
            (*s) = 1;
    }
}

typedef float offf_t;


static void draw_pixel(int x, int y, Uint32 color, t_window *w)
{
    if (y > WIN_Y || x > WIN_X || x < 0 || y < 0)
    {
        ft_putstr("x: ");
        ft_putnbr(x);
        ft_putstr(", y:");
        ft_putnbr(y);
        ft_putendl(" pixel over/under flow!!!!!");
        return ;
    }
    w->img_ptr[WIN_X * y + x] = color;
}

void drawcircle(int x0, int y0, int radius, Uint32 color, t_window *w)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        draw_pixel(x0 + x, y0 + y, color, w);
        draw_pixel(x0 + y, y0 + x, color, w);
        draw_pixel(x0 - y, y0 + x, color, w);
        draw_pixel(x0 - x, y0 + y, color, w);
        draw_pixel(x0 - x, y0 - y, color, w);
        draw_pixel(x0 - y, y0 - x, color, w);
        draw_pixel(x0 + y, y0 - x, color, w);
        draw_pixel(x0 + x, y0 - y, color, w);

        y += 1;
        err += 1 + 2*y;
        if (2*(err-x) + 1 > 0)
        {
            x -= 1;
            err += 1 - 2*x;
        }
    }
}

static void		draw_pix(t_window *w, offf_t off, offf_t x, offf_t y, Uint32 color)
{
    offf_t x1 = -(off / 2);
    offf_t y1 = -(off / 2);

    while (y1 < off  / 2 + 1)
    {
        while (x1 < off / 2 + 1)
        {
            draw_pixel((int)(x + x1), (int)(y + y1), color, w);
            x1++;
        }
        x1 = -(off/2);
        y1++;
    }
}

static void		render_map(t_window *w, t_env *env)
{
    float 	off = L_CF(1, 0, env->mod, 0, WIN_Y - 10 - (WIN_Y / 8));
    offf_t 	x;
    offf_t 	y;
    offf_t 	x1 = 0;
    offf_t		y1 = 0;
    offf_t     fact = 0;
    offf_t     x0;

    x0 = (off / 2) + ((WIN_X - (off * env->mod)) / 2);
    x = x0;
    y = (off / 2) + (WIN_Y / 8) + 5;
    while (y1 < env->line)
    {
        while (x1 < env->mod)
        {
            if (env->tab[(int)y1][(int)x1] == 0)
                draw_pix(w, off, x, y, STATE_0);
            else if (env->tab[(int)y1][(int)x1] == 1)
                draw_pix(w, off, x, y, STATE_1);
            else if (env->tab[(int)y1][(int)x1] == 2)
                draw_pix(w, off, x, y, STATE_2);
            else if (env->tab[(int)y1][(int)x1] == 3)
                draw_pix(w, off, x, y, STATE_3);
            else if (env->tab[(int)y1][(int)x1] == 4)
                draw_pix(w, off, x, y, STATE_4);
            else if (env->tab[(int)y1][(int)x1] == 5)
                draw_pix(w, off, x, y, STATE_5);
            else if (env->tab[(int)y1][(int)x1] == 6)
                draw_pix(w, off, x, y, STATE_6);
            else if (env->tab[(int)y1][(int)x1] == 7)
                draw_pix(w, off, x, y, STATE_7);
            else if (env->tab[(int)y1][(int)x1] == 8)
                draw_pix(w, off, x, y, STATE_8);
            else if (env->tab[(int)y1][(int)x1] >= 9)
                draw_pix(w, off, x, y, STATE_9);
            else
                draw_pix(w, off, x, y, 0);
            x +=off;
            x1++;
            if (fact != 0)
                x1 += pow(2, fact);
        }
        y += off;
        x = x0;//(off / 2) + 5;
        x1 = 0;
        y1++;
        if (fact != 0)
            y1 += pow(2, fact);
    }
}


static void     get_mouse_coor(int x, int y, t_env *env, int *state)
{
    int marx;
    int mary;
    float       x2;
    float       y2;
    float 	    rad = L_CF(1, 0, env->mod, 0, WIN_Y - 10 - (WIN_Y / 8));

    marx = (int)(WIN_X - rad * env->mod) / 2;
    mary = (int)(WIN_Y - rad * env->mod);
    x2 = (float)(x - marx) / rad;
    y2 = (float)(y - mary) / rad;
    if (x2 < 0 || y2 < 0 || x2 > env->mod || y2 > env->mod)
        ft_putendl("error mouse");
    else
        env->tab[(int) y2][(int) x2] = *state;

}

static void     save_map(t_env *env)
{
    int i = 0;
    char str[16];
    int fd = 0;
    int j = 0;
    while (i < 255)
    {
        sprintf(str, "./map_saved_%d", i);
        if ((fd = open(str, O_RDWR | O_CREAT | O_EXCL)) > 0)
            break ;
        i++;
    }
    if (i == 255)
        return;
    ft_putstr_fd(env->b, fd);
    ft_putchar_fd('/', fd);
    ft_putendl_fd(env->s, fd);
    i = 0;
    while (i < env->mod)
    {
        while (j < env->mod)
        {
            ft_putchar_fd(' ', fd);
            ft_putchar_fd((char)(env->tab[i][j] + 48), fd);
            j++;
        }
        ft_putchar_fd('\n', fd);
        j = 0;
        i++;
    }
    close(fd);
    usleep(100000);
}

static void      get_input(t_env *env, int *state, int x, int y)
{
    float rad = WIN_Y / 64;
    int   radius = WIN_Y / 32;

    if (x >= (WIN_X / 18) - (rad / 2) && x <= (WIN_X / 18) + (rad / 2) && y >=  (WIN_Y / 32) - (rad / 2) && y <=  (WIN_Y / 32) + (rad / 2))
        *state = 0;
    else if (x >= (WIN_X / 18) - (rad / 2) && x <= (WIN_X / 18) + (rad / 2) && y >= ((WIN_Y / 32) + (WIN_Y / 32)) - (rad / 2) && y <= ((WIN_Y / 32) + (WIN_Y / 32)) + (rad / 2))
        *state = 1;


    if (x >= (WIN_X / 2) - (radius) && x <= (WIN_X / 2) + (radius) && y >=  (WIN_Y / 16) - (radius) && y <=  (WIN_Y / 16) + (radius))
        save_map(env);
}

static int      mouse_hit(t_env *env, int *state)
{
    int x;
    int y;

    x = 0;
    y = 0;
    if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        if (y > WIN_Y / 8)
            get_mouse_coor(x, y, env, state);
        else
            get_input(env, state, x, y);
        //usleep(5000);
    }
    return (0);
}

static void draw_menu(t_env *env, t_window *w)
{
    int i = 0;
    int j = WIN_Y / 8 ;
    offf_t rad = WIN_Y / 64;
    offf_t x;
    int     radius = WIN_Y / 32;

    while (i < WIN_X)
        draw_pixel(i++, j, WHITE, w);
    draw_pix(w, rad, WIN_X / 18, WIN_Y / 32, WHITE);
    draw_pix(w, rad, WIN_X / 18, WIN_Y / 32 + WIN_Y / 32, STATE_1);
    draw_pix(w, rad, WIN_X / 18 + WIN_X / 18, WIN_Y / 32, STATE_2);
    draw_pix(w, rad, WIN_X / 18 + WIN_X / 18, WIN_Y / 32 + WIN_Y / 32, STATE_3);
    while (radius > 0)
        drawcircle(WIN_X / 2, WIN_Y / 16, radius--, RED, w);
}

void edit_menu(t_env *env, t_window *w)
{
    int s = 0;
    int state = 1;

    bzero(w->img_ptr, sizeof(Uint32) * WIN_Y * WIN_X);
    while (s == 0)
    {
        while (SDL_PollEvent(&w->event))
            key_handler(w->event, env, w, &s);
        mouse_hit(env, &state);
        draw_menu(env, w);
        render_map(w, env);
        SDL_UpdateTexture(w->image, NULL, w->img_ptr, WIN_X * sizeof(Uint32));
        SDL_RenderCopy(w->renderer, w->image, NULL, NULL);
        SDL_RenderPresent(w->renderer);
        bzero(w->img_ptr, sizeof(Uint32) * WIN_Y * WIN_X);
    }
    env->ly = 0;
}
