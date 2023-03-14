#include "Functions.h"

int ix;
DWORD EntityObjStart = 0x0;
DWORD EntlistJmpBack = 0x0;
DWORD PlayerJmpBack = 0x0;
bool alreadyThere = false;

// Created with ReClass.NET 1.2 by KN4CK3R

class localplayer;
class wcoordsclass1;

class localplayer
{
public:
    char pad_0x0000[0x354]; //0x0000
    wcoordsclass1* wcoordsptr1; //0x0354 
    char pad_0x0358[0x7D8]; //0x0358
    vec3 coords; //0x0B30 
    char pad_0x0B3C[0x104]; //0x0B3C

}; //Size=0x0C40
localplayer* LP;

class wcoordsclass1
{
public:
    char pad_0x0000[0x3CC]; //0x0000
    vec3 wcoords; //0x03CC 
    char pad_0x03D8[0x2C]; //0x03D8

}; //Size=0x0404


class rdmmob
{
public:
    char pad_0000[132]; //0x0000
    vec3 coords; //0x0084
    char pad_0090[952]; //0x0090
}; //Size: 0x0448
static_assert(sizeof(rdmmob) == 0x448, ".");

rdmmob* ents[255];
rdmmob* entsptr;

//ab hier 2ter hook
// Created with ReClass.NET 1.2 by KN4CK3R

class player
{
public:
    char pad_0000[132]; //0x0000
    vec3 coords2; //0x0084
    char pad_0090[184]; //0x0090
}; //Size: 0x0148
static_assert(sizeof(player) == 0x148, ".");

player* ents2[255];
player* ents2ptr;

__declspec(naked) void playerhook()
{
    __asm {
        mov[ecx + 0xB38], eax
        mov [LP], ecx
        pushad
    }
    __asm {
        popad
        jmp[PlayerJmpBack]
    }
}

__declspec(naked) void entityhook()
{
    __asm {
        mov edx, [esi + 0x34]
        mov eax, [esi + 0x38]
        mov EntityObjStart, esi
        pushad
    }

    __asm {
        mov eax, EntityObjStart
        mov[entsptr], eax
    }

    if (entsptr == nullptr)
    {
        goto GIVE_UP;
    }

    alreadyThere = false;

    for (ix = 0; ix < 254; ix++)
    {
        if (ents[ix] == entsptr)
        {
            alreadyThere = true;
            break;
        }
    }

    if (alreadyThere)
    {
        goto GIVE_UP;
    }
    else
    {
        for (ix = 0; ix < 254; ix++)
        {
            if (ents[ix] == 0)
            {
                ents[ix] = entsptr;
                break;
            }
        }
    }

GIVE_UP:
    __asm {
        popad
        jmp[EntlistJmpBack]
    }
}
