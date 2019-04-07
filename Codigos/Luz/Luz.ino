#include<VirtualWire.h>

const int Emi=11;
const int Res=10;
const int Sen=9;

void setup()
{
  Serial.begin(9600);
  
  vw_setup(2000); // configuranos velocidad de transmision 
  vw_set_tx_pin(Emi); //Configurar pin del Emisor
  vw_set_rx_pin(Res); //Configurar pin del reseptor
  vw_rx_start();

  pinMode(Sen, INPUT);  //declaramos el pin de entrada
}

void loop()
{
  uint8_t ID;  //creamos Variable donde recibiremos el ID
  uint8_t IDlength=1; //Guardamos espacion pra el ID
  
  String str;  //Creamos cadena
  char buf[VW_MAX_MESSAGE_LEN]; //Guardamos espacio para el dato
  
  if(vw_get_message(&ID,&IDlength))
  {
    int Digital = 0;
    int dataInt=digitalRead(Sen); //Declaramos el entero que mandaremos
    float dataAnalog=analogRead(A0);
    if(dataInt == HIGH)
    {
      Digital=1;
    }
    else
    {
      Digital=0;
    }
    
    if((char)ID=='b') //si es asi procesamos el dato y lo enviamos 
    {
      str="p"+String(Digital); //casteamos a una cadena.
      str.toCharArray(buf,sizeof(buf)); // Convertir a char array
      vw_send((uint8_t *)buf, strlen(buf)); // Enviar array
      vw_wait_tx(); // Esperar envio

      delay(200);
    }
    else if((char)ID=='c')
    {
      str="p"+String(dataAnalog); //convertimos a String nuestro dato
      str.toCharArray(buf,sizeof(buf)); //convertimos a char array
      vw_send((uint8_t *)buf, strlen(buf)); // Enviar array
      vw_wait_tx();

      delay (200);
    }
  }
}
