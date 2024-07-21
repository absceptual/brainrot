#pragma once

#include <cmath>
#include <numbers>
#include <iostream>

#ifdef _WIN64
using decimal_t = decimal_t;
#else
using decimal_t = float;
#endif

namespace math {

    inline decimal_t to_degrees( const decimal_t radians ) {
        return radians * 180 / std::numbers::pi_v< decimal_t >;
    }

    inline decimal_t to_radians( const decimal_t degrees ) {
        return degrees * std::numbers::pi_v< decimal_t > * 2;
    }

    class vector3
    {
    public:
        decimal_t x, y, z;

    public:
        vector3( ) : x( ), y( ), z( ) { }
        vector3( decimal_t x, decimal_t y, decimal_t z ) : x( x ), y( y ), z( z ) { }

        vector3 operator + ( const vector3& other ) const { return { this->x + other.x, this->y + other.y, this->z + other.z }; }
        vector3 operator - ( const vector3& other ) const { return { this->x - other.x, this->y - other.y, this->z - other.z }; }
        vector3 operator * ( decimal_t offset ) const { return { this->x * offset, this->y * offset, this->z * offset }; }
        vector3 operator / ( decimal_t offset ) const { return { this->x / offset, this->y / offset, this->z / offset }; }

        vector3& operator *= ( const decimal_t other ) { this->x *= other; this->y *= other; this->z *= other; return *this; }
        vector3& operator /= ( const decimal_t other ) { this->x /= other; this->y /= other; this->z /= other; return *this; }

        vector3& operator = ( const vector3& other ) { this->x = other.x; this->y = other.y; this->z = other.z; return *this; }
        vector3& operator += ( const vector3& other ) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
        vector3& operator -= ( const vector3& other ) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
        vector3& operator *= ( const vector3& other ) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
        vector3& operator /= ( const vector3& other ) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }

        operator bool( ) { return bool( this->x || this->y || this->z ); }
        friend bool operator == ( const vector3& a, const vector3& b ) { return a.x == b.x && a.y == b.y && a.z == b.z; }
        friend bool operator != ( const vector3& a, const vector3& b ) { return !( a == b ); }

        friend std::ostream& operator<<( std::ostream& out, const vector3& vec ) { return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")"; }
        decimal_t dot( const vector3& V ) { return x * V.x + y * V.y + z * V.z; }
        decimal_t sizesquared( ) { return x * x + y * y + z * z; }

        void normalize( )
        {
            while ( this->x > 180.0f )
            {
                this->x -= 360.0f;
            }
            while ( this->x < -180.0f )
            {
                this->x += 360.0f;
            }
            while ( this->y > 180.0f )
            {
                this->y -= 360.0f;
            }
            while ( this->y < -180.0f )
            {
                this->y += 360.0f;
            }

            this->z = 0;
        }

        void clamp( float min, float max )
        {
            if ( this->x < min )
            {
                this->x = min;
            }
            else if ( this->x > max )
            {
                this->x = max;
            }

            if ( this->y < min )
            {
                this->y = min;
            }
            else if ( this->y > max )
            {
                this->y = max;
            }

            this->z = 0;
        }

        decimal_t magnitude( ) const {
            return static_cast< decimal_t >( std::sqrt( std::pow( x, 2 ) + std::pow( y, 2 ) + std::pow( z, 2 ) ) );
        }

        decimal_t distance( const vector3& other ) const {
            return ( *this - other ).magnitude( );
        }
    };

    class vector2
    {
    public:
        decimal_t x, y;

    public:
        vector2( ) : x( ), y( ) { }
        vector2( decimal_t x, decimal_t y ) : x( x ), y( y ) { }

        vector2 operator + ( const vector2& other ) const { return { this->x + other.x, this->y + other.y }; }
        vector2 operator - ( const vector2& other ) const { return { this->x - other.x, this->y - other.y }; }
        vector2 operator * ( decimal_t offset ) const { return { this->x * offset, this->y * offset }; }
        vector2 operator / ( decimal_t offset ) const { return { this->x / offset, this->y / offset }; }

        vector2& operator *= ( const decimal_t other ) { this->x *= other; this->y *= other; return *this; }
        vector2& operator /= ( const decimal_t other ) { this->x /= other; this->y /= other; return *this; }

        vector2& operator = ( const vector2& other ) { this->x = other.x; this->y = other.y; return *this; }
        vector2& operator += ( const vector2& other ) { this->x += other.x; this->y += other.y; return *this; }
        vector2& operator -= ( const vector2& other ) { this->x -= other.x; this->y -= other.y; return *this; }
        vector2& operator *= ( const vector2& other ) { this->x *= other.x; this->y *= other.y; return *this; }
        vector2& operator /= ( const vector2& other ) { this->x /= other.x; this->y /= other.y; return *this; }

        operator bool( ) { return bool( this->x || this->y ); }
        friend bool operator == ( const vector2& A, const vector2& B ) { return A.x == B.x && A.y == A.y; }
        friend bool operator != ( const vector2& A, const vector2& B ) { return !( A == B ); }
        friend std::ostream& operator<<( std::ostream& out, const vector2& vec ) { return out << "(" << vec.x << ", " << vec.y << ")"; }


    };

}


