#include <DS1775.h>
#include <Wire.h>

#define TEMPERATURE_POINTER   0x00
#define CONFIGURATION_POINTER 0x01
#define T_HYST_POINTER        0x02
#define T_OS_POINTER          0x03

void DS1775::init( int model ) {
  Wire.begin();
  DS1775::model = model;
  DS1775::pointer = TEMPERATURE_POINTER;
}

void DS1775::configure( bool sd, bool tm, bool pol, bool f0
                     , bool f1, bool r0, bool r1 ) {
  int rawValue = sd | ( tm << 1 ) | ( pol << 2 ) | ( f0 << 3 )
                    | ( f1 << 4 ) | ( r0 << 5 ) | ( r1 << 6 );

  Wire.beginTransmission( DS1775::model );
  Wire.write( CONFIGURATION_POINTER );
  Wire.write( rawValue );
  Wire.endTransmission();
}

float DS1775::get_temperature() {
  return get( TEMPERATURE_POINTER );
}

Configuration DS1775::get_configuration() {
  int rawValue;
  if( DS1775::pointer != CONFIGURATION_POINTER )
    DS1775::switch_pointer( CONFIGURATION_POINTER );

  Wire.requestFrom( DS1775::model, 1 );
  rawValue = Wire.read();
           // SD, TM, POL, F0, F1, R0, R1
  return { rawValue & 1, rawValue & 2, rawValue & 4
         , rawValue & 8, rawValue & 16, rawValue & 32, rawValue & 64 };
}

float DS1775::get_t_os() {
  return DS1775::get( T_OS_POINTER );
}

float DS1775::get_t_hyst() {
  return DS1775::get( T_HYST_POINTER );
}

void DS1775::set_t_os( float value ) {
  DS1775::set( T_OS_POINTER, value );
}

void DS1775::set_t_hyst( float value ) {
  DS1775::set( T_HYST_POINTER, value );
}

float DS1775::get( int pointer ) {
  if( DS1775::pointer != pointer )
    DS1775::switch_pointer( pointer );

  signed short rawValue;

  Wire.requestFrom( DS1775::model, 2 );
  // Read the MSB and LSB
  rawValue = Wire.read() << 8;
  rawValue |= Wire.read();

  // Convert to the floating point number that it represents
  return ((float)rawValue) / 256.0;
}

void DS1775::set( int pointer, float value ) {
  signed short rawValue = (short)( value * 256.0 );

  Wire.beginTransmission( DS1775::model );
  Wire.write( pointer );
  Wire.write( ( rawValue >> 8 ) && 0xFF );
  Wire.write( rawValue && 0xFF );
  Wire.endTransmission();
}

void DS1775::switch_pointer( int pointer ) {
  DS1775::pointer = pointer;

  Wire.beginTransmission( DS1775::model );
  Wire.write( pointer );
  Wire.endTransmission();
}
