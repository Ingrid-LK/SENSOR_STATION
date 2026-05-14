




int photoPin = 32;
void setup() {
  // put your setup code here, to run once:

//pinMode(photoPin, INPUT); //yellow not needed since pinMode is only for digital pins
  
Serial.begin(115200);


}


void loop() {
  // put your main code here, to run repeatedly:
  int light = analogRead(photoPin);

  Serial.println(light);
  
  delay(1000);


  //MISSSING VALUE MAP 
  //OF THE FINAL VALUE 
//SO YOU CAN TRIGGER TURN OFF THE LIGHTS OR SOMETHING LIKE THAT
// also dont know if i will just output a state like (good light, acceptable and bad light) 
//instead of proper value 
  
}