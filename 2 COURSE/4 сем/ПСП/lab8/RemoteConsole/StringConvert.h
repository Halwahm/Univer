#pragma once
#include <string>
#include <cassert>
#include <vector>
std::string get_locale_string(const std::wstring& s)
{
	const wchar_t* cs = s.c_str();
#pragma warning(suppress : 4996)
	const size_t wn = wcsrtombs(NULL, &cs, 0, NULL);

	if (wn == size_t(-1))
	{
		return "";
	}

	std::vector<char> buf(wn + 1);
#pragma warning(suppress : 4996)
	const size_t wn_again = wcsrtombs(&buf[0], &cs, wn + 1, NULL);

	if (wn_again == size_t(-1))
	{
		return "";
	}

	assert(cs == NULL); // successful conversion

	return std::string(&buf[0], wn);
}

std::wstring get_wstring(const std::string& s)
{
	const char* cs = s.c_str();
#pragma warning(suppress : 4996)
	const size_t wn = mbsrtowcs(NULL, &cs, 0, NULL);

	if (wn == size_t(-1))
	{
		return L"";
	}

	std::vector<wchar_t> buf(wn + 1);
#pragma warning(suppress : 4996)
	const size_t wn_again = mbsrtowcs(&buf[0], &cs, wn + 1, NULL);

	if (wn_again == size_t(-1))
	{
		return L"";
	}

	assert(cs == NULL); // successful conversion

	return std::wstring(&buf[0], wn);
}