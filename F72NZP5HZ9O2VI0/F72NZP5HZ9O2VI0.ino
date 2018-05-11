/*
	Under the bed nightlight

	Lights up a led strip under the bed when it detects movement.

	The circuit:
	* PIR for movement. The ammout of sensors depends on the bed. 

	Created 25-08-2014
	By VeryEvilBetty

*/
#define led_pin 9
const int out_pin = 12;

const int pir_pin = 8;  // Pin of the pir sensor

const int led_time = 8; // Time to have the leds on (no an exact timing) (in Sec)
const int on_delay = 100; // Delay to turn the leds on (in mSec)
const int off_delay = 30; // Delay to turn the leds off (in mSec)


const int led_max = 50;  // Ledstrip max pwm value
const int led_min = 0;    // Ledstrip min pwm value (0 recommended, else it wont turn off)

boolean led = false;     // Boolean thats true when the led strip is on;
int timer = 0;           // Integer for the timer;

void setup(){

  pinMode(pir_pin,INPUT);
  pinMode(led_pin,OUTPUT);
  pinMode(out_pin,OUTPUT);

  
}

void loop(){

  // Read all pir sensors
  boolean pir = false;    
      if (digitalRead(pir_pin) == 1){
        pir = true;    
  }

  
  // If the room is dark and movement is detected the leds turn on, send a high signal to Pi, and the timer is set to 0
  if (pir == true){
    digitalWrite(out_pin, HIGH);
    ledAan();
    timer = 0;
  } else {
    digitalWrite(out_pin, LOW);
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
