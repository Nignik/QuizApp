#pragma once

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class CSVRow
{
public:
	std::wstring_view operator[](std::size_t index) const
	{
		return std::wstring_view(&m_line[m_data[index] + 1], m_data[index + 1] - (m_data[index] + 1));
	}
	std::size_t size() const
	{
		return m_data.size() - 1;
	}
	void readNextRow(std::wistream& str)
	{
		std::getline(str, m_line);

		m_data.clear();
		m_data.emplace_back(-1);
		std::wstring::size_type pos = 0;
		while ((pos = m_line.find(L',', pos)) != std::wstring::npos)
		{
			m_data.emplace_back(pos);
			++pos;
		}
		// This checks for a trailing comma with no data after it.
		pos = m_line.size();
		m_data.emplace_back(pos);
	}
private:
	std::wstring         m_line;
	std::vector<int>    m_data;
};

inline std::wistream& operator>>(std::wistream& str, CSVRow& data)
{
	data.readNextRow(str);
	return str;
}

class CSVIterator
{
public:
	typedef std::input_iterator_tag     iterator_category;
	typedef CSVRow                      value_type;
	typedef std::size_t                 difference_type;
	typedef CSVRow* pointer;
	typedef CSVRow& reference;

	CSVIterator(std::wistream& str) :m_str(str.good() ? &str : nullptr) { ++(*this); }
	CSVIterator() :m_str(nullptr) {}

	// Pre Increment
	CSVIterator& operator++() { if (m_str) { if (!((*m_str) >> m_row)) { m_str = nullptr; } }return *this; }
	// Post increment
	CSVIterator operator++(int) { CSVIterator    tmp(*this); ++(*this); return tmp; }
	CSVRow const& operator*()   const { return m_row; }
	CSVRow const* operator->()  const { return &m_row; }

	bool operator==(CSVIterator const& rhs) { return ((this == &rhs) || ((this->m_str == nullptr) && (rhs.m_str == nullptr))); }
	bool operator!=(CSVIterator const& rhs) { return !((*this) == rhs); }
private:
	std::wistream* m_str;
	CSVRow              m_row;
};

class CSVRange
{
	std::wistream& stream;
public:
	CSVRange(std::wistream& str)
		: stream(str)
	{
	}
	CSVIterator begin() const { return CSVIterator{ stream }; }
	CSVIterator end()   const { return CSVIterator{}; }
};