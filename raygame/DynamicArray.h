#pragma once

template<typename T>
class DynamicArray
{
public:
	DynamicArray();
	DynamicArray(const T* array, int size);
	DynamicArray(const DynamicArray<T>& other);
	~DynamicArray();

	DynamicArray<T>& operator=(const DynamicArray<T>& other);
	T& operator[](int index);
	const T& operator[](int index) const;

	int Length() const;
	void Resize(int newSize);

	T* begin();
	const T* begin() const;
	T* end();
	const T* end() const;

	void Add(const T& value);
	void Add(const T* array, int size);
	void Add(const DynamicArray<T>& other);
	void AddUnique(const T& value);
	void Insert(int index, const T& value);
	void Insert(int index, const T* array, int size);
	void Insert(int index, const DynamicArray<T>& other);
	void RemoveIndex(int index);
	bool Remove(const T& value);
	bool Remove(const T* array, int size);
	bool Remove(const DynamicArray<T>& other);
	void Clear();

private:
	T* m_array;
	int m_length;
};

template<typename T>
inline DynamicArray<T>::DynamicArray()
{
	m_length = 0;
	m_array = new T[m_length];
}

template<typename T>
inline DynamicArray<T>::DynamicArray(const T* array, int size)
{
	m_length = size;
	m_array = new T[m_length];
	for (int i = 0; i < m_length; i++)
	{
		m_array[i] = array[i];
	}
}

template<typename T>
inline DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
{
	m_length = other.m_length;
	m_array = new T[m_length];
	for (int i = 0; i < m_length, i++;)
	{
		m_array[i] = other.m_array[i];
	}
}

template<typename T>
inline DynamicArray<T>::~DynamicArray()
{
	delete[] m_array;
}

template<typename T>
inline DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
{
	m_length = other.m_length;
	delete[] m_array;
	m_array = new T[m_length];
	for (int i = 0; i < m_length; i++)
	{
		m_array[i] = other.m_array[i];
	}
	return *this;
}

template<typename T>
inline T& DynamicArray<T>::operator[](int index)
{
	return m_array[index];
}

template<typename T>
inline const T& DynamicArray<T>::operator[](int index) const
{
	return m_array[index];
}

template<typename T>
inline int DynamicArray<T>::Length() const
{
	return m_length;
}

template<typename T>
inline void DynamicArray<T>::Resize(int newSize)
{
	T* newArray = new T[newSize];
	for (int i = 0; i < m_length && i < newSize; i++)
	{
		newArray[i] = m_array[i];
	}
	delete[] m_array;
	m_array = newArray;
	m_length = newSize;
}


template<typename T>
inline T* DynamicArray<T>::begin()
{
	return m_array;
}

template<typename T>
inline const T* DynamicArray<T>::begin() const
{
	return m_array;
}

template<typename T>
inline T* DynamicArray<T>::end()
{
	return m_array + m_length;
}

template<typename T>
inline const T* DynamicArray<T>::end() const
{
	return m_array + m_length;
}

template<typename T>
inline void DynamicArray<T>::Add(const T& value)
{
	Resize(m_length + 1);
	m_array[m_length - 1] = value;
}

template<typename T>
inline void DynamicArray<T>::Add(const T* array, int size)
{
	int oldLength = m_length;
	Resize(m_length + size);
	for (int i = 0; i < size; i++)
	{
		m_array[oldLength + i] = array[i];
	}
}

template<typename T>
inline void DynamicArray<T>::Add(const DynamicArray<T>& other)
{
	int oldLength = m_length;
	Resize(m_length + other.m_length);
	for (int i = 0; i < other.m_length; i++)
	{
		m_array[oldLength + i] = other.m_array[i];
	}
}

template<typename T>
inline void DynamicArray<T>::AddUnique(const T& value)
{
	for (int i = 0; i < m_length; i++)
	{
		if (m_array[i] = value)
			return;
	}
	Add(value);
}

template<typename T>
inline void DynamicArray<T>::Insert(int index, const T& value)
{
	Resize(m_length + 1);
	for (int i = m_length - 1; i > index; i--)
	{
		m_array[i] = m_array[i - 1];
	}
	m_array[index] = value;
}

template<typename T>
inline void DynamicArray<T>::Insert(int index, const T* array, int size)
{
	Resize(m_length + size);
	for (int i = m_length - 1; i >= index + size; i--)
	{
		m_array[i] = m_array[i - size];
	}
	for (int i = 0; i < size; i++)
	{
		m_array[index + i] = array[i];
	}
}

template<typename T>
inline void DynamicArray<T>::Insert(int index, const DynamicArray<T>& other)
{
	Resize(m_length + other.m_length);
	for (int i = m_length - 1; i >= index + other.m_length; i--)
	{
		m_array[i] = m_array[i - other.m_length];
	}
	for (int i = 0; i < other.m_length; i++)
	{
		m_array[index + i] = other.m_array[i];
	}
}

template<typename T>
inline void DynamicArray<T>::RemoveIndex(int index)
{
	for (int i = index; i < m_length - 1; i++)
	{
		m_array[i] = m_array[i + 1];
	}
	Resize(m_length - 1);
}

template<typename T>
inline bool DynamicArray<T>::Remove(const T& value)
{
	for (int i = 0; i < m_length; i++)
	{
		if (m_array[i] == value)
		{
			RemoveIndex(i);
			return true;
		}
	}
	return false;
}

template<typename T>
inline bool DynamicArray<T>::Remove(const T* array, int size)
{
	int removedCount = 0;
	for (int i = 0; i < size; i++)
	{
		if (Remove(array[i]))
			removedCount++;
	}
	return removedCount == size;
}

template<typename T>
inline bool DynamicArray<T>::Remove(const DynamicArray<T>& other)
{
	int removedCount = 0;
	for (int i = 0; i < other.m_length; i++)
	{
		if (Remove(other.m_array[i]))
			removedCount++;
	}
	return removedCount == other.Length();
}

template<typename T>
inline void DynamicArray<T>::Clear()
{
	Resize(0);
}
