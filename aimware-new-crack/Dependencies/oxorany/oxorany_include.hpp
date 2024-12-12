#ifndef OXORANY_INCLUDE_H
#define OXORANY_INCLUDE_H

#define OXORANY_USE_BIT_CAST
#define OXORANY_DISABLE_OBFUSCATION

#include "oxorany.hpp"

// To change Marco in an easy way
#if defined(_DEBUG)

#define _(x) (x)
#define _FLT(x) (x)

#else

#if defined(PRODUCTION_BUILD)

#define _( x ) oxorany( x )
#define _FLT( x ) oxorany_flt( x )

#else

#define _( x ) ( x )
#define _FLT( x ) ( x )

#endif

#undef OXORANY_DISABLE_OBFUSCATION
#endif

#define VARIABLE_OBFUSCATED_MEMBER(var, member) *(decltype(decltype(var)::member)*)(int64_t(&var) + _(offsetof(decltype(var), member)))

template <typename T>
static OXORANY_FORCEINLINE void copy_string_without_return(T* target, const T* source)
{
	while (*source) {
		*target = *source;
		++source;
		++target;
	}
	*target = 0;
}

#define XOR_DEFINE_STRING_ARRAY(type,name,s) type name[sizeof(s)/sizeof(type)]; copy_string_without_return(name, WRAPPER_MARCO(s))

#endif