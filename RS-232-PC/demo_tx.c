
/**************************************************

file: demo_tx.c
purpose: simple demo that transmits characters to
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

compile with the command: gcc demo_tx.c rs232.c -Wall -Wextra -o2 -o test_tx

**************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"

#define BUF_ERROR         -1
#define STOP              10
#define NUMBER_COM        48
#define USE               0
#define RECEIVE_LENG      4096
#define CHECK_DATA        "FROMESP32"
#define USE_COPY          1


const char *COM[NUMBER_COM]={"\\\\.\\COM1",  "\\\\.\\COM2",  "\\\\.\\COM3",  "\\\\.\\COM4",
                            "\\\\.\\COM5",  "\\\\.\\COM6",  "\\\\.\\COM7",  "\\\\.\\COM8",
                            "\\\\.\\COM9",  "\\\\.\\COM10", "\\\\.\\COM11", "\\\\.\\COM12",
                            "\\\\.\\COM13", "\\\\.\\COM14", "\\\\.\\COM15", "\\\\.\\COM16",
                            "\\\\.\\COM17", "\\\\.\\COM18", "\\\\.\\COM19", "\\\\.\\COM20",
                            "\\\\.\\COM21", "\\\\.\\COM22", "\\\\.\\COM23", "\\\\.\\COM24",
                            "\\\\.\\COM25", "\\\\.\\COM26", "\\\\.\\COM27", "\\\\.\\COM28",
                            "\\\\.\\COM29", "\\\\.\\COM30", "\\\\.\\COM31", "\\\\.\\COM32",
                            "\\\\.\\COM33", "\\\\.\\COM34", "\\\\.\\COM35", "\\\\.\\COM36",
                            "\\\\.\\COM37", "\\\\.\\COM38", "\\\\.\\COM39", "\\\\.\\COM40",
                            "\\\\.\\COM41", "\\\\.\\COM42", "\\\\.\\COM43", "\\\\.\\COM44",
                            "\\\\.\\COM45", "\\\\.\\COM46", "\\\\.\\COM47", "\\\\.\\COM48"};


void task_receive(int *port,bool *checkInformation)
{
    int n;
    unsigned char buf[RECEIVE_LENG];
    n = RS232_PollComport(*port, buf, RECEIVE_LENG-1);
    if(n > 0)
    {
      buf[n] = 0;   /* always put a "null" at the end of a string! */

      for(int i=0; i < n; i++)
      {
        if(buf[i] < 32)  /* replace unreadable control-codes by dots */
        {
          buf[i] = '.';
        }
      }

      //printf("received %i bytes: %s\n", n, (char *)buf);
      //if(isalpha((int)buf[0]))
      {
        char *delitemine = " ";
        char *token;
        token = strtok((char*)buf,delitemine);
        while(token != NULL)
        {
          if(!strcmp(token,CHECK_DATA))
          {
            printf("token:= %s\n",token);
            *checkInformation = true;
            break;
          }
          token = strtok(NULL,delitemine);
        }
      }
      memset(buf,0,RECEIVE_LENG);
      
    }
    return;
}
int main()
{
  int i=0,
      cport_nr=4,        /* /dev/ttyS0 (COM1 on windows) */
      bdrate=9600;//count=0;       /* 9600 baud */
  
  char mode[]={'8','N','1',0},
       str[2][512];


  strcpy(str[0], "Hello World!\n");

  strcpy(str[1], "Happy serial programming!\n");

  if(RS232_OpenComport(cport_nr, bdrate, mode, 0))
  {
    printf("Can not open comport\n");

    return(0);
  }
  
  // for(int i=0;i < NUMBER_COM ; i++)
  // { 
  //     // if(RS232_GetPortnr(COM[i]) != -1)
  //     // {
  //     //   (RS232_GetPortnr(COM[i]) == i) ? printf("COM%d\n",i+1) : printf("error\n");
  //     // }
  //     printf("com:= %d\n",RS232_GetPortnr(COM[i]));
  // }
  
  char buf[] = "rs232 from pc\n";
  
  //char byte = 'P';
  bool checkInformation=false;
  while(1)
  { 
    if(!checkInformation)
    {
      if(RS232_SendBuf(cport_nr,(unsigned char*)buf,sizeof(buf))== BUF_ERROR)
      {
          printf("can not send buf\n");
          return 0;
      }
      // checkInformation=true;
    }
    
    task_receive(&cport_nr,&checkInformation);
#if USE
    count++;
    (count > STOP) ? RS232_CloseComport(cport_nr) : printf("count:= %d\n",count);
    //RS232_SendByte(cport_nr,"\n");
    if(RS232_SendByte(cport_nr,byte))
    {
        printf("can not send bytes\n");
        return 0;
    }
    if(RS232_SendBuf(cport_nr,(unsigned char*)buf,sizeof(buf))== BUF_ERROR)
    {
        printf("can not send buf\n");
        return 0;
    }
    RS232_cputs(cport_nr, str[i]);

    printf("sent: %s buf:= %s byte:= %c\n", str[i],buf,byte);

#endif
#ifdef _WIN32
    Sleep(1000);
#else
    usleep(1000000);  /* sleep for 1 Second */
#endif

    i++;

    i %= 2;
  }

  return(0);
}

