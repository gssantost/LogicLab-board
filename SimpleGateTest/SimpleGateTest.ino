#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define TX 10
#define RX 11

char ch = ' ';
int TEST_VALUE;
int pinArray[4] = { 2, 3, 4, 5 };

SoftwareSerial BTSerial(TX, RX);

// Probanado con cuatro pines (dos inversores) del 74ls04
const char* json = "{\"pinNo\":4,\"config\":\"OIOIOIOIOIOIOO\"}"; 
const int capacity = JSON_OBJECT_SIZE(2);

void setup() {

  // Set baud-rate para HC-05
  //BTSerial.begin(9600);
  
  Serial.begin(9600);
  Serial.println("ARDUINO is listening...");
  
}

void loop() {

  /*
   * 
  if (BTSerial.available()) {
    // do same algorithm but reading JSON from remote app... and STUFF
  }
  */

  if (Serial.available()) {
    ch = Serial.read();

    if (ch == '0') {
      simpleTest(pinArray, LOW);
    }
    else if (ch == '1') {
      simpleTest(pinArray, HIGH);
    }
    
    
  } // end of Serial.available()

  delay(1000);
  
}

void simpleTest(int pinArray[4], int testValue) {
    DynamicJsonBuffer jsonBuffer(capacity);
    JsonObject& obj = jsonBuffer.parseObject(json);
      
    if (obj.success()) {
      const int pinNo = obj["pinNo"];
      const char* pinConfig = obj["config"];

      /*switch(ch) {
        case '0': TEST_VALUE = LOW; break;
        case '1': TEST_VALUE = HIGH; break;
      }*/

      for (int i = 0; i < pinNo; i++) {
        if (pinConfig[i] == 'I') {
          pinMode(pinArray[i], INPUT);
          Serial.print("Pin ["); Serial.print(pinArray[i]); Serial.println("] configurado como ENTRADA.");
        } else if (pinConfig[i] == 'O') {
          pinMode(pinArray[i], OUTPUT);
          digitalWrite(pinArray[i], testValue);
          Serial.print("Pin ["); Serial.print(pinArray[i]); Serial.print("] configurado como SALIDA. ");
          Serial.print("Valor de prueba: "); Serial.println(testValue);
        }
      }

      for (int i = 0; i < pinNo; i++) {
        if (pinConfig[i] == 'I') {
          Serial.print("Valor leído en Pin ["); Serial.print(pinArray[i]); Serial.print("] es: "); 
          //delay(1000);
          Serial.println(digitalRead(pinArray[i]));
        }
      }
    }
    else {
      Serial.println("JSON not parsed");  
    }
}
