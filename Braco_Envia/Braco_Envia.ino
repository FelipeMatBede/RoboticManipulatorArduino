#include <SoftwareSerial.h>

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

double a1 = 22.25;
double a2 = 145;
double a3 = 180;
double a4 = 120;

float teta1 = 0;    
float teta2 = 0;       
float teta3 = 0;          
float teta4 = 0;
double teta5 = 0;

double gama = 0;
double beta = 0;
double alfa = 0;
double w = 0;
double k = 0;

int countEnviar=1;
int countMax=2;
bool PEnviar=true;
SoftwareSerial mySerial(12, 11); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(A0,OUTPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  mySerial.begin(9600);

}

void loop() { 


  /*posPotBaseAtual=map(analogRead(A0),0,1023,0,180);
  posPotBra1Atual=map(analogRead(A1),0,1023,0,180);
  posPotBra2Atual=map(analogRead(A2),0,1023,0,180);
  posPotBra3Atual=map(analogRead(A3),0,1023,0,180);
  posPotGiAtual=map(analogRead(A4),0,1023,0,180);
  posPotGrAtual=map(analogRead(A5),0,1023,0,180);
  
  posPotBase= (posPotBaseAtual-posBaseinit)*DEG_TO_RAD;
  posPotBra1=(posPotBra1Atual-90)*DEG_TO_RAD;
  posPotBra2=(posPotBra2Atual-posSobe2init)*DEG_TO_RAD;
  posPotBra3=(posPotBra3Atual-posSobe3init)*DEG_TO_RAD;
  posPotGi=(posPotGiAtual-posGiroinit)*DEG_TO_RAD;
  posPotGr=(posPotGrAtual-posGarrainit)*DEG_TO_RAD;*/
/*switch(mySerial.read()){
  
  case 'a':
  //Serial.println("ENTROU");
    countEnviar++;
 if(countEnviar>(countMax)){
    countEnviar=1;
    }
  PEnviar=true;
  break;

  }
if(PEnviar==true){
  //Serial.println("Entrou PEnvia");
    if(countEnviar==1){
    CinematicaInversa(300,300,60);
    }
    if(countEnviar==2){
    CinematicaInversa(350,250,100);
    }
   
  
PEnviar=false;
}
 */

Enviar(0.785398,1.115651,-0.857282,-0.258369,0.10000,0.10000);
delay(3000);
Enviar(-0.174533,1.115651,-0.857282,-0.258369,0.10000,0.10000);
delay(3000);


}
void Enviar(float teta1, float teta2, float teta3, float teta4, float teta5, float teta6){
  //Serial.println(teta3);
  String t1 = " "; 
  String t2 = " "; 
  String t3 = " "; 
  String t4 = " "; 
  String t5 = " "; 
  String t6 = " "; 
  String Pacote = " ";
  
  if(teta1> 0 || teta1< 0){
  t1=String(int(teta1))+ "."+String(getDecimal(teta1));
  }
  if(int(teta1) == 0 && teta1 < 0 ){
  t1="-"+String(int(teta1))+ "."+String(getDecimal(teta1)); 
    }
  
  if(teta2>0 || teta2<0){
  t2=String(int(teta2))+ "."+String(getDecimal(teta2));    
    }
  if(int(teta2) == 0 && teta2 < 0){
  t2="-"+String(int(teta2))+ "."+String(getDecimal(teta2));
    }
    
  if(teta3>0||teta3<0){
  t3=String(int(teta3))+ "."+String(getDecimal(teta3));  
    }
  if(int(teta3) == 0 && teta3 < 0){
  t3="-"+String(int(teta3))+ "."+String(getDecimal(teta3));
    }
    
  if(teta4>0||teta4<0){
  t4=String(int(teta4))+ "."+String(getDecimal(teta4));
    }
  if(int(teta4) == 0 && teta4 < 0){
  t4="-"+String(int(teta4))+ "."+String(getDecimal(teta4));    
    }
    
  if(teta5>0||teta5<0){
  t5=String(int(teta5))+ "."+String(getDecimal(teta5));
    }
  if(int(teta5) == 0 && teta5 < 0){
  t5="-"+String(int(teta5))+ "."+String(getDecimal(teta5)); 
    }
    
  if(teta6>0||teta6<0){
  t6=String(int(teta6))+ "."+String(getDecimal(teta6));    
    }
  if(int(teta6) == 0 && teta6 < 0){
  t6="-"+String(int(teta6))+ "."+String(getDecimal(teta6));
    }

  
  Pacote.concat("%");
  Pacote.concat(t1);
  Pacote.concat(";");
  Pacote.concat(t2);
  Pacote.concat(";");
  Pacote.concat(t3);
  Pacote.concat(";");
  Pacote.concat(t4);
  Pacote.concat(";");
  Pacote.concat(t5);
  Pacote.concat(";");
  Pacote.concat(t6);
  Pacote.concat("#");
  
  char PacotePos[61];
  Pacote.toCharArray(PacotePos,Pacote.length()+1);
  
 for(int i=0;i<strlen(PacotePos) ;i++){
  mySerial.write(PacotePos[i]);
  delay(15);
  }
  
  } 
 long getDecimal(float val)
{
  int intPart = int(val);
  long decPart = 1000000*(val-intPart); //I am multiplying by 1000 assuming that the foat values will have a maximum of 3 decimal places. 
                                    //Change to match the number of decimal places you need
  if(decPart>0)return(decPart);           //return the decimal part of float number if it is available 
  else if(decPart<0)return((-1)*decPart); //if negative, multiply by -1
  else if(decPart=0)return(00);           //return 0 if decimal part of float number is not available
}
void CinematicaInversa(float coordX, float coordY, float coordZ){
  
  w = sqrt (coordX*coordX + coordY*coordY);// essa variável é tipo uma auxiliar ao x
  
  w = w - a4;
 // Serial.print("Variavel w: ");
  //Serial.println(w);
  
  k = sqrt ((pow(w,2) + pow((coordZ-a1),2)));
  //Serial.print("Variavel k: ");
  //Serial.println(k);

  alfa = acos (w/k);
  //Serial.print("Variavel alfa: ");
  //Serial.println(alfa);

  gama = ((pow(a2,2) + pow(k,2) - pow(a3,2))/(2*a2*k));
  
if (gama>1.0 || gama<-1.0){
    gama=gama-(int)gama;
    }
    gama = acos(gama);
    //Serial.print("Variavel gama: ");
    //Serial.println(gama);

  beta = ((pow(a2,2) + pow(a3,2) - pow(k,2)) / (2*a2*a3));

  if(beta>1.0 || beta<-1.0) {
    beta=beta-(int)beta;
    }
  beta = acos(beta);
    //Serial.print("Variavel beta: ");
    //Serial.println(beta);
  //beta3 = beta3 ;
  //Serial.println(beta3);

  teta1 = atan(coordY/coordX);
  
  teta2 = HALF_PI - gama - alfa;

  teta3 = HALF_PI - beta;
  
  teta4 = -teta2 - teta3;
  Enviar(teta1,teta2,teta3,teta4, 0.01, 0.01);
  /*Serial.print("teta1 = ");
  Serial.println(teta1);
  //Serial.println(teta1*RAD_TO_DEG);
  Serial.print("teta2 = ");
   Serial.println(teta2);
  //Serial.println(teta2*RAD_TO_DEG);
  Serial.print("teta3 = ");
  Serial.println(teta3);
  //Serial.println(teta3*RAD_TO_DEG);
  Serial.print("teta4 = ");
   Serial.println(teta4);
  //Serial.println(teta4*RAD_TO_DEG); */
}


