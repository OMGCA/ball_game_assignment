#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <graphics_lib.h>
#include "bendy.h"


int x_pos[5] = {92, 92, 70, 78, 94};
int y_pos[5] = {307, 345, 341, 376, 376};
int head_radius = 17;
int upper_body_radius = 22;
int body_width = 44, body_height = 37;
int leg_width = 13, leg_height = 24;

void draw_bendy ( void )
{else if ( action.equals(circle))
        {
            for ( int i = 1; i <= 360; i++)
            {
                Double pixleOrAngle = Double.parseDouble(value);
                this.move(pixleOrAngle);
                this.turn(1);
            }
        }
    /*Head*/
    filled_circle(x_pos[0], y_pos[0], head_radius, BLACK);
    /*Body*/
    filled_circle(x_pos[1], y_pos[1], upper_body_radius, BLACK);
    filled_rectangle(x_pos[2], y_pos[2], x_pos[2] + body_width, y_pos[2] + body_height, BLACK);
    /*Leg*/
    filled_rectangle(x_pos[3], y_pos[3], x_pos[3] + leg_width, y_pos[3] + leg_height, BLACK);
    filled_rectangle(x_pos[4], y_pos[4], x_pos[4] + leg_width, y_pos[4] + leg_height, BLACK);
}

int cover_bendy ( int x_pos[], int y_pos[],
                 int head_radius, int upper_radius, int body_width, int body_height,
                 int leg_width, int leg_height, int color )
{
    int old_x[5], old_y[5];
    int count;
    for ( count = 0; count < 5; count++ )
    {
        old_x[count] = x_pos[count];
        old_y[count] = y_pos[count];
    }
    /*Head*/
    filled_circle(old_x[0], old_y[0], head_radius, LIGHTBLUE);
    /*Body*/
    filled_circle(old_x[1], old_y[1], upper_body_radius, LIGHTBLUE);
    filled_rectangle(old_x[2], old_y[2], old_x[2] + body_width, old_y[2] + body_height, LIGHTBLUE);
    /*Leg*/
    filled_rectangle(old_x[3], old_y[3], old_x[3] + leg_width, old_y[3] + leg_height, LIGHTBLUE);
    filled_rectangle(old_x[4], old_y[4], old_x[4] + leg_width, old_y[4] + leg_height, LIGHTBLUE);
}

int draw_new_bendy ( int x_pos[], int y_pos[],
                 int head_radius, int upper_radius, int body_width, int body_height,
                 int leg_width, int leg_height, int color)
{
    /*Head*/
    filled_circle(x_pos[0], y_pos[0], head_radius, color);
    /*Body*/
    filled_circle(x_pos[1], y_pos[1], upper_radius, color);
    filled_rectangle(x_pos[2], y_pos[2], x_pos[2] + body_width, y_pos[2] + body_height, color);
    /*Leg*/
    filled_rectangle(x_pos[3], y_pos[3], x_pos[3] + leg_width, y_pos[3] + leg_height, color);
    filled_rectangle(x_pos[4], y_pos[4], x_pos[4] + leg_width, y_pos[4] + leg_height, color);
}

int copy_array ( int new_array[], int old_array[], int total )
{
    int count = 0;
    for ( count = 0; count < total; count++ )
    {
        new_array[count] = old_array[count];
    }
}

void generate_obstacle ( int *x, int *y )
{
    *x = rand() %251+250;
    *y = rand() %151+200;
    filled_rectangle ( *x, *y, *x+30, *y+30, BROWN);
}

/*This function is modified from Lab 3 Lab Script*/
int InputCheck( int scanf_validation )
{
    if (scanf_validation < 1)
    {
        fflush(stdin);
        printf("Please input an number.:");
    }
    return scanf_validation;
}

void score_section ( int *label_start )
{
    *label_start = 200;
    int thickness = 6;

    setcolor(YELLOW);
    line(*label_start, 395, *label_start, 405, thickness);

    line(*label_start + 100, 395, *label_start + 100, 405, thickness);
    line(*label_start + 405, 395, *label_start + 405, 405, thickness); //10 pts

    line(*label_start + 185, 395, *label_start + 185, 405, thickness);
    line(*label_start + 305, 395, *label_start + 305, 405, thickness); //20 pts

    line(*label_start + 220, 395, *label_start + 220, 405, thickness); //30 pts

    int count = 0;

    setcolor(BLACK);
    initfont();
    outtextxy( *label_start + 50, 380, "10");
    outtextxy( *label_start + 145, 380, "20");
    outtextxy( *label_start + 195, 380, "30");
    outtextxy( *label_start + 265, 380, "20");
    outtextxy( *label_start + 355, 380, "10");

}

void generate_wind (double *wind_speed, double *wind_direction, double *wind_angle)
{
    *wind_angle = rand()%225+0;
    *wind_direction = *wind_angle / 180 * PI;

    *wind_speed = rand()%19+5;
}

void welcome_msg (void)
{
    printf("Welcome to Bendy Theft Ball I\n");
    Sleep(1200);
    printf("After the welcome message, you are able to adjust Bendy's position.\n\n");
    Sleep(1200);
    printf("Press <-- or --> to move the Bendy\n\n");
    printf("Then press ENTER to continue.\n\n");
    Sleep(1300);
    printf("After that, you need to set the initial velocity and angle(0бу~90бу) of a ball in Bendy's hand.\n\n");
    Sleep(1200);
    printf("Wind will affect the ball's motion, information will be given.\n\n");
    Sleep(1200);
    printf("Score will be given by which slot the ball is in multiplied by the difficulty level.\n\n");
    Sleep(1100);
    printf("Hitting the left side of any block will cause score invaild.\n\n");
    printf("Top or bottom of the block is accessible, 5 points will be awarded if hitting the inner right side of the block.\n\n");
    Sleep(1500);
    printf("You have 1 minute after the intro.\n\n");
    printf("10 points penalty will be awarded if running out of time.\n\n");
    Sleep(2000);
    printf("Get ready.\n");
    Sleep(2000);
    printf("Countdown will start after the difficulty level is selected.\n\n");
}

