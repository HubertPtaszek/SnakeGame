#pragma once
#include <string>

using namespace std;

class ChiliException
{
	wstring note;
	wstring file;
	unsigned int line;
public:
	ChiliException(const wchar_t* file, unsigned int line, const wstring& note = L"") : note(note), file(file), line(line)
	{}

	const wstring& GetNote() const
	{
		return note;
	}
	const wstring& GetFile() const
	{
		return file;
	}
	unsigned int GetLine() const
	{
		return line;
	}
	wstring GetLocation() const
	{
		return wstring(L"Line [") + to_wstring(line) + L"] in " + file;
	}
	virtual wstring GetFullMessage() const = 0;
	virtual wstring GetExceptionType() const = 0;
};