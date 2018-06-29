#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons()
{
  adc_key_in = analogRead(0);
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 250)  return btnUP;
  if (adc_key_in < 450)  return btnDOWN;
  if (adc_key_in < 650)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT;

  return btnNONE;  // when all others fail, return this...
}

int marge = 1000 ;
int i = int(marge / 2) ;
int nombreDeCoups = 15 ;
int secret = 0 ;

void setup() {
  randomSeed(analogRead(5));
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Le juste prix !") ;
  lcd.setCursor(0, 1) ;
  lcd.print("De 1 a 1000") ;
  delay(2250);
  lcd.setCursor(0, 1) ;
  lcd.print("En 15 essais") ;
   delay(1750);
  lcd.clear() ;
  secret = random(1, marge);
}

void loop() {

  while (nombreDeCoups != 0) {
    
    lcd.setCursor(0, 0) ;
    lcd.print(i) ;

    if (nombreDeCoups >= 10) {
      lcd.setCursor(14, 0) ;
    }
    else {
      lcd.setCursor(15, 0) ;
    }
    lcd.print(nombreDeCoups) ;

    lcd_key = read_LCD_buttons();

    switch (lcd_key)
    {
      case btnUP: {
          i = i + 1 ;
          break;
        }
      case btnDOWN: {
          i = i - 1 ;
          break;
        }
      case btnRIGHT: {
          i = i + 10 ;
          break;
        }
      case btnLEFT: {
          i = i - 10 ;
          break;
        }
      case btnSELECT: {
          lcd.setCursor(0, 1) ;
          if (i < secret) {
            lcd.print("c'est plus ") ;
          }
          if (i > secret) {
            lcd.print("c'est moins") ;
          }
          while (i == secret) {
            lcd.setCursor(0, 1) ;
            lcd.print("Felicitation !") ;
          }
          nombreDeCoups = nombreDeCoups - 1 ;
          delay(550);
          break;
        }
    }
    if (lcd_key != 5) {
      delay(200);
      lcd.clear() ;
    }

  }
  lcd.setCursor(0, 0) ;
  lcd.print("Perdu") ;

}
