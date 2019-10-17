#include <Bridge.h>
#define BugPin       7   //蟲罐      

int BugCounter = 0;
long suspendTimestamp = millis();
void blink(){//Bugs
    if (millis()-suspendTimestamp > 1000){
        BugCounter += 1;
        suspendTimestamp = millis();
        Serial.println("Pest detected.");
    }
    else{
        suspendTimestamp = millis();
        Serial.println("under counting time, reset counter time.");
    }
}

void setup() {
    pinMode(BugPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BugPin), blink, RISING);    //BugPin register to Interrupt
    
    Serial.begin(115200);
    Bridge.begin();   // D0 and D1 are used by the Bridge library.
    //IoTtalk successful registration notification
    pinMode(13,OUTPUT);    
}

void loop() {
    char valueStr[23];
    int  valueInt=0;
    
    Bridge.get("Reg_done",  valueStr, 2);
    digitalWrite(13, atoi(valueStr));      
   
    itoa(BugCounter, valueStr, 10);
    Bridge.put("Bugs", valueStr);
    Serial.print("Bugs counter: ");    Serial.println(BugCounter);    

    Bridge.get("resetCounter",  valueStr, 5);
    if (strcmp(valueStr,"") != 0){
        BugCounter = 0;
        Serial.println("Reset bug's counter.");
        Bridge.put("resetCounter", "");
    }

    Serial.println("    ");
    delay(1000);
}
