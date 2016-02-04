const int buttonPin = 2;
const int ledPin = 8;
const int audioPin = 3;

unsigned int song[] = { 440, 880, 220, 440, 110 };

byte gameState = 0;
int gameSpeed = 400;

byte oldButtonState = 0;
byte buttonState = 0;
byte activeLed = 0;

byte audioState = LOW;

int prevMillis = 0;
int wait = 0;

void setup() {
  // Make the led pins ouput.
  for (int i = 0; i < 5; i++)
  {
    pinMode(ledPin + i, OUTPUT);
  }

  // Make the audio pin output.
  pinMode(audioPin, OUTPUT);

  // Make the button pin input.
  pinMode(buttonPin, INPUT);

  // Reset timer.
  prevMillis = millis();
}

void loop() {
  // Handel button press.
  oldButtonState = buttonState;
  buttonState = digitalRead(buttonPin);

  // Make sure state is only changed once if button is held.
  if ((buttonState == LOW) && (oldButtonState != buttonState))
  {
    gameState = !gameState;

    // Change game speed.
    if (!gameState)
    {
      gameSpeed -= (gameSpeed / 4);
      if (gameSpeed < 1)
      {
        gameSpeed = 1;
      }
    }
  }

  // Update game state.
  if (gameState)
  {
    // Handel timer.
    int ms = millis();
    wait += ms - prevMillis;
    prevMillis = ms;

    if (wait > gameSpeed)
    {
      // Reset wait timer.
      wait = 0;

      // Play sound.
      tone(audioPin, song[activeLed]);

      // Update active led.
      activeLed++;
      if (activeLed >= 5)
      {
        activeLed = 0;
      }
    }
  }

  // Turn of all the leds.
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(ledPin + i, LOW);
  }

  // Turn on active led.
  digitalWrite(ledPin + activeLed, HIGH);
}
