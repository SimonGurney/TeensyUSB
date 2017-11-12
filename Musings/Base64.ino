// Download zip of https://github.com/adamvr/arduino-base64  and import into Arduino as Zip library
#include <Base64.h>
#define ledPin 13

void setup() {
pinMode(ledPin, OUTPUT);
digitalWrite(ledPin, HIGH);
};

void b64EncodeAndType(char* inputString){
int inputLen = strlen(inputString);
int encodedLen = base64_enc_len(inputLen);
char encoded[encodedLen];
base64_encode(encoded, inputString, inputLen);
Keyboard.println(encoded); // Do something with it as it will be DESTROYED
};

void loop() {
delay(1000);
b64EncodeAndType("simon is really really really cool");
b64EncodeAndType("simon is still really really really cool");
}

