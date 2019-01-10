#pragma once
#include "ChiliWin.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "ChiliException.h"
#include <string>

using namespace std;

/**
* Nadanie dostepu dla klasy Graphics do klasy wbudowanej HWNDKey
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

/**
* Klasa MainWindow dziedziczy r�wnie� po klasie wbudowanej HWNDKey.
*
* Zawiera ona obs�uge wyj�tk�w oraz standardowwa obs�ug� okna.
*/
class MainWindow : public HWNDKey
{
public:
	class Exception : public ChiliException
	{
	public:
		using ChiliException::ChiliException;
		virtual wstring GetFullMessage() const override { return GetNote() + L"\nAt: " + GetLocation(); }
		virtual wstring GetExceptionType() const override { return L"Windows Exception"; }
	};
public:
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
private:
	static LRESULT WINAPI _HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI _HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	Keyboard kbd;
	Mouse mouse;
private:
	static constexpr wchar_t* wndClassName = L"Snake Game";
	HINSTANCE hInst = nullptr;
	wstring args;
};