/*
    ParaGUI - crossplatform widgetset
    Copyright (C) 2000,2001,2002  Alexander Pipelka

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Alexander Pipelka
    pipelka@teleweb.at

    Last Update:      $Author: braindead $
    Update Date:      $Date: 2003/03/30 16:30:57 $
    Source File:      $Source: /sources/paragui/paragui/include/paraconfig.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.14 $
    Status:           $State: Exp $
*/

#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

#undef PACKAGE
#undef VERSION

#define PG_VERSIONNUM(X, Y, Z) ((X)*10000 + (Y)*100 + (Z))

#if (defined(WIN32) || defined(__WIN32__)) && (defined(__MINGW32__) || defined(_MSC_VER) || defined(__BCPLUSPLUS__) || defined(__MWERKS__))
#include "paraconfig_win32.h"
#elif defined(__MACOS__) 
#include "paraconfig_macos.h"
#else // GNU
#include "paraconfig_gnu.h"
#endif // GNU

// STL map / hash_map

#if defined(HAVE_HASH_MAP)
#define HASH_MAP_INC <hash_map>
#define MAP_INC <hash_map>
#define STL_MAP hash_map
#elif defined(HAVE_EXT_HASH_MAP)
#define HASH_MAP_INC <ext/hash_map>
#define MAP_INC <ext/hash_map>
#if PG_VERSIONNUM(__GNUC__, __GNUC_MINOR__, 0) >= PG_VERSIONNUM(3, 1, 0)
#define STL_MAP __gnu_cxx::hash_map
#else
#define STL_MAP hash_map
#endif
#else
#define MAP_INC <map>
#define STL_MAP map
#endif


//
// Modelled after g++ stdc++ v3
//
#if defined(EXCEPTIONS_ENABLED) || defined(__EXCEPTIONS)
#define PG_TRY try
#define PG_CATCH_ALL catch(...)
#define PG_THROW(_ex_) throw _ex_
#define PG_RETHROW throw
#define PG_NOTHROW throw()
#define PG_UNWIND(action) catch(...) {action; throw;}
#define PG_CATCH(_ex_, _name_) catch(_ex_& _name_)
#else
#define PG_TRY
#define PG_CATCH_ALL if (false)
#define PG_THROW(_ex_)
#define PG_RETHROW
#define PG_NOTHROW
#define PG_UNWIND
#define PG_CATCH(_ex_, _name_) if (false)
#endif

//
// Replacement for strdup
//
#ifndef HAVE_STRDUP
extern "C" {
char* strdup(const char* s);
}
#endif

// Replacement for fnmatch
#ifndef HAVE_FNMATCH
extern "C" {
/* Bits set in the FLAGS argument to `fnmatch'.  */
#define	FNM_PATHNAME	(1 << 0) /* No wildcard can ever match `/'.  */
#define	FNM_NOESCAPE	(1 << 1) /* Backslashes don't quote special chars.  */
#define	FNM_PERIOD	(1 << 2) /* Leading `.' is matched only explicitly.  */
#define	__FNM_FLAGS	(FNM_PATHNAME|FNM_NOESCAPE|FNM_PERIOD)

/* Value returned by `fnmatch' if STRING does not match PATTERN.  */
#define	FNM_NOMATCH	1

int fnmatch(const char *, const char *, int);
}
#else
#include <fnmatch.h>
#endif

#endif // CONFIG_INCLUDED

