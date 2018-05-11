/*
	Under the bed nightlight

	Lights up a led strip under the bed when it detects movement while its dark.

	The circuit:
	* PIR for movement. The ammout of sensors depends on the bed. 
	* LDR for light sensor
        * Transistor to drive the LED strip

	Created 25-08-2014
	By VeryEvilBetty

*/
#define ldr_pin A5
#define led_pin 9

const int numberOfPirs = 1;              // Number of pir sensors
const int pir_pins[numberOfPirs] = {8};  // Pins of the pir sensors Example = {pin,pin,pin}

const int led_time = 10; // Time to have the leds on (no an exact timing) (in Sec)
const int on_delay = 20; // Delay to turn the leds on (in mSec)
const int off_delay = 1; // Delay to turn the leds off (in mSec)

const int ldr_value = 500; // Value to make the differene between dark and light

const int led_max = 180;  // Ledstrip max pwm value
const int led_min = 0;    // Ledstrip min pwm value (0 recommended, else it wont turn off)

boolean licht = false;   // Booelan thats true when the light is on;
boolean led = false;     // Boolean thats true when the led strip is on;
int timer = 0;           // Integer for the timer;

void setup(){

  pinMode(ldr_pin,INPUT);
  
  // Set pinmode for all pir sensors
  for (int i=0; i < numberOfPirs; i++){
    pinMode(pir_pins[i],INPUT);
  }
  
  pinMode(led_pin,OUTPUT);
}

void loop(){
  
  // Read ldr value
  int ldr = analogRead(ldr_pin);
 
  // Read all pir sensors
  boolean pir = false;    
  for (int i=0; i < numberOfPirs; i++){
      if (digitalRead(pir_pins[i]) == 1){
        pir = true;    
      }
  }

  // Check if the room hase enough light
  if (ldr > ldr_value){
    licht = false; 
  }else{
    licht = true; 
  }
 
  // If the room is dark and movement is detected the leds turn on and the timer is set to 0
  if (pir == true && licht == false){
    ledAan();
    timer = 0;
  }
  
  // if the leds are on and the room has enough light the leds go off
  if (led == true && licht == true){
    ledUit(); 
  }
  
  // if the leds are on icrement the timer
  if (led == true) timer++;
  
  // if the timer is equal to the set time turn the leds off.
  if (timer == led_time){
    ledUit(); 
  }
 
  delay(1000);
}


// function to turn the leds on
void ledAan(){
  if (led == false){
    for(int i=led_min;i<=led_max; i++){
      analogWrite(led_pin,i);
      delay(on_delay);
    }    
    led = true;
  }
}

// function to turn the leds off
void ledUit(){
  if (led == true){
    for(int i=led_max;i>=led_min; i--){
      analogWrite(led_pin,i);
      delay(off_delay);      
    }    
    led = false;
  }
}
