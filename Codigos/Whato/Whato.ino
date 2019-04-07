#include<VirtualWire.h>
const int Emi = 9;
const int Res = 10;
int voltaje;
int corriente;
int Whats;

void setup() 
{
  Serial.begin(9600);
  vw_set_tx_pin(Emi);
  vw_set_rx_pin(Res);
  vw_rx_start();
}

void loop() 
{
 Calculo();
 enviar(); 
}
void enviar()
{
  uint8_t ID;  //creamos Variable donde recibiremos el ID
  uint8_t IDlength=1; //Guardamos espacion pra el ID

  String str;
  char buf[VW_MAX_MESSAGE_LEN]; //Guardamos espacio para el dato

  if(vw_get_message(&ID,&IDlength))
  {
    if((char)ID=='d')
    {
      str="p"+String(Whats);
      str.toCharArray(buf,sizeof(buf)); 
      vw_send((uint8_t*)buf, strlen(buf));
      vw_wait_tx();
    }
  }
  
}
void Calculo()
{
  voltaje = analogRead(A0); //leemos el ADC A0
  corriente = analogRead(A1); //leemos el ADC A1
  voltaje  = map(voltaje, 0, 938, 0, 295); //mapeamos la lectura del ADC A0 para valores entre 0 y 295.
  corriente = map(corriente, 62, 834, 0, 1023);  //mapeamos la lectura del ADC A1 para valores entre 0 y (en espera).
  Whats=(voltaje * corriente);
}
