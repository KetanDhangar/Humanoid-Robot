#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <DHT.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SERVO_PIN_1 3
#define SERVO_PIN_2 5
#define SERVO_PIN_3 9
#define SERVO_PIN_4 6
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
int s, k;
#define DHTPIN 10 // Digital pin connected to the DHT sensor
const int LDR = 11;
#define DHTTYPE       DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
 
const int LED1 = 2;
const int LED2 = 4;
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
char x = 64;
char y = 64;
 
void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LDR, INPUT);
  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);
  servo3.attach(SERVO_PIN_3);
  servo4.attach(SERVO_PIN_4);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  dht.begin();
  display.clearDisplay();
}
 
void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command.equals("happy")) {
      happy();
    } else if (command.equals("sad")){
      sad();
    } else if (command.equals("turn left")){
      turnleft();
    } else if (command.equals("turn right")){
      turnright();
    } else if (command.equals("reset")){
      reset();
    } else if (command.equals("hello")){
      hello();
    } else if (command.equals("name")){
      name();
    } else if (command.equals("ronaldo")){
      ronaldo();
    } else if (command.equals("dance")){
      dance();
    } else if (command.equals("surprise")){
      surprise();
    } else if (command.equals("angry")){
      angry();
    } else if (command.equals("info")){
      info();
    } else if (command.equals("temp")){
      temp();
    }
  }
  int ldrValue = digitalRead(LDR);
  if (ldrValue == 1) {
    digitalWrite(LED1, HIGH);  // Turn on LED
    digitalWrite(LED2, HIGH);
  } else {
    digitalWrite(LED1, LOW);  // Turn off LED
    digitalWrite(LED2, LOW);
  }
}
 
void happy(){
  display.clearDisplay();
  display.fillCircle(x, 32, 32,WHITE);
  display.fillCircle(x, 32, 22,BLACK);
  display.fillRect(0, 0, 128, 32,0);
  display.fillRect((x - 32), 22, 66, 10,1);
  display.display();
  for (s=0; s<5; s++){
  eyeblink();
  }
}
 
void eyeblink(){
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  delay(750);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(750);
}
 
void sad() {
  display.clearDisplay();
  display.fillCircle(x, 48, 32,WHITE);
  display.fillCircle(x, 48, 22,BLACK);
  display.fillRect(0, 48, 128, 32,0);
  display.display();
  for (s=0; s<5; s++){
  eyeblink();
  }
}
 
void moveServosToPosition(int angle1, int angle2, int angle3, int angle4) {
  servo1.write(angle1); // Move servo1 to angle1
  servo2.write(angle2); // Move servo2 to angle2
  servo3.write(angle3); // Move servo3 to angle3
  servo4.write(angle4); // Move servo4 to angle4
}
 
void turnright() {
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("TURNING RIGHT");
  display.display();
  moveServosToPositionSmoothly(40, 40, 90, 90); // Move servos to another position
  delay(2000);
}
 
void turnleft() {
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("TURNING  LEFT");
  display.display();
  moveServosToPositionSmoothly(130, 130, 90, 90); // Move servos to another position
  delay(2000);
}
 
void reset() {
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,32);
  display.println(" RESET ");
  display.display();
  moveServosToPositionSmoothly(90, 90, 90, 90); // Move servos to another position
  delay(2000);
}
 
void info(){
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,32);
  display.println("ROBOMAX");
  display.display();
  for (s=0; s<11; s++){
  eyeblink();
  }
}
 
void hello() {
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,32);
  display.println(" HELLO ");
  display.display();
  eyeblink();
    moveServosToPositionSmoothly(90, 90, 90, 180);
    delay(2000);
    moveServosToPositionSmoothly(90, 90, 90, 90);
}
 
void name(){
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,32);
  display.println("ROBOMAX");
  display.display();
  for (s=0; s<5; s++){
  eyeblink();
  }
}
 
void temp(){
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    return;
  }
  display.clearDisplay();
  display.setCursor(0, 24);
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.print(temperature);
  display.print(" C");
  display.display();
  Serial.println(temperature);
}
 
void ronaldo(){
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,32);
  display.println("SUIIIII");
  display.display();
  moveServosToPositionSmoothly(90, 90, 10, 170);
  delay(2000);
  moveServosToPositionSmoothly(90, 90, 90, 90);
  delay(2000);
  for (s=0; s<5; s++){
  eyeblink();
  }
}
 
void dance(){
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,32);
  display.println(" DANCE ");
  display.display();
  for (k=0; k<2; k++){
    display.display();
    moveServosToPositionSmoothly(90, 50, 10, 170);
    delay(500);
    moveServosToPositionSmoothly(90, 90, 90, 90);
    delay(500);
    moveServosToPositionSmoothly(90, 120, 10, 170);
    delay(500);
    moveServosToPositionSmoothly(90, 90, 90, 90);
    delay(500);
    eyeblink();
    }
}
 
void surprise(){
  display.clearDisplay();
  display.drawCircle(64, 32, 30,WHITE);
  display.drawCircle(64, 32, 29,WHITE);
  display.drawCircle(64, 32, 28,WHITE);
  display.display();
  for (s=0; s<5; s++){
  eyeblink();
  }
  display.clearDisplay();
}
 
void angry(){
  display.clearDisplay();
  display.drawLine(16, 29, 112, 29,WHITE);
  display.drawLine(16, 30, 112, 30,WHITE);
  display.drawLine(16, 31, 112, 31,WHITE);
  display.drawLine(16, 32, 112, 32,WHITE);
  display.drawLine(16, 33, 112, 33,WHITE);
  display.drawLine(16, 34, 112, 34,WHITE);
  display.drawLine(16, 35, 112, 35,WHITE);
  display.display();
  for (s=0; s<5; s++){
  eyeblink();
  }
  display.clearDisplay();
}
 
void moveServosToPositionSmoothly(int targetAngle1, int targetAngle2, int targetAngle3, int targetAngle4) {
  int currentAngle1 = servo1.read();
  int currentAngle2 = servo2.read();
  int currentAngle3 = servo3.read();
  int currentAngle4 = servo4.read();
 
  int step1 = (targetAngle1 - currentAngle1 > 0) ? 1 : -1;
  int step2 = (targetAngle2 - currentAngle2 > 0) ? 1 : -1;
  int step3 = (targetAngle3 - currentAngle3 > 0) ? 1 : -1;
  int step4 = (targetAngle4 - currentAngle4 > 0) ? 1 : -1;
 
  while (currentAngle1 != targetAngle1 || currentAngle2 != targetAngle2 || currentAngle3 != targetAngle3 || currentAngle4 != targetAngle4) {
    if (currentAngle1 != targetAngle1) {
      currentAngle1 += step1;
      servo1.write(currentAngle1);
    }
    if (currentAngle2 != targetAngle2) {
      currentAngle2 += step2;
      servo2.write(currentAngle2);
    }
    if (currentAngle3 != targetAngle3) {
      currentAngle3 += step3;
      servo3.write(currentAngle3);
    }
    if (currentAngle4 != targetAngle4) {
      currentAngle4 += step4;
      servo4.write(currentAngle4);
    }
    delay(10); // Adjust this delay to control the speed of movement
  }
}