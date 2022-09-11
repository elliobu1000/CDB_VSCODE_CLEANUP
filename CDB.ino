//INCLUDE LIBRARIES

#include <Wire.h>
#include <Servo.h>
#include <Stepper.h>
#include <dht.h>
/* Include the standard Arduino SPI library */
#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define RFID_SDA 9
#define RFID_RST 8
/* Create an instance of the RFID library */
RFID RC522(RFID_SDA, RFID_RST); 




//SLAVE ADRESS

#define SLAVE_ADDRESS 0x04 

//DEFINING VARIABLES

/*  C7 ___________  C8  ___________ C6    
                    ||              ||
    C4   _____  Main_Board _____    C5
                    ||
    C1 ___________  C3  ___________ C2  */

    //C3M
int SW_button = 24;
int pot = A3;
int Joystick_Switch = 22;
int VRy = A1;
int VRx = A2;
int led3 = 23;
int DHT11_S = 12;
int D_Cap_de_Son = 3;
int A_Cap_de_Son = A4;
int buzzer = 2;
int D_Cap_de_Gaz = 4;
int A_Cap_de_Gaz = A5;
int D_Cap_de_Flammes = 5;
int A_Cap_de_Flammes = A6;
int led1 = 6;
int led2 = 7;

    //C4M
int RFID_SCK = 52;
int RFID_MOSI = 51;
int RFID_MISO = 50;
int led4 = 26;

    //C8M
int led7 = 25;
int PWM_SG90 = 11;
Servo myservo;
int IN4_Steper = 27;
int IN3_Steper = 28;
int IN2_Steper = 29;
int IN1_Steper = 30;
#define stepsPerRevolution 100
int previous = 0;
Stepper myStepper(stepsPerRevolution, 30, 29, 28, 27);
int Photo_Resistance_PWM = 10;
int C8_led4 = 32;
int C8_led3 = 33;
int C8_led2 = 34;
int C8_led1 = 35;
int Red = 41;
int Green = 42;
int Blue = 43;
int led8 = 44;
int DC_input1 = 45;
int DC_input2 = 47;
int ena = 46;
int PIR = 48;
int led6 = 49;

    //C5M
int led5 = 36;
int S_inf = A8;
int TrigPin = 37;
int EchoPin = 38;




int func1_val = 0;
int func1_val2 = 0;
int i2cdata =0;
//FLAG_I2C
int flag = 0;


// Handle reception of incoming I2C data
void receiveData(int byteCount) {
  while (Wire.available()) {
    i2cData = Wire.read(); //the master command
    if (i2cData == 1) {

      flag = 1; //setting the flag value based on bus.write return from master

    }
    else if(i2cData == 2){

      flag = 2;
    }
  }
}

// Handle request to send I2C data
void sendData() {
    if(flag==1){
        Wire.write(func1_val);

    }else if(flag==2){
        Wire.write(func1_val2);
    }//else if(flag==3)==>mode3, write(func_val3) func_val3 being the sensor data from mode 3
    //...etc
}

//************MODES*****************

void led_blink_fast(){
  digitalWrite(LED, 1);
  delay(500);
  digitalWrite(LED, 0);
  delay(500);
  //func1_val = 12; just testing Wire.write from slave to master if the master requests data
}

void led_blink_slow(){
  digitalWrite(LED, 1);
  delay(1000);
  digitalWrite(LED, 0);
  delay(1000);
  //func1_val2 = 10; just testing Wire.write from slave to master if the master requests data
}

//....ETC, MODES




//************MODES*****************



void setup(){
    Serial.begin(9600);
    /* Enable the SPI interface */
    SPI.begin(); 
    /* Initialise the RFID reader */
    RC522.init();

    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    noTone(buzzer);
    myStepper.setSpeed(100);
    myservo.attach(PWM_SG90);

    //SETUP
    pinMode(EchoPin, OUTPUT);
    pinMode(TrigPin, OUTPUT);
    pinMode(S_inf, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(led6, OUTPUT);
    pinMode(PIR, OUTPUT);
    pinMode(ena, OUTPUT);
    pinMode(DC_input1, OUTPUT);
    pinMode(DC_input2, OUTPUT);
    pinMode(led8, OUTPUT);
    pinMode(Green, OUTPUT);
    pinMode(Blue, OUTPUT);
    pinMode(Red, OUTPUT);
    pinMode(C8_led1, OUTPUT);
    pinMode(C8_led2, OUTPUT);
    pinMode(C8_led3, OUTPUT);
    pinMode(C8_led4, OUTPUT);
    pinMode(Photo_Resistance_PWM, OUTPUT);

    pinMode(led7, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led1, OUTPUT);
    pinMode(A_Cap_de_Flammes, INPUT);
    pinMode(D_Cap_de_Flammes, INPUT);
    pinMode(D_Cap_de_Gaz, INPUT);
    pinMode(A_Cap_de_Gaz, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(A_Cap_de_Son, INPUT);
    pinMode(D_Cap_de_Son, INPUT);
    pinMode(DHT11_S, INPUT);
    pinMode(led3, OUTPUT);
    pinMode(VRx, INPUT);
    pinMode(VRy, INPUT);
    pinMode(Joystick_Switch, INPUT);
    pinMode(pot, INPUT);
    pinMode(SW_button, INPUT);
}

void loop() {
  if (flag == 1){
    led_blink_fast();
  }else if(flag==2){
    led_blink_slow();
//   }else if(flag==3){
//     ledblink_MODE1();
//   }else if(flag==4){
//     ledbuttonControl_MODE3();
//   }else if(flag==5){
//     lcdPrintButState_MODE2();
//   }else if(flag==6){
//     PWM_Led_MODE_6();
//   }else if(flag==7){
//     dc_motor_speed_MODE_7();
//   }else if(flag==8){
//     servopotlcd_MODE_8();
//   }else if(flag==9){
//     stepbystep_MODE_9();
//   }else if(flag==10){
//     Knob_STEPPER_MODE10();
//   }else if(flag==11){
//     JoyServoControl_MODE_11();
//   }else if(flag==12){
//     HC05_LEDonoff_MODE_13();
//   }else if(flag==13){
//     ultrason_lcd_MODE_14();
//   }else if(flag==14){
//     infra_obst_detec_MODE_15();
//   }else if(flag==15){
//     PIR_MODE_16();
//   }else if(flag==16){
//     CAP_Son_MODE_17();
//   }else if(flag==17){
//     flamme_detec_MODE_18();
//   }else if(flag==18){
//     DHT11_MODE_20();
//   }else if(flag==19){
//     Gas_SENSOR_MODE21();
//   } ... ETC
    delay(10);

  // Everything happens in the interrupts
}
