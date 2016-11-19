#include <EEPROM.h>

#define EE_ADDR_SOUND 0

#define SETTINGS_ENABLED 0xee
#define SETTINGS_DISABLED 0xdd


void settings_setup()
{
}



bool settings_has_sound()
{
  uint8_t snd_mode = EEPROM.read(EE_ADDR_SOUND);
  return snd_mode == SETTINGS_ENABLED;
}

void settings_set_sound(bool b)
{
  EEPROM.write(EE_ADDR_SOUND, b ? SETTINGS_ENABLED : SETTINGS_DISABLED);
}

