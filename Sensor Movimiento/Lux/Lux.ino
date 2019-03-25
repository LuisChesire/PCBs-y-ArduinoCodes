#include<VirtualWire.h>

const int Emi=9;
const int Res=8;
const int Sen=7;

void setup()
{
  Serial.begin(9600);
  vw_setup(2000);
  vw_set_tx_pin(Emi); //Configurar pin del Emisor
  vw_set_rx_pin(Res); //Configurar pin del reseptor
  vw_rx_start();

  pinMode(Sen, INPUT);
}
void loop()
{
  uint8_t ID;  //creamos Variable donde recibiremos el ID
  uint8_t IDlength=1; //Guardamos espacion pra el ID
  
  String str;  //Creamos cadena
  char buf[VW_MAX_MESSAGE_LEN]; //Guardamos espacio para el dato
  
  if(vw_get_message(&ID,&IDlength))
  {
    int valor=digitalRead(Sen); //Declaramos el entero que mandaremos
    //Comprobamos si el mensaje es para nosotros
    if((char)ID=='a') //si es asi procesamos el dato y lo enviamos 
    {
      str="iq"+String(valor); //casteamos a una cadena.
      str.toCharArray(buf,sizeof(buf)); // Convertir a char array
      vw_send((uint8_t *)buf, strlen(buf)); // Enviar array
      vw_wait_tx(); // Esperar envio
    }
    else
    {
      printf("no somos nosotros");
    }
  }
}