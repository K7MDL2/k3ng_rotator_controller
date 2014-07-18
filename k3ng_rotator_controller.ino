/* Arduino Rotator Controller
   Anthony Good
   K3NG
   anthony.good@gmail.com
  
   Contributions from John Eigenbode, W3SA
   w3sa@arrl.net
   Contributions: AZ/EL testing and debugging, AZ/EL LCD Enhancements, original North center code, Az/El Rotator Control Connector Pins
  
   Contributions from Jim Balls, M0CKE
   makidoja@gmail.com
   Contributions: Rotary Encoder Preset Support
  
   Contributions from Gord, VO1GPK
   Contribution: FEATURE_ADAFRUIT_BUTTONS code
  
   Moon2 and sunpos libraries courtesy of Pete Hardie, VE5VA
  
   Non-English extensions ideas, code, and testing provided by Marcin SP5IOU, Hjalmar OZ1JHM, and Sverre LA3ZA
  
   Testing, ideas, and hardware provided by Anthony M0UPU, Bent OZ1CT, Eric WB6KCN, Norm N3YKF, and many others
  
   Translations: Maximo, EA1DDO
  
 ***************************************************************************************************************
 *
 *  This program is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 *
 *                            http://creativecommons.org/licenses/by-nc-sa/3.0/
 *
 *                        http://creativecommons.org/licenses/by-nc-sa/3.0/legalcode
 *
 *
 ***************************************************************************************************************
  
  
  
  
                            All copyrights are the property of their respective owners
  
 
 
 Full documentation is currently located here: https://docs.google.com/document/d/1Q4_X2XdndylohjhZWsaAUNl1UIqYGt9Kxp1VM70XJGM/edit?usp=sharing

      Rules for using this code:

          Rule #1: Read the documentation.
  
          Rule #2: Refer to rule #1.

          Rule #3: Help others.

          Rule #4: Have fun.

  
  New in this release:
  
   HH-12 encoder support 
   OPTION_PULSE_IGNORE_AMBIGUOUS_PULSES
   \P PWM command is now \W
   \P is Park command
   park_in_progress_pin  // goes high when a park has been initiated and rotation is in progress 
   parked_pin            // goes high when in a parked position 
    heading_reading_inhibit_pin 
    FEATURE_LIMIT_SENSE 
   #define az_limit_sense_pin 0  // input - low stops azimuthal rotation 
   #define el_limit_sense_pin 0  // input - low stops elevation rotation 
    \Axxx command - manually set azimuth, xxx = azimuth (FEATURE_AZ_POSITION_ROTARY_ENCODER or FEATURE_AZ_POSITION_PULSE_INPUT only) 
    \Bxxx command - manually set elevation, xxx = elevation (FEATURE_EL_POSITION_POTENTIOMETER or FEATURE_EL_POSITION_ROTARY_ENCODER only) 
    fixed bug with preset encoder start and kill button
    FEATURE_AZ_POSITION_INCREMENTAL_ENCODER
    FEATURE_EL_POSITION_INCREMENTAL_ENCODER
    OPTION_INCREMENTAL_ENCODER_PULLUPS
   #define AZ_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV 8000.0
   #define EL_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV 8000.0
    AZIMUTH_STARTING_POINT_DEFAULT and AZIMUTH_ROTATION_CAPABILITY_DEFAULT are now persistent
    Yaesu P35, P45, and Z commands no longer write to eeprom 
    control_port points to the hardware port for computer interface
    remote_unit_port points to the hardware port for interfacing to remote unit
    removed OPTION_SERIAL1, 2, 3, 4
    SS command: SS0 = control port, SS1 = remote unit port
    No longer need to manually uncomment hh12.h or object declarations
    No longer need to manually uncomment LiquidCrystal lcd() 
    No longer need to manually uncomment Adafruit_ADXL345 accel 
    No longer need to manually uncomment ADXL345 accel 
    No longer need to manually uncomment Adafruit_LSM303 lsm;
    No longer need to manually uncomment HMC5883L compass;
    FEATURE_4_BIT_LCD_DISPLAY 
    FEATURE_ADAFRUIT_I2C_LCD 
    FEATURE_YOURDUINO_I2C_LCD 
    FEATURE_RFROBOT_I2C_DISPLAY 
    No longer need to uncomment:
     FEATURE_LCD_DISPLAY 
     FEATURE_I2C_LCD 
     any include files 
    serial led duration now set by SERIAL_LED_TIME_MS
   #define CONTROL_PORT_MAPPED_TO &Serial  // change this line to map the control port to a different serial port (Serial1, Serial2, etc.) 
   #define REMOTE_PORT_MAPPED_TO &Serial1  // change this line to map the remote_unit port to a different serial port 
    start of remote unit pin control
    remote unit pin control (add 100 to a pin number define to map to remote unit pin) 
    FEATURE_CLOCK 
    FEATURE_MOON_TRACKING 
   #define DEFAULT_LATITUDE 40.889958 
   #define DEFAULT_LONGITUDE -75.585972 
  
   #define INTERNAL_CLOCK_CORRECTION 0.00145
  
    \C - show clock 
    \O - set clock \OYYYYMMDDHHmm 
    \Mx - x = 0: deactive moon tracking; x = 1: activate moon tracking 
    \Gxxxxxx - set coordinates via grid square (example: \GFN20EV) 
  
    Park is now deactivated when issuing a Yaesu command (other than C) or when doing manual rotation
    FEATURE_GPS
   #define GPS_PORT_MAPPED_TO &Serial2 
   #define GPS_PORT_BAUD_RATE 9600 
   #define SYNC_TIME_WITH_GPS 1 
   #define SYNC_COORDINATES_WITH_GPS 1 
   #define GPS_SYNC_PERIOD_SECONDS 10  // how long to consider internal clock syncronized after a GPS reading 
   #define GPS_VALID_FIX_AGE_MS 10000  // consider a GPS reading valid if the fix age is less than this 
    FEATURE_SUN_TRACKING 
      \Ux - x = 0: deactive sun tracking; x = 1: activate sun tracking  
    FEATURE_AZ_POSITION_INCREMENTAL_ENCODER & FEATURE_EL_POSITION_INCREMENTAL_ENCODER coding
    Updated debug output format
    \XS - calibration az and el to sun heading - there are calculation bugs
    fixed initialize_serial() compilaton error when neither yaesu or easycom protocol is selected in features
    fixed bugs in \XS and \XM
    \XS and\XM now working on all sensor types 
    moon_tracking_active_pin   
    sun_tracking_active_pin      
    moon_tracking_activate_line    
    sun_tracking_activate_line     
    moon_tracking_button  
    sun_tracking_button   
    \A azimuth calibration now also works with sensors other than rotary encoders and pulse input
    \B elevation calibration now also works with sensors other than rotary encoders and pulse input
    OPTION_BUTTON_RELEASE_NO_SLOWDOWN 
    Fixed God-awful bug that caused Arduino to crash when running FEATURE_GPS.  Note to self: never declare a char in a switch case.  It causes unpredicatable, unexplainable evil stuff to occur.
    Fixed bug with elevation PWM
     gps_sync pin - goes high when clock is GPS synchronized 
     FEATURE_RTC_PCF8583 
    \O command also programs realtime clocks now
    Fixed bug in PWM outputs when changing direction
    Ethernet now working with backslash commands, Yaesu commands, and Easycom commands
    Fixed bug in Easycom (non-standard) AZ and EL commands
    Ethernet remote unit slave support (slave only, master using ethernet not done yet)
    #define GPS_MIRROR_PORT &Serial3   
    OPTION_DISPLAY_SMALL_CLOCK
      #define LCD_SMALL_CLOCK_POSITION LEFT
    OPTION_DISPLAY_GPS_INDICATOR
      #define LCD_GPS_INDICATOR_POSITION RIGHT
    OPTION_DISPLAY_MOON_TRACKING_CONTINUOUSLY
      #define LCD_MOON_TRACKING_ROW 3
      #define LCD_MOON_TRACKING_UPDATE_INTERVAL 5000    
    OPTION_DISPLAY_SUN_TRACKING_CONTINUOUSLY
      #define LCD_SUN_TRACKING_ROW 4
      #define LCD_SUN_TRACKING_UPDATE_INTERVAL 5000  
    #define LCD_ROWS 4  
    fixed bug with Yourduino LCD display initialization (thanks PA3FPQ)
    added GPS counters to debug output
    FEATURE_POWER_SWITCH
      #define POWER_SWITCH_IDLE_TIMEOUT 15  (unit: minutes)
      #define power_switch 0
    OPTION_DISPLAY_MOON_OR_SUN_TRACKING_CONDITIONAL
      #define LCD_MOON_OR_SUN_TRACKING_CONDITIONAL_ROW 3
    OPTION_DISPLAY_BIG_CLOCK
    #define GPS_UPDATE_LATENCY_COMPENSATION_MS 200
    #define AZIMUTH_CALIBRATION_FROM_ARRAY {180,630} 
    #define AZIMUTH_CALIBRATION_TO_ARRAY {180,630}
    #define ELEVATION_CALIBRATION_FROM_ARRAY {-180,0,180}
    #define ELEVATION_CALIBRATION_TO_ARRAY {-180,0,180}
    #define rotate_cw_ccw  0
    #define az_stepper_motor_direction 0
    #define el_stepper_motor_direction 0
    bug fix for long clock display
    performance improvement for az / el display on LCD
    #define az_stepper_motor_pulse 0
    #define el_stepper_motor_pulse 0  
    OPTION_DISPLAY_ALT_HHMM_CLOCK_AND_MAIDENHEAD 
    #define LCD_SMALL_CLOCK_AND_MAIDENHEAD_POSITION 
    #define LCD_SMALL_CLOCK_AND_MAIDENHEAD_ROW 4 
    #define LCD_GPS_INDICATOR_ROW 1 
    OPTION_EXTERNAL_ANALOG_REFERENCE
    more debug_print conversion

    OPTION_DISPLAY_SMALL_CLOCK renamed to OPTION_DISPLAY_HHMM_CLOCK 
    LCD_SMALL_CLOCK_POSITION renamed to LCD_HHMM_CLOCK_POSITION 
    OPTION_DISPLAY_HHMMSS_CLOCK 
    OPTION_DISPLAY_DISABLE_DIRECTION_STATUS 
    OPTION_DISPLAY_SMALL_CLOCK_AND_MAIDENHEAD renamed to OPTION_DISPLAY_ALT_HHMM_CLOCK_AND_MAIDENHEAD 
    OPTION_DISPLAY_CONSTANT_HHMMSS_CLOCK_AND_MAIDENHEAD 

    #define LCD_HHMM_CLOCK_POSITION LEFT          //LEFT or RIGHT  
    #define LCD_HHMMSS_CLOCK_POSITION LEFT          //LEFT or RIGHT 
    #define LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_POSITION LEFT 
    #define LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_ROW 1 
    #define LCD_CONSTANT_HHMMSS_CLOCK_AND_MAIDENHEAD_POSITION LEFT 
    #define LCD_CONSTANT_HHMMSS_CLOCK_AND_MAIDENHEAD_ROW 1 

    OPTION_DISPLAY_DISABLE_DIRECTION_STATUS changed to OPTION_DISPLAY_DIRECTION_STATUS 
    worked on FEATURE_TWO_DECIMAL_PLACE_HEADINGS
    LANGUAGE_ENGLISH

    Easycom improvements - space and LF are now also command delimiters.  Also fixed bug with one decimal place.  Works with PSTRotator
    Fixed issue with LCD display updating when target az or target el was changed during rotation
    I2C_LCD_COLOR also applies to Yourduino LCD display

    HH-12 elevation bug fix

    FEATURE_MASTER_WITH_SERIAL_SLAVE
    FEATURE_MASTER_WITH_ETHERNET_SLAVE
    FEATURE_EL_POSITION_MEMSIC_2125  under development - not working yet

    fixed a bug with azimuth and elevation offset zeroing out first decimal place
    Ethernet master/slave link!
    #define ETHERNET_SLAVE_IP_ADDRESS 192,168,1,173
    #define ETHERNET_SLAVE_TCP_PORT 23
    #define ETHERNET_SLAVE_RECONNECT_TIME_MS 250

    Changed master/slave AZ and EL command result format: AZxxx.xxxxxx EL+xxx.xxxxxx
    Slave CL command

    OPTION_SYNC_MASTER_CLOCK_TO_SLAVE

    fixed "if (clock_status == SLAVE_SYNC) {clock_status = FREE_RUNNING;}" compile error

    OPTION_CLOCK_ALWAYS_HAVE_HOUR_LEADING_ZERO

    OPTION_DISABLE_HMC5883L_ERROR_CHECKING
    HARDWARE_EA4TX_ARS_USB
    HARDWARE_M0UPU
    rotator_hardware.h file
    rotator_features_ea4tx_ars_usb.h
    rotator_pins_ea4tx_ars_usb.h
    #define AZ_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV 2000.0
    #define EL_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV 2000.0

    FEATURE_EL_POSITION_INCREMENTAL_ENCODER now does 360 degrees of rotation rather than 720

    OPTION_PRESET_ENCODER_0_360_DEGREES

    service_rotation() - fixed rollover bug with az and el slow down

    Fixed decimal place issue with Easycom AZ and EL query commands
    FEATURE_EL_POSITION_INCREMENTAL_ENCODER - fixed storage and retrieval of elevation in eeprom
    Bug fix - stop command wouldn't work when in slow down
    AZ_INITIALLY_IN_SLOW_DOWN_PWM
    EL_INITIALLY_IN_SLOW_DOWN_PWM 

    Fixed compilation error when FEATURE_JOYSTICK_CONTROL is activated and FEATURE_ELEVATION_CONTROL is disabled

  Not documented yet:

    FEATURE_ANALOG_OUTPUT_PINS
    FEATURE_AZ_POSITION_LSM303 is now FEATURE_AZ_POSITION_ADAFRUIT_LSM303
    FEATURE_EL_POSITION_LSM303 is now FEATURE_EL_POSITION_ADAFRUIT_LSM303

  */

#define CODE_VERSION "2.0.2014071801"

#include <avr/pgmspace.h>
#include <EEPROM.h>
#include <math.h>
#include <avr/wdt.h>
#include "rotator_hardware.h"
#ifdef HARDWARE_EA4TX_ARS_USB
#include "rotator_features_ea4tx_ars_usb.h"
#else
#include "rotator_features.h"
#endif
#include "rotator_dependencies.h"

#ifdef FEATURE_4_BIT_LCD_DISPLAY
#include <LiquidCrystal.h>  // required for classic 4 bit interface LCD display (FEATURE_4_BIT_LCD_DISPLAY)
#endif // FEATURE_4_BIT_LCD_DISPLAY
#ifdef FEATURE_WIRE_SUPPORT
#include <Wire.h>  // required for FEATURE_I2C_LCD, any ADXL345 feature, FEATURE_AZ_POSITION_HMC5883L, FEATURE_EL_POSITION_ADAFRUIT_LSM303
#endif
#if defined(FEATURE_ADAFRUIT_I2C_LCD)
#include <Adafruit_MCP23017.h> // required for Adafruit I2C LCD display
#include <Adafruit_RGBLCDShield.h> // required for Adafruit I2C LCD display
#endif
#if defined(FEATURE_YOURDUINO_I2C_LCD) || defined(FEATURE_RFROBOT_I2C_DISPLAY)
#include <LiquidCrystal_I2C.h> // required for YourDuino.com or DFRobot I2C LCD display
#endif
#if defined(FEATURE_YOURDUINO_I2C_LCD)
#include <LCD.h>   // required for YourDuino.com I2C LCD display
#endif
#if defined(FEATURE_AZ_POSITION_HMC5883L)
#include <HMC5883L.h> // required for HMC5883L digital compass support
#endif
#if defined(FEATURE_EL_POSITION_ADXL345_USING_ADAFRUIT_LIB) || defined(FEATURE_AZ_POSITION_ADAFRUIT_LSM303) || defined(FEATURE_EL_POSITION_ADAFRUIT_LSM303)
#include <Adafruit_Sensor.h>    // required for any Adafruit sensor libraries
#endif
#if defined(FEATURE_EL_POSITION_ADXL345_USING_LOVE_ELECTRON_LIB)
#include <ADXL345.h>  // required for elevation ADXL345 accelerometer using Love Electronics ADXL345 library
#endif
#if defined(FEATURE_EL_POSITION_ADXL345_USING_ADAFRUIT_LIB)
#include <Adafruit_ADXL345_U.h>   // required for elevation ADXL345 accelerometer using Adafruit ADXL345 library (FEATURE_EL_POSITION_ADXL345_USING_ADAFRUIT_LIB)
#endif
#if defined(FEATURE_EL_POSITION_ADAFRUIT_LSM303) || defined(FEATURE_AZ_POSITION_ADAFRUIT_LSM303)
#include <Adafruit_LSM303.h>     // required for azimuth and/or elevation using LSM303 compass and/or accelerometer
#endif
#if defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)
#include "moon2.h"
#endif // defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)
#ifdef FEATURE_SUN_TRACKING
#include "sunpos.h"
#endif // FEATURE_SUN_TRACKING
#ifdef FEATURE_GPS
#include "TinyGPS.h"
#endif // FEATURE_GPS
#ifdef FEATURE_RTC_DS1307
#include "RTClib.h"
#endif // FEATURE_RTC_DS1307
#ifdef FEATURE_RTC_PCF8583
#include "PCF8583.h"
#endif //FEATURE_RTC_PCF8583
#ifdef FEATURE_ETHERNET
#include "SPI.h"
#include "Ethernet.h"
#endif

#include "rotator.h"
#ifdef HARDWARE_EA4TX_ARS_USB
#include "rotator_pins_ea4tx_ars_usb.h"
#endif
#ifdef HARDWARE_M0UPU
#include "rotator_pins_m0upu.h"
#endif
#if !defined(HARDWARE_M0UPU) && !defined(HARDWARE_EA4TX_ARS_USB)
#include "rotator_pins.h"
#endif
#include "rotator_settings.h"






/*----------------------- variables -------------------------------------*/

byte incoming_serial_byte = 0;

#ifdef FEATURE_TWO_DECIMAL_PLACE_HEADINGS
long azimuth = 0;
long raw_azimuth = 0;
long target_azimuth = 0;
long target_raw_azimuth = 0;
long azimuth_starting_point = AZIMUTH_STARTING_POINT_DEFAULT;
long azimuth_rotation_capability = AZIMUTH_ROTATION_CAPABILITY_DEFAULT;
#else
int azimuth = 0;
int raw_azimuth = 0;
int target_azimuth = 0;
int target_raw_azimuth = 0;
int azimuth_starting_point = AZIMUTH_STARTING_POINT_DEFAULT;
int azimuth_rotation_capability = AZIMUTH_ROTATION_CAPABILITY_DEFAULT;
#endif




byte control_port_buffer[COMMAND_BUFFER_SIZE];
int control_port_buffer_index = 0;
byte az_state = IDLE;
byte debug_mode = DEFAULT_DEBUG_STATE;
int analog_az = 0;
unsigned long last_debug_output_time = 0;
unsigned long az_last_rotate_initiation = 0;
byte azimuth_button_was_pushed = 0;
byte brake_az_engaged = 0;
byte brake_el_engaged = 0;
byte configuration_dirty = 0;
unsigned long last_serial_receive_time = 0;

byte az_slowstart_active = AZ_SLOWSTART_DEFAULT;
byte az_slowdown_active = AZ_SLOWDOWN_DEFAULT;

byte az_request = 0;
int az_request_parm = 0;
byte az_request_queue_state = NONE;

unsigned long az_slowstart_start_time = 0;
byte az_slow_start_step = 0;
unsigned long az_last_step_time = 0;
byte az_slow_down_step = 0;
unsigned long az_timed_slow_down_start_time = 0;
byte backslash_command = 0;

struct config_t {
  byte magic_number;
  int analog_az_full_ccw;
  int analog_az_full_cw;
  int analog_el_0_degrees;
  int analog_el_max_elevation;
  // int azimuth_starting_point;
  // int azimuth_rotation_capability;
  float last_azimuth;
  float last_elevation;
  int last_az_incremental_encoder_position;
  int last_el_incremental_encoder_position;
  float azimuth_offset;
  float elevation_offset;
} configuration;




#ifdef FEATURE_TIMED_BUFFER
int timed_buffer_azimuths[TIMED_INTERVAL_ARRAY_SIZE];
int timed_buffer_number_entries_loaded = 0;
int timed_buffer_entry_pointer = 0;
int timed_buffer_interval_value_seconds = 0;
unsigned long last_timed_buffer_action_time = 0;
byte timed_buffer_status = 0;
#endif // FEATURE_TIMED_BUFFER

byte normal_az_speed_voltage = 0;
byte current_az_speed_voltage = 0;

#ifdef FEATURE_ELEVATION_CONTROL
int elevation = 0;
int target_elevation = 0;

byte el_request = 0;
int el_request_parm = 0;
byte el_request_queue_state = NONE;
byte el_slowstart_active = EL_SLOWSTART_DEFAULT;
byte el_slowdown_active = EL_SLOWDOWN_DEFAULT;
unsigned long el_slowstart_start_time = 0;
byte el_slow_start_step = 0;
unsigned long el_last_step_time = 0;
byte el_slow_down_step = 0;
unsigned long el_timed_slow_down_start_time = 0;
byte normal_el_speed_voltage = 0;
byte current_el_speed_voltage = 0;

int display_elevation = 0;
byte el_state = IDLE;
int analog_el = 0;

unsigned long el_last_rotate_initiation = 0;
#ifdef FEATURE_TIMED_BUFFER
int timed_buffer_elevations[TIMED_INTERVAL_ARRAY_SIZE];
#endif // FEATURE_TIMED_BUFFER
byte elevation_button_was_pushed = 0;
#endif // FEATURE_ELEVATION_CONTROL

#ifdef FEATURE_LCD_DISPLAY
unsigned long last_lcd_update = 0;
String last_row_0_string;  // this is only used in update_display(), however if you make it a static within the funtion, the compiler errors out with a strange error
byte push_lcd_update = 0;


//#ifdef FEATURE_I2C_LCD
//byte lcdcolor = I2C_LCD_COLOR;  
//#endif // FEATURE_I2C_LCD
#endif // FEATURE_LCD_DISPLAY

#ifdef FEATURE_ROTARY_ENCODER_SUPPORT
#ifdef OPTION_ENCODER_HALF_STEP_MODE      // Use the half-step state table (emits a code at 00 and 11)
const unsigned char ttable[6][4] = {
  { 0x3,  0x2,  0x1, 0x0  }, { 0x23, 0x0,  0x1, 0x0  },
  { 0x13, 0x2,  0x0, 0x0  }, { 0x3,  0x5,  0x4, 0x0  },
  { 0x3,  0x3,  0x4, 0x10 }, { 0x3,  0x5,  0x3, 0x20 }
};
#else                                      // Use the full-step state table (emits a code at 00 only)
const unsigned char ttable[7][4] = {
  { 0x0, 0x2, 0x4, 0x0  }, { 0x3, 0x0, 0x1, 0x10 },
  { 0x3, 0x2, 0x0, 0x0  }, { 0x3, 0x2, 0x1, 0x0  },
  { 0x6, 0x0, 0x4, 0x0  }, { 0x6, 0x5, 0x0, 0x10 },
  { 0x6, 0x5, 0x4, 0x0  },
};
#endif // OPTION_ENCODER_HALF_STEP_MODE
#ifdef FEATURE_AZ_PRESET_ENCODER            // Rotary Encoder State Tables
#if defined(FEATURE_ONE_DECIMAL_PLACE_HEADINGS) || defined(FEATURE_TWO_DECIMAL_PLACE_HEADINGS)
double az_encoder_raw_degrees = 0;
#else
int az_encoder_raw_degrees = 0;
#endif
volatile unsigned char az_encoder_state = 0;
#ifdef FEATURE_EL_PRESET_ENCODER
volatile unsigned char el_encoder_state = 0;
#if defined(FEATURE_ONE_DECIMAL_PLACE_HEADINGS) || defined(FEATURE_TWO_DECIMAL_PLACE_HEADINGS)
double el_encoder_degrees = 0;
#else
int el_encoder_degrees = 0;
#endif
#endif // FEATURE_EL_PRESET_ENCODER
byte preset_encoders_state = ENCODER_IDLE;
#endif // FEATURE_AZ_PRESET_ENCODER
#endif // FEATURE_ROTARY_ENCODER_SUPPORT

#ifdef DEBUG_PROFILE_LOOP_TIME
float average_loop_time = 0;
#endif // DEBUG_PROFILE_LOOP_TIME

#ifdef FEATURE_AZ_POSITION_PULSE_INPUT
volatile float az_position_pulse_input_azimuth = 0;
volatile byte last_known_az_state = 0;
#endif // FEATURE_AZ_POSITION_PULSE_INPUT

#ifdef FEATURE_EL_POSITION_PULSE_INPUT
volatile float el_position_pulse_input_elevation = 0;
volatile byte last_known_el_state = 0;
#endif // FEATURE_EL_POSITION_PULSE_INPUT

#if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) 
byte serial_read_event_flag[] = { 0, 0, 0, 0, 0 };
byte control_port_buffer_carriage_return_flag = 0;
#endif

#if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
byte remote_unit_port_buffer[COMMAND_BUFFER_SIZE];
int remote_unit_port_buffer_index = 0;
byte remote_unit_port_buffer_carriage_return_flag = 0;
unsigned long serial1_last_receive_time = 0;
byte remote_unit_command_submitted = 0;
unsigned long last_remote_unit_command_time = 0;
unsigned int remote_unit_command_timeouts = 0;
unsigned int remote_unit_bad_results = 0;
unsigned long remote_unit_good_results = 0;
unsigned int remote_unit_incoming_buffer_timeouts = 0;
byte remote_unit_command_results_available = 0;
float remote_unit_command_result_float = 0;
byte remote_port_rx_sniff = 0;
byte remote_port_tx_sniff = 0;
byte suspend_remote_commands = 0;
#endif //FEATURE_MASTER_WITH_SERIAL_SLAVE


#ifdef DEBUG_POSITION_PULSE_INPUT
// unsigned int az_position_pule_interrupt_handler_flag = 0;
// unsigned int el_position_pule_interrupt_handler_flag = 0;
volatile unsigned long az_pulse_counter = 0;
volatile unsigned long el_pulse_counter = 0;
volatile unsigned int az_pulse_counter_ambiguous = 0;
volatile unsigned int el_pulse_counter_ambiguous = 0;
#endif // DEBUG_POSITION_PULSE_INPUT

#ifdef FEATURE_PARK
byte park_status = NOT_PARKED;
byte park_serial_initiated = 0;
#endif // FEATURE_PARK

#ifdef FEATURE_AZ_POSITION_INCREMENTAL_ENCODER
volatile int az_incremental_encoder_position = 0;
volatile byte az_3_phase_encoder_last_phase_a_state = 0;
volatile byte az_3_phase_encoder_last_phase_b_state = 0;
#ifdef DEBUG_AZ_POSITION_INCREMENTAL_ENCODER
volatile int az_position_incremental_encoder_interrupt = 0;
#endif // DEBUG_AZ_POSITION_INCREMENTAL_ENCODER
#endif // FEATURE_AZ_POSITION_INCREMENTAL_ENCODER

#ifdef FEATURE_EL_POSITION_INCREMENTAL_ENCODER
volatile int el_incremental_encoder_position = 0;
volatile byte el_3_phase_encoder_last_phase_a_state = 0;
volatile byte el_3_phase_encoder_last_phase_b_state = 0;
#ifdef DEBUG_EL_POSITION_INCREMENTAL_ENCODER
volatile int el_position_incremental_encoder_interrupt = 0;
#endif // DEBUG_EL_POSITION_INCREMENTAL_ENCODER
#endif // FEATURE_EL_POSITION_INCREMENTAL_ENCODER

#if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION) || defined(FEATURE_CLOCK)
HardwareSerial * control_port;
#endif

#if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE)
HardwareSerial * remote_unit_port;
#endif

#if defined(FEATURE_GPS)
HardwareSerial * gps_port;
#ifdef GPS_MIRROR_PORT
HardwareSerial * (gps_mirror_port);
#endif //GPS_MIRROR_PORT
#endif //defined(FEATURE_GPS)

#if defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)
double latitude = DEFAULT_LATITUDE;
double longitude = DEFAULT_LONGITUDE;
#endif


#ifdef FEATURE_MOON_TRACKING
byte moon_tracking_active = 0;
byte moon_visible = 0;
double moon_azimuth = 0;
double moon_elevation = 0;
#endif // FEATURE_MOON_TRACKING

#ifdef FEATURE_SUN_TRACKING
float sun_azimuth = 0;
float sun_elevation = 0;
cTime c_time;
cLocation c_loc;
cSunCoordinates c_sposn;
byte sun_visible = 0;
byte sun_tracking_active = 0;
#endif // FEATURE_SUN_TRACKING

#ifdef FEATURE_CLOCK
unsigned long clock_years = 0;
unsigned long clock_months = 0;
unsigned long clock_days = 0;
unsigned long clock_hours = 0;
unsigned long clock_minutes = 0;
unsigned long clock_seconds = 0;
int clock_year_set = 2014;
byte clock_month_set = 1;
byte clock_day_set = 1;
byte clock_sec_set = 0;
unsigned long clock_hour_set = 0;
unsigned long clock_min_set = 0;
unsigned long millis_at_last_calibration = 0;
#endif // FEATURE_CLOCK

#if defined(FEATURE_GPS) || defined(FEATURE_RTC) || defined(FEATURE_CLOCK)
byte clock_status = FREE_RUNNING;
#endif // defined(FEATURE_GPS) || defined(FEATURE_RTC)

#ifdef FEATURE_GPS
byte gps_data_available = 0;
#endif // FEATURE_GPS

#ifdef FEATURE_ETHERNET
byte mac[] = {ETHERNET_MAC_ADDRESS};
IPAddress ip(ETHERNET_IP_ADDRESS);
IPAddress gateway(ETHERNET_IP_GATEWAY);
IPAddress subnet(ETHERNET_IP_SUBNET_MASK);
EthernetClient ethernetclient0;
EthernetServer ethernetserver0(ETHERNET_TCP_PORT_0);
#ifdef ETHERNET_TCP_PORT_1
EthernetClient ethernetclient1;
EthernetServer ethernetserver1(ETHERNET_TCP_PORT_1);
#endif //ETHERNET_TCP_PORT_1
#ifdef FEATURE_MASTER_WITH_ETHERNET_SLAVE
EthernetClient ethernetslavelinkclient0;
IPAddress slave_unit_ip(ETHERNET_SLAVE_IP_ADDRESS);
byte ethernetslavelinkclient0_state = ETHERNET_SLAVE_DISCONNECTED;
unsigned int ethernet_slave_reconnects = 0;
#endif //FEATURE_MASTER_WITH_ETHERNET_SLAVE
#endif //FEATURE_ETHERNET

#ifdef FEATURE_POWER_SWITCH
unsigned long last_activity_time = 0;
#endif //FEATURE_POWER_SWITCH

#ifdef FEATURE_STEPPER_MOTOR
byte az_stepper_motor_last_direction = STEPPER_UNDEF;
byte az_stepper_motor_last_pin_state = LOW;
#ifdef FEATURE_STEPPER_MOTOR_EXPERIMENTAL_CODE
unsigned long az_stepper_pulse_period_us = 0;
unsigned long az_stepper_pulses_remaining = 0;
#ifdef FEATURE_ELEVATION_CONTROL
unsigned long el_stepper_pulse_period_us = 0;
unsigned long el_stepper_pulses_remaining = 0;
#endif //FEATURE_ELEVATION_CONTROL
#endif //FEATURE_STEPPER_MOTOR_EXPERIMENTAL_CODE
#ifdef FEATURE_ELEVATION_CONTROL
byte el_stepper_motor_last_direction = STEPPER_UNDEF;
byte el_stepper_motor_last_pin_state = LOW;
#endif //FEATURE_ELEVATION_CONTROL
#endif //FEATURE_STEPPER_MOTOR


#ifdef FEATURE_AZIMUTH_CORRECTION
float azimuth_calibration_from[]  = AZIMUTH_CALIBRATION_FROM_ARRAY;    
float azimuth_calibration_to[]    = AZIMUTH_CALIBRATION_TO_ARRAY;
#endif // FEATURE_AZIMUTH_CORRECTION

#ifdef FEATURE_ELEVATION_CORRECTION
float elevation_calibration_from[]  = ELEVATION_CALIBRATION_FROM_ARRAY;
float elevation_calibration_to[]    = ELEVATION_CALIBRATION_TO_ARRAY;
#endif // FEATURE_ELEVATION_CORRECTION

/* ------------------ let's start doing some stuff now that we got the formalities out of the way --------------------*/

void setup() {

  delay(1000);

  initialize_serial();

  initialize_peripherals();

  read_settings_from_eeprom();

  initialize_pins();

  read_azimuth(0);
  #ifdef FEATURE_YAESU_EMULATION
  //report_current_azimuth();      // Yaesu - report the azimuth right off the bat without a C command; the Arduino doesn't wake up quick enough
                                 // to get first C command from HRD and if HRD doesn't see anything it doesn't connect
  #endif // FEATURE_YAESU_EMULATION

  #ifdef FEATURE_TIMED_BUFFER
  timed_buffer_status = EMPTY;
  #endif // FEATURE_TIMED_BUFFER

  #ifdef FEATURE_LCD_DISPLAY
  initialize_display();
  #endif

  initialize_rotary_encoders();

  initialize_interrupts();


} /* setup */

/*-------------------------- here's where the magic happens --------------------------------*/

void loop() {

  check_serial();
  read_headings();
  #ifndef FEATURE_REMOTE_UNIT_SLAVE
  service_request_queue();
  service_rotation();
  az_check_operation_timeout();
  #ifdef FEATURE_TIMED_BUFFER
  check_timed_interval();
  #endif // FEATURE_TIMED_BUFFER
  read_headings();
  check_buttons();
  check_overlap();
  check_brake_release();
  #ifdef FEATURE_ELEVATION_CONTROL
  el_check_operation_timeout();
  #endif
  #endif // ndef FEATURE_REMOTE_UNIT_SLAVE

  read_headings();

  #ifdef FEATURE_LCD_DISPLAY
  update_display();
  #endif

  read_headings();

  #ifndef FEATURE_REMOTE_UNIT_SLAVE
  #ifdef OPTION_AZ_MANUAL_ROTATE_LIMITS
  check_az_manual_rotate_limit();
  #endif


  #ifdef OPTION_EL_MANUAL_ROTATE_LIMITS
  check_el_manual_rotate_limit();
  #endif

  check_az_speed_pot();

  #ifdef FEATURE_AZ_PRESET_ENCODER            // Rotary Encoder or Preset Selector
  check_preset_encoders();
  #else
  check_az_preset_potentiometer();
  #endif // FEATURE_AZ_PRESET_ENCODER
  #endif // ndef FEATURE_REMOTE_UNIT_SLAVE

  #ifdef DEBUG_DUMP
  output_debug();
  #endif //DEBUG_DUMP

  check_for_dirty_configuration();

  read_headings();

  #ifdef DEBUG_PROFILE_LOOP_TIME
  profile_loop_time();
  #endif //DEBUG_PROFILE_LOOP_TIME

  #ifdef FEATURE_REMOTE_UNIT_SLAVE
  service_remote_unit_serial_buffer();
  #endif // FEATURE_REMOTE_UNIT_SLAVE

  #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
  service_remote_communications_incoming_buffer();
  #endif // defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)

  #ifdef FEATURE_JOYSTICK_CONTROL
  check_joystick();
  #endif // FEATURE_JOYSTICK_CONTROL

  #ifdef FEATURE_ROTATION_INDICATOR_PIN
  service_rotation_indicator_pin();
  #endif // FEATURE_ROTATION_INDICATOR_PIN

  #ifdef FEATURE_PARK
  service_park();
  #endif // FEATURE_PARK

  #ifdef FEATURE_LIMIT_SENSE
  check_limit_sense();
  #endif // FEATURE_LIMIT_SENSE

  #ifdef FEATURE_MOON_TRACKING
  service_moon_tracking();
  #endif // FEATURE_MOON_TRACKING

  #ifdef FEATURE_SUN_TRACKING
  service_sun_tracking();
  #endif // FEATURE_SUN_TRACKING

  #ifdef FEATURE_GPS
  service_gps();
  #endif // FEATURE_GPS

  #ifdef FEATURE_RTC
  service_rtc();
  #endif // FEATURE_RTC

  #ifdef FEATURE_ETHERNET
  service_ethernet();
  #endif // FEATURE_ETHERNET

  #ifdef FEATURE_POWER_SWITCH
  service_power_switch();
  #endif //FEATURE_POWER_SWITCH

  #if defined(FEATURE_CLOCK) && defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE) && (defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE))
  sync_master_clock_to_slave();
  #endif

  service_blink_led();

  #ifdef FEATURE_ANALOG_OUTPUT_PINS
  service_analog_output_pins();
  #endif //FEATURE_ANALOG_OUTPUT_PINS


} /* loop */
/* -------------------------------------- subroutines -----------------------------------------------
 
                                  Where the real work happens...
 
 */

void read_headings(){

  read_azimuth(0);

  #ifdef FEATURE_ELEVATION_CONTROL
  read_elevation(0);
  #endif

}

// --------------------------------------------------------------

void service_blink_led(){


  #ifdef blink_led
  static unsigned long last_blink_led_transition = 0;
  static byte blink_led_status = 0;


  if (((millis() - last_blink_led_transition) >= 1000) && (blink_led != 0)) {
    if (blink_led_status) {
      digitalWriteEnhanced(blink_led, LOW);
      blink_led_status = 0;
    } else {
      digitalWriteEnhanced(blink_led, HIGH);
      blink_led_status = 1;
    }
    last_blink_led_transition = millis();
  }
  #endif // blink_led



} /* service_blink_led */


// --------------------------------------------------------------
#ifdef DEBUG_PROFILE_LOOP_TIME
void profile_loop_time(){

  static unsigned long last_time = 0;
  static unsigned long last_print_time = 0;


  average_loop_time = (average_loop_time + (millis() - last_time)) / 2.0;
  last_time = millis();

  if (debug_mode) {
    if ((millis() - last_print_time) > 1000) {
      debug_print("avg loop time: ");
      debug_print_float(average_loop_time, 2);
      debug_println("");
      last_print_time = millis();
    }
  }


} /* profile_loop_time */

#endif //DEBUG_PROFILE_LOOP_TIME
// --------------------------------------------------------------
void check_az_speed_pot() {

  static unsigned long last_pot_check_time = 0;
  int pot_read = 0;
  byte new_azimuth_speed_voltage = 0;


  if (az_speed_pot && azimuth_speed_voltage && ((millis() - last_pot_check_time) > 500)) {
    pot_read = analogReadEnhanced(az_speed_pot);
    new_azimuth_speed_voltage = map(pot_read, SPEED_POT_LOW, SPEED_POT_HIGH, SPEED_POT_LOW_MAP, SPEED_POT_HIGH_MAP);
    if (new_azimuth_speed_voltage != normal_az_speed_voltage) {
      #ifdef DEBUG_AZ_SPEED_POT
      if (debug_mode) {
        debug_print("check_az_speed_pot: normal_az_speed_voltage: ");
        debug_print_int(normal_az_speed_voltage);
        debug_print(" new_azimuth_speed_voltage:");
        debug_print_int(new_azimuth_speed_voltage);
        debug_println("");
      }
      #endif // DEBUG_AZ_SPEED_POT
      // analogWriteEnhanced(azimuth_speed_voltage, new_azimuth_speed_voltage);
      normal_az_speed_voltage = new_azimuth_speed_voltage;
      update_az_variable_outputs(normal_az_speed_voltage);
      #if defined(OPTION_EL_SPEED_FOLLOWS_AZ_SPEED) && defined(FEATURE_ELEVATION_CONTROL)
      normal_el_speed_voltage = new_azimuth_speed_voltage;
      update_el_variable_outputs(normal_el_speed_voltage);
      #endif // OPTION_EL_SPEED_FOLLOWS_AZ_SPEED
    }
    last_pot_check_time = millis();
  }

} /* check_az_speed_pot */
// --------------------------------------------------------------
void check_az_preset_potentiometer() {


  byte check_pot = 0;
  static unsigned long last_pot_check_time = 0;
  static int last_pot_read = 9999;
  int pot_read = 0;
  int new_pot_azimuth = 0;
  byte button_read = 0;
  static byte pot_changed_waiting = 0;

  if (az_preset_pot) {
    if (last_pot_read == 9999) {  // initialize last_pot_read the first time we hit this subroutine
      last_pot_read = analogReadEnhanced(az_preset_pot);
    }

    if (!pot_changed_waiting) {
      if (preset_start_button) { // if we have a preset start button, check it
        button_read = digitalReadEnhanced(preset_start_button);
        if (button_read == BUTTON_ACTIVE_STATE) {
          check_pot = 1;
        }
      } else {  // if not, check the pot every 500 mS
        if ((millis() - last_pot_check_time) < 250) {
          check_pot = 1;
        }
      }
      if (check_pot) {
        pot_read = analogReadEnhanced(az_preset_pot);
        new_pot_azimuth = map(pot_read, AZ_PRESET_POT_FULL_CW, AZ_PRESET_POT_FULL_CCW, AZ_PRESET_POT_FULL_CW_MAP, AZ_PRESET_POT_FULL_CCW_MAP);
        if ((abs(last_pot_read - pot_read) > 4) && (abs(new_pot_azimuth - (raw_azimuth / HEADING_MULTIPLIER)) > AZIMUTH_TOLERANCE)) {
          pot_changed_waiting = 1;
          #ifdef DEBUG_AZ_PRESET_POT
          if (debug_mode) {
            debug_println("check_az_preset_potentiometer: in pot_changed_waiting");
          }
          #endif // DEBUG_AZ_PRESET_POT
          last_pot_read = pot_read;
        }
      }
      last_pot_check_time = millis();
    } else {  // we're in pot change mode
      pot_read = analogReadEnhanced(az_preset_pot);
      if (abs(pot_read - last_pot_read) > 3) {  // if the pot has changed, reset the timer
        last_pot_check_time = millis();
        last_pot_read = pot_read;
      } else {
        if ((millis() - last_pot_check_time) >= 250) {  // has it been awhile since the last pot change?
          new_pot_azimuth = map(pot_read, AZ_PRESET_POT_FULL_CW, AZ_PRESET_POT_FULL_CCW, AZ_PRESET_POT_FULL_CW_MAP, AZ_PRESET_POT_FULL_CCW_MAP);
          #ifdef DEBUG_AZ_PRESET_POT
          if (debug_mode) {
            debug_print("check_az_preset_potentiometer: pot change - current raw_azimuth: ");
            debug_print_float(raw_azimuth / HEADING_MULTIPLIER,0);
            debug_print(" new_azimuth: ");
            debug_print_int(new_pot_azimuth);
            debug_println("");
          }
          #endif // DEBUG_AZ_PRESET_POT
          submit_request(AZ, REQUEST_AZIMUTH_RAW, new_pot_azimuth * HEADING_MULTIPLIER, 44);
          pot_changed_waiting = 0;
          last_pot_read = pot_read;
          last_pot_check_time = millis();
        }
      }
    }
  } // if (az_preset_pot)
} /* check_az_preset_potentiometer */
// --------------------------------------------------------------

void initialize_rotary_encoders(){

  #ifdef FEATURE_AZ_PRESET_ENCODER
  pinModeEnhanced(az_rotary_preset_pin1, INPUT);
  pinModeEnhanced(az_rotary_preset_pin2, INPUT);
  az_encoder_raw_degrees = raw_azimuth;
  #ifdef OPTION_ENCODER_ENABLE_PULLUPS
  digitalWriteEnhanced(az_rotary_preset_pin1, HIGH);
  digitalWriteEnhanced(az_rotary_preset_pin2, HIGH);
  #endif // OPTION_ENCODER_ENABLE_PULLUPS
  #endif // FEATURE_AZ_PRESET_ENCODER


  #ifdef FEATURE_EL_PRESET_ENCODER
  pinModeEnhanced(el_rotary_preset_pin1, INPUT);
  pinModeEnhanced(el_rotary_preset_pin2, INPUT);
  el_encoder_degrees = elevation;
  #ifdef OPTION_ENCODER_ENABLE_PULLUPS
  digitalWriteEnhanced(el_rotary_preset_pin1, HIGH);
  digitalWriteEnhanced(el_rotary_preset_pin2, HIGH);
  #endif // OPTION_ENCODER_ENABLE_PULLUPS
  #endif // FEATURE_EL_PRESET_ENCODER

  #ifdef FEATURE_AZ_POSITION_ROTARY_ENCODER
  pinModeEnhanced(az_rotary_position_pin1, INPUT);
  pinModeEnhanced(az_rotary_position_pin2, INPUT);
  #ifdef OPTION_ENCODER_ENABLE_PULLUPS
  digitalWriteEnhanced(az_rotary_position_pin1, HIGH);
  digitalWriteEnhanced(az_rotary_position_pin2, HIGH);
  #endif // OPTION_ENCODER_ENABLE_PULLUPS
  #endif // FEATURE_AZ_POSITION_ROTARY_ENCODER


  #ifdef FEATURE_EL_POSITION_ROTARY_ENCODER
  pinModeEnhanced(el_rotary_position_pin1, INPUT);
  pinModeEnhanced(el_rotary_position_pin2, INPUT);
  #ifdef OPTION_ENCODER_ENABLE_PULLUPS
  digitalWriteEnhanced(el_rotary_position_pin1, HIGH);
  digitalWriteEnhanced(el_rotary_position_pin2, HIGH);
  #endif // OPTION_ENCODER_ENABLE_PULLUPS
  #endif // FEATURE_EL_POSITION_ROTARY_ENCODER


  #ifdef FEATURE_AZ_POSITION_INCREMENTAL_ENCODER
  pinMode(az_incremental_encoder_pin_phase_a, INPUT);
  pinMode(az_incremental_encoder_pin_phase_b, INPUT);
  pinMode(az_incremental_encoder_pin_phase_z, INPUT);
  #ifdef OPTION_INCREMENTAL_ENCODER_PULLUPS
  digitalWrite(az_incremental_encoder_pin_phase_a, HIGH);
  digitalWrite(az_incremental_encoder_pin_phase_b, HIGH);
  digitalWrite(az_incremental_encoder_pin_phase_z, HIGH);
  #endif // OPTION_INCREMENTAL_ENCODER_PULLUPS
  attachInterrupt(AZ_POSITION_INCREMENTAL_ENCODER_A_PIN_INTERRUPT, az_position_incremental_encoder_interrupt_handler, CHANGE);
  attachInterrupt(AZ_POSITION_INCREMENTAL_ENCODER_B_PIN_INTERRUPT, az_position_incremental_encoder_interrupt_handler, CHANGE);
  delay(250);
  az_3_phase_encoder_last_phase_a_state = digitalRead(az_incremental_encoder_pin_phase_a);
  az_3_phase_encoder_last_phase_b_state = digitalRead(az_incremental_encoder_pin_phase_b);
  #endif // FEATURE_AZ_POSITION_INCREMENTAL_ENCODER

  #ifdef FEATURE_EL_POSITION_INCREMENTAL_ENCODER
  pinMode(el_incremental_encoder_pin_phase_a, INPUT);
  pinMode(el_incremental_encoder_pin_phase_b, INPUT);
  pinMode(el_incremental_encoder_pin_phase_z, INPUT);
  #ifdef OPTION_INCREMENTAL_ENCODER_PULLUPS
  digitalWrite(el_incremental_encoder_pin_phase_a, HIGH);
  digitalWrite(el_incremental_encoder_pin_phase_b, HIGH);
  digitalWrite(el_incremental_encoder_pin_phase_z, HIGH);
  #endif // OPTION_INCREMENTAL_ENCODER_PULLUPS
  attachInterrupt(EL_POSITION_INCREMENTAL_ENCODER_A_PIN_INTERRUPT, el_position_incremental_encoder_interrupt_handler, CHANGE);
  attachInterrupt(EL_POSITION_INCREMENTAL_ENCODER_B_PIN_INTERRUPT, el_position_incremental_encoder_interrupt_handler, CHANGE);
  delay(250);
  el_3_phase_encoder_last_phase_a_state = digitalRead(el_incremental_encoder_pin_phase_a);
  el_3_phase_encoder_last_phase_b_state = digitalRead(el_incremental_encoder_pin_phase_b);
  #endif // FEATURE_EL_POSITION_INCREMENTAL_ENCODER

} /* initialize_rotary_encoders */


// --------------------------------------------------------------
#ifdef FEATURE_AZ_PRESET_ENCODER
void check_preset_encoders(){

  static unsigned long last_encoder_change_time = 0;
  byte button_read = HIGH;
  byte number_columns = 0;
  static byte submit_encoder_change = 0;
  static unsigned long last_preset_start_button_start = 0;
  static unsigned long last_preset_start_button_kill = 0;
  static unsigned long last_encoder_move = 0;

  #ifdef FEATURE_AZ_PRESET_ENCODER
  static unsigned long az_timestamp[5];
  #endif // FEATURE_AZ_PRESET_ENCODER

  #ifdef FEATURE_EL_PRESET_ENCODER
  static unsigned long el_timestamp[5];
  #endif // FEATURE_EL_PRESET_ENCODER

  #ifdef FEATURE_AZ_PRESET_ENCODER
  az_encoder_state = ttable[az_encoder_state & 0xf][((digitalReadEnhanced(az_rotary_preset_pin2) << 1) | digitalReadEnhanced(az_rotary_preset_pin1))];
  unsigned char az_encoder_result = az_encoder_state & 0x30;
  #ifdef DEBUG_PRESET_ENCODERS
  static byte last_az_rotary_preset_pin1 = 0;
  static byte last_az_rotary_preset_pin2 = 0;

  if ((debug_mode) && (( last_az_rotary_preset_pin1 != digitalReadEnhanced(az_rotary_preset_pin1)) || ( last_az_rotary_preset_pin2 != digitalReadEnhanced(az_rotary_preset_pin2)))) {
    debug_print("check_preset_encoders: az_rotary_preset_pin1: ");
    debug_print_int(digitalReadEnhanced(az_rotary_preset_pin1));
    debug_print(" az_rotary_preset_pin2: ");
    debug_print_int(digitalReadEnhanced(az_rotary_preset_pin2));
    debug_print(" encoder_result: ");
    debug_print_int(az_encoder_result);
    debug_println("");
  }
  last_az_rotary_preset_pin1 = digitalReadEnhanced(az_rotary_preset_pin1);
  last_az_rotary_preset_pin2 = digitalReadEnhanced(az_rotary_preset_pin2);
  #endif // DEBUG_PRESET_ENCODERS

  #endif // FEATURE_AZ_PRESET_ENCODER

  #ifdef FEATURE_EL_PRESET_ENCODER
  el_encoder_state = ttable[el_encoder_state & 0xf][((digitalReadEnhanced(el_rotary_preset_pin2) << 1) | digitalReadEnhanced(el_rotary_preset_pin1))];
  unsigned char el_encoder_result = el_encoder_state & 0x30;
  #endif // FEATURE_EL_PRESET_ENCODER

  #ifdef FEATURE_AZ_PRESET_ENCODER
  if (az_encoder_result) {                                 // If rotary encoder modified
    az_timestamp[0] = az_timestamp[1];                     // Encoder step timer
    az_timestamp[1] = az_timestamp[2];
    az_timestamp[2] = az_timestamp[3];
    az_timestamp[3] = az_timestamp[4];
    az_timestamp[4] = millis();

    last_encoder_move = millis();


    #ifdef DEBUG_PRESET_ENCODERS
    char tempchar[12] = "";
    if (debug_mode) {
      debug_print("check_preset_encoders: az_timestamps:");
      for (int y = 0; y < 5; y++) {
        debug_print(" ");
        dtostrf(az_timestamp[y],0,0,tempchar);
        debug_print(tempchar);
      }
      debug_println("");
    }
    #endif // DEBUG_PRESET_ENCODERS

    unsigned long az_elapsed_time = (az_timestamp[4] - az_timestamp[0]); // Encoder step time difference for 10's step

    #ifdef OPTION_PRESET_ENCODER_RELATIVE_CHANGE
    if ((preset_encoders_state == ENCODER_IDLE) || (preset_encoders_state == ENCODER_EL_PENDING)) {
      if (az_request_queue_state == IN_PROGRESS_TO_TARGET) {
        az_encoder_raw_degrees = target_raw_azimuth;
      } else {
        az_encoder_raw_degrees = raw_azimuth;
      }
    }
    #endif // OPTION_PRESET_ENCODER_RELATIVE_CHANGE

    // bbbbbb

    #ifndef OPTION_PRESET_ENCODER_0_360_DEGREES
    if (az_encoder_result == DIR_CW) {
      #ifdef DEBUG_PRESET_ENCODERS
      debug_print("check_preset_encoders: az CW");
      #endif // DEBUG_PRESET_ENCODERS
      if (az_elapsed_time < 250 /* mSec */) {
        az_encoder_raw_degrees += (5 * HEADING_MULTIPLIER);
      } else { az_encoder_raw_degrees += (1 * HEADING_MULTIPLIER); };                                                                                      // Single deg increase unless encoder turned quickly then 10's step
      // if (az_encoder_raw_degrees >=(360*HEADING_MULTIPLIER)) {az_encoder_raw_degrees -= (360*HEADING_MULTIPLIER);};
      if (az_encoder_raw_degrees > ((azimuth_starting_point + azimuth_rotation_capability) * HEADING_MULTIPLIER)) {
        az_encoder_raw_degrees =
          ((azimuth_starting_point * HEADING_MULTIPLIER)
           /* + ((azimuth_starting_point+azimuth_rotation_capability)*HEADING_MULTIPLIER) - az_encoder_raw_degrees*/);
      }
    }
    if (az_encoder_result == DIR_CCW) {
      #ifdef DEBUG_PRESET_ENCODERS
      debug_print("check_preset_encoders: az CCW");
      #endif // DEBUG_PRESET_ENCODERS
      if (az_elapsed_time < 250 /* mSec */) {
        az_encoder_raw_degrees -= (5 * HEADING_MULTIPLIER);
      } else { az_encoder_raw_degrees -= (1 * HEADING_MULTIPLIER); };                                                                                       // Single deg decrease unless encoder turned quickly then 10's step
      // if (az_encoder_raw_degrees < 0) {az_encoder_raw_degrees = (360*HEADING_MULTIPLIER);};
      if (az_encoder_raw_degrees < (azimuth_starting_point * HEADING_MULTIPLIER)) {
        az_encoder_raw_degrees = (((azimuth_starting_point + azimuth_rotation_capability) * HEADING_MULTIPLIER)
                                  /*- (az_encoder_raw_degrees-(azimuth_starting_point*HEADING_MULTIPLIER))*/);
      }
    }
    #else //ndef OPTION_PRESET_ENCODER_0_360_DEGREES
    if (az_encoder_result == DIR_CW) {
      #ifdef DEBUG_PRESET_ENCODERS
      debug_print("check_preset_encoders: az CW");
      #endif // DEBUG_PRESET_ENCODERS
      if (az_elapsed_time < 250) {  // Single deg increase unless encoder turned quickly then 10's step
        az_encoder_raw_degrees += (5 * HEADING_MULTIPLIER);
      } else {
        az_encoder_raw_degrees += (1 * HEADING_MULTIPLIER);
      }                                                                                   
      if (az_encoder_raw_degrees > (360 * HEADING_MULTIPLIER)) {
        //az_encoder_raw_degrees = (360 * HEADING_MULTIPLIER);
        az_encoder_raw_degrees = 0;
      //} else {
       // if (az_encoder_raw_degrees < 0) {
       //   az_encoder_raw_degrees = 0;
       // }
      }
    }
    if (az_encoder_result == DIR_CCW) {
      #ifdef DEBUG_PRESET_ENCODERS
      debug_print("check_preset_encoders: az CCW");
      #endif // DEBUG_PRESET_ENCODERS
      if (az_elapsed_time < 250) {  // Single deg decrease unless encoder turned quickly then 10's step
        az_encoder_raw_degrees -= (5 * HEADING_MULTIPLIER);
      } else { 
        az_encoder_raw_degrees -= (1 * HEADING_MULTIPLIER); 
      }                                                                                       
      //if (az_encoder_raw_degrees > (360 * HEADING_MULTIPLIER)) {
      //  az_encoder_raw_degrees = (360 * HEADING_MULTIPLIER);
      //} else {
        if (az_encoder_raw_degrees < 0) {
          //az_encoder_raw_degrees = 0;
          az_encoder_raw_degrees = 359 * HEADING_MULTIPLIER;
        }
      //}
    }
    #endif //ndef OPTION_PRESET_ENCODER_0_360_DEGREES



    last_encoder_change_time = millis();     // Encoder Check Timer

    #ifdef FEATURE_LCD_DISPLAY
    push_lcd_update = 1;                     // push an LCD update
    #endif // FEATURE_LCD_DISPLAY

    if (preset_encoders_state == ENCODER_IDLE) {
      preset_encoders_state = ENCODER_AZ_PENDING;
    } else {
      if (preset_encoders_state == ENCODER_EL_PENDING) {
        preset_encoders_state = ENCODER_AZ_EL_PENDING;
      }
    }

    #ifdef DEBUG_PRESET_ENCODERS
    debug_print("check_preset_encoders: az target: ");
    dtostrf((az_encoder_raw_degrees / HEADING_MULTIPLIER),0,1,tempchar);
    debug_println(tempchar);
    #endif // DEBUG_PRESET_ENCODERS

  } // if (az_encoder_result)
  #endif // FEATURE_AZ_PRESET_ENCODER

  #ifdef FEATURE_EL_PRESET_ENCODER

  #ifdef OPTION_PRESET_ENCODER_RELATIVE_CHANGE
  if ((preset_encoders_state == ENCODER_IDLE) || (preset_encoders_state == ENCODER_AZ_PENDING)) {
    if (el_request_queue_state == IN_PROGRESS_TO_TARGET) {
      el_encoder_degrees = target_elevation;
    } else {
      el_encoder_degrees = elevation;
    }
  }
    #endif // OPTION_PRESET_ENCODER_RELATIVE_CHANGE

  if (el_encoder_result) {                                 // If rotary encoder modified
    el_timestamp[0] = el_timestamp[1];                     // Encoder step timer
    el_timestamp[1] = el_timestamp[2];
    el_timestamp[2] = el_timestamp[3];
    el_timestamp[3] = el_timestamp[4];
    el_timestamp[4] = millis();

    last_encoder_move = millis();

    unsigned long el_elapsed_time = (el_timestamp[4] - el_timestamp[0]); // Encoder step time difference for 10's step

    if (el_encoder_result == DIR_CW) {                      // Rotary Encoder CW 0 - 359 Deg
      #ifdef DEBUG_PRESET_ENCODERS
      debug_println("check_preset_encoders: el CW");
      #endif // DEBUG_PRESET_ENCODERS
      if (el_elapsed_time < 250) {
        el_encoder_degrees += (5 * HEADING_MULTIPLIER);
      } else { el_encoder_degrees += (1 * HEADING_MULTIPLIER); };                                                                       // Single deg increase unless encoder turned quickly then 10's step
      if (el_encoder_degrees > (180 * HEADING_MULTIPLIER)) {
        el_encoder_degrees = (180 * HEADING_MULTIPLIER);
      }
      ;
    }
    if (el_encoder_result == DIR_CCW) {
      #ifdef DEBUG_PRESET_ENCODERS
      debug_println("check_preset_encoders: el CCW");
      #endif // DEBUG_PRESET_ENCODERS
      // Rotary Encoder CCW 359 - 0 Deg
      if (el_elapsed_time < 250) {
        el_encoder_degrees -= (5 * HEADING_MULTIPLIER);
      } else { el_encoder_degrees -= (1 * HEADING_MULTIPLIER); };                                                                        // Single deg decrease unless encoder turned quickly then 10's step
      if (el_encoder_degrees < 0) {
        el_encoder_degrees = 0;
      }
      ;
    }
    last_encoder_change_time = millis();     // Encoder Check Timer

    #ifdef FEATURE_LCD_DISPLAY
    last_lcd_update = 0;                     // push an LCD update
    #endif // FEATURE_LCD_DISPLAY

    if (preset_encoders_state == ENCODER_IDLE) {
      preset_encoders_state = ENCODER_EL_PENDING;
    } else {
      if (preset_encoders_state == ENCODER_AZ_PENDING) {
        preset_encoders_state = ENCODER_AZ_EL_PENDING;
      }
    }

    #ifdef DEBUG_PRESET_ENCODERS
    debug_print("check_preset_encoders: el target: ");
    dtostrf(el_encoder_degrees / HEADING_MULTIPLIER,0,1,tempchar);
    debug_println(tempchar);
    #endif // DEBUG_PRESET_ENCODERS


  } // if (el_encoder_result)


  #endif // FEATURE_EL_PRESET_ENCODER

  if ((preset_encoders_state != ENCODER_IDLE) && (!submit_encoder_change)) { // Check button or timer
    if (preset_start_button) {                                               // if we have a preset start button, check it
      button_read = digitalReadEnhanced(preset_start_button);
      if (button_read == BUTTON_ACTIVE_STATE) {
        submit_encoder_change = 1;
        last_preset_start_button_start = millis();

        #ifdef DEBUG_PRESET_ENCODERS
        debug_println("check_preset_encoders: preset_start_button submit_encoder_change");
        #endif // DEBUG_PRESET_ENCODERS
      }
    } else {
      if ((millis() - last_encoder_change_time) > 2000) {       // if enc not changed for more than 2 sec, rotate to target
        #ifdef DEBUG_PRESET_ENCODERS
        debug_println("check_preset_encoders: timer submit_encoder_change");
        #endif // DEBUG_PRESET_ENCODERS
        submit_encoder_change = 1;
      }
    }
  } // if (!enc_changed_waiting)


  if (preset_start_button) {                                         // if we have a preset start button, check it
    button_read = digitalReadEnhanced(preset_start_button);
    if ((button_read == BUTTON_ACTIVE_STATE) && (!submit_encoder_change) && ((millis() - last_preset_start_button_start) > 250)
        && ((millis() - last_preset_start_button_kill) > 250) && (preset_encoders_state == ENCODER_IDLE)) {
      #ifdef DEBUG_PRESET_ENCODERS
      debug_println("check_preset_encoders: preset button kill");
      #endif // DEBUG_PRESET_ENCODERS
      #ifdef FEATURE_AZ_PRESET_ENCODER
      if (az_state != IDLE) {
        submit_request(AZ, REQUEST_KILL, 0, 45);
      }
      #endif // FEATURE_AZ_PRESET_ENCODER
      #ifdef FEATURE_EL_PRESET_ENCODER
      if (el_state != IDLE) {
        submit_request(EL, REQUEST_KILL, 0, 46);
      }
      #endif // FEATURE_EL_PRESET_ENCODER
      last_preset_start_button_kill = millis();
    }
  }

  if ((submit_encoder_change) && (button_read == BUTTON_INACTIVE_STATE)) {
    #ifdef DEBUG_PRESET_ENCODERS
    debug_println("check_preset_encoders: submit_encoder_change ");
    #endif // DEBUG_PRESET_ENCODERS


    if ((preset_encoders_state == ENCODER_AZ_PENDING) || (preset_encoders_state == ENCODER_AZ_EL_PENDING)) {
      #ifndef OPTION_PRESET_ENCODER_0_360_DEGREES
      submit_request(AZ, REQUEST_AZIMUTH_RAW, az_encoder_raw_degrees, 47);
      #else
      submit_request(AZ, REQUEST_AZIMUTH, az_encoder_raw_degrees, 47);
      #endif //ndef OPTION_PRESET_ENCODER_0_360_DEGREES
    }

    #ifdef FEATURE_EL_PRESET_ENCODER
    if ((preset_encoders_state == ENCODER_EL_PENDING) || (preset_encoders_state == ENCODER_AZ_EL_PENDING)) {
      submit_request(EL, REQUEST_ELEVATION, el_encoder_degrees, 48);
    }
    #endif // FEATURE_EL_PRESET_ENCODER

    preset_encoders_state = ENCODER_IDLE;
    submit_encoder_change = 0;
  } // if (submit_encoder_change)

  if ((preset_start_button) && (preset_encoders_state != ENCODER_IDLE) && ((millis() - last_encoder_move) > ENCODER_PRESET_TIMEOUT)) { // timeout if we have a preset start button
    preset_encoders_state = ENCODER_IDLE;
    #ifdef FEATURE_LCD_DISPLAY
    push_lcd_update = 1;                     // push an LCD update
    #endif // FEATURE_LCD_DISPLAY
  }

} /* check_preset_encoders */

#endif // FEATURE_AZ_PRESET_ENCODER

// --------------------------------------------------------------

#ifdef OPTION_AZ_MANUAL_ROTATE_LIMITS
void check_az_manual_rotate_limit() {

  if ((current_az_state() == ROTATING_CCW) && (raw_azimuth <= (AZ_MANUAL_ROTATE_CCW_LIMIT * HEADING_MULTIPLIER))) {
    #ifdef DEBUG_AZ_MANUAL_ROTATE_LIMITS
    debug_print("check_az_manual_rotate_limit: stopping - hit AZ_MANUAL_ROTATE_CCW_LIMIT of ");
    debug_print_int(AZ_MANUAL_ROTATE_CCW_LIMIT);
    debug_println("");
    #endif // DEBUG_AZ_MANUAL_ROTATE_LIMITS
    submit_request(AZ, REQUEST_KILL, 0, 49);
  }
  if ((current_az_state() == ROTATING_CW) && (raw_azimuth >= (AZ_MANUAL_ROTATE_CW_LIMIT * HEADING_MULTIPLIER))) {
    #ifdef DEBUG_AZ_MANUAL_ROTATE_LIMITS
    debug_print("check_az_manual_rotate_limit: stopping - hit AZ_MANUAL_ROTATE_CW_LIMIT of ");
    debug_print_int(AZ_MANUAL_ROTATE_CW_LIMIT);
    debug_println("");
    #endif // DEBUG_AZ_MANUAL_ROTATE_LIMITS
    submit_request(AZ, REQUEST_KILL, 0, 50);
  }
} /* check_az_manual_rotate_limit */
#endif // #ifdef OPTION_AZ_MANUAL_ROTATE_LIMITS

// --------------------------------------------------------------

#if defined(OPTION_EL_MANUAL_ROTATE_LIMITS) && defined(FEATURE_ELEVATION_CONTROL)
void check_el_manual_rotate_limit() {

  if ((current_el_state() == ROTATING_DOWN) && (elevation <= (EL_MANUAL_ROTATE_DOWN_LIMIT * HEADING_MULTIPLIER))) {
    #ifdef DEBUG_EL_MANUAL_ROTATE_LIMITS
    debug_print("check_el_manual_rotate_limit: stopping - hit EL_MANUAL_ROTATE_DOWN_LIMIT of ");
    debug_print_int(EL_MANUAL_ROTATE_DOWN_LIMIT);
    debug_println("");
    #endif // DEBUG_EL_MANUAL_ROTATE_LIMITS
    submit_request(EL, REQUEST_KILL, 0, 51);
  }
  if ((current_el_state() == ROTATING_UP) && (elevation >= (EL_MANUAL_ROTATE_UP_LIMIT * HEADING_MULTIPLIER))) {
    #ifdef DEBUG_EL_MANUAL_ROTATE_LIMITS
    debug_print("check_el_manual_rotate_limit: stopping - hit EL_MANUAL_ROTATE_UP_LIMIT of ");
    debug_print_int(EL_MANUAL_ROTATE_UP_LIMIT);
    debug_println("");
    #endif // DEBUG_EL_MANUAL_ROTATE_LIMITS
    submit_request(EL, REQUEST_KILL, 0, 52);
  }
} /* check_el_manual_rotate_limit */
#endif // #ifdef OPTION_EL_MANUAL_ROTATE_LIMITS


// --------------------------------------------------------------
void check_brake_release() {


  static byte in_az_brake_release_delay = 0;
  static unsigned long az_brake_delay_start_time = 0;

  #ifdef FEATURE_ELEVATION_CONTROL
  static byte in_el_brake_release_delay = 0;
  static unsigned long el_brake_delay_start_time = 0;
  #endif // FEATURE_ELEVATION_CONTROL

  if ((az_state == IDLE) && (brake_az_engaged)) {
    if (in_az_brake_release_delay) {
      if ((millis() - az_brake_delay_start_time) > AZ_BRAKE_DELAY) {
        brake_release(AZ, BRAKE_RELEASE_OFF);
        in_az_brake_release_delay = 0;
      }
    } else {
      az_brake_delay_start_time = millis();
      in_az_brake_release_delay = 1;
    }
  }

    #ifdef FEATURE_ELEVATION_CONTROL
  if ((el_state == IDLE) && (brake_el_engaged)) {
    if (in_el_brake_release_delay) {
      if ((millis() - el_brake_delay_start_time) > EL_BRAKE_DELAY) {
        brake_release(EL, BRAKE_RELEASE_OFF);
        in_el_brake_release_delay = 0;
      }
    } else {
      el_brake_delay_start_time = millis();
      in_el_brake_release_delay = 1;
    }
  }
      #endif // FEATURE_ELEVATION_CONTROL

} /* check_brake_release */

// --------------------------------------------------------------
void brake_release(byte az_or_el, byte operation){

  if (az_or_el == AZ) {
    if (brake_az) {
      if (operation == BRAKE_RELEASE_ON) {
        digitalWriteEnhanced(brake_az, HIGH);
        brake_az_engaged = 1;
        #ifdef DEBUG_BRAKE
        debug_println("brake_release: brake_az BRAKE_RELEASE_ON");
        #endif // DEBUG_BRAKE
      } else {
        digitalWriteEnhanced(brake_az, LOW);
        brake_az_engaged = 0;
        #ifdef DEBUG_BRAKE
        debug_println("brake_release: brake_az BRAKE_RELEASE_OFF");
        #endif // DEBUG_BRAKE
      }
    }
  } else {
        #ifdef FEATURE_ELEVATION_CONTROL
    if (brake_el) {
      digitalWriteEnhanced(brake_el, HIGH);
      brake_el_engaged = 1;
      #ifdef DEBUG_BRAKE
      debug_println("brake_release: brake_el BRAKE_RELEASE_ON");
      #endif // DEBUG_BRAKE
    } else {
      digitalWriteEnhanced(brake_el, LOW);
      brake_el_engaged = 0;
      #ifdef DEBUG_BRAKE
      debug_println("brake_release: brake_el BRAKE_RELEASE_OFF");
      #endif // DEBUG_BRAKE
    }
    #endif // FEATURE_ELEVATION_CONTROL
  }
} /* brake_release */

// --------------------------------------------------------------
void check_overlap(){

  static byte overlap_led_status = 0;
  static unsigned long last_check_time;

  if ((overlap_led) && ((millis() - last_check_time) > 500)) {
    // if ((analog_az > (500*HEADING_MULTIPLIER)) && (azimuth > (ANALOG_AZ_OVERLAP_DEGREES*HEADING_MULTIPLIER)) && (!overlap_led_status)) {
    if ((raw_azimuth > (ANALOG_AZ_OVERLAP_DEGREES * HEADING_MULTIPLIER)) && (!overlap_led_status)) {
      digitalWriteEnhanced(overlap_led, HIGH);
      overlap_led_status = 1;
      #ifdef DEBUG_OVERLAP
      debug_println("check_overlap: in overlap");
      #endif // DEBUG_OVERLAP
    } else {
      // if (((analog_az < (500*HEADING_MULTIPLIER)) || (azimuth < (ANALOG_AZ_OVERLAP_DEGREES*HEADING_MULTIPLIER))) && (overlap_led_status)) {
      if ((raw_azimuth < (ANALOG_AZ_OVERLAP_DEGREES * HEADING_MULTIPLIER)) && (overlap_led_status)) {
        digitalWriteEnhanced(overlap_led, LOW);
        overlap_led_status = 0;
        #ifdef DEBUG_OVERLAP
        debug_println("check_overlap: overlap off");
        #endif // DEBUG_OVERLAP
      }
    }
    last_check_time = millis();

  }

} /* check_overlap */



// --------------------------------------------------------------
void clear_command_buffer(){

  control_port_buffer_index = 0;
  control_port_buffer[0] = 0;


}


// --------------------------------------------------------------
#if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_ANCILLARY_PIN_CONTROL)
byte get_analog_pin(byte pin_number){

  byte return_output = 0;

  switch (pin_number) {
    case 0: return_output = A0; break;
    case 1: return_output = A1; break;
    case 2: return_output = A2; break;
    case 3: return_output = A3; break;
    case 4: return_output = A4; break;
    case 5: return_output = A5; break;
    case 6: return_output = A6; break;
  }

  return return_output;

}
#endif // FEATURE_REMOTE_UNIT_SLAVE

// --------------------------------------------------------------
#ifdef FEATURE_REMOTE_UNIT_SLAVE
void service_remote_unit_serial_buffer(){


/*
 *
 * This implements a protocol for host unit to remote unit communications
 *
 *
 * Remote Slave Unit Protocol Reference
 *
 *  PG - ping
 *  AZ - read azimuth
 *  EL - read elevation
 *  DOxx - digital pin initialize as output;
 *  DIxx - digital pin initialize as input
 *  DPxx - digital pin initialize as input with pullup
 *  DRxx - digital pin read
 *  DLxx - digital pin write low
 *  DHxx - digital pin write high
 *  DTxxyyyy - digital pin tone output
 *  NTxx - no tone
 *  ARxx - analog pin read
 *  AWxxyyy - analog pin write
 *  SWxy - serial write byte
 *  SDx - deactivate serial read event; x = port #
 *  SSxyyyyyy... - serial write sting; x = port #, yyyy = string of characters to send
 *  SAx - activate serial read event; x = port #
 *  RB - reboot
 *
 * Responses
 *
 *  ER - report an error (remote to host only)
 *  EV - report an event (remote to host only)
 *  OK - report success (remote to host only)
 *  CS - report a cold start (remote to host only)
 *
 * Error Codes
 *
 *  ER01 - Serial port buffer timeout
 *  ER02 - Command syntax error
 *
 * Events
 *
 *  EVSxy - Serial port read event; x = serial port number, y = byte returned
 *
 *
 */


  String command_string;
  byte command_good = 0;

  if (control_port_buffer_carriage_return_flag) {

    if (control_port_buffer_index < 3) {
      control_port->println(F("ER02"));  // we don't have enough characters - syntax error
    } else {
      command_string = String(char(toupper(control_port_buffer[0]))) + String(char(toupper(control_port_buffer[1])));

      #ifdef DEBUG_SERVICE_SERIAL_BUFFER
      debug_print("serial_serial_buffer: command_string: ");
      debug_print(command_string);
      debug_print("$ control_port_buffer_index: ");
      debug_print_int(control_port_buffer_index);
      debug_println("");
      #endif // DEBUG_SERVICE_SERIAL_BUFFER

      if ((command_string == "SS") && (control_port_buffer[2] > 47) && (control_port_buffer[2] < 53)) { // this is a variable length command
        command_good = 1;
        for (byte x = 3; x < control_port_buffer_index; x++) {
          switch (control_port_buffer[2] - 48) {
            case 0: control_port->write(control_port_buffer[x]); break;
            #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE)
            case 1: remote_unit_port->write(control_port_buffer[x]); break;
            #endif
          }
        }
      }

      if (control_port_buffer_index == 3) {
        if (command_string == "PG") {
          control_port->println(F("PG")); command_good = 1;
        }                                                                        // PG - ping
        if (command_string == "RB") {
          wdt_enable(WDTO_30MS); while (1) {
          }
        }                                                                        // RB - reboot
        if (command_string == "AZ") {
          control_port->print(F("AZ"));
          if (raw_azimuth < 1000) {
            control_port->print("0");
          }
          if (raw_azimuth < 100) {
            control_port->print("0");
          }
          if (raw_azimuth < 10) {
            control_port->print("0");
          }
          control_port->println(raw_azimuth);
          command_good = 1;
        }
        #ifdef FEATURE_ELEVATION_CONTROL
        if (command_string == "EL") {
          control_port->print(F("EL"));
          if (elevation >= 0) {
            control_port->print("+");
          } else {
            control_port->print("-");
          }
          if (abs(elevation) < 1000) {
            control_port->print("0");
          }
          if (abs(elevation) < 100) {
            control_port->print("0");
          }
          if (abs(elevation) < 10) {
            control_port->print("0");
          }
          control_port->println(abs(elevation));
          command_good = 1;
        }
          #endif // FEATURE_ELEVATION_CONTROL
      } // end of three byte commands



      if (control_port_buffer_index == 4) {
        if ((command_string == "SA") & (control_port_buffer[2] > 47) && (control_port_buffer[2] < 53)) {
          serial_read_event_flag[control_port_buffer[2] - 48] = 1;
          command_good = 1;
          control_port->println("OK");
        }
        if ((command_string == "SD") & (control_port_buffer[2] > 47) && (control_port_buffer[2] < 53)) {
          serial_read_event_flag[control_port_buffer[2] - 48] = 0;
          command_good = 1;
          control_port->println("OK");
        }

      }


      if (control_port_buffer_index == 5) {
        if (command_string == "SW") { // Serial Write command
          switch (control_port_buffer[2]) {
            case '0': control_port->write(control_port_buffer[3]); command_good = 1; break;
            #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE)
            case '1': remote_unit_port->write(control_port_buffer[3]); command_good = 1; break;
            #endif
          }
        }

        if (command_string == "DO") {
          if ((((control_port_buffer[2] > 47) && (control_port_buffer[2] < 58)) || (toupper(control_port_buffer[2]) == 'A')) && (control_port_buffer[3] > 47) && (control_port_buffer[3] < 58)) {
            command_good = 1;
            byte pin_value = 0;
            if (toupper(control_port_buffer[2]) == 'A') {
              pin_value = get_analog_pin(control_port_buffer[3] - 48);
            } else {
              pin_value = ((control_port_buffer[2] - 48) * 10) + (control_port_buffer[3] - 48);
            }
            #ifdef DEBUG_SERVICE_SERIAL_BUFFER
            debug_print("service_serial_buffer: pin_value: ");
            debug_print_int(pin_value);
            debug_println("");
            #endif // DEBUG_SERVICE_SERIAL_BUFFER
            control_port->println("OK");
            pinModeEnhanced(pin_value, OUTPUT);
          }
        }

        if (command_string == "DH") {
          if ((((control_port_buffer[2] > 47) && (control_port_buffer[2] < 58)) || (toupper(control_port_buffer[2]) == 'A')) && (control_port_buffer[3] > 47) && (control_port_buffer[3] < 58)) {
            command_good = 1;
            byte pin_value = 0;
            if (toupper(control_port_buffer[2]) == 'A') {
              pin_value = get_analog_pin(control_port_buffer[3] - 48);
            } else {
              pin_value = ((control_port_buffer[2] - 48) * 10) + (control_port_buffer[3] - 48);
            }
            digitalWriteEnhanced(pin_value, HIGH);
            control_port->println("OK");
          }
        }

        if (command_string == "DL") {
          if ((((control_port_buffer[2] > 47) && (control_port_buffer[2] < 58)) || (toupper(control_port_buffer[2]) == 'A')) && (control_port_buffer[3] > 47) && (control_port_buffer[3] < 58)) {
            command_good = 1;
            byte pin_value = 0;
            if (toupper(control_port_buffer[2]) == 'A') {
              pin_value = get_analog_pin(control_port_buffer[3] - 48);
            } else {
              pin_value = ((control_port_buffer[2] - 48) * 10) + (control_port_buffer[3] - 48);
            }
            digitalWriteEnhanced(pin_value, LOW);
            control_port->println("OK");
          }
        }

        if (command_string == "DI") {
          if ((((control_port_buffer[2] > 47) && (control_port_buffer[2] < 58)) || (toupper(control_port_buffer[2]) == 'A')) && (control_port_buffer[3] > 47) && (control_port_buffer[3] < 58)) {
            command_good = 1;
            byte pin_value = 0;
            if (toupper(control_port_buffer[2]) == 'A') {
              pin_value = get_analog_pin(control_port_buffer[3] - 48);
            } else {
              pin_value = ((control_port_buffer[2] - 48) * 10) + (control_port_buffer[3] - 48);
            }
            pinModeEnhanced(pin_value, INPUT);
            control_port->println("OK");
          }
        }

        if (command_string == "DP") {
          if ((((control_port_buffer[2] > 47) && (control_port_buffer[2] < 58)) || (toupper(control_port_buffer[2]) == 'A')) && (control_port_buffer[3] > 47) && (control_port_buffer[3] < 58)) {
            command_good = 1;
            byte pin_value = 0;
            if (toupper(control_port_buffer[2]) == 'A') {
              pin_value = get_analog_pin(control_port_buffer[3] - 48);
            } else {
              pin_value = ((control_port_buffer[2] - 48) * 10) + (control_port_buffer[3] - 48);
            }
            // pinModeEnhanced(pin_value,INPUT_PULLUP);
            pinModeEnhanced(pin_value, INPUT);
            digitalWriteEnhanced(pin_value, HIGH);
            control_port->println("OK");
          }
        }

        if (command_string == "DR") {
          if ((((control_port_buffer[2] > 47) && (control_port_buffer[2] < 58)) || (toupper(control_port_buffer[2]) == 'A')) && (control_port_buffer[3] > 47) && (control_port_buffer[3] < 58)) {
            command_good = 1;
            byte pin_value = 0;
            if (toupper(control_port_buffer[2]) == 'A') {
              pin_value = get_analog_pin(control_port_buffer[3] - 48);
            } else {
              pin_value = ((control_port_buffer[2] - 48) * 10) + (control_port_buffer[3] - 48);
            }
            byte pin_read = digitalReadEnhanced(pin_value);
            control_port->print("DR");
            control_port->write(control_port_buffer[2]);
            control_port->write(control_port_buffer[3]);
            if (pin_read) {
              control_port->println("1");
            } else {
              control_port->println("0");
            }
          }
        }
        if (command_string == "AR") {
          if ((((control_port_buffer[2] > 47) && (control_port_buffer[2] < 58)) || (toupper(control_port_buffer[2]) == 'A')) && (control_port_buffer[3] > 47) && (control_port_buffer[3] < 58)) {
            command_good = 1;
            byte pin_value = 0;
            if (toupper(control_port_buffer[2]) == 'A') {
              pin_value = get_analog_pin(control_port_buffer[3] - 48);
            } else {
              pin_value = ((control_port_buffer[2] - 48) * 10) + (control_port_buffer[3] - 48);
            }
            int pin_read = analogReadEnhanced(pin_value);
            control_port->print("AR");
            control_port->write(control_port_buffer[2]);
            control_port->write(control_port_buffer[3]);
            if (pin_read < 1000) {
              control_port->print("0");
            }
            if (pin_read < 100) {
              control_port->print("0");
            }
            if (pin_read < 10) {
              control_port->print("0");
            }
            control_port->println(pin_read);
          }
        }

        if (command_string == "NT") {
          if ((((control_port_buffer[2] > 47) && (control_port_buffer[2] < 58)) || (toupper(control_port_buffer[2]) == 'A')) && (control_port_buffer[3] > 47) && (control_port_buffer[3] < 58)) {
            command_good = 1;
            byte pin_value = 0;
            if (toupper(control_port_buffer[2]) == 'A') {
              pin_value = get_analog_pin(control_port_buffer[3] - 48);
            } else {
              pin_value = ((control_port_buffer[2] - 48) * 10) + (control_port_buffer[3] - 48);
            }
            noTone(pin_value);
            control_port->println("OK");
          }
        }

      } // if (control_port_buffer_index == 5)

      if (control_port_buffer_index == 8) {
        if (command_string == "AW") {
          if ((((control_port_buffer[2] > 47) && (control_port_buffer[2] < 58)) || (toupper(control_port_buffer[2]) == 'A')) && (control_port_buffer[3] > 47) && (control_port_buffer[3] < 58)) {
            byte pin_value = 0;
            if (toupper(control_port_buffer[2]) == 'A') {
              pin_value = get_analog_pin(control_port_buffer[3] - 48);
            } else {
              pin_value = ((control_port_buffer[2] - 48) * 10) + (control_port_buffer[3] - 48);
            }
            int write_value = ((control_port_buffer[4] - 48) * 100) + ((control_port_buffer[5] - 48) * 10) + (control_port_buffer[6] - 48);
            if ((write_value >= 0) && (write_value < 256)) {
              analogWriteEnhanced(pin_value, write_value);
              control_port->println("OK");
              command_good = 1;
            }
          }
        }
      }

      if (control_port_buffer_index == 9) {
        if (command_string == "DT") {
          if ((((control_port_buffer[2] > 47) && (control_port_buffer[2] < 58)) || (toupper(control_port_buffer[2]) == 'A')) && (control_port_buffer[3] > 47) && (control_port_buffer[3] < 58)) {
            byte pin_value = 0;
            if (toupper(control_port_buffer[2]) == 'A') {
              pin_value = get_analog_pin(control_port_buffer[3] - 48);
            } else {
              pin_value = ((control_port_buffer[2] - 48) * 10) + (control_port_buffer[3] - 48);
            }
            int write_value = ((control_port_buffer[4] - 48) * 1000) + ((control_port_buffer[5] - 48) * 100) + ((control_port_buffer[6] - 48) * 10) + (control_port_buffer[7] - 48);
            if ((write_value >= 0) && (write_value <= 9999)) {
              tone(pin_value, write_value);
              control_port->println("OK");
              command_good = 1;
            }
          }
        }
      }


      if (!command_good) {
        control_port->println(F("ER02"));
      }
    }
    control_port_buffer_carriage_return_flag = 0;
    control_port_buffer_index = 0;
  } else {
    if (((millis() - last_serial_receive_time) > REMOTE_BUFFER_TIMEOUT_MS) && control_port_buffer_index) {
      control_port->println(F("ER01"));
      control_port_buffer_index = 0;
    }
  }



} /* service_remote_unit_serial_buffer */

      #endif // FEATURE_REMOTE_UNIT_SLAVE
// --------------------------------------------------------------
void check_serial(){

  static unsigned long serial_led_time = 0;
  float tempfloat = 0;
  char return_string[100] = ""; 

  #if !defined(FEATURE_AZ_POSITION_ROTARY_ENCODER) && !defined(FEATURE_AZ_POSITION_PULSE_INPUT)
  long place_multiplier = 0;
  byte decimalplace = 0;
  #endif

  #ifdef FEATURE_CLOCK
  int temp_year = 0;
  byte temp_month = 0;
  byte temp_day = 0;
  byte temp_minute = 0;
  byte temp_hour = 0;
  #endif // FEATURE_CLOCK

  #if defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)
  char grid[10] = "";
  byte hit_error = 0;
  #endif // defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)

  #if defined(FEATURE_AZ_POSITION_ROTARY_ENCODER) || defined(FEATURE_AZ_POSITION_PULSE_INPUT)
  int new_azimuth = 9999;
  #endif
  #ifdef FEATURE_ELEVATION_CONTROL
  #if defined(FEATURE_EL_POSITION_ROTARY_ENCODER) || defined(FEATURE_EL_POSITION_PULSE_INPUT)
  int new_elevation = 9999;
  #endif // FEATURE_ELEVATION_CONTROL
  #endif // defined(FEATURE_AZ_POSITION_ROTARY_ENCODER) || defined(FEATURE_AZ_POSITION_PULSE_INPUT)


  #if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)

  if ((serial_led) && (serial_led_time != 0) && ((millis() - serial_led_time) > SERIAL_LED_TIME_MS)) {
    digitalWriteEnhanced(serial_led, LOW);
    serial_led_time = 0;
  }

  if (control_port->available()) {
    if (serial_led) {
      digitalWriteEnhanced(serial_led, HIGH);                      // blink the LED just to say we got something
      serial_led_time = millis();
    }

    #ifdef FEATURE_POWER_SWITCH
    last_activity_time = millis();
    #endif //FEATURE_POWER_SWITCH

    #ifdef DEBUG_SERIAL
    int control_port_available = control_port->available();
    #endif // DEBUG_SERIAL

    incoming_serial_byte = control_port->read();
    last_serial_receive_time = millis();

    #ifdef DEBUG_SERIAL
    debug_print("check_serial: control_port: ");
    debug_print_int(control_port_available);
    debug_print(":");
    debug_print_int(incoming_serial_byte);
    debug_println("");
    #endif // DEBUG_SERIAL


    if ((incoming_serial_byte > 96) && (incoming_serial_byte < 123)) {  // uppercase it
      incoming_serial_byte = incoming_serial_byte - 32;
    }                                                                                                                    


    #ifdef FEATURE_EASYCOM_EMULATION   //Easycom uses spaces, linefeeds, and carriage returns as command delimiters----------

    // Easycom only

    if ((control_port_buffer[0] == '\\') or (control_port_buffer[0] == '/') or ((control_port_buffer_index == 0) && ((incoming_serial_byte == '\\') || (incoming_serial_byte == '/')))) {
      // if it's a backslash command add it to the buffer if it's not a line feed or carriage return
      if ((incoming_serial_byte != 10) && (incoming_serial_byte != 13)) { 
        control_port_buffer[control_port_buffer_index] = incoming_serial_byte;
        control_port_buffer_index++;
      }
    } else {
      // if it's an easycom command add it to the buffer if it's not a line feed, carriage return, or space
      if ((incoming_serial_byte != 10) && (incoming_serial_byte != 13) && (incoming_serial_byte != 32)) { 
        control_port_buffer[control_port_buffer_index] = incoming_serial_byte;
        control_port_buffer_index++;
      }
    }

    // if it is an Easycom command and we have a space, line feed, or carriage return, process it
    if (((incoming_serial_byte == 10) || (incoming_serial_byte == 13) || (incoming_serial_byte == 32)) && (control_port_buffer[0] != '\\') && (control_port_buffer[0] != '/')){
      if (control_port_buffer_index > 1){
        process_easycom_command(control_port_buffer,control_port_buffer_index,CONTROL_PORT0,return_string);
        control_port->println(return_string);
      }
      clear_command_buffer();
    } else {
      // if it is a backslash command, process it if we have a carriage return
      if ((incoming_serial_byte == 13) && ((control_port_buffer[0] == '\\') or (control_port_buffer[0] == '/'))){
        process_backslash_command(control_port_buffer, control_port_buffer_index, CONTROL_PORT0, return_string);
        control_port->println(return_string);
        clear_command_buffer();
      }
    }


    #else //FEATURE_EASYCOM_EMULATION ------------------------------------------------------
    // Yaesu, Remote Slave
    if ((incoming_serial_byte != 10) && (incoming_serial_byte != 13)) { // add it to the buffer if it's not a line feed or carriage return
      control_port_buffer[control_port_buffer_index] = incoming_serial_byte;
      control_port_buffer_index++;
    }

    if (incoming_serial_byte == 13) {  // do we have a carriage return?
      if ((control_port_buffer[0] == '\\') or (control_port_buffer[0] == '/')) {
        process_backslash_command(control_port_buffer, control_port_buffer_index, CONTROL_PORT0, return_string);
      } else {
        #ifdef FEATURE_YAESU_EMULATION
        process_yaesu_command(control_port_buffer,control_port_buffer_index,CONTROL_PORT0,return_string);
        #endif //FEATURE_YAESU_EMULATION

        #ifdef FEATURE_REMOTE_UNIT_SLAVE
        process_remote_slave_command(control_port_buffer,control_port_buffer_index,CONTROL_PORT0,return_string);
        #endif //FEATURE_REMOTE_UNIT_SLAVE
      }  
      control_port->println(return_string);
      clear_command_buffer();
    }

    #endif //FEATURE_EASYCOM_EMULATION--------------------------



  } // if (control_port->available())
  #endif // defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)


  // remote unit port servicing
  #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE)
  if (remote_unit_port->available()) {
    incoming_serial_byte = remote_unit_port->read();

    #if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)
    // if (serial_read_event_flag[1]) {
    //   control_port->print("EVS1");
    //   control_port->write(incoming_serial_byte);
    //   control_port->println();
    // }
    if (remote_port_rx_sniff) {
      control_port->write(incoming_serial_byte);
    }
    #endif //defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)

    if ((incoming_serial_byte != 10) && (remote_unit_port_buffer_index < COMMAND_BUFFER_SIZE)) {
      // incoming_serial_byte = toupper(incoming_serial_byte);
      remote_unit_port_buffer[remote_unit_port_buffer_index] = incoming_serial_byte;
      remote_unit_port_buffer_index++;
      if ((incoming_serial_byte == 13) || (remote_unit_port_buffer_index == COMMAND_BUFFER_SIZE)) {
        remote_unit_port_buffer_carriage_return_flag = 1;
      }
    }
    serial1_last_receive_time = millis();

  }
  #endif // defined(FEATURE_MASTER_WITH_SERIAL_SLAVE)


  #ifdef FEATURE_GPS
  if (gps_port->available()) {
    byte gps_port_read = gps_port->read();
    #ifdef GPS_MIRROR_PORT
    gps_mirror_port->write(gps_port_read);
    #endif //GPS_MIRROR_PORT
    #ifdef DEBUG_GPS_SERIAL
    debug_print_char(gps_port_read);
    //port_flush();    
    #endif //DEBUG_GPS_SERIAL
    if (gps.encode(gps_port_read)) {
      gps_data_available = 1;
    }
  }
  #endif // FEATURE_GPS

  #if defined(GPS_MIRROR_PORT) && defined(FEATURE_GPS)
  if (gps_mirror_port->available()) {
    gps_port->write(gps_mirror_port->read());
  }
  #endif //defined(GPS_MIRROR_PORT) && defined(FEATURE_GPS)


} /* check_serial */


// --------------------------------------------------------------
void check_buttons(){

  #ifdef FEATURE_ADAFRUIT_BUTTONS
  int buttons = 0;
  buttons = lcd.readButtons();

  if (buttons & BUTTON_RIGHT) {
  #else
  if (button_cw && (digitalReadEnhanced(button_cw) == BUTTON_ACTIVE_STATE)) {
  #endif // FEATURE_ADAFRUIT_BUTTONS
    if (azimuth_button_was_pushed == 0) {
    #ifdef DEBUG_BUTTONS
    debug_println("check_buttons: button_cw pushed");
    #endif // DEBUG_BUTTONS
    #ifdef OPTION_AZ_MANUAL_ROTATE_LIMITS
      if (raw_azimuth < (AZ_MANUAL_ROTATE_CW_LIMIT * HEADING_MULTIPLIER)) {
      #endif
      submit_request(AZ, REQUEST_CW, 0, 61);
      azimuth_button_was_pushed = 1;
      #ifdef OPTION_AZ_MANUAL_ROTATE_LIMITS
    } else {
      #ifdef DEBUG_BUTTONS
      debug_println("check_buttons: exceeded AZ_MANUAL_ROTATE_CW_LIMIT");
      #endif // DEBUG_BUTTONS
    }
      #endif
    }

  } else {
    #ifdef FEATURE_ADAFRUIT_BUTTONS
    if (buttons & BUTTON_LEFT) {
    #else
    if (button_ccw && (digitalReadEnhanced(button_ccw) == BUTTON_ACTIVE_STATE)) {
    #endif // FEATURE_ADAFRUIT_BUTTONS
    if (azimuth_button_was_pushed == 0) {
    #ifdef DEBUG_BUTTONS
    debug_println("check_buttons: button_ccw pushed");
    #endif // DEBUG_BUTTONS  
    #ifdef OPTION_AZ_MANUAL_ROTATE_LIMITS
        if (raw_azimuth > (AZ_MANUAL_ROTATE_CCW_LIMIT * HEADING_MULTIPLIER)) {
      #endif
        submit_request(AZ, REQUEST_CCW, 0, 62);
        azimuth_button_was_pushed = 1;
      #ifdef OPTION_AZ_MANUAL_ROTATE_LIMITS
      } else {
        #ifdef DEBUG_BUTTONS
        debug_println("check_buttons: exceeded AZ_MANUAL_ROTATE_CCW_LIMIT");
        #endif // DEBUG_BUTTONS
      }
      #endif // OPTION_AZ_MANUAL_ROTATE_LIMITS
      }
    }
  }

#ifdef FEATURE_ADAFRUIT_BUTTONS
  if ((azimuth_button_was_pushed) && (!(buttons & 0x12))) {
    #ifdef DEBUG_BUTTONS
    debug_println("check_buttons: no button depressed");
    #endif // DEBUG_BUTTONS
    submit_request(AZ, REQUEST_STOP, 0, 63);
    azimuth_button_was_pushed = 0;
  }

#else
  if ((azimuth_button_was_pushed) && (digitalReadEnhanced(button_ccw) == BUTTON_INACTIVE_STATE) && (digitalReadEnhanced(button_cw) == BUTTON_INACTIVE_STATE)) {
    delay(200);
    if ((digitalReadEnhanced(button_ccw) == BUTTON_INACTIVE_STATE) && (digitalReadEnhanced(button_cw) == BUTTON_INACTIVE_STATE)) {
    #ifdef DEBUG_BUTTONS
    debug_println("check_buttons: no AZ button depressed");
    #endif // DEBUG_BUTTONS
    #ifndef OPTION_BUTTON_RELEASE_NO_SLOWDOWN
    submit_request(AZ, REQUEST_STOP, 0, 64);
    #else
    submit_request(AZ, REQUEST_KILL, 0, 65);
    #endif // OPTION_BUTTON_RELEASE_NO_SLOWDOWN
    azimuth_button_was_pushed = 0;
    }
  }
#endif // FEATURE_ADAFRUIT_BUTTONS

#ifdef FEATURE_ELEVATION_CONTROL
#ifdef FEATURE_ADAFRUIT_BUTTONS
  if (buttons & 0x08) {
  #else
  if (button_up && (digitalReadEnhanced(button_up) == BUTTON_ACTIVE_STATE)) {
  #endif // FEATURE_ADAFRUIT_BUTTONS
    if (elevation_button_was_pushed == 0) {
      submit_request(EL, REQUEST_UP, 0, 66);
      elevation_button_was_pushed = 1;
      #ifdef DEBUG_BUTTONS
      debug_println("check_buttons: button_up pushed");
      #endif // DEBUG_BUTTONS  
    }

  } else {
    #ifdef FEATURE_ADAFRUIT_BUTTONS
    if (buttons & 0x04) {
    #else
    if (button_down && (digitalReadEnhanced(button_down) == BUTTON_ACTIVE_STATE)) {
    #endif // FEATURE_ADAFRUIT_BUTTONS
      if (elevation_button_was_pushed == 0) {
        submit_request(EL, REQUEST_DOWN, 0, 67);
        elevation_button_was_pushed = 1;
      #ifdef DEBUG_BUTTONS
      debug_println("check_buttons: button_down pushed");
      #endif // DEBUG_BUTTONS    
      }
    }
  }

#ifdef FEATURE_ADAFRUIT_BUTTONS
  if ((elevation_button_was_pushed) && (!(buttons & 0x0C))) {
  #ifdef DEBUG_BUTTONS
  debug_println("check_buttons: no EL button depressed");
  #endif // DEBUG_BUTTONS
  #ifndef OPTION_BUTTON_RELEASE_NO_SLOWDOWN
    submit_request(EL, REQUEST_STOP, 0, 68);
  #else
    submit_request(EL, REQUEST_KILL, 0, 69);
  #endif // OPTION_BUTTON_RELEASE_NO_SLOWDOWN
    elevation_button_was_pushed = 0;
  }

#else
  if ((elevation_button_was_pushed) && (digitalReadEnhanced(button_up) == BUTTON_INACTIVE_STATE) && (digitalReadEnhanced(button_down) == BUTTON_INACTIVE_STATE)) {
    delay(200);
    if ((digitalReadEnhanced(button_up) == BUTTON_INACTIVE_STATE) && (digitalReadEnhanced(button_down) == BUTTON_INACTIVE_STATE)) {
    #ifdef DEBUG_BUTTONS
    debug_println("check_buttons: no EL button depressed");
    #endif // DEBUG_BUTTONS
    #ifndef OPTION_BUTTON_RELEASE_NO_SLOWDOWN
      submit_request(EL, REQUEST_STOP, 0, 70);
    #else
      submit_request(EL, REQUEST_KILL, 0, 71);
    #endif // OPTION_BUTTON_RELEASE_NO_SLOWDOWN
      elevation_button_was_pushed = 0;
    }
  }
#endif // FEATURE_ADAFRUIT_BUTTONS

#endif // FEATURE_ELEVATION_CONTROL


#ifdef FEATURE_PARK
  static byte park_button_pushed = 0;
  static unsigned long last_time_park_button_pushed = 0;

  if (button_park) {
    if ((digitalReadEnhanced(button_park) == BUTTON_ACTIVE_STATE)) {
      park_button_pushed = 1;
      last_time_park_button_pushed = millis();
    #ifdef DEBUG_BUTTONS
    debug_println("check_buttons: button_park pushed");
    #endif // DEBUG_BUTTONS   
    } else {
      if ((park_button_pushed) && ((millis() - last_time_park_button_pushed) >= 250)) {
        if (park_status != PARK_INITIATED) {
          #ifdef DEBUG_BUTTONS
          debug_println("check_buttons: executing park");
          #endif // DEBUG_BUTTONS
          initiate_park();
        } else {
          #ifdef DEBUG_BUTTONS
          debug_println("check_buttons: park aborted");
          #endif // DEBUG_BUTTONS
          submit_request(AZ, REQUEST_KILL, 0, 72);
            #ifdef FEATURE_ELEVATION_CONTROL
          submit_request(EL, REQUEST_KILL, 0, 73);
            #endif // FEATURE_ELEVATION_CONTROL
        }
        park_button_pushed = 0;
      }
    }

  }

    #endif /* ifdef FEATURE_PARK */


  if (button_stop) {
    if ((digitalReadEnhanced(button_stop) == BUTTON_ACTIVE_STATE)) {
      #ifdef DEBUG_BUTTONS
      debug_println("check_buttons: button_stop pushed");
      #endif // DEBUG_BUTTONS      
      #ifndef OPTION_BUTTON_RELEASE_NO_SLOWDOWN
      submit_request(AZ, REQUEST_STOP, 0, 74);
      #else
      submit_request(AZ, REQUEST_KILL, 0, 75);
      #endif // OPTION_BUTTON_RELEASE_NO_SLOWDOWN
      #ifdef FEATURE_ELEVATION_CONTROL
      #ifndef OPTION_BUTTON_RELEASE_NO_SLOWDOWN
      submit_request(EL, REQUEST_STOP, 0, 76);
      #else
      submit_request(EL, REQUEST_KILL, 0, 77);
      #endif // OPTION_BUTTON_RELEASE_NO_SLOWDOWN
      #endif // FEATURE_ELEVATION_CONTROL
    }
  }

  #ifdef FEATURE_MOON_TRACKING
  static byte moon_tracking_button_pushed = 0;
  static unsigned long last_time_moon_tracking_button_pushed = 0;
  if (moon_tracking_button) {
    if ((digitalReadEnhanced(moon_tracking_button) == BUTTON_ACTIVE_STATE)) {
      moon_tracking_button_pushed = 1;
      last_time_moon_tracking_button_pushed = millis();
      #ifdef DEBUG_BUTTONS
      debug_println("check_buttons: moon_tracking_button pushed");
      #endif // DEBUG_BUTTONS
    } else {
      if ((moon_tracking_button_pushed) && ((millis() - last_time_moon_tracking_button_pushed) >= 250)) {
        if (!moon_tracking_active) {
          #ifdef DEBUG_BUTTONS
          debug_println("check_buttons: moon tracking on");
          #endif // DEBUG_BUTTONS
          moon_tracking_active = 1;
        } else {
          #ifdef DEBUG_BUTTONS
           debug_println("check_buttons: moon tracking off");
          #endif // DEBUG_BUTTONS
          moon_tracking_active = 0;
        }
        moon_tracking_button_pushed = 0;
      }
    }
  }
  #endif // FEATURE_MOON_TRACKING

  #ifdef FEATURE_SUN_TRACKING
  static byte sun_tracking_button_pushed = 0;
  static unsigned long last_time_sun_tracking_button_pushed = 0;
  if (sun_tracking_button) {
    if ((digitalReadEnhanced(sun_tracking_button) == BUTTON_ACTIVE_STATE)) {
      sun_tracking_button_pushed = 1;
      last_time_sun_tracking_button_pushed = millis();
      #ifdef DEBUG_BUTTONS
      debug_println("check_buttons: sun_tracking_button pushed");
      #endif // DEBUG_BUTTONS
    } else {
      if ((sun_tracking_button_pushed) && ((millis() - last_time_sun_tracking_button_pushed) >= 250)) {
        if (!sun_tracking_active) {
          #ifdef DEBUG_BUTTONS
          debug_println("check_buttons: sun tracking on");
          #endif // DEBUG_BUTTONS
          sun_tracking_active = 1;
        } else {
          #ifdef DEBUG_BUTTONS
          debug_print("check_buttons: sun tracking off");
          #endif // DEBUG_BUTTONS
          sun_tracking_active = 0;
        }
        sun_tracking_button_pushed = 0;
      }
    }
  }
  #endif // FEATURE_SUN_TRACKING

} /* check_buttons */
// --------------------------------------------------------------
#ifdef FEATURE_LCD_DISPLAY
char * idle_status(){


  #ifdef OPTION_DISPLAY_DIRECTION_STATUS
  return azimuth_direction(azimuth);
  #endif //OPTION_DISPLAY_DIRECTION_STATUS

  return("");



}


#endif //FEATURE_LCD_DISPLAY
// --------------------------------------------------------------

#if defined(FEATURE_LCD_DISPLAY) && defined(OPTION_DISPLAY_DIRECTION_STATUS)
char * azimuth_direction(int azimuth_in){

  azimuth_in = azimuth_in / HEADING_MULTIPLIER;



  if (azimuth_in > 348) {
    return N_STRING;
  }
  if (azimuth_in > 326) {
    return NNW_STRING;
  }
  if (azimuth_in > 303) {
    return NW_STRING;
  }
  if (azimuth_in > 281) {
    return WNW_STRING;
  }
  if (azimuth_in > 258) {
    return W_STRING;
  }
  if (azimuth_in > 236) {
    return WNW_STRING;
  }
  if (azimuth_in > 213) {
    return SW_STRING;
  }
  if (azimuth_in > 191) {
    return SSW_STRING;
  }
  if (azimuth_in > 168) {
    return S_STRING;
  }
  if (azimuth_in > 146) {
    return SSE_STRING;
  }
  if (azimuth_in > 123) {
    return SE_STRING;
  }
  if (azimuth_in > 101) {
    return ESE_STRING;
  }
  if (azimuth_in > 78) {
    return E_STRING;
  }
  if (azimuth_in > 56) {
    return ENE_STRING;
  }
  if (azimuth_in > 33) {
    return NE_STRING;
  }
  if (azimuth_in > 11) {
    return NNE_STRING;
  }
  return N_STRING;

} /* azimuth_direction */
#endif /* ifdef FEATURE_LCD_DISPLAY */
// --------------------------------------------------------------
#if defined(FEATURE_LCD_DISPLAY)
void update_display(){

  // update the LCD display

  static byte lcd_state_row_0 = 0;
  static byte lcd_state_row_1 = 0;

  String row_0_string;

  static int last_azimuth = -1;

  char workstring[10] = "";

  unsigned int target = 0;

  #ifdef FEATURE_ELEVATION_CONTROL
  static int last_elevation = -1;
  static int last_target_elevation = 0;
  static byte last_el_state = 999;
  #endif

  byte decimal_places = 0;
  static byte last_az_state = 999;


  if ((lcd_state_row_0 == 0) && (lcd_state_row_1 == 0)){
    if (millis() < SPLASH_SCREEN_TIME){
      return;
    } else {
      lcd.clear();
      lcd_state_row_0 = LCD_IDLE_STATUS;
    }
  }


  // row 0 ------------------------------------------------------------

  #ifndef FEATURE_ELEVATION_CONTROL
  if (((millis() - last_lcd_update) > LCD_UPDATE_TIME) || (push_lcd_update) || (az_state != last_az_state)) {
  #else
  if (((millis() - last_lcd_update) > LCD_UPDATE_TIME) || (push_lcd_update) || (az_state != last_el_state) || (el_state != last_el_state)) {
  #endif

    #ifndef FEATURE_ELEVATION_CONTROL
    #ifdef FEATURE_AZ_PRESET_ENCODER
    target = az_encoder_raw_degrees;
    if (target > (359 * LCD_HEADING_MULTIPLIER)) {
      target = target - (360 * LCD_HEADING_MULTIPLIER);
    }
    if (target > (359 * LCD_HEADING_MULTIPLIER)) {
      target = target - (360 * LCD_HEADING_MULTIPLIER);
    }

    if (preset_encoders_state == ENCODER_AZ_PENDING) {
      clear_display_row(0);                                                 // Show Target Deg on upper line
      row_0_string = TARGET_STRING;
      dtostrf(target / LCD_HEADING_MULTIPLIER, 1, LCD_DECIMAL_PLACES, workstring);
      row_0_string.concat(workstring);
      row_0_string.concat(char(223));
      lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
      lcd.print(row_0_string);

      lcd_state_row_0 = LCD_TARGET_AZ;
      #ifdef DEBUG_DISPLAY
      if (debug_mode) {
        control_port->print(F("update_display: "));
        control_port->println(row_0_string);
      }
      #endif // DEBUG_DISPLAY

    } else {
    #endif // FEATURE_AZ_PRESET_ENCODER

    if (last_az_state != az_state){
      if (az_state != IDLE) {
        if (az_request_queue_state == IN_PROGRESS_TO_TARGET) {
          clear_display_row(0);
          row_0_string = ROTATING_TO_STRING;
          dtostrf(target_azimuth / LCD_HEADING_MULTIPLIER, 1, LCD_DECIMAL_PLACES, workstring);
          row_0_string.concat(workstring);
          // row_0_string.concat(int(target_azimuth / LCD_HEADING_MULTIPLIER));
          row_0_string.concat(char(223));
          lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
          lcd.print(row_0_string);
          lcd_state_row_0 = LCD_ROTATING_TO;

          #ifdef DEBUG_DISPLAY
          if (debug_mode) {
            control_port->print(F("update_display: "));
            control_port->println(row_0_string);
          }
          #endif // DEBUG_DISPLAY

        } else {

          if ((az_state == SLOW_START_CW) || (az_state == NORMAL_CW) || (az_state == SLOW_DOWN_CW) || (az_state == TIMED_SLOW_DOWN_CW)) {
            if (lcd_state_row_0 != LCD_ROTATING_CW) {
              clear_display_row(0);
              row_0_string = ROTATING_CW_STRING;
              lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
              lcd.print(row_0_string);
              lcd_state_row_0 = LCD_ROTATING_CW;
              #ifdef DEBUG_DISPLAY
              if (debug_mode) {
                control_port->print(F("update_display: "));
                control_port->println(row_0_string);
              }
              #endif // DEBUG_DISPLAY
            }
          } else {
            if (lcd_state_row_0 != LCD_ROTATING_CCW) {
              clear_display_row(0);
              row_0_string = ROTATING_CCW_STRING;
              lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
              lcd.print(row_0_string);
              lcd_state_row_0 = LCD_ROTATING_CCW;
              #ifdef DEBUG_DISPLAY
              if (debug_mode) {
                control_port->print(F("update_display: "));
                control_port->println(row_0_string);
              }
              #endif // DEBUG_DISPLAY
            }
          }
        }
      } else {   // az_state == IDLE


        #ifndef FEATURE_PARK // ---------
        if ((last_azimuth != azimuth) || (lcd_state_row_0 != LCD_IDLE_STATUS)) {
          row_0_string.concat(idle_status());
          if ((last_row_0_string == row_0_string) || (lcd_state_row_0 != LCD_IDLE_STATUS)) {
            clear_display_row(0);
            lcd_state_row_0 = LCD_IDLE_STATUS;
            #ifdef OPTION_DISPLAY_DIRECTION_STATUS
            lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
            lcd.print(row_0_string);            
            #ifdef DEBUG_DISPLAY
            if (debug_mode) {
              control_port->print(F("update_display: "));
              control_port->println(row_0_string);
            }
            #endif // DEBUG_DISPLAY
            #endif //OPTION_DISPLAY_DIRECTION_STATUS
          } else {
            #ifdef OPTION_DISPLAY_DIRECTION_STATUS
            lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2) - 1, 0);
            lcd.print(" ");
            lcd.print(row_0_string);
            lcd.print(" ");
            #ifdef DEBUG_DISPLAY
            if (debug_mode) {
              control_port->print(F("update_display: "));
              control_port->println(row_0_string);
            }
            #endif // DEBUG_DISPLAY
            #endif //OPTION_DISPLAY_DIRECTION_STATUS
          }
        }

        #else // FEATURE_PARK-----------

        if (park_status == PARKED) {
          if (lcd_state_row_0 != LCD_PARKED) {
            row_0_string = PARKED_STRING;
            clear_display_row(0);
            lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
            lcd.print(row_0_string);
            lcd_state_row_0 = LCD_PARKED;
          }

        } else {
          if ((last_azimuth != azimuth) || (lcd_state_row_0 != LCD_IDLE_STATUS)) {
            row_0_string.concat(idle_status());
            if ((last_row_0_string == row_0_string) || (lcd_state_row_0 != LCD_IDLE_STATUS)) {
              clear_display_row(0);
              lcd_state_row_0 = LCD_IDLE_STATUS;
              #ifdef OPTION_DISPLAY_DIRECTION_STATUS
              lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
              lcd.print(row_0_string);            
              #ifdef DEBUG_DISPLAY
              if (debug_mode) {
                control_port->print(F("update_display: "));
                control_port->println(row_0_string);
              }
              #endif // DEBUG_DISPLAY
              #endif //OPTION_DISPLAY_DIRECTION_STATUS
            } else {
              #ifdef OPTION_DISPLAY_DIRECTION_STATUS
              lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2) - 1, 0);
              lcd.print(" ");
              lcd.print(row_0_string);
              lcd.print(" ");
              #ifdef DEBUG_DISPLAY
              if (debug_mode) {
                control_port->print(F("update_display: "));
                control_port->println(row_0_string);
              }
              #endif // DEBUG_DISPLAY
              #endif //OPTION_DISPLAY_DIRECTION_STATUS
            }
          }
        }
        #endif // FEATURE_PARK ---------





      }   // (az_state != IDLE)
      }//<---
    #ifdef FEATURE_AZ_PRESET_ENCODER
  }   // (preset_encoders_state == ENCODER_AZ_PENDING)
    #endif // FEATURE_AZ_PRESET_ENCODER
    #endif /* ifndef FEATURE_ELEVATION_CONTROL */

    // ------------ AZ & EL -----------------------------------------------

    #ifdef FEATURE_ELEVATION_CONTROL

    #ifdef FEATURE_AZ_PRESET_ENCODER
    #ifndef FEATURE_EL_PRESET_ENCODER

    unsigned int target = az_encoder_raw_degrees;
    if (target > (359 * LCD_HEADING_MULTIPLIER)) {
      target = target - (360 * LCD_HEADING_MULTIPLIER);
    }
    if (target > (359 * LCD_HEADING_MULTIPLIER)) {
      target = target - (360 * LCD_HEADING_MULTIPLIER);
    }

    if (preset_encoders_state == ENCODER_AZ_PENDING) {
      clear_display_row(0);                                                 // Show Target Deg on upper line
      row_0_string = TARGET_STRING;
      dtostrf(target / LCD_HEADING_MULTIPLIER, 1, LCD_DECIMAL_PLACES, workstring);
      row_0_string.concat(workstring);
      lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
      lcd.print(row_0_string);

      lcd_state_row_0 = LCD_TARGET_AZ;
      #ifdef DEBUG_DISPLAY
      if (debug_mode) {
        control_port->print(F("update_display: "));
        control_port->println(row_0_string);
      }
      #endif // DEBUG_DISPLAY

    } else {

    #endif // ndef FEATURE_EL_PRESET_ENCODER
    #endif // FEATURE_AZ_PRESET_ENCODER


    #ifdef FEATURE_EL_PRESET_ENCODER
    unsigned int target = az_encoder_raw_degrees;
    if (target > (359 * LCD_HEADING_MULTIPLIER)) {
      target = target - (360 * LCD_HEADING_MULTIPLIER);
    }
    if (target > (359 * LCD_HEADING_MULTIPLIER)) {
      target = target - (360 * LCD_HEADING_MULTIPLIER);
    }

    if (preset_encoders_state != ENCODER_IDLE) {
      switch (preset_encoders_state) {
        case ENCODER_AZ_PENDING:
          clear_display_row(0);                                                 // Show Target Deg on upper line
          row_0_string = AZ_TARGET_STRING;
          dtostrf(target / LCD_HEADING_MULTIPLIER, 1, LCD_DECIMAL_PLACES, workstring);
          row_0_string.concat(workstring);
          row_0_string.concat(char(223));
          lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
          lcd.print(row_0_string);
          lcd_state_row_0 = LCD_TARGET_AZ;
          break;
        case ENCODER_EL_PENDING:
          clear_display_row(0);                                                 // Show Target Deg on upper line
          row_0_string = EL_TARGET_STRING;
          dtostrf(el_encoder_degrees / LCD_HEADING_MULTIPLIER, 1, LCD_DECIMAL_PLACES, workstring);
          row_0_string.concat(workstring);
          row_0_string.concat(char(223));
          lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
          lcd.print(row_0_string);
          lcd_state_row_0 = LCD_TARGET_EL;
          break;
        case ENCODER_AZ_EL_PENDING:
          clear_display_row(0);                                                 // Show Target Deg on upper line
          row_0_string = TARGET_STRING;
          dtostrf(target / LCD_HEADING_MULTIPLIER, 1, LCD_DECIMAL_PLACES, workstring);
          row_0_string.concat(workstring);
          row_0_string.concat(char(223));
          dtostrf(el_encoder_degrees / LCD_HEADING_MULTIPLIER, 1, LCD_DECIMAL_PLACES, workstring);
          row_0_string.concat("   ");
          row_0_string.concat(workstring);
          row_0_string.concat(char(223));
          lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
          lcd.print(row_0_string);
          lcd_state_row_0 = LCD_TARGET_AZ_EL;
          break;
      } /* switch */
    } else { // (preset_encoders_state != ENCODER_IDLE)
    #endif // FEATURE_EL_PRESET_ENCODER


  if ((az_state != last_az_state) || (el_state != last_el_state) || push_lcd_update){

    if ((az_state != IDLE) && (el_state == IDLE)) {
      if (az_request_queue_state == IN_PROGRESS_TO_TARGET) {
        clear_display_row(0);
        row_0_string = ROTATING_TO_STRING;
        dtostrf(target_azimuth / LCD_HEADING_MULTIPLIER, 1, LCD_DECIMAL_PLACES, workstring);
        row_0_string.concat(workstring);
        row_0_string.concat(char(223));
        lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
        lcd.print(row_0_string);
        lcd_state_row_0 = LCD_ROTATING_TO;
      } else {
        if ((az_state == SLOW_START_CW) || (az_state == NORMAL_CW) || (az_state == SLOW_DOWN_CW) || (az_state == TIMED_SLOW_DOWN_CW)) {
          clear_display_row(0);
          row_0_string = ROTATING_CW_STRING;
          lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
          lcd.print(row_0_string);
          lcd_state_row_0 = LCD_ROTATING_CW;
        } else {
          clear_display_row(0);
          row_0_string = ROTATING_CCW_STRING;
          lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
          lcd.print(row_0_string);
          lcd_state_row_0 = LCD_ROTATING_CCW;
        }
      }
    }   // ((az_state != IDLE) && (el_state == IDLE))

    if ((az_state == IDLE) && (el_state != IDLE)) {
      // if ((el_request_queue_state == IN_PROGRESS_TO_TARGET) && ((lcd_state_row_0 != LCD_ELEVATING_TO) || (target_elevation != last_target_elevation))){
      if (el_request_queue_state == IN_PROGRESS_TO_TARGET) {
        if ((lcd_state_row_0 != LCD_ELEVATING_TO) || (target_elevation != last_target_elevation)) {
          clear_display_row(0);
          row_0_string = ELEVATING_TO_STRING;
          dtostrf(target_elevation / LCD_HEADING_MULTIPLIER, 1, LCD_DECIMAL_PLACES, workstring);
          row_0_string.concat(workstring);
          row_0_string.concat(char(223));
          lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
          lcd.print(row_0_string);
          lcd_state_row_0 = LCD_ELEVATING_TO;
        }
      } else {
        if (((el_state == SLOW_START_UP) || (el_state == NORMAL_UP) || (el_state == SLOW_DOWN_UP) || (el_state == TIMED_SLOW_DOWN_UP)) && (lcd_state_row_0 != LCD_ELEVATING_UP)) {
          clear_display_row(0);
          row_0_string = ELEVATING_UP_STRING;
          lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
          lcd.print(row_0_string);
          lcd_state_row_0 = LCD_ELEVATING_UP;
        }
        if (((el_state == SLOW_START_DOWN) || (el_state == NORMAL_DOWN) || (el_state == SLOW_DOWN_DOWN) || (el_state == TIMED_SLOW_DOWN_DOWN)) && (lcd_state_row_0 != LCD_ELEVATING_DOWN)) {
          clear_display_row(0);
          row_0_string = ELEVATING_DOWN_STRING;
          lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
          lcd.print(row_0_string);
          lcd_state_row_0 = LCD_ELEVATING_DOWN;
        }
      }
    }   // ((az_state == IDLE) && (el_state != IDLE))

    if ((az_state != IDLE) && (el_state != IDLE) && (lcd_state_row_0 != LCD_ROTATING_AZ_EL)) {
      clear_display_row(0);
      row_0_string = ROTATING_STRING;
      if (az_request_queue_state == NONE) {
        if (current_az_state() == ROTATING_CW) {
          row_0_string.concat(CW_STRING);
        } else {
          row_0_string.concat(CCW_STRING);
        }
      } else {
        //row_0_string.concat(int(target_azimuth / LCD_HEADING_MULTIPLIER));
        if ((target_azimuth / LCD_HEADING_MULTIPLIER) < 100){decimal_places = LCD_DECIMAL_PLACES;} else {decimal_places = 0;}
        dtostrf(target_azimuth / LCD_HEADING_MULTIPLIER, 1, decimal_places, workstring);
        row_0_string.concat(workstring);        
      }
      row_0_string.concat(" ");
      if (el_request_queue_state == NONE) {
        if (current_el_state() == ROTATING_UP) {
          row_0_string.concat(UP_STRING);
        } else {
          row_0_string.concat(DOWN_STRING);
        }
      } else {
        if ((target_elevation / LCD_HEADING_MULTIPLIER) < 100){decimal_places = LCD_DECIMAL_PLACES;} else {decimal_places = 0;}
        dtostrf(target_elevation / LCD_HEADING_MULTIPLIER, 1, decimal_places, workstring);
        row_0_string.concat(workstring);
      }
      lcd_state_row_0 = LCD_ROTATING_AZ_EL;
      lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
      lcd.print(row_0_string);
    }   // ((az_state != IDLE) && (el_state != IDLE))

    if ((az_state == IDLE) && (el_state == IDLE)) {

      #ifndef FEATURE_PARK
      if ((last_azimuth != azimuth) || (lcd_state_row_0 != LCD_IDLE_STATUS)) {
        row_0_string.concat(idle_status());
        if ((last_row_0_string != row_0_string) || (lcd_state_row_0 != LCD_IDLE_STATUS)) {
          clear_display_row(0);
          lcd_state_row_0 = LCD_IDLE_STATUS;          
          #ifdef OPTION_DISPLAY_DIRECTION_STATUS
          lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
          lcd.print(row_0_string);
          #endif //OPTION_DISPLAY_DIRECTION_STATUS
        } else {
          #ifdef OPTION_DISPLAY_DIRECTION_STATUS
          lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2) - 1, 0);
          lcd.print(" ");
          lcd.print(row_0_string);
          lcd.print(" ");
          #endif //OPTION_DISPLAY_DIRECTION_STATUS
        }
      }
      #else // FEATURE_PARK


      if (park_status == PARKED) {
        if (lcd_state_row_0 != LCD_PARKED) {
          row_0_string = PARKED_STRING;
          clear_display_row(0);
          lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
          lcd.print(row_0_string);
          lcd_state_row_0 = LCD_PARKED;
        }
      } else {
        if ((last_azimuth != azimuth) || (lcd_state_row_0 != LCD_IDLE_STATUS)) {
          row_0_string.concat(idle_status());
          if ((last_row_0_string == row_0_string) || (lcd_state_row_0 != LCD_IDLE_STATUS)) {
            clear_display_row(0);
            lcd_state_row_0 = LCD_IDLE_STATUS;
            #ifdef OPTION_DISPLAY_DIRECTION_STATUS       
            lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 0);
            lcd.print(row_0_string);
            #endif //OPTION_DISPLAY_DIRECTION_STATUS
          } else {
            #ifdef OPTION_DISPLAY_DIRECTION_STATUS
            lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2) - 1, 0);
            lcd.print(" ");
            lcd.print(row_0_string);
            lcd.print(" ");
            #endif //OPTION_DISPLAY_DIRECTION_STATUS
          }
        }
      }
      #endif // FEATURE_PARK


    }   // ((az_state == IDLE) && (el_state == IDLE))

      #ifdef FEATURE_EL_PRESET_ENCODER
  }   // (preset_encoders_state != ENCODER_IDLE)
    #endif // FEATURE_EL_PRESET_ENCODER



    #ifdef FEATURE_AZ_PRESET_ENCODER
    #ifndef FEATURE_EL_PRESET_ENCODER
  }
  #endif // ndef FEATURE_EL_PRESET_ENCODER
  #endif // FEATURE_AZ_PRESET_ENCODER

  } //<--

    #endif // FEATURE_ELEVATION_CONTROL



    push_lcd_update = 0;
    last_az_state = az_state;
    #ifdef FEATURE_ELEVATION_CONTROL
    last_el_state = el_state;
    #endif // FEATURE_ELEVATION_CONTROL

  }


  //     row 1 --------------------------------------------


  if ((millis() - last_lcd_update) > LCD_UPDATE_TIME) {
    #ifndef FEATURE_ELEVATION_CONTROL // ---------------- az only -----------------------------------
    if (last_azimuth != azimuth) {
      //clear_display_row(1);
      row_0_string = AZIMUTH_STRING;
      dtostrf(azimuth / LCD_HEADING_MULTIPLIER, 1, LCD_DECIMAL_PLACES, workstring);
      row_0_string.concat(workstring);
      row_0_string.concat(char(223));
      //lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 1);
      lcd.setCursor(0,1);
      int x = LCD_COLUMNS - row_0_string.length();
      byte y = 0;
      while (x > 0){
        if ((y%2) != 0){
          row_0_string = " " + row_0_string;
        } else {
          row_0_string.concat(" ");
        }
        y++;
        x--;
      }      
      lcd.print(row_0_string);
      last_azimuth = azimuth;
      lcd_state_row_1 = LCD_HEADING;
    }
    #endif // FEATURE_ELEVATION_CONTROL---------------------------------------------------------------




    #ifdef FEATURE_ELEVATION_CONTROL  // --------------------az & el---------------------------------
    if ((last_azimuth != azimuth) || (last_elevation != elevation)) {
      //clear_display_row(1);
      #if defined(FEATURE_ONE_DECIMAL_PLACE_HEADINGS) || defined(FEATURE_TWO_DECIMAL_PLACE_HEADINGS)
      if ((azimuth >= 1000) && (elevation >= 1000)) {
        row_0_string = AZ_STRING;
      } else {
        row_0_string = AZ_SPACE_STRING;
      }
      #else
      row_0_string = AZ_SPACE_STRING;
      #endif // efined(FEATURE_ONE_DECIMAL_PLACE_HEADINGS) || defined(FEATURE_TWO_DECIMAL_PLACE_HEADINGS)
      dtostrf(azimuth/ LCD_HEADING_MULTIPLIER, 3, LCD_DECIMAL_PLACES, workstring);
      row_0_string.concat(workstring);

      #if !defined(FEATURE_ONE_DECIMAL_PLACE_HEADINGS) && !defined(FEATURE_TWO_DECIMAL_PLACE_HEADINGS)
      if (LCD_COLUMNS > 14) {
        row_0_string.concat(char(223));
      }
      #else
      if ((LCD_COLUMNS > 18) || ((azimuth < 100) && (elevation < 100))) {
        row_0_string.concat(char(223));
      }
      #endif

      #if defined(FEATURE_ONE_DECIMAL_PLACE_HEADINGS) || defined(FEATURE_TWO_DECIMAL_PLACE_HEADINGS)
      if ((elevation >= 1000) && (azimuth >= 1000)) {
        row_0_string.concat(SPACE_EL_STRING);
      } else {
        row_0_string.concat(SPACE_EL_SPACE_STRING);
      }
      #else
      row_0_string.concat(SPACE_EL_SPACE_STRING);
      #endif // defined(FEATURE_ONE_DECIMAL_PLACE_HEADINGS) || defined(FEATURE_TWO_DECIMAL_PLACE_HEADINGS)

      dtostrf(elevation / LCD_HEADING_MULTIPLIER, 1, LCD_DECIMAL_PLACES, workstring);
      row_0_string.concat(workstring);

      #if !defined(FEATURE_ONE_DECIMAL_PLACE_HEADINGS) && !defined(FEATURE_TWO_DECIMAL_PLACE_HEADINGS)
      if (LCD_COLUMNS > 14) {
        row_0_string.concat(char(223));
      }
      #else
      if ((LCD_COLUMNS > 18) || ((azimuth < 100) && (elevation < 100))) {
        row_0_string.concat(char(223));
      }
      #endif

      lcd.setCursor(0,1);
      int x = LCD_COLUMNS - row_0_string.length();
      byte y = 0;
      while (x > 0){
        if ((y%2) != 0){
          row_0_string = " " + row_0_string;
        } else {
          row_0_string.concat(" ");
        }
        y++;
        x--;
      }
      //lcd.setCursor(((LCD_COLUMNS - row_0_string.length()) / 2), 1);
      lcd.print(row_0_string);

      last_azimuth = azimuth;
      last_elevation = elevation;
      lcd_state_row_1 = LCD_HEADING;
    }
        #endif // FEATURE_ELEVATION_CONTROL //------------------------------------------------------------



  }


  char temp_string[10] = "";

  // clock display -- small ----------------------------------------------------------
  #if defined(OPTION_DISPLAY_HHMMSS_CLOCK) && defined(FEATURE_CLOCK)

  
  char clock_temp_string[9] = "";
  static byte last_clock_seconds = 0;
  static byte last_clock_lcd_row_state = 0;
  byte clock_digits = 0;


  update_time();
  if (((last_clock_seconds != clock_seconds) || (last_clock_lcd_row_state != LCD_IDLE_STATUS)) && (lcd_state_row_0 == LCD_IDLE_STATUS)){
    #ifdef OPTION_CLOCK_ALWAYS_HAVE_HOUR_LEADING_ZERO
    if (clock_hours < 10) {
      strcat(clock_temp_string, "0");
    }    
    dtostrf(clock_hours, 0, 0, temp_string);
    strcat(clock_temp_string,temp_string);    
    #else    
    dtostrf(clock_hours, 0, 0, temp_string);
    strcpy(clock_temp_string,temp_string);
    #endif //OPTION_CLOCK_ALWAYS_HAVE_HOUR_LEADING_ZERO
    strcat(clock_temp_string,":");
    if (clock_minutes < 10) {
      strcat(clock_temp_string, "0");
    }
    if (clock_hours > 9){
      clock_digits = 1;
    }
    dtostrf(clock_minutes, 0, 0, temp_string);
    strcat(clock_temp_string,temp_string);
    strcat(clock_temp_string,":");
    if (clock_seconds < 10) {
      strcat(clock_temp_string, "0");
    }
    dtostrf(clock_seconds, 0, 0, temp_string);
    strcat(clock_temp_string,temp_string);
    if (LCD_HHMMSS_CLOCK_POSITION == LEFT){
      lcd.setCursor(0,0);
    } else {
      lcd.setCursor(LCD_COLUMNS-(7+clock_digits),0);
    }
    lcd.print(clock_temp_string);
    if ((clock_minutes == 0) && (clock_hours == 0)) {
      if (LCD_HHMMSS_CLOCK_POSITION == RIGHT){
        lcd.setCursor(LCD_COLUMNS-(9+clock_digits),0);
      }
      lcd.print("  ");
    }
    last_clock_seconds = clock_seconds;
    
  }
  last_clock_lcd_row_state = lcd_state_row_0;
  #endif //defined(OPTION_DISPLAY_HHMMSS_CLOCK) && defined(FEATURE_CLOCK)



  // clock display -- small ----------------------------------------------------------
  #if defined(OPTION_DISPLAY_HHMM_CLOCK) && defined(FEATURE_CLOCK)

  
  char clock_temp_string[10] = "";
  static byte last_clock_minutes = 0;
  static byte last_clock_lcd_row_state = 0;
  byte clock_digits = 0;


  update_time();
  if (((last_clock_minutes != clock_minutes) || (last_clock_lcd_row_state != LCD_IDLE_STATUS)) && (lcd_state_row_0 == LCD_IDLE_STATUS)){
    #ifdef OPTION_CLOCK_ALWAYS_HAVE_HOUR_LEADING_ZERO
    if (clock_hours < 10) {
      strcat(clock_temp_string, "0");
    }    
    dtostrf(clock_hours, 0, 0, temp_string);
    strcat(clock_temp_string,temp_string);    
    #else
    dtostrf(clock_hours, 0, 0, temp_string);
    strcpy(clock_temp_string,temp_string);
    #endif //OPTION_CLOCK_ALWAYS_HAVE_HOUR_LEADING_ZERO
    strcat(clock_temp_string,":");
    if (clock_minutes < 10) {
      strcat(clock_temp_string, "0");
    }
    if (clock_hours > 9){
      clock_digits = 1;
    }
    dtostrf(clock_minutes, 0, 0, temp_string);
    strcat(clock_temp_string,temp_string);
    if (LCD_HHMM_CLOCK_POSITION == LEFT){
      lcd.setCursor(0,0);
    } else {
      lcd.setCursor(LCD_COLUMNS-(4+clock_digits),0);
    }
    lcd.print(clock_temp_string);
    if ((clock_minutes == 0) && (clock_hours == 0)) {
      if (LCD_HHMM_CLOCK_POSITION == RIGHT){
        lcd.setCursor(LCD_COLUMNS-(6+clock_digits),0);
      }
      lcd.print("  ");
    }
    last_clock_minutes = clock_minutes;
    
  }
  last_clock_lcd_row_state = lcd_state_row_0;
  #endif //defined(OPTION_DISPLAY_HHMM_CLOCK) && defined(FEATURE_CLOCK)


// alternating H:MM clock and maidenhead display ------------------------------------------------------------
  #if defined(OPTION_DISPLAY_ALT_HHMM_CLOCK_AND_MAIDENHEAD) && defined(FEATURE_CLOCK)

  
  char clock_temp_string[10] = "";
  static byte last_clock_minutes = 0;
  static byte last_clock_seconds = 0;
  static byte last_clock_lcd_row_state = 0;
  byte clock_digits = 0;
  static byte displaying_clock = 1;


  if ((lcd_state_row_0 != LCD_UNDEF) && ((lcd_state_row_0 == LCD_IDLE_STATUS) || ((LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_ROW-1)!= 0))){
    update_time();

    if (((last_clock_seconds != clock_seconds) || ((((LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_ROW-1)== 0))) && (last_clock_lcd_row_state != LCD_IDLE_STATUS)) && ((lcd_state_row_0 == LCD_IDLE_STATUS) || ((LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_ROW-1)!= 0))){
      if (((clock_seconds % 5) == 0) || (((LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_ROW-1)== 0) && (last_clock_lcd_row_state != LCD_IDLE_STATUS))) {
        if (displaying_clock){
          if (LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_POSITION == LEFT){
            lcd.setCursor(0,LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_ROW-1);        
          } else {
            lcd.setCursor(LCD_COLUMNS-6,LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_ROW-1); 
          }
          lcd.print(coordinates_to_maidenhead(latitude,longitude));
          displaying_clock = 0;
        } else {
          displaying_clock = 2;  // switch to the clock (2 == print the clock regardless of time)
        }

      }
      last_clock_seconds = clock_seconds;
    }


    if (((displaying_clock && (last_clock_minutes != clock_minutes)) || (displaying_clock == 2)) && ((lcd_state_row_0 == LCD_IDLE_STATUS) || ((LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_ROW-1)!= 0))){
      #ifdef OPTION_CLOCK_ALWAYS_HAVE_HOUR_LEADING_ZERO
      if (clock_hours < 10) {
        strcpy(clock_temp_string, "0");
      }    
      dtostrf(clock_hours, 0, 0, temp_string);
      strcat(clock_temp_string,temp_string);    
      #else          
      dtostrf(clock_hours, 0, 0, temp_string);
      strcpy(clock_temp_string,temp_string);
      #endif //OPTION_CLOCK_ALWAYS_HAVE_HOUR_LEADING_ZERO
      strcat(clock_temp_string,":");
      if (clock_minutes < 10) {
        strcat(clock_temp_string, "0");
      }
      if (clock_hours > 9){
        clock_digits = 1;
      }
      dtostrf(clock_minutes, 0, 0, temp_string);
      strcat(clock_temp_string,temp_string);
      if (LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_POSITION == LEFT){
        lcd.setCursor(0,LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_ROW-1);
      } else {
        lcd.setCursor(LCD_COLUMNS-(4+clock_digits),LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_ROW-1);
      }
      lcd.print(clock_temp_string);
      if (LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_POSITION == RIGHT){
        lcd.setCursor(LCD_COLUMNS-(6+clock_digits),LCD_ALT_HHMM_CLOCK_AND_MAIDENHEAD_ROW-1);
      }
      lcd.print("  ");
      last_clock_minutes = clock_minutes;
      displaying_clock = 1;
    }
    last_clock_lcd_row_state = lcd_state_row_0;
  }
  #endif //defined(OPTION_DISPLAY_ALT_HHMM_CLOCK_AND_MAIDENHEAD) && defined(FEATURE_CLOCK)

  // constant HH:MM:SS clock and maidenhead display  ----------------------------------------------------------
  #if defined(OPTION_DISPLAY_CONSTANT_HHMMSS_CLOCK_AND_MAIDENHEAD) && defined(FEATURE_CLOCK)

  
  char clock_temp_string[14] = "";
  static byte last_clock_minutes = 0;
  static byte last_clock_seconds = 0;
  static byte last_clock_lcd_row_state = 0;
  byte clock_digits = 0;


  if ((lcd_state_row_0 != LCD_UNDEF) && ((lcd_state_row_0 == LCD_IDLE_STATUS) || ((LCD_CONSTANT_HHMMSS_CLOCK_AND_MAIDENHEAD_ROW-1)!= 0))){
    update_time();

    if (((last_clock_seconds != clock_seconds) || ((((LCD_CONSTANT_HHMMSS_CLOCK_AND_MAIDENHEAD_ROW-1)== 0))) && (last_clock_lcd_row_state != LCD_IDLE_STATUS)) && ((lcd_state_row_0 == LCD_IDLE_STATUS) || ((LCD_CONSTANT_HHMMSS_CLOCK_AND_MAIDENHEAD_ROW-1)!= 0))){
      if (LCD_CONSTANT_HHMMSS_CLOCK_AND_MAIDENHEAD_POSITION == LEFT){
        lcd.setCursor(0,LCD_CONSTANT_HHMMSS_CLOCK_AND_MAIDENHEAD_ROW-1);        
      } else {
        lcd.setCursor(LCD_COLUMNS-14,LCD_CONSTANT_HHMMSS_CLOCK_AND_MAIDENHEAD_ROW-1); 
      }
      #ifdef OPTION_CLOCK_ALWAYS_HAVE_HOUR_LEADING_ZERO
      if (clock_hours < 10) {
        strcpy(clock_temp_string, "0");
      }    
      dtostrf(clock_hours, 0, 0, temp_string);
      strcat(clock_temp_string,temp_string);    
      #else          
      dtostrf(clock_hours, 0, 0, temp_string);
      strcpy(clock_temp_string,temp_string);
      #endif //OPTION_CLOCK_ALWAYS_HAVE_HOUR_LEADING_ZERO
      strcat(clock_temp_string,":");
      if (clock_minutes < 10) {
        strcat(clock_temp_string, "0");
      }
      if (clock_hours > 9){
        clock_digits = 1;
      }
      dtostrf(clock_minutes, 0, 0, temp_string);
      strcat(clock_temp_string,temp_string);
      strcat(clock_temp_string,":");
      if (clock_seconds < 10) {
        strcat(clock_temp_string, "0");
      }
      dtostrf(clock_seconds, 0, 0, temp_string);
      strcat(clock_temp_string,temp_string);
      lcd.print(clock_temp_string);
      lcd.print(" ");
      lcd.print(coordinates_to_maidenhead(latitude,longitude));
      last_clock_seconds = clock_seconds;
    }


    last_clock_lcd_row_state = lcd_state_row_0;
  }
  #endif //defined(OPTION_DISPLAY_CONSTANT_HHMMSS_CLOCK_AND_MAIDENHEAD) && defined(FEATURE_CLOCK)
 
  // gps indicator -------------------------------------------------------------------------
  #if defined(OPTION_DISPLAY_GPS_INDICATOR) && defined(FEATURE_GPS) && defined(FEATURE_CLOCK)
  static byte last_clock_status = FREE_RUNNING;
  static byte last_gps_lcd_row_state = 0;

  if ((lcd_state_row_0 != LCD_UNDEF) && ((lcd_state_row_0 == LCD_IDLE_STATUS) || ((LCD_GPS_INDICATOR_ROW-1)!= 0))){
    if ((last_clock_status != clock_status) || ((LCD_GPS_INDICATOR_ROW == 1) && (last_gps_lcd_row_state != lcd_state_row_0))) {
      if (LCD_GPS_INDICATOR_POSITION == LEFT){
        lcd.setCursor(0,LCD_GPS_INDICATOR_ROW-1);
      } else {
        lcd.setCursor(LCD_COLUMNS-3,LCD_GPS_INDICATOR_ROW-1);
      }
      if (clock_status == GPS_SYNC){
        lcd.print(GPS_STRING);
      } else {
        lcd.print("   ");
      }
    }
    last_clock_status = clock_status;
  }
  last_gps_lcd_row_state = lcd_state_row_0;
  #endif //defined(OPTION_DISPLAY_GPS_INDICATOR) && defined(FEATURE_GPS)  && defined(FEATURE_CLOCK)




  #if (defined(OPTION_DISPLAY_MOON_TRACKING_CONTINUOUSLY) && defined(FEATURE_MOON_TRACKING)) || (defined(OPTION_DISPLAY_SUN_TRACKING_CONTINUOUSLY) && defined(FEATURE_SUN_TRACKING)) || defined(OPTION_DISPLAY_MOON_OR_SUN_TRACKING_CONDITIONAL)
  char trackingstring[LCD_COLUMNS+2] = "";
  char temptrackingstring[LCD_COLUMNS+2] = "";
  #endif

  //  moon tracking ----------------------------------------------------------
  #if defined(OPTION_DISPLAY_MOON_TRACKING_CONTINUOUSLY) && defined(FEATURE_MOON_TRACKING)

  static unsigned long last_moon_tracking_check_time = 0;
  static byte last_strlen_moon = 0;

  if ((lcd_state_row_0 != 0) && (lcd_state_row_1 != 0) && ((millis()-last_moon_tracking_check_time) > LCD_MOON_TRACKING_UPDATE_INTERVAL)) {  
    update_moon_position();
    strcpy(trackingstring,"");
    if (moon_tracking_active){
      if (moon_visible){
        strcat(trackingstring,TRACKING_ACTIVE_CHAR);
      } else {
        strcat(trackingstring,"-");
      }
    }
    strcat(trackingstring,MOON_STRING);
    dtostrf(moon_azimuth,0,LCD_DECIMAL_PLACES,temp_string);
    strcat(trackingstring,temp_string);
    if ((LCD_COLUMNS>16) && ((moon_azimuth < 100) || (abs(moon_elevation)<100))) {strcat(trackingstring,"\xDF");}
    strcat(trackingstring," ");
    dtostrf(moon_elevation,0,LCD_DECIMAL_PLACES,temp_string);
    strcat(trackingstring,temp_string);
    if ((LCD_COLUMNS>16) && ((moon_azimuth < 100) || (abs(moon_elevation)<100))) {strcat(trackingstring,"\xDF");}
    if (moon_tracking_active){
      if (moon_visible){
        strcat(trackingstring,TRACKING_ACTIVE_CHAR);
      } else {
        strcat(trackingstring,TRACKING_INACTIVE_CHAR);
      }
    }
    // if (strlen(trackingstring) < last_strlen_moon){
    //   clear_display_row(LCD_MOON_TRACKING_ROW-1);
    // }
    // last_strlen_moon = strlen(trackingstring);
    // lcd.setCursor((LCD_COLUMNS-strlen(trackingstring))/2,LCD_MOON_TRACKING_ROW-1);

    lcd.setCursor(0,LCD_MOON_TRACKING_ROW-1);
    int x = LCD_COLUMNS - strlen(trackingstring);
    byte y = 0;
    while (x > 0){
      if ((y%2) != 0){
        strcpy(temptrackingstring," ");
        strcat(temptrackingstring,trackingstring);
        strcpy(trackingstring,temptrackingstring);
      } else {
        strcat(trackingstring," ");
      }
      y++;
      x--;
    }



    lcd.print(trackingstring);
    last_moon_tracking_check_time = millis();
  }
  #endif //defined(OPTION_DISPLAY_MOON_TRACKING_CONTINUOUSLY) && defined(FEATURE_MOON_TRACKING)


  //  sun tracking ----------------------------------------------------------
  #if defined(OPTION_DISPLAY_SUN_TRACKING_CONTINUOUSLY) && defined(FEATURE_SUN_TRACKING)

  static unsigned long last_sun_tracking_check_time = 0;
  static byte last_strlen_sun = 0;

  if ((lcd_state_row_0 != 0) && (lcd_state_row_1 != 0) && ((millis()-last_sun_tracking_check_time) > LCD_SUN_TRACKING_UPDATE_INTERVAL)) {  
    update_sun_position();
    strcpy(trackingstring,"");
    if (sun_tracking_active){
      if (sun_visible){
        strcat(trackingstring,TRACKING_ACTIVE_CHAR);
      } else {
        strcat(trackingstring,TRACKING_INACTIVE_CHAR);
      }
    }
    strcat(trackingstring,SUN_STRING);
    dtostrf(sun_azimuth,0,LCD_DECIMAL_PLACES,temp_string);
    strcat(trackingstring,temp_string);
    if ((LCD_COLUMNS>16) && ((sun_azimuth < 100) || (abs(sun_elevation)<100))) {strcat(trackingstring,"\xDF");}
    strcat(trackingstring," ");
    dtostrf(sun_elevation,0,LCD_DECIMAL_PLACES,temp_string);
    strcat(trackingstring,temp_string);
    if ((LCD_COLUMNS>16) && ((sun_azimuth < 100) || (abs(sun_elevation)<100))) {strcat(trackingstring,"\xDF");}
    if (sun_tracking_active){
      if (sun_visible){
        strcat(trackingstring,TRACKING_ACTIVE_CHAR);
      } else {
        strcat(trackingstring,TRACKING_INACTIVE_CHAR);
      }
    }
    // if (strlen(trackingstring) < last_strlen_sun){
    //   clear_display_row(LCD_SUN_TRACKING_ROW-1);
    // }
    // last_strlen_sun = strlen(trackingstring);
    // lcd.setCursor((LCD_COLUMNS-strlen(trackingstring))/2,LCD_SUN_TRACKING_ROW-1);

    lcd.setCursor(0,LCD_SUN_TRACKING_ROW-1);
    int x = LCD_COLUMNS - strlen(trackingstring);
    byte y = 0;
    while (x > 0){
      if ((y%2) != 0){
        strcpy(temptrackingstring," ");
        strcat(temptrackingstring,trackingstring);
        strcpy(trackingstring,temptrackingstring);
      } else {
        strcat(trackingstring," ");
      }
      y++;
      x--;
    }



    lcd.print(trackingstring);
    last_sun_tracking_check_time = millis();
  }
  #endif //defined(OPTION_DISPLAY_SUN_TRACKING_CONTINUOUSLY) && defined(FEATURE_SUN_TRACKING)






  // moon and/or sun tracking conditional ------------------------------------------------------------------------
  #ifdef OPTION_DISPLAY_MOON_OR_SUN_TRACKING_CONDITIONAL

  //  moon tracking ----
  #if defined(FEATURE_MOON_TRACKING)

  static unsigned long last_moon_tracking_check_time = 0;
  static byte last_strlen_moon = 0;
  static byte last_moon_tracking_state = 0;

  if ((lcd_state_row_0 != 0) && (lcd_state_row_1 != 0) && ((millis()-last_moon_tracking_check_time) > LCD_MOON_TRACKING_UPDATE_INTERVAL) && moon_tracking_active) {  
    update_moon_position();
    strcpy(trackingstring,"");
    strcat(trackingstring,MOON_STRING);
    dtostrf(moon_azimuth,0,LCD_DECIMAL_PLACES,temp_string);
    strcat(trackingstring,temp_string);
    if ((LCD_COLUMNS>16) && ((moon_azimuth < 100) || (abs(moon_elevation)<100))) {strcat(trackingstring,"\xDF");}
    strcat(trackingstring," ");
    dtostrf(moon_elevation,0,LCD_DECIMAL_PLACES,temp_string);
    strcat(trackingstring,temp_string);
    if ((LCD_COLUMNS>16) && ((moon_azimuth < 100) || (abs(moon_elevation)<100))) {strcat(trackingstring,"\xDF");}
    if (strlen(trackingstring) < last_strlen_moon){
      clear_display_row(LCD_MOON_OR_SUN_TRACKING_CONDITIONAL_ROW-1);
    }
    last_strlen_moon = strlen(trackingstring);
    lcd.setCursor((LCD_COLUMNS-strlen(trackingstring))/2,LCD_MOON_OR_SUN_TRACKING_CONDITIONAL_ROW-1);
    lcd.print(trackingstring);
    last_moon_tracking_check_time = millis();
    last_moon_tracking_state = 1;
  }

  if (!moon_tracking_active && last_moon_tracking_state){
    clear_display_row(LCD_MOON_OR_SUN_TRACKING_CONDITIONAL_ROW-1);
    last_moon_tracking_state = 0;
  }

  #endif //defined(OPTION_DISPLAY_MOON_TRACKING_CONTINUOUSLY) && defined(FEATURE_MOON_TRACKING)


  //  sun tracking ----------------------------------------------------------
  #if defined(FEATURE_SUN_TRACKING)

  static unsigned long last_sun_tracking_check_time = 0;
  static byte last_strlen_sun = 0;
  static byte last_sun_tracking_state = 0;

  if ((lcd_state_row_0 != 0) && (lcd_state_row_1 != 0) && ((millis()-last_sun_tracking_check_time) > LCD_SUN_TRACKING_UPDATE_INTERVAL) && sun_tracking_active) {  
    update_sun_position();
    strcpy(trackingstring,"");
    strcat(trackingstring,SUN_STRING);
    dtostrf(sun_azimuth,0,LCD_DECIMAL_PLACES,temp_string);
    strcat(trackingstring,temp_string);
    if ((LCD_COLUMNS>16) && ((sun_azimuth < 100) || (abs(sun_elevation)<100))) {strcat(trackingstring,"\xDF");}
    strcat(trackingstring," ");
    dtostrf(sun_elevation,0,LCD_DECIMAL_PLACES,temp_string);
    strcat(trackingstring,temp_string);
    if ((LCD_COLUMNS>16) && ((sun_azimuth < 100) || (abs(sun_elevation)<100))) {strcat(trackingstring,"\xDF");}
    if (strlen(trackingstring) < last_strlen_sun){
      clear_display_row(LCD_MOON_OR_SUN_TRACKING_CONDITIONAL_ROW-1);
    }
    last_strlen_sun = strlen(trackingstring);
    lcd.setCursor((LCD_COLUMNS-strlen(trackingstring))/2,LCD_MOON_OR_SUN_TRACKING_CONDITIONAL_ROW-1);
    lcd.print(trackingstring);
    last_sun_tracking_check_time = millis();
    last_sun_tracking_state = 1;
  }
  

  if (!sun_tracking_active && last_sun_tracking_state){
    clear_display_row(LCD_MOON_OR_SUN_TRACKING_CONDITIONAL_ROW-1);
    last_sun_tracking_state = 0;
  }  

  #endif //defined(FEATURE_SUN_TRACKING)

  #endif //OPTION_DISPLAY_MOON_OR_SUN_TRACKING_CONDITIONAL

  // end of moon and/or sun conditional -----

  if ((millis() - last_lcd_update) > LCD_UPDATE_TIME) {
    last_lcd_update = millis();
  }

  last_row_0_string = row_0_string;






  // clock display --- big clock ---------------------------------------------------------
  /* this is outside the normal LCD refresh timing so the seconds update as soon as possible */
  #if defined(OPTION_DISPLAY_BIG_CLOCK) && defined(FEATURE_CLOCK)
  
  char clock_big_temp_string[22] = "";
  static byte last_clock_big_seconds = 0;
  static byte last_clock_big_minutes = 0;
  static byte printed_z = 0;


  update_time();
  if ((last_clock_big_seconds != clock_seconds) && (lcd_state_row_0 != 0) && (lcd_state_row_1 != 0)){
    sprintf(clock_big_temp_string, "%s", clock_string()); 
    //clock_big_temp_string[20] 
    if (last_clock_big_minutes == clock_minutes){  // if the minutes didn't change, don't send the whole string to the LCD
      
      if ((int(float(last_clock_big_seconds)/10.0)) != (int(float(clock_seconds)/10.0))){   
        lcd.setCursor(((LCD_COLUMNS-20)/2)+17,LCD_BIG_CLOCK_ROW-1);
        lcd.print(clock_big_temp_string[17]);
      } else {
        lcd.setCursor(((LCD_COLUMNS-20)/2)+18,LCD_BIG_CLOCK_ROW-1);
      }
      lcd.print(clock_big_temp_string[18]);
      last_clock_big_seconds = clock_seconds;



    } else {  // print the whole clock
      lcd.setCursor((LCD_COLUMNS-20)/2,LCD_BIG_CLOCK_ROW-1);
      if (!printed_z){clock_big_temp_string[20] = 0;}  // I put this in to fix mysterious characters that appear at 0,0 for no reason
      lcd.print(clock_big_temp_string);
      last_clock_big_seconds = clock_seconds;
      last_clock_big_minutes = clock_minutes;
      printed_z = 1;
    }
  }
  #endif //defined(OPTION_DISPLAY_BIG_CLOCK) && defined(FEATURE_CLOCK)
  // end clock display --- big clock ---------------------------------------------------------



} /* update_display */
#endif /* ifdef FEATURE_LCD_DISPLAY */


// --------------------------------------------------------------
#ifdef FEATURE_LCD_DISPLAY
void clear_display_row(byte row_number){
  lcd.setCursor(0, row_number);
  for (byte x = 0; x < LCD_COLUMNS; x++) {
    lcd.print(" ");
  }
}
#endif

// --------------------------------------------------------------
#if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)
void get_keystroke(){
  while (control_port->available() == 0) {
  }
  while (control_port->available() > 0)
    incoming_serial_byte = control_port->read();
}
#endif // defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)

// --------------------------------------------------------------
#ifdef FEATURE_YAESU_EMULATION
void print_wrote_to_memory(){

  control_port->println(F("Wrote to memory"));

}

#endif // FEATURE_YAESU_EMULATION
// --------------------------------------------------------------
#ifdef FEATURE_YAESU_EMULATION
void clear_serial_buffer(){

  delay(200);
  while (control_port->available()) incoming_serial_byte = control_port->read();
}

#endif // FEATURE_YAESU_EMULATION
// --------------------------------------------------------------


void read_settings_from_eeprom(){

  byte * p = (byte *)(void *)&configuration;
  unsigned int i;
  int ee = 0;

  for (i = 0; i < sizeof(configuration); i++) {
    *p++ = EEPROM.read(ee++);
  }

  if (configuration.magic_number == EEPROM_MAGIC_NUMBER) {
    #ifdef DEBUG_EEPROM
    if (debug_mode) {
      debug_println("read_settings_from_eeprom: reading settings from eeprom: ");
      debug_print("\nanalog_az_full_ccw");
      debug_print_int(configuration.analog_az_full_ccw);
      debug_print("\nanalog_az_full_cw");
      debug_print_int(configuration.analog_az_full_cw);
      debug_print("\nanalog_el_0_degrees");
      debug_print_int(configuration.analog_el_0_degrees);
      debug_print("\nanalog_el_max_elevation");
      debug_print_int(configuration.analog_el_max_elevation);
      debug_print("\nlast_azimuth:");
      debug_print_float(configuration.last_azimuth, 1);
      debug_print("\nlast_elevation:");
      debug_print_float(configuration.last_elevation, 1);
      debug_print("\nlast_az_incremental_encoder_position:");
      debug_print_int(configuration.last_az_incremental_encoder_position);
      debug_print("\nlast_el_incremental_encoder_position:");
      debug_print_int(configuration.last_el_incremental_encoder_position);
      debug_print("\naz_offset:");
      debug_print_float(configuration.azimuth_offset,2);
      debug_print("\nel_offset:");
      debug_print_float(configuration.elevation_offset,2);
      debug_println("");
    }
    #endif // DEBUG_EEPROM


    #if defined(FEATURE_AZ_POSITION_INCREMENTAL_ENCODER)
    az_incremental_encoder_position = configuration.last_az_incremental_encoder_position;
    #endif

    #if defined(FEATURE_ELEVATION_CONTROL) && defined(FEATURE_EL_POSITION_INCREMENTAL_ENCODER)
    el_incremental_encoder_position = configuration.last_el_incremental_encoder_position;
    #endif


    #if defined(FEATURE_AZ_POSITION_ROTARY_ENCODER)
    raw_azimuth = int(configuration.last_azimuth * HEADING_MULTIPLIER);
    if (raw_azimuth >= (360 * HEADING_MULTIPLIER)) {
      azimuth = raw_azimuth - (360 * HEADING_MULTIPLIER);
    } else {
      azimuth = raw_azimuth;
    }
      #endif // defined(FEATURE_AZ_POSITION_ROTARY_ENCODER)

      #if defined(FEATURE_ELEVATION_CONTROL) && defined(FEATURE_EL_POSITION_ROTARY_ENCODER)
    elevation = int(configuration.last_elevation * HEADING_MULTIPLIER);
      #endif // defined(FEATURE_EL_POSITION_ROTARY_ENCODER)



    #ifdef FEATURE_AZ_POSITION_PULSE_INPUT
    raw_azimuth = int(configuration.last_azimuth * HEADING_MULTIPLIER);
    if (raw_azimuth >= (360 * HEADING_MULTIPLIER)) {
      azimuth = raw_azimuth - (360 * HEADING_MULTIPLIER);
    } else {
      azimuth = raw_azimuth;
    }
    az_position_pulse_input_azimuth = configuration.last_azimuth;
    #endif // FEATURE_AZ_POSITION_PULSE_INPUT

    #if defined(FEATURE_ELEVATION_CONTROL) && defined(FEATURE_EL_POSITION_PULSE_INPUT)
    elevation = int(configuration.last_elevation * HEADING_MULTIPLIER);
    el_position_pulse_input_elevation = configuration.last_elevation;
    #endif // FEATURE_EL_POSITION_PULSE_INPUT

    #if defined(FEATURE_AZ_POSITION_PULSE_INPUT) || defined(FEATURE_AZ_POSITION_ROTARY_ENCODER)
    configuration.azimuth_offset = 0;
    #endif

    #if defined(FEATURE_EL_POSITION_PULSE_INPUT) || defined(FEATURE_EL_POSITION_ROTARY_ENCODER)
    configuration.elevation_offset = 0;
    #endif



  } else {  // initialize eeprom with default values
    #ifdef DEBUG_EEPROM
    debug_println("read_settings_from_eeprom: uninitialized eeprom, calling initialize_eeprom_with_defaults()");
    #endif // DEBUG_EEPROM
    initialize_eeprom_with_defaults();
  }
} /* read_settings_from_eeprom */
// --------------------------------------------------------------
void initialize_eeprom_with_defaults(){

  #ifdef DEBUG_EEPROM
  debug_println("initialize_eeprom_with_defaults: writing eeprom");
  #endif // DEBUG_EEPROM

  configuration.analog_az_full_ccw = ANALOG_AZ_FULL_CCW;
  configuration.analog_az_full_cw = ANALOG_AZ_FULL_CW;
  configuration.analog_el_0_degrees = ANALOG_EL_0_DEGREES;
  configuration.analog_el_max_elevation = ANALOG_EL_MAX_ELEVATION;
  // azimuth_starting_point = AZIMUTH_STARTING_POINT_DEFAULT;
  // azimuth_rotation_capability = AZIMUTH_ROTATION_CAPABILITY_DEFAULT;
  configuration.last_azimuth = raw_azimuth;
  configuration.last_az_incremental_encoder_position = 0;
  configuration.last_el_incremental_encoder_position = 0;
  configuration.azimuth_offset = 0;
  configuration.elevation_offset = 0;
  #ifdef FEATURE_ELEVATION_CONTROL
  configuration.last_elevation = elevation;
  #else
  configuration.last_elevation = 0;
  #endif

  write_settings_to_eeprom();

} /* initialize_eeprom_with_defaults */


// --------------------------------------------------------------
void write_settings_to_eeprom(){
  #ifdef DEBUG_EEPROM
  debug_println("write_settings_to_eeprom: writing settings to eeprom");
  #endif // DEBUG_EEPROM

  configuration.magic_number = EEPROM_MAGIC_NUMBER;

  const byte * p = (const byte *)(const void *)&configuration;
  unsigned int i;
  int ee = 0;
  for (i = 0; i < sizeof(configuration); i++) {
    EEPROM.write(ee++, *p++);
  }

  // EEPROM_writeAnything(0,configuration);
  configuration_dirty = 0;

}

// --------------------------------------------------------------

void az_check_operation_timeout(){

  // check if the last executed rotation operation has been going on too long

  if (((millis() - az_last_rotate_initiation) > OPERATION_TIMEOUT) && (az_state != IDLE)) {
    submit_request(AZ, REQUEST_KILL, 0, 78);
    #ifdef DEBUG_AZ_CHECK_OPERATION_TIMEOUT
    debug_println("az_check_operation_timeout: timeout reached, aborting rotation");
    #endif // DEBUG_AZ_CHECK_OPERATION_TIMEOUT
  }
}

// --------------------------------------------------------------

#ifdef FEATURE_TIMED_BUFFER
void clear_timed_buffer(){
  timed_buffer_status = EMPTY;
  timed_buffer_number_entries_loaded = 0;
  timed_buffer_entry_pointer = 0;
}
#endif // FEATURE_TIMED_BUFFER
// --------------------------------------------------------------
// #ifdef FEATURE_YAESU_EMULATION
// void yaesu_m_command(){

//   int parsed_azimuth = 0;

//   // parse out M command
//   if (control_port_buffer_index > 4) {  // if there are more than 4 characters in the command buffer, we got a timed interval command
//     #ifdef FEATURE_TIMED_BUFFER
//     yaesu_az_load_timed_intervals();
//     #else
//     control_port->println(F("Feature not activated ?>"));
//     #endif // FEATURE_TIMED_BUFFER
//     return;
//   } else {                         // if there are four characters, this is just a single direction setting
//     if (control_port_buffer_index == 4) {
//       parsed_azimuth = ((int(control_port_buffer[1]) - 48) * 100) + ((int(control_port_buffer[2]) - 48) * 10) + (int(control_port_buffer[3]) - 48);
//       #ifdef FEATURE_TIMED_BUFFER
//       clear_timed_buffer();
//       #endif // FEATURE_TIMED_BUFFER
//       if ((parsed_azimuth > -1) && (parsed_azimuth <= (azimuth_starting_point + azimuth_rotation_capability))) {
//         submit_request(AZ, REQUEST_AZIMUTH, (parsed_azimuth * HEADING_MULTIPLIER));
//         return;
//       }
//     }
//   }

//   control_port->println(F("?>"));

// } /* yaesu_m_command */
// #endif // FEATURE_YAESU_EMULATION
// --------------------------------------------------------------

#ifdef FEATURE_TIMED_BUFFER
void initiate_timed_buffer(byte source_port){
  if (timed_buffer_status == LOADED_AZIMUTHS) {
    timed_buffer_status = RUNNING_AZIMUTHS;
    submit_request(AZ, REQUEST_AZIMUTH, timed_buffer_azimuths[1], 79);
    last_timed_buffer_action_time = millis();
    timed_buffer_entry_pointer = 2;
    #ifdef DEBUG_TIMED_BUFFER
    debug_println("initiate_timed_buffer: changing state to RUNNING_AZIMUTHS");
    #endif // DEBUG_TIMED_BUFFER
  } else {
    #ifdef FEATURE_ELEVATION_CONTROL
    if (timed_buffer_status == LOADED_AZIMUTHS_ELEVATIONS) {
      timed_buffer_status = RUNNING_AZIMUTHS_ELEVATIONS;
      submit_request(AZ, REQUEST_AZIMUTH, timed_buffer_azimuths[1], 80);
      submit_request(EL, REQUEST_ELEVATION, timed_buffer_elevations[1], 81);
      last_timed_buffer_action_time = millis();
      timed_buffer_entry_pointer = 2;
      #ifdef DEBUG_TIMED_BUFFER
      debug_println("initiate_timed_buffer: changing state to RUNNING_AZIMUTHS_ELEVATIONS");
      #endif // DEBUG_TIMED_BUFFER
    } else {
      print_to_port(">",source_port);  // error
    }
    #endif
  }

} /* initiate_timed_buffer */
#endif // FEATURE_TIMED_BUFFER
// --------------------------------------------------------------
#ifdef FEATURE_TIMED_BUFFER
void print_timed_buffer_empty_message(){

  #ifdef DEBUG_TIMED_BUFFER
  debug_println("check_timed_interval: completed timed buffer; changing state to EMPTY");
  #endif // DEBUG_TIMED_BUFFER

}

#endif // FEATURE_TIMED_BUFFER
// --------------------------------------------------------------
#ifdef FEATURE_TIMED_BUFFER
void check_timed_interval(){

  if ((timed_buffer_status == RUNNING_AZIMUTHS) && (((millis() - last_timed_buffer_action_time) / 1000) > timed_buffer_interval_value_seconds)) {
    timed_buffer_entry_pointer++;
    #ifdef DEBUG_TIMED_BUFFER
    debug_println("check_timed_interval: executing next timed interval step - azimuths");
    #endif // DEBUG_TIMED_BUFFER
    submit_request(AZ, REQUEST_AZIMUTH, timed_buffer_azimuths[timed_buffer_entry_pointer - 1], 82);
    last_timed_buffer_action_time = millis();
    if (timed_buffer_entry_pointer == timed_buffer_number_entries_loaded) {
      clear_timed_buffer();
      print_timed_buffer_empty_message();
    }
  }
  #ifdef FEATURE_ELEVATION_CONTROL
  if ((timed_buffer_status == RUNNING_AZIMUTHS_ELEVATIONS) && (((millis() - last_timed_buffer_action_time) / 1000) > timed_buffer_interval_value_seconds)) {
    timed_buffer_entry_pointer++;
    #ifdef DEBUG_TIMED_BUFFER
    debug_println("check_timed_interval: executing next timed interval step - az and el");
    #endif // DEBUG_TIMED_BUFFER
    submit_request(AZ, REQUEST_AZIMUTH, timed_buffer_azimuths[timed_buffer_entry_pointer - 1], 83);
    submit_request(EL, REQUEST_ELEVATION, timed_buffer_elevations[timed_buffer_entry_pointer - 1], 84);
    last_timed_buffer_action_time = millis();
    if (timed_buffer_entry_pointer == timed_buffer_number_entries_loaded) {
      clear_timed_buffer();
      print_timed_buffer_empty_message();

    }
  }
  #endif
} /* check_timed_interval */
#endif // FEATURE_TIMED_BUFFER


// --------------------------------------------------------------

void read_azimuth(byte force_read){


  unsigned int previous_raw_azimuth = raw_azimuth;
  static unsigned long last_measurement_time = 0;

  #ifdef FEATURE_AZ_POSITION_INCREMENTAL_ENCODER
  static unsigned int incremental_encoder_previous_raw_azimuth = raw_azimuth;
  #endif // FEATURE_AZ_POSITION_INCREMENTAL_ENCODER

  if (heading_reading_inhibit_pin) {
    if (digitalReadEnhanced(heading_reading_inhibit_pin)) {
      return;
    }
  }

  #ifdef DEBUG_HEADING_READING_TIME
  static unsigned long last_time = 0;
  static unsigned long last_print_time = 0;
  static float average_read_time = 0;
  #endif // DEBUG_HEADING_READING_TIME

  #ifdef DEBUG_HH12
  static unsigned long last_hh12_debug = 0;
  #endif

  #ifndef FEATURE_AZ_POSITION_GET_FROM_REMOTE_UNIT
  if (((millis() - last_measurement_time) > AZIMUTH_MEASUREMENT_FREQUENCY_MS) || (force_read)) {
  #else
  if (1) {
  #endif

    #ifdef FEATURE_AZ_POSITION_POTENTIOMETER
    analog_az = analogReadEnhanced(rotator_analog_az);
    raw_azimuth = map(analog_az, configuration.analog_az_full_ccw, configuration.analog_az_full_cw, (azimuth_starting_point * HEADING_MULTIPLIER), ((azimuth_starting_point + azimuth_rotation_capability) * HEADING_MULTIPLIER));
    //raw_azimuth = map(analog_az* HEADING_MULTIPLIER, configuration.analog_az_full_ccw* HEADING_MULTIPLIER, configuration.analog_az_full_cw* HEADING_MULTIPLIER, (azimuth_starting_point * HEADING_MULTIPLIER), ((azimuth_starting_point + azimuth_rotation_capability) * HEADING_MULTIPLIER));

    #ifdef FEATURE_AZIMUTH_CORRECTION
    raw_azimuth = (correct_azimuth(raw_azimuth / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
    #endif // FEATURE_AZIMUTH_CORRECTION
    raw_azimuth = raw_azimuth + (configuration.azimuth_offset * HEADING_MULTIPLIER);
    if (AZIMUTH_SMOOTHING_FACTOR > 0) {
      raw_azimuth = (raw_azimuth * (1 - (AZIMUTH_SMOOTHING_FACTOR / 100.))) + (previous_raw_azimuth * (AZIMUTH_SMOOTHING_FACTOR / 100.));
    }
    if (raw_azimuth >= (360 * HEADING_MULTIPLIER)) {
      azimuth = raw_azimuth - (360 * HEADING_MULTIPLIER);
      if (azimuth >= (360 * HEADING_MULTIPLIER)) {
        azimuth = azimuth - (360 * HEADING_MULTIPLIER);
      }
    } else {
      if (raw_azimuth < 0) {
        azimuth = raw_azimuth + (360 * HEADING_MULTIPLIER);
      } else {
        azimuth = raw_azimuth;
      }
    }
    #endif // FEATURE_AZ_POSITION_POTENTIOMETER

    #ifdef FEATURE_AZ_POSITION_GET_FROM_REMOTE_UNIT
    #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
    static unsigned long last_remote_unit_az_query_time = 0;
    // do we have a command result waiting for us?
    if (remote_unit_command_results_available == REMOTE_UNIT_AZ_COMMAND) {

      #ifdef DEBUG_HEADING_READING_TIME
      average_read_time = (average_read_time + (millis() - last_time)) / 2.0;
      last_time = millis();

      if (debug_mode) {
        if ((millis() - last_print_time) > 1000) {
          debug_println("read_azimuth: avg read frequency: ");
          debug_print_float(average_read_time, 2);
          debug_println("");
          last_print_time = millis();
        }
      }
      #endif // DEBUG_HEADING_READING_TIME
      raw_azimuth = remote_unit_command_result_float * HEADING_MULTIPLIER;


      #ifdef FEATURE_AZIMUTH_CORRECTION
      raw_azimuth = (correct_azimuth(raw_azimuth / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
      #endif // FEATURE_AZIMUTH_CORRECTION

      raw_azimuth = raw_azimuth + (configuration.azimuth_offset * HEADING_MULTIPLIER);

      if (AZIMUTH_SMOOTHING_FACTOR > 0) {
        raw_azimuth = (raw_azimuth * (1 - (AZIMUTH_SMOOTHING_FACTOR / 100))) + (previous_raw_azimuth * (AZIMUTH_SMOOTHING_FACTOR / 100));
      }
      if (raw_azimuth >= (360 * HEADING_MULTIPLIER)) {
        azimuth = raw_azimuth - (360 * HEADING_MULTIPLIER);
        if (azimuth >= (360 * HEADING_MULTIPLIER)) {
          azimuth = azimuth - (360 * HEADING_MULTIPLIER);
        }
      } else {
        if (raw_azimuth < 0) {
          azimuth = raw_azimuth + (360 * HEADING_MULTIPLIER);
        } else {
          azimuth = raw_azimuth;
        }
      }
      remote_unit_command_results_available = 0;
    } else {
      // is it time to request the azimuth?
      if ((millis() - last_remote_unit_az_query_time) > AZ_REMOTE_UNIT_QUERY_TIME_MS) {
        if (submit_remote_command(REMOTE_UNIT_AZ_COMMAND, 0, 0)) {
          last_remote_unit_az_query_time = millis();
        }
      }
    }
    #endif // defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
    #endif // FEATURE_AZ_POSITION_GET_FROM_REMOTE_UNIT



    #ifdef FEATURE_AZ_POSITION_ROTARY_ENCODER
    static byte az_position_encoder_state = 0;
    az_position_encoder_state = ttable[az_position_encoder_state & 0xf][((digitalReadEnhanced(az_rotary_position_pin2) << 1) | digitalReadEnhanced(az_rotary_position_pin1))];
    byte az_position_encoder_result = az_position_encoder_state & 0x30;
    if (az_position_encoder_result) {
      if (az_position_encoder_result == DIR_CW) {
        configuration.last_azimuth = configuration.last_azimuth + AZ_POSITION_ROTARY_ENCODER_DEG_PER_PULSE;
        #ifdef DEBUG_POSITION_ROTARY_ENCODER
        debug_println("read_azimuth: AZ_POSITION_ROTARY_ENCODER: CW");
        #endif // DEBUG_POSITION_ROTARY_ENCODER
      }
      if (az_position_encoder_result == DIR_CCW) {
        configuration.last_azimuth = configuration.last_azimuth - AZ_POSITION_ROTARY_ENCODER_DEG_PER_PULSE;
        #ifdef DEBUG_POSITION_ROTARY_ENCODER
        debug_println("read_azimuth: AZ_POSITION_ROTARY_ENCODER: CCW");
        #endif // DEBUG_POSITION_ROTARY_ENCODER
      }

      #ifdef OPTION_AZ_POSITION_ROTARY_ENCODER_HARD_LIMIT
      if (configuration.last_azimuth < azimuth_starting_point) {
        configuration.last_azimuth = azimuth_starting_point;
      }
      if (configuration.last_azimuth > (azimuth_starting_point + azimuth_rotation_capability)) {
        configuration.last_azimuth = (azimuth_starting_point + azimuth_rotation_capability);
      }
      #else
      if (configuration.last_azimuth < 0) {
        configuration.last_azimuth += 360;
      }
      if (configuration.last_azimuth >= 360) {
        configuration.last_azimuth -= 360;
      }
      #endif // OPTION_AZ_POSITION_ROTARY_ENCODER_HARD_LIMIT


      raw_azimuth = int(configuration.last_azimuth * HEADING_MULTIPLIER);


      #ifdef FEATURE_AZIMUTH_CORRECTION
      raw_azimuth = (correct_azimuth(raw_azimuth / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
      #endif // FEATURE_AZIMUTH_CORRECTION

      if (raw_azimuth >= (360 * HEADING_MULTIPLIER)) {
        azimuth = raw_azimuth - (360 * HEADING_MULTIPLIER);
      } else {
        azimuth = raw_azimuth;
      }
      configuration_dirty = 1;
    }
    #endif // FEATURE_AZ_POSITION_ROTARY_ENCODER

    #ifdef FEATURE_AZ_POSITION_HMC5883L
    MagnetometerScaled scaled = compass.ReadScaledAxis(); // scaled values from compass.

    #ifdef DEBUG_HMC5883L
    debug_print("read_azimuth: HMC5883L x:");
    debug_print_float(scaled.XAxis,4);
    debug_print(" y:");
    debug_print_float(scaled.YAxis,4);
    debug_println("");
    #endif //DEBUG_HMC5883L


    float heading = atan2(scaled.YAxis, scaled.XAxis);
    //  heading += declinationAngle;
    // Correct for when signs are reversed.
    if (heading < 0) heading += 2 * PI;
    if (heading > 2 * PI) heading -= 2 * PI;
    raw_azimuth = (heading * RAD_TO_DEG) * HEADING_MULTIPLIER; // radians to degree
    if (AZIMUTH_SMOOTHING_FACTOR > 0) {
      raw_azimuth = (raw_azimuth * (1 - (AZIMUTH_SMOOTHING_FACTOR / 100))) + (previous_raw_azimuth * (AZIMUTH_SMOOTHING_FACTOR / 100));
    }
    #ifdef FEATURE_AZIMUTH_CORRECTION
    raw_azimuth = (correct_azimuth(raw_azimuth / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
    #endif // FEATURE_AZIMUTH_CORRECTION
    raw_azimuth = raw_azimuth + (configuration.azimuth_offset * HEADING_MULTIPLIER);
    azimuth = raw_azimuth;
    #endif // FEATURE_AZ_POSITION_HMC5883L





    #ifdef FEATURE_AZ_POSITION_ADAFRUIT_LSM303
    lsm.read();
    float heading = atan2(lsm.magData.y, lsm.magData.x);
    //  heading += declinationAngle;
    // Correct for when signs are reversed.
    if (heading < 0) heading += 2 * PI;
    if (heading > 2 * PI) heading -= 2 * PI;
    raw_azimuth = (heading * RAD_TO_DEG) * HEADING_MULTIPLIER; // radians to degree
    #ifdef FEATURE_AZIMUTH_CORRECTION
    raw_azimuth = (correct_azimuth(raw_azimuth / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
    #endif // FEATURE_AZIMUTH_CORRECTION
    raw_azimuth = raw_azimuth + (configuration.azimuth_offset * HEADING_MULTIPLIER);
    if (AZIMUTH_SMOOTHING_FACTOR > 0) {
      raw_azimuth = (raw_azimuth * (1 - (AZIMUTH_SMOOTHING_FACTOR / 100))) + (previous_raw_azimuth * (AZIMUTH_SMOOTHING_FACTOR / 100));
    }
    azimuth = raw_azimuth;
    #endif // FEATURE_AZ_POSITION_ADAFRUIT_LSM303




    #ifdef FEATURE_AZ_POSITION_PULSE_INPUT
    #ifdef DEBUG_POSITION_PULSE_INPUT
//    if (az_position_pule_interrupt_handler_flag) {
//      control_port->print(F("read_azimuth: az_position_pusle_interrupt_handler_flag: "));
//      control_port->println(az_position_pule_interrupt_handler_flag);
//      az_position_pule_interrupt_handler_flag = 0;
//    }
    #endif // DEBUG_POSITION_PULSE_INPUT
    static float last_az_position_pulse_input_azimuth = az_position_pulse_input_azimuth;
    if (az_position_pulse_input_azimuth != last_az_position_pulse_input_azimuth) {
      #ifdef DEBUG_POSITION_PULSE_INPUT
//        if (debug_mode){
//          control_port->print(F("read_azimuth: last_az_position_pulse_input_azimuth:"));
//          control_port->print(last_az_position_pulse_input_azimuth);
//          control_port->print(F(" az_position_pulse_input_azimuth:"));
//          control_port->print(az_position_pulse_input_azimuth);
//          control_port->print(F(" az_pulse_counter:"));
//          control_port->println(az_pulse_counter);
//        }
      #endif // DEBUG_POSITION_PULSE_INPUT
      configuration.last_azimuth = az_position_pulse_input_azimuth;
      configuration_dirty = 1;
      last_az_position_pulse_input_azimuth = az_position_pulse_input_azimuth;
      raw_azimuth = int(configuration.last_azimuth * HEADING_MULTIPLIER);
      #ifdef FEATURE_AZIMUTH_CORRECTION
      raw_azimuth = (correct_azimuth(raw_azimuth / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
      #endif // FEATURE_AZIMUTH_CORRECTION
      raw_azimuth = raw_azimuth + (configuration.azimuth_offset * HEADING_MULTIPLIER);
      if (raw_azimuth >= (360 * HEADING_MULTIPLIER)) {
        azimuth = raw_azimuth - (360 * HEADING_MULTIPLIER);
      } else {
        azimuth = raw_azimuth;
      }
    }
    #endif // FEATURE_AZ_POSITION_PULSE_INPUT

    #ifdef FEATURE_AZ_POSITION_HH12_AS5045_SSI
    raw_azimuth = int(azimuth_hh12.heading() * HEADING_MULTIPLIER);
    #ifdef DEBUG_HH12
    if ((millis() - last_hh12_debug) > 5000) {
      control_port->print(F("read_azimuth: HH-12 raw: "));
      control_port->println(raw_azimuth);
      last_hh12_debug = millis();
    }
    #endif // DEBUG_HH12
    #ifdef FEATURE_AZIMUTH_CORRECTION
    raw_azimuth = (correct_azimuth(raw_azimuth / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
    #endif // FEATURE_AZIMUTH_CORRECTION
    raw_azimuth = raw_azimuth + (configuration.azimuth_offset * HEADING_MULTIPLIER);
    azimuth = raw_azimuth;
    #endif // FEATURE_AZ_POSITION_HH12_AS5045_SSI

    #ifdef FEATURE_AZ_POSITION_INCREMENTAL_ENCODER
    if (AZIMUTH_STARTING_POINT_DEFAULT == 0) {
      raw_azimuth = (((((az_incremental_encoder_position) / (AZ_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.)) * 360.0)) * HEADING_MULTIPLIER);
    } else {
      if (az_incremental_encoder_position > (AZ_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.)) {
        raw_azimuth = (((((az_incremental_encoder_position - (AZ_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.)) / (AZ_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.)) * 360.0)) * HEADING_MULTIPLIER);
      } else {
        raw_azimuth = (((((az_incremental_encoder_position + (AZ_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.)) / (AZ_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.)) * 360.0)) * HEADING_MULTIPLIER);
      }
    }
    #ifdef FEATURE_AZIMUTH_CORRECTION
    raw_azimuth = (correct_azimuth(raw_azimuth / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
    #endif // FEATURE_AZIMUTH_CORRECTION
    raw_azimuth = raw_azimuth + (configuration.azimuth_offset * HEADING_MULTIPLIER);
    if (raw_azimuth >= (360 * HEADING_MULTIPLIER)) {
      azimuth = raw_azimuth - (360 * HEADING_MULTIPLIER);
    } else {
      azimuth = raw_azimuth;
    }
    if (raw_azimuth != incremental_encoder_previous_raw_azimuth) {
      configuration.last_az_incremental_encoder_position = az_incremental_encoder_position;
      configuration_dirty = 1;
      incremental_encoder_previous_raw_azimuth = raw_azimuth;
    }
    #endif // FEATURE_AZ_POSITION_INCREMENTAL_ENCODER




    last_measurement_time = millis();
  }


} /* read_azimuth */

// --------------------------------------------------------------

void output_debug(){

  #ifdef DEBUG_DUMP

  char tempstring[32] = "";

  #if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)

  if (((millis() - last_debug_output_time) >= 3000) && (debug_mode)) {

    #ifdef DEBUG_GPS_SERIAL
    debug_println("");
    #endif //DEBUG_GPS_SERIAL

    //port_flush();

    debug_print("debug: \t");
    debug_print(CODE_VERSION);
    debug_print("\t\t");

    #ifdef FEATURE_CLOCK
    update_time();
    sprintf(tempstring, "%s", clock_string());
    debug_print(tempstring);
    #else // FEATURE_CLOCK
    dtostrf((millis() / 1000),0,0,tempstring);
    debug_print(tempstring);
    #endif // FEATURE_CLOCK

    #if defined(FEATURE_GPS) || defined(FEATURE_RTC) || (defined(FEATURE_CLOCK) && defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE))
    debug_print("\t");
    debug_print(clock_status_string());
    #endif // defined(FEATURE_GPS) || defined(FEATURE_RTC) || (defined(FEATURE_CLOCK) && defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE))

    #if defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)
    debug_print("\t");
    sprintf(tempstring, "%s", coordinate_string());
    debug_print(tempstring); 
    debug_print(" ");
    debug_print(coordinates_to_maidenhead(latitude,longitude));
    #endif

    debug_print("\t\t");
    #ifdef DEBUG_MEMORY
    void * HP = malloc(4);
    if (HP) {free(HP);}
    unsigned long free = (unsigned long)SP - (unsigned long)HP;
    sprintf(tempstring,"%lu",(unsigned long)free);
    debug_print(tempstring);
    debug_print("b free");
    #endif //DEBUG_MEMORY

    #ifdef FEATURE_YAESU_EMULATION
    debug_print("\t\tGS-232");
    #ifdef OPTION_GS_232B_EMULATION
    debug_print("B");
    #else
    debug_print("A");
    #endif
    #endif // FEATURE_YAESU_EMULATION

    #ifdef FEATURE_PARK
    switch (park_status) {
      case NOT_PARKED: debug_print("\tNOT_PARKED"); break;
      case PARK_INITIATED: debug_print("\tPARK_INITIATED"); break;
      case PARKED: debug_print("\tPARKED"); break;
    }
    #endif // FEATURE_PARK


    debug_print("\n");

    debug_print("\tAZ: ");
    switch (az_state) {
      case IDLE: debug_print("IDLE"); break;
      #ifndef HARDWARE_EA4TX_ARS_USB
      case SLOW_START_CW: debug_print("SLOW_START_CW"); break;
      case SLOW_START_CCW: debug_print("SLOW_START_CCW"); break;
      #endif //ifndef HARDWARE_EA4TX_ARS_USB
      case NORMAL_CW: debug_print("NORMAL_CW"); break;
      case NORMAL_CCW: debug_print("NORMAL_CCW"); break;
      #ifndef HARDWARE_EA4TX_ARS_USB
      case SLOW_DOWN_CW: debug_print("SLOW_DOWN_CW"); break;
      case SLOW_DOWN_CCW: debug_print("SLOW_DOWN_CCW"); break;
      case INITIALIZE_SLOW_START_CW: debug_print("INITIALIZE_SLOW_START_CW"); break;
      case INITIALIZE_SLOW_START_CCW: debug_print("INITIALIZE_SLOW_START_CCW"); break;
      case INITIALIZE_TIMED_SLOW_DOWN_CW: debug_print("INITIALIZE_TIMED_SLOW_DOWN_CW"); break;
      case INITIALIZE_TIMED_SLOW_DOWN_CCW: debug_print("INITIALIZE_TIMED_SLOW_DOWN_CCW"); break;
      case TIMED_SLOW_DOWN_CW: debug_print("TIMED_SLOW_DOWN_CW"); break;
      case TIMED_SLOW_DOWN_CCW: debug_print("TIMED_SLOW_DOWN_CCW"); break;
      case INITIALIZE_DIR_CHANGE_TO_CW: debug_print("INITIALIZE_DIR_CHANGE_TO_CW"); break;
      case INITIALIZE_DIR_CHANGE_TO_CCW: debug_print("INITIALIZE_DIR_CHANGE_TO_CCW"); break;
      case INITIALIZE_NORMAL_CW: debug_print("INITIALIZE_NORMAL_CW"); break;
      case INITIALIZE_NORMAL_CCW: debug_print("INITIALIZE_NORMAL_CCW"); break; 
      #endif //ifndef HARDWARE_EA4TX_ARS_USB     
    }

    debug_print("\tQ: ");
    switch (az_request_queue_state) {
      case NONE: debug_print("-"); break;
      case IN_QUEUE: debug_print("IN_QUEUE"); break;
      case IN_PROGRESS_TIMED: debug_print("IN_PROGRESS_TIMED"); break;
      case IN_PROGRESS_TO_TARGET: debug_print("IN_PROGRESS_TO_TARGET"); break;
    }

    debug_print(" AZ: ");
    debug_print_float((azimuth / LCD_HEADING_MULTIPLIER), LCD_DECIMAL_PLACES);
    debug_print(" (raw: ");
    debug_print_float((raw_azimuth / LCD_HEADING_MULTIPLIER), LCD_DECIMAL_PLACES);
    debug_print(")");


    if (az_state != IDLE) {
      debug_print("  Target: ");
      debug_print_float((target_azimuth / LCD_HEADING_MULTIPLIER), LCD_DECIMAL_PLACES);
   

      debug_print(" (raw: ");

      debug_print_float((target_raw_azimuth / LCD_HEADING_MULTIPLIER), LCD_DECIMAL_PLACES);
      debug_print(")");

      debug_print("  Secs_left: ");
      debug_print_int((OPERATION_TIMEOUT - (millis() - az_last_rotate_initiation)) / 1000);
    }

    #ifdef FEATURE_AZ_POSITION_POTENTIOMETER
    debug_print("  Analog: ");
    dtostrf(analog_az,0,0,tempstring);
    debug_print(tempstring);
    debug_print(" (");
    dtostrf(configuration.analog_az_full_ccw,0,0,tempstring);
    debug_print(tempstring);
    debug_print("-");
    dtostrf(configuration.analog_az_full_cw,0,0,tempstring);
    debug_print(tempstring);
    debug_print(") ");
    #endif // FEATURE_AZ_POSITION_POTENTIOMETER

    debug_print("\t[");
    debug_print_int(azimuth_starting_point);
    debug_print("+");
    debug_print_int(azimuth_rotation_capability);
    debug_print("]");

    #ifndef HARDWARE_EA4TX_ARS_USB
    debug_print("  AZ Speed Norm: ");
    debug_print_int(normal_az_speed_voltage);

    debug_print(" Current: ");
    debug_print_int(current_az_speed_voltage);


    if (az_speed_pot) {
      debug_print("  AZ Speed Pot: ");
      debug_print_int(analogReadEnhanced(az_speed_pot));
    }
    if (az_preset_pot) {
      debug_print(" AZ Preset Pot Analog: ");
      debug_print_int(analogReadEnhanced(az_preset_pot));
      debug_print("  AZ Preset Pot Setting: ");
      dtostrf((map(analogReadEnhanced(az_preset_pot), AZ_PRESET_POT_FULL_CW, AZ_PRESET_POT_FULL_CCW, AZ_PRESET_POT_FULL_CW_MAP, AZ_PRESET_POT_FULL_CCW_MAP)),0,0,tempstring);
      debug_print(tempstring);
    }

    debug_print("\tOffset: ");
    dtostrf(configuration.azimuth_offset,0,2,tempstring);
    debug_print(tempstring);
    #endif // ndef HARDWARE_EA4TX_ARS_USB
    debug_println("");


    #ifdef FEATURE_ELEVATION_CONTROL
    debug_print("\tEL: ");
    switch (el_state) {
      case IDLE: debug_print("IDLE"); break;
      #ifndef HARDWARE_EA4TX_ARS_USB
      case SLOW_START_UP: debug_print("SLOW_START_UP"); break;
      case SLOW_START_DOWN: debug_print("SLOW_START_DOWN"); break;
      #endif //ifndef HARDWARE_EA4TX_ARS_USB
      case NORMAL_UP: debug_print("NORMAL_UP"); break;
      case NORMAL_DOWN: debug_print("NORMAL_DOWN"); break;
      #ifndef HARDWARE_EA4TX_ARS_USB
      case SLOW_DOWN_DOWN: debug_print("SLOW_DOWN_DOWN"); break;
      case SLOW_DOWN_UP: debug_print("SLOW_DOWN_UP"); break;
      case TIMED_SLOW_DOWN_UP: debug_print("TIMED_SLOW_DOWN_UP"); break;
      case TIMED_SLOW_DOWN_DOWN: debug_print("TIMED_SLOW_DOWN_DOWN"); break;
      #endif //ifndef HARDWARE_EA4TX_ARS_USB
    }

    debug_print("\tQ: ");
    switch (el_request_queue_state) {
      case NONE: debug_print("-"); break;
      case IN_QUEUE: debug_print("IN_QUEUE"); break;
      case IN_PROGRESS_TIMED: debug_print("IN_PROGRESS_TIMED"); break;
      case IN_PROGRESS_TO_TARGET: debug_print("IN_PROGRESS_TO_TARGET"); break;
    }
    debug_print(" EL: ");
    dtostrf(elevation / LCD_HEADING_MULTIPLIER, 0, LCD_DECIMAL_PLACES,tempstring);
    debug_print(tempstring);
    if (el_state != IDLE) {
      debug_print("\tTarget: ");
      dtostrf(target_elevation / LCD_HEADING_MULTIPLIER, 0, LCD_DECIMAL_PLACES,tempstring);
      debug_print(tempstring);
    }

    #ifdef FEATURE_EL_POSITION_POTENTIOMETER
    debug_print("\tEL Analog: ");
    dtostrf(analog_el,0,0,tempstring);
    debug_print(tempstring);
    debug_print(" (");
    dtostrf(configuration.analog_el_0_degrees,0,0,tempstring);
    debug_print(tempstring);
    debug_print("-");
    dtostrf(configuration.analog_el_max_elevation,0,0,tempstring);
    debug_print(tempstring);
    debug_print(") ");
    #endif // FEATURE_EL_POSITION_POTENTIOMETER
   
    #ifndef HARDWARE_EA4TX_ARS_USB
    debug_print("  EL Speed Norm: ");
    debug_print_int(normal_el_speed_voltage);


    debug_print(" Current: ");
    debug_print_int(current_el_speed_voltage);

    debug_print("\tOffset: ");
    debug_print_float(configuration.elevation_offset, 2);
    #endif //ifndef HARDWARE_EA4TX_ARS_USB
    debug_println("");
    #endif // FEATURE_ELEVATION_CONTROL

    //port_flush();

    #ifdef FEATURE_TIMED_BUFFER
    if (timed_buffer_status != EMPTY) {
      debug_print("\tTimed interval buff: ");
      switch (timed_buffer_status) {
        // case EMPTY: debug_print("EMPTY"); break;
        case LOADED_AZIMUTHS: debug_print("LOADED_AZIMUTHS"); break;
        case RUNNING_AZIMUTHS: debug_print("RUNNING_AZIMUTHS"); break;
        #ifdef FEATURE_ELEVATION_CONTROL
        case LOADED_AZIMUTHS_ELEVATIONS: debug_print("LOADED_AZIMUTHS_ELEVATIONS"); break;
        case RUNNING_AZIMUTHS_ELEVATIONS: debug_print("RUNNING_AZIMUTHS_ELEVATIONS"); break;
        #endif
      }

      debug_print("\tInterval (secs): ");
      debug_print_int(timed_buffer_interval_value_seconds);
      debug_print("\tEntries: ");
      debug_print_int(timed_buffer_number_entries_loaded);
      debug_print("\tEntry ptr: ");
      debug_print_int(timed_buffer_entry_pointer);
      debug_print("\tSecs since last action: ");
      debug_print_int((millis() - last_timed_buffer_action_time) / 1000);

      if (timed_buffer_number_entries_loaded > 0) {
        for (int x = 0; x < timed_buffer_number_entries_loaded; x++) {
          debug_print_int(x + 1);
          debug_print("\t:");
          debug_print_int(timed_buffer_azimuths[x] / HEADING_MULTIPLIER);
        #ifdef FEATURE_ELEVATION_CONTROL
          debug_print("\t- ");
          debug_print_int(timed_buffer_elevations[x] / HEADING_MULTIPLIER);
        #endif
          debug_print("\n");
        }
        debug_println("");
      }

    } // if (timed_buffer_status != EMPTY)
    #endif // FEATURE_TIMED_BUFFER


    #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
    /*debug_print("\tRemote Slave: Command: ");
    debug_print_int(remote_unit_command_submitted);*/
    debug_print("\tRemote Slave: Good: ");
    debug_print_float(remote_unit_good_results,0);
    debug_print(" Bad: ");
    debug_print_int(remote_unit_bad_results);
    /*debug_print(" Index: ");
    debug_print_int(remote_unit_port_buffer_index);*/
    debug_print(" CmdTouts: ");
    debug_print_int(remote_unit_command_timeouts);
    debug_print(" BuffTouts: ");
    debug_print_int(remote_unit_incoming_buffer_timeouts);
    /*debug_print(" Result: ");
    debug_print_float(remote_unit_command_result_float,2);*/
    debug_println("");
    #endif // defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)

    #if defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
    debug_print("\tEthernet Slave TCP Link State: ");
    switch(ethernetslavelinkclient0_state){
      case ETHERNET_SLAVE_DISCONNECTED: debug_print("DIS");
      case ETHERNET_SLAVE_CONNECTED: debug_print("CONNECTED");
    }
    debug_print(" Reconnects: ");
    debug_print_int(ethernet_slave_reconnects);  
    debug_println("");
    #endif // defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)  

    #ifdef DEBUG_POSITION_PULSE_INPUT
    static unsigned long last_pulse_count_time = 0;
    static unsigned long last_az_pulse_counter = 0;
    static unsigned long last_el_pulse_counter = 0;
    debug_print("\tPulse counters: AZ: ");
    debug_print_int(az_pulse_counter);
    debug_print(" AZ Ambiguous: ");
    debug_print_int(az_pulse_counter_ambiguous);
    debug_print(" EL: ");
    debug_print_int(el_pulse_counter);
    debug_print(" EL Ambiguous: ");
    debug_print_int(el_pulse_counter_ambiguous);
    debug_print(" Rate per sec: AZ: ");
    debug_print_float(((az_pulse_counter - last_az_pulse_counter) / ((millis() - last_pulse_count_time) / 1000.0)),2);
    debug_print(" EL: ");
    debug_print_float(((el_pulse_counter - last_el_pulse_counter) / ((millis() - last_pulse_count_time) / 1000.0)),2);
    debug_println("");
    last_az_pulse_counter = az_pulse_counter;
    last_el_pulse_counter = el_pulse_counter;
    last_pulse_count_time = millis();
    #endif // DEBUG_POSITION_PULSE_INPUT


    #if defined(FEATURE_AZ_POSITION_INCREMENTAL_ENCODER) && defined(DEBUG_AZ_POSITION_INCREMENTAL_ENCODER)
    debug_print("\taz_position_incremental_encoder_interrupt: ");
    debug_print_int(az_position_incremental_encoder_interrupt);
    debug_print("\taz_incremental_encoder_position: ");
    debug_print_int(az_incremental_encoder_position);
    #endif // DEBUG_AZ_POSITION_INCREMENTAL_ENCODER
    #if defined(FEATURE_EL_POSITION_INCREMENTAL_ENCODER) && defined(DEBUG_EL_POSITION_INCREMENTAL_ENCODER)
    debug_print("\n\tel_position_incremental_encoder_interrupt: ");
    debug_print_int(el_position_incremental_encoder_interrupt);
    debug_print("\tel_incremental_encoder_position: ");
    debug_print(el_incremental_encoder_position);
    #endif // DEBUG_EL_POSITION_INCREMENTAL_ENCODER
    #if (defined(FEATURE_AZ_POSITION_INCREMENTAL_ENCODER) && defined(DEBUG_AZ_POSITION_INCREMENTAL_ENCODER)) || (defined(FEATURE_EL_POSITION_INCREMENTAL_ENCODER) && defined(DEBUG_EL_POSITION_INCREMENTAL_ENCODER))
    debug_println("");
    #endif




    #ifdef FEATURE_MOON_TRACKING
    update_moon_position();
    debug_print(moon_status_string());
    #endif // FEATURE_MOON_TRACKING

    #ifdef FEATURE_SUN_TRACKING
    update_sun_position();
    debug_print(sun_status_string());
    #endif // FEATURE_SUN_TRACKING

    #if defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)
    debug_println("");
    #endif //defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)

    #ifdef FEATURE_GPS
    unsigned long gps_chars = 0;
    unsigned short gps_good_sentences = 0;
    unsigned short gps_failed_checksum = 0;
    char gps_temp_string[12] = "";
    float gps_lat_temp = 0;
    float gps_long_temp = 0;

    debug_print("\tGPS: satellites: ");
    gps_chars = gps.satellites();
    if (gps_chars == 255){gps_chars = 0;}
    dtostrf(gps_chars,0,0,gps_temp_string);
    debug_print(gps_temp_string);  
    unsigned long gps_fix_age_temp = 0;
    gps.f_get_position(&gps_lat_temp,&gps_long_temp,&gps_fix_age_temp); 
    debug_print(" lat: ");
    debug_print_float(gps_lat_temp,4);
    debug_print(" long: ");
    debug_print_float(gps_long_temp,4);
    debug_print(" fix age (mS): ");
    dtostrf(gps_fix_age_temp,0,0,gps_temp_string);
    debug_print(gps_temp_string);   
    gps.stats(&gps_chars,&gps_good_sentences,&gps_failed_checksum);     
    debug_print(" data chars: ");
    dtostrf(gps_chars,0,0,gps_temp_string);
    debug_print(gps_temp_string);
    debug_print(" good sentences: ");
    dtostrf(gps_good_sentences,0,0,gps_temp_string);
    debug_print(gps_temp_string);    
    debug_print(" failed checksum: ");
    dtostrf(gps_failed_checksum,0,0,gps_temp_string);
    debug_print(gps_temp_string);    
    debug_println("");
    #endif //FEATURE_GPS



    debug_println("\n\n\n");

    //port_flush();

    last_debug_output_time = millis();

    #endif //DEBUG_DUMP

  }
  #endif // defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)

} /* output_debug */

// --------------------------------------------------------------


// void report_current_azimuth() {

//   #ifdef FEATURE_YAESU_EMULATION
//   // The C command that reports azimuth

//   String azimuth_string;

//   #ifndef OPTION_GS_232B_EMULATION
//   control_port->print(F("+0"));
//   #endif
//   #ifdef OPTION_GS_232B_EMULATION
//   control_port->print(F("AZ="));
//   #endif
//   // control_port->write("report_current_azimith: azimuth=");
//   // control_port->println(azimuth);
//   azimuth_string = String(int(azimuth / HEADING_MULTIPLIER), DEC);
//   if (azimuth_string.length() == 1) {
//     control_port->print(F("00"));
//   } else {
//     if (azimuth_string.length() == 2) {
//       control_port->print(F("0"));
//     }
//   }
//   control_port->print(azimuth_string);

//     #ifdef FEATURE_ELEVATION_CONTROL
//     #ifndef OPTION_C_COMMAND_SENDS_AZ_AND_EL
//   if ((control_port_buffer[1] == '2') && (control_port_buffer_index > 1)) {     // did we get the C2 command?
//     #endif
//   report_current_elevation();
//     #ifndef OPTION_C_COMMAND_SENDS_AZ_AND_EL
// } else {
//   control_port->println();
// }
//     #endif // OPTION_C_COMMAND_SENDS_AZ_AND_EL
//   #endif // FEATURE_ELEVATION_CONTROL

//   #ifndef FEATURE_ELEVATION_CONTROL
//   if ((control_port_buffer[1] == '2') && (control_port_buffer_index > 1)) {     // did we get the C2 command?
//     #ifndef OPTION_GS_232B_EMULATION
//     control_port->println(F("+0000"));    // return a dummy elevation since we don't have the elevation feature turned on
//     #else
//     control_port->println(F("EL=000"));
//     #endif
//   } else {
//     control_port->println();
//   }
//     #endif // FEATURE_ELEVATION_CONTROL



//   #endif // FEATURE_YAESU_EMULATION
// }


// --------------------------------------------------------------
void print_to_port(char * print_this,byte port){

  switch(port){
    case CONTROL_PORT0: control_port->println(print_this);break;
    #ifdef FEATURE_ETHERNET
    case ETHERNET_PORT0: ethernetclient0.print(print_this); break;
    #ifdef ETHERNET_TCP_PORT_1
    case ETHERNET_PORT1: ethernetclient1.print(print_this); break;
    #endif //ETHERNET_TCP_PORT_1
    #endif //FEATURE_ETHERNET
  }

}


// --------------------------------------------------------------
void print_help(byte port){

  // The H command

  #if defined(OPTION_SERIAL_HELP_TEXT) && defined(FEATURE_YAESU_EMULATION)
  print_to_port("R Rotate Azimuth Clockwise\n",port);
  print_to_port("L Rotate Azimuth Counter Clockwise\n",port);
  print_to_port("A Stop\n",port);
  print_to_port("C Report Azimuth in Degrees\n",port);
  print_to_port("M### Rotate to ### degrees\n",port);
  print_to_port("MTTT XXX XXX XXX ... Timed Interval Direction Setting  (TTT = Step value in seconds, XXX = Azimuth in degrees)\n",port);
  print_to_port("T Start Timed Interval Tracking\n",port);
  print_to_port("N Report Total Number of M Timed Interval Azimuths\n",port);
  print_to_port("X1 Horizontal Rotation Low Speed\n",port);
  print_to_port("X2 Horizontal Rotation Middle 1 Speed\n",port);
  print_to_port("X3 Horizontal Rotation Middle 2 Speed\n",port);
  print_to_port("X4 Horizontal Rotation High Speed\n",port);
  print_to_port("S Stop\n",port);
  print_to_port("O Offset Calibration\n",port);
  print_to_port("F Full Scale Calibration\n",port);
  #ifdef FEATURE_ELEVATION_CONTROL
  print_to_port("U Rotate Elevation Up\n",port);
  print_to_port("D Rotate Elevation Down\n",port);
  print_to_port("E Stop Elevation Rotation\n",port);
  print_to_port("B Report Elevation in Degrees\n",port);
  print_to_port("Wxxx yyy Rotate Azimuth to xxx Degrees and Elevation to yyy Degrees\n",port);
  print_to_port("O2 Elevation Offset Calibration (0 degrees)\n",port);
  print_to_port("F2 Elevation Full Scale Calibration (180 degrees (or maximum))\n",port);
  #endif // FEATURE_ELEVATION_CONTROL
  #endif // defined(OPTION_SERIAL_HELP_TEXT) && defined(FEATURE_YAESU_EMULATION)


} /* print_help */

// --------------- Elevation -----------------------

#ifdef FEATURE_ELEVATION_CONTROL
void el_check_operation_timeout(){

  // check if the last executed rotation operation has been going on too long

  if (((millis() - el_last_rotate_initiation) > OPERATION_TIMEOUT) && (el_state != IDLE)) {
    submit_request(EL, REQUEST_KILL, 0, 85);
    #ifdef DEBUG_EL_CHECK_OPERATION_TIMEOUT
    if (debug_mode) {
      control_port->println(F("el_check_operation_timeout: timeout reached, aborting rotation"));
    }
    #endif // DEBUG_EL_CHECK_OPERATION_TIMEOUT
  }
}
#endif

// --------------------------------------------------------------



// #ifdef FEATURE_YAESU_EMULATION
// void yaesu_w_command(){

//   // parse out W command
//   // Short Format: WXXX YYY = azimuth YYY = elevation
//   // Long Format : WSSS XXX YYY  SSS = timed interval   XXX = azimuth    YYY = elevation

//   int parsed_elevation = 0;
//   int parsed_azimuth = 0;

//   #ifdef FEATURE_TIMED_BUFFER
//   int parsed_value1 = 0;
//   int parsed_value2 = 0;
//   #endif //FEATURE_TIMED_BUFFER

//   if (control_port_buffer_index > 8) {  // if there are more than 4 characters in the command buffer, we got a timed interval command
//     #if defined(FEATURE_TIMED_BUFFER) && defined(FEATURE_ELEVATION_CONTROL)
//     parsed_value1 = ((int(control_port_buffer[1]) - 48) * 100) + ((int(control_port_buffer[2]) - 48) * 10) + (int(control_port_buffer[3]) - 48);
//     if ((parsed_value1 > 0) && (parsed_value1 < 1000)) {
//       timed_buffer_interval_value_seconds = parsed_value1;
//       for (int x = 5; x < control_port_buffer_index; x = x + 8) {
//         parsed_value1 = ((int(control_port_buffer[x]) - 48) * 100) + ((int(control_port_buffer[x + 1]) - 48) * 10) + (int(control_port_buffer[x + 2]) - 48);
//         parsed_value2 = ((int(control_port_buffer[x + 4]) - 48) * 100) + ((int(control_port_buffer[x + 5]) - 48) * 10) + (int(control_port_buffer[x + 6]) - 48);
//         if ((parsed_value1 > -1) && (parsed_value1 < 361) && (parsed_value2 > -1) && (parsed_value2 < 181)) {  // is it a valid azimuth?
//           timed_buffer_azimuths[timed_buffer_number_entries_loaded] = (parsed_value1 * HEADING_MULTIPLIER);
//           timed_buffer_elevations[timed_buffer_number_entries_loaded] = (parsed_value2 * HEADING_MULTIPLIER);
//           timed_buffer_number_entries_loaded++;
//           timed_buffer_status = LOADED_AZIMUTHS_ELEVATIONS;
//           if (timed_buffer_number_entries_loaded > TIMED_INTERVAL_ARRAY_SIZE) {   // is the array full?
//             x = control_port_buffer_index;  // array is full, go to the first azimuth and elevation

//           }
//         } else {   // we hit an invalid bearing
//           timed_buffer_status = EMPTY;
//           timed_buffer_number_entries_loaded = 0;
//           control_port->println(F("?>"));  // error
//           return;
//         }
//       }
//     }
//     timed_buffer_entry_pointer = 1;             // go to the first bearings
//     parsed_azimuth = timed_buffer_azimuths[0];
//     parsed_elevation = timed_buffer_elevations[0];
//     #else /* ifdef FEATURE_TIMED_BUFFER */
//     control_port->println(F("Feature not activated ?>"));
//     #endif // FEATURE_TIMED_BUFFER
//   } else {
//     // this is a short form W command, just parse the azimuth and elevation and initiate rotation
//     parsed_azimuth = (((int(control_port_buffer[1]) - 48) * 100) + ((int(control_port_buffer[2]) - 48) * 10) + (int(control_port_buffer[3]) - 48)) * HEADING_MULTIPLIER;
//     parsed_elevation = (((int(control_port_buffer[5]) - 48) * 100) + ((int(control_port_buffer[6]) - 48) * 10) + (int(control_port_buffer[7]) - 48)) * HEADING_MULTIPLIER;
//   }

//   if ((parsed_azimuth >= 0) && (parsed_azimuth <= (360 * HEADING_MULTIPLIER))) {
//     submit_request(AZ, REQUEST_AZIMUTH, parsed_azimuth);
//   } else {
//       #ifdef DEBUG_YAESU
//     if (debug_mode) {
//       control_port->println(F("yaesu_w_command: W command elevation error"));
//     }
//       #endif // DEBUG_YAESU
//     control_port->println(F("?>"));      // bogus elevation - return and error and don't do anything
//     return;
//   }

//   #ifdef FEATURE_ELEVATION_CONTROL
//   if ((parsed_elevation >= 0) && (parsed_elevation <= (180 * HEADING_MULTIPLIER))) {
//     submit_request(EL, REQUEST_ELEVATION, parsed_elevation);
//   } else {
//       #ifdef DEBUG_YAESU
//     if (debug_mode) {
//       control_port->println(F("yaesu_w_command: W command elevation error"));
//     }
//       #endif // DEBUG_YAESU
//     control_port->println(F("?>"));      // bogus elevation - return and error and don't do anything
//     return;
//   }
//   #endif // FEATURE_ELEVATION_CONTROL
//   control_port->println();

// } /* yaesu_w_command */
// #endif // FEATURE_YAESU_EMULATION


// --------------------------------------------------------------

#ifdef FEATURE_ELEVATION_CONTROL
void read_elevation(byte force_read){
  // read analog input and convert it to degrees

  unsigned int previous_elevation = elevation;
  static unsigned long last_measurement_time = 0;

  #ifdef FEATURE_EL_POSITION_INCREMENTAL_ENCODER
  static unsigned int incremental_encoder_previous_elevation = elevation;
  #endif

  if (heading_reading_inhibit_pin) {
    if (digitalReadEnhanced(heading_reading_inhibit_pin)) {
      return;
    }
  }

  #ifdef DEBUG_HEADING_READING_TIME
  static unsigned long last_time = 0;
  static unsigned long last_print_time = 0;
  static float average_read_time = 0;
  #endif // DEBUG_HEADING_READING_TIME

  #ifdef DEBUG_HH12
  static unsigned long last_hh12_debug = 0;
  #endif // DEBUG_HH12

  #ifndef FEATURE_EL_POSITION_GET_FROM_REMOTE_UNIT
  if (((millis() - last_measurement_time) > ELEVATION_MEASUREMENT_FREQUENCY_MS) || (force_read)) {
  #else
  if (1) {
  #endif

    #ifdef FEATURE_EL_POSITION_POTENTIOMETER
    analog_el = analogReadEnhanced(rotator_analog_el);
    elevation = (map(analog_el, configuration.analog_el_0_degrees, configuration.analog_el_max_elevation, 0, (ELEVATION_MAXIMUM_DEGREES * HEADING_MULTIPLIER)));
    #ifdef FEATURE_ELEVATION_CORRECTION
    elevation = (correct_elevation(elevation / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
    #endif // FEATURE_ELEVATION_CORRECTION
    elevation = elevation + (configuration.elevation_offset * HEADING_MULTIPLIER);
    if (ELEVATION_SMOOTHING_FACTOR > 0) {
      elevation = (elevation * (1 - (ELEVATION_SMOOTHING_FACTOR / 100))) + (previous_elevation * (ELEVATION_SMOOTHING_FACTOR / 100));
    }
    if (elevation < 0) {
      elevation = 0;
    }
    #endif // FEATURE_EL_POSITION_POTENTIOMETER


    #ifdef FEATURE_EL_POSITION_ROTARY_ENCODER
    static byte el_position_encoder_state = 0;
    el_position_encoder_state = ttable[el_position_encoder_state & 0xf][((digitalReadEnhanced(el_rotary_position_pin2) << 1) | digitalReadEnhanced(el_rotary_position_pin1))];
    byte el_position_encoder_result = el_position_encoder_state & 0x30;
    if (el_position_encoder_result) {
      if (el_position_encoder_result == DIR_CW) {
        configuration.last_elevation = configuration.last_elevation + EL_POSITION_ROTARY_ENCODER_DEG_PER_PULSE;
        #ifdef DEBUG_POSITION_ROTARY_ENCODER
        if (debug_mode) {
          control_port->println(F("read_elevation: EL_POSITION_ROTARY_ENCODER: CW/UP"));
        }
        #endif // DEBUG_POSITION_ROTARY_ENCODER
      }
      if (el_position_encoder_result == DIR_CCW) {
        configuration.last_elevation = configuration.last_elevation - EL_POSITION_ROTARY_ENCODER_DEG_PER_PULSE;
        #ifdef DEBUG_POSITION_ROTARY_ENCODER
        if (debug_mode) {
          control_port->println(F("read_elevation: EL_POSITION_ROTARY_ENCODER: CCW/DWN"));
        }
        #endif // DEBUG_POSITION_ROTARY_ENCODER
      }
        #ifdef OPTION_EL_POSITION_ROTARY_ENCODER_HARD_LIMIT
      if (configuration.last_elevation < 0) {
        configuration.last_elevation = 0;
      }
      if (configuration.last_elevation > ELEVATION_MAXIMUM_DEGREES) {
        configuration.last_elevation = ELEVATION_MAXIMUM_DEGREES;
      }
      #endif
      elevation = int(configuration.last_elevation * HEADING_MULTIPLIER);
      #ifdef FEATURE_ELEVATION_CORRECTION
      elevation = (correct_elevation(elevation / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
      #endif // FEATURE_ELEVATION_CORRECTION
      configuration_dirty = 1;
    }
    #endif // FEATURE_EL_POSITION_ROTARY_ENCODER


    #ifdef FEATURE_EL_POSITION_ADXL345_USING_LOVE_ELECTRON_LIB
    AccelerometerRaw raw = accel.ReadRawAxis();
    AccelerometerScaled scaled = accel.ReadScaledAxis();
    #ifdef DEBUG_ACCEL
    if (debug_mode) {
      control_port->print(F("read_elevation: raw.ZAxis: "));
      control_port->println(raw.ZAxis);
    }
    #endif // DEBUG_ACCEL
    elevation = (atan2(scaled.YAxis, scaled.ZAxis) * 180 * HEADING_MULTIPLIER) / M_PI;
    #ifdef FEATURE_ELEVATION_CORRECTION
    elevation = (correct_elevation(elevation / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
    #endif // FEATURE_ELEVATION_CORRECTION
    elevation = elevation + (configuration.elevation_offset * HEADING_MULTIPLIER);
    if (ELEVATION_SMOOTHING_FACTOR > 0) {
      elevation = (elevation * (1 - (ELEVATION_SMOOTHING_FACTOR / 100))) + (previous_elevation * (ELEVATION_SMOOTHING_FACTOR / 100));
    }
    #endif // FEATURE_EL_POSITION_ADXL345_USING_LOVE_ELECTRON_LIB

    #ifdef FEATURE_EL_POSITION_ADXL345_USING_ADAFRUIT_LIB
    sensors_event_t event;
    accel.getEvent(&event);
    #ifdef DEBUG_ACCEL
    if (debug_mode) {
      control_port->print(F("read_elevation: event.acceleration.z: "));
      control_port->println(event.acceleration.z);
    }
    #endif // DEBUG_ACCEL
    elevation = (atan2(event.acceleration.y, event.acceleration.z) * 180 * HEADING_MULTIPLIER) / M_PI;
    #ifdef FEATURE_ELEVATION_CORRECTION
    elevation = (correct_elevation(elevation / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
    #endif // FEATURE_ELEVATION_CORRECTION
    elevation = elevation + (configuration.elevation_offset * HEADING_MULTIPLIER);
    #endif // FEATURE_EL_POSITION_ADXL345_USING_ADAFRUIT_LIB



    #ifdef FEATURE_EL_POSITION_ADAFRUIT_LSM303
    lsm.read();
    #ifdef DEBUG_ACCEL
    if (debug_mode) {
      control_port->print(F("read_elevation: lsm.accelData.y: "));
      control_port->print(lsm.accelData.y);
      control_port->print(F(" lsm.accelData.z: "));
      control_port->println(lsm.accelData.z);
    }
    #endif // DEBUG_ACCEL
    elevation = (atan2(lsm.accelData.y, lsm.accelData.z) * 180 * HEADING_MULTIPLIER) / M_PI;
    #ifdef FEATURE_ELEVATION_CORRECTION
    elevation = (correct_elevation(elevation / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
    #endif // FEATURE_ELEVATION_CORRECTION
    elevation = elevation + (configuration.elevation_offset * HEADING_MULTIPLIER);
    #endif // FEATURE_EL_POSITION_ADAFRUIT_LSM303



    #ifdef FEATURE_EL_POSITION_PULSE_INPUT
    #ifdef DEBUG_POSITION_PULSE_INPUT
    //    if (el_position_pule_interrupt_handler_flag) {
    //      control_port->print(F("read_elevation: el_position_pule_interrupt_handler_flag: "));
    //      control_port->println(el_position_pule_interrupt_handler_flag);
    //      el_position_pule_interrupt_handler_flag = 0;
    //    }
    #endif // DEBUG_POSITION_PULSE_INPUT

    static float last_el_position_pulse_input_elevation = el_position_pulse_input_elevation;

    if (el_position_pulse_input_elevation != last_el_position_pulse_input_elevation) {
      #ifdef DEBUG_POSITION_PULSE_INPUT
      //      if (debug_mode){
      //        control_port->print(F("read_elevation: el_position_pulse_input_elevation:"));
      //        control_port->println(el_position_pulse_input_elevation);
      //      }
      #endif // DEBUG_POSITION_PULSE_INPUT
      configuration.last_elevation = el_position_pulse_input_elevation;
      configuration_dirty = 1;
      last_el_position_pulse_input_elevation = el_position_pulse_input_elevation;
      elevation = int(configuration.last_elevation * HEADING_MULTIPLIER);
      #ifdef FEATURE_ELEVATION_CORRECTION
      elevation = (correct_elevation(elevation / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
      #endif FEATURE_ELEVATION_CORRECTION
      elevation = elevation + (configuration.elevation_offset * HEADING_MULTIPLIER);
    }
    #endif // FEATURE_EL_POSITION_PULSE_INPUT

    #ifdef FEATURE_EL_POSITION_GET_FROM_REMOTE_UNIT
    #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
    static unsigned long last_remote_unit_el_query_time = 0;
    // do we have a command result waiting for us?
    if (remote_unit_command_results_available == REMOTE_UNIT_EL_COMMAND) {

      #ifdef DEBUG_HEADING_READING_TIME
      average_read_time = (average_read_time + (millis() - last_time)) / 2.0;
      last_time = millis();

      if (debug_mode) {
        if ((millis() - last_print_time) > 1000) {
          control_port->print(F("read_elevation: avg read frequency: "));
          control_port->println(average_read_time, 2);
          last_print_time = millis();
        }
      }
      #endif // DEBUG_HEADING_READING_TIME
      elevation = remote_unit_command_result_float * HEADING_MULTIPLIER;
      #ifdef FEATURE_ELEVATION_CORRECTION
      elevation = (correct_elevation(elevation / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
      #endif // FEATURE_ELEVATION_CORRECTION
      elevation = elevation + (configuration.elevation_offset * HEADING_MULTIPLIER);
      if (ELEVATION_SMOOTHING_FACTOR > 0) {
        elevation = (elevation * (1 - (ELEVATION_SMOOTHING_FACTOR / 100))) + (previous_elevation * (ELEVATION_SMOOTHING_FACTOR / 100));
      }
      remote_unit_command_results_available = 0;
    } else {
      // is it time to request the elevation?
      if ((millis() - last_remote_unit_el_query_time) > EL_REMOTE_UNIT_QUERY_TIME_MS) {
        if (submit_remote_command(REMOTE_UNIT_EL_COMMAND, 0, 0)) {
          last_remote_unit_el_query_time = millis();
        }
      }
    }
    #endif // defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
    #endif // FEATURE_EL_POSITION_GET_FROM_REMOTE_UNIT


    #ifdef FEATURE_EL_POSITION_HH12_AS5045_SSI
    elevation = int(elevation_hh12.heading() * HEADING_MULTIPLIER);
    #ifdef DEBUG_HH12
    if ((millis() - last_hh12_debug) > 5000) {
      control_port->print(F("read_elevation: HH-12 raw: "));
      control_port->println(elevation);
      last_hh12_debug = millis();
    }
    #endif // DEBUG_HH12
    if (elevation > (180 * HEADING_MULTIPLIER)) {
      elevation = elevation - (360 * HEADING_MULTIPLIER);
    }
    #ifdef FEATURE_ELEVATION_CORRECTION
    elevation = (correct_elevation(elevation / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
    #endif // FEATURE_ELEVATION_CORRECTION
    elevation = elevation + (configuration.elevation_offset * HEADING_MULTIPLIER);
    #endif // FEATURE_EL_POSITION_HH12_AS5045_SSI


    #ifdef FEATURE_EL_POSITION_INCREMENTAL_ENCODER
    elevation = ((((el_incremental_encoder_position) / (EL_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.)) * 360.0) * HEADING_MULTIPLIER);
    #ifdef FEATURE_ELEVATION_CORRECTION
    elevation = (correct_elevation(elevation / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
    #endif // FEATURE_ELEVATION_CORRECTION
    if (incremental_encoder_previous_elevation != elevation) {
      configuration.last_el_incremental_encoder_position = el_incremental_encoder_position;
      configuration_dirty = 1;
      incremental_encoder_previous_elevation = elevation;
    }
    elevation = elevation + (configuration.elevation_offset * HEADING_MULTIPLIER);
    #endif // FEATURE_EL_POSITION_INCREMENTAL_ENCODER

    #ifdef FEATURE_EL_POSITION_MEMSIC_2125
    unsigned int pulseY = pulseIn(pin_memsic_2125_y,HIGH,250000);
    pulseY = pulseIn(pin_memsic_2125_y,HIGH,250000);
    double Yangle = (asin(((( pulseY / 10. ) - 500.) * 8.) / 1000.0 )) * (360. / (2. * M_PI));
    #ifdef DEBUG_MEMSIC_2125
    debug_print("read_elevation: memsic2125 pulseY:");
    debug_print_int(pulseY);
    debug_println("");
    #endif //DEBUG_MEMSIC_2125
    elevation = Yangle * HEADING_MULTIPLIER;    
    #ifdef FEATURE_ELEVATION_CORRECTION
    elevation = (correct_elevation(elevation / HEADING_MULTIPLIER) * HEADING_MULTIPLIER);
    #endif //FEATURE_ELEVATION_CORRECTION
    #endif //FEATURE_EL_POSITION_MEMSIC_2125

    last_measurement_time = millis();
  }




} /* read_elevation */
#endif /* ifdef FEATURE_ELEVATION_CONTROL */


// --------------------------------------------------------------
#ifdef FEATURE_ELEVATION_CONTROL
void update_el_variable_outputs(byte speed_voltage){


  #ifdef DEBUG_VARIABLE_OUTPUTS
  debug_print("update_el_variable_outputs: speed_voltage: ");
  debug_print_int(speed_voltage);
  #endif // DEBUG_VARIABLE_OUTPUTS

  if (((el_state == SLOW_START_UP) || (el_state == NORMAL_UP) || (el_state == SLOW_DOWN_UP) || (el_state == TIMED_SLOW_DOWN_UP)) && (rotate_up_pwm)) {
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print("\trotate_up_pwm");
    #endif // DEBUG_VARIABLE_OUTPUTS
    analogWriteEnhanced(rotate_up_pwm, speed_voltage);
  }

  if (((el_state == SLOW_START_DOWN) || (el_state == NORMAL_DOWN) || (el_state == SLOW_DOWN_DOWN) || (el_state == TIMED_SLOW_DOWN_DOWN)) && (rotate_down_pwm)) {
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print("\trotate_down_pwm");
    #endif // DEBUG_VARIABLE_OUTPUTS
    analogWriteEnhanced(rotate_down_pwm, speed_voltage);
  }

  if (((el_state == SLOW_START_DOWN) || (el_state == NORMAL_DOWN) || (el_state == SLOW_DOWN_DOWN) || (el_state == TIMED_SLOW_DOWN_DOWN) ||
       (el_state == SLOW_START_UP) || (el_state == NORMAL_UP) || (el_state == SLOW_DOWN_UP) || (el_state == TIMED_SLOW_DOWN_UP)) && (rotate_up_down_pwm)) {
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print("\trotate_up_down_pwm");
    #endif // DEBUG_VARIABLE_OUTPUTS
    analogWriteEnhanced(rotate_up_down_pwm, speed_voltage);
  }


  if (((el_state == SLOW_START_UP) || (el_state == NORMAL_UP) || (el_state == SLOW_DOWN_UP) || (el_state == TIMED_SLOW_DOWN_UP)) && (rotate_up_freq)) {
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print("\trotate_up_freq");
    #endif // DEBUG_VARIABLE_OUTPUTS
    tone(rotate_up_freq, map(speed_voltage, 0, 255, EL_VARIABLE_FREQ_OUTPUT_LOW, EL_VARIABLE_FREQ_OUTPUT_HIGH));
  }

  if (((el_state == SLOW_START_DOWN) || (el_state == NORMAL_DOWN) || (el_state == SLOW_DOWN_DOWN) || (el_state == TIMED_SLOW_DOWN_DOWN)) && (rotate_down_freq)) {
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print("\trotate_down_freq");
    #endif // DEBUG_VARIABLE_OUTPUTS
    tone(rotate_down_freq, map(speed_voltage, 0, 255, EL_VARIABLE_FREQ_OUTPUT_LOW, EL_VARIABLE_FREQ_OUTPUT_HIGH));
  }

  #ifdef FEATURE_STEPPER_MOTOR

  unsigned int el_tone = 0;

  if (((el_state == SLOW_START_UP) || (el_state == NORMAL_UP) || (el_state == SLOW_DOWN_UP) || (el_state == TIMED_SLOW_DOWN_UP) || (el_state == SLOW_START_DOWN) || (el_state == NORMAL_DOWN) || (el_state == SLOW_DOWN_DOWN) || (el_state == TIMED_SLOW_DOWN_DOWN)) && (el_stepper_motor_pulse)) {
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print("\tel_stepper_motor_pulse: ");
    #endif // DEBUG_VARIABLE_OUTPUTS
    el_tone = map(speed_voltage, 0, 255, EL_VARIABLE_FREQ_OUTPUT_LOW, EL_VARIABLE_FREQ_OUTPUT_HIGH);

    if ((el_tone < 31) && (el_tone != 0)) {el_tone = 31;}
    if (el_tone > 20000) {el_tone = 20000;}
    if (el_tone > 0) {
      tone(el_stepper_motor_pulse,el_tone);
    } else {
      noTone(el_stepper_motor_pulse);
    }
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print_int(el_tone);
    #endif // DEBUG_VARIABLE_OUTPUTS
    //tone(el_stepper_motor_pulse, map(speed_voltage, 0, 255, EL_VARIABLE_FREQ_OUTPUT_LOW, EL_VARIABLE_FREQ_OUTPUT_HIGH));
  }
  #endif //FEATURE_STEPPER_MOTOR

  if (elevation_speed_voltage) {
    analogWriteEnhanced(elevation_speed_voltage, speed_voltage);
  }

  #ifdef DEBUG_VARIABLE_OUTPUTS
  debug_println("");
  #endif // DEBUG_VARIABLE_OUTPUTS

  current_el_speed_voltage = speed_voltage;


} /* update_el_variable_outputs */
#endif // FEATURE_ELEVATION_CONTROL

// --------------------------------------------------------------
void update_az_variable_outputs(byte speed_voltage){


  #ifdef DEBUG_VARIABLE_OUTPUTS
  int temp_int = 0;

  debug_print("update_az_variable_outputs: az_state: ");
  switch (az_state) {
    case IDLE: debug_print("IDLE"); break;
    case SLOW_START_CW: debug_print("SLOW_START_CW"); break;
    case SLOW_START_CCW: debug_print("SLOW_START_CCW"); break;
    case NORMAL_CW: debug_print("NORMAL_CW"); break;
    case NORMAL_CCW: debug_print("NORMAL_CCW"); break;
    case SLOW_DOWN_CW: debug_print("SLOW_DOWN_CW"); break;
    case SLOW_DOWN_CCW: debug_print("SLOW_DOWN_CCW"); break;
    case INITIALIZE_SLOW_START_CW: debug_print("INITIALIZE_SLOW_START_CW"); break;
    case INITIALIZE_SLOW_START_CCW: debug_print("INITIALIZE_SLOW_START_CCW"); break;
    case INITIALIZE_TIMED_SLOW_DOWN_CW: debug_print("INITIALIZE_TIMED_SLOW_DOWN_CW"); break;
    case INITIALIZE_TIMED_SLOW_DOWN_CCW: debug_print("INITIALIZE_TIMED_SLOW_DOWN_CCW"); break;
    case TIMED_SLOW_DOWN_CW: debug_print("TIMED_SLOW_DOWN_CW"); break;
    case TIMED_SLOW_DOWN_CCW: debug_print("TIMED_SLOW_DOWN_CCW"); break;
    case INITIALIZE_DIR_CHANGE_TO_CW: debug_print("INITIALIZE_DIR_CHANGE_TO_CW"); break;
    case INITIALIZE_DIR_CHANGE_TO_CCW: debug_print("INITIALIZE_DIR_CHANGE_TO_CCW"); break;
    case INITIALIZE_NORMAL_CW: debug_print("INITIALIZE_NORMAL_CW"); break;
    case INITIALIZE_NORMAL_CCW: debug_print("INITIALIZE_NORMAL_CCW"); break;
    default: debug_print("UNDEF"); break;
  }
  debug_print(" speed_voltage: ");
  debug_print_int(speed_voltage);
  #endif // DEBUG_VARIABLE_OUTPUTS

  if (((az_state == SLOW_START_CW) || (az_state == NORMAL_CW) || (az_state == SLOW_DOWN_CW) || (az_state == TIMED_SLOW_DOWN_CW)) && (rotate_cw_pwm)) {
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print("\trotate_cw_pwm");
    #endif // DEBUG_VARIABLE_OUTPUTS
    analogWriteEnhanced(rotate_cw_pwm, speed_voltage);
  }

  if (((az_state == SLOW_START_CCW) || (az_state == NORMAL_CCW) || (az_state == SLOW_DOWN_CCW) || (az_state == TIMED_SLOW_DOWN_CCW)) && (rotate_ccw_pwm)) {
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print("\trotate_ccw_pwm");
    #endif // DEBUG_VARIABLE_OUTPUTS
    analogWriteEnhanced(rotate_ccw_pwm, speed_voltage);
  }

  if (((az_state == SLOW_START_CW) || (az_state == NORMAL_CW) || (az_state == SLOW_DOWN_CW) || (az_state == TIMED_SLOW_DOWN_CW) || (az_state == SLOW_START_CCW) || (az_state == NORMAL_CCW) || (az_state == SLOW_DOWN_CCW) || (az_state == TIMED_SLOW_DOWN_CCW)) && (rotate_cw_ccw_pwm)) {
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print("\trotate_cw_ccw_pwm");
    #endif // DEBUG_VARIABLE_OUTPUTS
    analogWriteEnhanced(rotate_cw_ccw_pwm, speed_voltage);
  }


  if (((az_state == SLOW_START_CW) || (az_state == NORMAL_CW) || (az_state == SLOW_DOWN_CW) || (az_state == TIMED_SLOW_DOWN_CW)) && (rotate_cw_freq)) {
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print("\trotate_cw_freq: ");
    temp_int = map(speed_voltage, 0, 255, AZ_VARIABLE_FREQ_OUTPUT_LOW, AZ_VARIABLE_FREQ_OUTPUT_HIGH);
    tone(rotate_cw_freq, temp_int);
    debug_print_int(temp_int);
    #else // DEBUG_VARIABLE_OUTPUTS
    tone(rotate_cw_freq, map(speed_voltage, 0, 255, AZ_VARIABLE_FREQ_OUTPUT_LOW, AZ_VARIABLE_FREQ_OUTPUT_HIGH));
    #endif // DEBUG_VARIABLE_OUTPUTS
  }

  if (((az_state == SLOW_START_CCW) || (az_state == NORMAL_CCW) || (az_state == SLOW_DOWN_CCW) || (az_state == TIMED_SLOW_DOWN_CCW)) && (rotate_ccw_freq)) {
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print("\trotate_ccw_freq: ");
    temp_int = map(speed_voltage, 0, 255, AZ_VARIABLE_FREQ_OUTPUT_LOW, AZ_VARIABLE_FREQ_OUTPUT_HIGH);
    tone(rotate_ccw_freq, temp_int);
    debug_print_int(temp_int);    
    #else // DEBUG_VARIABLE_OUTPUTS
    tone(rotate_ccw_freq, map(speed_voltage, 0, 255, AZ_VARIABLE_FREQ_OUTPUT_LOW, AZ_VARIABLE_FREQ_OUTPUT_HIGH));
    #endif // DEBUG_VARIABLE_OUTPUTS
  }

  #ifdef FEATURE_STEPPER_MOTOR

  unsigned int az_tone = 0;

  if (((az_state == SLOW_START_CW) || (az_state == NORMAL_CW) || (az_state == SLOW_DOWN_CW) || (az_state == TIMED_SLOW_DOWN_CW) || (az_state == SLOW_START_CCW) || (az_state == NORMAL_CCW) || (az_state == SLOW_DOWN_CCW) || (az_state == TIMED_SLOW_DOWN_CCW)) && (az_stepper_motor_pulse)) {
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print("\taz_stepper_motor_pulse: ");
    #endif // DEBUG_VARIABLE_OUTPUTS
    az_tone = map(speed_voltage, 0, 255, AZ_VARIABLE_FREQ_OUTPUT_LOW, AZ_VARIABLE_FREQ_OUTPUT_HIGH);
    if ((az_tone < 31) && (az_tone != 0)) {az_tone = 31;}
    if (az_tone > 20000) {az_tone = 20000;}
    if (az_tone > 0) {
      tone(az_stepper_motor_pulse,az_tone);
    } else {
      noTone(az_stepper_motor_pulse);
    }
    #ifdef DEBUG_VARIABLE_OUTPUTS
    debug_print_int(az_tone);
    #endif // DEBUG_VARIABLE_OUTPUTS 
  }
  #endif //FEATURE_STEPPER_MOTOR

  if (azimuth_speed_voltage) {
    analogWriteEnhanced(azimuth_speed_voltage, speed_voltage);
  }

  #ifdef DEBUG_VARIABLE_OUTPUTS
  debug_println("");
  #endif // DEBUG_VARIABLE_OUTPUTS

  current_az_speed_voltage = speed_voltage;

} /* update_az_variable_outputs */

// --------------------------------------------------------------

void rotator(byte rotation_action, byte rotation_type) {

  #ifdef DEBUG_ROTATOR
  if (debug_mode) {
    control_port->flush();
    control_port->print(F("rotator: rotation_action:"));
    control_port->print(rotation_action);
    control_port->print(F(" rotation_type:"));
    control_port->flush();
    control_port->print(rotation_type);
    control_port->print(F("->"));
    control_port->flush();
    // delay(1000);
  }
  #endif // DEBUG_ROTATOR

  switch (rotation_type) {
    case CW:
    #ifdef DEBUG_ROTATOR
      if (debug_mode) {
        control_port->print(F("CW ")); control_port->flush();
      }
    #endif // DEBUG_ROTATOR
      if (rotation_action == ACTIVATE) {
      #ifdef DEBUG_ROTATOR
        if (debug_mode) {
          control_port->println(F("ACTIVATE")); control_port->flush();
        }
      #endif // DEBUG_ROTATOR
        brake_release(AZ, BRAKE_RELEASE_ON);
        if (az_slowstart_active) {
          if (rotate_cw_pwm) {
            analogWriteEnhanced(rotate_cw_pwm, 0);
          }
          if (rotate_ccw_pwm) {
            analogWriteEnhanced(rotate_ccw_pwm, 0); digitalWriteEnhanced(rotate_ccw_pwm, LOW);
          }
          if (rotate_cw_ccw_pwm) {
            analogWriteEnhanced(rotate_cw_ccw_pwm, 0);
          }
          if (rotate_cw_freq) {
            noTone(rotate_cw_freq);
          }
          if (rotate_ccw_freq) {
            noTone(rotate_ccw_freq);
          }
          if (az_stepper_motor_pulse) {
            noTone(az_stepper_motor_pulse);
            digitalWriteEnhanced(az_stepper_motor_pulse, LOW);
          }                 
        } else {
          if (rotate_cw_pwm) {
            analogWriteEnhanced(rotate_cw_pwm, normal_az_speed_voltage);
          }
          if (rotate_ccw_pwm) {
            analogWriteEnhanced(rotate_ccw_pwm, 0); digitalWriteEnhanced(rotate_ccw_pwm, LOW);
          }
          if (rotate_cw_ccw_pwm) {
            analogWriteEnhanced(rotate_cw_ccw_pwm, normal_az_speed_voltage);
          }
          if (rotate_cw_freq) {
            tone(rotate_cw_freq, map(normal_az_speed_voltage, 0, 255, AZ_VARIABLE_FREQ_OUTPUT_LOW, AZ_VARIABLE_FREQ_OUTPUT_HIGH));
          }
          if (rotate_ccw_freq) {
            noTone(rotate_ccw_freq);
          }
          if (az_stepper_motor_pulse) {
            tone(az_stepper_motor_pulse, map(normal_az_speed_voltage, 0, 255, AZ_VARIABLE_FREQ_OUTPUT_LOW, AZ_VARIABLE_FREQ_OUTPUT_HIGH));
          }          
        }
        if (rotate_cw) {
          digitalWriteEnhanced(rotate_cw, ROTATE_PIN_ACTIVE_VALUE);
        }
        if (rotate_ccw) {
          digitalWriteEnhanced(rotate_ccw, ROTATE_PIN_INACTIVE_VALUE);
        }
        if (rotate_cw_ccw){
          digitalWriteEnhanced(rotate_cw_ccw, ROTATE_PIN_ACTIVE_VALUE);
        }
        #ifdef FEATURE_STEPPER_MOTOR
        if (az_stepper_motor_direction){
          if (az_stepper_motor_last_direction != STEPPER_CW){
            if (az_stepper_motor_last_pin_state == LOW){
              digitalWriteEnhanced(az_stepper_motor_direction,HIGH);
              az_stepper_motor_last_pin_state = HIGH;
            } else {
              digitalWriteEnhanced(az_stepper_motor_direction,LOW);
              az_stepper_motor_last_pin_state = LOW;              
            }
            az_stepper_motor_last_direction = STEPPER_CW;
          }
        }
        #endif //FEATURE_STEPPER_MOTOR
        #ifdef DEBUG_ROTATOR
        if (debug_mode) {
          control_port->print(F("rotator: normal_az_speed_voltage:"));
          control_port->println(normal_az_speed_voltage);
          //control_port->flush();
        }
        #endif // DEBUG_ROTATOR
      } else {
          #ifdef DEBUG_ROTATOR
        if (debug_mode) {
          control_port->println(F("DEACTIVATE")); //control_port->flush();
        }
          #endif // DEBUG_ROTATOR
        if (rotate_cw_pwm) {
          analogWriteEnhanced(rotate_cw_pwm, 0); digitalWriteEnhanced(rotate_cw_pwm, LOW);
        }
        if (rotate_cw_ccw_pwm) {
          analogWriteEnhanced(rotate_cw_ccw_pwm, 0);
        }
        if (rotate_cw) {
          digitalWriteEnhanced(rotate_cw, ROTATE_PIN_INACTIVE_VALUE);
        }
        if (rotate_cw_ccw){
          digitalWriteEnhanced(rotate_cw_ccw, ROTATE_PIN_INACTIVE_VALUE);
        }        
        if (rotate_cw_freq) {
          noTone(rotate_cw_freq);
        }
        #ifdef FEATURE_STEPPER_MOTOR
        if (az_stepper_motor_pulse) {
          noTone(az_stepper_motor_pulse);
          digitalWriteEnhanced(az_stepper_motor_pulse, HIGH);
        }  
        #endif //FEATURE_STEPPER_MOTOR      
      }
      break;
    case CCW:
      #ifdef DEBUG_ROTATOR
      if (debug_mode) {
        control_port->print(F("CCW ")); control_port->flush();
      }
        #endif // DEBUG_ROTATOR
      if (rotation_action == ACTIVATE) {
          #ifdef DEBUG_ROTATOR
        if (debug_mode) {
          control_port->println(F("ACTIVATE")); control_port->flush();
        }
          #endif // DEBUG_ROTATOR
        brake_release(AZ, BRAKE_RELEASE_ON);
        if (az_slowstart_active) {
          if (rotate_cw_pwm) {
            analogWriteEnhanced(rotate_cw_pwm, 0); digitalWriteEnhanced(rotate_cw_pwm, LOW);
          }
          if (rotate_ccw_pwm) {
            analogWriteEnhanced(rotate_ccw_pwm, 0);
          }
          if (rotate_cw_ccw_pwm) {
            analogWriteEnhanced(rotate_cw_ccw_pwm, 0);
          }
          if (rotate_cw_freq) {
            noTone(rotate_cw_freq);
          }
          if (rotate_ccw_freq) {
            noTone(rotate_ccw_freq);
          }
          #ifdef FEATURE_STEPPER_MOTOR
          if (az_stepper_motor_pulse) {
            noTone(az_stepper_motor_pulse);
            digitalWriteEnhanced(az_stepper_motor_pulse, LOW);
          }    
          #endif //FEATURE_STEPPER_MOTOR        
        } else {
          if (rotate_cw_pwm) {
            analogWriteEnhanced(rotate_cw_pwm, 0); digitalWriteEnhanced(rotate_cw_pwm, LOW);
          }
          if (rotate_ccw_pwm) {
            analogWriteEnhanced(rotate_ccw_pwm, normal_az_speed_voltage);
          }
          if (rotate_cw_ccw_pwm) {
            analogWriteEnhanced(rotate_cw_ccw_pwm, normal_az_speed_voltage);
          }
          if (rotate_cw_freq) {
            noTone(rotate_cw_freq);
          }
          if (rotate_ccw_freq) {
            tone(rotate_ccw_freq, map(normal_az_speed_voltage, 0, 255, AZ_VARIABLE_FREQ_OUTPUT_LOW, AZ_VARIABLE_FREQ_OUTPUT_HIGH));
          }
          #ifdef FEATURE_STEPPER_MOTOR
          if (az_stepper_motor_pulse) {
            tone(az_stepper_motor_pulse, map(normal_az_speed_voltage, 0, 255, AZ_VARIABLE_FREQ_OUTPUT_LOW, AZ_VARIABLE_FREQ_OUTPUT_HIGH));
          }     
          #endif //FEATURE_STEPPER_MOTOR        
        }
        if (rotate_cw) {
          digitalWriteEnhanced(rotate_cw, ROTATE_PIN_INACTIVE_VALUE);
        }
        if (rotate_ccw) {
          digitalWriteEnhanced(rotate_ccw, ROTATE_PIN_ACTIVE_VALUE);
        }
        if (rotate_cw_ccw){
          digitalWriteEnhanced(rotate_cw_ccw, ROTATE_PIN_ACTIVE_VALUE);
        }       
        #ifdef FEATURE_STEPPER_MOTOR
        if (az_stepper_motor_direction){
          if (az_stepper_motor_last_direction != STEPPER_CCW){
            if (az_stepper_motor_last_pin_state == LOW){
              digitalWriteEnhanced(az_stepper_motor_direction,HIGH);
              az_stepper_motor_last_pin_state = HIGH;
            } else {
              digitalWriteEnhanced(az_stepper_motor_direction,LOW);
              az_stepper_motor_last_pin_state = LOW;              
            }
            az_stepper_motor_last_direction = STEPPER_CCW;
          }
        }
        #endif //FEATURE_STEPPER_MOTOR

        #ifdef DEBUG_ROTATOR
        if (debug_mode) {
          control_port->print(F("rotator: normal_az_speed_voltage:"));
          control_port->println(normal_az_speed_voltage);
          control_port->flush();
        }
        #endif // DEBUG_ROTATOR
      } else {
        #ifdef DEBUG_ROTATOR
        if (debug_mode) {
          control_port->println(F("DEACTIVATE")); control_port->flush();
        }
              #endif // DEBUG_ROTATOR
        if (rotate_ccw_pwm) {
          analogWriteEnhanced(rotate_ccw_pwm, 0); digitalWriteEnhanced(rotate_ccw_pwm, LOW);
        }
        if (rotate_ccw) {
          digitalWriteEnhanced(rotate_ccw, ROTATE_PIN_INACTIVE_VALUE);
        }
        if (rotate_ccw_freq) {
          noTone(rotate_ccw_freq);
        }
      }
      break;

            #ifdef FEATURE_ELEVATION_CONTROL


    case UP:
    #ifdef DEBUG_ROTATOR
      if (debug_mode) {
        control_port->print(F("ROTATION_UP ")); control_port->flush();
      }
    #endif // DEBUG_ROTATOR
      if (rotation_action == ACTIVATE) {
      #ifdef DEBUG_ROTATOR
        if (debug_mode) {
          control_port->println(F("ACTIVATE")); control_port->flush();
        }
      #endif // DEBUG_ROTATOR
        brake_release(EL, BRAKE_RELEASE_ON);
        if (el_slowstart_active) {
          if (rotate_up_pwm) {
            analogWriteEnhanced(rotate_up_pwm, 0);
          }
          if (rotate_down_pwm) {
            analogWriteEnhanced(rotate_down_pwm, 0); digitalWriteEnhanced(rotate_down_pwm, LOW);
          }
          if (rotate_up_down_pwm) {
            analogWriteEnhanced(rotate_up_down_pwm, 0);
          }
          if (rotate_up_freq) {
            noTone(rotate_up_freq);
          }
          if (rotate_down_freq) {
            noTone(rotate_down_freq);
          }
          #ifdef FEATURE_STEPPER_MOTOR
          if (el_stepper_motor_pulse) {
            noTone(el_stepper_motor_pulse);
            digitalWriteEnhanced(el_stepper_motor_pulse,LOW);
          }      
          #endif //FEATURE_STEPPER_MOTOR    
        } else {
          if (rotate_up_pwm) {
            analogWriteEnhanced(rotate_up_pwm, normal_el_speed_voltage);
          }
          if (rotate_down_pwm) {
            analogWriteEnhanced(rotate_down_pwm, 0); digitalWriteEnhanced(rotate_down_pwm, LOW);
          }
          if (rotate_up_down_pwm) {
            analogWriteEnhanced(rotate_up_down_pwm, normal_el_speed_voltage);
          }
          if (rotate_up_freq) {
            tone(rotate_up_freq, map(normal_el_speed_voltage, 0, 255, EL_VARIABLE_FREQ_OUTPUT_LOW, EL_VARIABLE_FREQ_OUTPUT_HIGH));
          }
          #ifdef FEATURE_STEPPER_MOTOR
          if (el_stepper_motor_pulse) {
            tone(el_stepper_motor_pulse, map(normal_el_speed_voltage, 0, 255, EL_VARIABLE_FREQ_OUTPUT_LOW, EL_VARIABLE_FREQ_OUTPUT_HIGH));
          }
          #endif //FEATURE_STEPPER_MOTOR  
          if (rotate_down_freq) {
            noTone(rotate_down_freq);
          }
        }
        if (rotate_up) {
          digitalWriteEnhanced(rotate_up, ROTATE_PIN_ACTIVE_VALUE);
        }
        if (rotate_down) {
          digitalWriteEnhanced(rotate_down, ROTATE_PIN_INACTIVE_VALUE);
        }
        if (rotate_up_or_down) {
          digitalWriteEnhanced(rotate_up_or_down, ROTATE_PIN_ACTIVE_VALUE);
        } 
        #ifdef FEATURE_STEPPER_MOTOR
        if (el_stepper_motor_direction){
          if (el_stepper_motor_last_direction != STEPPER_UP){
             if (el_stepper_motor_last_pin_state == LOW){
               digitalWriteEnhanced(el_stepper_motor_direction,HIGH);
               el_stepper_motor_last_pin_state = HIGH;
             } else {
               digitalWriteEnhanced(el_stepper_motor_direction,LOW);
               el_stepper_motor_last_pin_state = LOW;              
             }
             el_stepper_motor_last_direction = STEPPER_UP;
          }
        }
        #endif //FEATURE_STEPPER_MOTOR           
      } else {
      #ifdef DEBUG_ROTATOR
        if (debug_mode) {
          control_port->println(F("DEACTIVATE")); control_port->flush();
        }
      #endif // DEBUG_ROTATOR
        if (rotate_up) {
          digitalWriteEnhanced(rotate_up, ROTATE_PIN_INACTIVE_VALUE);
        }
        if (rotate_up_pwm) {
          analogWriteEnhanced(rotate_up_pwm, 0); digitalWriteEnhanced(rotate_up_pwm, LOW);
        }
        if (rotate_up_down_pwm) {
          analogWriteEnhanced(rotate_up_down_pwm, 0);
        }
        if (rotate_up_freq) {
          noTone(rotate_up_freq);
        }
        if (rotate_up_or_down) {
          digitalWriteEnhanced(rotate_up_or_down, ROTATE_PIN_INACTIVE_VALUE);
        }   
        #ifdef FEATURE_STEPPER_MOTOR
        if (el_stepper_motor_pulse) {
          noTone(el_stepper_motor_pulse);
          digitalWriteEnhanced(el_stepper_motor_pulse,HIGH);
        }      
        #endif //FEATURE_STEPPER_MOTOR   
      }
      break;

    case DOWN:
      #ifdef DEBUG_ROTATOR
      if (debug_mode) {
        control_port->print(F("ROTATION_DOWN ")); control_port->flush();
      }
      #endif // DEBUG_ROTATOR
      if (rotation_action == ACTIVATE) {
        #ifdef DEBUG_ROTATOR
        if (debug_mode) {
          control_port->println(F("ACTIVATE")); control_port->flush();
        }
        #endif // DEBUG_ROTATOR
        brake_release(EL, BRAKE_RELEASE_ON);
        if (el_slowstart_active) {
          if (rotate_down_pwm) {
            analogWriteEnhanced(rotate_down_pwm, 0);
          }
          if (rotate_up_pwm) {
            analogWriteEnhanced(rotate_up_pwm, 0); digitalWriteEnhanced(rotate_up_pwm, LOW);
          }
          if (rotate_up_down_pwm) {
            analogWriteEnhanced(rotate_up_down_pwm, 0);
          }
          if (rotate_up_freq) {
            noTone(rotate_up_freq);
          }
          if (rotate_down_freq) {
            noTone(rotate_down_freq);
          }
          #ifdef FEATURE_STEPPER_MOTOR
          if (el_stepper_motor_pulse) {
            noTone(el_stepper_motor_pulse);
            digitalWriteEnhanced(el_stepper_motor_pulse,LOW);
          }      
          #endif //FEATURE_STEPPER_MOTOR             
        } else {
          if (rotate_down_pwm) {
            analogWriteEnhanced(rotate_down_pwm, normal_el_speed_voltage);
          }
          if (rotate_up_pwm) {
            analogWriteEnhanced(rotate_up_pwm, 0); digitalWriteEnhanced(rotate_up_pwm, LOW);
          }
          if (rotate_up_down_pwm) {
            analogWriteEnhanced(rotate_up_down_pwm, normal_el_speed_voltage);
          }
          if (rotate_down_freq) {
            tone(rotate_down_freq, map(normal_el_speed_voltage, 0, 255, EL_VARIABLE_FREQ_OUTPUT_LOW, EL_VARIABLE_FREQ_OUTPUT_HIGH));
          }
          if (rotate_up_freq) {
            noTone(rotate_up_freq);
          }
          #ifdef FEATURE_STEPPER_MOTOR
          if (el_stepper_motor_pulse) {
            tone(el_stepper_motor_pulse, map(normal_el_speed_voltage, 0, 255, EL_VARIABLE_FREQ_OUTPUT_LOW, EL_VARIABLE_FREQ_OUTPUT_HIGH));
            digitalWriteEnhanced(el_stepper_motor_pulse,LOW);
          }      
          #endif //FEATURE_STEPPER_MOTOR             
        }
        if (rotate_up) {
          digitalWriteEnhanced(rotate_up, ROTATE_PIN_INACTIVE_VALUE);
        }
        if (rotate_down) {
          digitalWriteEnhanced(rotate_down, ROTATE_PIN_ACTIVE_VALUE);
        }
        if (rotate_up_or_down) {
          digitalWriteEnhanced(rotate_up_or_down, ROTATE_PIN_ACTIVE_VALUE);
        }         
        #ifdef FEATURE_STEPPER_MOTOR
        if (el_stepper_motor_direction){
          if (el_stepper_motor_last_direction != STEPPER_DOWN){
             if (el_stepper_motor_last_pin_state == LOW){
               digitalWriteEnhanced(el_stepper_motor_direction,HIGH);
               el_stepper_motor_last_pin_state = HIGH;
             } else {
               digitalWriteEnhanced(el_stepper_motor_direction,LOW);
               el_stepper_motor_last_pin_state = LOW;              
             }
             el_stepper_motor_last_direction = STEPPER_DOWN;
          }
        }
        #endif //FEATURE_STEPPER_MOTOR  
      } else {
          #ifdef DEBUG_ROTATOR
        if (debug_mode) {
          control_port->println(F("DEACTIVATE")); control_port->flush();
        }
          #endif // DEBUG_ROTATOR
        if (rotate_down) {
          digitalWriteEnhanced(rotate_down, ROTATE_PIN_INACTIVE_VALUE);
        }
        if (rotate_down_pwm) {
          analogWriteEnhanced(rotate_down_pwm, 0); digitalWriteEnhanced(rotate_down_pwm, LOW);
        }
        if (rotate_up_down_pwm) {
          analogWriteEnhanced(rotate_up_down_pwm, 0);
        }
        if (rotate_down_freq) {
          noTone(rotate_down_freq);
        }
        if (rotate_up_or_down) {
          digitalWriteEnhanced(rotate_up_or_down, ROTATE_PIN_INACTIVE_VALUE);
        }        
        #ifdef FEATURE_STEPPER_MOTOR
        if (el_stepper_motor_pulse) {
          noTone(el_stepper_motor_pulse);
          digitalWriteEnhanced(el_stepper_motor_pulse,HIGH);
        }      
        #endif //FEATURE_STEPPER_MOTOR 
      }
      break;
          #endif // FEATURE_ELEVATION_CONTROL
  } /* switch */

  #ifdef DEBUG_ROTATOR
  if (debug_mode) {
    control_port->println(F("rotator: exiting"));
    control_port->flush();
  }
  #endif // DEBUG_ROTATOR
} /* rotator */

// --------------------------------------------------------------
void initialize_interrupts(){

  #ifdef FEATURE_AZ_POSITION_PULSE_INPUT
  attachInterrupt(AZ_POSITION_PULSE_PIN_INTERRUPT, az_position_pulse_interrupt_handler, FALLING);
  #endif // FEATURE_AZ_POSITION_PULSE_INPUT

  #ifdef FEATURE_EL_POSITION_PULSE_INPUT
  attachInterrupt(EL_POSITION_PULSE_PIN_INTERRUPT, el_position_pulse_interrupt_handler, FALLING);
  #endif // FEATURE_EL_POSITION_PULSE_INPUT


}

// --------------------------------------------------------------

void initialize_pins(){

  if (serial_led) {
    pinModeEnhanced(serial_led, OUTPUT);
  }

  if (overlap_led) {
    pinModeEnhanced(overlap_led, OUTPUT);
  }

  if (brake_az) {
    pinModeEnhanced(brake_az, OUTPUT);
    digitalWriteEnhanced(brake_az, LOW);
  }

  if (az_speed_pot) {
    pinModeEnhanced(az_speed_pot, INPUT);
    digitalWriteEnhanced(az_speed_pot, LOW);
  }

  if (az_preset_pot) {
    pinModeEnhanced(az_preset_pot, INPUT);
    digitalWriteEnhanced(az_preset_pot, LOW);
  }

  if (preset_start_button) {
    pinModeEnhanced(preset_start_button, INPUT);
    digitalWriteEnhanced(preset_start_button, HIGH);
  }

  if (button_stop) {
    pinModeEnhanced(button_stop, INPUT);
    digitalWriteEnhanced(button_stop, HIGH);
  }

  #ifdef FEATURE_ELEVATION_CONTROL
  if (brake_el) {
    pinModeEnhanced(brake_el, OUTPUT);
    digitalWriteEnhanced(brake_el, LOW);
  }
  #endif // FEATURE_ELEVATION_CONTROL

  if (rotate_cw) {
    pinModeEnhanced(rotate_cw, OUTPUT);
  }
  if (rotate_ccw) {
    pinModeEnhanced(rotate_ccw, OUTPUT);
  }
  if (rotate_cw_pwm) {
    pinModeEnhanced(rotate_cw_pwm, OUTPUT);
  }
  if (rotate_ccw_pwm) {
    pinModeEnhanced(rotate_ccw_pwm, OUTPUT);
  }
  if (rotate_cw_ccw_pwm) {
    pinModeEnhanced(rotate_cw_ccw_pwm, OUTPUT);
  }
  if (rotate_cw_freq) {
    pinModeEnhanced(rotate_cw_freq, OUTPUT);
  }
  if (rotate_ccw_freq) {
    pinModeEnhanced(rotate_ccw_freq, OUTPUT);
  }

  rotator(DEACTIVATE, CW);
  rotator(DEACTIVATE, CCW);

  #ifndef FEATURE_AZ_POSITION_HMC5883L
  pinModeEnhanced(rotator_analog_az, INPUT);
  #endif

  if (button_cw) {
    pinModeEnhanced(button_cw, INPUT);
    digitalWriteEnhanced(button_cw, HIGH);
  }
  if (button_ccw) {
    pinModeEnhanced(button_ccw, INPUT);
    digitalWriteEnhanced(button_ccw, HIGH);
  }

  normal_az_speed_voltage = PWM_SPEED_VOLTAGE_X4;
  current_az_speed_voltage = PWM_SPEED_VOLTAGE_X4;

  #ifdef FEATURE_ELEVATION_CONTROL
  normal_el_speed_voltage = PWM_SPEED_VOLTAGE_X4;
  current_el_speed_voltage = PWM_SPEED_VOLTAGE_X4;
  #endif // FEATURE_ELEVATION_CONTROL

  if (azimuth_speed_voltage) {                 // if azimuth_speed_voltage pin is configured, set it up for PWM output
    analogWriteEnhanced(azimuth_speed_voltage, PWM_SPEED_VOLTAGE_X4);
  }


  #ifdef FEATURE_ELEVATION_CONTROL
  pinModeEnhanced(rotate_up, OUTPUT);
  pinModeEnhanced(rotate_down, OUTPUT);
  if (rotate_up_or_down) {
    pinModeEnhanced(rotate_up_or_down, OUTPUT);
  }
  if (rotate_up_pwm) {
    pinModeEnhanced(rotate_up_pwm, OUTPUT);
  }
  if (rotate_down_pwm) {
    pinModeEnhanced(rotate_down_pwm, OUTPUT);
  }
  if (rotate_up_down_pwm) {
    pinModeEnhanced(rotate_up_down_pwm, OUTPUT);
  }
  if (rotate_up_freq) {
    pinModeEnhanced(rotate_up_freq, OUTPUT);
  }
  if (rotate_down_freq) {
    pinModeEnhanced(rotate_down_freq, OUTPUT);
  }
  rotator(DEACTIVATE, UP);
  rotator(DEACTIVATE, DOWN);
  #ifdef FEATURE_EL_POSITION_POTENTIOMETER
  pinModeEnhanced(rotator_analog_el, INPUT);
  #endif // FEATURE_EL_POSITION_POTENTIOMETER
  if (button_up) {
    pinModeEnhanced(button_up, INPUT);
    digitalWriteEnhanced(button_up, HIGH);
  }
  if (button_down) {
    pinModeEnhanced(button_down, INPUT);
    digitalWriteEnhanced(button_down, HIGH);
  }

  if (elevation_speed_voltage) {                 // if elevation_speed_voltage pin is configured, set it up for PWM output
    analogWriteEnhanced(elevation_speed_voltage, PWM_SPEED_VOLTAGE_X4);
    normal_el_speed_voltage = PWM_SPEED_VOLTAGE_X4;
    current_el_speed_voltage = PWM_SPEED_VOLTAGE_X4;
  }

  read_elevation(0);
  #endif // FEATURE_ELEVATION_CONTROL

  #ifdef FEATURE_AZ_POSITION_PULSE_INPUT
  if (az_position_pulse_pin) {
    pinModeEnhanced(az_position_pulse_pin, INPUT);
    #ifdef OPTION_POSITION_PULSE_INPUT_PULLUPS
    digitalWriteEnhanced(az_position_pulse_pin, HIGH);
    #endif // OPTION_POSITION_PULSE_INPUT_PULLUPS
  }
  #endif // FEATURE_AZ_POSITION_PULSE_INPUT


  #ifdef FEATURE_EL_POSITION_PULSE_INPUT
  if (el_position_pulse_pin) {
    pinModeEnhanced(el_position_pulse_pin, INPUT);
    #ifdef OPTION_POSITION_PULSE_INPUT_PULLUPS
    digitalWriteEnhanced(el_position_pulse_pin, HIGH);
    #endif // OPTION_POSITION_PULSE_INPUT_PULLUPS
  }
  #endif // FEATURE_EL_POSITION_PULSE_INPUT

  #ifdef FEATURE_PARK
  if (button_park) {
    pinModeEnhanced(button_park, INPUT);
    digitalWriteEnhanced(button_park, HIGH);
  }
  #endif // FEATURE_PARK

  #ifdef FEATURE_ROTATION_INDICATOR_PIN
  if (rotation_indication_pin) {
    pinModeEnhanced(rotation_indication_pin, OUTPUT);
    digitalWriteEnhanced(rotation_indication_pin, ROTATION_INDICATOR_PIN_INACTIVE_STATE);
  }
  #endif // FEATURE_ROTATION_INDICATOR_PIN

  #ifdef FEATURE_PARK
  if (park_in_progress_pin) {
    pinModeEnhanced(park_in_progress_pin, OUTPUT);
    digitalWriteEnhanced(park_in_progress_pin, LOW);
  }
  if (parked_pin) {
    pinModeEnhanced(parked_pin, OUTPUT);
    digitalWriteEnhanced(parked_pin, LOW);
  }
  #endif // FEATURE_PARK

  if (blink_led) {
    pinModeEnhanced(blink_led, OUTPUT);
  }

  if (heading_reading_inhibit_pin) {
    pinModeEnhanced(heading_reading_inhibit_pin, INPUT);
  }

  #ifdef FEATURE_LIMIT_SENSE
  if (az_limit_sense_pin) {
    pinModeEnhanced(az_limit_sense_pin, INPUT);
    digitalWriteEnhanced(az_limit_sense_pin, HIGH);
  }
  #ifdef FEATURE_ELEVATION_CONTROL
  if (el_limit_sense_pin) {
    pinModeEnhanced(el_limit_sense_pin, INPUT);
    digitalWriteEnhanced(el_limit_sense_pin, HIGH);
  }
  #endif // FEATURE_ELEVATION_CONTROL
  #endif // FEATURE_LIMIT_SENSE

  #ifdef FEATURE_MOON_TRACKING
  if (moon_tracking_active_pin) {
    pinModeEnhanced(moon_tracking_active_pin, OUTPUT);
    digitalWriteEnhanced(moon_tracking_active_pin, LOW);
  }
  if (moon_tracking_activate_line) {
    pinModeEnhanced(moon_tracking_activate_line, INPUT);
    digitalWriteEnhanced(moon_tracking_activate_line, HIGH);
  }
  if (moon_tracking_button) {
    pinModeEnhanced(moon_tracking_button, INPUT);
    digitalWriteEnhanced(moon_tracking_button, HIGH);
  }
  #endif // FEATURE_MOON_TRACKING


  #ifdef FEATURE_SUN_TRACKING
  if (sun_tracking_active_pin) {
    pinModeEnhanced(sun_tracking_active_pin, OUTPUT);
    digitalWriteEnhanced(sun_tracking_active_pin, LOW);
  }
  if (sun_tracking_activate_line) {
    pinModeEnhanced(sun_tracking_activate_line, INPUT);
    digitalWriteEnhanced(sun_tracking_activate_line, HIGH);
  }
  if (sun_tracking_button) {
    pinModeEnhanced(sun_tracking_button, INPUT);
    digitalWriteEnhanced(sun_tracking_button, HIGH);
  }
  #endif // FEATURE_SUN_TRACKING
  
  
  #ifdef FEATURE_GPS
  if (gps_sync) {
    pinModeEnhanced(gps_sync, OUTPUT);
    digitalWriteEnhanced(gps_sync, LOW);
  }
  #endif //FEATURE_GPS

  #ifdef FEATURE_POWER_SWITCH
  pinModeEnhanced(power_switch, OUTPUT);
  digitalWriteEnhanced(power_switch, HIGH);
  #endif //FEATURE_POWER_SWITCH

  #ifdef FEATURE_STEPPER_MOTOR
  if (az_stepper_motor_pulse){
    pinModeEnhanced(az_stepper_motor_pulse, OUTPUT);
    digitalWriteEnhanced(az_stepper_motor_pulse, HIGH);
  }

  if (az_stepper_motor_direction){
    pinModeEnhanced(az_stepper_motor_direction, OUTPUT);
    digitalWriteEnhanced(az_stepper_motor_direction, LOW);
  }


  #ifdef FEATURE_ELEVATION_CONTROL
  if (el_stepper_motor_pulse){
    pinModeEnhanced(el_stepper_motor_pulse, OUTPUT);
    digitalWriteEnhanced(el_stepper_motor_pulse, HIGH);
  }

  if (el_stepper_motor_direction){
    pinModeEnhanced(el_stepper_motor_direction, OUTPUT);
    digitalWriteEnhanced(el_stepper_motor_direction, LOW);
  }
  #endif //FEATURE_ELEVATION_CONTROL
  #endif //FEATURE_STEPPER_MOTOR

  #ifdef FEATURE_EL_POSITION_MEMSIC_2125
  pinModeEnhanced(pin_memsic_2125_x, INPUT);
  pinModeEnhanced(pin_memsic_2125_y, INPUT);
  #endif //FEATURE_EL_POSITION_MEMSIC_2125

  #ifdef FEATURE_ANALOG_OUTPUT_PINS
  pinModeEnhanced(pin_analog_az_out, OUTPUT);
  digitalWriteEnhanced(pin_analog_az_out, LOW);
  #ifdef FEATURE_ELEVATION_CONTROL
  pinModeEnhanced(pin_analog_el_out, OUTPUT);
  digitalWriteEnhanced(pin_analog_el_out, LOW);
  #endif //FEATURE_ELEVATION_CONTROL
  #endif //FEATURE_ANALOG_OUTPUT_PINS


} /* initialize_pins */

// --------------------------------------------------------------

void initialize_serial(){

  #if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION) || defined(FEATURE_CLOCK)
  control_port = CONTROL_PORT_MAPPED_TO;
  control_port->begin(CONTROL_PORT_BAUD_RATE);
  #endif

  #ifdef FEATURE_REMOTE_UNIT_SLAVE
  control_port->print(F("CS"));
  control_port->println(CODE_VERSION);
  #endif // FEATURE_REMOTE_UNIT_SLAVE

  #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE)
  remote_unit_port = REMOTE_PORT_MAPPED_TO;
  remote_unit_port->begin(REMOTE_UNIT_PORT_BAUD_RATE);
  #endif

  #ifdef FEATURE_GPS
  gps_port = GPS_PORT_MAPPED_TO;
  gps_port->begin(GPS_PORT_BAUD_RATE);
  #ifdef GPS_MIRROR_PORT
  gps_mirror_port = GPS_MIRROR_PORT;
  gps_mirror_port->begin(GPS_MIRROR_PORT_BAUD_RATE);
  #endif //GPS_MIRROR_PORT
  #endif //FEATURE_GPS

} /* initialize_serial */

// --------------------------------------------------------------

#ifdef FEATURE_LCD_DISPLAY
void initialize_display(){

  byte start_row = 0;


  lcd.begin(LCD_COLUMNS, LCD_ROWS);

  #ifdef FEATURE_YOURDUINO_I2C_LCD
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(I2C_LCD_COLOR);
  #endif // FEATURE_YOURDUINO_I2C_LCD

  #ifdef FEATURE_ADAFRUIT_I2C_LCD
  lcd.setBacklight(I2C_LCD_COLOR);
  #endif // FEATURE_ADAFRUIT_I2C_LCD

  if (LCD_ROWS == 4){start_row = 1;}

  lcd.setCursor(((LCD_COLUMNS - 4) / 2), start_row);
  lcd.print("\x4B\x33\x4E\x47");                           
  lcd.setCursor(((LCD_COLUMNS - 16) / 2), start_row + 1);
  lcd.print("\x52\x6F\x74\x6F\x72\x20\x43\x6F\x6E\x74\x72\x6F\x6C\x6C\x65\x72");
  last_lcd_update = millis();

} /* initialize_display */
#endif /* ifdef FEATURE_LCD_DISPLAY */

// --------------------------------------------------------------

void initialize_peripherals(){

  #ifdef FEATURE_WIRE_SUPPORT
  Wire.begin();
  #endif

  #ifdef FEATURE_AZ_POSITION_HMC5883L
  compass = HMC5883L();
  int error;
  error = compass.SetScale(1.3); // Set the scale of the compass.
  #ifndef OPTION_DISABLE_HMC5883L_ERROR_CHECKING
  if (error != 0) {
    #if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)
    control_port->print(F("setup: compass error:"));
    control_port->println(compass.GetErrorText(error)); // check if there is an error, and print if so
    #endif
  }
  #endif //OPTION_DISABLE_HMC5883L_ERROR_CHECKING
  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  #ifndef OPTION_DISABLE_HMC5883L_ERROR_CHECKING
  if (error != 0) {
    #if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)
    control_port->print(F("setup: compass error:"));
    control_port->println(compass.GetErrorText(error)); // check if there is an error, and print if so
    #endif
  }
  #endif //OPTION_DISABLE_HMC5883L_ERROR_CHECKING
  #endif // FEATURE_AZ_POSITION_HMC5883L

  #ifdef FEATURE_EL_POSITION_ADXL345_USING_LOVE_ELECTRON_LIB
  accel = ADXL345();
  accel.SetRange(2, true);
  accel.EnableMeasurements();
  #endif // FEATURE_EL_POSITION_ADXL345_USING_LOVE_ELECTRON_LIB

  #ifdef FEATURE_EL_POSITION_ADXL345_USING_ADAFRUIT_LIB
  accel.begin();
  #endif // FEATURE_EL_POSITION_ADXL345_USING_ADAFRUIT_LIB

  #ifdef FEATURE_JOYSTICK_CONTROL
  pinModeEnhanced(pin_joystick_x, INPUT);
  pinModeEnhanced(pin_joystick_y, INPUT);
  #endif // FEATURE_JOYSTICK_CONTROL

  #if defined(FEATURE_EL_POSITION_ADAFRUIT_LSM303) || defined(FEATURE_AZ_POSITION_ADAFRUIT_LSM303)
  if (!lsm.begin()) {
    #if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)
    control_port->println(F("setup: LSM303 error"));
    #endif
  }
  #endif // FEATURE_EL_POSITION_ADAFRUIT_LSM303 || FEATURE_AZ_POSITION_ADAFRUIT_LSM303

  #ifdef FEATURE_AZ_POSITION_HH12_AS5045_SSI
  azimuth_hh12.initialize(az_hh12_clock_pin, az_hh12_cs_pin, az_hh12_data_pin);
  #endif // FEATURE_AZ_POSITION_HH12_AS5045_SSI

  #ifdef FEATURE_EL_POSITION_HH12_AS5045_SSI
  elevation_hh12.initialize(el_hh12_clock_pin, el_hh12_cs_pin, el_hh12_data_pin);
  #endif // FEATURE_EL_POSITION_HH12_AS5045_SSI

  #ifdef FEATURE_RTC_DS1307
  rtc.begin();
  #endif // FEATURE_RTC_DS1307

  #ifdef FEATURE_ETHERNET
  Ethernet.begin(mac, ip, gateway, subnet);
  ethernetserver0.begin();
  #endif //FEATURE_ETHERNET

} /* initialize_peripherals */


// --------------------------------------------------------------
void submit_request(byte axis, byte request, int parm, byte called_by){

  #ifdef DEBUG_SUBMIT_REQUEST
  debug_print("submit_request: ");
  debug_print_int(called_by);
  debug_print(" ");
  #endif // DEBUG_SUBMIT_REQUEST

  #ifdef FEATURE_PARK
  park_status = NOT_PARKED;
  #endif // FEATURE_PARK

  if (axis == AZ) {
    #ifdef DEBUG_SUBMIT_REQUEST
    debug_print("AZ "); 
    #endif // DEBUG_SUBMIT_REQUEST
    az_request = request;
    az_request_parm = parm;
    az_request_queue_state = IN_QUEUE;
  }

  #ifdef FEATURE_ELEVATION_CONTROL
  if (axis == EL) {
    #ifdef DEBUG_SUBMIT_REQUEST
    debug_print("EL ");
    #endif // DEBUG_SUBMIT_REQUEST
    el_request = request;
    el_request_parm = parm;
    el_request_queue_state = IN_QUEUE;
  }
  #endif // FEATURE_ELEVATION_CONTROL

  #ifdef DEBUG_SUBMIT_REQUEST
  switch(request){
    case 0: debug_print("REQUEST_STOP");break;
    case 1: debug_print("REQUEST_AZIMUTH");break;
    case 2: debug_print("REQUEST_AZIMUTH_RAW");break;
    case 3: debug_print("REQUEST_CW");break;
    case 4: debug_print("REQUEST_CCW");break;
    case 5: debug_print("REQUEST_UP");break;
    case 6: debug_print("REQUEST_DOWN");break;
    case 7: debug_print("REQUEST_ELEVATION");break;
    case 8: debug_print("REQUEST_KILL");break;
  }
  debug_print(" ");
  debug_print_int(parm);
  debug_println("");
  #endif // DEBUG_SUBMIT_REQUEST  

} /* submit_request */
// --------------------------------------------------------------
void service_rotation(){

  static byte az_direction_change_flag = 0;
  static byte az_initial_slow_down_voltage = 0;

  #ifdef FEATURE_ELEVATION_CONTROL
  static byte el_direction_change_flag = 0;
  static byte el_initial_slow_down_voltage = 0;
  #endif // FEATURE_ELEVATION_CONTROL

  if (az_state == INITIALIZE_NORMAL_CW) {
    update_az_variable_outputs(normal_az_speed_voltage);
    rotator(ACTIVATE, CW);
    az_state = NORMAL_CW;
  }

  if (az_state == INITIALIZE_NORMAL_CCW) {
    update_az_variable_outputs(normal_az_speed_voltage);
    rotator(ACTIVATE, CCW);
    az_state = NORMAL_CCW;
  }

  if (az_state == INITIALIZE_SLOW_START_CW) {
    update_az_variable_outputs(AZ_SLOW_START_STARTING_PWM);
    rotator(ACTIVATE, CW);
    az_slowstart_start_time = millis();
    az_last_step_time = 0;
    az_slow_start_step = 0;
    az_state = SLOW_START_CW;
    #ifdef DEBUG_SERVICE_ROTATION
    debug_print("service_rotation: INITIALIZE_SLOW_START_CW -> SLOW_START_CW");
    #endif // DEBUG_SERVICE_ROTATION
  }

  if (az_state == INITIALIZE_SLOW_START_CCW) {
    update_az_variable_outputs(AZ_SLOW_START_STARTING_PWM);
    rotator(ACTIVATE, CCW);
    az_slowstart_start_time = millis();
    az_last_step_time = 0;
    az_slow_start_step = 0;
    az_state = SLOW_START_CCW;
    #ifdef DEBUG_SERVICE_ROTATION
    debug_print("service_rotation: INITIALIZE_SLOW_START_CCW -> SLOW_START_CCW");
    #endif // DEBUG_SERVICE_ROTATION
  }

  if (az_state == INITIALIZE_TIMED_SLOW_DOWN_CW) {
    az_direction_change_flag = 0;
    az_timed_slow_down_start_time = millis();
    az_last_step_time = millis();
    az_slow_down_step = AZ_SLOW_DOWN_STEPS - 1;
    az_state = TIMED_SLOW_DOWN_CW;
  }

  if (az_state == INITIALIZE_TIMED_SLOW_DOWN_CCW) {
    az_direction_change_flag = 0;
    az_timed_slow_down_start_time = millis();
    az_last_step_time = millis();
    az_slow_down_step = AZ_SLOW_DOWN_STEPS - 1;
    az_state = TIMED_SLOW_DOWN_CCW;
  }

  if (az_state == INITIALIZE_DIR_CHANGE_TO_CW) {
    az_direction_change_flag = 1;
    az_timed_slow_down_start_time = millis();
    az_last_step_time = millis();
    az_slow_down_step = AZ_SLOW_DOWN_STEPS - 1;
    az_state = TIMED_SLOW_DOWN_CCW;
  }

  if (az_state == INITIALIZE_DIR_CHANGE_TO_CCW) {
    az_direction_change_flag = 1;
    az_timed_slow_down_start_time = millis();
    az_last_step_time = millis();
    az_slow_down_step = AZ_SLOW_DOWN_STEPS - 1;
    az_state = TIMED_SLOW_DOWN_CW;
  }

  // slow start-------------------------------------------------------------------------------------------------
  if ((az_state == SLOW_START_CW) || (az_state == SLOW_START_CCW)) {
    if ((millis() - az_slowstart_start_time) >= AZ_SLOW_START_UP_TIME) {  // is it time to end slow start?
      #ifdef DEBUG_SERVICE_ROTATION
      debug_print("service_rotation: NORMAL_C");
      #endif // DEBUG_SERVICE_ROTATION
      if (az_state == SLOW_START_CW) {
        az_state = NORMAL_CW;
        #ifdef DEBUG_SERVICE_ROTATION
        debug_print("W");
        #endif // DEBUG_SERVICE_ROTATION
      } else {
        az_state = NORMAL_CCW;
        #ifdef DEBUG_SERVICE_ROTATION
        debug_print("CW");
        #endif // DEBUG_SERVICE_ROTATION
      }
      update_az_variable_outputs(normal_az_speed_voltage);
    } else {  // it's not time to end slow start yet, but let's check if it's time to step up the speed voltage
      if (((millis() - az_last_step_time) > (AZ_SLOW_START_UP_TIME / AZ_SLOW_START_STEPS)) && (normal_az_speed_voltage > AZ_SLOW_START_STARTING_PWM)) {
        #ifdef DEBUG_SERVICE_ROTATION
        debug_print("service_rotation: step up: ");
        debug_print_int(az_slow_start_step);
        debug_print(" pwm: ");
        debug_print_int((int)(AZ_SLOW_START_STARTING_PWM + ((normal_az_speed_voltage - AZ_SLOW_START_STARTING_PWM) * ((float)az_slow_start_step / (float)(AZ_SLOW_START_STEPS - 1)))));
        debug_println("");
        #endif // DEBUG_SERVICE_ROTATION
        update_az_variable_outputs((AZ_SLOW_START_STARTING_PWM + ((normal_az_speed_voltage - AZ_SLOW_START_STARTING_PWM) * ((float)az_slow_start_step / (float)(AZ_SLOW_START_STEPS - 1)))));
        az_last_step_time = millis();
        az_slow_start_step++;
      }
    }
  } // ((az_state == SLOW_START_CW) || (az_state == SLOW_START_CCW))


  // timed slow down ------------------------------------------------------------------------------------------------------
  if (((az_state == TIMED_SLOW_DOWN_CW) || (az_state == TIMED_SLOW_DOWN_CCW)) && ((millis() - az_last_step_time) >= (TIMED_SLOW_DOWN_TIME / AZ_SLOW_DOWN_STEPS))) {
    #ifdef DEBUG_SERVICE_ROTATION
    debug_print("service_rotation: TIMED_SLOW_DOWN step down: ");
    debug_print_int(az_slow_down_step);
    debug_print(" pwm: ");
    debug_print_int((int)(normal_az_speed_voltage * ((float)az_slow_down_step / (float)AZ_SLOW_DOWN_STEPS)));
    debug_println("");
    #endif // DEBUG_SERVICE_ROTATION
    update_az_variable_outputs((int)(normal_az_speed_voltage * ((float)az_slow_down_step / (float)AZ_SLOW_DOWN_STEPS)));
    az_last_step_time = millis();
    if (az_slow_down_step > 0) {az_slow_down_step--;}

    if (az_slow_down_step == 0) { // is it time to exit timed slow down?
      #ifdef DEBUG_SERVICE_ROTATION
      debug_print("service_rotation: TIMED_SLOW_DOWN->IDLE");
      #endif // DEBUG_SERVICE_ROTATION
      rotator(DEACTIVATE, CW);
      rotator(DEACTIVATE, CCW);        
      if (az_direction_change_flag) {
        if (az_state == TIMED_SLOW_DOWN_CW) {
          //rotator(ACTIVATE, CCW);
          if (az_slowstart_active) {
            az_state = INITIALIZE_SLOW_START_CCW;
          } else { az_state = NORMAL_CCW; };
          az_direction_change_flag = 0;
        }
        if (az_state == TIMED_SLOW_DOWN_CCW) {
          //rotator(ACTIVATE, CW);
          if (az_slowstart_active) {
            az_state = INITIALIZE_SLOW_START_CW;
          } else { az_state = NORMAL_CW; };
          az_direction_change_flag = 0;
        }
      } else {
        az_state = IDLE;
        az_request_queue_state = NONE;
      }
    }

  }  // ((az_state == TIMED_SLOW_DOWN_CW) || (az_state == TIMED_SLOW_DOWN_CCW))



  // slow down ---------------------------------------------------------------------------------------------------------------
  if ((az_state == SLOW_DOWN_CW) || (az_state == SLOW_DOWN_CCW)) {

    // is it time to do another step down?
    if (abs((target_raw_azimuth - raw_azimuth) / HEADING_MULTIPLIER) <= (((float)SLOW_DOWN_BEFORE_TARGET_AZ * ((float)az_slow_down_step / (float)AZ_SLOW_DOWN_STEPS)))) {
      #ifdef DEBUG_SERVICE_ROTATION
      debug_print("service_rotation: step down: ");
      debug_print_int(az_slow_down_step);
      debug_print(" pwm: ");
      debug_print_int((int)(AZ_SLOW_DOWN_PWM_STOP + ((az_initial_slow_down_voltage - AZ_SLOW_DOWN_PWM_STOP) * ((float)az_slow_down_step / (float)AZ_SLOW_DOWN_STEPS))));
      debug_println("");
      #endif // DEBUG_SERVICE_ROTATION
      update_az_variable_outputs((AZ_SLOW_DOWN_PWM_STOP + ((az_initial_slow_down_voltage - AZ_SLOW_DOWN_PWM_STOP) * ((float)az_slow_down_step / (float)AZ_SLOW_DOWN_STEPS))));
      if (az_slow_down_step > 0) {az_slow_down_step--;}
    }
  }  // ((az_state == SLOW_DOWN_CW) || (az_state == SLOW_DOWN_CCW))

  // normal -------------------------------------------------------------------------------------------------------------------
  // if slow down is enabled, see if we're ready to go into slowdown
  if (((az_state == NORMAL_CW) || (az_state == SLOW_START_CW) || (az_state == NORMAL_CCW) || (az_state == SLOW_START_CCW)) &&
      (az_request_queue_state == IN_PROGRESS_TO_TARGET) && az_slowdown_active && (abs((target_raw_azimuth - raw_azimuth) / HEADING_MULTIPLIER) <= SLOW_DOWN_BEFORE_TARGET_AZ)) {

    byte az_state_was = az_state;

    #ifdef DEBUG_SERVICE_ROTATION
    debug_print("service_rotation: SLOW_DOWN_C");
    #endif // DEBUG_SERVICE_ROTATION
    az_slow_down_step = AZ_SLOW_DOWN_STEPS - 1;
    if ((az_state == NORMAL_CW) || (az_state == SLOW_START_CW)) {
      az_state = SLOW_DOWN_CW;
      #ifdef DEBUG_SERVICE_ROTATION
      debug_print("W");
      #endif // DEBUG_SERVICE_ROTATION
    } else {
      az_state = SLOW_DOWN_CCW;
      #ifdef DEBUG_SERVICE_ROTATION
      debug_print("CW");
      #endif // DEBUG_SERVICE_ROTATION
    }
    //aaaaaa
    if ((az_state_was == SLOW_START_CW) || (az_state_was == SLOW_START_CCW)){
      az_initial_slow_down_voltage = (AZ_INITIALLY_IN_SLOW_DOWN_PWM);
      update_az_variable_outputs(az_initial_slow_down_voltage);
      #ifdef DEBUG_SERVICE_ROTATION
      debug_print(" SLOW_START -> SLOW_DOWN az_initial_slow_down_voltage:");
      debug_print_int(az_initial_slow_down_voltage);
      debug_print(" ");
      #endif // DEBUG_SERVICE_ROTATION
    } else {
      if (AZ_SLOW_DOWN_PWM_START < current_az_speed_voltage) {
        update_az_variable_outputs(AZ_SLOW_DOWN_PWM_START);
        az_initial_slow_down_voltage = AZ_SLOW_DOWN_PWM_START;
      } else {
        az_initial_slow_down_voltage = current_az_speed_voltage;
      }
    }

  }

  // check rotation target --------------------------------------------------------------------------------------------------------
  if ((az_state != IDLE) && (az_request_queue_state == IN_PROGRESS_TO_TARGET) ) {
    if ((az_state == NORMAL_CW) || (az_state == SLOW_START_CW) || (az_state == SLOW_DOWN_CW)) {
      if ((abs(raw_azimuth - target_raw_azimuth) < (AZIMUTH_TOLERANCE * HEADING_MULTIPLIER)) || ((raw_azimuth > target_raw_azimuth) && ((raw_azimuth - target_raw_azimuth) < ((AZIMUTH_TOLERANCE + 5) * HEADING_MULTIPLIER)))) {
        delay(50);
        read_azimuth(0);
        if ((abs(raw_azimuth - target_raw_azimuth) < (AZIMUTH_TOLERANCE * HEADING_MULTIPLIER)) || ((raw_azimuth > target_raw_azimuth) && ((raw_azimuth - target_raw_azimuth) < ((AZIMUTH_TOLERANCE + 5) * HEADING_MULTIPLIER)))) {
          rotator(DEACTIVATE, CW);
          rotator(DEACTIVATE, CCW);
          az_state = IDLE;
          az_request_queue_state = NONE;
          #ifdef DEBUG_SERVICE_ROTATION
          debug_print("service_rotation: IDLE");
          #endif // DEBUG_SERVICE_ROTATION

          #if defined(FEATURE_PARK) && !defined(FEATURE_ELEVATION_CONTROL)
          if (park_status == PARK_INITIATED) {
            park_status = PARKED;
          }
          #endif // defined(FEATURE_PARK) && !defined(FEATURE_ELEVATION_CONTROL)

          #if defined(FEATURE_PARK) && defined(FEATURE_ELEVATION_CONTROL)
          if ((park_status == PARK_INITIATED) && (el_state == IDLE)) {
            park_status = PARKED;
          }
          #endif // defined(FEATURE_PARK) && !defined(FEATURE_ELEVATION_CONTROL)

        }
      }
    } else {
      if ((abs(raw_azimuth - target_raw_azimuth) < (AZIMUTH_TOLERANCE * HEADING_MULTIPLIER)) || ((raw_azimuth < target_raw_azimuth) && ((target_raw_azimuth - raw_azimuth) < ((AZIMUTH_TOLERANCE + 5) * HEADING_MULTIPLIER)))) {
        delay(50);
        read_azimuth(0);
        if ((abs(raw_azimuth - target_raw_azimuth) < (AZIMUTH_TOLERANCE * HEADING_MULTIPLIER)) || ((raw_azimuth < target_raw_azimuth) && ((target_raw_azimuth - raw_azimuth) < ((AZIMUTH_TOLERANCE + 5) * HEADING_MULTIPLIER)))) {
          rotator(DEACTIVATE, CW);
          rotator(DEACTIVATE, CCW);
          az_state = IDLE;
          az_request_queue_state = NONE;
          #ifdef DEBUG_SERVICE_ROTATION
          debug_print("service_rotation: IDLE");
          #endif // DEBUG_SERVICE_ROTATION

          #if defined(FEATURE_PARK) && !defined(FEATURE_ELEVATION_CONTROL)
          if (park_status == PARK_INITIATED) {
            park_status = PARKED;
          }
          #endif // defined(FEATURE_PARK) && !defined(FEATURE_ELEVATION_CONTROL)

          #if defined(FEATURE_PARK) && defined(FEATURE_ELEVATION_CONTROL)
          if ((park_status == PARK_INITIATED) && (el_state == IDLE)) {
            park_status = PARKED;
          }
          #endif // defined(FEATURE_PARK) && !defined(FEATURE_ELEVATION_CONTROL)

        }
      }
    }
  }



    #ifdef FEATURE_ELEVATION_CONTROL
  if (el_state == INITIALIZE_NORMAL_UP) {
    update_el_variable_outputs(normal_el_speed_voltage);
    rotator(ACTIVATE, UP);
    el_state = NORMAL_UP;
  }

  if (el_state == INITIALIZE_NORMAL_DOWN) {
    update_el_variable_outputs(normal_el_speed_voltage);
    rotator(ACTIVATE, DOWN);
    el_state = NORMAL_DOWN;
  }

  if (el_state == INITIALIZE_SLOW_START_UP) {
    update_el_variable_outputs(EL_SLOW_START_STARTING_PWM);
    rotator(ACTIVATE, UP);
    el_slowstart_start_time = millis();
    el_last_step_time = 0;
    el_slow_start_step = 0;
    el_state = SLOW_START_UP;
    #ifdef DEBUG_SERVICE_ROTATION
    debug_print("service_rotation: INITIALIZE_SLOW_START_UP -> SLOW_START_UP");
    #endif // DEBUG_SERVICE_ROTATION
  }

  if (el_state == INITIALIZE_SLOW_START_DOWN) {
    update_el_variable_outputs(EL_SLOW_START_STARTING_PWM);
    rotator(ACTIVATE, DOWN);
    el_slowstart_start_time = millis();
    el_last_step_time = 0;
    el_slow_start_step = 0;
    el_state = SLOW_START_DOWN;
    #ifdef DEBUG_SERVICE_ROTATION
    debug_print("service_rotation: INITIALIZE_SLOW_START_DOWN -> SLOW_START_DOWN");
    #endif // DEBUG_SERVICE_ROTATION
  }

  if (el_state == INITIALIZE_TIMED_SLOW_DOWN_UP) {
    el_direction_change_flag = 0;
    el_timed_slow_down_start_time = millis();
    el_last_step_time = millis();
    el_slow_down_step = EL_SLOW_DOWN_STEPS - 1;
    el_state = TIMED_SLOW_DOWN_UP;
  }

  if (el_state == INITIALIZE_TIMED_SLOW_DOWN_DOWN) {
    el_direction_change_flag = 0;
    el_timed_slow_down_start_time = millis();
    el_last_step_time = millis();
    el_slow_down_step = EL_SLOW_DOWN_STEPS - 1;
    el_state = TIMED_SLOW_DOWN_DOWN;
  }

  if (el_state == INITIALIZE_DIR_CHANGE_TO_UP) {
    el_direction_change_flag = 1;
    el_timed_slow_down_start_time = millis();
    el_last_step_time = millis();
    el_slow_down_step = EL_SLOW_DOWN_STEPS - 1;
    el_state = TIMED_SLOW_DOWN_DOWN;
  }

  if (el_state == INITIALIZE_DIR_CHANGE_TO_DOWN) {
    el_direction_change_flag = 1;
    el_timed_slow_down_start_time = millis();
    el_last_step_time = millis();
    el_slow_down_step = EL_SLOW_DOWN_STEPS - 1;
    el_state = TIMED_SLOW_DOWN_UP;
  }

  // slow start-------------------------------------------------------------------------------------------------
  if ((el_state == SLOW_START_UP) || (el_state == SLOW_START_DOWN)) {
    if ((millis() - el_slowstart_start_time) >= EL_SLOW_START_UP_TIME) {  // is it time to end slow start?
      #ifdef DEBUG_SERVICE_ROTATION
      debug_print("service_rotation: NORMAL_");
      #endif // DEBUG_SERVICE_ROTATION
      if (el_state == SLOW_START_UP) {
        el_state = NORMAL_UP;
        #ifdef DEBUG_SERVICE_ROTATION
        debug_print("UP");
        #endif // DEBUG_SERVICE_ROTATION
      } else {
        el_state = NORMAL_DOWN;
        #ifdef DEBUG_SERVICE_ROTATION
        debug_print("DOWN");
        #endif // DEBUG_SERVICE_ROTATION
      }
      update_el_variable_outputs(normal_el_speed_voltage);
    } else {  // it's not time to end slow start yet, but let's check if it's time to step up the speed voltage
      if (((millis() - el_last_step_time) > (EL_SLOW_START_UP_TIME / EL_SLOW_START_STEPS)) && (normal_el_speed_voltage > EL_SLOW_START_STARTING_PWM)) {
        #ifdef DEBUG_SERVICE_ROTATION
        debug_print("service_rotation: step up: ");
        debug_print_int(el_slow_start_step);
        debug_print(" pwm: ");
        debug_print_int((int)(EL_SLOW_START_STARTING_PWM + ((normal_el_speed_voltage - EL_SLOW_START_STARTING_PWM) * ((float)el_slow_start_step / (float)(EL_SLOW_START_STEPS - 1)))));
        debug_println("");
        #endif // DEBUG_SERVICE_ROTATION
        update_el_variable_outputs((EL_SLOW_START_STARTING_PWM + ((normal_el_speed_voltage - EL_SLOW_START_STARTING_PWM) * ((float)el_slow_start_step / (float)(EL_SLOW_START_STEPS - 1)))));
        el_last_step_time = millis();
        el_slow_start_step++;
      }
    }
  } // ((el_state == SLOW_START_UP) || (el_state == SLOW_START_DOWN))


  // timed slow down ------------------------------------------------------------------------------------------------------
  if (((el_state == TIMED_SLOW_DOWN_UP) || (el_state == TIMED_SLOW_DOWN_DOWN)) && ((millis() - el_last_step_time) >= (TIMED_SLOW_DOWN_TIME / EL_SLOW_DOWN_STEPS))) {
    #ifdef DEBUG_SERVICE_ROTATION
    debug_print("service_rotation: TIMED_SLOW_DOWN step down: ");
    debug_print_int(el_slow_down_step);
    debug_print(" pwm: ");
    debug_print_int((int)(normal_el_speed_voltage * ((float)el_slow_down_step / (float)EL_SLOW_DOWN_STEPS)));
    debug_println("");
    #endif // DEBUG_SERVICE_ROTATION
    update_el_variable_outputs((int)(normal_el_speed_voltage * ((float)el_slow_down_step / (float)EL_SLOW_DOWN_STEPS)));
    el_last_step_time = millis();
    if (el_slow_down_step > 0) {el_slow_down_step--;}

    if (el_slow_down_step == 0) { // is it time to exit timed slow down?
      #ifdef DEBUG_SERVICE_ROTATION
      debug_print("service_rotation: TIMED_SLOW_DOWN->IDLE");
      #endif // DEBUG_SERVICE_ROTATION
      rotator(DEACTIVATE, UP);
      rotator(DEACTIVATE, DOWN);
      if (el_direction_change_flag) {
        if (el_state == TIMED_SLOW_DOWN_UP) {
          if (el_slowstart_active) {
            el_state = INITIALIZE_SLOW_START_DOWN;
          } else { el_state = NORMAL_DOWN; };
          el_direction_change_flag = 0;
        }
        if (el_state == TIMED_SLOW_DOWN_DOWN) {
          if (el_slowstart_active) {
            el_state = INITIALIZE_SLOW_START_UP;
          } else { el_state = NORMAL_UP; };
          el_direction_change_flag = 0;
        }
      } else {
        el_state = IDLE;
        el_request_queue_state = NONE;
      }
    }

  }  // ((el_state == TIMED_SLOW_DOWN_UP) || (el_state == TIMED_SLOW_DOWN_DOWN))



  // slow down ---------------------------------------------------------------------------------------------------------------
  if ((el_state == SLOW_DOWN_UP) || (el_state == SLOW_DOWN_DOWN)) {
    // is it time to do another step down?
    if (abs((target_elevation - elevation) / HEADING_MULTIPLIER) <= (((float)SLOW_DOWN_BEFORE_TARGET_EL * ((float)el_slow_down_step / (float)EL_SLOW_DOWN_STEPS)))) {
      #ifdef DEBUG_SERVICE_ROTATION
      debug_print("service_rotation: step down: ");
      debug_print_int(el_slow_down_step);
      debug_print(" pwm: ");
      debug_print_int((int)(EL_SLOW_DOWN_PWM_STOP + ((el_initial_slow_down_voltage - EL_SLOW_DOWN_PWM_STOP) * ((float)el_slow_down_step / (float)EL_SLOW_DOWN_STEPS))));
      debug_println("");
      #endif // DEBUG_SERVICE_ROTATION
      update_el_variable_outputs((EL_SLOW_DOWN_PWM_STOP + ((el_initial_slow_down_voltage - EL_SLOW_DOWN_PWM_STOP) * ((float)el_slow_down_step / (float)EL_SLOW_DOWN_STEPS))));
      if (el_slow_down_step > 0) {el_slow_down_step--;}
    }
  }  // ((el_state == SLOW_DOWN_UP) || (el_state == SLOW_DOWN_DOWN))

  // normal -------------------------------------------------------------------------------------------------------------------
  // if slow down is enabled, see if we're ready to go into slowdown
  if (((el_state == NORMAL_UP) || (el_state == SLOW_START_UP) || (el_state == NORMAL_DOWN) || (el_state == SLOW_START_DOWN)) &&
      (el_request_queue_state == IN_PROGRESS_TO_TARGET) && el_slowdown_active && (abs((target_elevation - elevation) / HEADING_MULTIPLIER) <= SLOW_DOWN_BEFORE_TARGET_EL)) {
    
    byte el_state_was = el_state;


    #ifdef DEBUG_SERVICE_ROTATION
    debug_print("service_rotation: SLOW_DOWN_");
    #endif // DEBUG_SERVICE_ROTATION
    el_slow_down_step = EL_SLOW_DOWN_STEPS - 1;
    if ((el_state == NORMAL_UP) || (el_state == SLOW_START_UP)) {
      el_state = SLOW_DOWN_UP;
      #ifdef DEBUG_SERVICE_ROTATION
      debug_print("UP");
      #endif // DEBUG_SERVICE_ROTATION
    } else {
      el_state = SLOW_DOWN_DOWN;
      #ifdef DEBUG_SERVICE_ROTATION
      debug_print("DOWN");
      #endif // DEBUG_SERVICE_ROTATION
    }

    if ((el_state_was == SLOW_START_UP) || (el_state_was == SLOW_START_DOWN)){
      el_initial_slow_down_voltage = EL_INITIALLY_IN_SLOW_DOWN_PWM;
      update_el_variable_outputs(el_initial_slow_down_voltage);
      #ifdef DEBUG_SERVICE_ROTATION
      debug_print(" SLOW_START -> SLOW_DOWN el_initial_slow_down_voltage:");
      debug_print_int(el_initial_slow_down_voltage);
      debug_print(" ");
      #endif // DEBUG_SERVICE_ROTATION    

    } else {
      if (EL_SLOW_DOWN_PWM_START < current_el_speed_voltage) {
        update_el_variable_outputs(EL_SLOW_DOWN_PWM_START);
        el_initial_slow_down_voltage = EL_SLOW_DOWN_PWM_START;
      } else {
        el_initial_slow_down_voltage = current_el_speed_voltage;
      }
    }
  }

  // check rotation target --------------------------------------------------------------------------------------------------------
  if ((el_state != IDLE) && (el_request_queue_state == IN_PROGRESS_TO_TARGET) ) {
    if ((el_state == NORMAL_UP) || (el_state == SLOW_START_UP) || (el_state == SLOW_DOWN_UP)) {
      if ((abs(elevation - target_elevation) < (ELEVATION_TOLERANCE * HEADING_MULTIPLIER)) || ((elevation > target_elevation) && ((elevation - target_elevation) < ((ELEVATION_TOLERANCE + 5) * HEADING_MULTIPLIER)))) {
        delay(50);
        read_elevation(0);
        if ((abs(elevation - target_elevation) < (ELEVATION_TOLERANCE * HEADING_MULTIPLIER)) || ((elevation > target_elevation) && ((elevation - target_elevation) < ((ELEVATION_TOLERANCE + 5) * HEADING_MULTIPLIER)))) {
          rotator(DEACTIVATE, UP);
          rotator(DEACTIVATE, DOWN);
          el_state = IDLE;
          el_request_queue_state = NONE;
          #ifdef DEBUG_SERVICE_ROTATION
          debug_print("service_rotation: IDLE");
          #endif // DEBUG_SERVICE_ROTATION

          #if defined(FEATURE_PARK)
          if ((park_status == PARK_INITIATED) && (az_state == IDLE)) {
            park_status = PARKED;
          }
          #endif // defined(FEATURE_PARK)

        }
      }
    } else {
      if ((abs(elevation - target_elevation) < (ELEVATION_TOLERANCE * HEADING_MULTIPLIER)) || ((elevation < target_elevation) && ((target_elevation - elevation) < ((ELEVATION_TOLERANCE + 5) * HEADING_MULTIPLIER)))) {
        delay(50);
        read_elevation(0);
        if ((abs(elevation - target_elevation) < (ELEVATION_TOLERANCE * HEADING_MULTIPLIER)) || ((elevation < target_elevation) && ((target_elevation - elevation) < ((ELEVATION_TOLERANCE + 5) * HEADING_MULTIPLIER)))) {
          rotator(DEACTIVATE, UP);
          rotator(DEACTIVATE, DOWN);
          el_state = IDLE;
          el_request_queue_state = NONE;
          #ifdef DEBUG_SERVICE_ROTATION
          debug_print("service_rotation: IDLE");
          #endif // DEBUG_SERVICE_ROTATION

          #if defined(FEATURE_PARK)
          if ((park_status == PARK_INITIATED) && (az_state == IDLE)) {
            park_status = PARKED;
          }
          #endif // defined(FEATURE_PARK)
        }
      }
    }
  }




  #endif // FEATURE_ELEVATION_CONTROL



} /* service_rotation */
// --------------------------------------------------------------
void stop_all_tracking(){


  #ifdef FEATURE_MOON_TRACKING
  moon_tracking_active = 0;
  #endif // FEATURE_MOON_TRACKING
  #ifdef FEATURE_SUN_TRACKING
  sun_tracking_active = 0;
  #endif // FEATURE_SUN_TRACKING

}

// --------------------------------------------------------------
void service_request_queue(){

// xxxx

  int work_target_raw_azimuth = 0;
  byte direction_to_go = 0;
  byte within_tolerance_flag = 0;

  if (az_request_queue_state == IN_QUEUE) {


    #ifdef FEATURE_POWER_SWITCH
    last_activity_time = millis();
    #endif //FEATURE_POWER_SWITCH

    #ifdef DEBUG_SERVICE_REQUEST_QUEUE
    debug_print("service_request_queue: AZ ");
    #endif // DEBUG_SERVICE_REQUEST_QUEUE

    switch (az_request) {
      case (REQUEST_STOP):
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        debug_print("REQUEST_STOP");
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        stop_all_tracking();
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        if (az_state != IDLE) {
          if (az_slowdown_active) {
            if ((az_state == TIMED_SLOW_DOWN_CW) || (az_state == TIMED_SLOW_DOWN_CCW) || (az_state == SLOW_DOWN_CW) || (az_state == SLOW_DOWN_CCW)) {  // if we're already in timed slow down and we get another stop, do a hard stop
              rotator(DEACTIVATE, CW);
              rotator(DEACTIVATE, CCW);
              az_state = IDLE;
              az_request_queue_state = NONE;
            }
            if ((az_state == SLOW_START_CW) || (az_state == NORMAL_CW)) {
              az_state = INITIALIZE_TIMED_SLOW_DOWN_CW;
              az_request_queue_state = IN_PROGRESS_TIMED;
              az_last_rotate_initiation = millis();
            }
            if ((az_state == SLOW_START_CCW) || (az_state == NORMAL_CCW)) {
              az_state = INITIALIZE_TIMED_SLOW_DOWN_CCW;
              az_request_queue_state = IN_PROGRESS_TIMED;
              az_last_rotate_initiation = millis();
            }

          } else {
            rotator(DEACTIVATE, CW);
            rotator(DEACTIVATE, CCW);
            az_state = IDLE;
            az_request_queue_state = NONE;
          }
        } else {
          az_request_queue_state = NONE; // nothing to do - we clear the queue
        }
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println();
        }
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        break; // REQUEST_STOP

      case (REQUEST_AZIMUTH):
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        debug_print("REQUEST_AZIMUTH");
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        if ((az_request_parm >= 0) && (az_request_parm <= (360 * HEADING_MULTIPLIER))) {
          target_azimuth = az_request_parm;
          target_raw_azimuth = az_request_parm;
          if (target_azimuth == (360 * HEADING_MULTIPLIER)) {
            target_azimuth = 0;
          }
          if ((target_azimuth > (azimuth - (AZIMUTH_TOLERANCE * HEADING_MULTIPLIER))) && (target_azimuth < (azimuth + (AZIMUTH_TOLERANCE * HEADING_MULTIPLIER)))) {
            #ifdef DEBUG_SERVICE_REQUEST_QUEUE
            debug_print(" request within tolerance");
            #endif // DEBUG_SERVICE_REQUEST_QUEUE
            within_tolerance_flag = 1;
            az_request_queue_state = NONE;
          } else {  // target azimuth is not within tolerance, we need to rotate
            #ifdef DEBUG_SERVICE_REQUEST_QUEUE
            debug_print(" ->A");
            #endif // DEBUG_SERVICE_REQUEST_QUEUE
            work_target_raw_azimuth = target_azimuth;
            #ifdef DEBUG_SERVICE_REQUEST_QUEUE
            debug_print(" work_target_raw_azimuth:");
            debug_print_int(work_target_raw_azimuth / HEADING_MULTIPLIER);
            debug_print(" azimuth_starting_point:");
            debug_print_int(azimuth_starting_point);
            debug_print(" ");
            #endif // DEBUG_SERVICE_REQUEST_QUEUE

            if (work_target_raw_azimuth < (azimuth_starting_point * HEADING_MULTIPLIER)) {
              work_target_raw_azimuth = work_target_raw_azimuth + (360 * HEADING_MULTIPLIER);
              target_raw_azimuth = work_target_raw_azimuth;
              #ifdef DEBUG_SERVICE_REQUEST_QUEUE
              debug_print("->B");
              #endif // DEBUG_SERVICE_REQUEST_QUEUE
            }
            if ((work_target_raw_azimuth + (360 * HEADING_MULTIPLIER)) < ((azimuth_starting_point + azimuth_rotation_capability) * HEADING_MULTIPLIER)) { // is there a second possible heading in overlap?
              if (abs(raw_azimuth - work_target_raw_azimuth) < abs((work_target_raw_azimuth + (360 * HEADING_MULTIPLIER)) - raw_azimuth)) { // is second possible heading closer?
                #ifdef DEBUG_SERVICE_REQUEST_QUEUE
                debug_print("->C");
                #endif // DEBUG_SERVICE_REQUEST_QUEUE
                if (work_target_raw_azimuth  > raw_azimuth) { // not closer, use position in non-overlap
                  direction_to_go = CW;
                  #ifdef DEBUG_SERVICE_REQUEST_QUEUE
                  debug_print("->CW!");
                  #endif // DEBUG_SERVICE_REQUEST_QUEUE
                } else {
                  direction_to_go = CCW;
                  #ifdef DEBUG_SERVICE_REQUEST_QUEUE
                  debug_print("->CCW!");
                  #endif // DEBUG_SERVICE_REQUEST_QUEUE
                }
              } else { // go to position in overlap
                #ifdef DEBUG_SERVICE_REQUEST_QUEUE
                debug_print("->D");
                #endif // DEBUG_SERVICE_REQUEST_QUEUE
                target_raw_azimuth = work_target_raw_azimuth + (360 * HEADING_MULTIPLIER);
                if ((work_target_raw_azimuth + (360 * HEADING_MULTIPLIER)) > raw_azimuth) {
                  direction_to_go = CW;
                  #ifdef DEBUG_SERVICE_REQUEST_QUEUE
                  debug_print("->CW!");
                  #endif // DEBUG_SERVICE_REQUEST_QUEUE
                } else {
                  direction_to_go = CCW;
                  #ifdef DEBUG_SERVICE_REQUEST_QUEUE
                  debug_print("->CCW!");
                  #endif // DEBUG_SERVICE_REQUEST_QUEUE
                }
              }
            } else {  // no possible second heading in overlap
              #ifdef DEBUG_SERVICE_REQUEST_QUEUE
              debug_print("->E");
              #endif // DEBUG_SERVICE_REQUEST_QUEUE
              if (work_target_raw_azimuth  > raw_azimuth) {
                direction_to_go = CW;
              } else {
                direction_to_go = CCW;
              }
            }
          }
        } else {
          #ifdef DEBUG_SERVICE_REQUEST_QUEUE
          debug_print("->F");
          #endif // DEBUG_SERVICE_REQUEST_QUEUE
          if ((az_request_parm > (360 * HEADING_MULTIPLIER)) && (az_request_parm <= ((azimuth_starting_point + azimuth_rotation_capability) * HEADING_MULTIPLIER))) {
            target_azimuth = az_request_parm - (360 * HEADING_MULTIPLIER);
            target_raw_azimuth = az_request_parm;
            if (az_request_parm > raw_azimuth) {
              direction_to_go = CW;
            } else {
              direction_to_go = CCW;
            }
          } else {
            #ifdef DEBUG_SERVICE_REQUEST_QUEUE
            debug_print(" error: bogus azimuth request:");
            debug_print_int(az_request_parm);
            debug_println("");
            #endif // DEBUG_SERVICE_REQUEST_QUEUE
            rotator(DEACTIVATE, CW);
            rotator(DEACTIVATE, CCW);
            az_state = IDLE;
            az_request_queue_state = NONE;         
            return;
          }
        }
        if (direction_to_go == CW) {
          if (((az_state == SLOW_START_CCW) || (az_state == NORMAL_CCW) || (az_state == SLOW_DOWN_CCW) || (az_state == TIMED_SLOW_DOWN_CCW)) && (az_slowstart_active)) {
            az_state = INITIALIZE_DIR_CHANGE_TO_CW;
            #ifdef DEBUG_SERVICE_REQUEST_QUEUE
            debug_print(" INITIALIZE_DIR_CHANGE_TO_CW");
            #endif // DEBUG_SERVICE_REQUEST_QUEUE
          } else {
            if ((az_state != INITIALIZE_SLOW_START_CW) && (az_state != SLOW_START_CW) && (az_state != NORMAL_CW)) { // if we're already rotating CW, don't do anything
              // rotator(ACTIVATE,CW);
              if (az_slowstart_active) {
                az_state = INITIALIZE_SLOW_START_CW;
              } else { az_state = INITIALIZE_NORMAL_CW; };
            }
          }
        }
        if (direction_to_go == CCW) {
          if (((az_state == SLOW_START_CW) || (az_state == NORMAL_CW) || (az_state == SLOW_DOWN_CW) || (az_state == TIMED_SLOW_DOWN_CW)) && (az_slowstart_active)) {
            az_state = INITIALIZE_DIR_CHANGE_TO_CCW;
            #ifdef DEBUG_SERVICE_REQUEST_QUEUE
            debug_print(" INITIALIZE_DIR_CHANGE_TO_CCW");
            #endif // DEBUG_SERVICE_REQUEST_QUEUE
          } else {
            if ((az_state != INITIALIZE_SLOW_START_CCW) && (az_state != SLOW_START_CCW) && (az_state != NORMAL_CCW)) { // if we're already rotating CCW, don't do anything
              // rotator(ACTIVATE,CCW);
              if (az_slowstart_active) {
                az_state = INITIALIZE_SLOW_START_CCW;
              } else { az_state = INITIALIZE_NORMAL_CCW; };
            }
          }
        }
        if (!within_tolerance_flag) {
          az_request_queue_state = IN_PROGRESS_TO_TARGET;
          az_last_rotate_initiation = millis();
        }
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println();
        }
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        break; // REQUEST_AZIMUTH

      case (REQUEST_AZIMUTH_RAW):
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        debug_print("REQUEST_AZIMUTH_RAW");
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        target_raw_azimuth = az_request_parm;
        target_azimuth = target_raw_azimuth;
        if (target_azimuth >= (360 * HEADING_MULTIPLIER)) {
          target_azimuth = target_azimuth - (360 * HEADING_MULTIPLIER);
        }

        if (((abs(raw_azimuth - target_raw_azimuth) < (AZIMUTH_TOLERANCE * HEADING_MULTIPLIER))) && (az_state == IDLE)) {
          #ifdef DEBUG_SERVICE_REQUEST_QUEUE
          debug_print(" request within tolerance");
          #endif // DEBUG_SERVICE_REQUEST_QUEUE
          az_request_queue_state = NONE;
          within_tolerance_flag = 1;
        } else {
          if (target_raw_azimuth > raw_azimuth) {
            if (((az_state == SLOW_START_CCW) || (az_state == NORMAL_CCW) || (az_state == SLOW_DOWN_CCW) || (az_state == TIMED_SLOW_DOWN_CCW)) && (az_slowstart_active)) {
              az_state = INITIALIZE_DIR_CHANGE_TO_CW;
              #ifdef DEBUG_SERVICE_REQUEST_QUEUE
              debug_print(" INITIALIZE_DIR_CHANGE_TO_CW");
              #endif // DEBUG_SERVICE_REQUEST_QUEUE
            } else {
              if ((az_state != INITIALIZE_SLOW_START_CW) && (az_state != SLOW_START_CW) && (az_state != NORMAL_CW)) { // if we're already rotating CW, don't do anything
                if (az_slowstart_active) {
                  az_state = INITIALIZE_SLOW_START_CW;
                } else { az_state = INITIALIZE_NORMAL_CW; };
              }
            }
          }
          if (target_raw_azimuth < raw_azimuth) {
            if (((az_state == SLOW_START_CW) || (az_state == NORMAL_CW) || (az_state == SLOW_DOWN_CW) || (az_state == TIMED_SLOW_DOWN_CW)) && (az_slowstart_active)) {
              az_state = INITIALIZE_DIR_CHANGE_TO_CCW;
              #ifdef DEBUG_SERVICE_REQUEST_QUEUE
              debug_print(" INITIALIZE_DIR_CHANGE_TO_CCW");
              #endif // DEBUG_SERVICE_REQUEST_QUEUE
            } else {
              if ((az_state != INITIALIZE_SLOW_START_CCW) && (az_state != SLOW_START_CCW) && (az_state != NORMAL_CCW)) { // if we're already rotating CCW, don't do anything
                if (az_slowstart_active) {
                  az_state = INITIALIZE_SLOW_START_CCW;
                } else { az_state = INITIALIZE_NORMAL_CCW; };
              }
            }
          }
          if (!within_tolerance_flag) {
            az_request_queue_state = IN_PROGRESS_TO_TARGET;
            az_last_rotate_initiation = millis();
          }
        }
      #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println();
        }
      #endif // DEBUG_SERVICE_REQUEST_QUEUE
        break; // REQUEST_AZIMUTH_RAW

      case (REQUEST_CW):
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        debug_print("REQUEST_CW");
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        stop_all_tracking();
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        if (((az_state == SLOW_START_CCW) || (az_state == NORMAL_CCW) || (az_state == SLOW_DOWN_CCW) || (az_state == TIMED_SLOW_DOWN_CCW)) && (az_slowstart_active)) {
          az_state = INITIALIZE_DIR_CHANGE_TO_CW;
          #ifdef DEBUG_SERVICE_REQUEST_QUEUE
          debug_print(" INITIALIZE_DIR_CHANGE_TO_CW");
          #endif // DEBUG_SERVICE_REQUEST_QUEUE
        } else {
          if ((az_state != SLOW_START_CW) && (az_state != NORMAL_CW)) {
            // rotator(ACTIVATE,CW);
            if (az_slowstart_active) {
              az_state = INITIALIZE_SLOW_START_CW;
            } else { 
              az_state = INITIALIZE_NORMAL_CW;
            };
          }
        }
        az_request_queue_state = NONE;
        az_last_rotate_initiation = millis();
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println();
        }
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        break; // REQUEST_CW

      case (REQUEST_CCW):
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        debug_print("REQUEST_CCW");
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        stop_all_tracking();
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        if (((az_state == SLOW_START_CW) || (az_state == NORMAL_CW) || (az_state == SLOW_DOWN_CW) || (az_state == TIMED_SLOW_DOWN_CW)) && (az_slowstart_active)) {
          az_state = INITIALIZE_DIR_CHANGE_TO_CCW;
          #ifdef DEBUG_SERVICE_REQUEST_QUEUE
          debug_print(" INITIALIZE_DIR_CHANGE_TO_CCW");
          #endif // DEBUG_SERVICE_REQUEST_QUEUE
        } else {
          if ((az_state != SLOW_START_CCW) && (az_state != NORMAL_CCW)) {
            // rotator(ACTIVATE,CCW);
            if (az_slowstart_active) {
              az_state = INITIALIZE_SLOW_START_CCW;
            } else { az_state = INITIALIZE_NORMAL_CCW; };
          }
        }
        az_request_queue_state = NONE;
        az_last_rotate_initiation = millis();
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println();
        }
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        break; // REQUEST_CCW

      case (REQUEST_KILL):
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        debug_print("REQUEST_KILL");
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        stop_all_tracking();
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        rotator(DEACTIVATE, CW);
        rotator(DEACTIVATE, CCW);
        az_state = IDLE;
        az_request_queue_state = NONE;
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        debug_println("");
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        break; // REQUEST_KILL
    } /* switch */

    #ifdef FEATURE_LCD_DISPLAY
    if (az_request_queue_state != IN_QUEUE) {push_lcd_update = 1;}
    #endif //FEATURE_LCD_DISPLAY
  }

  #ifdef FEATURE_ELEVATION_CONTROL
  if (el_request_queue_state == IN_QUEUE) {

    #ifdef FEATURE_POWER_SWITCH
    last_activity_time = millis();
    #endif //FEATURE_POWER_SWITCH

    within_tolerance_flag = 0;
    #ifdef DEBUG_SERVICE_REQUEST_QUEUE
    debug_print("service_request_queue: EL ");
    #endif // DEBUG_SERVICE_REQUEST_QUEUE
    switch (el_request) {
      case (REQUEST_ELEVATION):
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        debug_print("REQUEST_ELEVATION ");
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        target_elevation = el_request_parm;

        if (target_elevation > (ELEVATION_MAXIMUM_DEGREES * HEADING_MULTIPLIER)) {
          target_elevation = ELEVATION_MAXIMUM_DEGREES * HEADING_MULTIPLIER;
          #ifdef DEBUG_SERVICE_REQUEST_QUEUE
          if (debug_mode) {
            control_port->print(F("REQUEST_ELEVATION: target_elevation > ELEVATION_MAXIMUM_DEGREES"));
          }
          #endif // DEBUG_SERVICE_REQUEST_QUEUE
        }

        #ifdef OPTION_EL_MANUAL_ROTATE_LIMITS
        if (target_elevation < (EL_MANUAL_ROTATE_DOWN_LIMIT * HEADING_MULTIPLIER)) {
          target_elevation = EL_MANUAL_ROTATE_DOWN_LIMIT * HEADING_MULTIPLIER;
          #ifdef DEBUG_SERVICE_REQUEST_QUEUE
          if (debug_mode) {
            control_port->print(F("REQUEST_ELEVATION: target_elevation < EL_MANUAL_ROTATE_DOWN_LIMIT"));
          }
          #endif // DEBUG_SERVICE_REQUEST_QUEUE
        }
        if (target_elevation > (EL_MANUAL_ROTATE_UP_LIMIT * HEADING_MULTIPLIER)) {
          target_elevation = EL_MANUAL_ROTATE_UP_LIMIT * HEADING_MULTIPLIER;
          #ifdef DEBUG_SERVICE_REQUEST_QUEUE
          if (debug_mode) {
            control_port->print(F("REQUEST_ELEVATION: target_elevation > EL_MANUAL_ROTATE_UP_LIMIT"));
          }
          #endif // DEBUG_SERVICE_REQUEST_QUEUE
        }
        #endif // OPTION_EL_MANUAL_ROTATE_LIMITS

        if (abs(target_elevation - elevation) < (ELEVATION_TOLERANCE * HEADING_MULTIPLIER)) {
          #ifdef DEBUG_SERVICE_REQUEST_QUEUE
          if (debug_mode) {
            control_port->println(F("requested elevation within tolerance"));
          }
          #endif // DEBUG_SERVICE_REQUEST_QUEUE
          within_tolerance_flag = 1;
          el_request_queue_state = NONE;
        } else {
          if (target_elevation > elevation) {
            if (((el_state == SLOW_START_DOWN) || (el_state == NORMAL_DOWN) || (el_state == SLOW_DOWN_DOWN) || (el_state == TIMED_SLOW_DOWN_DOWN)) && (el_slowstart_active)) {
              el_state = INITIALIZE_DIR_CHANGE_TO_UP;
                #ifdef DEBUG_SERVICE_REQUEST_QUEUE
              if (debug_mode) {
                control_port->println(F(" INITIALIZE_DIR_CHANGE_TO_UP"));
              }
                #endif // DEBUG_SERVICE_REQUEST_QUEUE
            } else {
              if ((el_state != INITIALIZE_SLOW_START_UP) && (el_state != SLOW_START_UP) && (el_state != NORMAL_UP)) { // if we're already rotating UP, don't do anything
                if (el_slowstart_active) {
                  el_state = INITIALIZE_SLOW_START_UP;
                } else { el_state = INITIALIZE_NORMAL_UP; };
              }
            }
          } // (target_elevation > elevation)
          if (target_elevation < elevation) {
            if (((el_state == SLOW_START_UP) || (el_state == NORMAL_UP) || (el_state == SLOW_DOWN_UP) || (el_state == TIMED_SLOW_DOWN_UP)) && (el_slowstart_active)) {
              el_state = INITIALIZE_DIR_CHANGE_TO_DOWN;
              #ifdef DEBUG_SERVICE_REQUEST_QUEUE
              if (debug_mode) {
                control_port->println(F(" INITIALIZE_DIR_CHANGE_TO_DOWN"));
              }
              #endif // DEBUG_SERVICE_REQUEST_QUEUE
            } else {
              if ((el_state != INITIALIZE_SLOW_START_DOWN) && (el_state != SLOW_START_DOWN) && (el_state != NORMAL_DOWN)) { // if we're already rotating DOWN, don't do anything
                if (el_slowstart_active) {
                  el_state = INITIALIZE_SLOW_START_DOWN;
                } else { el_state = INITIALIZE_NORMAL_DOWN; };
              }
            }
          }  // (target_elevation < elevation)
        }  // (abs(target_elevation - elevation) < ELEVATION_TOLERANCE)
        if (!within_tolerance_flag) {
          el_request_queue_state = IN_PROGRESS_TO_TARGET;
          el_last_rotate_initiation = millis();
        }
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println();
        }
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        break; // REQUEST_ELEVATION

      case (REQUEST_UP):
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println(F("REQUEST_UP"));
        }
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        stop_all_tracking();
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        if (((el_state == SLOW_START_DOWN) || (el_state == NORMAL_DOWN) || (el_state == SLOW_DOWN_DOWN) || (el_state == TIMED_SLOW_DOWN_DOWN)) && (el_slowstart_active)) {
          el_state = INITIALIZE_DIR_CHANGE_TO_UP;
          #ifdef DEBUG_SERVICE_REQUEST_QUEUE
          if (debug_mode) {
            control_port->println(F("service_request_queue: INITIALIZE_DIR_CHANGE_TO_UP"));
          }
          #endif // DEBUG_SERVICE_REQUEST_QUEUE
        } else {
          if ((el_state != SLOW_START_UP) && (el_state != NORMAL_UP)) {
            if (el_slowstart_active) {
              el_state = INITIALIZE_SLOW_START_UP;
            } else { el_state = INITIALIZE_NORMAL_UP; };
          }
        }
        el_request_queue_state = NONE;
        el_last_rotate_initiation = millis();
          #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println();
        }
          #endif // DEBUG_SERVICE_REQUEST_QUEUE
        break; // REQUEST_UP

      case (REQUEST_DOWN):
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println(F("REQUEST_DOWN"));
        }
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        stop_all_tracking();
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        if (((el_state == SLOW_START_UP) || (el_state == NORMAL_UP) || (el_state == SLOW_DOWN_UP) || (el_state == TIMED_SLOW_DOWN_UP)) && (el_slowstart_active)) {
          el_state = INITIALIZE_DIR_CHANGE_TO_DOWN;
          #ifdef DEBUG_SERVICE_REQUEST_QUEUE
          if (debug_mode) {
            control_port->println(F("service_request_queue: INITIALIZE_DIR_CHANGE_TO_DOWN"));
          }
          #endif // DEBUG_SERVICE_REQUEST_QUEUE
        } else {
          if ((el_state != SLOW_START_DOWN) && (el_state != NORMAL_DOWN)) {
            if (el_slowstart_active) {
              el_state = INITIALIZE_SLOW_START_DOWN;
            } else { el_state = INITIALIZE_NORMAL_DOWN; };
          }
        }
        el_request_queue_state = NONE;
        el_last_rotate_initiation = millis();
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println();
        }
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        break; // REQUEST_DOWN

      case (REQUEST_STOP):
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println(F("REQUEST_STOP"));
        }
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        stop_all_tracking();
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        if (el_state != IDLE) {
          if (el_slowdown_active) {
            if ((el_state == TIMED_SLOW_DOWN_UP) || (el_state == TIMED_SLOW_DOWN_DOWN) || (el_state == SLOW_DOWN_UP) || (el_state == SLOW_DOWN_DOWN)) {  // if we're already in timed slow down and we get another stop, do a hard stop
              rotator(DEACTIVATE, UP);
              rotator(DEACTIVATE, DOWN);
              el_state = IDLE;
              el_request_queue_state = NONE;
            }
            if ((el_state == SLOW_START_UP) || (el_state == NORMAL_UP)) {
              el_state = INITIALIZE_TIMED_SLOW_DOWN_UP;
              el_request_queue_state = IN_PROGRESS_TIMED;
              el_last_rotate_initiation = millis();
            }
            if ((el_state == SLOW_START_DOWN) || (el_state == NORMAL_DOWN)) {
              el_state = INITIALIZE_TIMED_SLOW_DOWN_DOWN;
              el_request_queue_state = IN_PROGRESS_TIMED;
              el_last_rotate_initiation = millis();
            }
          } else {
            rotator(DEACTIVATE, UP);
            rotator(DEACTIVATE, DOWN);
            el_state = IDLE;
            el_request_queue_state = NONE;
          }
        } else {
          el_request_queue_state = NONE; // nothing to do, we're already in IDLE state
        }
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println();
        }
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        break; // REQUEST_STOP

      case (REQUEST_KILL):
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println(F("REQUEST_KILL"));
        }
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        stop_all_tracking();
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        rotator(DEACTIVATE, UP);
        rotator(DEACTIVATE, DOWN);
        el_state = IDLE;
        el_request_queue_state = NONE;
        #ifdef DEBUG_SERVICE_REQUEST_QUEUE
        if (debug_mode) {
          control_port->println();
        }
        #endif // DEBUG_SERVICE_REQUEST_QUEUE
        break; // REQUEST_KILL
    } /* switch */

    #ifdef FEATURE_LCD_DISPLAY
    if (el_request_queue_state != IN_QUEUE) {push_lcd_update = 1;}
    #endif //FEATURE_LCD_DISPLAY

  } // (el_request_queue_state == IN_QUEUE)
  #endif // FEATURE_ELEVATION_CONTROL


} /* service_request_queue */

// --------------------------------------------------------------
void check_for_dirty_configuration(){

  static unsigned long last_config_write_time = 0;

  if ((configuration_dirty) && ((millis() - last_config_write_time) > (EEPROM_WRITE_DIRTY_CONFIG_TIME * 1000))) {
    write_settings_to_eeprom();
    last_config_write_time = millis();
  }

}

// --------------------------------------------------------------
byte current_az_state(){

  if ((az_state == SLOW_START_CW) || (az_state == NORMAL_CW) || (az_state == SLOW_DOWN_CW) || (az_state == TIMED_SLOW_DOWN_CW)) {
    return ROTATING_CW;
  }
  if ((az_state == SLOW_START_CCW) || (az_state == NORMAL_CCW) || (az_state == SLOW_DOWN_CCW) || (az_state == TIMED_SLOW_DOWN_CCW)) {
    return ROTATING_CCW;
  }
  return NOT_DOING_ANYTHING;

}
// --------------------------------------------------------------
#ifdef FEATURE_ELEVATION_CONTROL
byte current_el_state(){

  if ((el_state == SLOW_START_UP) || (el_state == NORMAL_UP) || (el_state == SLOW_DOWN_UP) || (el_state == TIMED_SLOW_DOWN_UP)) {
    return ROTATING_UP;
  }
  if ((el_state == SLOW_START_DOWN) || (el_state == NORMAL_DOWN) || (el_state == SLOW_DOWN_DOWN) || (el_state == TIMED_SLOW_DOWN_DOWN)) {
    return ROTATING_DOWN;
  }
  return NOT_DOING_ANYTHING;

}
#endif // FEATURE_ELEVATION_CONTROL
// --------------------------------------------------------------
#ifdef FEATURE_AZ_POSITION_PULSE_INPUT
void az_position_pulse_interrupt_handler(){


 #ifdef DEBUG_POSITION_PULSE_INPUT
  // az_position_pule_interrupt_handler_flag++;
  az_pulse_counter++;
  #endif // DEBUG_POSITION_PULSE_INPUT

  if (current_az_state() == ROTATING_CW) {
    az_position_pulse_input_azimuth += AZ_POSITION_PULSE_DEG_PER_PULSE;
    last_known_az_state = ROTATING_CW;
  } else {
    if (current_az_state() == ROTATING_CCW) {
      az_position_pulse_input_azimuth -= AZ_POSITION_PULSE_DEG_PER_PULSE;
      last_known_az_state = ROTATING_CCW;
    } else {
          #ifndef OPTION_PULSE_IGNORE_AMBIGUOUS_PULSES
      if (last_known_az_state == ROTATING_CW) {
        az_position_pulse_input_azimuth += AZ_POSITION_PULSE_DEG_PER_PULSE;
      } else {
        if (last_known_az_state == ROTATING_CCW) {
          az_position_pulse_input_azimuth -= AZ_POSITION_PULSE_DEG_PER_PULSE;
        }
      }
            #endif // OPTION_PULSE_IGNORE_AMBIGUOUS_PULSES
            #ifdef DEBUG_POSITION_PULSE_INPUT
      az_pulse_counter_ambiguous++;
            #endif // DEBUG_POSITION_PULSE_INPUT
    }
  }

  #ifdef OPTION_AZ_POSITION_PULSE_HARD_LIMIT
  if (az_position_pulse_input_azimuth < azimuth_starting_point) {
    az_position_pulse_input_azimuth = azimuth_starting_point;
  }
  if (az_position_pulse_input_azimuth > (azimuth_starting_point + azimuth_rotation_capability)) {
    az_position_pulse_input_azimuth = (azimuth_starting_point + azimuth_rotation_capability);
  }
  #else
  if (az_position_pulse_input_azimuth < 0) {
    az_position_pulse_input_azimuth += 360;
  }
  if (az_position_pulse_input_azimuth >= 360) {
    az_position_pulse_input_azimuth -= 360;
  }
  #endif // OPTION_AZ_POSITION_PULSE_HARD_LIMIT

} /* az_position_pulse_interrupt_handler */
#endif // FEATURE_AZ_POSITION_PULSE_INPUT
// --------------------------------------------------------------
#ifdef FEATURE_ELEVATION_CONTROL
#ifdef FEATURE_EL_POSITION_PULSE_INPUT
void el_position_pulse_interrupt_handler(){

  #ifdef DEBUG_POSITION_PULSE_INPUT
  // el_position_pule_interrupt_handler_flag++;
  el_pulse_counter++;
  #endif // DEBUG_POSITION_PULSE_INPUT

  if (current_el_state() == ROTATING_UP) {
    el_position_pulse_input_elevation += EL_POSITION_PULSE_DEG_PER_PULSE;
    last_known_el_state = ROTATING_UP;
  } else {
    if (current_el_state() == ROTATING_DOWN) {
      el_position_pulse_input_elevation -= EL_POSITION_PULSE_DEG_PER_PULSE;
      last_known_el_state = ROTATING_DOWN;
    } else {
          #ifndef OPTION_PULSE_IGNORE_AMBIGUOUS_PULSES
      if (last_known_el_state == ROTATING_UP) {
        el_position_pulse_input_elevation += EL_POSITION_PULSE_DEG_PER_PULSE;
      } else {
        if (last_known_el_state == ROTATING_DOWN) {
          el_position_pulse_input_elevation -= EL_POSITION_PULSE_DEG_PER_PULSE;
        }
      }
            #endif // OPTION_PULSE_IGNORE_AMBIGUOUS_PULSES
            #ifdef DEBUG_POSITION_PULSE_INPUT
      el_pulse_counter_ambiguous++;
            #endif // DEBUG_POSITION_PULSE_INPUT
    }
  }

        #ifdef OPTION_EL_POSITION_PULSE_HARD_LIMIT
  if (el_position_pulse_input_elevation < 0) {
    el_position_pulse_input_elevation = 0;
  }
  if (el_position_pulse_input_elevation > ELEVATION_MAXIMUM_DEGREES) {
    el_position_pulse_input_elevation = ELEVATION_MAXIMUM_DEGREES;
  }
        #endif // OPTION_EL_POSITION_PULSE_HARD_LIMIT


} /* el_position_pulse_interrupt_handler */
#endif // FEATURE_EL_POSITION_PULSE_INPUT
#endif // FEATURE_ELEVATION_CONTROL
// --------------------------------------------------------------------------
#if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
byte submit_remote_command(byte remote_command_to_send, byte parm1, int parm2){

  #ifdef FEATURE_MASTER_WITH_ETHERNET_SLAVE
  char ethernet_send_string[32];
  char temp_string[32];
  #endif //FEATURE_MASTER_WITH_ETHERNET_SLAVE

  #ifdef FEATURE_MASTER_WITH_ETHERNET_SLAVE
  if (ethernetslavelinkclient0_state != ETHERNET_SLAVE_CONNECTED){return 0;}
  #endif //FEATURE_MASTER_WITH_ETHERNET_SLAVE

  if ((remote_unit_command_submitted && ((remote_command_to_send == REMOTE_UNIT_AZ_COMMAND) || (remote_command_to_send == REMOTE_UNIT_EL_COMMAND) || (remote_command_to_send == REMOTE_UNIT_CL_COMMAND))) || suspend_remote_commands) {
    return 0;
  } else {
    switch (remote_command_to_send) {
      case REMOTE_UNIT_CL_COMMAND:
        #ifdef FEATURE_MASTER_WITH_SERIAL_SLAVE
        remote_unit_port->println("CL");
        #endif //FEATURE_MASTER_WITH_SERIAL_SLAVE
        #ifdef FEATURE_MASTER_WITH_ETHERNET_SLAVE
        ethernet_slave_link_send("CL");
        #endif //FEATURE_MASTER_WITH_ETHERNET_SLAVE
        #if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)
        if (remote_port_tx_sniff) {control_port->println("CL");}
        #endif
        remote_unit_command_submitted = REMOTE_UNIT_CL_COMMAND;
        break;


      case REMOTE_UNIT_AZ_COMMAND:
        #ifdef FEATURE_MASTER_WITH_SERIAL_SLAVE
        remote_unit_port->println("AZ");
        #endif //FEATURE_MASTER_WITH_SERIAL_SLAVE
        #ifdef FEATURE_MASTER_WITH_ETHERNET_SLAVE
        ethernet_slave_link_send("AZ");
        #endif //FEATURE_MASTER_WITH_ETHERNET_SLAVE
        #if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)
        if (remote_port_tx_sniff) {control_port->println("AZ");}
        #endif
        remote_unit_command_submitted = REMOTE_UNIT_AZ_COMMAND;
        break;

      case REMOTE_UNIT_EL_COMMAND:
        #ifdef FEATURE_MASTER_WITH_SERIAL_SLAVE
        remote_unit_port->println("EL");
        #endif //FEATURE_MASTER_WITH_SERIAL_SLAVE
        #ifdef FEATURE_MASTER_WITH_ETHERNET_SLAVE
        ethernet_slave_link_send("EL");
        #endif //FEATURE_MASTER_WITH_ETHERNET_SLAVE        
        #if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)
        if (remote_port_tx_sniff) {control_port->println("EL");}
        #endif
        remote_unit_command_submitted = REMOTE_UNIT_EL_COMMAND;
        break;


      case REMOTE_UNIT_AW_COMMAND:
        #ifdef FEATURE_MASTER_WITH_SERIAL_SLAVE
        take_care_of_pending_remote_command();
        remote_unit_port->print("AW");
        parm1 = parm1 - 100;   // pin number
        if (parm1 < 10) {remote_unit_port->print("0");}
        remote_unit_port->print(parm1);
        if (parm2 < 10) {remote_unit_port->print("0");}
        if (parm2 < 100) {remote_unit_port->print("0");}
        remote_unit_port->println(parm2);
        #endif //FEATURE_MASTER_WITH_SERIAL_SLAVE

        #ifdef FEATURE_MASTER_WITH_ETHERNET_SLAVE
        take_care_of_pending_remote_command();
        strcpy(ethernet_send_string,"AW");
        parm1 = parm1 - 100;   // pin number
        if (parm1 < 10) {strcat(ethernet_send_string,"0");}
        dtostrf(parm1,0,0,temp_string);
        if (parm2 < 10) {strcat(ethernet_send_string,"0");}
        if (parm2 < 100) {strcat(ethernet_send_string,"0");}
        dtostrf(parm2,0,0,temp_string);
        strcat(ethernet_send_string,temp_string);
        ethernet_slave_link_send(ethernet_send_string);
        #endif //FEATURE_MASTER_WITH_ETHERNET_SLAVE

        remote_unit_command_submitted = REMOTE_UNIT_OTHER_COMMAND;
        break;

      case REMOTE_UNIT_DHL_COMMAND:
        #ifdef FEATURE_MASTER_WITH_SERIAL_SLAVE
        take_care_of_pending_remote_command();
        remote_unit_port->print("D");
        if (parm2 == HIGH) {remote_unit_port->print("H");} else {remote_unit_port->print("L");}
        parm1 = parm1 - 100;
        if (parm1 < 10) {remote_unit_port->print("0");}
        remote_unit_port->println(parm1);
        #endif //FEATURE_MASTER_WITH_SERIAL_SLAVE


        #ifdef FEATURE_MASTER_WITH_ETHERNET_SLAVE
        take_care_of_pending_remote_command();
        strcpy(ethernet_send_string,"D");
        if (parm2 == HIGH) {strcat(ethernet_send_string,"H");} else {strcat(ethernet_send_string,"L");}
        parm1 = parm1 - 100;
        if (parm1 < 10) {strcat(ethernet_send_string,"0");}
        dtostrf(parm1,0,0,temp_string);
        strcat(ethernet_send_string,temp_string);
        ethernet_slave_link_send(ethernet_send_string);
        #endif //FEATURE_MASTER_WITH_ETHERNET_SLAVE

        remote_unit_command_submitted = REMOTE_UNIT_OTHER_COMMAND;

        break;

      case REMOTE_UNIT_DOI_COMMAND:
        #ifdef FEATURE_MASTER_WITH_SERIAL_SLAVE
        take_care_of_pending_remote_command();
        remote_unit_port->print("D");
        if (parm2 == OUTPUT) {remote_unit_port->print("O");} else {remote_unit_port->print("I");}
        parm1 = parm1 - 100;
        if (parm1 < 10) {remote_unit_port->print("0");}
        remote_unit_port->println(parm1);
        remote_unit_command_submitted = REMOTE_UNIT_OTHER_COMMAND;
        // get_remote_port_ok_response();
        #endif //FEATURE_MASTER_WITH_SERIAL_SLAVE

        #ifdef FEATURE_MASTER_WITH_ETHERNET_SLAVE
        take_care_of_pending_remote_command();
        strcpy(ethernet_send_string,"D");
        if (parm2 == OUTPUT) {strcat(ethernet_send_string,"O");} else {strcat(ethernet_send_string,"I");}
        parm1 = parm1 - 100;
        if (parm1 < 10) {strcat(ethernet_send_string,"0");}
        dtostrf(parm1,0,0,temp_string);
        strcat(ethernet_send_string,temp_string);
        ethernet_slave_link_send(ethernet_send_string);
        remote_unit_command_submitted = REMOTE_UNIT_OTHER_COMMAND;
        #endif //FEATURE_MASTER_WITH_ETHERNET_SLAVE

        break;


    } /* switch */
    last_remote_unit_command_time = millis();
    remote_unit_command_results_available = 0;
    return 1;
  }



} /* submit_remote_command */
#endif // defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)

// --------------------------------------------------------------------------

#if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
byte is_ascii_number(byte char_in){

  if ((char_in > 47) && (char_in < 58)) {
    return 1;
  } else {
    return 0;
  }

}\

 #endif // defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
// --------------------------------------------------------------------------
#if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
void service_remote_communications_incoming_buffer(){


  #if defined(FEATURE_CLOCK) && defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE)
  int temp_year = 0;
  byte temp_month = 0;
  byte temp_day = 0;
  byte temp_minute = 0;
  byte temp_hour = 0;
  byte temp_sec = 0;
  #endif // defined(FEATURE_CLOCK) && defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE)



  byte good_data = 0;

  if (remote_unit_port_buffer_carriage_return_flag) {

    #ifdef DEBUG_SVC_REMOTE_COMM_INCOMING_BUFFER
    debug_print("service_remote_communications_incoming_buffer: remote_unit_port_buffer_index: ");
    debug_print_int(remote_unit_port_buffer_index);
    debug_print(" buffer: ");
    for (int x = 0; x < remote_unit_port_buffer_index; x++) {
      debug_write((char*)remote_unit_port_buffer[x]);
      debug_println("$");
    }
    #endif // DEBUG_SVC_REMOTE_COMM_INCOMING_BUFFER

    if (remote_unit_command_submitted) {   // this was a solicited response
      switch (remote_unit_command_submitted) {

        case REMOTE_UNIT_CL_COMMAND:
          if ((remote_unit_port_buffer[0] == 'C') && (remote_unit_port_buffer[1] == 'L') &&
            (remote_unit_port_buffer[12] == ' ') && (remote_unit_port_buffer[21] == 'Z'))
          {
            #if defined(FEATURE_CLOCK) && defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE)
            temp_year = ((remote_unit_port_buffer[2] - 48) * 1000) + ((remote_unit_port_buffer[3] - 48) * 100) + ((remote_unit_port_buffer[4] - 48) * 10) + (remote_unit_port_buffer[5] - 48);
            temp_month = ((remote_unit_port_buffer[7] - 48) * 10) + (remote_unit_port_buffer[8] - 48);
            temp_day = ((remote_unit_port_buffer[10] - 48) * 10) + (remote_unit_port_buffer[11] - 48);
            temp_hour = ((remote_unit_port_buffer[13] - 48) * 10) + (remote_unit_port_buffer[14] - 48);
            temp_minute = ((remote_unit_port_buffer[16] - 48) * 10) + (remote_unit_port_buffer[17] - 48);
            temp_sec = ((remote_unit_port_buffer[19] - 48) * 10) + (remote_unit_port_buffer[20] - 48);
            if ((temp_year > 2013) && (temp_year < 2070) &&
                (temp_month > 0) && (temp_month < 13) &&
                (temp_day > 0) && (temp_day < 32) &&
                (temp_hour >= 0) && (temp_hour < 24) &&
                (temp_minute >= 0) && (temp_minute < 60) &&
                (temp_sec >= 0) && (temp_sec < 60) ) {

              clock_year_set = temp_year;
              clock_month_set = temp_month;
              clock_day_set = temp_day;
              clock_hour_set = temp_hour;
              clock_min_set = temp_minute;
              clock_sec_set = temp_sec;
              millis_at_last_calibration = millis();
              #ifdef DEBUG_SYNC_MASTER_CLOCK_TO_SLAVE
              debug_println("service_remote_communications_incoming_buffer: clock synced to slave clock");
              #endif //DEBUG_SYNC_MASTER_CLOCK_TO_SLAVE
              good_data = 1;
              if (clock_status == FREE_RUNNING) {clock_status = SLAVE_SYNC;}
            } else {

              #ifdef DEBUG_SYNC_MASTER_CLOCK_TO_SLAVE
              debug_println("service_remote_communications_incoming_buffer: slave clock sync error");
              #endif //DEBUG_SYNC_MASTER_CLOCK_TO_SLAVE  
              if (clock_status == SLAVE_SYNC) {clock_status = FREE_RUNNING;}   
            }
            #endif // defined(FEATURE_CLOCK) && defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE)

            #if !defined(FEATURE_CLOCK) || !defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE)
            good_data = 1;
            #endif //!defined(FEATURE_CLOCK) || !defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE)
          } else {
            #if defined(FEATURE_CLOCK) && defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE)
            #ifdef DEBUG_SYNC_MASTER_CLOCK_TO_SLAVE
            debug_print("service_remote_communications_incoming_buffer: REMOTE_UNIT_CL_COMMAND format error.  remote_unit_port_buffer_index: ");
            debug_print_int(remote_unit_port_buffer_index);
            debug_println("");
            #endif //DEBUG_SYNC_MASTER_CLOCK_TO_SLAVE 
            if (clock_status == SLAVE_SYNC) {clock_status = FREE_RUNNING;} 
            #endif // defined(FEATURE_CLOCK) && defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE)          
          }
          break;
        case REMOTE_UNIT_AZ_COMMAND:
          if ((remote_unit_port_buffer_index == 13) && (remote_unit_port_buffer[0] == 'A') && (remote_unit_port_buffer[1] == 'Z') &&
              (is_ascii_number(remote_unit_port_buffer[2])) && (is_ascii_number(remote_unit_port_buffer[3])) && (is_ascii_number(remote_unit_port_buffer[4])) && (is_ascii_number(remote_unit_port_buffer[6]))  && (is_ascii_number(remote_unit_port_buffer[7])) && (is_ascii_number(remote_unit_port_buffer[8])) && (is_ascii_number(remote_unit_port_buffer[9])) && (is_ascii_number(remote_unit_port_buffer[10])) && (is_ascii_number(remote_unit_port_buffer[11]))) {
            remote_unit_command_result_float = ((remote_unit_port_buffer[2] - 48) * 100) + ((remote_unit_port_buffer[3] - 48) * 10) + (remote_unit_port_buffer[4] - 48) + ((remote_unit_port_buffer[6] - 48) / 10.0) + ((remote_unit_port_buffer[7] - 48) / 100.0) + ((remote_unit_port_buffer[8] - 48) / 1000.0) + ((remote_unit_port_buffer[9] - 48) / 10000.0) + ((remote_unit_port_buffer[10] - 48) / 100000.0) + ((remote_unit_port_buffer[11] - 48) / 1000000.0);
            good_data = 1;
          }
          break;
        case REMOTE_UNIT_EL_COMMAND:
          if ((remote_unit_port_buffer_index == 14) && (remote_unit_port_buffer[0] == 'E') && (remote_unit_port_buffer[1] == 'L') &&
              (is_ascii_number(remote_unit_port_buffer[3])) && (is_ascii_number(remote_unit_port_buffer[4])) && (is_ascii_number(remote_unit_port_buffer[5])) && (is_ascii_number(remote_unit_port_buffer[7])) && (is_ascii_number(remote_unit_port_buffer[8])) && (is_ascii_number(remote_unit_port_buffer[9])) && (is_ascii_number(remote_unit_port_buffer[10])) && (is_ascii_number(remote_unit_port_buffer[11])) && (is_ascii_number(remote_unit_port_buffer[12]))) {
            remote_unit_command_result_float = ((remote_unit_port_buffer[3] - 48) * 100) + ((remote_unit_port_buffer[4] - 48) * 10) + (remote_unit_port_buffer[5] - 48) + ((remote_unit_port_buffer[7] - 48) / 10.0)  + ((remote_unit_port_buffer[8] - 48) / 100.0)  + ((remote_unit_port_buffer[9] - 48) / 1000.0)  + ((remote_unit_port_buffer[10] - 48) / 10000.0)  + ((remote_unit_port_buffer[11] - 48) / 100000.0)  + ((remote_unit_port_buffer[12] - 48) / 1000000.0);
            if (remote_unit_port_buffer[2] == '+') {
              good_data = 1;
            }
            if (remote_unit_port_buffer[2] == '-') {
              remote_unit_command_result_float = remote_unit_command_result_float * -1.0;
              good_data = 1;
            }
          }
          break;
        case REMOTE_UNIT_OTHER_COMMAND:
          if ((remote_unit_port_buffer[0] == 'O') && (remote_unit_port_buffer[1] == 'K')) {
            good_data = 1;
          }
          break;
      } /* switch */
      if (good_data) {
        if (remote_unit_command_submitted != REMOTE_UNIT_OTHER_COMMAND) {
          remote_unit_command_results_available = remote_unit_command_submitted;
        }
        remote_unit_good_results++;

        #ifdef DEBUG_SVC_REMOTE_COMM_INCOMING_BUFFER
        debug_print("service_remote_communications_incoming_buffer: remote_unit_command_results_available: ");
        debug_print_int(remote_unit_command_results_available);
        debug_print(" remote_unit_command_result_float: ");
        debug_print_float(remote_unit_command_result_float,2);
        debug_println("");
        #endif // DEBUG_SVC_REMOTE_COMM_INCOMING_BUFFER


      } else {

        #ifdef DEBUG_SVC_REMOTE_COMM_INCOMING_BUFFER_BAD_DATA
        debug_print("service_remote_communications_incoming_buffer: bad data: remote_unit_command_submitted: ");
        switch (remote_unit_command_submitted) {
          case REMOTE_UNIT_AZ_COMMAND: debug_print("REMOTE_UNIT_AZ_COMMAND"); break;
          case REMOTE_UNIT_EL_COMMAND: debug_print("REMOTE_UNIT_EL_COMMAND"); break;
          case REMOTE_UNIT_OTHER_COMMAND: debug_print("REMOTE_UNIT_OTHER_COMMAND"); break;
          default: debug_print("UNDEFINED"); break;
        }
        debug_print(" buffer_index:");
        debug_print_int(remote_unit_port_buffer_index);
        debug_print(" buffer: ");
        for (int x = 0; x < remote_unit_port_buffer_index; x++) {
          debug_write((char*)remote_unit_port_buffer[x]);
        }
        debug_println("$");
        #endif // DEBUG_SVC_REMOTE_COMM_INCOMING_BUFFER_BAD_DATA


        remote_unit_command_results_available = 0;
        remote_unit_bad_results++;
      }
      remote_unit_command_submitted = 0;
    } else {  // this was an unsolicited message

    }
    remote_unit_port_buffer_carriage_return_flag = 0;
    remote_unit_port_buffer_index = 0;
  }

  // has a command timed out?
  if ((remote_unit_command_submitted) && ((millis() - last_remote_unit_command_time) > REMOTE_UNIT_COMMAND_TIMEOUT_MS)) {

    #if defined(FEATURE_CLOCK) && defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE)
    if ((remote_unit_command_submitted == REMOTE_UNIT_CL_COMMAND) && (clock_status == SLAVE_SYNC)){
      clock_status = FREE_RUNNING;
    }
    #endif //defined(FEATURE_CLOCK) && defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE)

    remote_unit_command_timeouts++;
    remote_unit_command_submitted = 0;
    remote_unit_port_buffer_index = 0;
    
  }

  // have characters been in the buffer for some time but no carriage return?
  if ((remote_unit_port_buffer_index) && (!remote_unit_command_submitted) && ((millis() - serial1_last_receive_time) > REMOTE_UNIT_COMMAND_TIMEOUT_MS)) {
    remote_unit_port_buffer_index = 0;
    remote_unit_incoming_buffer_timeouts++;
  }

} /* service_remote_communications_incoming_buffer */

#endif // defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
// --------------------------------------------------------------------------
#ifdef FEATURE_AZIMUTH_CORRECTION
float correct_azimuth(float azimuth_in){

  if (sizeof(azimuth_calibration_from) != sizeof(azimuth_calibration_to)) {
    return azimuth_in;
  }
  for (unsigned int x = 0; x < (sizeof(azimuth_calibration_from) - 2); x++) {
    if ((azimuth_in >= azimuth_calibration_from[x]) && (azimuth_in <= azimuth_calibration_from[x + 1])) {
      return (map(azimuth_in * 10, azimuth_calibration_from[x] * 10, azimuth_calibration_from[x + 1] * 10, azimuth_calibration_to[x] * 10, azimuth_calibration_to[x + 1] * 10)) / 10.0;
    }
  }
  return(azimuth_in);

}
#endif // FEATURE_AZIMUTH_CORRECTION
// --------------------------------------------------------------------------
#ifdef FEATURE_ELEVATION_CORRECTION
float correct_elevation(float elevation_in){

  if (sizeof(elevation_calibration_from) != sizeof(elevation_calibration_to)) {
    return elevation_in;
  }
  for (unsigned int x = 0; x < (sizeof(elevation_calibration_from) - 2); x++) {
    if ((elevation_in >= elevation_calibration_from[x]) && (elevation_in <= elevation_calibration_from[x + 1])) {
      return (map(elevation_in * 10, elevation_calibration_from[x] * 10, elevation_calibration_from[x + 1] * 10, elevation_calibration_to[x] * 10, elevation_calibration_to[x + 1] * 10)) / 10.0;
    }
  }
  return(elevation_in);

}
#endif // FEATURE_ELEVATION_CORRECTION
// --------------------------------------------------------------------------
#ifdef FEATURE_JOYSTICK_CONTROL
void check_joystick(){

  int joystick_x = 0;
  int joystick_y = 0;

  static int joystick_resting_x = 0;
  static int joystick_resting_y = 0;

  static unsigned long last_joystick_az_action_time = 0;

  static byte joystick_azimuth_rotation = NOT_DOING_ANYTHING;

  #ifdef FEATURE_ELEVATION_CONTROL
  static byte joystick_elevation_rotation = NOT_DOING_ANYTHING;
  static unsigned long last_joystick_el_action_time = 0;
  #endif // FEATURE_ELEVATION_CONTROL

  if ((joystick_resting_x == 0) || (joystick_resting_y == 0)) {  // initialize the resting readings if this is our first time here

    joystick_resting_x = analogReadEnhanced(pin_joystick_x);
    joystick_resting_y = analogReadEnhanced(pin_joystick_y);

  } else {

    joystick_x = analogReadEnhanced(pin_joystick_x);
    joystick_y = analogReadEnhanced(pin_joystick_y);

    if ((millis() - last_joystick_az_action_time) > JOYSTICK_WAIT_TIME_MS) {
      #ifdef DEBUG_JOYSTICK
      static unsigned long last_debug_joystick_status = 0;

      if ((debug_mode) && ((millis() - last_debug_joystick_status) > 1000)) {
        control_port->print("check_joystick: x: ");
        control_port->print(joystick_x);
        control_port->print("\ty: ");
        control_port->println(joystick_y);
        last_debug_joystick_status = millis();
      }
      #endif // DEBUG_JOYSTICK

      #ifndef OPTION_JOYSTICK_REVERSE_X_AXIS
      if ((joystick_resting_x - joystick_x) < (joystick_resting_x * -0.2)) {   // left
      #else
      if ((joystick_resting_x - joystick_x) > (joystick_resting_x * 0.2)) {
      #endif
        #ifdef DEBUG_JOYSTICK
        if (debug_mode) {
          control_port->println("check_joystick: L");
        }
          #endif // DEBUG_JOYSTICK
        if (current_az_state() != ROTATING_CCW) {
          submit_request(AZ, REQUEST_CCW, 0, 1);
        }
        joystick_azimuth_rotation = ROTATING_CCW;
        last_joystick_az_action_time = millis();

      } else {
        #ifndef OPTION_JOYSTICK_REVERSE_X_AXIS
        if ((joystick_resting_x - joystick_x) > (joystick_resting_x * 0.2)) {  // right
        #else
        if ((joystick_resting_x - joystick_x) < (joystick_resting_x * -0.2)) {
        #endif
          #ifdef DEBUG_JOYSTICK
          if (debug_mode) {
            control_port->println("check_joystick: R");
          }
            #endif // DEBUG_JOYSTICK
          if (current_az_state() != ROTATING_CW) {
            submit_request(AZ, REQUEST_CW, 0, 2);
          }
          joystick_azimuth_rotation = ROTATING_CW;
          last_joystick_az_action_time = millis();

        } else { // joystick is in X axis resting position
          if (joystick_azimuth_rotation != NOT_DOING_ANYTHING) {
            if (current_az_state() != NOT_DOING_ANYTHING) {
              submit_request(AZ, REQUEST_STOP, 0, 3);
              last_joystick_az_action_time = millis();
            }
            joystick_azimuth_rotation = NOT_DOING_ANYTHING;
          }
        }

      }

    }

    #ifdef FEATURE_ELEVATION_CONTROL
    if ((millis() - last_joystick_el_action_time) > JOYSTICK_WAIT_TIME_MS) {   
      #ifndef OPTION_JOYSTICK_REVERSE_Y_AXIS
      if ((joystick_resting_y - joystick_y) > (joystick_resting_y * 0.2)) {  // down
        #else
      if ((joystick_resting_y - joystick_y) < (joystick_resting_y * -0.2)) {
          #endif
          #ifdef DEBUG_JOYSTICK
        if (debug_mode) {
          control_port->println("check_joystick: D");
        }
          #endif // DEBUG_JOYSTICK
        if (current_el_state() != ROTATING_DOWN) {
          submit_request(EL, REQUEST_DOWN, 0, 4);
        }
        joystick_elevation_rotation = ROTATING_DOWN;
        last_joystick_el_action_time = millis();
      } else {
            #ifndef OPTION_JOYSTICK_REVERSE_Y_AXIS
        if ((joystick_resting_y - joystick_y) < (joystick_resting_y * -0.2)) { // up
          #else
        if ((joystick_resting_y - joystick_y) > (joystick_resting_y * 0.2)) {
            #endif
            #ifdef DEBUG_JOYSTICK
          if (debug_mode) {
            control_port->println("check_joystick: U");
          }
            #endif // DEBUG_JOYSTICK
          if (current_el_state() != ROTATING_UP) {
            submit_request(EL, REQUEST_UP, 0, 5);
          }
          joystick_elevation_rotation = ROTATING_UP;
          last_joystick_el_action_time = millis();

        } else {  // Y axis is in resting position
          if (joystick_elevation_rotation != NOT_DOING_ANYTHING) {
            if (current_el_state() != NOT_DOING_ANYTHING) {
              submit_request(EL, REQUEST_STOP, 0, 6);
              last_joystick_el_action_time = millis();
            }
            joystick_elevation_rotation = NOT_DOING_ANYTHING;
          }
        }
      }
      

    }
    #endif // FEATURE_ELEVATION_CONTROL

  }


} /* check_joystick */
#endif // FEATURE_JOYSTICK_CONTROL
// --------------------------------------------------------------------------

#ifdef FEATURE_ROTATION_INDICATOR_PIN
void service_rotation_indicator_pin(){


  static byte rotation_indication_pin_state = 0;
  static unsigned long time_rotation_went_inactive = 0;

  #ifdef FEATURE_ELEVATION_CONTROL
  if ((!rotation_indication_pin_state) && ((az_state != IDLE) || (el_state != IDLE))) {
    #else
  if ((!rotation_indication_pin_state) && ((az_state != IDLE))) {
      #endif
    if (rotation_indication_pin) {
      digitalWriteEnhanced(rotation_indication_pin, ROTATION_INDICATOR_PIN_ACTIVE_STATE);
    }
    rotation_indication_pin_state = 1;
      #ifdef DEBUG_ROTATION_INDICATION_PIN
    if (debug_mode) {
      control_port->println(F("service_rotation_indicator_pin: active"));
    }
      #endif
  }

    #ifdef FEATURE_ELEVATION_CONTROL
  if ((rotation_indication_pin_state) && (az_state == IDLE) && (el_state == IDLE)) {
      #else
  if ((rotation_indication_pin_state) && (az_state == IDLE)) {
        #endif
    if (time_rotation_went_inactive == 0) {
      time_rotation_went_inactive = millis();
    } else {
      if ((millis() - time_rotation_went_inactive) >= ((ROTATION_INDICATOR_PIN_TIME_DELAY_SECONDS * 1000) + (ROTATION_INDICATOR_PIN_TIME_DELAY_MINUTES * 60 * 1000))) {
        if (rotation_indication_pin) {
          digitalWriteEnhanced(rotation_indication_pin, ROTATION_INDICATOR_PIN_INACTIVE_STATE);
        }
        rotation_indication_pin_state = 0;
        time_rotation_went_inactive = 0;
              #ifdef DEBUG_ROTATION_INDICATION_PIN
        if (debug_mode) {
          control_port->println(F("service_rotation_indicator_pin: inactive"));
        }
              #endif
      }
    }
  }


} /* service_rotation_indicator_pin */
      #endif // FEATURE_ROTATION_INDICATOR_PIN
// --------------------------------------------------------------
#ifdef FEATURE_PARK
void deactivate_park(){

  park_status = NOT_PARKED;
  park_serial_initiated = 0;
}
#endif // FEATURE_PARK

// --------------------------------------------------------------
#ifdef FEATURE_PARK
void initiate_park(){

  #ifdef DEBUG_PARK
  control_port->println(F("initiate_park: park initiated"));
  #endif // DEBUG_PARK

  byte park_initiated = 0;

  stop_all_tracking();

  if (abs(raw_azimuth - PARK_AZIMUTH) > (AZIMUTH_TOLERANCE * HEADING_MULTIPLIER)) {
    submit_request(AZ, REQUEST_AZIMUTH_RAW, PARK_AZIMUTH, 7);
    park_initiated = 1;
  }
  #ifdef FEATURE_ELEVATION_CONTROL
  if (abs(elevation - PARK_ELEVATION) > (ELEVATION_TOLERANCE * HEADING_MULTIPLIER)) {
    submit_request(EL, REQUEST_ELEVATION, PARK_ELEVATION, 8);
    park_initiated = 1;
  }
  #endif // FEATURE_ELEVATION

  if (park_initiated) {
    park_status = PARK_INITIATED;
  } else {
    park_status = PARKED;
  }

} /* initiate_park */
  #endif // FEATURE_PARK

// --------------------------------------------------------------
#ifdef FEATURE_PARK
void service_park(){

  static byte last_park_status = NOT_PARKED;

  if (park_status == PARKED) {
    if (abs(raw_azimuth - PARK_AZIMUTH) > (AZIMUTH_TOLERANCE * HEADING_MULTIPLIER)) {
      park_status = NOT_PARKED;
    }
    #ifdef FEATURE_ELEVATION_CONTROL
    if (abs(elevation - PARK_ELEVATION) > (ELEVATION_TOLERANCE * HEADING_MULTIPLIER)) {
      park_status = NOT_PARKED;
    }
    #endif // FEATURE_ELEVATION_CONTROL
  }


  if (park_status != last_park_status) {
    switch (park_status) {
      case NOT_PARKED:
        if (park_in_progress_pin) {
          digitalWriteEnhanced(park_in_progress_pin, LOW);
        }
        if (parked_pin) {
          digitalWriteEnhanced(parked_pin, LOW);
        }
      #ifdef DEBUG_PARK
        control_port->println(F("service_park: park_in_progress_pin: LOW  parked_pin: LOW"));
      #endif // DEBUG_PARK
        break;
      case PARK_INITIATED:
        if (park_in_progress_pin) {
          digitalWriteEnhanced(park_in_progress_pin, HIGH);
        }
        if (parked_pin) {
          digitalWriteEnhanced(parked_pin, LOW);
        }
      #ifdef DEBUG_PARK
        control_port->println(F("service_park: park_in_progress_pin: HIGH  parked_pin: LOW"));
      #endif // DEBUG_PARK
        break;
      case PARKED:
        if (park_in_progress_pin) {
          digitalWriteEnhanced(park_in_progress_pin, LOW);
        }
        if (parked_pin) {
          digitalWriteEnhanced(parked_pin, HIGH);
        }
        if (park_serial_initiated) {
        #if defined(FEATURE_REMOTE_UNIT_SLAVE) || defined(FEATURE_YAESU_EMULATION) || defined(FEATURE_EASYCOM_EMULATION)
          control_port->println(F("Parked."));
        #endif
          park_serial_initiated = 0;
        }
      #ifdef DEBUG_PARK
        control_port->println(F("service_park: park_in_progress_pin: LOW  parked_pin: HIGH"));
      #endif // DEBUG_PARK
        break;
    } /* switch */
  }

  last_park_status = park_status;

} /* service_park */
#endif // FEATURE_PARK

// --------------------------------------------------------------

#ifdef FEATURE_LIMIT_SENSE
void check_limit_sense(){

  static byte az_limit_tripped = 0;

  #ifdef FEATURE_ELEVATION_CONTROL
  static byte el_limit_tripped = 0;
  #endif // FEATURE_ELEVATION_CONTROL

  if (az_limit_sense_pin) {
    if (digitalReadEnhanced(az_limit_sense_pin) == 0) {
      if (!az_limit_tripped) {
        submit_request(AZ, REQUEST_KILL, 0, 9);
        az_limit_tripped = 1;
        #ifdef DEBUG_LIMIT_SENSE
        control_port->println(F("check_limit_sense: az limit tripped"));
        #endif // DEBUG_LIMIT_SENSE
      }
    } else {
      az_limit_tripped = 0;
    }
  }

    #ifdef FEATURE_ELEVATION_CONTROL
  if (el_limit_sense_pin) {
    if (digitalReadEnhanced(el_limit_sense_pin) == 0) {
      if (!el_limit_tripped) {
        submit_request(EL, REQUEST_KILL, 0, 10);
        el_limit_tripped = 1;
          #ifdef DEBUG_LIMIT_SENSE
        control_port->println(F("check_limit_sense: el limit tripped"));
          #endif // DEBUG_LIMIT_SENSE
      }
    } else {
      el_limit_tripped = 0;
    }
  }
      #endif // FEATURE_ELEVATION_CONTROL


} /* check_limit_sense */
    #endif // FEATURE_LIMIT_SENSE
// --------------------------------------------------------------
#ifdef FEATURE_AZ_POSITION_INCREMENTAL_ENCODER
void az_position_incremental_encoder_interrupt_handler(){

  byte rotation_result = 0;
  byte current_phase_a = digitalReadEnhanced(az_incremental_encoder_pin_phase_a);
  byte current_phase_b = digitalReadEnhanced(az_incremental_encoder_pin_phase_b);
  byte current_phase_z = digitalReadEnhanced(az_incremental_encoder_pin_phase_z);

  #ifdef DEBUG_AZ_POSITION_INCREMENTAL_ENCODER
  az_position_incremental_encoder_interrupt++;
  #endif // DEBUG_AZ_POSITION_INCREMENTAL_ENCODER

  if ((az_3_phase_encoder_last_phase_a_state != current_phase_a) || (az_3_phase_encoder_last_phase_b_state != current_phase_b)) {
    if (az_3_phase_encoder_last_phase_a_state == LOW) {
      rotation_result++;
    }
    rotation_result = rotation_result << 1;
    if (az_3_phase_encoder_last_phase_b_state == LOW) {
      rotation_result++;
    }
    rotation_result = rotation_result << 1;
    if (current_phase_a == LOW) {
      rotation_result++;
    }
    rotation_result = rotation_result << 1;
    if (current_phase_b == LOW) {
      rotation_result++;
    }
    switch (rotation_result) {
      case B0010: //az_incremental_encoder_position++; break;
      case B1011: //az_incremental_encoder_position++; break;
      case B1101: //az_incremental_encoder_position++; break;
      case B0100: az_incremental_encoder_position++; break;

      case B0001: //az_incremental_encoder_position--; break;
      case B0111: //az_incremental_encoder_position--; break;
      case B1110: //az_incremental_encoder_position--; break;
      case B1000: az_incremental_encoder_position--; break;
    }

    if (az_incremental_encoder_position > ((int(AZ_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.) - 1) * 2)) {
      az_incremental_encoder_position = 0;
    }
    if (az_incremental_encoder_position < 0) {
      az_incremental_encoder_position = ((int(AZ_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.) - 1) * 2);
    }

    if ((current_phase_a == LOW) && (current_phase_b == LOW) && (current_phase_z == LOW)) {
      if ((az_incremental_encoder_position < int((AZ_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.) / 2)) || (az_incremental_encoder_position > int((AZ_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.) * 1.5))) {
        az_incremental_encoder_position = 0;
      } else {
        az_incremental_encoder_position = int(AZ_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.);
      }
    }

    az_3_phase_encoder_last_phase_a_state = current_phase_a;
    az_3_phase_encoder_last_phase_b_state = current_phase_b;

  }

} /* az_position_incremental_encoder_interrupt_handler */
  #endif // FEATURE_AZ_POSITION_INCREMENTAL_ENCODER
// --------------------------------------------------------------

#ifdef FEATURE_EL_POSITION_INCREMENTAL_ENCODER
void el_position_incremental_encoder_interrupt_handler(){

  byte rotation_result = 0;
  byte current_phase_a = digitalReadEnhanced(el_incremental_encoder_pin_phase_a);
  byte current_phase_b = digitalReadEnhanced(el_incremental_encoder_pin_phase_b);
  byte current_phase_z = digitalReadEnhanced(el_incremental_encoder_pin_phase_z);

  #ifdef DEBUG_EL_POSITION_INCREMENTAL_ENCODER
  el_position_incremental_encoder_interrupt++;
  #endif // DEBUG_EL_POSITION_INCREMENTAL_ENCODER

  if ((el_3_phase_encoder_last_phase_a_state != current_phase_a) || (el_3_phase_encoder_last_phase_b_state != current_phase_b)) {
    if (el_3_phase_encoder_last_phase_a_state == LOW) {
      rotation_result++;
    }
    rotation_result = rotation_result << 1;
    if (el_3_phase_encoder_last_phase_b_state == LOW) {
      rotation_result++;
    }
    rotation_result = rotation_result << 1;
    if (current_phase_a == LOW) {
      rotation_result++;
    }
    rotation_result = rotation_result << 1;
    if (current_phase_b == LOW) {
      rotation_result++;
    }
    switch (rotation_result) {
      case B0010: //el_incremental_encoder_position++; break;
      case B1011: //el_incremental_encoder_position++; break;
      case B1101: //el_incremental_encoder_position++; break;
      case B0100: el_incremental_encoder_position++; break;

      case B0001: //el_incremental_encoder_position--; break;
      case B0111: //el_incremental_encoder_position--; break;
      case B1110: //el_incremental_encoder_position--; break;
      case B1000: el_incremental_encoder_position--; break;
    }


    if ((current_phase_a == LOW) && (current_phase_b == LOW) && (current_phase_z == LOW)) {
      el_incremental_encoder_position = 0;
    } else {

      if (el_incremental_encoder_position < 0) {
        el_incremental_encoder_position = int((EL_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.) - 1);
      }

      if (el_incremental_encoder_position >= int(EL_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.)) {
        el_incremental_encoder_position = 0;
      }  

    } 

    /*

    if (el_incremental_encoder_position > ((int((EL_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.)) - 1) * 2)) {
      el_incremental_encoder_position = 0;
    }
    if (el_incremental_encoder_position < 0) {
      el_incremental_encoder_position = ((int(((EL_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.)*4.)) - 1) * 2);
    }

    if ((current_phase_a == LOW) && (current_phase_b == LOW) && (current_phase_z == LOW)) {
      if ((el_incremental_encoder_position < int((EL_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.) / 2)) || (el_incremental_encoder_position > int((EL_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.) * 1.5))) {
        el_incremental_encoder_position = 0;
      } else {
        el_incremental_encoder_position = int((EL_POSITION_INCREMENTAL_ENCODER_PULSES_PER_REV*4.));
      }
    }

    */

    el_3_phase_encoder_last_phase_a_state = current_phase_a;
    el_3_phase_encoder_last_phase_b_state = current_phase_b;

  }

} /* el_position_incremental_encoder_interrupt_handler */
  #endif // FEATURE_EL_POSITION_INCREMENTAL_ENCODER

// --------------------------------------------------------------

void pinModeEnhanced(uint8_t pin, uint8_t mode){

  #if !defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) && !defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
  pinMode(pin, mode);
  #else
  if (pin < 100) {
    pinMode(pin, mode);
  } else {
    submit_remote_command(REMOTE_UNIT_DHL_COMMAND, pin, mode);
  }
  #endif // !defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) && !defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)

}

// --------------------------------------------------------------

void digitalWriteEnhanced(uint8_t pin, uint8_t writevalue){



  #if !defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) && !defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
  digitalWrite(pin, writevalue);
  #else
  if (pin < 100) {
    digitalWrite(pin, writevalue);
  } else {
    submit_remote_command(REMOTE_UNIT_DHL_COMMAND, pin, writevalue);
  }
  #endif // !defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) && !defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)

}

// --------------------------------------------------------------

int digitalReadEnhanced(uint8_t pin){

  return digitalRead(pin);

}

// --------------------------------------------------------------

int analogReadEnhanced(uint8_t pin){

  #ifdef OPTION_EXTERNAL_ANALOG_REFERENCE
  analogReference(EXTERNAL);
  #endif //OPTION_EXTERNAL_ANALOG_REFERENCE
  return analogRead(pin);

}

// --------------------------------------------------------------


void analogWriteEnhanced(uint8_t pin, int writevalue){


  #if !defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) && !defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
  analogWrite(pin, writevalue);
  #else
  if (pin < 100) {
    analogWrite(pin, writevalue);
  } else {
    submit_remote_command(REMOTE_UNIT_AW_COMMAND, pin, writevalue);
  }
  #endif // !defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) && !defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)

}


// --------------------------------------------------------------

#if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
void take_care_of_pending_remote_command(){

  // if there's a command already sent to the remote and we're awaiting the response, service the serial buffer and the queue

  unsigned long start_time = millis();

  while ((remote_unit_command_submitted) && ((millis() - start_time) < 200)) {
    #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE)
    check_serial();
    #endif //defined(FEATURE_MASTER_WITH_SERIAL_SLAVE)
    #if defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
    service_ethernet();
    #endif //defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
    service_remote_communications_incoming_buffer();
  }


}
#endif // defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
// --------------------------------------------------------------
#ifdef FEATURE_MOON_TRACKING
void service_moon_tracking(){

  static unsigned long last_check = 0;
  static byte moon_tracking_activated_by_activate_line = 0;

  static byte moon_tracking_pin_state = 0;

  if (moon_tracking_active_pin) {
    if ((moon_tracking_active) && (!moon_tracking_pin_state)) {
      digitalWriteEnhanced(moon_tracking_active_pin, HIGH);
      moon_tracking_pin_state = 1;
    }
    if ((!moon_tracking_active) && (moon_tracking_pin_state)) {
      digitalWriteEnhanced(moon_tracking_active_pin, LOW);
      moon_tracking_pin_state = 0;
    }
  }

  if (moon_tracking_activate_line) {
    if ((!moon_tracking_active) && (!digitalReadEnhanced(moon_tracking_activate_line))) {
      moon_tracking_active = 1;
      moon_tracking_activated_by_activate_line = 1;
    }
    if ((moon_tracking_active) && (digitalReadEnhanced(moon_tracking_activate_line)) && (moon_tracking_activated_by_activate_line)) {
      moon_tracking_active = 0;
      moon_tracking_activated_by_activate_line = 0;
    }
  }

  if ((moon_tracking_active) && ((millis() - last_check) > MOON_TRACKING_CHECK_INTERVAL)) {

    update_time();
    update_moon_position();

    #ifdef DEBUG_MOON_TRACKING
    control_port->print(F("service_moon_tracking: AZ: "));
    control_port->print(moon_azimuth);
    control_port->print(" EL: ");
    control_port->print(moon_elevation);
    control_port->print(" lat: ");
    control_port->print(latitude);
    control_port->print(" long: ");
    control_port->println(longitude);
    #endif // DEBUG_MOON_TRACKING

    if ((moon_azimuth >= MOON_AOS_AZIMUTH_MIN) && (moon_azimuth <= MOON_AOS_AZIMUTH_MAX) && (moon_elevation >= MOON_AOS_ELEVATION_MIN) && (moon_elevation <= MOON_AOS_ELEVATION_MAX)) {
      submit_request(AZ, REQUEST_AZIMUTH, moon_azimuth * HEADING_MULTIPLIER, 11);
      submit_request(EL, REQUEST_ELEVATION, moon_elevation * HEADING_MULTIPLIER, 12);
      if (!moon_visible) {
        moon_visible = 1;
        #ifdef DEBUG_MOON_TRACKING
        control_port->println(F("service_moon_tracking: moon AOS"));
        #endif // DEBUG_MOON_TRACKING
      }
    } else {
      if (moon_visible) {
        moon_visible = 0;
          #ifdef DEBUG_MOON_TRACKING
        control_port->println(F("service_moon_tracking: moon loss of AOS"));
          #endif // DEBUG_MOON_TRACKING
      } else {
            #ifdef DEBUG_MOON_TRACKING
        control_port->println(F("service_moon_tracking: moon out of AOS limits"));
            #endif // DEBUG_MOON_TRACKING
      }
    }

    last_check = millis();
  }



} /* service_moon_tracking */
    #endif // FEATURE_MOON_TRACKING

// --------------------------------------------------------------
#ifdef FEATURE_SUN_TRACKING

void update_sun_position(){

  update_time();
  c_time.iYear = clock_years;
  c_time.iMonth = clock_months;
  c_time.iDay = clock_days;

  c_time.dHours = clock_hours;
  c_time.dMinutes = clock_minutes;
  c_time.dSeconds = clock_seconds;

  c_loc.dLongitude = longitude;
  c_loc.dLatitude  = latitude;

  c_sposn.dZenithAngle = 0;
  c_sposn.dAzimuth = 0;

  sunpos(c_time, c_loc, &c_sposn);

  // Convert Zenith angle to elevation
  sun_elevation = 90. - c_sposn.dZenithAngle;
  sun_azimuth = c_sposn.dAzimuth;

} /* update_sun_position */
#endif // FEATURE_SUN_TRACKING

// --------------------------------------------------------------
#ifdef FEATURE_SUN_TRACKING
void service_sun_tracking(){

  static unsigned long last_check = 0;
  static byte sun_tracking_pin_state = 0;
  static byte sun_tracking_activated_by_activate_line = 0;

  if (sun_tracking_active_pin) {
    if ((sun_tracking_active) && (!sun_tracking_pin_state)) {
      digitalWriteEnhanced(sun_tracking_active_pin, HIGH);
      sun_tracking_pin_state = 1;
    }
    if ((!sun_tracking_active) && (sun_tracking_pin_state)) {
      digitalWriteEnhanced(sun_tracking_active_pin, LOW);
      sun_tracking_pin_state = 0;
    }
  }

  if (sun_tracking_activate_line) {
    if ((!sun_tracking_active) && (!digitalReadEnhanced(sun_tracking_activate_line))) {
      sun_tracking_active = 1;
      sun_tracking_activated_by_activate_line = 1;
    }
    if ((sun_tracking_active) && (digitalReadEnhanced(sun_tracking_activate_line)) && (sun_tracking_activated_by_activate_line)) {
      sun_tracking_active = 0;
      sun_tracking_activated_by_activate_line = 0;
    }
  }

  if ((sun_tracking_active) && ((millis() - last_check) > SUN_TRACKING_CHECK_INTERVAL)) {

    update_time();
    update_sun_position();


    #ifdef DEBUG_SUN_TRACKING
    control_port->print(F("service_sun_tracking: AZ: "));
    control_port->print(sun_azimuth);
    control_port->print(" EL: ");
    control_port->print(sun_elevation);
    control_port->print(" lat: ");
    control_port->print(latitude);
    control_port->print(" long: ");
    control_port->println(longitude);
    #endif // DEBUG_SUN_TRACKING

    if ((sun_azimuth >= SUN_AOS_AZIMUTH_MIN) && (sun_azimuth <= SUN_AOS_AZIMUTH_MAX) && (sun_elevation >= SUN_AOS_ELEVATION_MIN) && (sun_elevation <= SUN_AOS_ELEVATION_MAX)) {
      submit_request(AZ, REQUEST_AZIMUTH, sun_azimuth * HEADING_MULTIPLIER, 13);
      submit_request(EL, REQUEST_ELEVATION, sun_elevation * HEADING_MULTIPLIER, 14);
      if (!sun_visible) {
        sun_visible = 1;
        #ifdef DEBUG_SUN_TRACKING
        control_port->println(F("service_sun_tracking: sun AOS"));
        #endif // DEBUG_SUN_TRACKING
      }
    } else {
      if (sun_visible) {
        sun_visible = 0;
          #ifdef DEBUG_SUN_TRACKING
        control_port->println(F("service_sun_tracking: sun loss of AOS"));
          #endif // DEBUG_SUN_TRACKING
      } else {
            #ifdef DEBUG_SUN_TRACKING
        control_port->println(F("service_sun_tracking: sun out of AOS limits"));
            #endif // DEBUG_SUN_TRACKING
      }
    }

    last_check = millis();
  }




} /* service_sun_tracking */
#endif // FEATURE_SUN_TRACKING
// --------------------------------------------------------------

#ifdef FEATURE_CLOCK
void update_time(){
  unsigned long runtime = millis() - millis_at_last_calibration;

  unsigned long time = (3600L * clock_hour_set) + (60L * clock_min_set) + clock_sec_set + ((runtime + (runtime * INTERNAL_CLOCK_CORRECTION)) / 1000.0);

  clock_years = clock_year_set;
  clock_months = clock_month_set;
  clock_days = time / 86400L;
  time -= clock_days * 86400L;
  clock_days += clock_day_set;
  clock_hours = time / 3600L;

  switch (clock_months) {

    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      if (clock_days > 31) {
        clock_days = 1; clock_months++;
      }
      break;

    case 2:
      if ((float(clock_years) / 4.0) == 0.0) {  // do we have a leap year?
        if (clock_days > 29) {
          clock_days = 1; clock_months++;
        }
      } else {
        if (clock_days > 28) {
          clock_days = 1; clock_months++;
        }
      }
      break;

    case 4:
    case 6:
    case 9:
    case 11:
      if (clock_days > 30) {
        clock_days = 1; clock_months++;
      }
      break;
  } /* switch */

  if (clock_months > 12) {
    clock_months = 1; clock_years++;
  }

  time -= clock_hours * 3600L;
  clock_minutes  = time / 60L;
  time -= clock_minutes * 60L;
  clock_seconds = time;
} /* update_time */
    #endif // FEATURE_CLOCK


// --------------------------------------------------------------
#ifdef FEATURE_GPS
void service_gps(){

  long gps_lat, gps_lon;
  unsigned long fix_age;
  int gps_year;
  byte gps_month, gps_day, gps_hours, gps_minutes, gps_seconds, gps_hundredths;
  byte gps_sync_pin_active = 0;
  #ifdef DEBUG_GPS
  char tempstring[10] = "";
  #endif //#ifdef DEBUG_GPS

  static unsigned long last_sync = 0;

  if (gps_data_available) {
    // retrieves +/- lat/long in 100000ths of a degree
    gps.get_position(&gps_lat, &gps_lon, &fix_age);
    gps.crack_datetime(&gps_year, &gps_month, &gps_day, &gps_hours, &gps_minutes, &gps_seconds, &gps_hundredths, &fix_age);
    #ifdef DEBUG_GPS
    #ifdef DEBUG_GPS_SERIAL
    debug_println("");
    #endif //DEBUG_GPS_SERIAL    
    debug_print("service_gps: fix_age:");
    debug_print_int(fix_age);
    debug_print(" lat:");
    debug_print_float(gps_lat,4);
    debug_print(" long:");
    debug_print_float(gps_lon,4);
    debug_print(" ");
    debug_print_int(gps_year);
    debug_print("-");
    debug_print_int(gps_month);
    debug_print("-");
    debug_print_int(gps_day);
    debug_print(" ");
    debug_print_int(gps_hours);
    debug_print(":");
    debug_print_int(gps_minutes);
    debug_println("");
    #endif // DEBUG_GPS

    if (fix_age < GPS_VALID_FIX_AGE_MS) {

      if (SYNC_TIME_WITH_GPS) {
        clock_year_set = gps_year;
        clock_month_set = gps_month;
        clock_day_set = gps_day;
        clock_hour_set = gps_hours;
        clock_min_set = gps_minutes;
        clock_sec_set = gps_seconds;
        millis_at_last_calibration = millis() - GPS_UPDATE_LATENCY_COMPENSATION_MS;
        update_time();
        #ifdef DEBUG_GPS
        #ifdef DEBUG_GPS_SERIAL
        debug_println("");
        #endif //DEBUG_GPS_SERIAL        
        debug_print("service_gps: clock sync:");
        sprintf(tempstring,"%s",clock_string());
        debug_print(tempstring);
        debug_println("");
        #endif // DEBUG_GPS
      }

      #if defined(OPTION_SYNC_RTC_TO_GPS) && defined(FEATURE_RTC_DS1307)
      static unsigned long last_rtc_gps_sync_time;
      if ((millis() - last_rtc_gps_sync_time) >= (SYNC_RTC_TO_GPS_SECONDS * 1000)) {
        rtc.adjust(DateTime(gps_year, gps_month, gps_day, gps_hours, gps_minutes, gps_seconds));
        #ifdef DEBUG_RTC
        debug_println("service_gps: synced RTC");
        #endif // DEBUG_RTC
        last_rtc_gps_sync_time = millis();
      }
      #endif // defined(OPTION_SYNC_RTC_TO_GPS) && defined(FEATURE_RTC_DS1307)

      #if defined(OPTION_SYNC_RTC_TO_GPS) && defined(FEATURE_RTC_PCF8583)
      static unsigned long last_rtc_gps_sync_time;
      if ((millis() - last_rtc_gps_sync_time) >= (SYNC_RTC_TO_GPS_SECONDS * 1000)) {
        rtc.year = gps_year;
        rtc.month = gps_month;
        rtc.day = gps_day;
        rtc.hour  = gps_hours;
        rtc.minute = gps_minutes;
        rtc.second = gps_seconds;
        rtc.set_time();
        #ifdef DEBUG_RTC
        debug_println("service_gps: synced RTC");
        #endif // DEBUG_RTC
        last_rtc_gps_sync_time = millis();
      }
      #endif // defined(OPTION_SYNC_RTC_TO_GPS) && defined(FEATURE_RTC_PCF8583)


      #if defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)
      if (SYNC_COORDINATES_WITH_GPS) {
        latitude = float(gps_lat) / 1000000.0;
        longitude = float(gps_lon) / 1000000.0;
        #ifdef DEBUG_GPS
        debug_print("service_gps: coord sync:");
        debug_print_float(latitude,2);
        debug_print(" ");
        debug_print_float(longitude,2);
        debug_println("");
        #endif // DEBUG_GPS
      }
      #endif // defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)

      last_sync = millis();
    }

    gps_data_available = 0;
  }

  if ((millis() > (GPS_SYNC_PERIOD_SECONDS * 1000)) && ((millis() - last_sync) < (GPS_SYNC_PERIOD_SECONDS * 1000)) && (SYNC_TIME_WITH_GPS)) {
    clock_status = GPS_SYNC;
    if ((!gps_sync_pin_active) && (gps_sync)){
      digitalWriteEnhanced(gps_sync,HIGH);
      gps_sync_pin_active = 1;  
    }
  } else {
    if (clock_status == GPS_SYNC) {
      clock_status = FREE_RUNNING;
      if (gps_sync_pin_active){
        digitalWriteEnhanced(gps_sync,LOW);
        gps_sync_pin_active = 0;  
      }
    }
  }


} /* service_gps */
  #endif // FEATURE_GPS
// --------------------------------------------------------------
#ifdef FEATURE_MOON_TRACKING

void update_moon_position(){

  update_time();

  double RA, Dec, topRA, topDec, LST, HA, dist;
  update_time();
  moon2(clock_years, clock_months, clock_days, (clock_hours + (clock_minutes / 60.0) + (clock_seconds / 3600.0)), longitude, latitude, &RA, &Dec, &topRA, &topDec, &LST, &HA, &moon_azimuth, &moon_elevation, &dist);


}
#endif // FEATURE_SUN_TRACKING
// --------------------------------------------------------------
#if defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)
byte calibrate_az_el(float new_az, float new_el){

  #ifdef DEBUG_OFFSET
  control_port->print("calibrate_az_el: new_az:");
  control_port->print(new_az, 2);
  control_port->print(" new_el:");
  control_port->println(new_el, 2);
  #endif // DEBUG_OFFSET



  if ((new_az >= 0 ) && (new_az <= 360) && (new_el >= 0) && (new_el <= 90)) {
    configuration.azimuth_offset = 0;
    configuration.elevation_offset = 0;
    read_azimuth(1);
    read_elevation(1);

    #ifdef DEBUG_OFFSET
    control_port->print("calibrate_az_el: az:");
    control_port->print(azimuth / LCD_HEADING_MULTIPLIER, 2);
    control_port->print(" el:");
    control_port->println(elevation / LCD_HEADING_MULTIPLIER, 2);
    #endif // DEBUG_OFFSET


    configuration.azimuth_offset = new_az - (float(azimuth) / float(HEADING_MULTIPLIER));
    #if defined(FEATURE_ELEVATION_CONTROL)
    configuration.elevation_offset = new_el - (float(elevation) / float(HEADING_MULTIPLIER));
    #endif
    configuration_dirty = 1;
    return 1;
  } else {
    return 0;
  }

} /* calibrate_az_el */
  #endif // defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)
// --------------------------------------------------------------

#ifdef FEATURE_RTC
void service_rtc(){

  static unsigned long last_rtc_sync_time = 0;

  if (((millis() - last_rtc_sync_time) >= (SYNC_WITH_RTC_SECONDS * 1000)) || (clock_status == FREE_RUNNING)){
    last_rtc_sync_time = millis();
    #ifdef FEATURE_GPS
    if (clock_status == GPS_SYNC) { // if we're also equipped with GPS and we're synced to it, don't sync to realtime clock
      #ifdef DEBUG_RTC
      debug_println("service_rtc: synced to GPS already.  Exiting.");
      #endif // DEBUG_RTC
      return;
    }
    #endif // FEATURE_GPS


    #ifdef FEATURE_RTC_DS1307
    if (rtc.isrunning()) {
      DateTime now = rtc.now();
      #ifdef DEBUG_RTC
      debug_print("service_rtc: syncing: ");
      debug_print_int(now.year());
      debug_print("/");
      debug_print_int(now.month());
      debug_print("/");
      debug_print_int(now.day());
      debug_print(" ");
      debug_print_int(now.hour());
      debug_print(":");
      debug_print_int(now.minute());
      debug_print(":");
      debug_print_int(now.second());
      debug_println("");
      #endif // DEBUG_RTC
      clock_year_set = now.year();
      clock_month_set = now.month();
      clock_day_set = now.day();
      clock_hour_set = now.hour();
      clock_min_set = now.minute();
      clock_sec_set = now.second();
      millis_at_last_calibration = millis();
      update_time();
      clock_status = RTC_SYNC;
    } else {
      clock_status = FREE_RUNNING;
      #ifdef DEBUG_RTC
      debug_println("service_rtc: error: RTC not running");
      #endif // DEBUG_RTC
    }
    #endif //#FEATURE_RTC_DS1307



    #ifdef FEATURE_RTC_PCF8583
    rtc.get_time();
    if ((rtc.year > 2000) && (rtc.month > 0) && (rtc.month < 13)){  // do we have a halfway reasonable date?
      #ifdef DEBUG_RTC
      control_port->print("service_rtc: syncing: ");
      control_port->print(rtc.year, DEC);
      control_port->print('/');
      control_port->print(rtc.month, DEC);
      control_port->print('/');
      control_port->print(rtc.day, DEC);
      control_port->print(' ');
      control_port->print(rtc.hour, DEC);
      control_port->print(':');
      control_port->print(rtc.minute, DEC);
      control_port->print(':');
      control_port->println(rtc.second, DEC);
      #endif // DEBUG_RTC
      clock_year_set = rtc.year;
      clock_month_set = rtc.month;
      clock_day_set = rtc.day;
      clock_hour_set = rtc.hour;
      clock_min_set = rtc.minute;
      clock_sec_set = rtc.second;
      millis_at_last_calibration = millis();
      update_time();
      clock_status = RTC_SYNC;
    } else {
      clock_status = FREE_RUNNING;
      #ifdef DEBUG_RTC
      control_port->print("service_rtc: error: RTC not returning valid date or time: ");
      control_port->print(rtc.year, DEC);
      control_port->print('/');
      control_port->print(rtc.month, DEC);
      control_port->print('/');
      control_port->print(rtc.day, DEC);
      control_port->print(' ');
      control_port->print(rtc.hour, DEC);
      control_port->print(':');
      control_port->print(rtc.minute, DEC);
      control_port->print(':');
      control_port->println(rtc.second, DEC);
      #endif // DEBUG_RTC
    }
    #endif //#FEATURE_RTC_PCF8583



  }
} /* service_rtc */
#endif // FEATURE_RTC

// -------------------------------------------------------------

byte process_backslash_command(byte input_buffer[], int input_buffer_index, byte source_port, char * return_string){

  strcpy(return_string,"");
  static unsigned long serial_led_time = 0;
  float tempfloat = 0;

  #if !defined(FEATURE_AZ_POSITION_ROTARY_ENCODER) && !defined(FEATURE_AZ_POSITION_PULSE_INPUT)
  long place_multiplier = 0;
  byte decimalplace = 0;
  #endif

  #ifdef FEATURE_CLOCK
  int temp_year = 0;
  byte temp_month = 0;
  byte temp_day = 0;
  byte temp_minute = 0;
  byte temp_hour = 0;
  #endif // FEATURE_CLOCK

  #if defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)
  char grid[10] = "";
  byte hit_error = 0;
  #endif // defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)

  #if defined(FEATURE_AZ_POSITION_ROTARY_ENCODER) || defined(FEATURE_AZ_POSITION_PULSE_INPUT)
  int new_azimuth = 9999;
  #endif
  #ifdef FEATURE_ELEVATION_CONTROL
  #if defined(FEATURE_EL_POSITION_ROTARY_ENCODER) || defined(FEATURE_EL_POSITION_PULSE_INPUT)
  int new_elevation = 9999;
  #endif // FEATURE_ELEVATION_CONTROL
  #endif // defined(FEATURE_AZ_POSITION_ROTARY_ENCODER) || defined(FEATURE_AZ_POSITION_PULSE_INPUT)

  char temp_string[20] = "";

  switch (input_buffer[1]) {

   #if defined(FEATURE_AZ_POSITION_ROTARY_ENCODER) || defined(FEATURE_AZ_POSITION_PULSE_INPUT)
    case 'A':      // \Ax[x][x] - manually set azimuth
      new_azimuth = 9999;
      switch (input_buffer_index) {
        case 3:
          new_azimuth = (input_buffer[2] - 48);
          break;
        case 4:
          new_azimuth = ((input_buffer[2] - 48) * 10) + (input_buffer[3] - 48);
          break;
        case 5:
          new_azimuth = ((input_buffer[2] - 48) * 100) + ((input_buffer[3] - 48) * 10) + (input_buffer[4] - 48);
          break;
      }
      if ((new_azimuth >= 0) && (new_azimuth < 360)) {
        azimuth = new_azimuth * HEADING_MULTIPLIER;
        configuration.last_azimuth = new_azimuth;
        raw_azimuth = new_azimuth * HEADING_MULTIPLIER;
        configuration_dirty = 1;
        strcpy(return_string, "Azimuth set to ");
        dtostrf(new_azimuth, 0, 0, temp_string);
        strcat(return_string, temp_string);
      } else {
        strcpy(return_string, "Error.  Format: \\Ax[x][x] ");
      }
      break;
        #else // defined(FEATURE_AZ_POSITION_ROTARY_ENCODER) || defined(FEATURE_AZ_POSITION_PULSE_INPUT)
    case 'A':      // \Ax[xxx][.][xxxx] - manually set azimuth
      place_multiplier = 1;
      for (int x = input_buffer_index - 1; x > 1; x--) {
        if (char(input_buffer[x]) != '.') {
          tempfloat += (input_buffer[x] - 48) * place_multiplier;
          place_multiplier = place_multiplier * 10;
        } else {
          decimalplace = x;
        }
      }
      if (decimalplace) {
        tempfloat = tempfloat / pow(10, (input_buffer_index - decimalplace - 1));
      }
      if ((tempfloat >= 0) && (tempfloat <= 360)) {
        configuration.azimuth_offset = 0;
        read_azimuth(1);
        configuration.azimuth_offset = tempfloat - float(azimuth / HEADING_MULTIPLIER);
        configuration_dirty = 1;
        strcpy(return_string, "Azimuth calibrated to ");
        dtostrf(tempfloat, 0, 2, temp_string);
        strcat(return_string, temp_string);
      } else {
        strcpy(return_string, "Error.");
      }

      break;
      #endif // defined(FEATURE_AZ_POSITION_ROTARY_ENCODER) || defined(FEATURE_AZ_POSITION_PULSE_INPUT)


    #if defined(FEATURE_ELEVATION_CONTROL)
    #if defined(FEATURE_EL_POSITION_ROTARY_ENCODER) || defined(FEATURE_EL_POSITION_PULSE_INPUT)
    case 'B':      // \Ax[x][x] - manually set elevation
      new_elevation = 9999;
      switch (input_buffer_index) {
        case 3:
          new_elevation = (input_buffer[2] - 48);
          break;
        case 4:
          new_elevation = ((input_buffer[2] - 48) * 10) + (input_buffer[3] - 48);
          break;
        case 5:
          new_elevation = ((input_buffer[2] - 48) * 100) + ((input_buffer[3] - 48) * 10) + (input_buffer[4] - 48);
          break;
      }
      if ((new_elevation >= 0) && (new_elevation <= 180)) {
        elevation = new_elevation * HEADING_MULTIPLIER;
        configuration.last_elevation = new_elevation;
        configuration_dirty = 1;
        strcpy(return_string, "Elevation set to ");
        dtostrf(new_elevation, 0, 0, temp_string);
        strcat(return_string, temp_string);
      } else {
        strcpy(return_string, "Error.  Format: \\Bx[x][x]");
      }
      break;
      #else // defined(FEATURE_EL_POSITION_ROTARY_ENCODER) || defined(FEATURE_EL_POSITION_PULSE_INPUT)
    case 'B':      // \Bx[xxx][.][xxxx] - manually set elevation
      place_multiplier = 1;
      for (int x = input_buffer_index - 1; x > 1; x--) {
        if (char(input_buffer[x]) != '.') {
          tempfloat += (input_buffer[x] - 48) * place_multiplier;
          place_multiplier = place_multiplier * 10;
        } else {
          decimalplace = x;
        }
      }
      if (decimalplace) {
        tempfloat = tempfloat / pow(10, (input_buffer_index - decimalplace - 1));
      }
      if ((tempfloat >= 0) && (tempfloat <= 180)) {
        configuration.elevation_offset = 0;
        read_elevation(1);
        configuration.elevation_offset = tempfloat - float(elevation / HEADING_MULTIPLIER);
        configuration_dirty = 1;
        strcpy(return_string, "Elevation calibrated to ");
        dtostrf(tempfloat, 0, 2, temp_string);
        strcat(return_string, temp_string);
      } else {
        strcpy(return_string, "Error.");
      }
      break;
      #endif // defined(FEATURE_EL_POSITION_ROTARY_ENCODER) || defined(FEATURE_EL_POSITION_PULSE_INPUT)
      #endif //FEATURE_ELEVATION_CONTROL

    #ifdef FEATURE_CLOCK
    case 'C':         // show clock
      update_time();
      sprintf(return_string, "%s", clock_string());


      break;
    case 'O':         // set clock
      temp_year = ((input_buffer[2] - 48) * 1000) + ((input_buffer[3] - 48) * 100) + ((input_buffer[4] - 48) * 10) + (input_buffer[5] - 48);
      temp_month = ((input_buffer[6] - 48) * 10) + (input_buffer[7] - 48);
      temp_day = ((input_buffer[8] - 48) * 10) + (input_buffer[9] - 48);
      temp_hour = ((input_buffer[10] - 48) * 10) + (input_buffer[11] - 48);
      temp_minute = ((input_buffer[12] - 48) * 10) + (input_buffer[13] - 48);
      if ((temp_year > 2013) && (temp_year < 2070) &&
          (temp_month > 0) && (temp_month < 13) &&
          (temp_day > 0) && (temp_day < 32) &&
          (temp_hour >= 0) && (temp_hour < 24) &&
          (temp_minute >= 0) && (temp_minute < 60) &&
          (input_buffer_index == 14)) {

        clock_year_set = temp_year;
        clock_month_set = temp_month;
        clock_day_set = temp_day;
        clock_hour_set = temp_hour;
        clock_min_set = temp_minute;
        clock_sec_set = 0;
        millis_at_last_calibration = millis();





        #if defined(FEATURE_RTC_DS1307)
        rtc.adjust(DateTime(temp_year, temp_month, temp_day, temp_hour, temp_minute, 0));
        #endif // defined(FEATURE_RTC_DS1307)
        #if defined(FEATURE_RTC_PCF8583)
        rtc.year = temp_year;
        rtc.month = temp_month;
        rtc.day = temp_day;
        rtc.hour  = temp_hour;
        rtc.minute = temp_minute;
        rtc.second = 0;
        rtc.set_time();
        #endif // defined(FEATURE_RTC_PCF8583)

        #if (!defined(FEATURE_RTC_DS1307) && !defined(FEATURE_RTC_PCF8583))
        strcpy(return_string, "Clock set to ");
        update_time();
        strcat(return_string, clock_string());
        #else
        strcpy(return_string, "Internal clock and RTC set to ");
        update_time();
        strcat(return_string, clock_string());
        #endif


      } else {
        strcpy(return_string, "Error. Usage: \\OYYYYMMDDHHmm");
      }
      break;
          #endif // FEATURE_CLOCK


    case 'D': 
      if (debug_mode & source_port) {
        debug_mode = debug_mode & (~source_port);
      } else {
        debug_mode = debug_mode | source_port;
      } 
      break;                                              // D - Debug

    case 'E':                                                                      // E - Initialize eeprom
      initialize_eeprom_with_defaults();
      strcpy(return_string, "Initialized eeprom, please reset...");
      break;

    case 'L':                                                                      // L - rotate to long path
      if (azimuth < (180 * HEADING_MULTIPLIER)) {
        submit_request(AZ, REQUEST_AZIMUTH, (azimuth + (180 * HEADING_MULTIPLIER)), 15);
      } else {
        submit_request(AZ, REQUEST_AZIMUTH, (azimuth - (180 * HEADING_MULTIPLIER)), 16);
      }
      break;

 #if defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)
    case 'G':   // G - set coordinates using grid square
      if (isalpha(input_buffer[2])) {
        grid[0] = input_buffer[2];
      } else { hit_error = 1; }
      if (isalpha(input_buffer[3])) {
        grid[1] = input_buffer[3];
      } else { hit_error = 1; }
      if (isdigit(input_buffer[4])) {
        grid[2] = input_buffer[4];
      } else { hit_error = 1; }
      if (isdigit(input_buffer[5])) {
        grid[3] = input_buffer[5];
      } else { hit_error = 1; }
      if (isalpha(input_buffer[6])) {
        grid[4] = input_buffer[6];
      } else { hit_error = 1; }
      if (isalpha(input_buffer[7])) {
        grid[5] = input_buffer[7];
      } else { hit_error = 1; }
      if ((input_buffer_index != 8) || (hit_error)) {
        strcpy(return_string, "Error.  Usage \\Gxxxxxx");
      } else {
        grid2deg(grid, &longitude, &latitude);
        strcpy(return_string, "Coordinates set to: ");
        dtostrf(latitude, 0, 4, temp_string);
        strcat(return_string, temp_string);
        strcat(return_string, " ");
        dtostrf(longitude, 0, 4, temp_string);
        strcat(return_string, temp_string);
      }
      break;
 #endif // defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)

  #ifdef FEATURE_MOON_TRACKING
    case 'M':
      switch (input_buffer[2]) {
        case '0':
          submit_request(AZ, REQUEST_STOP, 0, 17);
          submit_request(EL, REQUEST_STOP, 0, 18);
          strcpy(return_string, "Moon tracking deactivated.");
          break;
        case '1':
          moon_tracking_active = 1;
  #ifdef FEATURE_SUN_TRACKING
          sun_tracking_active = 0;
  #endif // FEATURE_SUN_TRACKING
          strcpy(return_string, "Moon tracking activated.");
          break;
        default: strcpy(return_string, "Error."); break;
      }
      break;
  #endif // FEATURE_MOON_TRACKING

  #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
    case 'R':
      strcpy(return_string, "Remote port rx sniff o");
      if (remote_port_rx_sniff) {
        remote_port_rx_sniff = 0;
        strcat(return_string, "ff");
      } else {
        remote_port_rx_sniff = 1;
        strcat(return_string, "n");
      }
      break;
    case 'S':
      #if defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
      ethernetslavelinkclient0.print(ETHERNET_PREAMBLE);
      #endif    
      for (int x = 2; x < input_buffer_index; x++) {
        #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE)
        remote_unit_port->write(input_buffer[x]);
        #endif
        #if defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
        ethernetslavelinkclient0.write(input_buffer[x]);
        #endif
        if (remote_port_tx_sniff) {
          control_port->write(input_buffer[x]);
        }
      }
      #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE)
      remote_unit_port->write(13);
      #endif
      #if defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)
      ethernetslavelinkclient0.write(13);
      #endif      
      if (remote_port_tx_sniff) {
        control_port->write(13);
      }
      break;
    case 'T':
      strcpy(return_string, "Remote port tx sniff o");
      if (remote_port_tx_sniff) {
        remote_port_tx_sniff = 0;
        strcat(return_string, "ff");
      } else {
        remote_port_tx_sniff = 1;
        strcat(return_string, "n");
      }
      break;
    case 'Z':
      strcpy(return_string, "Suspend auto remote commands o");
      if (suspend_remote_commands) {
        suspend_remote_commands = 0;
        strcat(return_string, "ff");
      } else {
        suspend_remote_commands = 1;
        strcat(return_string, "n");
      }
      break;
  #endif // defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE)

  #ifdef FEATURE_SUN_TRACKING
    case 'U':     // activate / deactivate sun tracking
      switch (input_buffer[2]) {
        case '0':
          submit_request(AZ, REQUEST_STOP, 0, 19);
          submit_request(EL, REQUEST_STOP, 0, 20);
          strcpy(return_string, "Sun tracking deactivated.");
          break;
        case '1':
          sun_tracking_active = 1;
          strcpy(return_string, "Sun tracking activated.");
  #ifdef FEATURE_MOON_TRACKING
          moon_tracking_active = 0;
  #endif // FEATURE_MOON_TRACKING
          break;
        default: strcpy(return_string, "Error."); break;
      }
      break;

  #endif // FEATURE_SUN_TRACKING

  #if defined(FEATURE_SUN_TRACKING) || defined(FEATURE_MOON_TRACKING)
    case 'X':
      switch (toupper(input_buffer[2])) {
        #if defined(FEATURE_SUN_TRACKING)
        case 'S':
          update_sun_position();
          if (calibrate_az_el(sun_azimuth, sun_elevation)) {
            strcpy(return_string, az_el_calibrated_string());
          } else {
            strcpy(return_string, "Error.");
          }
          break;
        #endif // FEATURE_SUN_TRACKING
        #if defined(FEATURE_MOON_TRACKING)
        case 'M':
          update_moon_position();
          if (calibrate_az_el(moon_azimuth, moon_elevation)) {
            strcpy(return_string, az_el_calibrated_string());
          } else {
            strcpy(return_string, "Error.");
          }
          break;
        #endif // FEATURE_MOON_TRACKING
        case '0':
          configuration.azimuth_offset = 0;
          configuration.elevation_offset = 0;
          configuration_dirty = 1;
          break;
        default: strcpy(return_string, "?>"); break;


      } /* switch */
      break;
      #endif // defined(FEATURE_SUN_TRACKING) || defined(FEATURE_MOON_TRACKING)

    #ifdef FEATURE_PARK
    case 'P':    // Park
      strcpy(return_string, "Parking...");
      initiate_park();
      park_serial_initiated = 1;
      break;
      #endif // FEATURE_PARK

    #ifdef FEATURE_ANCILLARY_PIN_CONTROL
    case 'N':      // \Nxx - turn pin on; xx = pin number
      if ((((input_buffer[2] > 47) && (input_buffer[2] < 58)) || (toupper(input_buffer[2]) == 'A')) && (input_buffer[3] > 47) && (input_buffer[3] < 58) && (input_buffer_index == 4)) {
        byte pin_value = 0;
        if (toupper(input_buffer[2]) == 'A') {
          pin_value = get_analog_pin(input_buffer[3] - 48);
        } else {
          pin_value = ((input_buffer[2] - 48) * 10) + (input_buffer[3] - 48);
        }
        pinModeEnhanced(pin_value, OUTPUT);
        digitalWriteEnhanced(pin_value, HIGH);
        strcpy(return_string, "OK");
      } else {
        strcpy(return_string, "Error");
      }
      break;
    case 'F':      // \Fxx - turn pin off; xx = pin number
      if ((((input_buffer[2] > 47) && (input_buffer[2] < 58)) || (toupper(input_buffer[2]) == 'A')) && (input_buffer[3] > 47) && (input_buffer[3] < 58) && (input_buffer_index == 4)) {
        byte pin_value = 0;
        if (toupper(input_buffer[2]) == 'A') {
          pin_value = get_analog_pin(input_buffer[3] - 48);
        } else {
          pin_value = ((input_buffer[2] - 48) * 10) + (input_buffer[3] - 48);
        }
        pinModeEnhanced(pin_value, OUTPUT);
        digitalWriteEnhanced(pin_value, LOW);
        strcpy(return_string, "OK");
      } else {
        strcpy(return_string, "Error");
      }
      break;
    case 'W':    // \Wxxyyy - turn on pin PWM; xx = pin number, yyy = PWM value (0-255)
      if (((input_buffer[2] > 47) && (input_buffer[2] < 58)) && (input_buffer[3] > 47) && (input_buffer[3] < 58)  && (input_buffer_index == 7)) {
        byte pin_value = 0;
        if (toupper(input_buffer[2]) == 'A') {
          pin_value = get_analog_pin(input_buffer[3] - 48);
        } else {
          pin_value = ((input_buffer[2] - 48) * 10) + (input_buffer[3] - 48);
        }
        int write_value = ((input_buffer[4] - 48) * 100) + ((input_buffer[5] - 48) * 10) + (input_buffer[6] - 48);
        if ((write_value >= 0) && (write_value < 256)) {
          pinModeEnhanced(pin_value, OUTPUT);
          analogWriteEnhanced(pin_value, write_value);
          strcpy(return_string, "OK");
        } else {
          strcpy(return_string, "Error");
        }
      } else {
        strcpy(return_string, "Error");
      }
      break;
  #endif // FEATURE_ANCILLARY_PIN_CONTROL


    default: strcpy(return_string, "Error.");



  } /* switch */
} /* process_backslash_command */


// --------------------------------------------------------------
#ifdef FEATURE_CLOCK
char * clock_string(){

  char return_string[32] = "";
  char temp_string[16] = "";



  dtostrf(clock_years, 0, 0, temp_string);
  strcpy(return_string, temp_string);
  strcat(return_string, "-");
  if (clock_months < 10) {
    strcat(return_string, "0");
  }
  dtostrf(clock_months, 0, 0, temp_string);
  strcat(return_string, temp_string);
  strcat(return_string, "-");
  if (clock_days < 10) {
    strcat(return_string, "0");
  }
  dtostrf(clock_days, 0, 0, temp_string);
  strcat(return_string, temp_string);
  strcat(return_string, " ");

  if (clock_hours < 10) {
    strcat(return_string, "0");
  }
  dtostrf(clock_hours, 0, 0, temp_string);
  strcat(return_string, temp_string);
  strcat(return_string, ":");
  if (clock_minutes < 10) {
    strcat(return_string, "0");
  }
  dtostrf(clock_minutes, 0, 0, temp_string);
  strcat(return_string, temp_string);
  strcat(return_string, ":");
  if (clock_seconds < 10) {
    strcat(return_string, "0");
  }
  dtostrf(clock_seconds, 0, 0, temp_string);
  strcat(return_string, temp_string);
  strcat(return_string,"Z");
  return return_string;

} /* clock_string */
#endif // FEATURE_CLOCK


// --------------------------------------------------------------
#if defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)
char * az_el_calibrated_string(){

  char return_string[48] = "";
  char tempstring[16] = "";

  read_azimuth(1);
  read_elevation(1);
  strcpy(return_string, "Heading calibrated.  Az: ");
  dtostrf((azimuth / LCD_HEADING_MULTIPLIER), 0, LCD_DECIMAL_PLACES, tempstring);
  strcat(return_string, tempstring);
  #ifdef FEATURE_ELEVATION_CONTROL
  strcat(return_string, " El: ");
  dtostrf((elevation / LCD_HEADING_MULTIPLIER), 0, LCD_DECIMAL_PLACES, tempstring);
  strcat(return_string, tempstring);
  #endif //FEATURE_ELEVATION_CONTROL
  return return_string;

}
#endif // defined(FEATURE_MOON_TRACKING) || defined(FEATURE_SUN_TRACKING)
// --------------------------------------------------------------
void debug_print(char * print_string){

  if (debug_mode & CONTROL_PORT0){
    control_port->print(print_string);
  }

  #ifdef FEATURE_ETHERNET
  if (debug_mode & ETHERNET_PORT0){
    ethernetclient0.print(print_string);
  }
  #endif //FEATURE_ETHERNET

  #if defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1)
  if (debug_mode & ETHERNET_PORT1){
    ethernetclient1.print(print_string);
  }
  #endif //defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1)

}
// --------------------------------------------------------------
void debug_println(char * print_string){

  if (debug_mode & CONTROL_PORT0){
    control_port->println(print_string);
  }

  #ifdef FEATURE_ETHERNET
  if (debug_mode & ETHERNET_PORT0){
    ethernetclient0.println(print_string);
  }
  #endif //FEATURE_ETHERNET

  #if defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1)
  if (debug_mode & ETHERNET_PORT1){
    ethernetclient1.println(print_string);
  }
  #endif //defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1)

}
// --------------------------------------------------------------
void debug_print_char(char print_char){

  if (debug_mode & CONTROL_PORT0){
    control_port->print(print_char);
  }

  #ifdef FEATURE_ETHERNET
  if (debug_mode & ETHERNET_PORT0){
    ethernetclient0.print(print_char);
  }
  #endif //FEATURE_ETHERNET

  #if defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1)
  if (debug_mode & ETHERNET_PORT1){
    ethernetclient1.print(print_char);
  }
  #endif //defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1)
}
// --------------------------------------------------------------
void debug_write(char * print_string){

  if (debug_mode & CONTROL_PORT0){
    control_port->write(print_string);
  }

  #ifdef FEATURE_ETHERNET
  if (debug_mode & ETHERNET_PORT0){
    ethernetclient0.write(print_string);
  }
  #endif //FEATURE_ETHERNET

  #if defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1)
  if (debug_mode & ETHERNET_PORT1){
    ethernetclient1.write(print_string);
  }
  #endif //defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1) 

}
// --------------------------------------------------------------
void debug_print_int(int print_int){

  if (debug_mode & CONTROL_PORT0){
    control_port->print(print_int);
  }

  #ifdef FEATURE_ETHERNET
  if (debug_mode & ETHERNET_PORT0){
    ethernetclient0.print(print_int);
  }
  #endif //FEATURE_ETHERNET

  #if defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1)
  if (debug_mode & ETHERNET_PORT1){
    ethernetclient1.print(print_int);
  }
  #endif //defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1) 


}
// --------------------------------------------------------------
void debug_write_int(int write_int){

  if (debug_mode & CONTROL_PORT0){
    control_port->write(write_int);
  }

  #ifdef FEATURE_ETHERNET
  if (debug_mode & ETHERNET_PORT0){
    ethernetclient0.write(write_int);
  }  
  #endif //FEATURE_ETHERNET

  #if defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1)
  if (debug_mode & ETHERNET_PORT1){
    ethernetclient1.write(write_int);
  }  
  #endif //defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1)

}
// --------------------------------------------------------------
void debug_print_float(float print_float,byte places){

  char tempstring[16] = "";

  dtostrf(print_float,0,places,tempstring);

  if (debug_mode & CONTROL_PORT0){
    control_port->print(tempstring);
  }

  #ifdef FEATURE_ETHERNET
  if (debug_mode & ETHERNET_PORT0){
    ethernetclient0.print(tempstring);
  }
  #endif //FEATURE_ETHERNET

  #if defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1)
  if (debug_mode & ETHERNET_PORT1){
    ethernetclient1.print(tempstring);
  }
  #endif //defined(FEATURE_ETHERNET) && defined(ETHERNET_TCP_PORT_1)  

}
// --------------------------------------------------------------
#ifdef FEATURE_MOON_TRACKING
char * moon_status_string(){

    char returnstring[128] = "";
    char tempstring[16] = "";

    strcpy(returnstring,"\tmoon: AZ: ");
    dtostrf(moon_azimuth,0,2,tempstring);
    strcat(returnstring,tempstring);
    strcat(returnstring," EL: ");
    dtostrf(moon_elevation,0,2,tempstring);
    strcat(returnstring,tempstring);
    strcat(returnstring,"\tTRACKING_");
    if (!moon_tracking_active) {
      strcat(returnstring,"IN");
    }
    strcat(returnstring,"ACTIVE ");
    if (moon_tracking_active) {
      if (!moon_visible) {
        strcat(returnstring,"NOT_");
      }
      strcat(returnstring,"VISIBLE");
    }
    return returnstring;
}
#endif // FEATURE_MOON_TRACKING
// --------------------------------------------------------------
#ifdef FEATURE_SUN_TRACKING
char * sun_status_string(){

    char returnstring[128] = "";
    char tempstring[16] = "";

    strcpy(returnstring,"\tsun: AZ: ");
    dtostrf(sun_azimuth,0,2,tempstring);
    strcat(returnstring,tempstring);
    strcat(returnstring," EL: ");
    dtostrf(sun_elevation,0,2,tempstring);
    strcat(returnstring,tempstring);
    strcat(returnstring,"\tTRACKING_");
    if (!sun_tracking_active) {
      strcat(returnstring,"IN");
    }
    strcat(returnstring,"ACTIVE ");
    if (sun_tracking_active) {
      if (!sun_visible) {
        strcat(returnstring,"NOT_");
      }
      strcat(returnstring,"VISIBLE");
    }
    return returnstring;
}
#endif // FEATURE_SUN_TRACKING
// --------------------------------------------------------------
#ifdef FEATURE_CLOCK
char * clock_status_string(){

  switch (clock_status) {
    case FREE_RUNNING: return("FREE_RUNNING"); break;
    case GPS_SYNC: return("GPS_SYNC"); break;
    case RTC_SYNC: return("RTC_SYNC"); break;
    case SLAVE_SYNC: return("SLAVE_SYNC"); break;
  }
}
#endif //FEATURE_CLOCK
// --------------------------------------------------------------
#if defined(FEATURE_SUN_TRACKING) || defined(FEATURE_MOON_TRACKING)
char * coordinate_string(){

  char returnstring[32] = "";
  char tempstring[12] = "";

  dtostrf(latitude,0,4,returnstring);
  strcat(returnstring," ");
  dtostrf(longitude,0,4,tempstring);
  strcat(returnstring,tempstring);
  return returnstring;

}
#endif //defined(FEATURE_SUN_TRACKING) || defined(FEATURE_MOON_TRACKING)










// --------------------------------------------------------------
#ifdef FEATURE_YAESU_EMULATION
void process_yaesu_command(byte * yaesu_command_buffer, int yaesu_command_buffer_index, byte source_port, char * return_string){



    char tempstring[11] = "";
    int parsed_value = 0;
  
    int parsed_elevation = 0;
  

    #ifdef FEATURE_TIMED_BUFFER
    int parsed_value2 = 0;
    #endif //FEATURE_TIMED_BUFFER

    strcpy(return_string,"");

    switch (yaesu_command_buffer[0]) {          // look at the first character of the command
      case 'C':                                // C - return current azimuth
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: C\n");
        }
        #endif // DEBUG_PROCESS_YAESU
        #ifdef OPTION_DELAY_C_CMD_OUTPUT
        delay(400);
        #endif    
        //strcpy(return_string,"");
        #ifndef OPTION_GS_232B_EMULATION
        strcat(return_string,"+0");
        #else
        strcat(return_string,"AZ=");
        #endif
        dtostrf(int(azimuth / HEADING_MULTIPLIER),0,0,tempstring);
        if (int(azimuth / HEADING_MULTIPLIER) < 10) {
          strcat(return_string,"0");
        }
        if (int(azimuth / HEADING_MULTIPLIER) < 100) {
          strcat(return_string,"0");
        }
        strcat(return_string,tempstring);
      
        #ifdef FEATURE_ELEVATION_CONTROL
        #ifndef OPTION_C_COMMAND_SENDS_AZ_AND_EL
        if ((yaesu_command_buffer[1] == '2') && (yaesu_command_buffer_index > 1)) {     // did we get the C2 command?
        #endif


        #ifndef OPTION_GS_232B_EMULATION
        if (elevation < 0) {
          strcat(return_string,"-0");
        } else {
          strcat(return_string,"+0");
        }
        #endif
        #ifdef OPTION_GS_232B_EMULATION
        strcat(return_string,"EL=");
        #endif
        dtostrf(int(elevation / HEADING_MULTIPLIER),0,0,tempstring);
        if (int(elevation / HEADING_MULTIPLIER) < 10) {
          strcat(return_string,("0"));
        }
        if (int(elevation / HEADING_MULTIPLIER) < 100) {
          strcat(return_string,"0");
        }
        strcat(return_string,tempstring);

        #ifndef OPTION_C_COMMAND_SENDS_AZ_AND_EL
        } else {
          //strcat(return_string,"\n");
        }
        #endif // OPTION_C_COMMAND_SENDS_AZ_AND_EL
        #endif // FEATURE_ELEVATION_CONTROL
      
        #ifndef FEATURE_ELEVATION_CONTROL
        if ((yaesu_command_buffer[1] == '2') && (yaesu_command_buffer_index > 1)) {     // did we get the C2 command?
          #ifndef OPTION_GS_232B_EMULATION
          strcat(return_string,"+0000");    // return a dummy elevation since we don't have the elevation feature turned on
          #else
          strcat(return_string,"EL=000");
          #endif
        } else {
          //strcat(return_string,"\n");
        }
        #endif // FEATURE_ELEVATION_CONTROL   
        break;
        
        
        //-----------------end of C command-----------------
        
      #ifdef FEATURE_AZ_POSITION_POTENTIOMETER
      case 'F': // F - full scale calibration
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: F\n");
        }
        #endif // DEBUG_PROCESS_YAESU
      
      
        #ifdef FEATURE_ELEVATION_CONTROL
        if ((yaesu_command_buffer[1] == '2') && (yaesu_command_buffer_index > 1)) {     // did we get the F2 command?

          clear_serial_buffer();
          if (source_port == CONTROL_PORT0){
            control_port->println(F("Elevate to 180 (or max elevation) and send keystroke..."));
          }
          get_keystroke();
          read_elevation(1);
          configuration.analog_el_max_elevation = analog_el;
          write_settings_to_eeprom();
          strcpy(return_string,"Wrote to memory");
          return;
        }
        #endif
      
        clear_serial_buffer();
        if (source_port == CONTROL_PORT0){
          control_port->println(F("Rotate to full CW and send keystroke..."));
          get_keystroke();
        }
        read_azimuth(1);
        configuration.analog_az_full_cw = analog_az;
        write_settings_to_eeprom();
        strcpy(return_string,"Wrote to memory");     
        break;
        #endif // FEATURE_AZ_POSITION_POTENTIOMETER
      case 'H': print_help(source_port); break;                     // H - print help - depricated
      case 'L':  // L - manual left (CCW) rotation
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: L\n");
        }
        #endif // DEBUG_PROCESS_YAESU
        submit_request(AZ, REQUEST_CCW, 0, 21);
        //strcpy(return_string,"\n");
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        break;
        
      #ifdef FEATURE_AZ_POSITION_POTENTIOMETER
      case 'O':  // O - offset calibration
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: O\n");
        }
        #endif // DEBUG_PROCESS_YAESU

        #ifdef FEATURE_ELEVATION_CONTROL
        if ((yaesu_command_buffer[1] == '2') && (yaesu_command_buffer_index > 1)) {     // did we get the O2 command?       
          clear_serial_buffer();
          if (source_port == CONTROL_PORT0){  
            control_port->println(F("Elevate to 0 degrees and send keystroke..."));
          }
          get_keystroke();
          read_elevation(1);
          configuration.analog_el_0_degrees = analog_el;
          write_settings_to_eeprom();
          strcpy(return_string,"Wrote to memory");
          return;
        }
        #endif
      
        clear_serial_buffer();  
        if (source_port == CONTROL_PORT0){    
          control_port->println(F("Rotate to full CCW and send keystroke..."));
        }
        get_keystroke();
        read_azimuth(1);
        configuration.analog_az_full_ccw = analog_az;
        write_settings_to_eeprom();
        strcpy(return_string,"Wrote to memory");
        break;
        #endif // FEATURE_AZ_POSITION_POTENTIOMETER
      
      case 'R':  // R - manual right (CW) rotation
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: R\n");
        }
        #endif // DEBUG_PROCESS_YAESU
        submit_request(AZ, REQUEST_CW, 0, 22);
        strcpy(return_string,"\n");
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        break;
        
      case 'A':  // A - CW/CCW rotation stop
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: A\n");
        }
        #endif // DEBUG_PROCESS_YAESU
        submit_request(AZ, REQUEST_STOP, 0, 23);
        //strcpy(return_string,"\n");
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        break;
        
      case 'S':         // S - all stop
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: S\n");
        }
        #endif // DEBUG_PROCESS_YAESU
        submit_request(AZ, REQUEST_STOP, 0, 24);
        #ifdef FEATURE_ELEVATION_CONTROL
        submit_request(EL, REQUEST_STOP, 0, 25);
        #endif
        #ifdef FEATURE_TIMED_BUFFER
        clear_timed_buffer();
        #endif // FEATURE_TIMED_BUFFER
        //strcpy(return_string,"");
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        break;
        
      case 'M': // M - auto azimuth rotation
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: M\n");
        }
        #endif // DEBUG_PROCESS_YAESU
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
  
        if (yaesu_command_buffer_index > 4) {  // if there are more than 4 characters in the command buffer, we got a timed interval command
          #ifdef FEATURE_TIMED_BUFFER
          clear_timed_buffer();
          parsed_value = ((int(yaesu_command_buffer[1]) - 48) * 100) + ((int(yaesu_command_buffer[2]) - 48) * 10) + (int(yaesu_command_buffer[3]) - 48);
          if ((parsed_value > 0) && (parsed_value < 1000)) {
            timed_buffer_interval_value_seconds = parsed_value;
            for (int x = 5; x < yaesu_command_buffer_index; x = x + 4) {
              parsed_value = ((int(yaesu_command_buffer[x]) - 48) * 100) + ((int(yaesu_command_buffer[x + 1]) - 48) * 10) + (int(yaesu_command_buffer[x + 2]) - 48);
              if ((parsed_value >= 0) && (parsed_value <= 360)) {  // is it a valid azimuth?
                timed_buffer_azimuths[timed_buffer_number_entries_loaded] = parsed_value * HEADING_MULTIPLIER;
                timed_buffer_number_entries_loaded++;
                timed_buffer_status = LOADED_AZIMUTHS;
                if (timed_buffer_number_entries_loaded > TIMED_INTERVAL_ARRAY_SIZE) {   // is the array full?
                  submit_request(AZ, REQUEST_AZIMUTH, timed_buffer_azimuths[0], 26);  // array is full, go to the first azimuth
                  timed_buffer_entry_pointer = 1;
                  return;
                }
              } else {   // we hit an invalid bearing
                timed_buffer_status = EMPTY;
                timed_buffer_number_entries_loaded = 0;
                strcpy(return_string,"?>");  // error
                return;
              }
            }
            submit_request(AZ, REQUEST_AZIMUTH, timed_buffer_azimuths[0], 27);   // go to the first azimuth
            timed_buffer_entry_pointer = 1;       
          } else {
            strcpy(return_string,"?>");  // error
          }
          #else
          strcpy(return_string,"?>");
          #endif // FEATURE_TIMED_BUFFER
          return;
        } else {                         // if there are four characters, this is just a single direction setting
          if (yaesu_command_buffer_index == 4) {
            parsed_value = ((int(yaesu_command_buffer[1]) - 48) * 100) + ((int(yaesu_command_buffer[2]) - 48) * 10) + (int(yaesu_command_buffer[3]) - 48);
            #ifdef FEATURE_TIMED_BUFFER
            clear_timed_buffer();
            #endif // FEATURE_TIMED_BUFFER
            if ((parsed_value >= 0) && (parsed_value <= (azimuth_starting_point + azimuth_rotation_capability))) {
              submit_request(AZ, REQUEST_AZIMUTH, (parsed_value * HEADING_MULTIPLIER), 28);
              return;
            }
          }
        }
        strcpy(return_string,"?>");      
        break;
        
      #ifdef FEATURE_TIMED_BUFFER
      case 'N': // N - number of loaded timed interval entries
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: N\n");
        }
        #endif // DEBUG_PROCESS_YAESU
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        sprintf(return_string,"%d",timed_buffer_number_entries_loaded);
        break;
        #endif // FEATURE_TIMED_BUFFER
        
      #ifdef FEATURE_TIMED_BUFFER
      case 'T': // T - initiate timed tracking
        initiate_timed_buffer(source_port);
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        break;           
        #endif // FEATURE_TIMED_BUFFER
        
      case 'X':  // X - azimuth speed change
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: X\n");
        }
        #endif // DEBUG_PROCESS_YAESU
        
        
        if (yaesu_command_buffer_index > 1) {
          switch (yaesu_command_buffer[1]) {
            case '4':
              normal_az_speed_voltage = PWM_SPEED_VOLTAGE_X4;
              update_az_variable_outputs(PWM_SPEED_VOLTAGE_X4);
              #if defined(FEATURE_ELEVATION_CONTROL) && defined(OPTION_EL_SPEED_FOLLOWS_AZ_SPEED)
              normal_el_speed_voltage = PWM_SPEED_VOLTAGE_X4;
              update_el_variable_outputs(PWM_SPEED_VOLTAGE_X4);
              #endif
              strcpy(return_string,"Speed X4");
              break;
            case '3':
              normal_az_speed_voltage = PWM_SPEED_VOLTAGE_X3;
              update_az_variable_outputs(PWM_SPEED_VOLTAGE_X3);
              #if defined(FEATURE_ELEVATION_CONTROL) && defined(OPTION_EL_SPEED_FOLLOWS_AZ_SPEED)
              normal_el_speed_voltage = PWM_SPEED_VOLTAGE_X3;
              update_el_variable_outputs(PWM_SPEED_VOLTAGE_X3);
              #endif
              strcpy(return_string,"Speed X3");
              break;
            case '2':
              normal_az_speed_voltage = PWM_SPEED_VOLTAGE_X2;
              update_az_variable_outputs(PWM_SPEED_VOLTAGE_X2);
              #if defined(FEATURE_ELEVATION_CONTROL) && defined(OPTION_EL_SPEED_FOLLOWS_AZ_SPEED)
              normal_el_speed_voltage = PWM_SPEED_VOLTAGE_X2;
              update_el_variable_outputs(PWM_SPEED_VOLTAGE_X2);
              #endif
              strcpy(return_string,"Speed X2");
              break;
            case '1':
              normal_az_speed_voltage = PWM_SPEED_VOLTAGE_X1;
              update_az_variable_outputs(PWM_SPEED_VOLTAGE_X1);
              #if defined(FEATURE_ELEVATION_CONTROL) && defined(OPTION_EL_SPEED_FOLLOWS_AZ_SPEED)
              normal_el_speed_voltage = PWM_SPEED_VOLTAGE_X1;
              update_el_variable_outputs(PWM_SPEED_VOLTAGE_X1);
              #endif
              strcpy(return_string,"Speed X1");
              break;
            default: strcpy(return_string,"?>"); break;
          } /* switch */
        } else {
          strcpy(return_string,"?>");
        }
        break;
        
      #ifdef FEATURE_ELEVATION_CONTROL
      case 'U':  // U - manual up rotation
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: U\n");
        }
        #endif // DEBUG_PROCESS_YAESU
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        submit_request(EL, REQUEST_UP, 0, 29);
        //strcpy(return_string,"\n");
        break;
        
      case 'D':  // D - manual down rotation
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: D\n");
        }
        #endif // DEBUG_PROCESS_YAESU
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        submit_request(EL, REQUEST_DOWN, 0, 30);
        //strcpy(return_string,"\n");
        break;
        
      case 'E':  // E - stop elevation rotation
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: E\n");
        }
        #endif // DEBUG_PROCESS_YAESU
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        submit_request(EL, REQUEST_STOP, 0, 31);
        //strcpy(return_string,"\n");
        break;
        
      case 'B': // B - return current elevation
        #ifndef OPTION_GS_232B_EMULATION
        if (elevation < 0) {
          strcat(return_string,"-0");
        } else {
          strcat(return_string,"+0");
        }
        #else
        strcat(return_string,"EL=");
        #endif //OPTION_GS_232B_EMULATION
        dtostrf(int(elevation / HEADING_MULTIPLIER),0,0,tempstring);
        if (int(elevation / HEADING_MULTIPLIER) < 10) {
          strcat(return_string,("0"));
        }
        if (int(elevation / HEADING_MULTIPLIER) < 100) {
          strcat(return_string,"0");
        }
        strcat(return_string,tempstring);
      break;        
      
      #endif /* ifdef FEATURE_ELEVATION_CONTROL */
      
      case 'W':  // W - auto elevation rotation
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("yaesu_serial_command: W\n");
        }
        #endif // DEBUG_PROCESS_YAESU
        #ifdef FEATURE_PARK
        deactivate_park();
        #endif // FEATURE_PARK
        
        
        // parse out W command
        // Short Format: WXXX YYYY           XXX = azimuth YYY = elevation
        // Long Format : WSSS XXX YYY        SSS = timed interval   XXX = azimuth    YYY = elevation

        if (yaesu_command_buffer_index > 8) {  // if there are more than 4 characters in the command buffer, we got a timed interval command
          #if defined(FEATURE_TIMED_BUFFER) && defined(FEATURE_ELEVATION_CONTROL) 
          parsed_value = ((int(yaesu_command_buffer[1]) - 48) * 100) + ((int(yaesu_command_buffer[2]) - 48) * 10) + (int(yaesu_command_buffer[3]) - 48);
          if ((parsed_value > 0) && (parsed_value < 1000)) {
            timed_buffer_interval_value_seconds = parsed_value;
            for (int x = 5; x < yaesu_command_buffer_index; x = x + 8) {
              parsed_value = ((int(yaesu_command_buffer[x]) - 48) * 100) + ((int(yaesu_command_buffer[x + 1]) - 48) * 10) + (int(yaesu_command_buffer[x + 2]) - 48);
              parsed_value2 = ((int(yaesu_command_buffer[x + 4]) - 48) * 100) + ((int(yaesu_command_buffer[x + 5]) - 48) * 10) + (int(yaesu_command_buffer[x + 6]) - 48);
              if ((parsed_value > -1) && (parsed_value < 361) && (parsed_value2 > -1) && (parsed_value2 < 181)) {  // is it a valid azimuth?
                timed_buffer_azimuths[timed_buffer_number_entries_loaded] = (parsed_value * HEADING_MULTIPLIER);
                timed_buffer_elevations[timed_buffer_number_entries_loaded] = (parsed_value2 * HEADING_MULTIPLIER);
                timed_buffer_number_entries_loaded++;
                timed_buffer_status = LOADED_AZIMUTHS_ELEVATIONS;
                if (timed_buffer_number_entries_loaded > TIMED_INTERVAL_ARRAY_SIZE) {   // is the array full?
                  x = yaesu_command_buffer_index;  // array is full, go to the first azimuth and elevation
      
                }
              } else {   // we hit an invalid bearing
                timed_buffer_status = EMPTY;
                timed_buffer_number_entries_loaded = 0;
                strcpy(return_string,"?>");  // error
                return;
              }
            }
          }
          timed_buffer_entry_pointer = 1;             // go to the first bearings
          parsed_value = timed_buffer_azimuths[0];
          parsed_elevation = timed_buffer_elevations[0];
          #else /* ifdef FEATURE_TIMED_BUFFER FEATURE_ELEVATION_CONTROL*/
          strcpy(return_string,"?>");
          #endif // FEATURE_TIMED_BUFFER FEATURE_ELEVATION_CONTROL
        } else {
          // this is a short form W command, just parse the azimuth and elevation and initiate rotation
          parsed_value = (((int(yaesu_command_buffer[1]) - 48) * 100) + ((int(yaesu_command_buffer[2]) - 48) * 10) + (int(yaesu_command_buffer[3]) - 48)) * HEADING_MULTIPLIER;
          parsed_elevation = (((int(yaesu_command_buffer[5]) - 48) * 100) + ((int(yaesu_command_buffer[6]) - 48) * 10) + (int(yaesu_command_buffer[7]) - 48)) * HEADING_MULTIPLIER;
        }
      
         #ifndef FEATURE_ELEVATION_CONTROL
        if ((parsed_value >= 0) && (parsed_value <= (360 * HEADING_MULTIPLIER))) {
          submit_request(AZ, REQUEST_AZIMUTH, parsed_value, 32);
        } else {
          #ifdef DEBUG_PROCESS_YAESU
          if (debug_mode) {
            debug_print("process_yaesu_command: W cmd az error");
          }
          #endif // DEBUG_PROCESS_YAESU
          strcpy(return_string,"?>");      // bogus elevation - return and error and don't do anything
        }
        
        #else
         if ((parsed_value >= 0) && (parsed_value <= (360 * HEADING_MULTIPLIER)) && (parsed_elevation >= 0) && (parsed_elevation <= (180 * HEADING_MULTIPLIER))) {
          submit_request(AZ, REQUEST_AZIMUTH, parsed_value, 33);
          submit_request(EL, REQUEST_ELEVATION, parsed_elevation, 34);
        } else {
          #ifdef DEBUG_PROCESS_YAESU
          if (debug_mode) {
            debug_print("process_yaesu_command: W cmd az/el error");
          }
          #endif // DEBUG_PROCESS_YAESU
          strcpy(return_string,"?>");      // bogus elevation - return and error and don't do anything
        } 
        #endif // FEATURE_ELEVATION_CONTROL
        
        
        break;
        
      #ifdef OPTION_GS_232B_EMULATION
      case 'P':  // P - switch between 360 and 450 degree mode

        if ((yaesu_command_buffer[1] == '3') && (yaesu_command_buffer_index > 2)) {  // P36 command
          azimuth_rotation_capability = 360;
          strcpy(return_string,"Mode 360 degree");
          // write_settings_to_eeprom();
        } else {
          if ((yaesu_command_buffer[1] == '4') && (yaesu_command_buffer_index > 2)) { // P45 command
            azimuth_rotation_capability = 450;
            strcpy(return_string,"Mode 450 degree");
            // write_settings_to_eeprom();
          } else {
            strcpy(return_string,"?>");
          }
        }
   
      
      break;                 
      case 'Z':                                           // Z - Starting point toggle
        if (azimuth_starting_point == 180) {
          azimuth_starting_point = 0;
          strcpy(return_string,"N");
        } else {
          azimuth_starting_point = 180;
          strcpy(return_string,"S");
        }
        strcat(return_string," Center");
        // write_settings_to_eeprom();
        break;
        #endif
        
      default:
        strcpy(return_string,"?>");
        #ifdef DEBUG_PROCESS_YAESU
        if (debug_mode) {
          debug_print("process_yaesu_command: yaesu_command_buffer_index: ");
          debug_print_int(yaesu_command_buffer_index);
          for (int debug_x = 0; debug_x < yaesu_command_buffer_index; debug_x++) {
            debug_print("process_yaesu_command: yaesu_command_buffer[");
            debug_print_int(debug_x);
            debug_print("]: ");
            debug_print_int(yaesu_command_buffer[debug_x]);
            debug_print(" ");
            debug_write_int(yaesu_command_buffer[debug_x]);
            debug_print("\n");;
          }
        }
        #endif // DEBUG_PROCESS_YAESU
    } /* switch */

} /* yaesu_serial_command */
  #endif // FEATURE_YAESU_EMULATION
// --------------------------------------------------------------
#ifdef FEATURE_ETHERNET
void service_ethernet(){


  byte incoming_byte = 0;
  static unsigned long last_incoming_byte_receive_time = 0;
  char return_string[100] = ""; 
  static byte ethernet_port_buffer0[COMMAND_BUFFER_SIZE];
  static int ethernet_port_buffer_index0 = 0;
  static byte first_connect_occurred = 0;
  static long last_received_byte0 = 0;

  #ifdef FEATURE_REMOTE_UNIT_SLAVE
  static byte preamble_received = 0;
  #endif //FEATURE_REMOTE_UNIT_SLAVE

  /*  this is the server side (receiving bytes from a client such as a master unit receiving commands from a computer
      or a slave receiving commands from a master unit

  */

 
  // clear things out if we received a partial message and it's been awhile
  if ((ethernet_port_buffer_index0) && ((millis()-last_received_byte0) > ETHERNET_MESSAGE_TIMEOUT_MS)){
    ethernet_port_buffer_index0 = 0;
    #ifdef FEATURE_REMOTE_UNIT_SLAVE
    preamble_received = 0;
    #endif //FEATURE_REMOTE_UNIT_SLAVE
  }


  if (ethernetserver0.available()){
    ethernetclient0 = ethernetserver0.available();

    last_received_byte0 = millis();

    if (!first_connect_occurred){  // clean out the cruft that's alway spit out on first connect
      while(ethernetclient0.available()){ethernetclient0.read();}
      first_connect_occurred = 1;
      return;
    }    

    if (ethernetclient0.available() > 0){        // the client has sent something
      incoming_byte = ethernetclient0.read();
      last_incoming_byte_receive_time = millis();

      #ifdef DEBUG_ETHERNET
      debug_print("service_ethernet: client:") ;
      debug_print(" char:");
      debug_print_char((char) incoming_byte);
      debug_print("\n");
      #endif //DEBUG_ETHERNET  

      if ((incoming_byte > 96) && (incoming_byte < 123)) {  // uppercase it
        incoming_byte = incoming_byte - 32;
      }          

      char ethernet_preamble[] = ETHERNET_PREAMBLE;

      #ifdef FEATURE_REMOTE_UNIT_SLAVE
      if (preamble_received < 254){         // the master/slave ethernet link has each message prefixed with a preamble
        if (ethernet_preamble[preamble_received] == 0){
          preamble_received = 254;
        } else {
          if (incoming_byte == ethernet_preamble[preamble_received]){
            preamble_received++;
          } else {
            preamble_received = 0;
          }
        }
      }
      // add it to the buffer if it's not a line feed or carriage return and we've received the preamble
      if ((incoming_byte != 10) && (incoming_byte != 13) && (preamble_received == 254)) { 
        ethernet_port_buffer0[ethernet_port_buffer_index0] = incoming_byte;
        ethernet_port_buffer_index0++;
      }
      #else 
      if ((incoming_byte != 10) && (incoming_byte != 13)) { // add it to the buffer if it's not a line feed or carriage return
        ethernet_port_buffer0[ethernet_port_buffer_index0] = incoming_byte;
        ethernet_port_buffer_index0++;
      }
      #endif //FEATURE_REMOTE_UNIT_SLAVE


      if (((incoming_byte == 13) || (ethernet_port_buffer_index0 >= COMMAND_BUFFER_SIZE)) && (ethernet_port_buffer_index0 > 0)){  // do we have a carriage return?
        if ((ethernet_port_buffer0[0] == '\\') or (ethernet_port_buffer0[0] == '/')) {
          process_backslash_command(ethernet_port_buffer0, ethernet_port_buffer_index0, ETHERNET_PORT0, return_string);
        } else {
          #ifdef FEATURE_YAESU_EMULATION
          process_yaesu_command(ethernet_port_buffer0,ethernet_port_buffer_index0,ETHERNET_PORT0,return_string);
          #endif //FEATURE_YAESU_EMULATION
          #ifdef FEATURE_EASYCOM_EMULATION
          process_easycom_command(ethernet_port_buffer0,ethernet_port_buffer_index0,ETHERNET_PORT0,return_string);
          #endif //FEATURE_EASYCOM_EMULATION
          #ifdef FEATURE_REMOTE_UNIT_SLAVE
          process_remote_slave_command(ethernet_port_buffer0,ethernet_port_buffer_index0,ETHERNET_PORT0,return_string);
          #endif //FEATURE_REMOTE_UNIT_SLAVE          
        }  
        ethernetclient0.println(return_string);
        ethernet_port_buffer_index0 = 0;
        #ifdef FEATURE_REMOTE_UNIT_SLAVE
        preamble_received = 0;
        #endif //FEATURE_REMOTE_UNIT_SLAVE
      }

    }
  }


  #ifdef ETHERNET_TCP_PORT_1
  static byte ethernet_port_buffer1[COMMAND_BUFFER_SIZE];
  static int ethernet_port_buffer_index1 = 0;

  if (ethernetserver1.available()){

    ethernetclient1 = ethernetserver1.available();

    if (ethernetclient1.available() > 0){        // the client has sent something
      incoming_byte = ethernetclient1.read();
      last_incoming_byte_receive_time = millis();

      #ifdef DEBUG_ETHERNET
      debug_print("service_ethernet: client:") ;
      debug_print(" char:");
      debug_print_char((char) incoming_byte);
      debug_print("\n");
      #endif //DEBUG_ETHERNET  

      if ((incoming_byte > 96) && (incoming_byte < 123)) {  // uppercase it
        incoming_byte = incoming_byte - 32;
      }                                                                                                                    
      if ((incoming_byte != 10) && (incoming_byte != 13)) { // add it to the buffer if it's not a line feed or carriage return
        ethernet_port_buffer1[ethernet_port_buffer_index1] = incoming_byte;
        ethernet_port_buffer_index1++;
      }
      if (incoming_byte == 13) {  // do we have a carriage return?
        if ((ethernet_port_buffer1[0] == '\\') or (ethernet_port_buffer1[0] == '/')) {
          process_backslash_command(ethernet_port_buffer1, ethernet_port_buffer_index1, ETHERNET_PORT1, return_string);
        } else {
          #ifdef FEATURE_YAESU_EMULATION
          process_yaesu_command(ethernet_port_buffer1,ethernet_port_buffer_index1,ETHERNET_PORT1,return_string);
          #endif //FEATURE_YAESU_EMULATION
          #ifdef FEATURE_EASYCOM_EMULATION
          process_easycom_command(ethernet_port_buffer1,ethernet_port_buffer_index1,ETHERNET_PORT1,return_string);
          #endif //FEATURE_EASYCOM_EMULATION
          #ifdef FEATURE_REMOTE_UNIT_SLAVE
          process_remote_slave_command(ethernet_port_buffer1,ethernet_port_buffer_index1,ETHERNET_PORT1,return_string);
          #endif //FEATURE_REMOTE_UNIT_SLAVE
        }  
        ethernetclient1.println(return_string);
        ethernet_port_buffer_index1 = 0;
      }

    }
  }
  #endif //ETHERNET_TCP_PORT_1

  #ifdef FEATURE_MASTER_WITH_ETHERNET_SLAVE
  static long last_connect_try = 0;
  static long last_received_byte_time = 0;
  byte incoming_ethernet_byte = 0;
  static byte first_ethernet_slave_connect_occurred = 0;

  // are we disconnected and is it time to reconnect?
  if ((ethernetslavelinkclient0_state == ETHERNET_SLAVE_DISCONNECTED)  && (((millis()-last_connect_try) >= ETHERNET_SLAVE_RECONNECT_TIME_MS) || (last_connect_try == 0))){

    #ifdef DEBUG_ETHERNET
    debug_println("service_ethernet: master_slave_ethernet: connecting");
    #endif //DEBUG_ETHERNET

    if (ethernetslavelinkclient0.connect(slave_unit_ip, ETHERNET_SLAVE_TCP_PORT)){
      ethernetslavelinkclient0_state = ETHERNET_SLAVE_CONNECTED;
      if (!first_ethernet_slave_connect_occurred){
        first_ethernet_slave_connect_occurred = 1;
        ethernet_slave_reconnects = 65535;
      }
    } else {
      ethernetslavelinkclient0.stop();
      #ifdef DEBUG_ETHERNET
      debug_println("service_ethernet: master_slave_ethernet: connect failed");
      #endif //DEBUG_ETHERNET
    }

    ethernet_slave_reconnects++;
    last_connect_try = millis();
  }


  if (ethernetslavelinkclient0.available()) {
    incoming_ethernet_byte = ethernetslavelinkclient0.read();

    #ifdef DEBUG_ETHERNET
    debug_print("service_ethernet: slave rx: ");
    debug_print_char(incoming_ethernet_byte);
    debug_print(" : ");
    debug_print_int(incoming_ethernet_byte);
    debug_println("");
    #endif //DEBUG_ETHERNET      

    if (remote_port_rx_sniff) {
      control_port->write(incoming_ethernet_byte);
    }

    if ((incoming_ethernet_byte != 10) && (remote_unit_port_buffer_index < COMMAND_BUFFER_SIZE)) {
      remote_unit_port_buffer[remote_unit_port_buffer_index] = incoming_ethernet_byte;
      remote_unit_port_buffer_index++;
      if ((incoming_ethernet_byte == 13) || (remote_unit_port_buffer_index >= COMMAND_BUFFER_SIZE)) {
        remote_unit_port_buffer_carriage_return_flag = 1;
        #ifdef DEBUG_ETHERNET
        debug_println("service_ethernet: remote_unit_port_buffer_carriage_return_flag");
        #endif //DEBUG_ETHERNET          
      }
    }
    last_received_byte_time = millis();

  }

  if (((millis() - last_received_byte_time) >= ETHERNET_MESSAGE_TIMEOUT_MS) && (remote_unit_port_buffer_index > 1) && (!remote_unit_port_buffer_carriage_return_flag)){
    remote_unit_port_buffer_index = 0;
    #ifdef DEBUG_ETHERNET
    debug_println("service_ethernet: master_slave_ethernet: remote_unit_incoming_buffer_timeout");
    #endif //DEBUG_ETHERNET    
    remote_unit_incoming_buffer_timeouts++;
  }

  if ((ethernetslavelinkclient0_state == ETHERNET_SLAVE_CONNECTED) && (!ethernetslavelinkclient0.connected())){
    ethernetslavelinkclient0.stop();
    ethernetslavelinkclient0_state = ETHERNET_SLAVE_DISCONNECTED;
    remote_unit_port_buffer_index = 0;
    #ifdef DEBUG_ETHERNET
    debug_println("service_ethernet: master_slave_ethernet: lost connection");
    #endif //DEBUG_ETHERNET    
  }


  #endif //FEATURE_MASTER_WITH_ETHERNET_SLAVE

}
#endif //FEATURE_ETHERNET
// --------------------------------------------------------------
#ifdef FEATURE_EASYCOM_EMULATION
void process_easycom_command(byte * easycom_command_buffer, int easycom_command_buffer_index, byte source_port, char * return_string){


  /* Easycom protocol implementation
   *
   * Implemented commands:
   *
   * Command      Meaning     Parameters
   * -------      -------     ----------
   *
   * ML           Move Left
   * MR           Move Right
   * MU           Move Up
   * MD           Move Down
   * SA           Stop azimuth moving
   * SE           Stop elevation moving
   *
   * VE           Request Version
   * AZ           Azimuth     number - 1 decimal place (activated with OPTION_EASYCOM_AZ_QUERY_COMMAND)
   * EL           Elevation   number - 1 decimal place (activated with OPTION_EASYCOM_EL_QUERY_COMMAND)
   *
   *
   */



  char tempstring[11] = "";
  float heading = -1;
  strcpy(return_string,"");

  switch (easycom_command_buffer[0]) { // look at the first character of the command
    case 'A':  // AZ
      if (easycom_command_buffer[1] == 'Z') {  // format is AZx.x or AZxx.x or AZxxx.x (why didn't they make it fixed length?)
        switch (easycom_command_buffer_index) {
          #ifdef OPTION_EASYCOM_AZ_QUERY_COMMAND
          case 2:
            strcpy(return_string,"AZ");
            dtostrf((float)azimuth/(float)HEADING_MULTIPLIER,0,1,tempstring);
            strcat(return_string,tempstring);
            return;
            break;
          #endif // OPTION_EASYCOM_AZ_QUERY_COMMAND
          case 5: // format AZx.x
            heading = (easycom_command_buffer[2] - 48) + ((easycom_command_buffer[4] - 48) / 10.);
            break;
          case 6: // format AZxx.x
            heading = ((easycom_command_buffer[2] - 48) * 10.) + (easycom_command_buffer[3] - 48) + ((easycom_command_buffer[5] - 48) / 10.);
            break;
          case 7: // format AZxxx.x
            heading = ((easycom_command_buffer[2] - 48) * 100.) + ((easycom_command_buffer[3] - 48) * 10.) + (easycom_command_buffer[4] - 48.) + ((easycom_command_buffer[6] - 48) / 10.);
            break;
            // default: control_port->println("?"); break;
        }
        if (((heading >= 0) && (heading < 451))  && (easycom_command_buffer[easycom_command_buffer_index - 2] == '.')) {
          submit_request(AZ, REQUEST_AZIMUTH, (heading * HEADING_MULTIPLIER), 36);
        } else {
          strcpy(return_string,"?");
        }
      } else {
        strcpy(return_string,"?");
      }
      break;
      #ifdef FEATURE_ELEVATION_CONTROL
    case 'E':  // EL
      if (easycom_command_buffer[1] == 'L') {
        switch (easycom_command_buffer_index) {
          #ifdef OPTION_EASYCOM_EL_QUERY_COMMAND
          case 2:
            strcpy(return_string,"EL");
            dtostrf((float)elevation/(float)HEADING_MULTIPLIER,0,1,tempstring);
            strcat(return_string,tempstring);            
            return;
            break;
          #endif // OPTION_EASYCOM_EL_QUERY_COMMAND
          case 5: // format ELx.x
            heading = (easycom_command_buffer[2] - 48) + ((easycom_command_buffer[4] - 48) / 10.);
            break;
          case 6: // format ELxx.x
            heading = ((easycom_command_buffer[2] - 48) * 10.) + (easycom_command_buffer[3] - 48) + ((easycom_command_buffer[5] - 48) / 10.);
            break;
          case 7: // format ELxxx.x
            heading = ((easycom_command_buffer[2] - 48) * 100.) + ((easycom_command_buffer[3] - 48) * 10.) + (easycom_command_buffer[4] - 48) + ((easycom_command_buffer[6] - 48) / 10.);
            break;
            // default: control_port->println("?"); break;
        }
        if (((heading >= 0) && (heading < 181)) && (easycom_command_buffer[easycom_command_buffer_index - 2] == '.')) {
          submit_request(EL, REQUEST_ELEVATION, (heading * HEADING_MULTIPLIER), 37);
        } else {
          strcpy(return_string,"?");
        }
      } else {
        strcpy(return_string,"?");
      }
      break;
      #endif // #FEATURE_ELEVATION_CONTROL
    case 'S':  // SA or SE - stop azimuth, stop elevation
      switch (easycom_command_buffer[1]) {
        case 'A':
          submit_request(AZ, REQUEST_STOP, 0, 38);
          break;
        #ifdef FEATURE_ELEVATION_CONTROL
        case 'E':
          submit_request(EL, REQUEST_STOP, 0, 39);
          break;
        #endif // FEATURE_ELEVATION_CONTROL
        default: strcpy(return_string,"?"); break;
      }
      break;
    case 'M':  // ML, MR, MU, MD - move left, right, up, down
      switch (easycom_command_buffer[1]) {
        case 'L': // ML - move left
          submit_request(AZ, REQUEST_CCW, 0, 40);
          break;
        case 'R': // MR - move right
          submit_request(AZ, REQUEST_CW, 0, 41);
          break;
        #ifdef FEATURE_ELEVATION_CONTROL
        case 'U': // MU - move up
          submit_request(EL, REQUEST_UP, 0, 42);
          break;
        case 'D': // MD - move down
          submit_request(EL, REQUEST_DOWN, 0, 43);
          break;
        #endif // FEATURE_ELEVATION_CONTROL
        default: strcpy(return_string,"?"); break;
      }
      break;
    case 'V': // VE - version query
      if (easycom_command_buffer[1] == 'E') {
        strcpy(return_string,"VE002");
      }                                                                       // not sure what to send back, sending 002 because this is easycom version 2?
      break;
    default: strcpy(return_string,"?"); break;
  } /* switch */



} /* easycom_serial_commmand */
#endif // FEATURE_EASYCOM_EMULATION





// --------------------------------------------------------------

#ifdef FEATURE_REMOTE_UNIT_SLAVE
void process_remote_slave_command(byte * slave_command_buffer, int slave_command_buffer_index, byte source_port, char * return_string){


/*
 *
 * This implements a protocol for host unit to remote unit communications
 *
 *
 * Remote Slave Unit Protocol Reference
 *
 *  PG - ping
 *  AZ - read azimuth  (returns AZxxx.xxxxxx)
 *  EL - read elevation (returns ELxxx.xxxxxx)
 *  DOxx - digital pin initialize as output;
 *  DIxx - digital pin initialize as input
 *  DPxx - digital pin initialize as input with pullup
 *  DRxx - digital pin read
 *  DLxx - digital pin write low
 *  DHxx - digital pin write high
 *  DTxxyyyy - digital pin tone output
 *  NTxx - no tone
 *  ARxx - analog pin read
 *  AWxxyyy - analog pin write
 *  SWxy - serial write byte
 *  SDx - deactivate serial read event; x = port #
 *  SSxyyyyyy... - serial write string; x = port #, yyyy = string of characters to send
 *  SAx - activate serial read event; x = port #
 *  RB - reboot
 *  CL - return clock date and time
 *
 * Responses
 *
 *  ER - report an error (remote to host only)
 *  EV - report an event (remote to host only)
 *  OK - report success (remote to host only)
 *  CS - report a cold start (remote to host only)
 *
 * Error Codes
 *
 *  ER01 - Serial port buffer timeout
 *  ER02 - Command syntax error
 *
 * Events
 *
 *  EVSxy - Serial port read event; x = serial port number, y = byte returned
 *
 *
 */



  byte command_good = 0;
  strcpy(return_string,"");
  char tempstring[25] = "";

  if (slave_command_buffer_index < 2) {
    strcpy(return_string,"ER02");  // we don't have enough characters - syntax error
  } else {

    #ifdef DEBUG_PROCESS_SLAVE
    debug_print("serial_serial_buffer: command_string: ");
    debug_print((char*)slave_command_buffer);
    debug_print("$ slave_command_buffer_index: ");
    debug_print_int(slave_command_buffer_index);
    debug_print("\n");
    #endif // DEBUG_PROCESS_SLAVE

    if (((slave_command_buffer[0] == 'S') && (slave_command_buffer[1] == 'S')) && (slave_command_buffer[2] > 47) && (slave_command_buffer[2] < 53)) { // this is a variable length command
      command_good = 1;
      for (byte x = 3; x < slave_command_buffer_index; x++) {
        switch (slave_command_buffer[2] - 48) {
          case 0: control_port->write(slave_command_buffer[x]); break;
          #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE)
          case 1: remote_unit_port->write(slave_command_buffer[x]); break;
          #endif
        }
      }
    }

    if (slave_command_buffer_index == 2) {

      #ifdef FEATURE_CLOCK
      if ((slave_command_buffer[0] == 'C') && (slave_command_buffer[1] == 'L')) {
        strcpy(return_string,"CL");
        update_time();
        strcat(return_string,clock_string());
        command_good = 1;
      }
      #endif //FEATURE_CLOCK

      if ((slave_command_buffer[0] == 'P') && (slave_command_buffer[1] == 'G')) {
        strcpy(return_string,"PG"); command_good = 1;
      }                                                                        // PG - ping
      if ((slave_command_buffer[0] == 'R') && (slave_command_buffer[1] == 'B')) {
        wdt_enable(WDTO_30MS); while (1) {
        }
      }                                                                        // RB - reboot
      if ((slave_command_buffer[0] == 'A') && (slave_command_buffer[1] == 'Z')) {
        strcpy(return_string,"AZ");
        //if ((raw_azimuth/HEADING_MULTIPLIER) < 1000) {
        //  strcat(return_string,"0");
        //}
        if ((raw_azimuth/HEADING_MULTIPLIER) < 100) {
          strcat(return_string,"0");
        }
        if ((raw_azimuth/HEADING_MULTIPLIER) < 10) {
          strcat(return_string,"0");
        }
        dtostrf(float(raw_azimuth/HEADING_MULTIPLIER),0,6,tempstring);
        strcat(return_string,tempstring);          
        command_good = 1;
      }
      #ifdef FEATURE_ELEVATION_CONTROL
      if ((slave_command_buffer[0] == 'E') && (slave_command_buffer[1] == 'L')) {
        strcpy(return_string,"EL");
        if ((elevation/HEADING_MULTIPLIER) >= 0) {
          strcat(return_string,"+");
        } else {
          strcat(return_string,"-");
        }
        //if (abs(elevation/HEADING_MULTIPLIER) < 1000) {
        //  strcat(return_string,"0");
        //}
        if (abs(elevation/HEADING_MULTIPLIER) < 100) {
          strcat(return_string,"0");
        }
        if (abs(elevation/HEADING_MULTIPLIER) < 10) {
          strcat(return_string,"0");
        }
        dtostrf(float(abs(elevation/HEADING_MULTIPLIER)),0,6,tempstring);
        strcat(return_string,tempstring);            
        command_good = 1;
      }
        #endif // FEATURE_ELEVATION_CONTROL
    } // end of two byte commands



    if (slave_command_buffer_index == 3) {
      if (((slave_command_buffer[0] == 'S') && (slave_command_buffer[1] == 'A')) & (slave_command_buffer[2] > 47) && (slave_command_buffer[2] < 53)) {
        serial_read_event_flag[slave_command_buffer[2] - 48] = 1;
        command_good = 1;
        strcpy(return_string,"OK");
      }
      if (((slave_command_buffer[0] == 'S') && (slave_command_buffer[1] == 'D')) & (slave_command_buffer[2] > 47) && (slave_command_buffer[2] < 53)) {
        serial_read_event_flag[slave_command_buffer[2] - 48] = 0;
        command_good = 1;
        strcpy(return_string,"OK");
      }

    }


    if (slave_command_buffer_index == 4) {
      if ((slave_command_buffer[0] == 'S') && (slave_command_buffer[1] == 'W')) { // Serial Write command
        switch (slave_command_buffer[2]) {
          case '0': control_port->write(slave_command_buffer[3]); command_good = 1; break;
          #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE)
          case '1': remote_unit_port->write(slave_command_buffer[3]); command_good = 1; break;
          #endif
        }
      }

      if ((slave_command_buffer[0] == 'D') && (slave_command_buffer[1] == 'O')) {
        if ((((slave_command_buffer[2] > 47) && (slave_command_buffer[2] < 58)) || (toupper(slave_command_buffer[2]) == 'A')) && (slave_command_buffer[3] > 47) && (slave_command_buffer[3] < 58)) {
          command_good = 1;
          byte pin_value = 0;
          if (toupper(slave_command_buffer[2]) == 'A') {
            pin_value = get_analog_pin(slave_command_buffer[3] - 48);
          } else {
            pin_value = ((slave_command_buffer[2] - 48) * 10) + (slave_command_buffer[3] - 48);
          }
          #ifdef DEBUG_PROCESS_SLAVE
          debug_print("service_serial_buffer: pin_value: ");
          debug_print_int(pin_value);
          #endif // DEBUG_PROCESS_SLAVE
          strcpy(return_string,"OK");
          pinModeEnhanced(pin_value, OUTPUT);
        }
      }

      if ((slave_command_buffer[0] == 'D') && (slave_command_buffer[1] == 'H')) {
        if ((((slave_command_buffer[2] > 47) && (slave_command_buffer[2] < 58)) || (toupper(slave_command_buffer[2]) == 'A')) && (slave_command_buffer[3] > 47) && (slave_command_buffer[3] < 58)) {
          command_good = 1;
          byte pin_value = 0;
          if (toupper(slave_command_buffer[2]) == 'A') {
            pin_value = get_analog_pin(slave_command_buffer[3] - 48);
          } else {
            pin_value = ((slave_command_buffer[2] - 48) * 10) + (slave_command_buffer[3] - 48);
          }
          digitalWriteEnhanced(pin_value, HIGH);
          strcpy(return_string,"OK");
        }
      }

      if ((slave_command_buffer[0] == 'D') && (slave_command_buffer[1] == 'L')) {
        if ((((slave_command_buffer[2] > 47) && (slave_command_buffer[2] < 58)) || (toupper(slave_command_buffer[2]) == 'A')) && (slave_command_buffer[3] > 47) && (slave_command_buffer[3] < 58)) {
          command_good = 1;
          byte pin_value = 0;
          if (toupper(slave_command_buffer[2]) == 'A') {
            pin_value = get_analog_pin(slave_command_buffer[3] - 48);
          } else {
            pin_value = ((slave_command_buffer[2] - 48) * 10) + (slave_command_buffer[3] - 48);
          }
          digitalWriteEnhanced(pin_value, LOW);
          strcpy(return_string,"OK");
        }
      }

      if ((slave_command_buffer[0] == 'D') && (slave_command_buffer[1] == 'I')) {
        if ((((slave_command_buffer[2] > 47) && (slave_command_buffer[2] < 58)) || (toupper(slave_command_buffer[2]) == 'A')) && (slave_command_buffer[3] > 47) && (slave_command_buffer[3] < 58)) {
          command_good = 1;
          byte pin_value = 0;
          if (toupper(slave_command_buffer[2]) == 'A') {
            pin_value = get_analog_pin(slave_command_buffer[3] - 48);
          } else {
            pin_value = ((slave_command_buffer[2] - 48) * 10) + (slave_command_buffer[3] - 48);
          }
          pinModeEnhanced(pin_value, INPUT);
          strcpy(return_string,"OK");
        }
      }

      if ((slave_command_buffer[0] == 'D') && (slave_command_buffer[1] == 'P')) {
        if ((((slave_command_buffer[2] > 47) && (slave_command_buffer[2] < 58)) || (toupper(slave_command_buffer[2]) == 'A')) && (slave_command_buffer[3] > 47) && (slave_command_buffer[3] < 58)) {
          command_good = 1;
          byte pin_value = 0;
          if (toupper(slave_command_buffer[2]) == 'A') {
            pin_value = get_analog_pin(slave_command_buffer[3] - 48);
          } else {
            pin_value = ((slave_command_buffer[2] - 48) * 10) + (slave_command_buffer[3] - 48);
          }
          pinModeEnhanced(pin_value, INPUT);
          digitalWriteEnhanced(pin_value, HIGH);
          strcpy(return_string,"OK");
        }
      }

      if ((slave_command_buffer[0] == 'D') && (slave_command_buffer[1] == 'R')) {
        if ((((slave_command_buffer[2] > 47) && (slave_command_buffer[2] < 58)) || (toupper(slave_command_buffer[2]) == 'A')) && (slave_command_buffer[3] > 47) && (slave_command_buffer[3] < 58)) {
          command_good = 1;
          byte pin_value = 0;
          if (toupper(slave_command_buffer[2]) == 'A') {
            pin_value = get_analog_pin(slave_command_buffer[3] - 48);
          } else {
            pin_value = ((slave_command_buffer[2] - 48) * 10) + (slave_command_buffer[3] - 48);
          }
          byte pin_read = digitalReadEnhanced(pin_value);
          strcpy(return_string,"DR");
          dtostrf((slave_command_buffer[2]-48),0,0,tempstring);
          strcat(return_string,tempstring);              
          dtostrf((slave_command_buffer[3]-48),0,0,tempstring);
          strcat(return_string,tempstring);  
          if (pin_read) {
            strcat(return_string,"1");
          } else {
            strcat(return_string,"0");
          }
        }
      }
      if ((slave_command_buffer[0] == 'A') && (slave_command_buffer[1] == 'R')) {
        if ((((slave_command_buffer[2] > 47) && (slave_command_buffer[2] < 58)) || (toupper(slave_command_buffer[2]) == 'A')) && (slave_command_buffer[3] > 47) && (slave_command_buffer[3] < 58)) {
          command_good = 1;
          byte pin_value = 0;
          if (toupper(slave_command_buffer[2]) == 'A') {
            pin_value = get_analog_pin(slave_command_buffer[3] - 48);
          } else {
            pin_value = ((slave_command_buffer[2] - 48) * 10) + (slave_command_buffer[3] - 48);
          }
          int pin_read = analogReadEnhanced(pin_value);
          strcpy(return_string,"AR");
          if (toupper(slave_command_buffer[2]) == 'A') {
            strcat(return_string,"A");
          } else {
            dtostrf((slave_command_buffer[2]-48),0,0,tempstring);
            strcat(return_string,tempstring);
          }
                        
          dtostrf((slave_command_buffer[3]-48),0,0,tempstring);
          strcat(return_string,tempstring);  
          if (pin_read < 1000) {
            strcat(return_string,"0");
          }
          if (pin_read < 100) {
            strcat(return_string,"0");
          }
          if (pin_read < 10) {
            strcat(return_string,"0");
          }
          dtostrf(pin_read,0,0,tempstring);
          strcat(return_string,tempstring);             
        }
      }

      if ((slave_command_buffer[0] == 'N') && (slave_command_buffer[1] == 'T')) {
        if ((((slave_command_buffer[2] > 47) && (slave_command_buffer[2] < 58)) || (toupper(slave_command_buffer[2]) == 'A')) && (slave_command_buffer[3] > 47) && (slave_command_buffer[3] < 58)) {
          command_good = 1;
          byte pin_value = 0;
          if (toupper(slave_command_buffer[2]) == 'A') {
            pin_value = get_analog_pin(slave_command_buffer[3] - 48);
          } else {
            pin_value = ((slave_command_buffer[2] - 48) * 10) + (slave_command_buffer[3] - 48);
          }
          noTone(pin_value);
          strcpy(return_string,"OK");
        }
      }

    } // if (slave_command_buffer_index == 4)

    if (slave_command_buffer_index == 7) {
      if ((slave_command_buffer[0] == 'A') && (slave_command_buffer[1] == 'W')) {
        if ((((slave_command_buffer[2] > 47) && (slave_command_buffer[2] < 58)) || (toupper(slave_command_buffer[2]) == 'A')) && (slave_command_buffer[3] > 47) && (slave_command_buffer[3] < 58)) {
          byte pin_value = 0;
          if (toupper(slave_command_buffer[2]) == 'A') {
            pin_value = get_analog_pin(slave_command_buffer[3] - 48);
          } else {
            pin_value = ((slave_command_buffer[2] - 48) * 10) + (slave_command_buffer[3] - 48);
          }
          int write_value = ((slave_command_buffer[4] - 48) * 100) + ((slave_command_buffer[5] - 48) * 10) + (slave_command_buffer[6] - 48);
          if ((write_value >= 0) && (write_value < 256)) {
            analogWriteEnhanced(pin_value, write_value);
            strcpy(return_string,"OK");
            command_good = 1;
          }
        }
      }
    }

    if (slave_command_buffer_index == 8) {
      if ((slave_command_buffer[0] == 'D') && (slave_command_buffer[1] == 'T')) {
        if ((((slave_command_buffer[2] > 47) && (slave_command_buffer[2] < 58)) || (toupper(slave_command_buffer[2]) == 'A')) && (slave_command_buffer[3] > 47) && (slave_command_buffer[3] < 58)) {
          byte pin_value = 0;
          if (toupper(slave_command_buffer[2]) == 'A') {
            pin_value = get_analog_pin(slave_command_buffer[3] - 48);
          } else {
            pin_value = ((slave_command_buffer[2] - 48) * 10) + (slave_command_buffer[3] - 48);
          }
          int write_value = ((slave_command_buffer[4] - 48) * 1000) + ((slave_command_buffer[5] - 48) * 100) + ((slave_command_buffer[6] - 48) * 10) + (slave_command_buffer[7] - 48);
          if ((write_value >= 0) && (write_value <= 9999)) {
            tone(pin_value, write_value);
            strcpy(return_string,"OK");
            command_good = 1;
          }
        }
      }
    }


    if (!command_good) {
      strcpy(return_string,"ER0289");
    }
  }

  slave_command_buffer_index = 0;

}
#endif //FEATURE_REMOTE_UNIT_SLAVE

// --------------------------------------------------------------
void port_flush(){

  #ifdef CONTROL_PORT_MAPPED_TO
  control_port->flush();
  #endif //CONTROL_PORT_MAPPED_TO

  #if defined(FEATURE_MASTER_WITH_SERIAL_SLAVE)
  remote_unit_port->flush();
  #endif

  #if defined(GPS_PORT_MAPPED_TO) && defined(FEATURE_GPS)
  gps_port->flush();
  #endif //defined(GPS_PORT_MAPPED_TO) && defined(FEATURE_GPS)
  

}
// --------------------------------------------------------------
#ifdef FEATURE_POWER_SWITCH
void service_power_switch(){

  static byte power_switch_state = 1;

  #ifdef FEATURE_ELEVATION_CONTROL
  if ((az_state != IDLE) || (el_state != IDLE)){
    last_activity_time = millis();
  }
  #else //FEATURE_ELEVATION_CONTROL
  if (az_state != IDLE){
    last_activity_time = millis();
  }
  #endif //FEATURE_ELEVATION_CONTROL


  if ((millis()-last_activity_time) > (60000 * POWER_SWITCH_IDLE_TIMEOUT)) {
    if (power_switch_state){ 
      digitalWriteEnhanced(power_switch, LOW);
      power_switch_state = 0;
    }
  } else {
    if (!power_switch_state){ 
      digitalWriteEnhanced(power_switch, HIGH);
      power_switch_state = 1;
    }
  }


}
#endif //FEATURE_POWER_SWITCH


//------------------------------------------------------
char * coordinates_to_maidenhead(float latitude_degrees,float longitude_degrees){

  char temp_string[8] = "";

  const char* asciiuppercase[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R"};
  const char* asciinumbers[] = {"0","1","2","3","4","5","6","7","8","9"};
  const char* asciilowercase[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x"};

  latitude_degrees += 90.0;
  longitude_degrees += 180.0;

  strcat(temp_string,asciiuppercase[int(longitude_degrees/20)]);
  strcat(temp_string,asciiuppercase[int(latitude_degrees/10)]);  
  strcat(temp_string,asciinumbers[int((longitude_degrees - int(longitude_degrees/20)*20)/2)]);
  strcat(temp_string,asciinumbers[int(latitude_degrees - int(latitude_degrees/10)*10)]);
  strcat(temp_string,asciilowercase[int((longitude_degrees - (int(longitude_degrees/2)*2)) / (5.0/60.0))]);
  strcat(temp_string,asciilowercase[int((latitude_degrees - (int(latitude_degrees/1)*1)) / (2.5/60.0))]);

  return temp_string;

}
//------------------------------------------------------
#ifdef FEATURE_MASTER_WITH_ETHERNET_SLAVE
byte ethernet_slave_link_send(char * string_to_send){

  if (ethernetslavelinkclient0_state == ETHERNET_SLAVE_CONNECTED){
    ethernetslavelinkclient0.print(ETHERNET_PREAMBLE);
    ethernetslavelinkclient0.println(string_to_send);
    #ifdef DEBUG_ETHERNET
    debug_print("ethernet_slave_link_send: ");
    debug_println(string_to_send);
    #endif //DEBUG_ETHERNET
    return 1;
  } else {
    #ifdef DEBUG_ETHERNET
    debug_print("ethernet_slave_link_send: link down not sending:");
    debug_println(string_to_send);
    #endif //DEBUG_ETHERNET    
    return 0;
  }

}
#endif //FEATURE_MASTER_WITH_ETHERNET_SLAVE

//------------------------------------------------------


#if defined(FEATURE_CLOCK) && defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE) && (defined(FEATURE_MASTER_WITH_SERIAL_SLAVE) || defined(FEATURE_MASTER_WITH_ETHERNET_SLAVE))
void sync_master_clock_to_slave(){

  static unsigned long last_sync_master_clock_to_slave = 5000;

  if ((millis() - last_sync_master_clock_to_slave) >= (SYNC_MASTER_CLOCK_TO_SLAVE_CLOCK_SECS * 1000)){
    if (submit_remote_command(REMOTE_UNIT_CL_COMMAND, 0, 0)) {
      #ifdef DEBUG_SYNC_MASTER_CLOCK_TO_SLAVE
      debug_println("sync_master_clock_to_slave: submitted REMOTE_UNIT_CL_COMMAND");
      #endif //DEBUG_SYNC_MASTER_CLOCK_TO_SLAVE
      last_sync_master_clock_to_slave = millis();  
    }  
  }

}
#endif //defined(FEATURE_CLOCK) && defined(OPTION_SYNC_MASTER_CLOCK_TO_SLAVE)

//------------------------------------------------------
#ifdef FEATURE_STEPPER_MOTOR_EXPERIMENTAL_CODE
void set_az_stepper_freq(int frequency){

  az_stepper_pulse_period_us = 1000000 / frequency;

}

#endif //FEATURE_STEPPER_MOTOR_EXPERIMENTAL_CODE
//------------------------------------------------------
#if defined(FEATURE_ELEVATION_CONTROL) && defined(FEATURE_STEPPER_MOTOR_EXPERIMENTAL_CODE)
void set_el_stepper_freq(int frequency){

  el_stepper_pulse_period_us = 1000000 / frequency;

}

#endif //defined(FEATURE_ELEVATION_CONTROL) && defined(FEATURE_STEPPER_MOTOR_EXPERIMENTAL_CODE)
//------------------------------------------------------
#ifdef FEATURE_STEPPER_MOTOR_EXPERIMENTAL_CODE
void service_stepper_pins(){


//az_stepper_pulses_remaining

//el_stepper_pulses_remaining

}
#endif //FEATURE_STEPPER_MOTOR_EXPERIMENTAL_CODE
//-------------------------------------------------------
#ifdef FEATURE_ANALOG_OUTPUT_PINS
void service_analog_output_pins(){

  static int last_azimith_voltage_out = 0;
  int azimuth_voltage_out = map(azimuth/HEADING_MULTIPLIER,0,360,0,255);
  if (last_azimith_voltage_out != azimuth_voltage_out){
    analogWriteEnhanced(pin_analog_az_out,azimuth_voltage_out);
    last_azimith_voltage_out = azimuth_voltage_out;
  }

  #ifdef FEATURE_ELEVATION_CONTROL
  static int last_elevation_voltage_out = 0;
  int elevation_voltage_out = map(elevation/HEADING_MULTIPLIER,0,ANALOG_OUTPUT_MAX_EL_DEGREES,0,255);
  if (last_elevation_voltage_out != elevation_voltage_out){
    analogWriteEnhanced(pin_analog_el_out,elevation_voltage_out);
    last_elevation_voltage_out = elevation_voltage_out;
  }
  #endif //FEATURE_ELEVATION_CONTROL

}
#endif //FEATURE_ANALOG_OUTPUT_PINS

