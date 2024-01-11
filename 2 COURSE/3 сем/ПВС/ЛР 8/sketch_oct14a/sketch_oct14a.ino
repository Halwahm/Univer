#define RED 12
#define YEL 11
#define GRN 10
int state = 0;
char mode;
void setup() {
 pinMode(RED, OUTPUT);
 pinMode(YEL, OUTPUT);
 pinMode(GRN, OUTPUT);
 Serial.begin(9600);
}
void loop() {
 while(Serial.available() > 0){
  char readChar = Serial.read();
   switch(toupper(readChar)){
     case 'N':{
       Serial.println("Светофор работает в режиме normal");
       state = 1;
       mode = 'N';
       break;
     }
     case 'S':{
       Serial.println("Светофор работает в режиме sleep");
       state = 2;
       mode = 'S';
       break;
     }
     case 'R':{
       Serial.println("Светофор работает в режиме red");
       mode = 'R';
       break;
      }
       case 'G':{
       Serial.println("Светофор работает в режиме green");
       mode = 'G';
       break;
     }
   }
 }
 switch(mode){
   case 'N': normalMode(); break;
   case 'S': sleepMode(); break;
   case 'R': {
     state = 1;
     setLight();
 break;
   }
   case 'G': {
     state = 3;
     setLight();
 break;
   }
}
 delay(1000);
}

void normalMode(){
 setLight();
 state == 3 ? state = 1 : state++;
}

void sleepMode(){
 digitalWrite(RED, LOW);
 state == 2 ? state = 0 : state = 2;
 setLight();
 digitalWrite(GRN, LOW);
}

void setLight(){
 state == 1 ? digitalWrite(RED, HIGH) : digitalWrite(RED, LOW);
 state == 2 ? digitalWrite(YEL, HIGH) : digitalWrite(YEL, LOW);
 state == 3 ? digitalWrite(GRN, HIGH) : digitalWrite(GRN, LOW);
}