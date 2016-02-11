int ledLight = 0;
int startTime = 0;
byte canPress = 1;
byte active = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, INPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if((digitalRead(13) == LOW) && (canPress == 1))
  {
    // Turn on/off led.
    ledLight = !ledLight;
    digitalWrite(4, ledLight);

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
    startTime = millis();
    canPress = 0;
  }

  int diff = millis() - startTime;
  if(diff > 500)
  {
    canPress = 1;
  }
}
