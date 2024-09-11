#define sensor_right 5
#define sensor_left 6

#define motor1_en 8
#define motor1_CW 9
#define motor1_CCW 10

#define motor2_en 13
#define motor2_CW 12
#define motor2_CCW 11

char command   ;
char mode = 'R';

void setup() 
{
  // TCCR0B= TCCR0B & B11111000 | B00000010 ; // لقيت السطر ده ففيديو
  Serial.begin(9600);

  pinMode(sensor_right, INPUT);
  pinMode(sensor_left, INPUT);

  pinMode(motor1_en, OUTPUT);
  pinMode(motor1_CW, OUTPUT);
  pinMode(motor1_CCW, OUTPUT);

  pinMode(motor2_en, OUTPUT);
  pinMode(motor2_CW, OUTPUT);
  pinMode(motor2_CCW, OUTPUT);
}

void loop() 
{
  if (mode == 'R') // RC Car
  {
    if (Serial.available() > 0) {
      command = Serial.read();
      RC(command);
    }
  } 

  else if (mode == 'L') // Line Follower 
  {
    line(); 

    if (Serial.available() > 0) {
      if (Serial.read() == 'R')  mode = 'R';
    }
    
  }
}

void RC(char command) 
{
  Serial.println(command);

  if (command == 'w' || command == 'W' || command == 'ص') 
    move_UP();
  
  else if (command == 'a' || command == 'A' || command == 'ش') 
    move_Left();
   
  else if (command == 's' || command == 'S' || command == 'س') 
    move_Back();
  
  else if (command == 'd' || command == 'D' || command == 'ي') 
    move_Right();
  
  else if (command == ' ') 
    stop();
  
  else if (command == 'l'||command == 'L'|| command == 'م') 
    mode = 'L';
  else return 0;
  delay(100);stop();
}

void line() 
{
    if (digitalRead(sensor_right) == HIGH && digitalRead(sensor_left) == HIGH) 
      move_UP();
    
    else if (digitalRead(sensor_right) == HIGH && digitalRead(sensor_left) == LOW) 
      move_Left();
    
    else if (digitalRead(sensor_right) == LOW && digitalRead(sensor_left) == HIGH) 
      move_Right();
    
    else if (digitalRead(sensor_right) == LOW && digitalRead(sensor_left) == LOW) 
      stop();
}



void move_UP() {
  motor1_UP();
  motor2_UP();
  Serial.println("UP");
}

void move_Back() {
  motor1_Back();
  motor2_Back();
  Serial.println("Back");
}

void move_Right() {
  motor1_Back();
  motor2_UP();
  Serial.println("Right");
}

void move_Left() {
  motor1_UP();
  motor2_Back();
  Serial.println("Left");
}


void stop() {
  digitalWrite(motor1_en, LOW);
  digitalWrite(motor1_CW, LOW);
  digitalWrite(motor1_CCW, LOW);

  digitalWrite(motor2_en, LOW);
  digitalWrite(motor2_CW, LOW);
  digitalWrite(motor2_CCW, LOW);

  Serial.println("Stop");
}

void motor1_UP() {
  digitalWrite(motor1_en, HIGH);
  digitalWrite(motor1_CW, HIGH);
  digitalWrite(motor1_CCW, LOW);
}
void motor1_Back() {
  digitalWrite(motor1_en, HIGH);
  digitalWrite(motor1_CW, LOW);
  digitalWrite(motor1_CCW, HIGH);
}


void motor2_UP() {
  digitalWrite(motor2_en, HIGH);
  digitalWrite(motor2_CW, HIGH);
  digitalWrite(motor2_CCW, LOW);
}

void motor2_Back() {
  digitalWrite(motor2_en, HIGH);
  digitalWrite(motor2_CW, LOW);
  digitalWrite(motor2_CCW, HIGH);
}
