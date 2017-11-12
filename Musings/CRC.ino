#include <FastCRC.h>
#include <FastCRC_cpu.h>
#include <FastCRC_tables.h>
FastCRC32 CRC32;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
delay(2000);
char buf[] = "Simon is cool";
Keyboard.println(buf);
Keyboard.println( CRC32.crc32((uint8_t *)buf, sizeof(buf) - 1), HEX );
}
