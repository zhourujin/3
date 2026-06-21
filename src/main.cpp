#include <Arduino.h>  

// 定义连接步进电机的四个GPIO引脚
int motorPins[] = {13, 12, 14, 27};
int stepDelay = 2;
int stepsPerRevolution = 2048;

// 正转序列
int forwardSeq[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

// 反转序列
int reverseSeq[8][4] = {
  {1, 0, 0, 1},
  {0, 0, 0, 1},
  {0, 0, 1, 1},
  {0, 0, 1, 0},
  {0, 1, 1, 0},
  {0, 1, 0, 0},
  {1, 1, 0, 0},
  {1, 0, 0, 0}
};

// 函数声明（放在前面）
void rotate(int seq[][4], int steps, int delayMs);

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(motorPins[i], OUTPUT);
    digitalWrite(motorPins[i], LOW);
  }
  Serial.begin(115200);
  Serial.println("程序开始运行");
}

void loop() {
  Serial.println("正转一圈");
  rotate(forwardSeq, stepsPerRevolution, stepDelay);
  
  Serial.println("停顿...");
  delay(1000);
  
  Serial.println("反转一圈");
  rotate(reverseSeq, stepsPerRevolution, stepDelay);
  
  delay(1000);
}

void rotate(int seq[][4], int steps, int delayMs) {
  for (int i = 0; i < steps; i++) {
    int index = i % 8;
    for (int pin = 0; pin < 4; pin++) {
      digitalWrite(motorPins[pin], seq[index][pin]);
    }
    delay(delayMs);
  }
  for (int pin = 0; pin < 4; pin++) {
    digitalWrite(motorPins[pin], LOW);
  }
}