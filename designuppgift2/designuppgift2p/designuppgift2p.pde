import processing.sound.*;
import processing.serial.*;

Serial myPort;  
SoundFile[] sounds;
int activeSong = -1;

void setup()
{
  size(600,600);
  
  // Load sounds.
  sounds = new SoundFile[3];
  sounds[0] = new SoundFile(this, "song1.mp3");
  sounds[1] = new SoundFile(this, "song2.mp3");
  sounds[2] = new SoundFile(this, "song3.mp3");
}

void PlaySong(int song)
{
  // Stop current song, if any.
  StopSong();
  
  // Play new song and set it as active.
  sounds[song].play();
  activeSong = song;
  println("Playing song: " + activeSong);
}

void StopSong()
{
  // Stop current song if any is active.
  if(activeSong != -1)
  {
    println("Stoping song: " + activeSong);
    sounds[activeSong].stop();
    activeSong = -1;
  }
}

void draw()
{
  // Create serial connection.
  if(myPort == null)
  {
    try
    {
      String portName = Serial.list()[2];
      println(portName);
      myPort = new Serial(this, portName, 9600);
    }
    catch(Exception ex)
    {
      // Failed to create connection.
      myPort = null;
    }
  }

  // Check for serial data.
  if( myPort.available() > 0) 
  {
    // If data is available, read it.
    String val = myPort.readStringUntil('\n');
    if(val != null)
    {
      // Get the commands.
      String[] commands = val.trim().split(":");
  
      // Check what command it is.
      if(commands[0].compareTo("play") == 0)
      {
        // Play song.
        int songNumber = Integer.parseInt(commands[1]);
        PlaySong(songNumber);
      }
      else if(commands[0].compareTo("stop") == 0)
      {
        // Stop song.
        StopSong();
      }
      else
      {
        // Unknown command.
        println("Error, command \"" + commands[0] + "\"unknown!");
      }
    }
  }
}