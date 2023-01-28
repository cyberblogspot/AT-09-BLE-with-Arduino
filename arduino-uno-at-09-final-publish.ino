/* cyberblogspot.com 21Jan2023
 *  
 * Program to send AT commands to AT-09 BLE module
 * and display the responses on the Serial Monitor
 * 
 * RX and TX cross wired 
 * 2k and 3k voltage divider on AT-09 RX (reduce 5V to 3V)
 */

#include <SoftwareSerial.h>
SoftwareSerial bleSerial(2, 3); //D2 is RX, D3 is TX

char bleData;  //storage for AT-09 data   
String mData;  //storage for AT-09 and serial monitor data

void setup() {
  Serial.begin(115200);   //initialize serial monitor
  bleSerial.begin(9600);  //and BLE serial port, default AT-09 baud rate is 9600 baud

  pinMode(13, OUTPUT);    //set D13 as output where built-in LED is connected
  digitalWrite(13, LOW);  //initially turn off LED
  
  Serial.println("AT-09 BLE module ready");
}

void loop() {
  if (Serial.available()) {      
    mData = Serial.readString(); //read serial monitor input
    Serial.println(mData);       //echo keyboard input to serial monitor
    bleSerial.println(mData);    //send keyboard input to AT-09 module
  }

  bleSerial.listen();                  //listen to the AT-09 port
  while (bleSerial.available() > 0) {  //if AT-09 data available
    bleData = bleSerial.read();        //read character and
    mData = String(bleData);           //convert to string format 
    Serial.print(mData);               //display to serial monitor
  }
  
  if (mData == "0") {
    digitalWrite(13, LOW);   //turn off LED
  }

  if (mData == "1") {
    digitalWrite(13, HIGH);  //turn on LED
  } 
}
