#include<LiquidCrystal.h>

/*Defining pins to decrease memory allocation*/
#define ir0 13
#define ir1 12
#define ir2 11
#define ir3 10
#define sw 9
#define rs 8
#define en 7
#define Vo 6
#define d4 5
#define d5 4
#define d6 3
#define d7 2


const int cont = 20; /*Contrast value for the LCD*/

int ir0_out = HIGH, ir1_out = HIGH, ir2_out = HIGH, ir3_out = HIGH; /* declaring to avoid false LOW during board bootup triggering false detections*/
int c0 = 0, c1 = 0, c2 = 0, c3 = 0, total = 0, flag, push, pcount = 0; /*Variables required to keep track of count*/

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  /*Initializing communication with Serial Monitor*/
  //Serial.begin(9600);

  /* LCD contrast*/
  analogWrite(Vo, cont);

  /*Setting up input pins on the arduino */
  pinMode(ir0, INPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(sw, INPUT);

  /*Setting up the display*/
  lcd.begin(16, 2);
  lcd.clear() ;
  //lcd.setCursor(0,0) ;
  lcd.print("Coin Counter") ;
}

void loop() {
  /*Reading input from switch*/
  push = digitalRead(sw);
  
  /*ir sensor output*/
  ir0_out = digitalRead(ir0);
  ir1_out = digitalRead(ir1);
  ir2_out = digitalRead(ir2);
  ir3_out = digitalRead(ir3);

  if (ir0_out == LOW) {
    // 1 Rupee
    c0++;
    delay(80);
  }

  if (ir1_out == LOW) {
    // 5 Rupee
    c1++;
    delay(120);
  }

  if (ir2_out == LOW) {
    // 2 Rupee
    c2++;
    delay(80);
  }

  if (ir3_out == LOW) {
    // 10 Rupee
    c3++;
    delay(80);
  }

  flag=total;
  total=c0*1+c1*5+c2*2+c3*10;

  if (push == LOW) {
    pcount++;
    delay(200);
    flag++;
  }

  if (flag!=total){
    lcd.clear();
    if (pcount%5==0){
      lcd.print("Total");
      lcd.setCursor(0,1);
      lcd.print(total);
    }
    else if(pcount%5==1){
      lcd.print("Rs 10 Coins");
      lcd.setCursor(0,1);
      lcd.print(c3);
    }
    else if(pcount%5==2){
      lcd.print("Rs 5 Coins");
      lcd.setCursor(0,1);
      lcd.print(c1);
    }
    else if(pcount%5==3){
      lcd.print("Rs 2 Coins");
      lcd.setCursor(0,1);
      lcd.print(c2);
    }
    else if(pcount%5==4){
      lcd.print("Rs 1 coins");
      lcd.setCursor(0,1);
      lcd.print(c0);
    }
  }
}
