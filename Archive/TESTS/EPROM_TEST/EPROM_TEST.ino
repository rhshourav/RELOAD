<<<<<<< HEAD
/*
 * Circuits4you.com
 * Reading and Writing String to EEPROM Example Code
 * Oct 2018
 */

#include <EEPROM.h>

void writeString(char add,String data);
String read_String(char add);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  EEPROM.begin(512);
  String data = "Hello World dgggggggggggggggg";
  String data1 =" Shouravbakjgadk fvnjad";

  Serial.print("Writing Data:");
  Serial.println(data);

  writeString(100, data);
  writeString(400, data1);//Address 10 and String type data
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  String recivedData;
  recivedData = read_String(100);
  String recived;
  recived = read_String(400);
  Serial.print("Read Data:");
  Serial.println(recivedData);
  delay(3000);
  Serial.println("Read Data1: ");
  Serial.print(recived);
}

void writeString(char add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
}


String read_String(char add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}
=======
/*
 * Circuits4you.com
 * Reading and Writing String to EEPROM Example Code
 * Oct 2018
 */

#include <EEPROM.h>

void writeString(char add,String data);
String read_String(char add);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  EEPROM.begin(512);
  String data = "Hello World dgggggggggggggggg";
  String data1 =" Shouravbakjgadk fvnjad";

  Serial.print("Writing Data:");
  Serial.println(data);

  writeString(100, data);
  writeString(400, data1);//Address 10 and String type data
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  String recivedData;
  recivedData = read_String(100);
  String recived;
  recived = read_String(400);
  Serial.print("Read Data:");
  Serial.println(recivedData);
  delay(3000);
  Serial.println("Read Data1: ");
  Serial.print(recived);
}

void writeString(char add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
}


String read_String(char add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}
>>>>>>> 8a7ce65297df2dec5a6fbe25181b472864c964a7
