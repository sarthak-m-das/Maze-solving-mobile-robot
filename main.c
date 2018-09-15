/*
 * o.c
 *
 * Created: 22-01-2018 02:16:36
 * Author : SARTHAK
 */ 

/*
 * TEST 2C.c
 *
 * Created: 27-12-2017 14:23:36
 * Author : SARTHAK
 */ 

#include <avr/io.h>


#define CLEARBIT(ADDRESS,BIT)    (ADDRESS &= ~(1<<BIT))
#define SETBIT(ADDRESS,BIT)    (ADDRESS |= (1<<BIT))
#define CHECKBIT(ADDRESS,BIT)    (ADDRESS & (1<<BIT))

void timer1_int()
{
	TCCR1B=(1<<CS02)|(1<<CS00);
	TCNT1=0;
}

int a;
int dir[50];
int n=0,i=0,p=0;

void straight();
void left();
void right();
void uturn();
int move_inch();
void stop();

#define R_MOTOR OCR3A
#define L_MOTOR OCR3B

void PWM_Init(void)
{
	ICR3=0xFFFF;
	TCCR3A |=(1<<WGM31)|(1<<COM3A1)|(1<<COM3B1);
	TCCR3B |=(1<<WGM33)|(1<<CS30);
	DDRC |= (1<<PC6)|(1<<PC5);
}

int main(void)
{
	for(i=0;i<50;i++)
	{
		dir[i]=0;
	}
	
	DDRC |=(1<<PC0)|(1<<PC0)|(1<<PC2)|(1<<PC3);
	
	PWM_Init();
	PORTE |=(1<<PE4)|(1<<PE5);
	PORTB |=(1<<PB1)|(1<<PB2)|(1<<PB3);
	R_MOTOR=0xFFFF;
	L_MOTOR=0xFFFF;
	
	int e=0,pe=0;
	int kp,ki,kd,I,P,D,O;
	kp=4.15;
	kd=1.75;
	ki=0;
	P=0;
	D=0;
	O=0;
	I=0;

	
	while (1)
	{
		//line following
		
		// move forward
		
		if(!CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
		{
			SETBIT(PORTC,PC1);          //RIGHT MOTOR(CLOCKWISE)
			CLEARBIT(PORTC,PC0);
			SETBIT(PORTC,PC2);          //LEFT MOTOR(CLOCKWISE)
			CLEARBIT(PORTC,PC3);
			
			e=0;
			
		
			R_MOTOR=50000-35000*O;
			L_MOTOR=50000+35000*O;
			
		}
			
	
		//left pid
		
		if(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
		{
			
			SETBIT(PORTC,PC1);          //RIGHT MOTOR(HIGH CLOCKWISE)
			CLEARBIT(PORTC,PC0);
			SETBIT(PORTC,PC2);          //LEFT MOTOR(MEDIUM CLOCKWISE)
			CLEARBIT(PORTC,PC3);
			
			e=1;
			
			R_MOTOR=50000-35000*O;
			L_MOTOR=50000+35000*O;
		}
		
		if(CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
		{
			
			SETBIT(PORTC,PC1);          //RIGHT MOTOR(HIGH CLOCKWISE)
			CLEARBIT(PORTC,PC0);
			SETBIT(PORTC,PC2);          //LEFT MOTOR(LOW CLOCKWISE)
			CLEARBIT(PORTC,PC3);
			
			e=2;
			
			R_MOTOR=50000-35000*O;
			L_MOTOR=50000+35000*O;
		}
		
		
		if(CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && !CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
		{
			SETBIT(PORTC,PC1);          //RIGHT MOTOR(CLOCKWISE)
			CLEARBIT(PORTC,PC0);
			SETBIT(PORTC,PC3);          //LEFT MOTOR(ANTICLOCKWISE)
			CLEARBIT(PORTC,PC2);
			
			e=3;
			
			R_MOTOR=50000-35000*O;
			L_MOTOR=50000+35000*O;
		}
		
		if(CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && !CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
		{
			SETBIT(PORTC,PC1);          //RIGHT MOTOR(CLOCKWISE)
			CLEARBIT(PORTC,PC0);
			SETBIT(PORTC,PC3);          //LEFT MOTOR(ANTICLOCKWISE)
			CLEARBIT(PORTC,PC2);
			
			e=4;
			
			R_MOTOR=50000-35000*O;
			L_MOTOR=50000+35000*O;
		}
		
		
		
		//RIGHT pid
		
		
		if(!CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
		{
			SETBIT(PORTC,PC1);          //RIGHT MOTOR(MEDIUM CLOCKWISE)
			CLEARBIT(PORTC,PC0);
			SETBIT(PORTC,PC2);          //LEFT MOTOR(HIGH CLOCKWISE)
			CLEARBIT(PORTC,PC3);
			
			e=-1;
			
			R_MOTOR=50000-35000*O;
			L_MOTOR=50000+35000*O;
		}
		
		if(CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
		{
			SETBIT(PORTC,PC1);          //RIGHT MOTOR(LOW CLOCKWISE)
			CLEARBIT(PORTC,PC0);
			SETBIT(PORTC,PC2);          //LEFT MOTOR(HIGH CLOCKWISE)
			CLEARBIT(PORTC,PC3);
			
			e=-2;
			
			R_MOTOR=50000-35000*O;
			L_MOTOR=50000+35000*O;
		}
		
		
		if(CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))
		{
			SETBIT(PORTC,PC0);          //RIGHT MOTOR(ANTICLOCKWISE)
			CLEARBIT(PORTC,PC1);
			SETBIT(PORTC,PC2);          //LEFT MOTOR(CLOCKWISE)
			CLEARBIT(PORTC,PC3);
			
			e=-3;
			
			R_MOTOR=50000-35000*O;
			L_MOTOR=50000+35000*O;
		}
		
		if(CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))
		{
			SETBIT(PORTC,PC0);          //RIGHT MOTOR(ANTICLOCKWISE)
			CLEARBIT(PORTC,PC1);
			SETBIT(PORTC,PC2);          //LEFT MOTOR(CLOCKWISE)
			CLEARBIT(PORTC,PC3);
			
			e=-4;
			
			R_MOTOR=50000-35000*O;
			L_MOTOR=50000+35000*O;
		}
		
		
		
		
		
		
		//90 degree left
		
		//cross
		
		if(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && !CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))
		{
			left();    
			dir[n]+=1;
			n++;
		}
		//Tee
		
		if(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && !CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))
		{
			left();
	
			dir[n]+=1;
			n++;
		}
		
		//11100
		if(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && !CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
		{
			left();
		
			dir[n]=1;
			n++;
		}
		
	
		//11110
		if(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && !CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
		{
			left();
			
			dir[n]+=1;
			n++;
		}
		
		
		//straight
		
		
		//01111
		
        if(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))
        {
		
		   a=move_inch();
		   if(a==1) 	
			{
	       	straight();
			}
			
			dir[n]+=2;
			n++;
		
       	}
	
		// 00111
		
		
		if(!CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))
		{
			a=move_inch()
			if(a==1)
			{
			straight();
			}
			
			dir[n]+=2;
			n++;
		}


        //90 degree right turn
		
        if(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))
        {
			a=move_inch;
			if(a==0)
			{
				right();
			}
			
			dir[n]+=3;
			n++;
		
		}
        
		if(!CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))
		{
			if()
			{
				right();
			}
			
			dir[n]+=3;
			n++;
		}
		
		
		
		//U turn
		
		if(CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
		{
			u_turn();
			
			
			dir[n]+=4;
			n++;
		}
		
		//stop
		
		if(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && !CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))
		{
			a=move_inch();
			if(a==2)
			{
			stop();
			break;
			}
			
		}
		

			P=kp*e;
			D=(e-pe)*kd;
			I=I+e;
			I=I*ki;
			
			O=I+P+D;
			pe=e;
			
	}
	if(dir[n-1]==4)
	{
		dir[n-1]=0;
		n=n--;
	}
	

	//SHORTEST DISTANCE
	     
	    do
		{
				//line following
				
				// move forward
				
				if(!CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
				{
					SETBIT(PORTC,PC1);          //RIGHT MOTOR(CLOCKWISE)
					CLEARBIT(PORTC,PC0);
					SETBIT(PORTC,PC2);          //LEFT MOTOR(CLOCKWISE)
					CLEARBIT(PORTC,PC3);
					
					e=0;
					
					
					R_MOTOR=50000-35000*O;
					L_MOTOR=50000+35000*O;
					
				}
				
				
				//left pid
				
				if(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
				{
					
					SETBIT(PORTC,PC1);          //RIGHT MOTOR(HIGH CLOCKWISE)
					CLEARBIT(PORTC,PC0);
					SETBIT(PORTC,PC2);          //LEFT MOTOR(MEDIUM CLOCKWISE)
					CLEARBIT(PORTC,PC3);
					
					e=1;
					
					R_MOTOR=50000-35000*O;
					L_MOTOR=50000+35000*O;
				}
				
				if(CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
				{
					
					SETBIT(PORTC,PC1);          //RIGHT MOTOR(HIGH CLOCKWISE)
					CLEARBIT(PORTC,PC0);
					SETBIT(PORTC,PC2);          //LEFT MOTOR(LOW CLOCKWISE)
					CLEARBIT(PORTC,PC3);
					
					e=2;
					
					R_MOTOR=50000-35000*O;
					L_MOTOR=50000+35000*O;
				}
				
				
				if(CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && !CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
				{
					SETBIT(PORTC,PC1);          //RIGHT MOTOR(CLOCKWISE)
					CLEARBIT(PORTC,PC0);
					SETBIT(PORTC,PC3);          //LEFT MOTOR(ANTICLOCKWISE)
					CLEARBIT(PORTC,PC2);
					
					e=3;
					
					R_MOTOR=50000-35000*O;
					L_MOTOR=50000+35000*O;
				}
				
				if(CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && !CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
				{
					SETBIT(PORTC,PC1);          //RIGHT MOTOR(CLOCKWISE)
					CLEARBIT(PORTC,PC0);
					SETBIT(PORTC,PC3);          //LEFT MOTOR(ANTICLOCKWISE)
					CLEARBIT(PORTC,PC2);
					
					e=4;
					
					R_MOTOR=50000-35000*O;
					L_MOTOR=50000+35000*O;
				}
				
				
				
				//RIGHT pid
				
				
				if(!CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
				{
					SETBIT(PORTC,PC1);          //RIGHT MOTOR(MEDIUM CLOCKWISE)
					CLEARBIT(PORTC,PC0);
					SETBIT(PORTC,PC2);          //LEFT MOTOR(HIGH CLOCKWISE)
					CLEARBIT(PORTC,PC3);
					
					e=-1;
					
					R_MOTOR=50000-35000*O;
					L_MOTOR=50000+35000*O;
				}
				
				if(CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
				{
					SETBIT(PORTC,PC1);          //RIGHT MOTOR(LOW CLOCKWISE)
					CLEARBIT(PORTC,PC0);
					SETBIT(PORTC,PC2);          //LEFT MOTOR(HIGH CLOCKWISE)
					CLEARBIT(PORTC,PC3);
					
					e=-2;
					
					R_MOTOR=50000-35000*O;
					L_MOTOR=50000+35000*O;
				}
				
				
				if(CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))
				{
					SETBIT(PORTC,PC0);          //RIGHT MOTOR(ANTICLOCKWISE)
					CLEARBIT(PORTC,PC1);
					SETBIT(PORTC,PC2);          //LEFT MOTOR(CLOCKWISE)
					CLEARBIT(PORTC,PC3);
					
					e=-3;
					
					R_MOTOR=50000-35000*O;
					L_MOTOR=50000+35000*O;
				}
				
				if(CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))
				{
					SETBIT(PORTC,PC0);          //RIGHT MOTOR(ANTICLOCKWISE)
					CLEARBIT(PORTC,PC1);
					SETBIT(PORTC,PC2);          //LEFT MOTOR(CLOCKWISE)
					CLEARBIT(PORTC,PC3);
					
					e=-4;
					
					R_MOTOR=50000-35000*O;
					L_MOTOR=50000+35000*O;
				}
			
			if((!CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))||(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))||(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && !CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))||(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && !CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))||(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && !CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5)))
			{
				switch(dir[i])
				{
					case 1:left();
					case 2:straight();
					case 3:right();
				}
				p++;
			}
		}
		
		while(dir[p]!=0) 
	
	return 0;
}

void left()
{
	timer1_int();
	while(1)
	{
		if(TCNT1<=7812)
		{
			R_MOTOR=0XFFFF;
			L_MOTOR=0XFFFF;
			SETBIT(PORTC,PC1);          //RIGHT MOTOR(CLOCKWISE)
			CLEARBIT(PORTC,PC0);
			SETBIT(PORTC,PC3);          //LEFT MOTOR(ANTICLOCKWISE)
			CLEARBIT(PORTC,PC2);
		}
		else 
		{
			CLEARBIT(PORTC,PC1);          //RIGHT MOTOR(STOP)
			CLEARBIT(PORTC,PC0);
			CLEARBIT(PORTC,PC2);          //LEFT MOTOR(STOP)
			CLEARBIT(PORTC,PC3);
			TCNT1=0;
			break;
		}
	}
}

void straight()
{
	timer1_int();
	while(1)
	{
		if(TCNT1<=7812)
		{
			R_MOTOR=0XFFFF;
			L_MOTOR=0XFFFF;
			SETBIT(PORTC,PC1);          //RIGHT MOTOR(CLOCKWISE)
			CLEARBIT(PORTC,PC0);
			SETBIT(PORTC,PC2);          //LEFT MOTOR(CLOCKWISE)
			CLEARBIT(PORTC,PC3);
		}
		else 
		{
			CLEARBIT(PORTC,PC1);          //RIGHT MOTOR(STOP)
			CLEARBIT(PORTC,PC0);
			CLEARBIT(PORTC,PC2);          //LEFT MOTOR(STOP)
			CLEARBIT(PORTC,PC3);
			TCNT1=0;
		    break;
		}
	}
}

void right()
{
	timer1_int();
	while(1)
	{
		if(TCNT0<=7812)
		{
			R_MOTOR=0xFFFF;
			L_MOTOR=0XFFFF;
			SETBIT(PORTC,PC0);          //RIGHT MOTOR(ANTI CLOCKWISE)
			CLEARBIT(PORTC,PC1);
			SETBIT(PORTC,PC2);          //LEFT MOTOR(CLOCKWISE)
			CLEARBIT(PORTC,PC3);
			
		}
		else 
		{
			CLEARBIT(PORTC,PC1);          //RIGHT MOTOR(STOP)
			CLEARBIT(PORTC,PC0);
			CLEARBIT(PORTC,PC2);          //LEFT MOTOR(STOP)
			CLEARBIT(PORTC,PC3);
			TCNT1=0;
			break;
		}
	}
}


void u_turn()
{
	timer1_int();
	while(1)
	{
		if(TCNT0<=15625)
		{
			R_MOTOR=0xFFFF;
			L_MOTOR=0XFFFF;
			SETBIT(PORTC,PC1);          //RIGHT MOTOR(CLOCKWISE)
			CLEARBIT(PORTC,PC0);
			SETBIT(PORTC,PC3);          //LEFT MOTOR(ANTICLOCKWISE)
			CLEARBIT(PORTC,PC2);
			
		}
		else 
		{
			CLEARBIT(PORTC,PC1);          //RIGHT MOTOR(STOP)
			CLEARBIT(PORTC,PC0);
			CLEARBIT(PORTC,PC2);          //LEFT MOTOR(STOP)
			CLEARBIT(PORTC,PC3);
			TCNT1=0;
			break;
		}
	}
}

int move_inch()
{
	timer1_int()
	while(1)
	{
		if(TCNT1<=1562)
		{
			R_MOTOR=0xFFFF;
			L_MOTOR=0XFFFF;
			SETBIT(PORTC,PC1);          //RIGHT MOTOR(CLOCKWISE)
			CLEARBIT(PORTC,PC0);
			SETBIT(PORTC,PC2);          //LEFT MOTOR(CLOCKWISE)
			CLEARBIT(PORTC,PC3);
			
		}
		else 
		{
			CLEARBIT(PORTC,PC1);          //RIGHT MOTOR(STOP)
			CLEARBIT(PORTC,PC0);
			CLEARBIT(PORTC,PC2);          //LEFT MOTOR(STOP)
			CLEARBIT(PORTC,PC3);
			TCNT1=0;
			break;
		}
	}
	
	if(!CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
	{
		return 1;
	}
	if(CHECKBIT(PINB,PB1) && CHECKBIT(PINB,PB2) && CHECKBIT(PINB,PB3) && CHECKBIT(PINE,PE4) && CHECKBIT(PINE,PE5))
	{
		return 0;
	}
	if(!CHECKBIT(PINB,PB1) && !CHECKBIT(PINB,PB2) && !CHECKBIT(PINB,PB3) && !CHECKBIT(PINE,PE4) && !CHECKBIT(PINE,PE5))
	{
		return 2;
	}
}

void stop()
{
   
	   		R_MOTOR=0xFFFF;
	   		L_MOTOR=0XFFFF;
	   		CLEARBIT(PORTC,PC1);          //RIGHT MOTOR(STOP)
	   		CLEARBIT(PORTC,PC0);
	   		CLEARBIT(PORTC,PC2);          //LEFT MOTOR(STOP)
	   		CLEARBIT(PORTC,PC3);

		
}






















