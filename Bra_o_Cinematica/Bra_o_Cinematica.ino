/*=====================================================================================
; Projeto Braço Robótica Jerimum
;
; Versao: 1.1
; Created:   01 / 03 / 2018
; Finalizado: 20 / 06 / 2018
; Autor: Felipe Bedê
;
;======================================================================================
; DESCRICAO
;======================================================================================
; 1. Receber pacote de dados via bluetooth 
; 2. Analisar se os movimentos requeridos no pacote são possíveis 
: 3. Caso seja possível, o movimento é realizado 
;=====================================================================================
; NOTAS TECNICAS
;=====================================================================================
;       Entradas: 
          1. Dados via bluetooh:
          
           BT           Arduino
           5V--------------5V
           RX--------------TX(D1)
           TX--------------RX(D0)
           GND-------------GND
           
          2. Botão descanso (Interrupção):
          
           Botão          Arduino
         Descanso-----------D2(Interrupção 0)
         
;       Saidas:
           Motor       Arduino
           Base-----------3 
           Sobe11---------5 
           Sobe12---------6
           Garra----------8 
           Sobe2----------9 
           Sobe3----------10 
           Giro-----------11 

;====================================================================================*/
#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

/*====================================================================================
; DEFINIÇÕES DE VARIÁVEIS DOS MOTORES
;====================================================================================*/
#include <Servo.h> 
Servo Base; 
Servo Sobe11; 
Servo Sobe12; 
Servo Sobe2; 
Servo Sobe3; 
Servo Giro; 
Servo Garra;

/*====================================================================================
; DEFINIÇÕES DE VARIÁVEIS POSIÇÃO 
;====================================================================================*/
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

/*====================================================================================
; DEFINIÇÕES DE VARIÁVEIS DE CONTROLE 
;====================================================================================*/
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
/*====================================================================================
; DEFINIÇÕES DE VARIÁVEIS DE CINEMATICA
;====================================================================================*/
double a1 = 22.25;
double a2 = 145;
double a3 = 180;
double a4 = 120;

float coordX;
float coordY;
float coordZ;

int Sp1 = 0;
int Sp2 = 0;
int Sp3 = 0;
int Sp4 = 0;
int Sp5 = 0;
int Sp6 = 0;
double pos1 = 0;
double pos2 = 0;
double pos3 = 0;
double pos4 = 0;
double pos5 = 0;
double pos6 = 0;

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
   attachInterrupt(0, Stop, RISING);  

}

void loop() {
    
  if(Serial.available()>0){
  
  leStringSerial();
  if(CalculoDireto(Basei,Sobe1i,Sobe2i,Sobe3i,Giroi) && Verificacao==true){
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
    Sobe11.write(posSobe11init+Sobe1int);
     Sobe12.write(posSobe12init-Sobe1int);
    Sobe2.write(posSobe2init+Sobe2int);
    Sobe3.write(posSobe3init+Sobe3int);
    //Serial.write('a');
    Verificacao=false;
   //  Giro.write(posGiroinit+Giroint);
    // Garra.write(posGarrainit+Garraint);
      /*deltaTempo();
      controlador1(Baseint);
      controlador2(Sobe1int);
      controlador3(Sobe2int);
      controlador4(Sobe3int);
      //controlador5(Giroi);
      //controlador6(Garrai);*/
     
    }
  }
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
}
/*====================================================================================
; FUNÇÃO PARA LER O PACOTE
;====================================================================================*/
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
/*====================================================================================
; FUNÇÃO PARA MULTIPLICAR MATRIZ
;====================================================================================*/
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
/*====================================================================================
;CALCULO DE CINEMATICA DIRETA
;====================================================================================*/
boolean CalculoDireto(float teta1,float teta2,float teta3,float teta4, double teta5){
 double A [4][4]={
  {cos(teta1), -sin(teta1), 0, 0},
  {sin(teta1), cos(teta1), 0, 0},
  {0, 0, 1.0, a1},
  {0,0, 0, 1.0},
  };
   
  double B [4][4]={
  {cos(teta2), 0, sin(teta2), 0},
  {0, 1.0, 0, 0},
  {-sin(teta2), 0, cos(teta2), 0},
  {0, 0, 0, 1.0},
  };
  
  double M01 [4][4]={// Essa é a Matrix M de 0 até 1
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  };
    
  mMatriz (A,B,M01);
  //Serial.println("Matriz M01");
  //imprimir(M01);
  
  double C [4][4]{
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,a2},
  {0,0,0,1.0},
  };
  
  double D [4][4]{
    {cos(teta3+HALF_PI), 0, sin(teta3+HALF_PI), 0},
    {0, 1.0, 0, 0},
    {-sin(teta3+HALF_PI), 0, cos(teta3+HALF_PI), 0},
    {0, 0, 0, 1.0},
  };
  double M12 [4][4]={// Essa é a Matrix M de 1 até 2
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  };
  mMatriz (C,D,M12);
  //Serial.println("Matriz M12");
  //imprimir(M12);
  
  double E [4][4]={
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,a3},
  {0,0,0,1.0},
  }; 
  
  double F [4][4]={
  {cos(teta4), 0, sin(teta4), 0},
  {0, 1.0, 0, 0},
  {-sin(teta4), 0, cos(teta4), 0},
  {0, 0, 0, 1},
  };
  double M23 [4][4]={// Essa é a Matrix M de 2 até 3
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  };
  
  mMatriz(E,F,M23);
  //Serial.println("Matriz M23");
  //imprimir(M23);
  
    
  double M02 [4][4]={ // Essa matriz calcula M de 3 até 4
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  };
    
  double M03 [4][4]={ // Essa matriz calcula M de 3 até 4
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  };
  mMatriz(M01,M12,M02);
  mMatriz(M02,M23,M03);
  
  double G [4][4]={
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,a4},
  {0,0,0,1.0},
  }; 
  
  double H [4][4]={
  {cos(teta5), -sin(teta5), 0, 0},
  {sin(teta5), cos(teta5), 0, 0},
  {0, 0, 1.0, 0},
  {0, 0, 0, 1.0},
  };
  
  double M34 [4][4]={ // Essa matriz calcula M de 3 até 4
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  };
  mMatriz(G,H,M34);
  //Serial.println("Matriz M34");
  //imprimir(M34);
  
  double M04 [4][4]={ // Essa matriz calcula M de 3 até 4
  {1.0,0,0,0},
  {0,1.0,0,0},
  {0,0,1.0,0},
  {0,0,0,1.0},
  };
  
  mMatriz(M03,M34,M04);
  //Serial.println("M04:");
  //imprimir(M04);
  
  coordX=M04[0][3];
  coordY=M04[1][3];
  coordZ=M04[2][3];
  //Serial.println(coordX);
  //Serial.println(coordY);
  //Serial.println(coordZ);
  if (coordZ<30){return false;}
  if(coordY>(115+a4)) {
  return true;}
  else {
    
  if(coordX>(115+a4)){ return true;}
  return false;
  }
  }
  void deltaTempo(){
  tempoAnterior = tempoAtual;
  tempoAtual = millis();
  dt = tempoAtual-tempoAnterior;
}
void controlador1(int Sp1){ 
  float erro1 = Sp1 - pos1;
  I1 =+ ki*erro1*dt; 
  pos1 = pos1 + Kp*erro1 + I1;
  Serial.println((int)pos1);
  Base.write(posBaseinit+(int)pos1);
}
void controlador2(int Sp2){ 
  float erro2 = Sp2 - pos2;
  I2 =+ ki*erro2*dt; 
  pos2 = pos2 + Kp*erro2 + I2;
  Serial.println(posSobe11init-(int)pos2);
  Serial.println(posSobe12init+(int)pos2);
  Sobe11.write(posSobe11init-(int)pos2);
  Sobe12.write(posSobe12init+(int)pos2);
}
void controlador3(int Sp3){ 
  float erro3 = Sp3 - pos3;
  I3 =+ ki*erro3*dt; 
  pos3 = pos3 + Kp*erro3 + I3;
  Serial.println(posSobe3init+(int)pos4);
  Sobe2.write(posSobe2init+(int)pos3);
}
void controlador4(int Sp4){ 
  float erro4 = Sp4 - pos4;
  I4 =+ ki*erro4*dt; 
  pos4 = pos4 + Kp*erro4 + I4;
  Serial.println(posSobe3init+(int)pos4);
  Sobe3.write(posSobe3init+(int)pos4);
}
void controlador5(int Sp5){ 
  float erro5 = Sp5 - pos5;
  I5 =+ ki*erro5*dt; 
  pos5 = pos5 + Kp*erro5 + I5;
  Serial.println(posGiroinit+(int)pos5);
  Giro.write(posGiroinit+(int)pos5);
}
void controlador6(int Sp6){ 
  float erro6 = Sp6 - pos6;
  I6 =+ ki*erro6*dt; 
  pos6 = pos6 + Kp*erro6 + I6;
  Serial.println(posGarrainit+(int)pos6);
  Giro.write(posGarrainit+(int)pos5);
}
void Stop(){
   stopbool= true;
  }
  

