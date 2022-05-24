#define BLYNK_TEMPLATE_ID "TMPLyZr4_5Go"
#define BLYNK_DEVICE_NAME "teste"
#define BLYNK_AUTH_TOKEN "89XdHUcZX7ZlpPvnVEKNKELLf1UxaBWo"
#define BLYNK_PRINT Serial

#include <NTPClient.h>

#include <WiFiUdp.h>

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include "BlynkSimpleEsp8266.h"

// Intanciar pinos do ESP8266
#define DHTPIN 2

//temperatura e umidade
#include "DHT.h"
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "br.pool.ntp.org", -10800.5, 60000);

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Teste";
char pass[] = "Jequitiba123501";



// DEFINAÇÃO DAS VARIÁVES (SENSOR DE CORRENTE)

int pino_sensor = A0;
int menor_valor;
int valor_lido;
int menor_valor_acumulado = 0;
int ZERO_SENSOR = 0;
float corrente_pico;
float corrente_eficaz;
double maior_valor = 0;
double corrente_valor = 0;

//Declaração dos pinos do reles
int rele1 = 16;
int rele2 = 5;
int rele3 = 4;
int rele4 = 0;
//int buzzer = 14;

int pos[4];

// definição das variáveis 
int error = 0;
int poserror = 0;
int tberror = 0;
int tbposerror = 0;

int westbutton = 0;
int eastbutton = 0;
int topbutton = 0;
int botbutton = 0;

int onoffswitch = 0;
int singledualswitch = 0;
int recordswitch = 0;
int controleManual = 1;
int record = 0;
int recordR[4];
int resetar = 0;

// definição dos sensores LDRs
int eldr = 14;
int wldr = 12;
int tldr = 13;
int bldr = 15;


int eastldr = 0;
int westldr = 0;
int topldr = 0;
int botldr = 0;


// Definição do tempo de rotação
int tempo = 1000;

void clearPlaca(double corrente){

    timeClient.update();
    int n = 0;
    String horario = timeClient.getFormattedTime();
    Serial.print(horario);
       
     topldr = analogRead(tldr);
     botldr = analogRead(bldr);
     eastldr = analogRead(eldr);
     westldr = analogRead(wldr);

     if((eastldr==0 && westldr==0 && topldr == 0 && botldr == 0)&& corrente<=0){
            if((horario>="05:00:00") && (horario<="23:00:00")&&(controleManual == 0) && (resetar == 0)){
          // Limpeza automática inicializada
              Serial.println("Limpeza automática inicializada");
              Blynk.logEvent("alerta_limpeza","Limpeza automática inicializada");
              Blynk.email("emaildousuarionoblynk@gmail.com", "Limpeza automática inicializada");
     }
   }
  
   delay(100);
}
  
// Programação do eixo único
void rastreamentoEixo1(){
  Serial.println("rastreamentoEixo1()");
  
    eastldr = digitalRead(14);
    Serial.print(eastldr);
    westldr = digitalRead(12);
    Serial.print(westldr);
    topldr = digitalRead(13);
    Serial.print(topldr);
    botldr = digitalRead(15);
    Serial.println(botldr);
    
   if((eastldr==0 && westldr==0 && topldr == 0 && botldr == 1)||(eastldr==0 && westldr==0 && topldr == 1 && botldr == 0)||
      (eastldr==0 && westldr==1 && topldr == 1 && botldr == 1)||(eastldr==1 && westldr==0 && topldr == 1 && botldr == 1)){
                if(pos[1]==0){
                  digitalWrite(rele1, HIGH);
                  digitalWrite(rele2, LOW);
                  pos[1] = 1;
                  pos[0] = 0;
                }
                delay(tempo);
                digitalWrite(rele1, HIGH);
                digitalWrite(rele2, HIGH);
          
        
      }else if ((eastldr==0 && westldr==1 && topldr == 0 && botldr == 0)||(eastldr==1 && westldr==0 && topldr == 0 && botldr == 0)||
               (eastldr==1 && westldr==1 && topldr == 0 && botldr == 1)||(eastldr==1 && westldr==1 && topldr == 1 && botldr == 0)){
                if(pos[0]==0){
                  digitalWrite(rele2, HIGH);
                  digitalWrite(rele1, LOW);
                  pos[0] = 1;
                  pos[1] = 0;
                }
                delay(tempo);
                digitalWrite(rele1, HIGH);
                digitalWrite(rele2, HIGH);
        
        }else if(eastldr==0 && westldr==0 && topldr == 1 && botldr == 1){
              if(pos[0]==0){
                  digitalWrite(rele2, HIGH);
                  digitalWrite(rele1, LOW);
                  pos[0] = 1;
                  pos[1] = 0;
                }
              delay(tempo);
              digitalWrite(rele1, HIGH);
              digitalWrite(rele2, HIGH);
            
        }else if(eastldr==1 && westldr==1 && topldr == 0 && botldr == 0){
                if(pos[0]==0){
                    digitalWrite(rele2, HIGH);
                    digitalWrite(rele1, LOW);
                    pos[0] = 1;
                    pos[1] = 0;
                  }
              delay(tempo);
              digitalWrite(rele1, HIGH);
              digitalWrite(rele2, HIGH);
            
       }else{
      digitalWrite(rele1, HIGH);
      digitalWrite(rele2, HIGH);
    }
}

  

void rastreamentoEixo2(){
  Serial.println("rastreamentoEixo2()");
  
    eastldr = digitalRead(14);
    Serial.print(eastldr);
    westldr = digitalRead(12);
    Serial.print(westldr);
    topldr = digitalRead(13);
    Serial.print(topldr);
    botldr = digitalRead(15);
    Serial.println(botldr);
    

        if((eastldr==0 && westldr==0 && topldr == 0 && botldr == 1)||(eastldr==0 && westldr==0 && topldr == 1 && botldr == 0)||
          (eastldr==0 && westldr==1 && topldr == 1 && botldr == 1)||(eastldr==1 && westldr==0 && topldr == 1 && botldr == 1)){
                if(pos[1]==0){
                  digitalWrite(rele1, HIGH);
                  digitalWrite(rele2, LOW);
                  pos[1] = 1;
                  pos[0] = 0;
                }
                if(pos[2]==0){
                    digitalWrite(rele4, HIGH);
                    digitalWrite(rele3, LOW);
                    pos[2] = 1;
                    pos[3] = 0;
                  }
                delay(tempo);
                digitalWrite(rele1, HIGH);
                digitalWrite(rele2, HIGH);
                digitalWrite(rele3, HIGH);
                digitalWrite(rele4, HIGH);
          
        
      }else if ((eastldr==0 && westldr==1 && topldr == 0 && botldr == 0)||(eastldr==1 && westldr==0 && topldr == 0 && botldr == 0)||
               (eastldr==1 && westldr==1 && topldr == 0 && botldr == 1)||(eastldr==1 && westldr==1 && topldr == 1 && botldr == 0)){
                if(pos[0]==0){
                  digitalWrite(rele2, HIGH);
                  digitalWrite(rele1, LOW);
                  pos[0] = 1;
                  pos[1] = 0;
                }
                  if(pos[3]==0){
                    digitalWrite(rele3, HIGH);
                    digitalWrite(rele4, LOW);
                    pos[3] = 1;
                    pos[2] = 0;
                  }
                delay(tempo);
                digitalWrite(rele1, HIGH);
                digitalWrite(rele2, HIGH);
                digitalWrite(rele3, HIGH);
                digitalWrite(rele4, HIGH);
        
        }else if(eastldr==0 && westldr==0 && topldr == 1 && botldr == 1){
              if(pos[0]==0){
                  digitalWrite(rele2, HIGH);
                  digitalWrite(rele1, LOW);
                  pos[0] = 1;
                  pos[1] = 0;
                }
              delay(tempo);
              digitalWrite(rele1, HIGH);
              digitalWrite(rele2, HIGH);
              digitalWrite(rele3, HIGH);
              digitalWrite(rele4, HIGH);
            
        }else if(eastldr==1 && westldr==1 && topldr == 0 && botldr == 0){
                if(pos[0]==0){
                    digitalWrite(rele2, HIGH);
                    digitalWrite(rele1, LOW);
                    pos[0] = 1;
                    pos[1] = 0;
                  }
              delay(tempo);
              digitalWrite(rele1, HIGH);
              digitalWrite(rele2, HIGH);
              digitalWrite(rele3, HIGH);
              digitalWrite(rele4, HIGH);
            
       }else if(eastldr==0 && westldr==1 && topldr == 0 && botldr == 1){
                if(pos[2]==0){
                    digitalWrite(rele4, HIGH);
                    digitalWrite(rele3, LOW);
                    pos[2] = 1;
                    pos[3] = 0;
                  }
              delay(tempo);
              digitalWrite(rele1, HIGH);
              digitalWrite(rele2, HIGH);
              digitalWrite(rele3, HIGH);
              digitalWrite(rele4, HIGH);
       }else if(eastldr==1 && westldr==0 && topldr == 1 && botldr == 0){
              if(pos[3]==0){
                  digitalWrite(rele3, HIGH);
                  digitalWrite(rele4, LOW);
                  pos[3] = 1;
                  pos[2] = 0;
                }
              delay(tempo);
              digitalWrite(rele1, HIGH);
              digitalWrite(rele2, HIGH);
              digitalWrite(rele3, HIGH);
              digitalWrite(rele4, HIGH);
      }else{
      digitalWrite(rele1, HIGH);
      digitalWrite(rele2, HIGH);
      digitalWrite(rele3, HIGH);
      digitalWrite(rele4, HIGH);
    }
}

// controle de tempo

BLYNK_WRITE(V12){  
  tempo = 0;
  int entradaT = param.asInt();
  tempo = entradaT*1000;  
  Serial.println(tempo);
}


// função que reseta as saídas dos motores
  void controlReset(){
     
      digitalWrite(rele1, recordR[0]);
      pos[0] = !recordR[0];
      digitalWrite(rele2, recordR[1]);
      pos[1] = !recordR[1];
      digitalWrite(rele3, recordR[2]);
      pos[2] = !recordR[2];
      digitalWrite(rele4, recordR[3]);
      pos[3] = !recordR[3];
      
      delay(tempo);
      
      for(int j = 0; j<4; j++){
        if(recordR[j]== 0){
          digitalWrite(rele1, HIGH);
          digitalWrite(rele2, HIGH);
          digitalWrite(rele3, HIGH);
          digitalWrite(rele4, HIGH);
          }
      }
      Serial.println("");
      delay(10);
  }
  

// Se botão1 for acionado
  BLYNK_WRITE(V1){
    int eastbutton = param.asInt();    
    if ((eastbutton == 1) && pos[0] == 0 && controleManual==1 && resetar == 0){ 
      digitalWrite(rele2, HIGH);
      digitalWrite(rele1, LOW);
      pos[0] = 1;
      pos[1] = 0;
      Serial.print(pos[0]);
      Serial.print(pos[1]);
      Serial.print(pos[2]);
      Serial.println(pos[3]);
      delay(tempo);
      digitalWrite(rele1, HIGH);
          } 
    else {
      digitalWrite(rele1, HIGH);      
    }
  }


   // Se botão2 for acionado
  BLYNK_WRITE(V2){
    int westbutton = param.asInt();
    if ((westbutton == 1)&& pos[1] ==0 && controleManual==1 && resetar == 0){ 
      digitalWrite(rele1, HIGH);
      digitalWrite(rele2, LOW);
      pos[1] = 1;
      pos[0] = 0;
      Serial.print(pos[0]);
      Serial.print(pos[1]);
      Serial.print(pos[2]);
      Serial.println(pos[3]);
      delay(tempo);
      digitalWrite(rele2, HIGH);
      
    } 
    else {
      digitalWrite(rele2, HIGH);
    }
  }
  
  // Se botão3 for acionado
  BLYNK_WRITE(V3){
    int topbutton = param.asInt();       
    if ((topbutton == 1)&& pos[2] == 0 && controleManual==1 && resetar == 0){ 
      digitalWrite(rele4, HIGH);
      digitalWrite(rele3, LOW);
      pos[2] = 1;
      pos[3] = 0;
      Serial.print(pos[0]);
      Serial.print(pos[1]);
      Serial.print(pos[2]);
      Serial.println(pos[3]);
      delay(tempo);
      digitalWrite(rele3, HIGH); 
    } 
    else {
      digitalWrite(rele3, HIGH);
    }
  }

BLYNK_WRITE(V4){
  //rotação automática do painel 
  //verifica primeiro a orientação leste-oeste
  
  int eixo = param.asInt();
  // re-leitura dos botões A-M-E1-E2
  while ((eixo == 1) && (controleManual == 0) && (resetar == 0)){
  
    Serial.println("Eixo 1 acionado");
    /*digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(100);*/
    rastreamentoEixo1();
 
  }
  while ((eixo == 0)&& (controleManual == 0) && (resetar == 0)){
    Serial.println("Eixo 2 acionado");
   /* digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(100);*/
    rastreamentoEixo2();
  }
}




 // Se botão4 for acionado
  BLYNK_WRITE(V0){
    int botbutton = param.asInt();
    if ((botbutton == 1)&& pos[3] ==0 && controleManual==1 && resetar == 0){ 
      digitalWrite(rele3, HIGH);
      digitalWrite(rele4, LOW);
      pos[3] = 1;
      pos[2] = 0;
      Serial.print(pos[0]);
      Serial.print(pos[1]);
      Serial.print(pos[2]);
      Serial.println(pos[3]);
      delay(tempo);
      digitalWrite(rele4, HIGH);
      
    } else {
      digitalWrite(rele4, HIGH);
    } 
  }

  BLYNK_WRITE(V9){  
  int c = param.asInt();
  if (c == 0){
    Serial.println("Controle manual acionado");
    controleManual = 1;
  }else{
    controleManual = 0;
    Serial.println("Controle automático acionado");
  }
}

BLYNK_WRITE(V10){  
  int gravar = param.asInt();
  if (gravar == 1){
    Serial.println("Gravação acionada");
    record=1;
    for(int i = 0; i<4; i++){
      recordR[i] = !pos[i];
      Serial.print(!recordR[i]); // em ordem inversa
    }
    Serial.println();
  }
}

BLYNK_WRITE(V11){  
  int iniciar = param.asInt();
  
  if(iniciar ==1){
    resetar = 1;
    if(recordR[0]==0 && recordR[1]==0 && recordR[2]==0 && recordR[3]==0){
        Serial.println("é igual");
    }
    
    else if (pos[0]==!recordR[0] && pos[1]==!recordR[1] && pos[2]==!recordR[2] && pos[3]==!recordR[3]){
      Serial.println("são iguais");
      }
    else{
      Serial.println("Sistema resetado para posição de limpeza");
      controlReset(); 
   }
  }else{
    resetar = 0;
  }
}


void setup(){
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timeClient.begin();

  //temperatura
  dht.begin();

  pinMode(pino_sensor, INPUT);
  delay(3000);
  
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT);
//  pinMode(buzzer, OUTPUT);

  digitalWrite(rele1 ,HIGH);
  digitalWrite(rele2 ,HIGH);
  digitalWrite(rele3 ,HIGH);
  digitalWrite(rele4 ,HIGH);

 // digitalWrite(buzzer ,LOW);
  pinMode (eldr, INPUT);
  pinMode (wldr, INPUT);
  pinMode (tldr, INPUT);
  pinMode (bldr, INPUT);

  Serial.println("Fazendo o Auto ZERO do Sensor...");

  menor_valor = 4095;

  for (int i = 0; i <10000; i++){
    valor_lido = analogRead(pino_sensor);
    if (valor_lido < menor_valor){
      menor_valor = valor_lido;
    }
    delayMicroseconds(1);
  }
  ZERO_SENSOR = menor_valor;
  Serial.print("zero do sensor:");
  Serial.println(ZERO_SENSOR);
  delay (10);
  
}




void loop(){

  Blynk.run();
  //temp
  float u = dht.readHumidity();
  Blynk.virtualWrite(V7, u);
  float t = dht.readTemperature();
  Blynk.virtualWrite(V5, t);

  if (isnan(u) || isnan(t)){
    Serial.println("Falha na leitura");
    return;
  }

  //Apresenta os dados d temperatura no serial
  Serial.print("Umidade: ");
  Serial.print(u);
  Serial.println(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" Celsius");
  
  menor_valor = 4095;

  for(int i = 0; i < 1600; i++){
    valor_lido = analogRead(pino_sensor);
    if (valor_lido <= menor_valor){
      menor_valor = valor_lido;
    }
    delayMicroseconds(10);
  }

  Serial.print("Menor Valor: ");
  Serial.println(menor_valor);

  corrente_pico = ZERO_SENSOR - menor_valor;
  corrente_pico = corrente_pico*0.805;
  corrente_pico = corrente_pico/185;

  Serial.print("Corrente de pico:");
  Serial.print(corrente_pico);
  Serial.print(" A");
  Serial.print(" --- ");
  Serial.print(corrente_pico*1000);
  Serial.println(" mA");

  corrente_eficaz = corrente_pico/1.4;
  Serial.print("Corrente Eficaz");
  Serial.print(corrente_eficaz);
  Serial.print(" A");
  Serial.print(" --- ");
  Serial.print(corrente_eficaz*1000);
  Serial.println(" mA");
  Blynk.virtualWrite(V8, corrente_pico*1000);

 clearPlaca(corrente_pico*1000);
  
  
  delay(10);
  
}
