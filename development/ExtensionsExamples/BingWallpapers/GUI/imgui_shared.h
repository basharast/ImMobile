#pragma once

enum ImGuiWindowFlags_Custom {
	// Render even if not focused
	ImGuiWindowFlags_RenderAlways		= 1 << 19,

	// Show touch pad
	ImGuiWindowFlags_TouchPad			= 1 << 20,

	// Force 30 FPS (Less GPU load)
	ImGuiWindowFlags_30FPS				= 1 << 21,

	// Delay render (Less CPU load)
	ImGuiWindowFlags_SleepFPS			= 1 << 22,

	// Force full mode
	ImGuiWindowFlags_RequireFull		= 1 << 29,

	// Don't show in task bar
	ImGuiWindowFlags_NoTaskBar			= 1 << 31,
};

enum ImGuiKeyboardFlags_Custom {
	ImGuiKeyboardFlags_Text,
	ImGuiKeyboardFlags_Number,
	ImGuiKeyboardFlags_URL,
	ImGuiKeyboardFlags_Email,
	ImGuiKeyboardFlags_FilePath,
	ImGuiKeyboardFlags_FileName,
	ImGuiKeyboardFlags_Digits,
};

struct inputFunctions
{
	static int inputCallback(ImGuiInputTextCallbackData* data);
};

enum class NetworkLevel
{
	None = 0,
	LocalAccess = 1,
	ConstrainedInternetAccess = 2,
	InternetAccess = 3,
	BlockByImMobile = 4,
	NotConnected = 5,
};

enum class SaverStatus
{
	Disabled = 0,
	Off = 1,
	On = 2,
};

enum class BluetoothState
{
	Unknown = 0,
	On = 1,
	Off = 2,
	Disabled = 3,
};

enum class SensorsDirection
{
	Up = 0,
	Down = 1,
	Left = 2,
	Right = 3,
};

enum class GamePadButtons
{
	None = 0,
	Menu = 0x1,
	View = 0x2,
	A = 0x4,
	B = 0x8,
	X = 0x10,
	Y = 0x20,
	DPadUp = 0x40,
	DPadDown = 0x80,
	DPadLeft = 0x100,
	DPadRight = 0x200,
	LeftShoulder = 0x400,
	RightShoulder = 0x800,
	LeftThumbstick = 0x1000,
	RightThumbstick = 0x2000,
	Paddle1 = 0x4000,
	Paddle2 = 0x8000,
	Paddle3 = 0x10000,
	Paddle4 = 0x20000,
};


enum class TouchPadButtons
{
	Select = 0,
	L3 = 1,
	R3 = 2,
	Start = 3,
	Up = 4,
	Right = 5,
	Down = 6,
	Left = 7,
	L2 = 8,
	R2 = 9,
	L1 = 10,
	R1 = 11,
	One = 12,
	Two = 13,
	Three = 14,
	Four = 15,
	Analog = 16, // Menu if analog disabled
	Count // Menu button
};
