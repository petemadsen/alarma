#define MP3_PRESS_DOWN 500


void mp3_setup()
{
  pinMode(MP3_NEXT_PIN, OUTPUT);
  pinMode(MP3_PREV_PIN, OUTPUT);
  
  digitalWrite(MP3_NEXT_PIN, HIGH);
  digitalWrite(MP3_PREV_PIN, HIGH);
}



void mp3_next()
{
  Serial.println("mp3-next");
  digitalWrite(MP3_NEXT_PIN, LOW);
  delay(MP3_PRESS_DOWN);
  digitalWrite(MP3_NEXT_PIN, HIGH);
}


void mp3_prev()
{
  Serial.println("mp3-prev");
  digitalWrite(MP3_PREV_PIN, LOW);
  delay(MP3_PRESS_DOWN);
  digitalWrite(MP3_PREV_PIN, HIGH);
}


