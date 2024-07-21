#pragma once

#include "../memory/memory.hpp"
#include "playerent.h"

namespace sdk {
	inline int* player_count;
	inline sdk::entitylist* entity_list;

	void initalize_globals( ) {
		const auto base = memory::get_module( L"ac_client.exe" );

		sdk::player_count = reinterpret_cast< int* >( base + 0x18AC0C );
		sdk::entity_list = *reinterpret_cast< sdk::entitylist** >( base + 0x18AC04 );
	}
}