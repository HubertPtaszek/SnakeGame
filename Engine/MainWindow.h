#pragma once
#include "ChiliWin.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "ChiliException.h"
#include <string>

using namespace std;

/*!
* @brief Nadanie dostepu dla klasy Graphics do klasy wbudowanej HWNDKey
*/
class HWNDKey
{
	friend Graphics::Graphics(HWNDKey&);
public:
	HWNDKey(const HWNDKey&) = delete;
	HWNDKey& operator=(HWNDKey&) = delete;
protected:
	HWNDKey() = default;
protected:
	HWND hWnd = nullptr;
};

/*!
* @brief Klasa MainWindow dziedziczy równie¿ po klasie wbudowanej HWNDKey.
*
* Zawiera ona obs³uge wyj¹tków oraz standardowwa obs³ugê okna.
*/
class MainWindow : public HWNDKey
{
	static LRESULT WINAPI _HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI _HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static constexpr wchar_t* wndClassName = L"Snake Game";
	HINSTANCE hInst = nullptr;
	wstring args;
public:
	class Exception : public ChiliException
	{
	public:
		using ChiliException::ChiliException;
		virtual wstring GetFullMessage() const override { return GetNote() + L"\nAt: " + GetLocation(); }
		virtual wstring GetExceptionType() const override { return L"Windows Exception"; }
	};
	MainWindow(HINSTANCE hInst, wchar_t* pArgs);
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
	~MainWindow();
	bool IsActive() const;
	bool IsMinimized() const;
	void ShowMessageBox(const wstring& title, const wstring& message) const;
	void Kill()
	{
		PostQuitMessage(0);
	}
	bool ProcessMessage();
	const wstring& GetArgs() const
	{
		return args;
	}
	Keyboard kbd;
	Mouse mouse;
};