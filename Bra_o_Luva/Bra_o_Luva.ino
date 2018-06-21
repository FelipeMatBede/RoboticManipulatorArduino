#include <Servo.h> 
// Create a servo object 
Servo Base; 
Servo Sobe11; 
Servo Sobe12; 
Servo Sobe2; 
Servo Sobe3; 
Servo Giro; 
Servo Garra;
int posBaseinit=90;
int var2 = -30;
int posSobe11init=90-var2;
int posSobe12init=90+var2;
int posSobe2init=110;
int posSobe3init=70;
int posGiroinit=75;
int posGarrainit=140;
int posBase=posBaseinit;
int posSobe11=posSobe11init;
int posSobe12=posSobe12init;
int posSobe2=posSobe2init;
int posSobe3=posSobe3init;
int posGiro=posGiroinit;
int posGarra=posGarrainit;
char pos;
int var = 2;
void setup() { 
   // We need to attach the servo to the used pin number 
      pinMode(13,OUTPUT);
   digitalWrite(13,LOW);
   Base.attach(3); 
   Sobe11.attach(5); 
   Sobe12.attach(6);
   Garra.attach(8); 
   Sobe2.attach(9); 
   Sobe3.attach(10); 
   Giro.attach(11); 
   Serial.begin(9600);
   Sobe11.write(posSobe11init);
   Sobe12.write(posSobe12init);
   Sobe2.write(posSobe2init);
   Sobe3.write(posSobe3init);
   Giro.write(posGiroinit);
   Garra.write(posGarrainit);
   Base.write(posBaseinit);
   delay(10000);
 digitalWrite(13,HIGH);
//    for (int i = 10; i<170; i++){
//      delay(35);
//   Sobe11.write(180-i);
//   Sobe12.write(i);
//    }
//    
//   delay(1000);
//    for (int i = 170; i>10; i--){
//      delay(35);
//   Sobe11.write(180-i);
//   Sobe12.write(i);
//    }

   
}
void loop(){ 
  if(Serial.available()){
  pos= (char) Serial.read();
  delay(15);
   switch (pos)
  {
    
     ///////////////////////(BASE)
     case 'a' :
     posBase= posBase+var;
     if (posBase>(posBaseinit+20)) posBase=posBaseinit+20;
     Base.write(posBase);
     break;
     case 'b':
     posBase= posBase-var;
     if (posBase<(posBaseinit-20)) posBase=posBaseinit-20;
     Base.write(posBase);
     break;
     ///////////////////////(BRAÇO 01)
     case 'c' :
     posSobe11= posSobe11-var;
     if (posSobe11<(posSobe11init-20)) posSobe11=posSobe11init-20;
     Sobe11.write(posSobe11);
     posSobe12= posSobe12+var;
     if (posSobe12<(posSobe12init+20)) posSobe12=posSobe12init+20;
     Sobe12.write(posSobe12);
     break;
     case 'd' :
     posSobe11= posSobe11+var;
     if (posSobe11<(posSobe11init+20)) posSobe11=posSobe11init+20;
     Sobe11.write(posSobe11);
     posSobe12= posSobe12-var;
     if (posSobe12<(posSobe12init-20)) posSobe12=posSobe12init-20;
     Sobe12.write(posSobe12);
     break;
     ////////////////////////(BRAÇO 02)
     case 'e' :
  
     posSobe2= posSobe2+var;
   if (posSobe12<(posSobe2init+20)) posSobe12=posSobe2init+20;
     Sobe2.write(posSobe2);
     break;
     case 'f' :
     posSobe2= posSobe2-var;
     if (posSobe2<(posSobe2init-20)) posSobe2=posSobe2init-20;
     Sobe2.write(posSobe2);
     break;
     ////////////////////////(BRAÇO 03)
     case 'g' :
     posSobe3= posSobe3+var;
     if (posSobe3<(posSobe3init+20)) posSobe3=posSobe3init+20;
     Sobe3.write(posSobe3);
     break;
     case 'h' :
     posSobe3= posSobe3-var;
     if (posSobe3<(posSobe3init-20)) posSobe3=posSobe3init-20;
     Sobe3.write(posSobe3);
     break;
     ////////////////////////(GIRO)
     case 'i' :
     posGiro= posGiro+var;
     if (posGiro<(posGiroinit+20)) posGiro=posGiroinit+20;
     Giro.write(posGiro);
     break;
     case 'j' :
     posGiro= posGiro-var;
     if (posGiro<(posGiroinit-20)) posGiro=posGiroinit-20;
     Giro.write(posGiro);
     break;
     ////////////////////////(GARRA)
     case 'k' :
     posGarra= posGarra+var;
     if (posGarra<(posGarrainit+20)) posGarra=posGarrainit+20;
     Garra.write(posGarra);
     break;
     case 'l' :
     posGarra= posGarra-var;
     if (posGarra<(posGarrainit-20)) posGarra=posGarrainit-20;
     Garra.write(posGarra);
     break;
  }}
}
