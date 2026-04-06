//
//  utils.h
#pragma once

#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

namespace utils {

// --- random ---
inline void srand0()
{
    srand(static_cast<unsigned>(time(nullptr)));
}

inline int GetRandomInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}


// --- fill ---
inline void Initialize(int* begin, int* end, int min, int max)
{
    for (int* i = begin; i < end; i++)
        *i = GetRandomInt(min, max);
}

inline void Initialize(int** arr, int rows, int columns, int min, int max)
{
    for (int** i = arr; i < arr + rows; i++)
    {
        int* begin = *i, *end = *i + columns;
        Initialize(begin, end, min, max);
    }
}

inline void Initialize(double* begin, double* end, int min, int max)
{
    for (double* i = begin; i < end; i++)
        *i = GetRandomInt(min, max) + (rand() % 1000) / 10000.0;
}

inline void Initialize(int* begin, int* end)
{
    *begin = 0;
    *(begin + 1) = 1;
    
    for (int* i = (begin + 2); i < end; i++)
        *i = *(i - 1) + *(i - 2);
}

inline void Initialize(char* begin, char* end)
{
    for (char* i = begin; i < end; i++)
        *i = GetRandomInt('A', 'z');
}


// --- string ---
inline void To_lower(char* begin, char* end)
{
    for (char* i = begin; i != end; i++)
        if ('A' <= *i && *i <= 'Z')
            *i += 32;
}


// --- sorting ---
template <typename T>
void Reverse(T* begin, T* end)
{
    for (T* j = end - 1, *i = begin; i < j; i++, j--)
        std::swap(*i, *j);
}

inline void Reverse(char* str)
{
    char* end = str;
    while (*end != '\0')
        end++;
    Reverse(str, end);
}

template <typename T>
void QuickSort(T* begin, T* end)
{
    T* i = begin, *j = end - 1;
    T middle = *(begin + (end - begin) / 2);
    
    do
    {
        while (*i < middle)
            i++;
        while (*j > middle)
            j--;
        
        if (i <= j)
        {
            std::swap(*i, *j);
            i++;
            j--;
        }
    } while (i <= j);
    
    if (i < end - 1)
        QuickSort(i, end);
    if (j > begin)
        QuickSort(begin, j + 1);
}

inline void QuickSort(const char **begin, const char **end)
{
    const char **i = begin;
    const char **j = end - 1;
    const char *middle = *(begin + (end - begin) / 2);
    
    do
    {
        while (strcmp(*i, middle) < 0)
            i++;
        while (strcmp(*j, middle) > 0)
            j--;
        
        if (i <= j)
        {
            std::swap(*i, *j);
            i++;
            j--;
        }
    } while (i <= j);
    
    if (i < end - 1)
        QuickSort(i, end);
    if (j > begin)
        QuickSort(begin, j + 1);
}

template <typename T>
void InsertionSort(T* begin, T* end, bool IsAscendingOrder = true)
{
    for (T* i = begin + 1; i < end; i++)
    {
        T key = *i, *j;
        for (j = i - 1; j >= begin && (IsAscendingOrder ? (key < *j) : (key > *j)); j--)
            *(j + 1) = *j;
        *(j + 1) = key;
    }
}

template <typename T>
void BubbleSort(T* begin, T* end, bool isAscendingOrder = true)
{
    for (T* j = begin; j < end; j++)
    {
        bool wasSwaped = false;
        for (T* i = begin; i < (end - 1) - (j - begin); i++)
            if (isAscendingOrder ? (*i > *(i + 1)) : (*i < *(i + 1)))
            {
                std::swap(*i, *(i + 1));
                wasSwaped = true;
            }
        if (!wasSwaped)
            break;
    }
}

template <typename T>
void SelectionSort(T* begin, T* end, bool isAscendingOrder = true)
{
    for (T* j = begin; j < end - 1; j++)
        for (T* i = j + 1; i < end; i++)
            if (isAscendingOrder ? (*i < *j) : (*i > *j))
                std::swap(*i, *j);
}


// --- search ---
template <typename T>
const T* BinarySearch(const T* begin, const T* end, T key)
{
    const T* leftBound = begin, *rightBound = end - 1;
    
    do
    {
        const T* middle = leftBound + (rightBound - leftBound) / 2;
        
        if (key > *middle)
            leftBound = middle + 1;
        else if (key < *middle)
            rightBound = middle - 1;
        else
            return middle;
    } while (leftBound <= rightBound);
    
    return nullptr;
}

template <typename T>
const T* LinearSearch(const T* begin, const T* end, const T value)
{
    for (const T* i = begin; i < end; i++)
        if (*i == value)
            return i;
    return nullptr;
}

template <typename T>
bool Compare(const T* begin1, const T* end1, const T* begin2, const T* end2)
{
    if ((end1 - begin1) != (end2 - begin2))
        return false;
    
    for (const T* i = begin1, *j = begin2; i < end1; i++, j++)
        if (*i != *j)
            return false;
    return true;
}

template <typename T>
const T* Find(const T* begin, const T* end, const T* sBegin, const T* sEnd)
{
    size_t needleLen = sEnd - sBegin;
    
    for(const T* i = begin; i <= end - needleLen; i++)
        if (Compare(i, i + needleLen, sBegin, sEnd))
            return i;
    return nullptr;
}

inline const char* Find(const char* sentences, const char* word)
{
    const char* end = sentences;
    while(*end != '\0')
        end++;
    const char* sEnd = word;
    while(*sEnd != '\0')
        sEnd++;
    return Find(sentences, end, word, sEnd);
}


// --- info ---
template <typename T>
T Sum(const T* begin, const T* end)
{
    T sum = 0;
    for (const T* i = begin; i < end; i++)
        sum += *i;
    return sum;
}

template <typename T>
size_t Count(const T* begin, const T* end, const T value)
{
    size_t counter = 0;
    const T* foundAddress = LinearSearch(begin, end, value);
    
    while (foundAddress != nullptr)
    {
        begin = foundAddress + 1;
        foundAddress = LinearSearch(begin, end, value);
        counter++;
    }
    return counter;
}

inline size_t Count(const char* str, char value)
{
    const char* end = str;
    while (*end != '\0')
        end++;
    return Count(str, end, value);
}

template <typename T>
bool IsSorted(const T* begin, const T* end, bool isAscendingOrder = true)
{
    for (const T* i = begin; i < end - 1; i++)
        if (isAscendingOrder ? (*i > *(i + 1)) : (*i < *(i + 1)))
            return false;
    return true;
}

template <typename T>
bool IsPalindrome(const T* begin, const T* end)
{
    for (const T* i = begin, *j = end - 1; i < j; i++, j--)
        if (*i != *j)
            return false;
    return true;
}


// --- dynamic memory ---
template <typename T>
T* Concat(const T* begin1, const T* end1, const T* begin2, const T* end2, size_t* outSize = nullptr)
{
    size_t size = (end1 - begin1) + (end2 - begin2);
    
    if (outSize != nullptr)
        *outSize = size;
    
    T* result = new T[size];
    T* ptr = result;
    
    for (const T* i = begin1; i < end1; i++, ptr++)
        *ptr = *i;
    for (const T* i = begin2; i < end2; i++, ptr++)
        *ptr = *i;
    
    return result;
}

inline char* Concat(const char* str1,const char* str2)
{
    const char* end1 = str1;
    while (*end1 != '\0')
        end1++;
    
    const char* end2 = str2;
    while (*end2 != '\0')
        end2++;
    
    return Concat(str1, end1, str2, end2 + 1);
}

template <typename T>
T* Copy(const T* begin, const T* end, size_t* outSize = nullptr)
{
    size_t size = (end - begin);
    
    if(outSize != nullptr)
        *outSize = size;
    
    T* result = new T[size];
    T* ptr = result;
    
    for (const T* i = begin; i < end; i++, ptr++)
        *ptr = *i;
    
    return result;
}

inline char* EnterString()
{
    static const size_t size = 256;
    static char str[size];
    
    std::cin.getline(str, size);
    
    const char* end = str;
    while (*end != '\0')
        end++;
    
    return Copy(str, end + 1);
}

template <typename T>
T* AddElement(T* begin, T* end, T value)
{
    size_t size = end - begin;
    T* temp = new T[size + 1];
    
    if (size != 0)
        for(T* i = begin,* j = temp; i < end; i++, j++)
            *j = *i;
    
    *(temp + size) = value;
    
    return temp;
}

template <typename T>
T* RemoveElement(T* begin, T* end, T* target)
{
    if (begin == end)
        return nullptr;
    
    size_t size = end - begin;
    T* temp = new T[size - 1];
    T* j = temp;
    
    
    for (T* i = begin; i < target; j++, i++)
        *j = *i;
    for (T* i = target + 1; i < end; j++, i++)
        *j = *i;
    
    return temp;
}


// --- purge ---
template <typename T>
T* Remove(T* begin, T* end, T value)
{
    T* ptrWriter = begin;
    
    for(T* i = begin; i < end; i++)
        if (*i != value)
        {
            *ptrWriter = *i;
            ptrWriter++;
        }
    return ptrWriter;
}

inline void Remove(char* str, char value)
{
    char* end = str;
    while (*end != '\0')
        end++;
    
    char* newEnd = Remove(str, end, value);
    *newEnd = '\0';
}


// --- show ---
template <typename T>
void Show(const T* begin, const T* end)
{
    for (const T* i = begin; i < end; i++)
        std::cout << *i << ' ';
}

template <typename T>
void Show(const T* const* arr, size_t rows, size_t columns)
{
    for (const T* const* i = arr; i < arr + rows; i++)
    {
        const T* begin = *i, *end = *i + columns;
        Show(begin, end);
        std::cout << '\n';
    }
}

template <typename T, size_t N>
void Show(const T (&arr)[N])
{
    for (const T* i = arr; i < arr + N; i++)
        std::cout << *i << ' ';
}

template <typename T, size_t N, size_t M>
void Show(const T (&arr)[M][N])
{
    for (const T (*i)[N] = arr; i < arr + M; i++)
    {
        Show(*i);
        std::cout << '\n';
    }
}

template <typename T>
void ShowUnique(const T* begin, const T* end)
{
    for (const T* i = begin; i < end; i++)
        if (i == begin || *i != *(i - 1))
            std::cout << *i << ' ';
}

template <typename T>
void ShowSingles(const T* begin, const T* end)
{
    for (const T* i = begin; i < end; i++)
    {
        bool IfFirst = (i == begin || *i != *(i - 1));
        bool IfLast = (i == end - 1 || *i != *(i + 1));
        if (IfFirst && IfLast)
            std::cout << *i << ' ';
    }
}


// --- input ---
inline int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
}

