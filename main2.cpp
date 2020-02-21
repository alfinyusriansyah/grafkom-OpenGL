#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<dos.h>
int main()
{
      int count, graphics_driver = DETECT, graphics_mode;
      int dx, dy, x0, y0, x1, y1;
      int x_axis_minimum, x_axis_maximum, y_axis_minimum, y_axis_maximum;
      int t_x0, t_x1, t_y0, t_y1, delay_time;
      float tmin, tmax, p[4], q[4], t;
      initgraph(&graphics_driver, &graphics_mode, "c:\\turboc3\\bgi");
      printf("\nEnter X - axis line coordinates:\n");
      printf("\nEnter the value of x0:\t");
      scanf("%d", &x0);
      printf("\nEnter the value of x1:\t");
      scanf("%d", &x1);
      printf("\nEnter Y - axis line coordinates:\n");
      printf("\nEnter the value of y0:\t");
      scanf("%d", &y0);
      printf("\nEnter the value of y1:\t");
      scanf("%d", &y1);
      printf("\nEnter delay time:\t");
      scanf("%d", &delay_time);
      printf("\nEnter Minimum and Maximum Values for X-axis and Y-axis\n");
      printf("X - Axis Minimum Value:\t");
      scanf("%d", &x_axis_minimum);
      printf("X - Axis Maximum Value:\t");
      scanf("%d", &x_axis_maximum);
      printf("Y - Axis Minimum Value:\t");
      scanf("%d", &y_axis_minimum);
      printf("Y - Axis Maximum Value:\t");
      scanf("%d", &y_axis_maximum);
      rectangle(x_axis_minimum, y_axis_minimum, x_axis_maximum, y_axis_maximum);
      dx = x1 - x0;
      dy = y1 - y0;
      p[0] = -dx;
      p[1] = dx;
      p[2] = -dy;
      p[3] = dy;
      q[0] = x0 - x_axis_minimum;
      q[1] = x_axis_maximum - x0;
      q[2] = y0 - y_axis_minimum;
      q[3] = y_axis_maximum - y0;
      for(count = 0; count < 4; count++)
      {
            if(p[count] == 0)
            {
                  printf("\nLine is parallel\n");
                  if(q[count] >= 0)
                  {
                        if(count < 2)
                        {
                              if(y0 < y_axis_minimum)
                              {
                                    y0 = y_axis_minimum;
                              } 
                              if(y1 > y_axis_maximum)
                              {
                                    y1 = y_axis_maximum;
                              } 
                              line(x0, y0, x1, y1);
                        }
                        if(count > 1)
                        {
                              if(x0 < x_axis_minimum)
                              {
                                    x0 = x_axis_minimum;
                              }
                              if(x1 > x_axis_maximum)
                              {
                                    x1 = x_axis_maximum;
                              } 
                              line(x0, y0, x1, y1);
                        }
                  }
            }
      }
      tmin = 0;
      tmax = 1;
      for(count = 0; count < 4; count++)
      {
            t = q[count] / p[count]; 
            if(p[count] < 0)
            {
                  if(tmin <= t)
                  {
                        tmin = t;
                  }
            }
            else
            {
                  if(tmax > t)
                  {
                        tmax = t;
                  }
            }
      }
      if(tmin < tmax)
      {
            t_x0 = x0 + tmin * p[1];
            t_x1 = x0 + tmax * p[1];
            t_y0 = y0 + tmin * p[3];
            t_y1 = y0 + tmax * p[3];
            line(t_x0, t_y0, t_x1, t_y1);
      }
      delay(delay_time);
      closegraph();   
}
