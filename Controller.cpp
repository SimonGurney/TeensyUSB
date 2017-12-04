#include "Controller.h"

	Controller::Controller(void)
	{
		pinMode(ledPin, OUTPUT);
		if (!(SD.begin(BUILTIN_SDCARD)))
			{
			error();	// Card not initiliased - ERROR
			}
		storage = SD.open(storageRootDir);
		currentFile = storage.openNextFile();
		if (strncmp(currentFile.name(), "SYSTEM", 6) == 0)
			{
			currentFile = storage.openNextFile();
			}
		if (! currentFile)
			{
			error(); // no more files, finished iteration
			}
	}
	char * Controller::base64Encode(char* inputString, int inputStringLength)
	{
		if (inputStringLength > base64InputSize)
		{
			error();
		}
		initilialiseBase64Buf();
		int inputLen = inputStringLength;
		int encodedLen = base64_enc_len(inputLen);
		base64_encode(base64Buf, inputString, inputLen);
		return base64Buf;
	};
	void Controller::blink(int msDelay)
	{
		digitalWrite(ledPin, HIGH);
		delay(msDelay);
		digitalWrite(ledPin, LOW);
	};
	void Controller::error()
	{
		while(true)
		{
			blink(errorBase);
			delay(errorBase * 2);
			blink(errorBase);
			delay(errorBase * 2);
			blink(errorBase * 10);
			delay(errorBase * 2);
		}
	}
	char* Controller::generateRandom()
	{
		randomSeed(analogRead(0));
		for (int i = 0; i < randomStringLength; ++i)
		{
			randomStringBuf[i] = random(65,90);
		}
		randomStringBuf[randomStringLength] = '\0';
		return randomStringBuf;
	};
	bool Controller::getLedState(int led)
	{
		if(keyboard_leds & led)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	};
	void Controller::initilialiseBase64Buf()
	{
		for (int i = 0; i < base64EncodedSize; ++i)
		{
			base64Buf[i] = '\0';
		}
	};
	void Controller::initilialiseFileReadBuf()
	{
		for (int i = 0; i < fileReadBufSize; ++i)
		{
			fileReadBuf[i] = '\0';
		}
	};
	void Controller::sendModifier(int key)
	{
		Keyboard.set_modifier(key);
		Keyboard.send_now();
		delay(modifierKeyReleaseDelay);
		Keyboard.set_modifier(0);
		Keyboard.send_now();
	};
	char* Controller::readCurrentFile()
	{
		initilialiseFileReadBuf();
		currentFile.read(fileReadBuf,fileReadBufSize);
		return fileReadBuf;
	};
	void Controller::rightClick()
	{
		Keyboard.set_modifier(MODIFIERKEY_SHIFT);
		Keyboard.set_key1(KEY_F10);
		Keyboard.send_now();
		delay(modifierKeyReleaseDelay);
		Keyboard.set_key1(0);
		Keyboard.set_modifier(0);
		Keyboard.send_now();
		delay(50); // Give it chance!
	};
	void Controller::unSelectObject()
	{
		Keyboard.set_modifier(MODIFIERKEY_CTRL);
		Keyboard.set_key1(KEY_SPACE);
		Keyboard.send_now();
		delay(modifierKeyReleaseDelay);
		Keyboard.set_key1(0);
		Keyboard.set_modifier(0);
		Keyboard.send_now();
		delay(50); // Give it chance!
	};
	void Controller::sendKey(int key, int numberOfTimes)
	{
		int i = 0;
		for (i = 0; i != numberOfTimes; i++)
		{
			Keyboard.set_key1(key);
			Keyboard.send_now();
			delay(sendKeyReleaseDelay);
			Keyboard.set_key1(0);
			Keyboard.send_now();
			delay(50);
		}
	};
	void Controller::typeCurrentFile()
	{
		while(currentFile.available())
		{
			delay(100);
			Keyboard.print(base64Encode(readCurrentFile()));
		}
	};
	void Controller::waitForKey(int key)
	{
		int led = 0;
		
		switch(key)
		{
			case KEY_NUM_LOCK: led = USB_LED_NUM_LOCK; break;
			case KEY_SCROLL_LOCK: led = USB_LED_SCROLL_LOCK; break;
			case KEY_CAPS_LOCK: led = USB_LED_CAPS_LOCK; break;
			default: error(); break;
		}
	while(getLedState(led)) // Turn led off if needed
		{
			sendKey(key);
		}
		digitalWrite(ledPin, HIGH); // Turn LED on to indicate waiting for input
		while (!getLedState(led))
		{
			delay(50);
		}
		digitalWrite(ledPin, LOW); // Turn LED off to indicate continued execution
	};
	void WindowsController::goToDesktop()  // Requires sendKey and unSelectObject
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
		sendKey(KEY_LEFT,1); // Select a random item if we can't go right
		unSelectObject(); // unSelect the random item
	};
	void WindowsController::cmdViaShortcut(char *cmd, char *shortcutName) // Requires sendKey and goToDesktop
	{
		goToDesktop();
		rightClick();
		sendKey(KEY_W,1);
		sendKey(KEY_W,1);
		sendKey(KEY_RIGHT,1);
		sendKey(KEY_S,1);
		sendKey(KEY_ENTER,1);
		delay(300); // Wait for the new shortcut window to open
		Keyboard.print(cmd); 
		sendKey(KEY_ENTER,1);
		Keyboard.print(shortcutName);
		sendKey(KEY_ENTER,1);
		delay(300); // Wait for the shortcut to be created
		goToDesktop();
		Keyboard.print(shortcutName);
		delay(100); // Wait for explorer to catch up
		sendKey(KEY_ENTER,1);
	};