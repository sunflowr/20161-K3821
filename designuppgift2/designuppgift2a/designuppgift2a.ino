int startTime = 0;
byte canPress = 1;
byte active = 0;

const byte btnStart = 13;
const byte btn1960 = 13;
const byte btn1970 = 12;
const byte btn1980 = 11;
const byte btn1990 = 10;
const byte btn2000 = 9;
const byte btn2010 = 8;

const byte ledCorrect = 4;
const byte ledWrong = 3;

void setup() {
  // Set pin mode.
  pinMode(btnStart, INPUT);
  pinMode(btn1960, INPUT);
  pinMode(btn1970, INPUT);
  pinMode(btn1980, INPUT);
  pinMode(btn1990, INPUT);
  pinMode(btn2000, INPUT);
  pinMode(btn2010, INPUT);
  pinMode(ledCorrect, OUTPUT);
  pinMode(ledWrong, OUTPUT);

  // Start serial.
  Serial.begin(9600);
}

void WrongAnswear()
{
  digitalWrite(ledWrong, HIGH);
  digitalWrite(ledCorrect, LOW);
}

void CorrectAnswear()
{
  digitalWrite(ledWrong, LOW);
  digitalWrite(ledCorrect, HIGH);
}

void Reset()
{
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);
}

byte PressedButton(byte button)
{
  // Can't press button until 500ms have passed.
  int diff = millis() - startTime;
  if(diff > 500)
  {
    // 500ms have passed so allow press again.
    canPress = 1;
  }

  // Check if we can press button.
  if((digitalRead(button) == HIGH) && (canPress == 1))
  {
    // Button pressed so reset timer.
    startTime = millis();
    canPress = 0;

    // Can press button.
    return 1;
  }

  // Can't press yet.
  return 0;
}

void loop() {
  if(PressedButton(btnStart))
  {    
    // Play/stop song.
    active = !active;
    if(active)
    {
      Serial.println("play:1");
    }
    else
    {
      Serial.println("stop");
    }
  }

  if(PressedButton(btn1960))
  {
    CorrectAnswear();
  }

  if(PressedButton(btn1970))
  {
    WrongAnswear();
  }
}
