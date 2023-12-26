#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Gree.h>

int basilan_tus     = 0;
int okunan_deger  = 0;
bool button = true;
const uint16_t IRLed = 14;
IRGreeAC ac(IRLed);
uint8_t temp = 25;
uint8_t fan = 0;
int analogValue = 0;
#define right     0
#define up  1
#define down   2
#define left    3
#define select    4
#define none     5


void printState() {
  // Display the settings.
  Serial.println("GREE A/C remote is in the following state:");
  Serial.printf("  %s\n", ac.toString().c_str());
  // Display the encoded IR sequence.
  unsigned char* ir_code = ac.getRaw();
  Serial.print("IR Code: 0x");
  for (uint8_t i = 0; i < kGreeStateLength; i++)
    Serial.printf("%02X", ir_code[i]);
  Serial.println();
}


byte buttonPress()
{
  analogValue = analogRead(2);
  
  if (analogValue < 100)
    return right; 
    
  if (analogValue < 1000)
    return up; 
  if (analogValue < 1300)
    return down; 
  if (analogValue < 1600)
    return left; 
  if (analogValue  < 2000)
    return select; 
  if (analogValue  > 2000)
    return none; 
}

void tempset(uint8_t value) {
  temp = temp + value;
  if(temp > 30) {
    temp = 30;
  } else if (temp < 16) {
    temp = 16;
  }
  ac.setTemp(temp);
  ac.send();
}

void fanset(uint8_t value) {
  fan = fan + value;
  if(fan > 3) {
    fan= 3;
  } else if (fan < 0) {
    fan = 0;
  }
  ac.setFan(fan);
  ac.send();
}

void onOFF() {

  
  
  if (buttonPress() == select){
    button = !button;
    if(!button) {
      ac.on();
      ac.send();
    } else {
      ac.off();
      ac.send();
    }
  }
  delay(100);
  
  
}



                                
void setup()
{
  ac.begin();
  Serial.begin(115200);
  delay(200);
  Serial.println("Default state of the remote.");
  printState();
  Serial.println("Setting desired state for A/C.");
  ac.setFan(0);
  // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
  ac.setMode(kGreeHeat);
  ac.setTemp(temp);  // 16-30C
  ac.setSwingVertical(false, kGreeSwingAuto);
  ac.setXFan(false);
  ac.setLight(true);
  ac.setSleep(false);
  ac.setTurbo(false);
}

void loop()
{

  while(button) {
    onOFF();
  } 
  onOFF();
  
  switch(buttonPress()) {
    case left:
      fanset(-1);
    break;
    case right:
      fanset(+1);
    break;
    case up:
      tempset(+1);
    break;
    case down:
      tempset(-1);
    break;
  }
  printState();
  Serial.println(temp);
  Serial.println(fan);
  Serial.println(button);
  delay(10);
  }
