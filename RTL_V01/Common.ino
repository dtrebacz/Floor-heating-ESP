
void EWR_String(char add,String data)
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
 
 
String ERD_String(char add,int maxlen)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<maxlen)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}

void EWR_Double(char addr, double value){

    union uf_tag {
      float temp_float ;
      byte temp_byte[4] ;
      } uf;

    uf.temp_float = value;
     
      for(int idx=0;idx<4;idx++)
        {
          EEPROM.write(addr+idx,uf.temp_byte[idx]);
        }
      EEPROM.commit();
  }


double ERD_Double(char addr){

    union uf_tag {
      float temp_float ;
      byte temp_byte[4] ;
      } uf;

     
      for(int idx=0;idx<4;idx++)
        {
          uf.temp_byte[idx] = EEPROM.read(addr+idx);
        }

      return uf.temp_float;
  }  
  
void BinOutCtrl(int GPIO, bool IN){
if (IN){
  digitalWrite(GPIO, HIGH);
}
else{
  digitalWrite(GPIO, LOW);
}




  
}

      
