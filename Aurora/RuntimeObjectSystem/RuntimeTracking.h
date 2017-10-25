//
// Copyright (c) 2017 Doug Binks
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once


// Source Dependencies are constructed from a macro template from sources which may include
// the __FILE__ macro, so to reduce inter-dependencies we return three values which are combined
// by the higher level code. The full source dependency filename is then pseudo-code:
// RemoveAnyFileName( relativeToPath ) + ReplaceExtension( filename, extension  )
struct SourceDependencyInfo
{
	const char* filename;			// If NULL then no SourceDependencyInfo
	const char* extension;			// If NULL then use extension in filename
	const char* relativeToPath;		// If NULL filename is either full or relative to known path
};

struct RuntimeTackingInfo
{
    static RuntimeTackingInfo GetNULL() { RuntimeTackingInfo ret = {0}; return ret; }
	SourceDependencyInfo sourceDependencyInfo;
	const char*          linkLibrary;
	const char*          includeFile;
};


#ifndef RCCPPOFF

struct IRuntimeTracking
{
	IRuntimeTracking( size_t max ) : MaxNum( max )
	{
	}

	// GetIncludeFile may return 0, so you should iterate through to GetMaxNum() ignoring 0 returns
	virtual RuntimeTackingInfo GetTrackingInfo( size_t Num_ ) const
	{
		return RuntimeTackingInfo::GetNULL();
	}

	size_t MaxNum; // initialized in constructor below
};


namespace
{
const size_t COUNTER_OFFSET = __COUNTER__;

template< size_t COUNT > struct RuntimeTracking : RuntimeTracking<COUNT-1>
{
	RuntimeTracking( size_t max ) : RuntimeTracking<COUNT-1>( max )
	{
	}
	RuntimeTracking() : RuntimeTracking<COUNT-1>( COUNT )
	{
	}
};

template<> struct RuntimeTracking<0> : IRuntimeTracking
{
	RuntimeTracking( size_t max ) : IRuntimeTracking( max )
	{
	}
	RuntimeTracking() : IRuntimeTracking( 0 )
	{
	}
};

}

#endif