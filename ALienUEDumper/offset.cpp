#include "pch.h"
#include "offset.h"


// Note: This is one more of the stupid things, but as said, it only takes a few milliseconds and makes it more readable
uint16_t OffsetsFinder::FindUObject_PEVTableIndex() {
    // Find any UObject class
    uintptr_t* (__fastcall * _StaticFindObject) (uintptr_t * ObjectClass, uintptr_t * InObjectPackage, const wchar_t* OrigInName, bool ExactClass);
    _StaticFindObject = decltype(_StaticFindObject)(Offsets::StaticFindObject);

    uintptr_t* Object = Object = _StaticFindObject(0, 0, L"CoreUObject.Object", false);
    if (Object == 0) return 0;

    __int64** vtable = *reinterpret_cast<__int64***>(Object);
    uint16_t index = 0;
    while (!IsBadReadPtr((void*)((__int64)vtable + (index * 8)), 8)) {
        if (*(__int64*)((__int64)vtable + (index * 8)) == Offsets::ProcessEvent) {
            return index;
        }

        index++;
    }

    return 0;
}


// Things below are tricky and might not always work, if it fails you need to hardcode them, or try to fix it :)


static bool VerifyProcessEvent(uintptr_t Address)
{
    // Now this is atleast for Fortnite, but between 1.8 and latest ProcessEvent has always started with this besides a few seasons between like s16-18

    return (
        *(uint8_t*)(Address) == 0x40 &&
        *(uint8_t*)(Address + 1) == 0x55 &&
        *(uint8_t*)(Address + 2) == 0x56 &&
        *(uint8_t*)(Address + 3) == 0x57 &&
        *(uint8_t*)(Address + 4) == 0x41 &&
        *(uint8_t*)(Address + 5) == 0x54 &&
        *(uint8_t*)(Address + 6) == 0x41 &&
        *(uint8_t*)(Address + 7) == 0x55 &&
        *(uint8_t*)(Address + 8) == 0x41 &&
        *(uint8_t*)(Address + 9) == 0x56 &&
        *(uint8_t*)(Address + 10) == 0x41
        );

    // Most of the time UE4 Games have a string above ProcessEvent like 2 functions above "AccessNoNoneContext", we may be able to check if this string is above it.
    return false;
}

//找一个UObject然后遍历虚表特征定位到ProcessEvent
static uintptr_t FindPE_1() {
    // Find any UObject class
    uintptr_t* (__fastcall * _StaticFindObject) (uintptr_t * ObjectClass, uintptr_t * InObjectPackage, const wchar_t* OrigInName, bool ExactClass);
    _StaticFindObject = decltype(_StaticFindObject)(Offsets::StaticFindObject);

    uintptr_t* Object = Object = _StaticFindObject(0, 0, L"CoreUObject.Object", false);
    if (Object == 0) return 0;

    __int64** vtable = *reinterpret_cast<__int64***>(Object);
    uint16_t index = 0;
    while (!IsBadReadPtr((void*)((__int64)vtable + (index * 8)), 8)) {
        if (VerifyProcessEvent(__int64(*(__int64*)((__int64)vtable + (index * 8)))))
        {
            return *(__int64*)((__int64)vtable + (index * 8));
        }

        index++;
    }

    return 0;
}

static uintptr_t FindPE_2() {
    uint64_t LastAddress = 0;
    while (true) {
        LastAddress = Memory::Sexy::PatternScan("0F 85 ? ? 00 00 F7 ? ? 00 00 00 00 04 00 00", LastAddress); // test dword ptr [rsi+98h], 400h
        if (!LastAddress) break;

        // A small check to make sure its process event ("0F 85 ? ? 00 00")
        // Maximal 10 bytes away ig, I tested it on a UE4 project and there was a mov between the two insturctions so yea
        bool isProcessEvent = false;
        for (uint8_t i = 0; i < 10; i++) {
            if (*(uint8_t*)(LastAddress - i) == 0x0F && *(uint8_t*)(LastAddress - i + 1) == 0x85 /*&& *(uint8_t*)(LastAddress - i + 4) == 0x00 && *(uint8_t*)(LastAddress - i + 5) == 0x00*/) {
                isProcessEvent = true;
                break;
            }
        }

        if (isProcessEvent) {
            for (uint8_t i = 0; i < 255; i++) {
                if (*(uint8_t*)(LastAddress - i) == 0x40 && *(uint8_t*)(LastAddress - i + 1) == 0x55) {
                    return LastAddress - i;
                }
            }
        }

        // We might reach this, but doesnt matter bc then we will find the correct function
        return 0;
    }
    return 0;
}

uintptr_t OffsetsFinder::FindProcessEvent() {
    // "Hacky" ways to find process event:
        // 1. Search a UObject and loop until you find a function starting with "40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC" (maybe a bit less, but this works for Fortnite...)
            // We can then get 3-4 other objects and check if they have the same function at that index, if all have that we can most likely assume that this is process event
        // 2. There is a small pattern that (almost) every UE4 game has in the PE pattern, so we can search that and go back to the begin of the function

    uintptr_t ProcessEvent = FindPE_1();

    // printf("PE1 works: %p\n", ProcessEvent);

    if (!ProcessEvent)
    {
        ProcessEvent = FindPE_2();

        if (!VerifyProcessEvent(ProcessEvent))
            // Very unlikly to happen
            ProcessEvent = 0;
    }

    return ProcessEvent;
}

uintptr_t OffsetsFinder::FindGObjects() {
    // Find GObjects by Process Event

    //RapaNui-Win64-Shipping.exe+11182FC - C1 F9 10              - sar ecx,10
    //RapaNui - Win64 - Shipping.exe + 11182FF - 48 63 C9 - movsxd  rcx, ecx
    //RapaNui - Win64 - Shipping.exe + 1118302 - 48 8D 14 40 - lea rdx, [rax + rax * 2]
    //RapaNui - Win64 - Shipping.exe + 1118306 - 48 8B 05 ABECB302 - mov rax, [RapaNui - Win64 - Shipping.exe + 3C56FB8]

    //torchlight_infinite.exe + 4BDEBB8 - C1 F9 10              - sar ecx,10
    //torchlight_infinite.exe + 4BDEBBB - 48 63 D1        - movsxd  rdx, ecx
    //torchlight_infinite.exe + 4BDEBBE - 48 8B 0D 1331F603 - mov rcx, [torchlight_infinite.exe + 8B41CD8]

    uint8_t found = 0;
    for (uint16_t i = 0; i < 0x256; i++) {
        if ( //sar ecx,10
            *(uint8_t*)(Offsets::ProcessEvent + i) == 0xC1 &&
            *(uint8_t*)(Offsets::ProcessEvent + i + 1) == 0xF9 &&
            *(uint8_t*)(Offsets::ProcessEvent + i + 2) == 0x10
            ) {
            found = 1;
            uintptr_t startaddr = Offsets::ProcessEvent + i + 2;
            if (found) {
                for (uint16_t j = 0; j < 0x256; j++)
                {
                    if (
                        *(uint8_t*)(startaddr + j) == 0x48 &&
                        *(uint8_t*)(startaddr + j + 1) == 0x8B
                        )
                    {
                        uintptr_t addr = startaddr + j;
                        return ((addr + 3 + 4) + *(int32_t*)(addr + 3));
                    }
                }
            }
        }
    }
    return 0;
}

bool OffsetsFinder::FindAll()
{
    if (!Offsets::StaticFindObject) {
        printf("Failed to find StaticFindObject\n");
        return false;
    }
    Offsets::ProcessEvent = OffsetsFinder::FindProcessEvent();
    if (!Offsets::ProcessEvent) {
        printf("Failed to find ProcessEvent\n");
        return false;
    }
    printf("Offsets::ProcessEvent:0x%llx\n", Offsets::ProcessEvent);
    Offsets::UObject::ProcessEvent = OffsetsFinder::FindUObject_PEVTableIndex();

    printf("Offsets::UObject::ProcessEvent:0x%x\n", Offsets::UObject::ProcessEvent);

    /*Offsets::GObjects = OffsetsFinder::FindGObjects();
    if (!Offsets::GObjects)
    {
        printf("Failed to find GObjects\n");
        return false;
    }
    printf("Offsets::GObjects:0x%llx\n", Offsets::GObjects);*/

    //if (!SDKMgr::UKismetStringLibrary::Init())
    //{
    //    return false;
    //}
    if (!SDKMgr::UKismetSystemLibrary::Init())
    {
        return false;
    }
    return TRUE;
}