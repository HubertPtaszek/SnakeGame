#pragma once
#include <queue>
#include <bitset>

using namespace std;

/*!
* @brief Klasa do obs³ugi klawiatury.
*
* @details Istnieje ona domyœlnie, lecz na potrzeby naszej aplikacji zosta³a rozszerzona.
*/
class Keyboard
{
	friend class MainWindow;
	void OnKeyPressed(unsigned char keycode);
	void OnKeyReleased(unsigned char keycode);
	void OnChar(char character);
	template<typename T>
	void TrimBuffer(queue<T>& buffer);
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 4u;
	bool autorepeatEnabled = false;
	bitset<nKeys> keystates;
	queue<char> charbuffer;
public:
	class Event
	{
		unsigned char code;
	public:
		enum Type
		{
			Press,
			Release,
			Invalid
		};
		Event()
			:
			type(Invalid),
			code(0u)
		{}
		Event(Type type, unsigned char code)
			:
			type(type),
			code(code)
		{}
		bool IsPress() const
		{
			return type == Press;
		}
		bool IsRelease() const
		{
			return type == Release;
		}
		bool IsValid() const
		{
			return type != Invalid;
		}
		unsigned char GetCode() const
		{
			return code;
		}
	private:
		Type type;
	};
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	bool KeyIsPressed(unsigned char keycode) const;
	Event ReadKey();
	bool KeyIsEmpty() const;
	char ReadChar();
	bool CharIsEmpty() const;
	void FlushKey();
	void FlushChar();
	void Flush();
	void EnableAutorepeat();
	void DisableAutorepeat();
	bool AutorepeatIsEnabled() const;
private:
	queue<Event> keybuffer;
};