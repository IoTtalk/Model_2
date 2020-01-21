#include <Bridge.h>
#define BugPin1       2   //蟲罐      
#define BugPin2       3   //蟲罐      

int BugCounter = 0;
int BugPin1state = 0;

long suspendTimestamp = millis();
void blink1(){//BugPin1
    //Serial.println("Bug Pin1 triggered.");    
    BugPin1state = 1;
}

void blink2(){//BugPin2
    //Serial.println("Bug Pin2 triggered.");    
    if (BugPin1state != 1) return;
    if (millis()-suspendTimestamp > 500){
        BugCounter += 1;
        BugPin1state = 0;
        suspendTimestamp = millis();
    }
    else{
        suspendTimestamp = millis();
    }
}

void setup() {
    pinMode(BugPin1, INPUT_PULLUP);
    pinMode(BugPin2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BugPin1), blink1, RISING);    //BugPin register to Interrupt
    attachInterrupt(digitalPinToInterrupt(BugPin2), blink2, RISING);    //BugPin register to Interrupt
    
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
