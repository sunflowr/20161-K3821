import processing.sound.*;
import processing.serial.*;

Serial myPort;  
SoundFile[][] sounds;
int activeSongYear = -1;
int activeSong = -1;

void setup()
{
  size(600,600);
  
  // Load sounds.
  sounds = new SoundFile[6][];

  // 1960 songs.
  sounds[0] = new SoundFile[1];
  sounds[0][0] = new SoundFile(this, "1960.mp3");

  // 1970 songs.
  sounds[1] = new SoundFile[1];
  sounds[1][0] = new SoundFile(this, "1970.mp3");

  // 1980 songs.
  sounds[2] = new SoundFile[1];
  sounds[2][0] = new SoundFile(this, "1980.mp3");

  // 1990 songs.
  sounds[3] = new SoundFile[1];
  sounds[3][0] = new SoundFile(this, "1990.mp3");

  // 2000 songs.
  sounds[4] = new SoundFile[1];
  sounds[4][0] = new SoundFile(this, "2000.mp3");

  // 2010 songs.
  sounds[5] = new SoundFile[1];
  sounds[5][0] = new SoundFile(this, "2010.mp3");
}

void PlaySong(int songYear)
{
  // Stop current song, if any.
  StopSong();
  
  // Play random new song from selected year.
  activeSongYear = songYear;
  activeSong = (int)random(0, sounds[activeSongYear].length);
  sounds[activeSongYear][activeSong].play();
  println("Playing song: " + activeSongYear + " " + activeSong);
}

void StopSong()
{
  // Stop current song if any is active.
  if((activeSongYear != -1) && (activeSong != -1))
  {
    println("Stoping song: " + activeSong);
    sounds[activeSongYear][activeSong].stop();
    activeSong = -1;
    activeSongYear = -1;
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
      myPort = new Serial(this, portName, 57600);
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
        int songNumber = Integer.parseInt(commands[1]);
        println("songnumber: " + songNumber);
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