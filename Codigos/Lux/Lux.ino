#include<VirtualWire.h>

const int Emi=11;
const int Res=10;
const int Sen=9;
int df =0;

void setup()
{
  Serial.begin(9600);
  vw_setup(2000);
  vw_set_tx_pin(Emi);                         //Configurar pin del Emisor
  vw_set_rx_pin(Res);                         //Configurar pin del reseptor
  vw_rx_start();

  pinMode(Sen, INPUT);
}
void loop()
{
  envios();
}
void envios()
{
  uint8_t ID;                                  //creamos Variable donde recibiremos el ID
  uint8_t IDlength=1;                          //Guardamos espacion pra el ID
  
  String str;                                  //Creamos cadena donde posteriormente guardaremos la cadena
  char buf[VW_MAX_MESSAGE_LEN];                //Guardamos espacio para el dato
  
  if(vw_get_message(&ID,&IDlength))
  {
    int valor=digitalRead(Sen);
    if(valor == HIGH)              
    {
      df = 1;
    }
    else
    {
      df = 0;
    }
                                               //Comprobamos si el mensaje es para nosotros
    if((char)ID=='a')                          //si es asi procesamos el dato y lo enviamos 
    {
      str="p"+String(df);                      //casteamos a una cadena.
      str.toCharArray(buf,sizeof(buf));        // Convertir a char array
      vw_send((uint8_t *)buf, strlen(buf));    // Enviar array
      vw_wait_tx(); // Esperar envio
    }
  }
}
