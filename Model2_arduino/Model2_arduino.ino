#include <Bridge.h>
#define UVpin        A0  //UV        
#define LUXpin       A1  //照度      
#define pHpin        A2  //土壤酸鹼  
#define MoisturePin  A3  //土壤濕度  
#define SoilTEMPpin  A4  //土壤溫度
#define SoilECpin    A5  //EC
#define BugPin       7   //蟲罐      

int BugCounter = 0;
long suspendTimestamp = millis();
void blink(){//Bugs
    if (millis()-suspendTimestamp > 180000){
        BugCounter += 1;
        suspendTimestamp = millis();
        Serial.println("Pest detected.");
    }
}

void setup() {
    pinMode(UVpin,INPUT);
    pinMode(LUXpin,INPUT);
    pinMode(pHpin,INPUT); 
    pinMode(MoisturePin,INPUT);
    pinMode(SoilTEMPpin,INPUT); 
    pinMode(SoilECpin,INPUT);
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

    const char *DFname[]={"UV1","UV2","pH1","Moisture1","SoilTemp-I","SoilEC-I"};
    const int pinNum[]={UVpin, LUXpin, pHpin, MoisturePin, SoilTEMPpin, SoilECpin};
    for(int i=0;i<=5;i++){
        valueInt = analogRead(pinNum[i]);     
        Serial.print(DFname[i]); Serial.print(": ");  Serial.println(valueInt);   
        itoa(valueInt, valueStr, 10); 
        Bridge.put(DFname[i], valueStr); 
    }
    
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
    delay(10000);
}
