#include "Controller.h"

#define modifierKeyReleaseDelay 50
#define sendKeyReleaseDelay 50
	void Controller::sendModifier(int Key)
	{
		Keyboard.set_modifier(Key);
		Keyboard.send_now();
		delay(modifierKeyReleaseDelay);
		Keyboard.set_modifier(0);
		Keyboard.send_now();
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
		unSelectObject(); // unSelect the random item
	};
	void WindowsController::cmdViaShortcut(String cmd, String shortcutName) // Requires sendKey and goToDesktop
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