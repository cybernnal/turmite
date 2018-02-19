#include <time.h>
#include "turmite.h"

static void key_handler(SDL_Event event, t_env *env, t_window *w)
{
	if (event.type == SDL_KEYDOWN)
	{
      	if (event.key.keysym.sym == SDLK_ESCAPE)
			exit(EXIT_SUCCESS);
	}
}

typedef float offf_t;

static void draw_pixel(int x, int y, Uint32 color, t_window *w)
{
//    if (y > WIN_Y || x > WIN_X || x < 0 || y < 0)
//    {
//        ft_putstr("x: ");
//        ft_putnbr(x);
//        ft_putstr(", y:");
//        ft_putnbr(y);
//        ft_putendl(" pixel over/under flow!!!!!");
//        return ;
//    }
        w->img_ptr[WIN_X * y + x] = color;
}

static void		draw_pix2(t_window *w, offf_t off, offf_t x, offf_t y, Uint32 color)
{
    offf_t x1 = 0;
    offf_t y1 = 0;

    while (y1 < off)
    {
        while (x1 < off)
        {
            draw_pixel((int) ((x * off) + x1), (int) ((y * off) + y1), color, w);
            x1++;
        }
        x1 = 0;
        y1++;
    }
}


static void render_map(t_window *w, t_env *env)
{
    int x = 0;
    int y = 0;

    while (y < env->max.y)
    {
        while (x < env->max.x)
        {
            if (env->map[y][x])
                draw_pix2(w, (((WIN_X) / (env->max.x))), x, y, env->map[y][x]->color);
            x++;
        }
        x = 0;
        y++;
    }
    env->ant = env->first;
}

int        render(t_env * env)
{
	static t_window w;

	if (!w.is_init)
	{
		init_window(&w);
		w.is_init = 1;
	}
    bzero(w.img_ptr, sizeof(Uint32) * WIN_Y * WIN_X);
 	while (SDL_PollEvent(&w.event))
		key_handler(w.event, env, &w);
	render_map(&w, env);
	SDL_UpdateTexture(w.image, NULL, w.img_ptr, WIN_X * sizeof(Uint32));
	SDL_RenderCopy(w.renderer, w.image, NULL, NULL);
	SDL_RenderPresent(w.renderer);
    return (1);
}
