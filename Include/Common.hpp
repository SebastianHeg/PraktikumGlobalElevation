#pragma once

typedef std::string String;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;

template <class T> using List = std::list<T>;
template <class T> using Vector = std::vector<T>;
template <class Key, class Value> using Map = std::map<Key, Value>;
template <class First, class Second> using Pair = std::pair<First, Second>;

#define RESOURCEPATH "..\\..\\Include\\Resources\\Test\\"