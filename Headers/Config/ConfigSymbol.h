#pragma once
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#ifdef _WIN32
#ifdef CONFIG_EXPORT

#define CONFIG_API __declspec(dllexport)
#define CONFIG_EXPIMP_TEMPLATE

#elif defined(CONFIG_IMPORT)

#define CONFIG_API __declspec(dllimport)
#define CONFIG_EXPIMP_TEMPLATE extern

#else

#define CONFIG_EXPIMP_TEMPLATE
#define CONFIG_API

#endif
#else

#define CONFIG_EXPIMP_TEMPLATE
#define CONFIG_API

#endif
