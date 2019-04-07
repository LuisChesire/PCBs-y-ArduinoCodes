#include <ArduinoJson.h>
#include <LowPower.h>
#include <VirtualWire.h>
char IDs [6]={'a','b','c','d','e','f'}; // arreglo de IDs, abajo se muestra a que modulo corresponde
                                    //MOV -> a
                                    //LUZ Digital -> b
                                    //Luz Analogico -> c
                                    //Whato -> d
                                    //PWM -> e y f
int Lecturas [4]={0,0,0,0}; //arrglo donde guardaremos las lecturas en el mismo orden que los ID's
int i = 0;  //variable para inicializar el indice del for para ir reccoriendo todos los modulos.
const int emi = 9; //asignamos el pin del amisor
const int res = 10; //asignamos el pin del reseptor
String str;                                  //Creamos cadena donde posteriormente guardaremos la cadena
char buf[VW_MAX_MESSAGE_LEN];                //Guardamos espacio para el dato

void setup() 
{
  Serial.begin(9600); //inicializamos el serial.
  vw_setup(2000); //configuramos la velocidad de los modulos de comunicaicon. 
  vw_set_tx_pin(emi); //configuramos el pin que usaremos como emisor. 
  vw_set_rx_pin(res); //configuramos el pin que usaremos como reseptor.
  vw_rx_start();      //inicializamos  el receptor.
}

void loop() 
{
  comunicacion();
  PWM();
}

void comunicacion()
{
  for(i=0;i<4;i++)
  {
    
    vw_send((uint8_t*)IDs[i], sizeof(IDs[i]) );//Enviamos el primer id
    vw_wait_tx(); //esperamos que el mensaje sea enviado
    leer(i); //mandamos a llamar la funcion leer
  }
}
//la funcion leer basicamente nos permitira recivir la informacion de 
// los diferentes modulos esto mediante la comprobacion de la existencia de 
//mensajes y en caso de que exita un mensaje este es guardado en la pocision 
//del arreglo que le corresponda.
void leer(int i)
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];  //Creamos nuesto buffer donde guardamos lo que nos manden
  uint8_t buflen = VW_MAX_MESSAGE_LEN; // asignamos el espacio maximo posible al buffer
  
  if (vw_get_message((uint8_t *)buf,&buflen)) //en caso de exista algo en el receptor lo guardamos en el buffer
    {
      String dataString;  //Variable donde guardaremos los datos
      if((char)buf[0]=='p') //comprobamos si el mnseje es para nosotos 
      {
        for (int j = 1; j < buflen; j++)  //recorremos todo el buffer
        {
           dataString.concat((char)buf[j]); //iremos concatenado lo que existe en el buffer
        }
           Lecturas[i] = dataString.toInt();  // Convertir a int y guardaremos en nuestro arreglo de lecturas
      }
    }
}

void PWM()
{
  int Mov=Lecturas[0];
  int Luz=Lecturas[2];
  
  str="e"+String(Mov);
  str.toCharArray(buf,strlen(buf));
  vw_wait_tx();
  
  str="f"+String(Luz);
  str.toCharArray(buf,strlen(buf));
  vw_wait_tx();
}
