

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int  Up_buttonPin   = 6;    // the pin that the pushbutton is attached to
const int  Up_buttonPin_DONE = 7;
const int reset = 9;
// Variables will change:
int NEW = 0;   
int DONE = 0;  
int TOTAL_CLIENTS = 0;
int up_buttonState = 0;         // current state of the up button
int up_buttonState_DONE = 0; 
int up_lastButtonState = 0;     // previous state of the up button
int up_lastButtonState_DONE = 0; 
bool bPress = false;
bool bPress_DONE = false;
bool start = true;
bool FULL = false; 

void setup() {
  
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("Clients");
  Serial.begin(9600);
  pinMode( Up_buttonPin , INPUT_PULLUP);
  pinMode( Up_buttonPin_DONE , INPUT_PULLUP);
   pinMode( reset , INPUT_PULLUP);
 
 
  // Print a message to the LCD.

  lcd.setCursor(0,0);
  lcd.print("Clients");
  lcd.setCursor(13,0);
  lcd.print(NEW);
  lcd.setCursor(0,1);
  lcd.print("CurentClient");
  lcd.setCursor(13,1);
  lcd.print(DONE);
  

}

void loop() {
  
  
if(start == true){
  
  
  if(DONE <4){
    if(NEW < 4){
  lcd.setCursor(13, 0);
  
   
   lcd.print(NEW);
      checkUp();
   checkUp_DONE();
     if( bPress){
       bPress = false;
       lcd.setCursor(13,0);
       lcd.print(NEW);
        }
     if( bPress_DONE){
       bPress_DONE = false;
       lcd.setCursor(13,1);
       lcd.print(DONE);
       }
    }else{
    FULL = true;
      
    
    lcd.setCursor(0,0);
    lcd.print("COME TOMMOROW   ");
    checkUp_DONE();
      if( bPress_DONE){
        bPress_DONE = false;
        lcd.setCursor(13,1);
        lcd.print(DONE);
        //Εμφανιζεται ο επόμενος πελάτης στο SerialMonitor
        TOTAL_CLIENTS = DONE +1;
        Serial.println(TOTAL_CLIENTS);
       }
       }
    }else{
   lcd.setCursor(0,0);
   lcd.print("END OF WORK!!   ");
   Serial.println("NO OTHER CLIENTS");
   start = false;
  }
  }
}

void checkUp()
{
  up_buttonState = digitalRead(Up_buttonPin);

  // compare the buttonState to its previous state
  if (up_buttonState != up_lastButtonState) {
    // if the state has changed, increment the counter
    if (up_buttonState == LOW) {
      
        bPress = true;
      // if the current state is HIGH then the button went from off to on:
      NEW++;
      
    } 
    // Delay a little bit to avoid bouncing
    delay(40);
  }
  // save the current state as the last state, for next time through the loop
  up_lastButtonState = up_buttonState;
}

void checkUp_DONE()
{
  up_buttonState_DONE = digitalRead(Up_buttonPin_DONE);

  // compare the buttonState to its previous state
  if (up_buttonState_DONE != up_lastButtonState_DONE) {
    // if the state has changed, increment the counter
    if (up_buttonState_DONE == LOW) {
        bPress_DONE = true;
      // if the current state is HIGH then the button went from off to on:
      DONE++;
      
    } 
    // Delay a little bit to avoid bouncing
    delay(40);
  }
  // save the current state as the last state, for next time through the loop
  up_lastButtonState_DONE = up_buttonState_DONE;
}



