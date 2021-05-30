/*************************************************************
Create with PROGRAMINO-IDE http://www.programino.com

Project:       Programino Lab Demo
Librarys:      
Author:        UlliS
Description:
**************************************************************/

// pwm pins for LEDs or other things
const int pwm1pin = 3;
const int pwm2pin = 5;
const int pwm3pin = 6;

// digital inputs
const int input1pin = A4;
const int input2pin = A5;
const int input3pin = 2;
const int input4pin = 4;
const int input5pin = 7;

// digital output pins
const int button1Pin = 8;
const int button2Pin = 9;
const int button3Pin = 10;
const int button4Pin = 11;
const int button5Pin = 12;
const int button6Pin = 13;


void setup() {
    
    // set baudrate
    Serial.begin(115200);
    while(!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }
    
    // digital outputs
    pinMode(button1Pin,OUTPUT);
    pinMode(button2Pin,OUTPUT);
    pinMode(button3Pin,OUTPUT);
    pinMode(button4Pin,OUTPUT);
    pinMode(button5Pin,OUTPUT);
    pinMode(button6Pin,OUTPUT);
    
    // digital inputs
    pinMode(input1pin,INPUT);
    pinMode(input2pin,INPUT);
    pinMode(input3pin,INPUT);
    pinMode(input4pin,INPUT);
    pinMode(input5pin,INPUT);
    
    // activate the internal pullup resistor (switch the input to GND)
    // if you're using no internal pullups then comment this part and use external pullup or pulldown resitor
    digitalWrite(input1pin,HIGH);
    digitalWrite(input2pin,HIGH);
    digitalWrite(input3pin,HIGH);
    digitalWrite(input4pin,HIGH);
    digitalWrite(input5pin,HIGH);
    
    // analog outputs
    pinMode(pwm1pin, OUTPUT);
    pinMode(pwm2pin, OUTPUT);
    pinMode(pwm3pin, OUTPUT);
    
    // set the outputs to high
    // if you're using a common-cathode LED, just use 0"
    analogWrite(pwm1pin,255);
    analogWrite(pwm2pin,255);
    analogWrite(pwm3pin,255);
    
}

void loop() {
    
    // if there's any serial available, read it
    while (Serial.available() >= 9) 
    {
        // look for the next valid integer in the incoming serial stream
        // value 0 to 255
        int pwm1 = Serial.parseInt();
        int pwm2 = Serial.parseInt();
        int pwm3 = Serial.parseInt();
        
        int Output1 = Serial.parseInt();
        int Output2 = Serial.parseInt();
        int Output3 = Serial.parseInt();
        int Output4 = Serial.parseInt();
        int Output5 = Serial.parseInt();
        int Output6 = Serial.parseInt();
        
        // look for the newline. That's the end of your sentence
        if (Serial.read() == '\n') 
        {
            // constrain the values to 0 - 255 and invert
            // if you're using a common-cathode LED, just use "constrain(pwm, 0, 255);"
            pwm1 = 255 - constrain(pwm1, 0, 255);
            pwm2 = 255 - constrain(pwm2, 0, 255);
            pwm3 = 255 - constrain(pwm3, 0, 255);
            
            // fade the LEDs
            analogWrite(pwm1pin, pwm1);
            analogWrite(pwm2pin, pwm2);
            analogWrite(pwm3pin, pwm3);
            
            // write the digital pins
            digitalWrite(button1Pin,Output1);
            digitalWrite(button2Pin,Output2);
            digitalWrite(button3Pin,Output3);
            digitalWrite(button4Pin,Output4);
            digitalWrite(button5Pin,Output5);
            digitalWrite(button6Pin,Output6);            
        }
    }
    
    
    // send the raw the values to the Programino Lab
    // value 0 to 1023
    Serial.print(analogRead(A0));
    Serial.print(",");
    
    Serial.print(analogRead(A1));
    Serial.print(",");
    
    Serial.print(analogRead(A2));
    Serial.print(",");
    
    Serial.print(analogRead(A3));
    Serial.print(",");
    
    
    // send the digital states to PROGRAMINO Lab
    // ! intervert the digital signal
    // value 0 or 1
    Serial.print(!digitalRead(input1pin));
    Serial.print(",");
    
    Serial.print(!digitalRead(input2pin));
    Serial.print(",");
    
    Serial.print(!digitalRead(input3pin));
    Serial.print(",");
    
    Serial.print(!digitalRead(input4pin));
    Serial.print(",");
    
    Serial.println(!digitalRead(input5pin));
    
    
    // set the sample rate from 1ms to 1000ms (no delay works, but is not recommended)
    // if the delay short then the PC CPU power is higher!!!
    // recommended is 25ms or 50ms
    delay(25);
    
}
