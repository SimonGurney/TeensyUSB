class Controller
{
public:
	static void sendModifier(int Key);
	static void rightClick();
	static void unSelectObject();
	static void sendKey(int key, int numberOfTimes = 1);
};

class WindowsController : public Controller
{
public:
	static void goToDesktop();  // Requires sendKey and unSelectObject
	static void cmdViaShortcut(String, String = "a1b2c3d4e5"); // Requires sendKey and goToDesktop
};