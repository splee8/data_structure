// linked_list.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <list>
#include <assert.h>

#define SAFE_DELETE(p) { delete p; p = nullptr; }

template <typename T>
class linked_list
{
public:
	struct elem
	{
		elem* m_prev = nullptr;
		elem* m_next = nullptr;
		T m_val = T();
	};

	class iterator
	{
	public:
		iterator(elem* rhs) : m_elem(rhs) {}

		iterator next()
		{
			return iterator(m_elem->m_next);
		}

		iterator prev()
		{
			return iterator(m_elem->m_prev);
		}

		bool operator==(const iterator& rhs)
		{
			return m_elem == rhs.m_elem;
		}

		bool operator!=(const iterator& rhs)
		{
			return !operator==(rhs);
		}

		bool valid()
		{
			return m_elem != nullptr;
		}

		T val()
		{
			if (!m_elem)
			{
				return T();
			}
			return m_elem->m_val;
		}

	private:
		elem* m_elem = nullptr;
		friend class linked_list<T>;
	};

	iterator begin()
	{
		return m_begin;
	}

	iterator end()
	{
		if (m_end)
		{
			m_end->m_next;
		}
		return nullptr;
	}

	void push_back(const T& rhs)
	{
		++m_count;
		elem* new_elem = new elem();
		new_elem->m_val = rhs;
		if (!m_end)
		{
			assert(!m_begin);
			m_begin = m_end = new_elem;
			return;
		}
		new_elem->m_prev = m_end;
		m_end->m_next = new_elem;
		m_end = new_elem;
	}

	void push_front(const T& rhs)
	{
		++m_count;
		elem* new_elem = new elem();
		new_elem->m_val = rhs;
		if (!m_begin)
		{
			assert(m_end == nullptr);
			m_begin = m_end = new_elem;
			return;
		}
		new_elem->m_next = m_begin;
		m_begin->m_prev = new_elem;
		m_begin = new_elem;
	}

	T pop_back()
	{
		T val = m_end->m_val;
		elem* end = m_end;
		m_end = m_end->m_prev;
		SAFE_DELETE(end);
		if (m_end)
		{
			m_end->m_next = nullptr;
		}
		--m_count;
		return val;
	}

	T pop_front()
	{
		T val = m_begin->m_val;
		elem* begin = m_begin;
		m_begin = m_begin->m_next;
		SAFE_DELETE(begin);
		if (m_begin)
		{
			m_begin->m_prev = nullptr;
		}
		--m_count;
		return val;
	}

	bool exist(const iterator& find_iter)
	{
		for (auto iter = begin(); iter != end(); iter = iter.next())
		{
			if (iter == find_iter)
				return true;
		}
		return false;
	}

	bool insert(iterator insert_iter, const T& rhs)
	{
		if (!exist(insert_iter))
		{
			return false;
		}
		elem* new_elem = new elem();
		new_elem->m_val = rhs;
		new_elem->m_next = insert_iter.m_elem->m_next;
		new_elem->m_prev = insert_iter.m_elem;
		insert_iter.m_elem->m_next = new_elem;
		++m_count;
		return true;
	}

	bool remove(iterator remove_iter)
	{
		if (!exist(remove_iter))
		{
			return false;
		}
		elem* remove_elem = remove_iter.m_elem;
		elem* remove_prev = remove_elem->m_prev;
		elem* remove_next = remove_elem->m_next;
		if (remove_prev)
		{
			remove_prev->m_next = remove_next;
		}
		if (remove_next)
		{
			remove_next->m_prev = remove_prev;
		}
		if (remove_iter == begin())
		{
			m_begin = remove_next;
		}
		else if (remove_iter == end())
		{
			m_end = remove_prev;
		}
		SAFE_DELETE(remove_elem);
		--m_count;
		return true;
	}

	void clear()
	{
		while (m_end)
		{
			pop_back();
		}
	}

private:
	elem* m_begin = nullptr;
	elem* m_end = nullptr;
	size_t m_count = 0;
	friend class linked_list<T>;
};

int main()
{
	linked_list<int> list;
	list.push_front(0);
	list.push_front(5);
	list.push_front(4);
	list.push_front(3);
	list.push_front(2);
	list.pop_back();
	list.push_back(9);
	list.push_back(7);
	list.push_back(6);
	list.push_back(8);
	list.push_back(1);
	list.pop_front();
	for (auto iter = list.begin(); iter != list.end(); iter = iter.next())
	{
		std::cout << iter.val() << ", ";
	}
	list.clear();
	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
