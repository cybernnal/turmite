# turmite
need a readme


gcc src/error.c src/init.c src/main.c src/print_map.c src/render.c src/turmite.c  libft/*.c -I./include/ -I./libft \`pkg-config --cflags sdl2\` \`pkg-config --libs sdl2\` -o turmite
