#define modifierKeyReleaseDelay 50
#define sendKeyReleaseDelay 50
#define ledPin 13
#define randomStringLength 50
#define errorBase 50
#define storageRootDir "/"
#define base64BlockSize 10 // base64 is 4 characters for 3 bytes.  Multiplied in functions
#define base64InputSize base64BlockSize * 3
#define base64EncodedSize base64BlockSize * 4
#define fileReadBufSize base64InputSize

#include <Base64.h>
#include <SD.h>
#include <SD_t3.h>

class Controller
{
private:

protected:
	char randomStringBuf[randomStringLength + 1];
	char base64Buf[base64EncodedSize];
	char fileReadBuf[fileReadBufSize];
	File storage;
	void initilialiseBase64Buf();
	void initilialiseFileReadBuf();
public:
	char* base64Encode(char* inputString, int inputStringLength = base64InputSize);
	void blink(int msDelay = 200);
	Controller();
	File currentFile;
	void error();
	char* generateRandom();
	char* readCurrentFile();
	void rightClick();
	void sendModifier(int Key);
	void sendKey(int key, int numberOfTimes = 1);
	void unSelectObject();
};

class WindowsController : public Controller
{
public:
	void goToDesktop();  // Requires sendKey and unSelectObject
	void cmdViaShortcut(char *, char * = "a2b2c3d4e5"); // Requires sendKey and goToDesktop
};