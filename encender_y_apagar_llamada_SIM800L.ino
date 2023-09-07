/*
 * interruptor por llamadas GSM
 * diseño por: ANDROBOT
 * 07/09/2023
 * Apoya y sigueme en mis redes:
 * Youtube: Androbot Tech
 * Tik Tok: @androbot_tech
 * facebook: @AndrobotTech
*/
#include <SoftwareSerial.h>

SoftwareSerial SIM(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

#define rele 5

String dato;

void setup()
{
  pinMode(rele,OUTPUT);
  digitalWrite(rele,LOW);
  
  Serial.begin(9600);
  SIM.begin(9600);

  delay(1000); 
  SIM.println("AT");
  delay(500);
  SIM.print("AT+CLIP=1\r\n"); //habilitar identificador de llamadas
  delay(500);
}

void loop()
{
  
  if(SIM.available()>0)//preguntar si esta disponible el sim
    {
      dato=SIM.readString();
      delay(100);
      Serial.println(dato);
      delay(100);
      if(dato.indexOf("71309733") > -1)//PREGUNTAR si encuentra RING
      {
           Serial.println("llamada detectada");
           delay(100);
        if(digitalRead(rele)==HIGH)
          {digitalWrite(rele,LOW);delay(100);}
        else
          {digitalWrite(rele,HIGH);delay(100);}
        delay(1000);
        SIM.println("ATH");
        delay(1000);
        dato="";
      }
    }
}
