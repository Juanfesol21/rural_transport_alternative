
const int Trig = 4;
const int Echo = 5;
const int pinSalida = 12; 
int duracion;
int distancia;

void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT); //This one sends 
  pinMode(Echo, INPUT);//This one receives data
  pinMode(pinSalida, OUTPUT); 
}

void loop() {
  // Trig pulse
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  
  // Measure of time in microseconds
  duracion = pulseIn(Echo, HIGH); 
  
  // Calculates distance
  distancia = duracion * 0.0343 / 2; //343 represents sound speed on air in m/s
  
  // Monitoring :)
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  
  // Conditional
  if (distancia <= 5 && distancia > 0) { 
    digitalWrite(pinSalida, HIGH); 
    delay (3000);
    digitalWrite(pinSalida, LOW);
  } 
  else {
    digitalWrite(pinSalida, LOW);  
   }
  // Prevention delay
  delay(100);
}

