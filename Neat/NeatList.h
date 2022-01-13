#pragma once

#include <vector>
#include <functional>
#include "NeatRandom.h"

#include <iostream>

template<typename T>
class NeatList
{
public:
	using List = std::vector<T>;

	NeatList();
	NeatList(const NeatList& other);

	NeatList& operator=(const NeatList& other);

	unsigned int size();

	void addObject(T object);
	T& popEnd();
	T& getObjectAt(unsigned int index);
	T& getRandomObject();

	void sort(std::function<bool(T, T)> f);

	void setRandom(std::shared_ptr<NeatRandom> _neatRandom) { neatRandom = _neatRandom; }
	bool hasRandom();

	void clear();

	auto begin();
	auto end();

	T& findBasedOn(std::function<bool(T)> f);
	bool contains(T& t, std::function<bool(T)> f);

	void print();

	T& operator[](int index) 
	{
		return list->at(index);
	}

private:
	std::shared_ptr<List> list;
	std::shared_ptr<NeatRandom> neatRandom;
};

template<typename T>
inline void NeatList<T>::clear()
{
	list->clear();
}

template<typename T>
inline NeatList<T>::NeatList()
	:list(std::make_shared<List>()),
	neatRandom(nullptr)
{
}

template<typename T>
inline NeatList<T>& NeatList<T>::operator=(const NeatList& other)
{
	if (this != &other) 
	{
		list = other.list;
		neatRandom = other.neatRandom;
	}

	return *this;
}

template<typename T>
inline NeatList<T>::NeatList(const NeatList& other)
{
	if (this != &other)
	{
		list = other.list;
		neatRandom = neatRandom;
	}
}

template<typename T>
inline unsigned int NeatList<T>::size()
{
	return static_cast<unsigned int>(list->size());
}

template<typename T>
inline void NeatList<T>::addObject(T object)
{
	list->push_back(object);
}

template<typename T>
inline T& NeatList<T>::popEnd()
{
	T object = list->at(list->size() - 1);
	list->pop_back();
	return object;
}

template<typename T>
inline T& NeatList<T>::getObjectAt(unsigned int index)
{
	return list->at(index);
}

template<typename T>
inline T& NeatList<T>::getRandomObject()
{
	/*if (neatRandom == nullptr) 
	{
		neatRandom = std::make_shared<NeatRandom>();
	}*/
	unsigned int index = neatRandom->getRandomInt(0,size()-1);
	return list->at(index);
}

template<typename T>
inline bool NeatList<T>::hasRandom()
{
	return neatRandom == nullptr;
}

template<typename T>
inline void NeatList<T>::sort(std::function<bool(T, T)> f)
{
	std::sort(begin(), end(), f);
}

template<typename T>
inline auto NeatList<T>::begin()
{
	return list->begin();
}

template<typename T>
inline auto NeatList<T>::end()
{
	return list->end();
}

template<typename T>
inline void NeatList<T>::print()
{
	std::cout << " [";
	for (auto element: *list) 
	{
		std::cout << "" << element << " ";
	}
	std::cout << " ]\n";
}

template<typename T>
std::ostream& operator<<(std::ostream& strm, NeatList<T>& a) {
	return strm << "Size: " << a.size();
}