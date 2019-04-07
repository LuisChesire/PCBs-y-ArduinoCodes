#include <VirtualWire.h>

const int Rec=9;
int Mov;
float Analog;
uint8_t buf[VW_MAX_MESSAGE_LEN];  //Creamos nuesto buffer donde guardamos lo que nos manden
uint8_t buflen = VW_MAX_MESSAGE_LEN; // asignamos el espacio maximo posible al buffer
  
void setup()
{
  Serial.begin(9600);
  vw_setup(2000);
  vw_set_rx_pin(Rec);
  vw_rx_start();
}

void loop()
{
 Lmov();
 Lanalog();
 Mapeo();
}
void Lmov()
{
  
  if (vw_get_message((uint8_t *)buf,&buflen)) //en caso de exista algo en el receptor lo guardamos en el buffer
    {
      String dataString;  //Variable donde guardaremos los datos
      if((char)buf[0]=='e') //comprobamos si el mnseje es para nosotos 
      {
        for (int j = 1; j < buflen; j++)  //recorremos todo el buffer
        {
           dataString.concat((char)buf[j]); //iremos concatenado lo que existe en el buffer
        }
           Mov = dataString.toInt();  // Convertir a int y guardaremos en nuestro arreglo de lecturas
      }
    }
}
void Lanalog()
{
  if (vw_get_message((uint8_t *)buf,&buflen)) //en caso de exista algo en el receptor lo guardamos en el buffer
    {
      String dataString;  //Variable donde guardaremos los datos
      if((char)buf[0]=='f') //comprobamos si el mnseje es para nosotos 
      {
        for (int j = 1; j < buflen; j++)  //recorremos todo el buffer
        {
           dataString.concat((char)buf[j]); //iremos concatenado lo que existe en el buffer
        }
           Analog = dataString.toFloat();  // Convertir a int y guardaremos en nuestro arreglo de lecturas
      }
    }
}
void Mapeo()
{
  int pwm=map(Analog, 0, 1023, 0, 255);    //Mapeamos el valor de pwm 
  if(Mov==1 && pwm>=85)
  {
     analogWrite(A1,pwm);                    //Escribimos el valor mapeado en la salida analogica
  }
  else                                      //En caso de que no no haya movimiento o la luz no se suficiente entonces
  {
     analogWrite(A1,0);                    //Escribimos el valor de 0 en el puerto analogico A1
  }
            
}
/*
 *   uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;

   if(vw_get_message((uint8_t*)buf,&buflen))
   {
    String dato;
      if((char)buf[0]=='e')
      {
          for (int i = 1; i < buflen; i++)//Vaceamos el buffer en una cadena 
          {
              dato.concat((char)buf[i]);
          }
            int pwm = dato.toInt();  // Convertir a int
            pwm=map(pwm, 0, 1023, 0, 255);
            analogWrite(A1,pwm);
      }
   }
*/
