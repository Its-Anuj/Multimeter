
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Enter Resistor: ");
  Serial.begin(9600);
}

int PrintRow(String Input, int Row)
{
  lcd.setCursor(0,Row);
  if(Input.length() > 15)
      lcd.print(Input);
  else
  {
    String SubStr = Input.substring(0, 15);
    lcd.print(SubStr);
  }
}

int Println(String Input)
{
  lcd.clear();
  
  if(Input.length() > 32)
    return -1;
 
  if(Input.length() > 16)
  {
    //Since input is greater than the row size 16 
    //we print in both lines
    
    PrintRow(Input.substring(0, 15), 0);
    PrintRow(Input.substring(15, Input.length()), 1);
  	return 0;
  }

  PrintRow(Input, 0);
  return 0;
}

int Resistor = 0;
void loop() {
  
  if(Serial.available())
  {
    Resistor = (Serial.readString().toInt());
  }
  
  if(Resistor != 0)
  {
    float Vol = analogRead(A0) * (5.0/1023.0);
    
    PrintRow("Voltage: " + String(Vol, 2), 0);
    // Calculating Current using input 

    float Current = (Vol/float(Resistor));
    PrintRow("Current: " + String(Current, 4), 1);
  }
  
  delay(50);
  
}