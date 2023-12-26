#include <SoftwareSerial.h>
#define SIM800L_IP5306_VERSION_20200811
SoftwareSerial mySIM(26, 27);
#define DUMP_AT_COMMANDS
#define TINY_GSM_DEBUG SerialMon
#include "utilities.h"
#define SerialMon Serial1
#define SerialAT Serial2
#define TINY_GSM_MODEM_SIM800    // Modem is SIM800
#define TINY_GSM_RX_BUFFER 1024  // Set RX buffer to 1Kb
#include <TinyGsmClient.h>
#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif
 #define SMS_TARGET "+528713659940"
void setup_sms() {
   mySIM.begin(9600); 
  if (setupPMU() == false) {
    Serial.println("Setting power error");
  }
  setupModem();
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
}

void loop_sms(){
   while (mySIM.available()) {
    Serial.write(mySIM.read());
  }
}

void updateSerial() {
  while (mySIM.available())  {
    String mge = mySIM.readStringUntil('\n');
    Serial.println(mge);
  }
}

// void send_sms2(String num, String txt) {
//   Serial.println("Sending SMS...");
//   mySIM.print("AT+CMGF=1\r");
//   updateSerial();
//   Serial.println(num);
//   num = "\"" + num + "\"";
//   mySIM.print("AT+CMGS=" + num + "\r");
//   updateSerial();
//    delay(500);
//   mySIM.print(txt);
//    delay(500);
//   mySIM.print((char)26);
//    delay(500);
//   mySIM.println();
//    delay(500);
//   Serial.println("Text Sent.");
// }
void send_sms(String num, String mensaje, int intentos) {
  Serial.println("Lanzando mensaje");
  Serial.println(mensaje);
  digitalWrite(13,HIGH);
  modem.restart();
  bool res = modem.sendSMS(num, mensaje);
  DBG("SMS:", res ? "OK" : "fail");
  
  Serial.println(res);
  if(res == 0 && intentos < 2){
    intentos = intentos + 1;
    send_sms(num, mensaje, intentos);
  }
  digitalWrite(12,HIGH);
  delay(2000);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
}