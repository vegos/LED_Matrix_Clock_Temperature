#include <MaxMatrix.h>            // Library http://code.google.com/p/arudino-maxmatrix-library/source/browse/MaxMatrix/
#include <avr/pgmspace.h>
#include "DHT.h"
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <EEPROM.h>
#include <MANCHESTER.h>



PROGMEM prog_uchar CH[] = {
3, 8, B0000000, B0000000, B0000000, B0000000, B0000000,   // space
1, 8, B1011111, B0000000, B0000000, B0000000, B0000000,   // !
3, 8, B0000011, B0000000, B0000011, B0000000, B0000000,   // "
5, 8, B0010100, B0111110, B0010100, B0111110, B0010100,   // #
4, 8, B0100100, B1101010, B0101011, B0010010, B0000000,   // $
5, 8, B1100011, B0010011, B0001000, B1100100, B1100011,   // %
5, 8, B0110110, B1001001, B1010110, B0100000, B1010000,   // &
1, 8, B0000011, B0000000, B0000000, B0000000, B0000000,   // '
3, 8, B0011100, B0100010, B1000001, B0000000, B0000000,   // (
3, 8, B1000001, B0100010, B0011100, B0000000, B0000000,   // )
5, 8, B0101000, B0011000, B0001110, B0011000, B0101000,   // *
5, 8, B0001000, B0001000, B0111110, B0001000, B0001000,   // +
2, 8, B10110000, B1110000, B0000000, B0000000, B0000000,  // ,
4, 8, B0001000, B0001000, B0001000, B0001000, B0000000,   // -
2, 8, B1100000, B1100000, B0000000, B0000000, B0000000,   // .
4, 8, B1100000, B0011000, B0000110, B0000001, B0000000,   // /
4, 8, B0111110, B1000001, B1000001, B0111110, B0000000,   // 0
3, 8, B1000010, B1111111, B1000000, B0000000, B0000000,   // 1
4, 8, B1100010, B1010001, B1001001, B1000110, B0000000,     // 2
4, 8, B0100010, B1000001, B1001001, B0110110, B0000000,   // 3
4, 8, B0011000, B0010100, B0010010, B1111111, B0000000,   // 4
4, 8, B0100111, B1000101, B1000101, B0111001, B0000000,   // 5
4, 8, B0111110, B1001001, B1001001, B0110000, B0000000,   // 6
4, 8, B1100001, B0010001, B0001001, B0000111, B0000000,   // 7
4, 8, B0110110, B1001001, B1001001, B0110110, B0000000,   // 8
4, 8, B0000110, B1001001, B1001001, B0111110, B0000000,   // 9
1, 8, B0100100, B00000000, B0000000, B0000000, B0000000,  // :
2, 8, B10000000, B01010000, B0000000, B0000000, B0000000, // ;
3, 8, B0010000, B0101000, B1000100, B0000000, B0000000,   // <
3, 8, B0010100, B0010100, B0010100, B0000000, B0000000,   // =
3, 8, B1000100, B0101000, B0010000, B0000000, B0000000,   // >
4, 8, B0000010, B1011001, B0001001, B0000110, B0000000,   // ?
5, 8, B0111110, B1001001, B1010101, B1011101, B0001110,   // @
4, 8, B1111110, B0010001, B0010001, B1111110, B0000000,   // A
4, 8, B1111111, B1001001, B1001001, B0110110, B0000000,   // B
5, 8, B0000111, B0001000, B1111110, B0001000, B0000111,   // Ψ
5, 8, B1111000, B1000110, B1000001, B1000110, B1111000,   // Δ
4, 8, B1111111, B1001001, B1001001, B1000001, B0000000,   // E
5, 8, B0000110, B1001001, B1111111, B0001001, B0000110,   // Φ
4, 8, B1111111, B0000001, B0000001, B0000001, B0000000,   // Γ
4, 8, B1111111, B0001000, B0001000, B1111111, B0000000,   // H
3, 8, B1000001, B1111111, B1000001, B0000000, B0000000,   // I
4, 8, B1000001, B1001001, B1001001, B1000001, B0000000,   // Ξ
4, 8, B1111111, B0001000, B0010100, B1100011, B0000000,   // K
5, 8, B1111000, B0000110, B0000001, B0000110, B1111000,   // Λ
5, 8, B1111111, B0000010, B0001100, B0000010, B1111111,   // M
5, 8, B1111111, B0000100, B0001000, B0010000, B1111111,   // N
4, 8, B0111110, B1000001, B1000001, B0111110, B0000000,   // O
4, 8, B1111111, B0000001, B0000001, B1111111, B0000000,   // Π
3, 8, B0000110, B0001001, B0000110, B0000000, B0000000,   // Degree
4, 8, B1111111, B0001001, B0001001, B0000110, B0000000,   // Ρ
5, 8, B1000001, B1100011, B1010101, B1001001, B1000001,   // Σ
5, 8, B0000001, B0000001, B1111111, B0000001, B0000001,   // T
4, 8, B0111110, B1001001, B1001001, B0111110, B0000000,   // Θ
5, 8, B1001110, B1010001, B1010001, B1010001, B1001110,   // V
4, 8, B0111110, B1000001, B1000001, B0100010, B0000000,   // C
5, 8, B1100011, B0010100, B0001000, B0010100, B1100011,   // X
5, 8, B0000111, B0001000, B1110000, B0001000, B0000111,   // Y
4, 8, B1100001, B1010001, B1001001, B1000111, B0000000,   // Z
2, 8, B1111111, B1000001, B0000000, B0000000, B0000000,   // [
4, 8, B0000001, B0000110, B0011000, B1100000, B0000000,   // backslash
2, 8, B1000001, B1111111, B0000000, B0000000, B0000000,   // ]
3, 8, B0000010, B0000001, B0000010, B0000000, B0000000,   // hat
4, 8, B1000000, B1000000, B1000000, B1000000, B0000000,   // _
2, 8, B0000001, B0000010, B0000000, B0000000, B0000000,   // `
4, 8, B0100000, B1010100, B1010100, B1111000, B0000000,   // a
4, 8, B1111111, B1000100, B1000100, B0111000, B0000000,   // b
4, 8, B0111000, B1000100, B1000100, B0101000, B0000000,   // c
4, 8, B0111000, B1000100, B1000100, B1111111, B0000000,   // d
4, 8, B0111000, B1010100, B1010100, B0011000, B0000000,   // e
3, 8, B0000100, B1111110, B0000101, B0000000, B0000000,   // f
4, 8, B10011000, B10100100, B10100100, B01111000, B0000000, // g
4, 8, B1111111, B0000100, B0000100, B1111000, B0000000,   // h
3, 8, B1000100, B1111101, B1000000, B0000000, B0000000,   // i
4, 8, B1000000, B10000000, B10000100, B1111101, B0000000, // j
4, 8, B1111111, B0010000, B0101000, B1000100, B0000000,   // k
3, 8, B1000001, B1111111, B1000000, B0000000, B0000000,   // l
5, 8, B1111100, B0000100, B1111100, B0000100, B1111000,   // m
4, 8, B1111100, B0000100, B0000100, B1111000, B0000000,   // n
4, 8, B0111000, B1000100, B1000100, B0111000, B0000000,   // o
4, 8, B11111100, B0100100, B0100100, B0011000, B0000000,  // p
4, 8, B0011000, B0100100, B0100100, B11111100, B0000000,  // q
4, 8, B1111100, B0001000, B0000100, B0000100, B0000000,   // r
4, 8, B1001000, B1010100, B1010100, B0100100, B0000000,   // s
3, 8, B0000100, B0111111, B1000100, B0000000, B0000000,   // t
4, 8, B0111100, B1000000, B1000000, B1111100, B0000000,   // u
5, 8, B0011100, B0100000, B1000000, B0100000, B0011100,   // v
5, 8, B0111100, B1000000, B0111100, B1000000, B0111100,   // w
5, 8, B1000100, B0101000, B0010000, B0101000, B1000100,   // x
4, 8, B10011100, B10100000, B10100000, B1111100, B0000000, // y
3, 8, B1100100, B1010100, B1001100, B0000000, B0000000,   // z
3, 8, B0001000, B0110110, B1000001, B0000000, B0000000,   // {
1, 8, B1111111, B0000000, B0000000, B0000000, B0000000,   // |
3, 8, B1000001, B0110110, B0001000, B0000000, B0000000,   // }
4, 8, B0001000, B0000100, B0001000, B0000100, B0000000,   // ~
};

#define DHTPIN         7      // DATA pin on DHT11
#define DHTTYPE    DHT11      // Type of DHT

DHT dht(DHTPIN, DHTTYPE);

#define DataPin       11      // To DATA on MAXIM 7219
#define LoadPin       10      // To LOAD on MAXIM 7219
#define ClockPin       9      // To CLK on on MAXIM 7219
#define ButtonPin     A0      // Button for setting the brightness of the matrix(es).
#define BuzzerPin     A1      // Buzzer :)

#define LEDPin        13      // LED 
#define TXPin          5      // Pin used for 433MHz TX Module (Data)

#define PIRSensor      6      // Pin for PIR Sensor

#define SensorNumber   5      // Sensor ID for transmitting messages
#define SensorType     1      // 1 for Temp/Hum
#define TotalMatrixes  3      //change this variable to set how many MAX7219's you'll use

MaxMatrix TheMatrix(DataPin, LoadPin, ClockPin, TotalMatrixes);

int Humidity = 0;
int Temperature = 0;
int Intensity = 0;
long UpdateTempMillis, TransmitMillis;
int DisplayDate = 0;
int DisplayHum = 0;

int Speeeeeed = 65;            // Scrolling Speed

byte buffer[10];               // Buffer used for transfering stored data from PROGMEM

long StartMillis;              // Keep current millis 
int DisplayTime = 5;           // Minutes to display when PIR detects movement
boolean DisplayIsOn = true;    // Display or not on the LED matrix


void setup()
{
  pinMode(ButtonPin, INPUT_PULLUP);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(PIRSensor, INPUT);
  pinMode(LEDPin, OUTPUT);
  pinMode(TXPin, OUTPUT);  
  setSyncProvider(RTC.get);
  MANCHESTER.SetTxPin(TXPin);
  Intensity=EEPROM.read(0);;
  TheMatrix.init();
  TheMatrix.setIntensity(Intensity);            // 0 - 15
  Humidity = dht.readHumidity();
  Temperature = dht.readTemperature();
  SendMessage();
  UpdateTempMillis=millis();
  TransmitMillis=millis();
  Serial.begin(9600);
  digitalWrite(BuzzerPin, HIGH);
  delay(100);
  digitalWrite(BuzzerPin, LOW);
  for (int i=0; i<5; i++)
  {
    digitalWrite(LEDPin, HIGH);
    delay(50);
    digitalWrite(LEDPin, LOW);
    delay(50);
  }
  if ((hour()<=12) && (hour()>=06))
    PrintStringWithShift("KALHMERA!  ",Speeeeeed-35);
  if ((hour()>=13) && (hour()<17))
    PrintStringWithShift("KALO MESHMERI!  ",Speeeeeed-35);
  if ((hour()>=17) && (hour()<22))
    PrintStringWithShift("KALHSPERA!  ",Speeeeeed-35);
  if (((hour()>=22) && (hour()<=23)) || ((hour()>=0) && (hour()<6)))
    PrintStringWithShift("KALO BRADY!  ",Speeeeeed-35);  
  Serial.println("Started!");
  Serial.println();
  Serial.println("You can set the time by typing T<epoch/unix timestamp>");
}

void loop()
{  
  if(Serial.available())
  {
     time_t t = ProcessSyncMessage();
     if (t > 0)
     {
       Serial.println("Time Received");             // Display time-received message.
       RTC.set(t);                                 // Set the RTC and the system time to the received value.
       setTime(t);                                 //
       TheMatrix.clear();
       PrintStringWithShift("H VRA APOUHKEYUHKE!  ",Speeeeeed-35);  // Display confirm message on LED Matrix.
       Serial.println("Time Setup on RTC!");       // Display confirm message on serial terminal.
     }
  }
  if (millis()-UpdateTempMillis>180000)            // Every 3 minutes, update Temperature/Humidity
  {
    Humidity = dht.readHumidity();
    Temperature = dht.readTemperature();
    UpdateTempMillis=millis();
  }
  if (millis()-TransmitMillis>300000)              // Every 5 minutes, transmit Temperature/Humidity
  {
    SendMessage();
    TransmitMillis=millis();
  }
  
  if (digitalRead(PIRSensor)==HIGH)                // Morion detected
    StartMillis=millis();
  
  
  if ((millis()-StartMillis)>(DisplayTime*60000)) // If it's some time before last PIR alarm
  {
    DisplayIsOn = false;                          // Entering standby -- do not display on the LED Matrix
    TheMatrix.clear();                            // Clear the LEDs
  }
  else
    DisplayIsOn = true;                           // Start displaying...
  
  if (DisplayIsOn)                                // Displaying data on LED Matrix
  {
    char TimeNow[14];
    sprintf(TimeNow,"VRA %.2d:%.2d:%.2d  ",hour(),minute(),second());
    PrintStringWithShift(TimeNow,Speeeeeed);
    DisplayDate+=1;
    if (DisplayDate>4)
    {
      char DisplayDateText[10];
      sprintf(DisplayDateText,"%.2d/%.2d/%.2d  ",day(),month(),year()-2000);
      PrintStringWithShift(DisplayDateText,Speeeeeed);
      DisplayDate=0;
    }
    char DisplayText[18];
    sprintf(DisplayText,"UERMOKRASIA %2dQW  ",Temperature);
    PrintStringWithShift(DisplayText,Speeeeeed);
   char DisplayText2[13];
    DisplayHum+=1;
    if (DisplayHum>5)
    {
      sprintf(DisplayText2,"YGRASIA %2d%%  ",Humidity);
      PrintStringWithShift(DisplayText2,Speeeeeed);
      DisplayHum=0;
    }  
  }
  if (Keypress())
  {
    long StartMillis=millis();
    TheMatrix.clear();
    boolean NotExit=true;
    while (NotExit)
    {
      if (Keypress())
        Intensity+=1;
      if (Intensity>15)
        Intensity=0;
      TheMatrix.setIntensity(Intensity);
      char tmpChar[2];
      sprintf(tmpChar,"%d ",Intensity);
      PrintStaticString(tmpChar);
      if (millis()-StartMillis>20000)
      {
        EEPROM.write(0,Intensity);
        TheMatrix.clear();
        PrintStringWithShift("APOUHKEYUHKE!  ",Speeeeeed-35);
        digitalWrite(BuzzerPin, HIGH);
        delay(100);
        digitalWrite(BuzzerPin, LOW);
        delay(100);
        NotExit=false;
      }
    }
  }
}

boolean Keypress()
{
  if (digitalRead(ButtonPin)==LOW)
  {
    digitalWrite(LEDPin, HIGH);
    digitalWrite(BuzzerPin, HIGH);
    delay(30);
    digitalWrite(LEDPin, LOW);
    digitalWrite(BuzzerPin, LOW);
    delay(70);
    return true;
  }
  else
    return false;
}


void PprintCharWithShift(char c, int ShiftSpeed)
{
  if (c < 32) return;
  c -= 32;
  memcpy_P(buffer, CH + 7*c, 7);
  TheMatrix.writeSprite(32, 0, buffer);
  TheMatrix.setColumn(32 + buffer[0], 0);
  
  for (int i=0; i<buffer[0]+1; i++) 
  {
    delay(ShiftSpeed);
    TheMatrix.shiftLeft(false, false);
  }
}

void PrintStringWithShift(char* s, int ShiftSpeed)
{
  while (*s != 0)
  {
    PprintCharWithShift(*s, ShiftSpeed);
    s++;
  }
}



/*  code to process time sync messages from the serial port   */
#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by unix time_t as ten ascii digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message

time_t ProcessSyncMessage() {
  // return the time if a valid sync message is received on the serial port.
  while(Serial.available() >=  TIME_MSG_LEN ){  // time message consists of a header and ten ascii digits
    char c = Serial.read() ; 
    Serial.print(c);  
    if( c == TIME_HEADER ) {       
      time_t pctime = 0;
      for(int i=0; i < TIME_MSG_LEN -1; i++){   
        c = Serial.read();          
        if( c >= '0' && c <= '9'){   
          pctime = (10 * pctime) + (c - '0') ; // convert digits to a number    
        }
      }   
      return pctime; 
    }  
  }
  Serial.println("");
  Serial.println("Command not recognized!");
  Serial.println("You can set the time by typing T<epoch/unix timestamp>");
  return 0;
}


void PrintStaticString(char* s)
{
  int col = 0;
  while (*s != 0)
  {
    if (*s < 32) continue;
    char c = *s - 32;
    memcpy_P(buffer, CH + 7*c, 7);
    TheMatrix.writeSprite(col, 0, buffer);
    TheMatrix.setColumn(col + buffer[0], 0);
    col += buffer[0] + 1;
    s++;
  }
}


void SendMessage()
{
  for (int x=0; x<2; x++)
  {
    //                    eg 2*1000=2000 + 10000 for temp + 25c = 12025
    digitalWrite(LEDPin, HIGH);
    MANCHESTER.Transmit((SensorNumber * 1000) + (SensorType * 10000) + Temperature);
    digitalWrite(LEDPin, LOW);
    delay(250);
    //                    eg 2*1000=2000 + 1+1 (for hum) * 10000 = 20000 for hum + 44% = 22044
    digitalWrite(LEDPin, HIGH);
    MANCHESTER.Transmit((SensorNumber*1000) + ((SensorType+1) * 10000) + Humidity);
    digitalWrite(LEDPin, LOW);
    delay(100);
  }  
}
