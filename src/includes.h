#pragma once
#define IO_START \
	AllocConsole( ); \
	FILE* output{ nullptr }; \
	freopen_s( &output, "CONOUT$", "w", stdout );

#define IO_END( mod ) \
	if ( output ) { fclose( output ); }; \
	FreeConsole( ); \
	if ( mod != 0 ) { FreeLibraryAndExitThread( mod, 0 ); }

#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <thread>

#include "memory/memory.hpp"

#include "sdk/playerent.h"
#include "sdk/globals.h"

