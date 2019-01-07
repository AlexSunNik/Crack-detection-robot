#include <Servo.h>
#define collectTimes 3
#define errorThreshold 10
//Initialize some variables

int theta;
int trigPin1=3;
int echoPin1=2;
int trigPin2=5;
int echoPin2=4;
int trigPin3=7;
int echoPin3=6;
int trigPin4=9;
int echoPin4=8;

int sen1LED=A0;
int sen2LED=A1;
int sen3LED=A3;
int sen4LED=A4;

int finiLED=A5;

unsigned short int sense1[90*collectTimes];
unsigned short int sense2[90*collectTimes];
unsigned short int sense3[90*collectTimes];
unsigned short int sense4[90*collectTimes];

Servo servo;
unsigned short int  duration, distance, cm1, cm2, cm3, cm4;
unsigned short int  prev1,prev2,prev3,prev4;
short int diff1,diff2,diff3,diff4;

void setup()
  {
    Serial.begin(9600);
    
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    
    pinMode(trigPin3, OUTPUT);
    pinMode(echoPin3, INPUT);
    
    pinMode(trigPin4, OUTPUT);
    pinMode(echoPin4, INPUT);

    pinMode(sen1LED, OUTPUT);
    pinMode(sen2LED, OUTPUT);
    pinMode(sen3LED, OUTPUT);
    pinMode(sen4LED, OUTPUT);

    pinMode(finiLED, OUTPUT);
  
    servo.attach(12);
  }

void loop()
{
    digitalWrite(finiLED, LOW);
    delay(5000);
    
    for(theta=0;theta<90; theta++)
      {
        servo.write(theta);

        prev1=prev2=prev3=prev4=0;
        
        for(int i=0;i<collectTimes;i++)
        {
          collectData(i,theta);
          
          if(i>=1)
          {
            workingProper(prev1,prev2,prev3,prev4,cm1,cm2,cm3,cm4);
          }
          
          prev1=cm1;
          prev2=cm2;
          prev3=cm3;
          prev4=cm4;

          delay(50);         
        }
      }
      
     printData();
}

  
float Ultrasensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  
  duration=pulseIn(echoPin, HIGH);
  distance=(duration/2)/29.1;
  
  return distance;
}


void workingProper(int prev1, int prev2, int prev3, int prev4, int cm1, int cm2, int cm3, int cm4)
{
  diff1=prev1-cm1;
  diff2=prev2-cm2;
  diff3=prev3-cm3;
  diff4=prev4-cm4;

  if(diff1>=errorThreshold||diff1<=(-errorThreshold))
  {
    digitalWrite(sen1LED,LOW);
  }
  else
  {
    digitalWrite(sen1LED,HIGH);
  }
  
  if(diff2>=errorThreshold||diff2<=(-errorThreshold))
  {
    digitalWrite(sen2LED,LOW);
  }
  else
  {
    digitalWrite(sen2LED,HIGH);
  }
  
  if(diff3>=errorThreshold||diff3<=(-errorThreshold))
  {
    digitalWrite(sen3LED,LOW);
  }
  else
  {
    digitalWrite(sen3LED,HIGH);
  }
  
  if(diff4>=errorThreshold||diff4<=(-errorThreshold))
  {
    digitalWrite(sen4LED,LOW);
  }
  else
  {
    digitalWrite(sen4LED,HIGH);
  }
  
}

void collectData(int i,int theta)
{
  int j=theta*collectTimes+i;
  
  cm1=Ultrasensor(trigPin1, echoPin1);
  cm2=Ultrasensor(trigPin2, echoPin2);
  cm3=Ultrasensor(trigPin3, echoPin3);
  cm4=Ultrasensor(trigPin4, echoPin4);
  
  sense1[j]=cm1;
  sense2[j]=cm2;
  sense3[j]=cm3;
  sense4[j]=cm4;
}

void printData()
{
  for(int i=0; i<90 ; i++)
     {
        for(int j=0;j<collectTimes;j++)
        {
          Serial.print(sense1[i*collectTimes+j]);
          Serial.println();
          delay(30);         
        }
     }
     for(int i=0; i<90 ; i++)
     {
        for(int j=0;j<collectTimes;j++)
        {
          Serial.print(sense2[i*collectTimes+j]);
          Serial.println();
          delay(30);         
        }
     }
     for(int i=0; i<90 ; i++)
     {
        for(int j=0;j<collectTimes;j++)
        {
          Serial.print(sense3[i*collectTimes+j]);
          Serial.println();
          delay(30);         
        }
     }
     for(int i=0; i<90 ; i++)
     {
        for(int j=0;j<collectTimes;j++)
        {
          Serial.print(sense3[i*collectTimes+j]);
          Serial.println();
          delay(30);         
        }
     }
     digitalWrite(finiLED, HIGH);
}
