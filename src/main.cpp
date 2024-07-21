#include "includes.h"
using main_t = unsigned(__stdcall*)(void*);

std::uint32_t __stdcall main( HINSTANCE module ) 
{
	IO_START;

	std::uintptr_t base = memory::get_module( L"ac_client.exe" );
	sdk::initalize_globals( );

	auto local_player = *reinterpret_cast< sdk::playerent** >( base + 0x17E0A8 );
	
	std::cout << "ac_client.exe: 0x" << std::hex << base << '\n';
	memory::hook_vfunc( local_player, 1, main );

	while ( !GetAsyncKeyState( VK_END ) & 1 ) {


		if ( !local_player || local_player->state.health <= 0 )
			continue;

		if ( !sdk::entity_list )
			sdk::initalize_globals( );

		decimal_t closest_distance = FLT_MAX;
		sdk::playerent* closest_player{  };
		for ( int i = 0; i < *sdk::player_count - 1; ++i ) {
			const auto target = sdk::entity_list->get_entity< sdk::playerent >( i );
			if ( !target || target == local_player || target->state.health <= 0 || target->team == local_player->team )
				continue;

			const decimal_t distance = local_player->body.distance( target->body );
			if ( distance < closest_distance ) {
				closest_distance = distance;
				closest_player = target;
			}
		}

		if ( !closest_player || !closest_player->name )
			continue;

		local_player->aim_at( closest_player );
	}

	

	IO_END( module );
}



bool __stdcall DllMain( HMODULE mod, std::uint32_t reason, void* reserved ) 
{
	if (reason == DLL_PROCESS_ATTACH) {
		CloseHandle( CreateThread(
			0,
			0,
			reinterpret_cast< LPTHREAD_START_ROUTINE >( main ),
			mod,
			0,
			nullptr
		) );
	}

	return TRUE;
}
