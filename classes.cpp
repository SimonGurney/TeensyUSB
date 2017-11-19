#define modifierKeyReleaseDelay 50
#define sendKeyReleaseDelay 50
class Controller
{
public:
	void sendModifier(int Key)
	{
		Keyboard.set_modifier(Key);
		Keyboard.send_now();
		delay(modifierKeyReleaseDelay);
		Keyboard.set_modifier(0);
		Keyboard.send_now();
	}
	void rightClick()
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
	void unSelectObject()
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
	void sendKey(int key, int numberOfTimes)
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
	}
}