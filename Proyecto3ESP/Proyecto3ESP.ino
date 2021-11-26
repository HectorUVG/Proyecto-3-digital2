//Hector Manuel de Leon Salguero
//Universidad del Valle de Guatmala
//19511
//Proyecto 3
//Electronica digital 2
//*****************************************************************************
//Librerias
//*****************************************************************************
#include <Arduino.h>
#include <Adafruit_AHT10.h>

Adafruit_AHT10 aht;
//-------------------------------neopixel-----------------------------------------
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        3 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
//*****************************************************************************
//Definicion de pines
//*****************************************************************************
//sensor


//Comunicacion Uart
#define RXD2 16
#define TXD2 17

//*****************************************************************************
//Prototipos de funciones
//*****************************************************************************

//para el el sensor
void SensorHumedadTemp(void);

void comunicacionTIVA(void);

void neopixel(void);
//*****************************************************************************
//Variables Globales
//*****************************************************************************

int datoPaLed = 0;




//delay1
unsigned long lastTime;
unsigned int sampleTime = 500;

//delay1
unsigned long lastTime2;
unsigned int sampleTime2 = 3000;



int humedadEntero = 0;
float humedad = 0.0;

//*****************************************************************************
//ISR
//*****************************************************************************

//*****************************************************************************
//Configuracion
//*****************************************************************************

void setup() {

  Serial.begin(115200);
//  ----------------sensor-------------------------------------------------
  Serial.println("Adafruit AHT10 demo!");

  if (! aht.begin()) {
    Serial.println("Could not find AHT10? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 found");
  
  Serial2.begin(115200);
  lastTime = millis();//delay de 500milisegundos
  lastTime2 = millis();//delay de 3000milisegundos

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  

  pixels.begin();
}


//*****************************************************************************
//Loop principal
//*****************************************************************************
void loop() {

   //llamar a la funcion del promedio
  //if(millis() - lastTime >= sampleTime){
    SensorHumedadTemp();
    comunicacionTIVA();
    neopixel();
    //definicion de decena unidad y decimal
    //tempAUnidades();
    humedadEntero = humedad;
    Serial2.write(humedadEntero);
  //}
}

//*****************************************************************************
//Funcion para media movil
//*****************************************************************************

void SensorHumedadTemp(){

  //if(millis() - lastTime2 >= sampleTime2){
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
    Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
    Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
    Serial.print("dato: "); Serial.println(datoPaLed);
    humedad = humidity.relative_humidity;
    delay(500);
  //}



}

//*****************************************************************************
//Comunicacion con la tiva
//*****************************************************************************
void comunicacionTIVA(){
  if(Serial2.available()){//si hay algun dato esperando a ser leido...
    datoPaLed = Serial2.read();//el dato es guardado en la variable
    }  
  }

//*****************************************************************************
//Neopixel
//*****************************************************************************
void neopixel(){
  
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  if(datoPaLed == 0){
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
  
      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixels.setPixelColor(i, pixels.Color(150, 150, 150));
  
      pixels.show();   // Send the updated pixel colors to the hardware.
  
      //delay(DELAYVAL); // Pause before next pass through loop
    }
  }

    if(datoPaLed == 1){
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
  
      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixels.setPixelColor(i, pixels.Color(0, 150, 0));
  
      pixels.show();   // Send the updated pixel colors to the hardware.
  
      //delay(DELAYVAL); // Pause before next pass through loop
    }
  }

    if(datoPaLed == 2){
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
  
      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixels.setPixelColor(i, pixels.Color(150, 0, 0));
  
      pixels.show();   // Send the updated pixel colors to the hardware.
  
      //delay(DELAYVAL); // Pause before next pass through loop
    }
  }
  
}
