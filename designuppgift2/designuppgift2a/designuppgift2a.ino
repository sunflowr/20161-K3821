int startTime = 0;
byte canPress = 1;
byte playingSong = 0;
byte activeYear = -1;

// Play commands send over to processing.
const char *playCommands[] = {
  "play:0", // 1960
  "play:1", // 1970
  "play:2", // 1980
  "play:3", // 1990
  "play:4", // 2000
  "play:5"  // 2010
};

// Button pins.
const byte btnStart = 13;
const byte btn1960 = 12;
const byte btn1970 = 11;
const byte btn1980 = 10;
const byte btn1990 = 9;
const byte btn2000 = 8;
const byte btn2010 = 7;

// LED pins.
const byte ledCorrect = 3;
const byte ledWrong = 4;

void setup() {
  // Set pin mode.
  pinMode(btnStart, INPUT_PULLUP);
  pinMode(btn1960, INPUT_PULLUP);
  pinMode(btn1970, INPUT_PULLUP);
  pinMode(btn1980, INPUT_PULLUP);
  pinMode(btn1990, INPUT_PULLUP);
  pinMode(btn2000, INPUT_PULLUP);
  pinMode(btn2010, INPUT_PULLUP);
  pinMode(ledCorrect, OUTPUT);
  pinMode(ledWrong, OUTPUT);

  // Start serial.
  Serial.begin(57600);

  Reset();
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
  digitalWrite(ledWrong, LOW);
  digitalWrite(ledCorrect, LOW);
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
    playingSong = !playingSong;
    if(playingSong)
    {
      // Send random year to play.
      activeYear = random(6);
      Serial.println(playCommands[activeYear]);

      // Reset game.
      Reset();
    }
  }

  if(PressedButton(btn1960))
  {
    if(activeYear == 0)
    {
      CorrectAnswear();
    }
    else
    {
      WrongAnswear();
    }

    // Send stop command.
    Serial.println("stop:0");
  }

  if(PressedButton(btn1970))
  {
    if(activeYear == 1)
    {
      CorrectAnswear();
    }
    else
    {
      WrongAnswear();
    }

    // Send stop command.
    Serial.println("stop:1");
  }

  if(PressedButton(btn1980))
  {
    if(activeYear == 2)
    {
      CorrectAnswear();
    }
    else
    {
      WrongAnswear();
    }

    // Send stop command.
    Serial.println("stop:2");
  }

  if(PressedButton(btn1990))
  {
    if(activeYear == 3)
    {
      CorrectAnswear();
    }
    else
    {
      WrongAnswear();
    }

    // Send stop command.
    Serial.println("stop:3");
  }

  if(PressedButton(btn2000))
  {
    if(activeYear == 4)
    {
      CorrectAnswear();
    }
    else
    {
      WrongAnswear();
    }

    // Send stop command.
    Serial.println("stop:4");
  }

  if(PressedButton(btn2010))
  {
    if(activeYear == 5)
    {
      CorrectAnswear();
    }
    else
    {
      WrongAnswear();
    }

    // Send stop command.
    Serial.println("stop:5");
  }
}
