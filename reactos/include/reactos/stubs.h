#include <stdarg.h>
#include <windef.h>
#include <winbase.h>

#include <wine/config.h>
#include <wine/exception.h>

ULONG __cdecl DbgPrint(_In_z_ _Printf_format_string_ PCSTR Format, ...);

#define __wine_spec_unimplemented_stub(module, function) \
{ \
    ULONG_PTR args[2]; \
    args[0] = (ULONG_PTR)module; \
    args[1] = (ULONG_PTR)function; \
    RaiseException( EXCEPTION_WINE_STUB, EH_NONCONTINUABLE, 2, args ); \
}
