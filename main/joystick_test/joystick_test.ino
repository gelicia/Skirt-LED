int xSensorPin = A1;
int ySensorPin = A0;
int selectButtonPin = 12;
int xSensorValue = 0;
int ySensorValue = 0;
//int selectButtonValue;
String outString = "";

void setup() {
  Serial.begin(9600); 
  pinMode(selectButtonPin, INPUT);
}

void loop() {
  outString = "";
  // read the value from the sensor:
   xSensorValue = analogRead(xSensorPin);    
   ySensorValue = analogRead(ySensorPin); 
   int selectButtonValue = digitalRead(selectButtonPin);
   
   if (xSensorValue < 20){
     outString = outString + "LEFT";
   }
   else if(xSensorValue > 1000){
     outString = outString + "RIGHT";
   }
   
   if (ySensorValue < 20){
     outString = outString + "DOWN";
   }
   else if(ySensorValue > 1000){
     outString = outString + "UP";
   }
   
   outString = outString + selectButtonValue;
   
  // String commaString = ", ";  
  //String serialString = xSensorValue + commaString + ySensorValue;*/
  Serial.println(outString);

  delay(50);
   
}
