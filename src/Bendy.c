//=======================================================================================================================
// Copyright Information
//===================================================
// Copyright (c) T.Xia <tx584@york.ac.uk>
//===================================================
// Sound files in 'music' folder
// looping_radio_mix.wav is extracted from The Stanley Parable, Copyright (c) Galactic Cafe 2013 All rights reserved.
//===================================================
// MP_DM_COUNTDOWN_30_1.wav, score.wav and wind.wav are extracted or captured from Grand Theft Auto V
// Copyright (c) Rockstar Games Inc. 2015 All rights reserved.
//===================================================
//The 'Bendy' figure is inspired by Portal 2, Copyright (c) Valve Coporation 2010 All rights reserved.
//===================================================
//Partial codes and functions are modified from lab scripts, all are stated before the codes and fucntions.
//bendy.h and the functions are in the 'include' folder.
//=======================================================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <process.h>
#include <math.h>
#include <graphics_lib.h>
#include "bendy.h"


int a;
int total_score = 0;
double x_position, y_position;

/*Axis of obstacles*/
int x[5] = {0, 0, 0, 0, 0};
int y[5] = {0, 0, 0, 0, 0};

void obstacle_col ( void );

/*Countdown thread*/
void thread( void )
{
    for ( a=60; a>=-1; a-- )
    {
        if ( a==60 )
          PlaySound(TEXT("music\\looping_radio_mix.wav"),NULL,SND_ASYNC); //This sound file is extracted from The Stanley Parable.
        if ( a==30 )
        {
            PlaySound(TEXT("music\\MP_DM_COUNTDOWN_30_1.wav"),NULL,SND_ASYNC);//Extracted from Grand Theft Auto V.
            printf("\n30 seconds to go.\n");
        }
        else if ( a==0 )
        {
            printf("\n10 points penalty awarded.\n");
            total_score = total_score - 10;
        }
        Sleep(1000);
    }
    _endthread();
}


int main(void)
{
    srand((unsigned) time(NULL)); //call srand

    welcome_msg();
    int input_validation;

    /*Level*/
    int diff_level;
    printf("Input difficulty level(1~5): ");
    do
    {
        input_validation = scanf("%d", &diff_level);
        InputCheck(input_validation);
        if ((diff_level<=0) || (diff_level>5))
        {
            input_validation == 0;
        }
    }
    while ( (input_validation < 1) );

    int diff_loop;

    /*Background*/
    initwindow( 640, 480 );
    filled_rectangle(0, 0, 640, 480, 9);//Background
    filled_rectangle(0, 400, 640, 480, BROWN);//Ground
    update_display();

    int x_pos[5] = {92, 92, 70, 78, 94};
    int y_pos[5] = {307, 345, 341, 376, 376};
    int head_radius = 17;
    int upper_body_radius = 22;
    int body_width = 44, body_height = 37;
    int leg_width = 13, leg_height = 24;
    int count;

    /*Environmental Effect*/
    double wind_speed, wind_direction, wind_angle;
    generate_wind(&wind_speed, &wind_direction, &wind_angle);//wind_angle is for info for players, wind_direction is for further calculation.

    printf("Wind speed: %.0lf\n", wind_speed);
    if ( wind_angle == 0 )
        printf("Wind direction: ¡ú\n");
    else if ( (wind_angle < 90) && (wind_angle > 0) )
        printf("Wind direction : ¨J Angle: %.0lf\n", wind_angle);
    else if ( wind_angle == 90 )
        printf("Wind direction : ¡ü Angle: %.0lf\n", wind_angle);
    else if ( (wind_angle < 180) && (wind_angle > 90))
        printf("Wind direction : ¨I Angle: %.0lf\n", wind_angle);
    else if ( wind_angle == 180 )
        printf("Wind direction : ¡û Angle: %.0lf\n", wind_angle);
    else if ( (wind_angle <= 225) && (wind_angle > 180))
    {
        printf("Wind direction : ¨L Angle: %.0lf\n", wind_angle);
    }

    /*Draw the Bendy*/
    draw_bendy();

    /*Put obstacles onto the screen, the quantity is according to the difficulty level*/
    int ob_gen_counter;
    for ( ob_gen_counter = 0; ob_gen_counter < diff_level+diff_loop; ob_gen_counter++ )
    {
    generate_obstacle(&x[ob_gen_counter], &y[ob_gen_counter]);
    }

    /*Score Sections*/
    int start_label;
    score_section(&start_label);

    update_display();

    /*Start the countdown thread*/
    /*Multithreading Code, ref: http://wenku.baidu.com/link?url=5gJVpTijD3yah-RTZONnXJRyoaPU8LbyEbE3ke0WxvCBDLgf3qom9vZt1Uc7tzSxqINWpMKLwhjshp9ILpl5Oc--gmrQrVyBHc3_OaT4haW*/
    int flag = -1;
    flag = _beginthread(thread, 0, 1);
    if ( flag == -1 )
    {
          printf("Timer initialization failed.\n");
    }

    /*Old statistics to cover the old Bendy*/
    int old_x[5];
    int old_y[5];

    /*Control Commands*/
    int key_pressed = 0, enter = 13;

    while ( key_pressed != enter )
    {
        key_pressed = getch();
        if ( ( key_pressed == 0 ) || ( key_pressed == 224 ) )
        {
          key_pressed = getch();

          copy_array( old_x, x_pos, 5 );
          copy_array( old_y, y_pos, 5 );

          switch(key_pressed)
          {
          case 77:
                for ( count = 0; count < 5; count++ )
                {
                    x_pos[count] = x_pos[count] + 3;
                    cover_bendy(old_x, old_y, head_radius, upper_body_radius, body_width, body_height, leg_width, leg_height, BLACK);
                    draw_new_bendy(x_pos, y_pos, head_radius, upper_body_radius, body_width, body_height, leg_width, leg_height, BLACK);
                    score_section(&start_label);
                    update_display();
                }
                break;
          case 75:
                for ( count = 0; count < 5; count++ )
                {
                    x_pos[count] = x_pos[count] - 3;
                    cover_bendy(old_x, old_y, head_radius, upper_body_radius, body_width, body_height, leg_width, leg_height, BLACK);
                    draw_new_bendy(x_pos, y_pos, head_radius, upper_body_radius, body_width, body_height, leg_width, leg_height, BLACK);
                    score_section(&start_label);
                    update_display();
                }
                break;
          }
        }

    }

      double vel, vel_x, vel_y, time;
      double gravity;
      double angle;
      gravity = 9.81;

      /*Velocity & Angle*/
      printf("\nInput the velocity:");

      do
      {
        input_validation = scanf("%lf", &vel);
        InputCheck(input_validation);
      }
      while ( input_validation < 1 );

      printf("Input the angle:");

      do
      {
        input_validation = scanf("%lf", &angle);
        InputCheck(input_validation);
      }
      while ( input_validation < 1 );

      if ( ( angle < 0 ) || ( angle > 90 ))
      {
        do
        {
          fflush(stdin);
          printf("Sorry, the angle must be between 0¡ã and 90¡ã:");
          do
          {
            input_validation = scanf("%lf", &angle);
            InputCheck(input_validation);
          }
          while ( input_validation < 1 );
        }
        while ( ( angle < 0 ) || ( angle > 90 ) );
      }

      angle = angle / 180 * PI;
      vel_x = vel * cos(angle);
      vel_y = vel * sin(angle);
      x_position = x_pos[0]+head_radius;
      y_position = y_pos[0]+ (body_height / 2) + 5;
      vel_x = vel_x+cos(wind_direction) * wind_speed;
      if ( (wind_angle <=90) || (wind_angle>180) )
      {
          vel_y = vel_y+sin(wind_direction) * wind_speed;
      }
      else if ( (wind_angle >90) && (wind_angle<=180) )
      {
          vel_y = vel_y-sin(wind_direction) * wind_speed;
      }
      /*Calculation of Positions*/
      moveto((int)x_position, (int)y_position);
      setcolor(BLACK);

      /*This do-while loop is modified from Lab 3 LabScript*/
      do
      {
        filled_circle( x_position, y_position, 5, LIGHTBLUE );
        time = (x_position - x_pos[0]) / vel_x;
        y_position = (y_pos[0] - (vel_y * time) + (gravity * time * time)/2)+60;
        x_position++;
        y_position--;
        filled_circle( x_position, y_position, 5, BLACK );
        obstacle_col();
        draw_new_bendy(x_pos, y_pos, head_radius, upper_body_radius, body_width, body_height, leg_width, leg_height, BLACK);
        update_display();
      }
      while ( y_position < 400 );
      score_section(&start_label);
      update_display();

      PlaySound(TEXT("music\\score.wav"),NULL,SND_FILENAME|SND_ASYNC|1);//Extracted from Grand Theft Auto V.

      if ( ((x_position >= start_label) && (x_position <= start_label + 100)) || ((x_position >= start_label + 305) && (x_position <= start_label + 405)))
        total_score = total_score + 10 * diff_level;
      else if ( ((x_position > start_label + 100) && (x_position <= start_label + 185)) || ((x_position >=start_label + 220) && (x_position < start_label + 305)))
        total_score = total_score + 20 * diff_level;
      else if ( (x_position > start_label + 185) && (x_position < start_label + 220))
        total_score = total_score + 30 * diff_level;

      if ( (x_position == x[0]+30) && ((y_position > y[0]) || (y_position > y[0]+30)))
        total_score = total_score + 5 * diff_level;
      else if ( (x_position == x[0]) && ((y_position > y[0]) || (y_position > y[0]+30)))
      {
        total_score = 0;
      }

      printf("\nYour total points are %d\n\n", total_score);

      Sleep(1000);
      printf("Press any key to continue.\n\n");

      getch();

      closegraph();

      return 0;
}

/*Function to tell whether the ball hits any of the obstacle*/
void obstacle_col ( void )
{
    double old_y;
        if ((x_position+5 == x[0]) ||
            (x_position+5 == x[1]) ||
            (x_position+5 == x[2]) ||
            (x_position+5 == x[3]) ||
            (x_position+5 == x[4]))
        {
            if (((y_position >= y[0]) && (y_position <= y[0]+30)) ||
                ((y_position >= y[1]) && (y_position <= y[2]+30)) ||
                ((y_position >= y[2]) && (y_position <= y[3]+30)) ||
                ((y_position >= y[3]) && (y_position <= y[3]+30)) ||
                ((y_position >= y[4]) && (y_position <= y[4]+30)))
            {
                old_y = y_position;
                y_position = 400;
                do
                {
                filled_circle( x_position, old_y, 5, LIGHTBLUE );
                old_y++;
                filled_circle( x_position, old_y, 5, BLACK );
                }
                while(old_y+5 <= 400);
            }
        }
        else if ((x_position+5 == x[0]+30) ||
                 (x_position+5 == x[1]+30) ||
                 (x_position+5 == x[2]+30) ||
                 (x_position+5 == x[3]+30) ||
                 (x_position+5 == x[4]+30) )
        {
            if (((y_position >= y[0]) && (y_position <= y[0]+30)) ||
                ((y_position >= y[1]) && (y_position <= y[1]+30)) ||
                ((y_position >= y[2]) && (y_position <= y[2]+30)) ||
                ((y_position >= y[3]) && (y_position <= y[3]+30)) ||
                ((y_position >= y[4]) && (y_position <= y[4]+30)))
            {
                old_y = y_position;
                y_position = 400;
                do
                {
                filled_circle( x_position, old_y, 5, LIGHTBLUE );
                old_y++;
                filled_circle( x_position, old_y, 5, BLACK );
                }
                while(old_y+5 <= 400);
            }

        }
        else if ((y_position == y[0]) ||
                 (y_position == y[1]) ||
                 (y_position == y[2]) ||
                 (y_position == y[3]) ||
                 (y_position == y[4]))
        {
            if (((x_position+5 >= x[0]) && (x_position+5 <= x[0]+30))||
                ((x_position+5 >= x[1]) && (x_position+5 <= x[1]+30))||
                ((x_position+5 >= x[2]) && (x_position+5 <= x[2]+30))||
                ((x_position+5 >= x[3]) && (x_position+5 <= x[3]+30))||
                ((x_position+5 >= x[4]) && (x_position+5 <= x[4]+30)))
            {
                old_y = y_position;
                y_position = 400;
                do
                {
                filled_circle( x_position, old_y, 5, LIGHTBLUE );
                old_y++;
                filled_circle( x_position, old_y, 5, BLACK );
                }
                while(old_y+5 <= 400);
            }

        }
        else if ((y_position == y[0]+30)||
                 (y_position == y[1]+30)||
                 (y_position == y[2]+30)||
                 (y_position == y[3]+30)||
                 (y_position == y[4]+30))
        {
            if (((x_position+5 >= x[0]) && (x_position+5 <= x[0]+30))||
                ((x_position+5 >= x[1]) && (x_position+5 <= x[1]+30))||
                ((x_position+5 >= x[2]) && (x_position+5 <= x[2]+30))||
                ((x_position+5 >= x[3]) && (x_position+5 <= x[3]+30))||
                ((x_position+5 >= x[4]) && (x_position+5 <= x[4]+30)))
            {
                old_y = y_position;
                y_position = 400;
                do
                {
                filled_circle( x_position, old_y, 5, LIGHTBLUE );
                old_y++;
                filled_circle( x_position, old_y, 5, BLACK );
                }
                while(old_y+5 <= 400);
            }
        }
        else
            return 0;
}
