#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <conio.h>
#endif
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#ifdef __APPLE__
#endif

void draw_bendy( void );

int draw_new_bendy ( int x_pos[], int y_pos[],
                 int head_radius, int upper_radius, int body_width, int body_height,
                 int leg_width, int leg_height, int color);

int cover_bendy ( int x_pos[], int y_pos[],
                 int head_radius, int upper_radius, int body_width, int body_height,
                 int leg_width, int leg_height, int color );

int copy_array ( int new_array[], int old_array[], int total );

void generate_obstacle ( int *x, int *y );

int InputCheck( int scanf_validation );

void score_section ( int *label_start );

void generate_wind (double *wind_speed, double *wind_direction, double *wind_angle);

void welcome_msg (void);
