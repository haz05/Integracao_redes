#include <Ethernet.h>
#include <SPI.h>

byte mac[] =      { 0x90, 0xA2, 0xDA, 0x0D, 0xCB, 0xC4 };
byte ip[] =       { 192, 168, 0, 57 };    
byte gateway[] =  { 192, 168, 0, 1 };
byte subnet[] =   { 255, 255, 255, 0 };
byte server[] =   { 192, 168, 0, 116 };

int atual,ref,acao,dif;

float ki = 1/100;
float kp = 1/100;
float integralA, proporcionalA, acA;
int temperaturaA, setpointA;


EthernetClient client;

int data;

void MbWriteReg(char ID,int RegAddr, int data)
{
  char buf[12] = {0x00,0x02,0x00,0x00,0x00,0x06,ID,0x06,RegAddr>>8,RegAddr&0x00FF,data>>8,data&0x00FF};
  client.write(buf,12);
  while(!client.available());
  while(client.available())
    char c = client.read();
}

void MbWriteCoil_on(char ID,int RegAddr)
{
  char buf[12] = {0x00,0x02,0x00,0x00,0x00,0x06,ID,0x05,RegAddr>>8,RegAddr&0x00FF,0xFF,0x00};
  client.write(buf,12);
  while(!client.available());
  while(client.available())
    char c = client.read();
}

void MbWriteCoil_off(char ID,int RegAddr)
{
  char buf[12] = {0x00,0x02,0x00,0x00,0x00,0x06,ID,0x05,RegAddr>>8,RegAddr&0x00FF,0x00,0x00};
  client.write(buf,12);
  while(!client.available());
  while(client.available())
    char c = client.read();
}

void MbReadInput(char ID,int RegAddr,int *data)
{
  char buf[12] = {0x00,0x02,0x00,0x00,0x00,0x06,ID,0x04,RegAddr>>8,RegAddr&0x00FF,0x00,0x01};
  client.write(buf,12);

  char resp[11];
  int i=0;
  while(!client.available());
  while(client.available())
  {
    resp[i] = client.read();
    i++;
  }
  *data = resp[9]<<8 | resp[10]&0xFF;
}

void MbReadCoil(char ID,int RegAddr,int *data)
{
  char buf[12] = {0x00,0x02,0x00,0x00,0x00,0x06,ID,0x02,RegAddr>>8,RegAddr&0x00FF,0x00,0x01};
  client.write(buf,12);

  char resp[11];
  int i=0;
  while(!client.available());
  while(client.available())
  {
    resp[i] = client.read();
    i++;
  }
  *data = resp[9];
}

void setup()
{
  Ethernet.begin(mac, ip, gateway, subnet);
  Serial.begin(9600);

  delay(1000);

  Serial.println("connecting...");
  while (!client.connect(server, 502));
  Serial.println("connected");

  integralA = 0;
}

void loop()
{
  int valor;
 
  // Controle de Luminosidade exterior 
  int ref = 8000;
  MbReadInput(1,0, &valor); // Leitura da Luminosidade 
  valor = valor;
  int erro;
  erro = ref - valor;
  MbWriteReg(1,0, erro); // Escreve direto na luminosidade exterior 

    // Lâmpada A
    MbReadCoil(1,0,&data);
    if (data == 1){
       MbWriteCoil_on(1,0);
    } else {
        MbWriteCoil_off(1,0);
      }

    // Temperatura A
    MbReadInput(1, 1, &temperaturaA);
    MbReadInput(1, 2, &setpointA);
    float erroA;
    erroA = (setpointA - temperaturaA)/2000;
    integralA = integralA + erroA;
    acA = integralA;
    if(acA<10 && acA>0){
      acA = acA;
      } else if (acA>10){
        acA = 10;
        } else if (acA<0){
          acA = 0;
        }
    Serial.println(acA);
    MbWriteReg(1,1, acA);
    

  // Lampada B
    MbReadCoil(1,1,&data);
  if (data == 1){
     MbWriteCoil_on(1,1);
  } else {
      MbWriteCoil_off(1,1);
    }

  // Lâmpada D
     MbReadCoil(1,2,&data);
  if (data == 1){
     MbWriteCoil_on(1,2);
  } else {
      MbWriteCoil_off(1,2);
    }

  // Lâmpada E
     MbReadCoil(1,3,&data);
  if (data == 1){
     MbWriteCoil_on(1,3);
  } else {
      MbWriteCoil_off(1,3);
    }

  // Lâmpada F
     MbReadCoil(1,4,&data);
  if (data == 1){
     MbWriteCoil_on(1,4);
  } else {
      MbWriteCoil_off(1,4);
    }

  // Lâmpada G
     MbReadCoil(1,5,&data);
  if (data == 1){
     MbWriteCoil_on(1,5);
  } else {
      MbWriteCoil_off(1,5);
    }

   // Lâmpada H
     MbReadCoil(1,6,&data);
   if (data == 1){
     MbWriteCoil_on(1,6);
  } else {
      MbWriteCoil_off(1,6);
    }

   // Lâmpada I
     MbReadCoil(1,7,&data);
   if (data == 1){
     MbWriteCoil_on(1,7);
  } else {
      MbWriteCoil_off(1,7);
    }

   // Lâmpada J
   MbReadCoil(1,8,&data);
   if (data == 1){
     MbWriteCoil_on(1,8);
  } else {
      MbWriteCoil_off(1,8);
    }  

   // Lâmpada K
   MbReadCoil(1,9,&data);
   if (data == 1){
     MbWriteCoil_on(1,9);
  } else {
      MbWriteCoil_off(1,9);
    }  

   // Lâmpada L
   MbReadCoil(1,10,&data);
   if (data == 1){
     MbWriteCoil_on(1,10);
  } else {
      MbWriteCoil_off(1,10);
    }  
      
   // Lâmpada M
   MbReadCoil(1,11,&data);
   if (data == 1){
     MbWriteCoil_on(1,11);
  } else {
      MbWriteCoil_off(1,11);
    }  

     // Lâmpada N
   MbReadCoil(1,12,&data);
   if (data == 1){
     MbWriteCoil_on(1,12);
  } else {
      MbWriteCoil_off(1,12);
    }  
  
}
