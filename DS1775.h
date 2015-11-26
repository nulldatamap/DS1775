
#define MODEL_DS1775R  0x48
#define MODEL_DS1775R1 0x48 | 1
#define MODEL_DS1775R2 0x48 | 2
#define MODEL_DS1775R3 0x48 | 3
#define MODEL_DS1775R4 0x48 | 4
#define MODEL_DS1775R5 0x48 | 5
#define MODEL_DS1775R6 0x48 | 6
#define MODEL_DS1775R7 0x48 | 7

typedef struct {
  bool sd;
  bool tm; 
  bool pol;
  bool f0;
  bool f1;
  bool r0;
  bool r1;
} Configuration;

class DS1775 {
  public:
    static void init( int model );
    static void configure( bool sd, bool tm, bool pol, bool f0
                         , bool f1, bool r0, bool r1 );
    static float get_temperature();
    static Configuration get_configuration();
    static float get_t_os();
    static float get_t_hyst();

    static void set_t_os( float value );
    static void set_t_hyst( float value );
  private:
    static float get( int pointer );
    static void set( int pointer, float value );
    static void switch_pointer( int pointer );

    static int model;
    static int pointer;
};
