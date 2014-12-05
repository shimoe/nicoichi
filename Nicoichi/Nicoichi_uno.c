//master sample
// Written by Nick Gammon
// February 2011


#include <SPI.h>

void setup (void)
{
  Serial.begin(9600);
  digitalWrite(SS, HIGH);  // ensure SS stays high for now
  digitalWrite(9, HIGH);  // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
}  // end of setup


void loop (void)
{

  char c;
  char r;

  // enable Slave Select
  digitalWrite(SS, LOW);    // SS is pin 10

  // send test string
  for (const char * p = "ABC\n" ; c = *p; p++)
  {
    r=SPI.transfer(c);
    Serial.print(r);
  }
  Serial.println('!');
  // disable Slave Select
  digitalWrite(SS, HIGH);
//////////////////////////////////////////////////////////////
  digitalWrite(9, LOW);    // SS is pin 10

  // send test string
  for (const char * p = "ABC\n" ; c = *p; p++)
  {
    r=SPI.transfer(c);
    Serial.print(r);
  }
  Serial.println('!');
  // disable Slave Select
  digitalWrite(9, HIGH);

  delay (500);  // 1 seconds delay 
}  // end of loop
