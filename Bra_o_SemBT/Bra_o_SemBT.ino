
#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105


#include <Servo.h> 

Servo Base; 
Servo Sobe11; 
Servo Sobe12; 
Servo Sobe2; 
Servo Sobe3; 
Servo Giro; 
Servo Garra;

int posBaseinit=90;
int var2 = 10;
int posSobe11init=90+var2;
int posSobe12init=90-var2;
int posSobe2init=70;
int posSobe3init=100;
int posGiroinit=90;
int posGarrainit=50;
int posBase=posBaseinit;
int posSobe11=posSobe11init;
int posSobe12=posSobe12init;
int posSobe2=posSobe2init;
int posSobe3=posSobe3init;
int posGiro=posGiroinit;
int posGarra=posGarrainit;

bool stopbool=false;
bool Verificacao=false;
int count=0;
int countPos=0;
float Basei;
float Sobe1i;
float Sobe2i;
float Sobe3i;
float Giroi;
float Garrai;
double a1 = 22.25;
double a2 = 145;
double a3 = 180;
double a4 = 120;

float coordX;
float coordY;
float coordZ;

float pos1 = 0;
float pos2 = 0;
float pos3 = 0;
float pos4 = 0;
float pos5 = 0;
float pos6 = 0;

//int count=0;
float t1 = 0;    
float t2 = 0;       
float t3 = 0;          
float t4 = 0;
double t5 = 0;

double r=0;
double gama = 0;
double beta = 0;
double alfa = 0;
double w = 0;
double k = 0;
double Kp = 1;
double ki = 0.0062;
float I1,I2,I3,I4,I5,I6;
int tempoAtual, tempoAnterior, dt;

void setup() {
   pinMode(13,OUTPUT);
   Base.attach(3); 
   Sobe11.attach(5); 
   Sobe12.attach(6);
   Garra.attach(8); 
   Sobe2.attach(9); 
   Sobe3.attach(10); 
   Giro.attach(11); 
   Serial.begin(9600);
     Base.write(posBase);
     Sobe11.write(posSobe11);
     Sobe12.write(posSobe12);
     Sobe2.write(posSobe2);
     Sobe3.write(posSobe3);
     Giro.write(posGiro);
     Garra.write(posGarra);
     
     stopbool=false;
  // attachInterrupt(0, Stop, RISING);  

}

void loop() {
  if(count==5){
    count=0;
    }
    if(count==0){
      CinematicaInversa(-400.0,250.0,40.0);
      }
    if(count==1){
      CinematicaInversa(-400.0,300.0,40.0);
      }
    if(count==2){
      CinematicaInversa(-375.0,250.0,40.0);
      }
    if(count==3){
      CinematicaInversa(-350.0,300.0,40.0);
      }
    if(count==4){
      CinematicaInversa(-350.0,250.0,40.0);
      }
  //if(Serial.available()>0){
  
  //leStringSerial();
  //if(CalculoDireto(Basei,Sobe1i,Sobe2i,Sobe3i,0)){
    //Serial.println("OK");
      int Baseint = Basei*(RAD_TO_DEG);
      int Sobe1int = Sobe1i*(RAD_TO_DEG);
      int Sobe2int = Sobe2i*(RAD_TO_DEG);
      int Sobe3int = Sobe3i*(RAD_TO_DEG);
      int Giroint = Giroi*(RAD_TO_DEG);
      int Garraint = Garrai*(RAD_TO_DEG);

     /*Serial.println(Baseint);
     Serial.println(Sobe1int);
     Serial.println(Sobe2int);
     Serial.println(Sobe3int);
     Serial.println(Giroint);*/
    
     posBase=posBase+Baseint;
     posSobe11=posSobe11+Sobe1int;
     posSobe12=posSobe12-Sobe1int;
     posSobe2=posSobe2+Sobe2int;
     posSobe3=posSobe3+Sobe3int;
     
     /*Serial.println(posBaseinit+Baseint);
     Serial.println(posSobe11init+Sobe1int);
     Serial.println(posSobe12init-Sobe1int);
     Serial.println(posSobe2init+Sobe2int);
     Serial.println(posSobe3init+Sobe3int);*/
     
     /*if(Baseint<0){
     for(int i=Base.read(); i> (posBaseinit+Baseint-1); i--){
      //Serial.println(i);
     Base.write(i);
     delay(10);
     }
     }
     if(Baseint>0){
     for(int i=Base.read(); i< (posBaseinit+Baseint+1); i++){
      //Serial.println(i);
     Base.write(i);
     delay(10);
     }
     }
     delay(10);
     Sobe11.write(posSobe11init-Sobe1int);
     Sobe12.write(posSobe12init+Sobe1int);
     delay(10);
     if(Sobe2int<0){
     for(int i=Sobe2.read(); i> (posSobe2init+Sobe2int-1); i--){
      //Serial.println(i);
     Sobe2.write(i);
     delay(10);
     }
     }
     if(Sobe2int>0){
     for(int i=Sobe2.read(); i< (posSobe2init+Sobe2int+1); i++){
      //Serial.println(i);
     Sobe2.write(i);
     delay(10);
     }
     }
     delay(10);
     if(Sobe3int<0){
     for(int i=Sobe3.read(); i> (posSobe3init+Sobe3int-1); i--){
      //Serial.println(i);
     Sobe3.write(i);
     delay(10);
     }
     }
     if(Sobe3int>0){
     for(int i=Sobe3.read(); i< (posSobe3init+Sobe3int+1); i++){
      //Serial.println(i);
     Sobe3.write(i);
     delay(10);
     }
     }*/
    Base.write(posBaseinit+Baseint);
    delay(100);
    Sobe11.write(posSobe11init+Sobe1int);
     Sobe12.write(posSobe12init-Sobe1int);
     delay(100);
    Sobe2.write(posSobe2init+Sobe2int);
    delay(100);
    Sobe3.write(posSobe3init+Sobe3int);
    //Serial.write('a');
   //  Giro.write(posGiroinit+Giroint);
    // Garra.write(posGarrainit+Garraint);
      /*deltaTempo();
      controlador1(Baseint);
      controlador2(Sobe1int);
      controlador3(Sobe2int);
      controlador4(Sobe3int);
      //controlador5(Giroi);
      //controlador6(Garrai);*/
     
   // }
  //}
  count++;
  if(stopbool==true){
     Base.write(90);
     delay(500);
     Sobe3.write(180);
     delay(500);
      Sobe2.write(60);
     delay(500);
     Sobe11.write(60); 
     Sobe12.write(120);
     delay(500);
     Giro.write(90);
     delay(500);
     Garra.write(50);
    }
  delay(1000);
}

void leStringSerial(){
  String Base = "";
  String Sobe1 = "";
  String Sobe2 = "";
  String Sobe3 = "";
  String Giro = "";
  String Garra = "";
  char caractere;
  bool Paco=false;
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      if(caractere == '%'){
        Paco=true;
        }
     if(Paco==true){
      if (count==0){
      if (caractere != '%' && caractere != ';')
      Base.concat(caractere);
    }
      if (count==1){
      if (caractere != ';')
      Sobe1.concat(caractere);
    }
      if (count==2){
      if (caractere != ';')
      Sobe2.concat(caractere);
    }
      if (count==3){
      if (caractere != ';')
      Sobe3.concat(caractere);
    }
      if (count==4){
      if (caractere != ';')
      Giro.concat(caractere);
    }
      if (count==5){
      if (caractere != ';' && caractere != '#')
      Garra.concat(caractere);
    }
    if (caractere == ';'){
      count++;
      }
    if (caractere == '#'){
      count=0;
      Verificacao=true;
      Paco=false;
      }
     }
    }
    
    
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
  if(Verificacao){
  Basei=Base.toFloat();;
  Sobe1i=Sobe1.toFloat();
  Sobe2i=Sobe2.toFloat();
  Sobe3i=Sobe3.toFloat();
  Giroi=Giro.toFloat();
  Garrai=Garra.toFloat();
  }

}

void mMatriz(double a[4][4],double b[4][4], double c[4][4]){
  for(int i=0;i<=3;i++)
  {
    for(int j=0;j<=3;j++)
    {
      c[i][j]=0;
      for(int k=0;k<=3;k++)
        c[i][j]=c[i][j]+a[i][k]*b[k][j];
    }
  }
}
void imprimir(double m[4][4]){
  for (int i=0;i<=3;i++){
    Serial.print("[ ");
    for (int j=0;j<=3;j++){
    Serial.print(m[i][j]);
    if (j<3) Serial.print(" , ");
        else Serial.println(" ]");
    }
  }
}
boolean CalculoDireto(float teta1,float teta2,float teta3,float teta4, double teta5){
double m02 [4][4]= {
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  }; 
  double m03 [4][4]= {
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  };   
  double m24 [4][4]= {
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  };  
  double m04 [4][4]= {
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  }; 
  
  //resultante m0-1
  double A [4][4]= {
  {cos(teta1),-sin(teta1),0,0},
  {sin(teta1),cos(teta1),0,0},
  {0,0,1.0,a1},
  {0,0,0,1.0},
  };  
  double B [4][4]= {
  {cos(teta2),0,sin(teta2),0},
  {0,1.0,0,0},
  {-sin(teta2),0,cos(teta2),0},
  {0,0,0,1.0},
  }; 
  double m01 [4][4]= {
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  };
  mMatriz(A,B,m01);
  //imprimir(m01);
    
  //resultante m1-2
  double C [4][4]= {
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,a2},
  {0,0,0,1.0},
  };  
  double D [4][4]= {
  {cos(HALF_PI+teta3),0,sin(HALF_PI+teta3),0},
  {0,1.0,0,0},
  {-sin(HALF_PI+teta3),0,cos(HALF_PI+teta3),0},
  {0,0,0,1.0},
  }; 
  double m12 [4][4]= {
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  };
  mMatriz(C,D,m12);
  //imprimir(m12);
  
  //resultante m2-3
  double E [4][4]= {
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,a3},
  {0,0,0,1.0},
  };  
  double F [4][4]= {
  {cos(teta4),0,sin(teta4),0},
  {0,1.0,0,0},
  {-sin(teta4),0,cos(teta4),0},
  {0,0,0,1.0},
  }; 
  double m23 [4][4]= {
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  };
  mMatriz(E,F,m23);
  //imprimir(m23);
  
  //resultante m3-4
  double G [4][4]= {
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,a4},
  {0,0,0,1.0},
  };  
  double H [4][4]= {
  {cos(teta5),-sin(teta5),0,0},
  {sin(teta5),cos(teta5),0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  }; 
  double m34 [4][4]= {
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  };
  mMatriz(G,H,m34);
  //imprimir(m34);
    
  /*
  double E [4][4]= {
  {1,0,0,0},
  {0,1,0,0},
  {0,0,1,a3},
  {0,0,0,1},
  };*/  
  
  //resultante m0-4
  mMatriz(m01,m12,m02);
  mMatriz(m02,m23,m03);
  mMatriz(m03,m34,m04);
  
  coordX=m04[0][3];
  coordY=m04[1][3];
  coordZ=m04[2][3];
  Serial.println(coordX);
  Serial.println(coordY);
  Serial.println(coordZ);
  if (coordZ<30){return false;}
  if(coordY>(115+a4)) {
  return true;}
  else {
    
  if(coordX>(115+a4)){ return true;}
  return false;
  }
  }
 void CinematicaInversa(float cordX, float cordY, float cordZ){
  
  w=sqrt((cordX*cordX)+(cordY*cordY));
  w-=a4;
  r=sqrt((w*w)+((cordZ-a1)*(cordZ-a1)));
  gama=acos(w/r);
  alfa=(-(a2*a2)-(r*r)+(a3*a3))/(-2*a2*r);
  if (alfa>1.0 || alfa<-1.0) 
    alfa=alfa-(int)alfa;
  alfa=acos(alfa);
  
  
  beta=(-(a2*a2)-(a3*a3)+(r*r))/(-2*a2*a3);
   if (beta>1.0 || beta<-1.0) 
    beta=beta-(int)beta;
  beta=acos(beta);
   
  
  t1=atan(cordY/cordX); 
  //t1=t1*(RAD_TO_DEG);
  t2=HALF_PI-gama-alfa;
  //t2=t2*(RAD_TO_DEG);
  t3=HALF_PI-beta;
  //t3=t3*(RAD_TO_DEG);
  
  t4=-t2-t3;
  
 Basei=t1;
 Sobe1i=t2;
 Sobe2i=t3;
 Sobe3i=t4;
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

void Stop(){
   stopbool= true;
  }
  

