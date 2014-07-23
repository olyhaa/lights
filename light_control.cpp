//light_control.cpp

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"
int cport_nr = 5;
int bdrate=19200; 

char convert(int num);
void send_color(int r, int g, int b);
void slow_rainbow();
void fast_rainbow();
void seizure();
void po_po();


void send_color(int r, int g, int b)
{
   //unsigned char buf[4096];
   //send string to controller
    RS232_SendByte(cport_nr, 'c');
    RS232_SendByte(cport_nr, convert(r/16));
    RS232_SendByte(cport_nr, convert(r%16));
    RS232_SendByte(cport_nr, convert(g/16));
    RS232_SendByte(cport_nr, convert(g%16));
    RS232_SendByte(cport_nr, convert(b/16));
    RS232_SendByte(cport_nr, convert(b%16));


  #ifdef _WIN32
     Sleep(25);
  #else
      usleep(50000);  /* sleep for 100 milliSeconds */
  #endif
  
  
}
char convert(int num){
    if(num < 10)
      return (char)(((int)'0')+num);
    switch(num){
      case 10: return 'a';
      case 11: return 'b';
      case 12: return 'c';
      case 13: return 'd';
      case 14: return 'e';
      case 15: return 'f';
    }
    return '0';
}
void slow_rainbow(){
  if(RS232_OpenComport(cport_nr, bdrate))
       printf("Can not open comport\n");

    int r = 255;
    int g = 0;
    int b = 0;


        for(; g < 255; g++)
           send_color(r,g,b);
        for(; r > 0; r--)
          send_color(r,g,b);
        for(; b < 255; b++)
          send_color(r,g,b);
        for(; g > 0; g--)
          send_color(r,g,b);
        for(; r < 255; r++)
          send_color(r,g,b);
        for(; b > 0; b--)
          send_color(r,g,b);

    RS232_CloseComport(cport_nr);
}
void fast_rainbow(){
  if(RS232_OpenComport(cport_nr, bdrate))
       printf("Can not open comport\n");

    int r = 250;
    int g = 0;
    int b = 0;


        for(; g < 250; g+=10)
           send_color(r,g,b);
        for(; r > 0; r-=10)
          send_color(r,g,b);
        for(; b < 250; b+=10)
          send_color(r,g,b);
        for(; g > 0; g-=10)
          send_color(r,g,b);
        for(; r < 250; r+=10)
          send_color(r,g,b);
        for(; b > 0; b-=10)
          send_color(r,g,b);

  
    RS232_CloseComport(cport_nr);
}

void seizure(){
   if(RS232_OpenComport(cport_nr, bdrate))
       printf("Can not open comport\n");
  time_t start = time(NULL);

  while(1){
     int r = rand()%256;
     int g = rand()%256;
     int b = rand()%256;
     send_color(r,g,b);
     send_color(0,0,0);
     if(difftime(time(NULL), start) >= 10)
       break;
  }

  RS232_CloseComport(cport_nr);
}
void po_po(){

    if(RS232_OpenComport(cport_nr, bdrate))
       printf("Can not open comport\n");
     int num;
    while(1){
        send_color(255, 0, 0);
        send_color(0, 0, 255);
    }


    RS232_CloseComport(cport_nr);
}
void fade(int r1, int g1, int b1, int r2, int g2, int b2){
  if(RS232_OpenComport(cport_nr, bdrate))
       printf("Can not open comport\n");
  int r = r1;
  int g = g1;
  int b = b1;

  //fade reds
  if(r1 < r2){
    for(; r < r2-5; r+= 5)
      send_color(r, g, b);
  }
  else
  {
    for(; r > r2+5; r -= 5)
      send_color(r, g, b);
  }
  r = r2;

  //fade greens
  if(g1 < g2){
    for(; g < g2-5; g+= 5)
      send_color(r, g, b);
  }
  else
  {
    for(; g > g2+5; g -= 5)
      send_color(r, g, b);
  }
  g = g2;

  //fade blues
  if(b1 < b2){
    for(; b < b2-5; b+= 5)
      send_color(r, g, b);
  }
  else
  {
    for(; b > b2+5; b -= 5)
      send_color(r, g, b);
  }
  b = b2;

  send_color(r, g, b);

  RS232_CloseComport(cport_nr);
}
int main()
{
    int r1 = 0;
    int g1 = 0;
    int b1 = 0;
    srand(time(NULL));

    //seizure();
    //po_po();
    //while(1){
     //fast_rainbow();
    //}


    return 0;
}



