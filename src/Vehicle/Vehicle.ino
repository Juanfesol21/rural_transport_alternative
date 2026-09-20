
int sensorPin = A0;
int lightValue = 0;  
int EnA = 10;
int EnB = 11;
int Speed = 120;
bool MaxSpeed= false;
void setup() {
  Serial.begin(9600); 
  pinMode(12,OUTPUT); //All pins should be output as they send energy
  pinMode(13,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(EnA,OUTPUT);
  pinMode(EnB,OUTPUT);
}

void loop() {
  lightValue = analogRead(sensorPin); //Reads value from 0 a 1023
  Serial.println (lightValue);
  if (lightValue < 700) //Defines value of light which tells wether motors should be working or not 
  {
    digitalWrite (12, HIGH);
    digitalWrite (13, LOW);
    digitalWrite (6, HIGH);
    digitalWrite (7, LOW);
    if (MaxSpeed == false)
   { 
      analogWrite (EnA, 250);//Short impulse for motors to start
      analogWrite (EnB, 250);
      delay (100);
      analogWrite (EnA, Speed);
      analogWrite (EnB, Speed);
      delay (100);
      Speed = Speed + 100;
      if (Speed >= 225) //For keeping it until light is received
      { 
        Speed = 225;
        analogWrite (EnA, Speed);
        analogWrite (EnB, Speed);
        MaxSpeed = true;
      }
    }
    
  } else {
    analogWrite(EnA, 95);//Gradual velocity reduction
    analogWrite(EnB, 95);
    delay (150);
    analogWrite(EnA, 50);
    analogWrite(EnB, 50);
    delay(150);
    analogWrite(EnA, 5);
    analogWrite(EnB, 5);
              
    MaxSpeed = false;    //Resets condition for the loop
    delay(5000);
    
   
  } 
}