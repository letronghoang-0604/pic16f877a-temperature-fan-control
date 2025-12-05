#INCLUDE <16f877a.H>       //
#device     adc=10         //
#FUSES  HS              // 
#USE DELAY(CLOCK=20M)      // 

#define LCD_ENABLE_PIN  PIN_B2                                    ////
#define LCD_RS_PIN      PIN_B4                                    ////
#define LCD_RW_PIN      PIN_B3                                    ////

#define LCD_DATA4       PIN_D7                                  ////
#define LCD_DATA5       PIN_D6                                    ////
#define LCD_DATA6       PIN_D5                                    ////
#define LCD_DATA7       PIN_D4                                    ////

#include <lcd.c>

#define        pir       pin_a1

unsigned int16 kq,ndlm35;

signed int32    PWM_DUTY,i;

VOID doc_lm35()
{
   SET_ADC_CHANNEL(0);
   kq=0;
   FOR(I=0;I<100;I++)         // 
   {
      kq = kq + READ_ADC();      // 
      DELAY_MS(2);
   }
   kq = kq/2.046/100;         // 
   ndlm35=kq;   
   lcd_gotoxy(1,1);
   lcd_putc(" NHIET DO:");
   lcd_putc(ndlm35/10+0x30);     // 
   lcd_putc(ndlm35%10+0X30);     // 
   lcd_putc(0xdf);
   lcd_putc("C  ");
}


VOID MAIN()
{
    set_tris_e(0xff);      //
    set_tris_c(0xff);
    set_tris_d(0x00);
    set_tris_a(0xff);
    
   
   LCD_INIT();        // 
   SETUP_ADC(ADC_CLOCK_DIV_32);    //
   SETUP_ADC_PORTS(AN0);          // 

   SETUP_TIMER_2(T2_DIV_BY_16,249,1);       //     
   SETUP_CCP1(CCP_PWM);
   PWM_DUTY=0;
   SET_PWM1_DUTY(PWM_DUTY);
   
   WHILE(TRUE)
   {
      DOC_LM35();
      if(input(pir)==0)
      {
         if(ndlm35<30)        //     
         {
            PWM_DUTY=0;
            SET_PWM1_DUTY(PWM_DUTY);
            lcd_gotoxy(1,2);
            lcd_putc("   QUAT DUNG    ");
         }
         else if(ndlm35<35)         //
         {
            PWM_DUTY=400;
            SET_PWM1_DUTY(PWM_DUTY);
            lcd_gotoxy(1,2);
            lcd_putc("QUAT CHAY CAP 1 ");
         }
         else if(ndlm35<40)        
         {
            PWM_DUTY=700;
            SET_PWM1_DUTY(PWM_DUTY);
            lcd_gotoxy(1,2);
            lcd_putc("QUAT CHAY CAP 2 ");
         }
         else
         {
            PWM_DUTY=1000;
            SET_PWM1_DUTY(PWM_DUTY);
            lcd_gotoxy(1,2);
            lcd_putc("QUAT CHAY CAP 3 ");
         }   
      }
      else
      {
         lcd_gotoxy(1,2);
         lcd_putc(" KHONG CO NGUOI ");   
         PWM_DUTY=0;
         SET_PWM1_DUTY(PWM_DUTY);
      }
   }
}

