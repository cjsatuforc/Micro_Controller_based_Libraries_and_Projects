#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char ADC_Conversion(unsigned char);
unsigned char ADC_Value1;
unsigned char ADC_Value2;
unsigned int str[7];
unsigned int k[4];


void config()
{
cli();

//ADC pin configuration
 DDRA = 0x00;  //set PORTA direction as input
 PORTA = 0x00; //set PORTA pins floating
 DDRC=0xC0;
 DDRB=0X08;
 DDRD=0X8C;
  

//Function to Initialize ADC
 ADCSRA = 0x00;
 ADMUX = 0x20;		//Vref=5V external --- ADLAR=1 --- MUX4:0 = 0000
 ACSR = 0x80;
 ADCSRA = 0x86;		//ADEN=1 --- ADIE=1 --- ADPS2:0 = 1 1 0

sei();

}

//This Function accepts the Channel Number and returns the corresponding Analog Value
unsigned char ADC_Conversion(unsigned char Ch)
{
 unsigned char a;
 Ch = Ch & 0x07;
 ADMUX= 0x20| Ch;
 ADCSRA = ADCSRA | 0x40;		//Set start conversion bit
 while((ADCSRA&0x10)==0);	    //Wait for ADC conversion to complete
 a=ADCH;
 ADCSRA = ADCSRA|0x10;          //clear ADIF (ADC Interrupt Flag) by writing 1 to it
 return a;
}


int main(void)
{
config();

unsigned int a,b,c,d;


   PORTC=0xC0;
   _delay_ms(5000);
   PORTC=0x00;
    _delay_ms(1000);
 
   // For white line readings
   
   str[0]= ADC_Conversion(0);
   str[1]= ADC_Conversion(1);
   str[2]= ADC_Conversion(2);
   str[3]= ADC_Conversion(3);
   
   PORTC=0xC0;
   _delay_ms(5000);
   PORTC=0x00;
   
   // For Black line readings
   
   str[4]=  ADC_Conversion(0);
   str[5]=  ADC_Conversion(1);
   str[6]=  ADC_Conversion(2);
   str[7]=  ADC_Conversion(3);

   
   for(int i=0;i<=3;i++)
   {
       k[i]=((str[i]+str[i+4])/2);
   }
   
   
   _delay_ms(1000);
   




while(1)
{
	
	
	
	if(ADC_Conversion(0)>k[0])
	{
	   a=1;
	}
	else if(ADC_Conversion(0)<k[0])
	{
	   a=0;
	}
	
	
	if(ADC_Conversion(1)>k[1])
	{
	   b=1;
	}
	else if(ADC_Conversion(1)<k[1])
	{
	   b=0;
	}
	
	
	if(ADC_Conversion(2)>k[2])
	{
	   c=1;
	}
	else if(ADC_Conversion(2)<k[2])
	{
	   c=0;
	}
	
	
	if(ADC_Conversion(3)>k[3])
	{
	   d=1;
	}
	else if(ADC_Conversion(3)<k[3])
	{
	   d=0;
	}
	
	
	if(a==0 && b==0 && c==0 && d==0)
	{
	  // STRAIGHT ROTATION
        
        PORTD=0X84;
		PORTB=0X00;
	}
	
	else if(a==0 && b==0 && c==0 && d==1)
	{
	  // LEFT ROTATION
        
        PORTD=0X80;
		PORTB=0X00;
	}
	
	else if(a==0 && b==0 && c==1 && d==0)
	{
	  // LEFT ROTATION
        
        PORTD=0X80;
		PORTB=0X00;
	}
	
	else if(a==0 && b==0 && c==1 && d==1)
	{
	  // LEFT ROTATION
        
        PORTD=0X80;
		PORTB=0X00;
	}
	
	else if(a==0 && b==1 && c==0 && d==0)
	{
// RIGHT ROTATION
        
        PORTD=0X04;
		PORTB=0X00;
	}
	
	else if(a==0 && b==1 && c==0 && d==1)
	{
	  // RIGHT ROTATION
        
        PORTD=0X04;
		PORTB=0X00;
	}
	
	else if(a==0 && b==1 && c==1 && d==0)
	{
	  // RIGHT ROTATION
        
        PORTD=0X04;
		PORTB=0X00;
	}
	
	else if(a==0 && b==1 && c==1 && d==1)
	{
	  // LEFT ROTATION
        
        PORTD=0X80;
		PORTB=0X00;
	}
	
	else if(a==1 && b==0 && c==0 && d==0)
	{
	  // LEFT ROTATION
        
        PORTD=0X80;
		PORTB=0X00;
	}
	
	else if(a==1 && b==0 && c==0 && d==1)
	{
	  // STRAIGHT ROTATION
        
        PORTD=0X84;
		PORTB=0X00;
	}
	
	else if(a==1 && b==0 && c==1 && d==0)
	{
	  // LEFT ROTATION
        
        PORTD=0X80;
		PORTB=0X00;
	}
	
	else if(a==1 && b==0 && c==1 && d==1)
	{
	  // LEFT ROTATION
        
        PORTD=0X80;
		PORTB=0X00;
	}
	
	else if(a==1 && b==1 && c==0 && d==0)
	{
	 // RIGHT ROTATION
        
        PORTD=0X04;
		PORTB=0X00;
	 }
	
	else if(a==1 && b==1 && c==0 && d==1)
	{
	  // RIGHT ROTATION
        
        PORTD=0X04;
		PORTB=0X00;
	}
	
	else if(a==1 && b==1 && c==1 && d==0)
	{
	  // RIGHT ROTATION
        
        PORTD=0X04;
		PORTB=0X00;
	}
	
	else if(a==1 && b==1 && c==1 && d==1)
	{
	  // UTURN ROTATION
        
        PORTD=0X04;
		PORTB=0X08;
	}
}


}

