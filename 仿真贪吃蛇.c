#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define SNAKE 20                 //��󳤶�
#define TIME 50                 //��ʾ��ʱʱ��
#define SPEED 10               //�ٶȿ���
#define anode P0
#define cathode P1
#define tube P2

sbit buzzer=P3^1;
sbit up=P3^3;       //
sbit down=P3^4;
sbit left=P3^2;
sbit right=P3^5;

//uchar a[10]={}
uchar x[SNAKE+1];
uchar y[SNAKE+1];          
uchar time,n,i,e;              //��ʱʱ�䣬��ǰ�߳���ͨ��ѭ����������ǰ�ٶ�		
char addx,addy,number=0,food=0;                //λ��ƫ����
/********************
��ʱ����
*********************/
void delay(char MS)
{
	char us,usn;
	while(MS!=0)
		{
			usn = 0;
			while(usn!=0)
			{
				us=0xff;
				while (us!=0)
					{us--;};
				usn--;
			}
		MS--;
		}
}
void delayus()
{
unsigned char t;
for(t=200;t>0;t--);
}	
/*******************************************
�ж���ײ
*******************************************/
bit knock()
{bit k;
k=0;
if(x[1]>7||y[1]>7)k=1;                             //ײǽ
for(i=2;i<n;i++)if((x[1]==x[i])&(y[1]==y[i]))k=1;  //ײ�Լ�
return k;
}
/*****************
�������Ҽ�λ����
*****************/
void turnkey()// interrupt 0 using 2  
{
if(left){addx=0;if(addy!=-1)addy=1; else addy=-1;}//
if(right){addx=0;if(addy!=1)addy=-1; else addy=1;}//
if(up){addy=0;if(addx!=1)addx=-1; else addx=1;}
if(down){addy=0;if(addx!=-1)addx=1; else addx=-1;}//


}
/*****************
�˷�����
*****************/
uchar mux(uchar temp) 
{
if(temp==7)return 128;
if(temp==6)return 64;
if(temp==5)return 32;
if(temp==4)return 16;
if(temp==3)return 8;
if(temp==2)return 4;
if(temp==1)return 2;
if(temp==0)return 1;																             
return 0;
}
/*****************
��ʾʱ�� ��ʾ����
*****************/
void timer0(uchar k)
{
while(k--)
{
for(i=0;i<SNAKE+2;i++)
{
	anode=mux(x[i]);
	cathode=255-mux(y[i]);
 
    turnkey();                     //�������Ҽ�λ����
    delay(TIME);                   //��ʾ�ӳ�
	  anode=0x00;
    cathode=0xff;
//	if(food)buzzer=~buzzer;
//P2=0x00;P0=0xff;
}}
food=0;
} 
/****************������*************/
void beep()
{
uchar bee=90,time;

for(time=255;time>0;time--)
{buzzer=~buzzer;
 while(bee--);
}
}
/**************�ж�**************/
void init()
{
TMOD=0x02;
TH0=0x00;
TL0=0x00;
TR0=1;
//EA=1;
//ET0=1;
}
/*********************�����**************/
void seg()
{
 unsigned char a[16]={0xc0,0xf3,0x89,0xa1,0xb2,0xa4,0x84,0xf1,0x80,0xa0,0x90,0x86,0x8f,0x83,0x8c,0x9c};
//uchar a[10]={0x81,0x82,0x84,0x88,0x90,0xa0,0xc0,};
tube=a[number]; 
}
/*****************
������
*****************/	
void main(void)
{
 uchar food=0;
 e=SPEED;
 anode	=0x00;
 P1		=0xff;
 cathode=0xff;
 P3		=0x00;
 seg();
 init();
while(1)       
 {
 buzzer=0;
 for(i=3;i<SNAKE+1;i++)x[i]=100;for(i=3;i<SNAKE+1;i++)y[i]=100;//��ʼ��
 

 x[0]=4;y[0]=4; 
                 //����                            
 
 n=3;                                                          //�߳� n=-1
 x[1]=1;y[1]=0;                                                //��ͷ
 x[2]=0;y[2]=0;                                                //��β1
 addx=0;addy=0;                                                //λ��ƫ��
 //k=1;
 while(1){//2 seg();
 		 if(up==1 || down==1 || right==1 || left==1) break;   timer0(1);}

 while(1)         
  {  
  seg();
	timer0(e);
      if(knock())
        {e=SPEED;number=0;break;}                          //�ж���ײ
        if((x[0]==x[1]+addx)&(y[0]==y[1]+addy))         //�Ƿ�Զ���
           {n++;
		   number++;
//		   food=1;
		   if(n==SNAKE+1)
		   {n=3;e=e-10;
		   for(i=3;i<SNAKE+1;i++)x[i]=100;
       for(i=3;i<SNAKE+1;i++)y[i]=100;
		   }
           x[0]=x[n-2];
           y[0]=y[n-2];
//			do{
//			food=1;
//			x[0]=TH0%8+1;y[0]=TL0%8+1;
//			for(i=2;i<n;i++)if((x[0]==x[i])&(y[0]==y[i]))food=0;
//           
//		   }while(!food);
		   }
    for(i=n-1;i>1;i--){x[i]=x[i-1];y[i]=y[i-1];}        

    x[1]=x[2]+addx;y[1]=y[2]+addy;                     //�ƶ�
//  for(i=2;i<n;i++)if((x[]==x[i])&(y[0]==y[i]))food=1; 
  }						
 }			
}
//void inter() interrupt 1
//{
//static unsigned int count=0;
//TH0=0xff;TL0=0xd1;
//if(count==20000)
//{
//count=0;
//number++;
//if(number==16)number=0;
//}
//count++;
//}