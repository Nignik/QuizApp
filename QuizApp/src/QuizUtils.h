#pragma once

#include <locale>
#include <codecvt>
#include <cwctype>

inline void ltrim(std::wstring& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](wchar_t ch) {
		return !std::iswspace(ch);
		}));
}

inline void rtrim(std::wstring& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](wchar_t ch) {
		return !std::iswspace(ch);
		}).base(), s.end());
}