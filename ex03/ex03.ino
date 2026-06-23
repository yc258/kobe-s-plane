const int ledPin = 2;

// 时序参数 和你delay逻辑完全一致
const unsigned long shortOn  = 200;
const unsigned long shortOff = 200;
const unsigned long longOn   = 600;
const unsigned long longOff  = 200;
const unsigned long charGap  = 500;
const unsigned long sosEndGap= 2000;

// 使用int数字状态，支持++自增，无编译报错
int curState = 0;
unsigned long stateStart = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  unsigned long now = millis();
  unsigned long elapsed = now - stateStart;

  switch(curState)
  {
    // 第一段 S：3次短闪 state 0 1 2
    case 0:
    case 1:
    case 2:
      digitalWrite(ledPin, HIGH);
      if(elapsed >= shortOn){
        digitalWrite(ledPin, LOW);
        if(elapsed >= shortOn + shortOff){
          stateStart = now;
          curState = curState + 1;
        }
      }
      break;

    case 3: // S与O之间间隔
      digitalWrite(ledPin, LOW);
      if(elapsed >= charGap){
        stateStart = now;
        curState = 4;
      }
      break;

    // 第二段 O：3次长闪 state 4 5 6
    case 4:
    case 5:
    case 6:
      digitalWrite(ledPin, HIGH);
      if(elapsed >= longOn){
        digitalWrite(ledPin, LOW);
        if(elapsed >= longOn + longOff){
          stateStart = now;
          curState = curState + 1;
        }
      }
      break;

    case 7: // O与末尾S之间间隔
      digitalWrite(ledPin, LOW);
      if(elapsed >= charGap){
        stateStart = now;
        curState = 8;
      }
      break;

    // 第三段 S：3次短闪 state 8 9 10
    case 8:
    case 9:
    case 10:
      digitalWrite(ledPin, HIGH);
      if(elapsed >= shortOn){
        digitalWrite(ledPin, LOW);
        if(elapsed >= shortOn + shortOff){
          stateStart = now;
          curState = curState + 1;
        }
      }
      break;

    case 12: // 整套SOS结束后长时间熄灭等待
      digitalWrite(ledPin, LOW);
      if(elapsed >= sosEndGap){
        stateStart = now;
        curState = 0; // 从头循环SOS
      }
      break;
  }
}