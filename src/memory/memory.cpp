#include "memory.hpp"

const PEB* memory::get_peb( ) {
#ifdef _WIN64
	return reinterpret_cast<  const PEB* >( __readgsqword( 0x60 ) );
#else
	return reinterpret_cast< const PEB* >( __readfsdword( 0x30 ) );
#endif
}

void memory::hook_vfunc( void* object, int index, void* replacement )
{
	void* address = reinterpret_cast< void* >( *static_cast< std::uintptr_t* >( object ) + ( sizeof( std::uintptr_t ) * index ) );

	DWORD old_protection{ };
	VirtualProtect( address, sizeof( std::uintptr_t ), PAGE_EXECUTE_READWRITE, &old_protection );
	memcpy_s( address, sizeof( std::uintptr_t ), &replacement, sizeof( std::uintptr_t ) );
}

std::uintptr_t memory::get_module( const std::wstring_view module_name ) {
	const PEB* peb = memory::get_peb( );

	LIST_ENTRY* module_list = &(peb->Ldr->InMemoryOrderModuleList);
	for ( LIST_ENTRY* module_entry = module_list->Flink; module_entry != module_list; module_entry = module_entry->Flink ) {
		const auto module_information = reinterpret_cast< _LDR_DATA_TABLE_ENTRY* >(
			CONTAINING_RECORD( module_entry, _LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks )
		);


		if ( module_name.compare( module_information->BaseDllName.Buffer ) == 0 )
			return reinterpret_cast< std::uintptr_t >( module_information->DllBase );
	}
	return 0x0;
}