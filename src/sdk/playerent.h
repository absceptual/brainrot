#pragma once
#include <bitset>
#include "math.h"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

namespace sdk {
    class playerstate;

    enum weapon_type {
        GUN_KNIFE = 0,
        GUN_PISTOL,
        GUN_CARBINE,
        GUN_SHOTGUN,
        GUN_SUBGUN,
        GUN_SNIPER,
        GUN_ASSAULT,
        GUN_GRENADE,
        GUN_AKIMBO,
        NUMGUNS
    };

    enum player_flags {
        in_water = 0,
        on_floor,
        on_ladder,
        jump_next,
        jump_d,
        crouching,
        crouched_in_air,
        trycrouch,
        cancollide,
        stuck,
        scoping,

        MAX_FLAGS
    };

    class playerstate
    {
    public:
        int health, armour;
        int primary, nextprimary;
        int gunselect;
        bool akimbo;
        int ammo[ NUMGUNS ], mag[ NUMGUNS ], gunwait[ NUMGUNS ];
        int pstatshots[ NUMGUNS ], pstatdamage[ NUMGUNS ];
    };

    class playerent {
    public:
        const static std::size_t MAX_NAME_LENGTH{ 16 };
        using position_t = std::size_t;


    public:
        // void** vtable;
        union {
            DEFINE_MEMBER_N( math::vector3, head_position, 0x4 );
            DEFINE_MEMBER_N( math::vector3, velocity, 0x10 );
            DEFINE_MEMBER_N( math::vector3, body, 0x28 );
            DEFINE_MEMBER_N( math::vector3, viewangles, 0x34 );
            DEFINE_MEMBER_N( decimal_t, maxspeed, 0x44 );
            DEFINE_MEMBER_N( decimal_t, radius, 0x4c );
            DEFINE_MEMBER_N( decimal_t, eyeheight, 0x50 );
            DEFINE_MEMBER_N( decimal_t, maxeyeheight, 0x54 );
            DEFINE_MEMBER_N( decimal_t, aboveeye, 0x58 );
            DEFINE_MEMBER_N( playerstate, state, 0xEC );
            DEFINE_MEMBER_N( std::bitset<11>, flags, 0x5C );
            DEFINE_MEMBER_N( bool, attacking, 0x204 );
            DEFINE_MEMBER_N( char, name[ playerent::MAX_NAME_LENGTH ], 0x205 );
            DEFINE_MEMBER_N( int, team, 0x30C );
        };

    public:
        bool get_flag( sdk::player_flags flag_type ) {
            return flags.test( flag_type );
        }

        void set_flag( sdk::player_flags flag_type, bool value ) {
            flags.set( flag_type, value );
        }

        void aim_at( const playerent* target ) {
            math::vector3 delta = target->head_position - this->head_position;

            const decimal_t magnitude = static_cast< decimal_t >( std::sqrt( delta.x * delta.x + delta.y * delta.y ) );
            decimal_t yaw = math::to_degrees( atan2f( delta.y, delta.x ) );
            decimal_t pitch = math::to_degrees( atan2f( delta.z, magnitude ) );

          
            math::vector3 new_angles{ yaw + 90, pitch, 0 };
            if ( new_angles.x < 0 )
                new_angles.x += 360;
            else if ( new_angles.x > 360 )
                new_angles.x -= 360;

            if ( new_angles.y > 90 )
                new_angles.y -= 180;
            else if ( new_angles.y < -90 )
                new_angles.y += 180;
            
            //std::cout << this->viewangles << '\n';
            //std::cout << new_angles << '\n';
            this->viewangles = new_angles;

        }
    };

    class entitylist {
    public:
        template <typename T>
        T* get_entity( int index ) {
            if ( index > 31 )
                return nullptr;

            std::uintptr_t* address = ( std::uintptr_t* )( reinterpret_cast< std::uintptr_t >( this ) + 4 + ( index * 4 ) );
            if ( !address )
                return nullptr;

            return *reinterpret_cast< T** >( address );
        }
    };
}






