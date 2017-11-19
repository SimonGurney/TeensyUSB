#include <Base64.h>
#include <SD.h>
#include <SD_t3.h>
#define ledPin 13
#define modifierKeyReleaseDelay 50
#define sendKeyReleaseDelay 50

void blink()
{
digitalWrite(ledPin, HIGH);
delay(200);
digitalWrite(ledPin, LOW);
}

void b64EncodeAndType(char* inputString){
int inputLen = 3; //strlen(inputString);
//Keyboard.println(inputLen);
int encodedLen = base64_enc_len(inputLen);
//Keyboard.println(encodedLen);
char encoded[encodedLen];
base64_encode(encoded, inputString, inputLen);
Keyboard.print(encoded); // Do something with it as it will be DESTROYED
delay(10);
};

void error()
{
  while(true)
  {
    blink();
  }
}

void eraseBuff(char* buf)
{
    buf[0] = '\0';
    buf[1] = '\0';
    buf[2] = '\0';
}
bool unSelectObject()
{
Keyboard.set_modifier(MODIFIERKEY_CTRL);
Keyboard.set_key1(KEY_SPACE);
Keyboard.send_now();
delay(modifierKeyReleaseDelay);
Keyboard.set_key1(0);
Keyboard.set_modifier(0);
Keyboard.send_now(); 
delay(50); // Give it chance!
}

void sendKey(int key,int numberOfTimes){
int i=0;
for (i=0; i!=numberOfTimes; i++){
Keyboard.set_key1(key);
Keyboard.send_now();
delay(sendKeyReleaseDelay);
Keyboard.set_key1(0); 
Keyboard.send_now();
delay(50);
}
}
bool rightClick()
{
Keyboard.set_modifier(MODIFIERKEY_SHIFT);
Keyboard.set_key1(KEY_F10);
Keyboard.send_now();
delay(modifierKeyReleaseDelay);
Keyboard.set_key1(0);
Keyboard.set_modifier(0);
Keyboard.send_now();
delay(50); // Give it chance!
}

void goToDesktop()  // Requires sendKey and unSelectObject
{
Keyboard.set_modifier(MODIFIERKEY_GUI);
Keyboard.set_key1(KEY_M);
Keyboard.send_now();
delay(50);
Keyboard.set_key1(0);
Keyboard.set_modifier(0);
Keyboard.send_now();
delay(100); // Give it chance to minimise windows
sendKey(KEY_RIGHT,1); // Select a random item
delay(500);
unSelectObject(); // unSelect the random item
delay(500);
}

void cmdViaShortcut(String cmd, String shortcutName) // Requires sendKey and goToDesktop
{
goToDesktop();
delay(1000);
rightClick();
delay(1000);
sendKey(KEY_W,1);
sendKey(KEY_W,1);
sendKey(KEY_RIGHT,1);
sendKey(KEY_S,1);
//sendKey(KEY_ENTER,1);
delay(500); // Wait for the new shortcut window to open
Keyboard.print(cmd); 
sendKey(KEY_ENTER,1);
Keyboard.print(shortcutName);
delay(1000);
sendKey(KEY_ENTER,1);
delay(500); // Wait for the shortcut to be created
goToDesktop();
Keyboard.print(shortcutName);
delay(100); // Wait for explorer to catch up
sendKey(KEY_ENTER,1);
}

void setup() 
{
  char buf[3];//29
  delay(5000);
  pinMode(ledPin, OUTPUT);
  randomSeed(analogRead(0));
  char randString[5];
  randString[0] = random(65,90);
  randString[1] = random(65,90);
  randString[2] = random(65,90);
  randString[3] = random(65,90);
  randString[4] = '\0';
  
  cmdViaShortcut("PowerShell.exe", randString);
  delay(3000); // Give PowerShell chance to initialise
  
  if (!(SD.begin(BUILTIN_SDCARD)))
  {
    // Card not initiliased - ERROR
    error();
  }
  
  File root;
  root = SD.open("/");
  
  while(true)
  {
    File f = root.openNextFile();
    if (! f)
    {
      // no more files, finished iteration
      break;
    }
  // Keyboard.println(entry.name());
    if (strncmp(f.name(), "SYSTEM", 6) != 0)
    {
        Keyboard.println("$outputFilePath = [Environment]::GetFolderPath('Desktop')");
        Keyboard.println("$outputFilePath += '\\'");
        Keyboard.print("$outputFilePath += '");
        Keyboard.print(f.name());
        Keyboard.println("'");
        Keyboard.print("$b64 = '");
      while (f.available()) 
      {
        eraseBuff(buf);
        f.read(buf,3);//30
        //Keyboard.println(buf);
        b64EncodeAndType(buf);
      }
      eraseBuff(buf);
      Keyboard.println("'");
      Keyboard.println("$PEBytes = [System.Convert]::FromBase64String($b64)");
      Keyboard.println("[System.IO.File]::WriteAllBytes($outputFilePath, $PEBytes);");
      //Keyboard.println("notepad.exe $outputFilePath");
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
