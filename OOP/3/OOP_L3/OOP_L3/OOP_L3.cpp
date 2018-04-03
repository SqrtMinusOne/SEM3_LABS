// OOP_L3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <iterator>
#include <initializer_list>
#include <stdexcept>

namespace stepik
{
	template <typename Type>
	class vector
	{
	public:
		typedef Type* iterator;
		typedef const Type* const_iterator;

		typedef Type value_type;

		typedef value_type& reference;
		typedef const value_type& const_reference;

		typedef std::ptrdiff_t difference_type;

		explicit vector(size_t count = 0) //Инициализация с числом
		{
			if (count) {
				m_first = new Type[count];
				m_last = m_first + count;
			}
			else {
				m_first = nullptr;
				m_last = nullptr;
			}
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last) //Инициализация с содержимым диапазона [first, last)
		{
			size_t count = last - first;
			if (count) {
				m_first = new Type[count];
				copy(first, last, stdext::checked_array_iterator<Type*>(m_first, count));
				m_last = m_first + count;
			}
			else {
				m_first = nullptr;
				m_last = nullptr;
			}
		}

		vector(std::initializer_list<Type> init) : vector (init.begin(), init.end()) //Инициализация с помощью списка инициализации
		{
			
		}

		vector(const vector& other) : vector (other.begin(), other.end())//Копирование
		{
			
		}

		vector(vector&& other)
		{
			m_first = other.m_first;
			m_last = other.m_last;
			other.m_first = nullptr;
			other.m_last = nullptr;
		}

		~vector()
		{
			if (!empty()) {
				delete[] m_first;
				m_first = nullptr;
			}
		}

		//at methods
		reference at(size_t pos)
		{
			return checkIndexAndGet(pos);
		}

		const_reference at(size_t pos) const
		{
			return checkIndexAndGet(pos);
		}

		//[] operators
		reference operator[](size_t pos)
		{
			return m_first[pos];
		}

		const_reference operator[](size_t pos) const
		{
			return m_first[pos];
		}

		//*begin methods
		iterator begin()
		{
			return m_first;
		}

		const_iterator begin() const
		{
			return m_first;
		}

		//*end methods
		iterator end()
		{
			return m_last;
		}

		const_iterator end() const
		{
			return m_last;
		}

		//size method
		size_t size() const
		{
			return m_last - m_first;
		}

		//empty method
		bool empty() const
		{
			return m_first == m_last;
		}

		void fill(Type T) {
			for (size_t i = 0; i < size(); i++) {
				this->operator[](i) = T;
			}
		}

		void out() {
			if (m_first) {
				for (size_t i = 0; i < size(); i++) {
					std::cout << this->operator[](i) << " ";
				}
				std::cout << endl;
			}
			else {
				std::cout << "Container has been destroyed" << endl;
			}
		}

	private:
		reference checkIndexAndGet(size_t pos) const
		{
			if (pos >= size())
			{
				throw std::out_of_range("out of range");
			}

			return m_first[pos];
		}

		//your private functions

	private:
		iterator m_first;
		iterator m_last;
	};
}// namespace stepik

using namespace std;

int main() {
	//Инициализация с числом
	stepik::vector<int> a(10);
	a.fill(10);
	a.out();
	cout << "---------------" << endl;
	//Инициализация с содержимым диапазона [first, last)
	stepik::vector<int> b(a.begin(), a.end());
	a[5] = 2;
	a.out();
	b.out();
	cout << "---------------" << endl;
	//Инициализация с помощью списка инициализации
	stepik::vector<int> c{ 1, 2, 3, 4, 5 };
	c.out();
	cout << "---------------" << endl;
	//Копирование
	stepik::vector<int> d(c);
	c[3] = 0;
	c.out();
	d.out();
	cout << "---------------" << endl;
	//Перемещение
	stepik::vector<int> e(std::move(d));
	d.out();
	e.out();
	cout << "---------------" << endl;
	//Разрушение
	e.~vector();
	e.out();

	return 0;
}