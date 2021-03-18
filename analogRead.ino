#define ALPHA_LIGHT 0.0001
#define EDGES_PER_REVOLUTION 6.0
#define VERBOSE 1

#define BUFFER_TOP 6
#define BUFFER_BOTTOM 2

#define SPEED 400
#define MOTOR_PIN 11


int analogPin1 = A0; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int analogPin2 = A2; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val1 = 0;  // variable to store the value read
int val2 = 0;  // variable to store the value read


float average_light1 = 0;

void set_average_light1(int new_value){
  average_light1 = (ALPHA_LIGHT * new_value) + (1.0 - ALPHA_LIGHT) * average_light1;
  
}

int get_average_light1(){
  return (int) average_light1;
}

float average_light2 = 0;

void set_average_light2(int new_value){
  average_light2 = (ALPHA_LIGHT * new_value) + (1.0 - ALPHA_LIGHT) * average_light2;
  
}

int get_average_light2(){
  return (int) average_light2;
}


int temp = 0;

int motor_running = 0;
int last_state = 0;


void setup_motors(){
  pinMode(MOTOR_PIN, OUTPUT);  // sets the pin as output
}

void turn_motor_on(){
    Serial.println("Turn motor On");
    for(int i =0; i< SPEED; i++){
      
    analogWrite(MOTOR_PIN, i); // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
    }
}

void turn_motor_off(){
    Serial.println("Turn motor Off"); 
    analogWrite(MOTOR_PIN, 0); // analogRead values go from 0 to 1023, analogWrite values from 0 to 255

  
}

void setup() {
    temp = analogRead(analogPin1);  // read the input pin
  average_light1 = float (temp);

  temp = analogRead(analogPin2);  // read the input pin
  average_light2 = float (temp);
  Serial.begin(9600);           //  setup serial

  setup_motors();
}


void loop() {
  temp = analogRead(analogPin1);  // read the input pin
  set_average_light1(temp);
  val1 = temp - get_average_light1() - BUFFER_BOTTOM;

  temp = analogRead(analogPin2);  // read the input pin
  set_average_light2(temp);
  val2 = temp - get_average_light2()- BUFFER_TOP;

  #ifdef VERBOSE
  //Serial.print(val1);          // debug value
  //Serial.print(" ");          // debug value
  //Serial.println(val2);          // debug value
  #endif

  if (val1 > 0){
    motor_running = 1;
  }
  if (val2 > 0){
    motor_running = 0;
    //Serial.println(val2);          // debug value
  }

  if (motor_running != last_state){
    if(motor_running){
      turn_motor_on();
    }else{
      turn_motor_off() ;  
    }
    last_state = motor_running;
  }
}
