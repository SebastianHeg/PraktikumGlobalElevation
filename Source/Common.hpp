#ifndef COMMON_HPP
#define COMMON_HPP

typedef std::string String;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;

template <class T> using List = std::list<T>;
template <class T> using Vector = std::vector<T>;
template <class Key, class Value> using Map = std::map<Key, Value>;
template <class First, class Second> using Pair = std::pair<First, Second>;

#define IMAGE_SIZE_G 3600
#define IMAGE_SIZE_S 1800

#define PATH "..\\..\\Include\\Resources\\Test\\";

//#define WINDOWS defined _WIN32 || defined WIN32 || defined _WIN64 || defined WIN64
//#define LINUX defined unix || defined __unix || defined __unix__ || defined __linux__
//#define MACOS defined __APPLE__ || defined __MACH__

//#if WINDOWS
//	#pragma message("On Windows")
//	#define RESOURCEPATH "..\\..\\Include\\Resources\\Test\\"
//#elif LINUX
//	#pragma message("On Linux")
//	#define RESOURCEPATH "../../Include/Resources/Test/"
//#elif MACOS
//	#pragma message("On MAC OS")*/
//#else
//	#error Unknown platform*/
//#endif

#endif
