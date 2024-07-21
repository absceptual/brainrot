#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "internals.h"

namespace memory {



	std::uintptr_t get_module( const std::wstring_view module_name );
	const PEB* get_peb( );
	void hook_vfunc( void* object, int index, void* replacement );

	template <typename T, typename ...Args>
	T call_vfunc( void* object, int index, Args... args ) {
		using function_t = T( __thiscall )( void* object, Args... arguments );
		function_t function = reinterpret_cast< function_t >( *static_cast< std::uintptr_t* >( object ) + ( sizeof( std::uintptr_t ) * index ) );

		return function( object, args );
	}

	

	template <typename T>
	T* read_chain( void* address, std::vector< std::size_t > offsets ) {

		std::uintptr_t pointer = address;
		for ( const std::size_t offset : offsets ) {
			pointer += offset;
			pointer = *reinterpret_cast< std::uintptr_t* >( pointer );
		}

		return static_cast< T* >( pointer );
	}

	template <typename T>
	void write_chain( void* address, const T& data, std::vector< std::size_t > offsets ) {
		std::uintptr_t pointer = address;
		for ( const std::size_t offset : offsets ) {
			pointer += offset;
			pointer = *reinterpret_cast< std::uintptr_t* >( pointer );
		}
		
		memcpy_s( pointer, sizeof( T ), &data, sizeof( T ) );
	}
}