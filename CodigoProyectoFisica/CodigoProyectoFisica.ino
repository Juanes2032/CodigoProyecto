#include <time.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
const int sensorPin1 = 9;
const int sensorPin2 = 10;
const float g = 9.8;
const float myu = 0.15;
const float m1 = 0.011;
const float m2 = 0.018;

float aceleracion = g*(m2 - (myu*m1))/(m2 + m1); 


//unidades en metros.
const double Xi = 0.06;
const double Xf = 0.26;
const double dX = Xf - Xi;

double Ti, Tf, dT, V;
//------------------------

bool aux = true;


void setup() {
  Serial.begin(9600);   //iniciar puerto serie

  pinMode(sensorPin1 , INPUT);  //definir pin como input
  pinMode(sensorPin2 , INPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PROGRAMA"); 
  lcd.setCursor(0,1);
  lcd.print("VELOCIDAD"); 
}
 
void loop(){

  //output del sensor 1.
  int output_s1 = digitalRead(sensorPin1);
  
  //entrada primer sensor.
  if (!output_s1) {
    Ti = millis();

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("analizando");

    aux = true;//abre la entrada al segundo sensor.
  }

  //output del sensor 2.
  int output_s2 = digitalRead(sensorPin2);

  //entrada segundo sensor.
  if (!output_s2 && aux) {
    Tf = millis();

    //diferencia entre tiempos.
    dT = Tf - Ti;
    dT = dT / 1000; //convercion a segundos.
    
    V = aceleracion*dT; //velocudad mrua.

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(V);
    lcd.setCursor(0,1);
    lcd.print("V(m/s)");

    aux = false;//cierra el paso del segundo sensor.
  }
}