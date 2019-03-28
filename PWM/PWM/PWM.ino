#include <VirtualWire.h>

const int Rec=9;

void setup()
{
  Serial.begin(9600);
  vw_setup(2000);
  vw_set_rx_pin(Rec);
  vw_rx_start();
}

void loop()
{
   uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;

   if(vw_get_message((uint8_t*)buf,&buflen))
   {
    String dato;
      //if((char)buf[0]=='f')
      //{
        for (int i = 1; i < buflen; i++)//Vaceamos el buffer en una cadena 
        {
            dato.concat((char)buf[i]);
        }
            int pwm = dato.toInt();  // Convertir a int
            pwm=map(pwm, 0, 1023, 0, 255);
            analogWrite(A1,pwm);
      //}
    }
}
