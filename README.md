
# What is this?
This is a low level library for communicating with the DS1775 temperature sensor family.

# API

```C++
void DS1775::init( int model );
```
Use `init` in your `setup` function before you use this module. The model parameter is one of the following depending on which chip you have:
`MODEL_DS1775R, MODEL_DS1775R1, MODEL_DS1775R2, MODEL_DS1775R3, MODEL_DS1775R4, MODEL_DS1775R5, MODEL_DS1775R6, MODEL_DS1775R7`


```C++
void DS1775::configure( bool sd, bool tm, bool pol, bool f0
                      , bool f1, bool r0, bool r1 );
```
This configures the chip with the specified flags. See the reference for what they mean.

```C++
Configuration DS1775::get_configuration();
```
Get configuration fetches the current configuration of the chip. The flags are stored in the configuration structure:
```C++
typedef struct {
  bool sd;
  bool tm; 
  bool pol;
  bool f0;
  bool f1;
  bool r0;
  bool r1;
} Configuration;
```

```C++
float DS1775::get_temperature();
```
Fetches the current temperature.

```C++
float DS1775::get_t_os();
float DS1775::get_t_hyst();

void DS1775::set_t_os( float value );
void DS1775::set_t_hyst( float value );
```
Gets/sets the chips high and low temperature triggers.