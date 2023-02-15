#pragma once
#include "../Core/Containers/UnrealString.h"
#include "../Core/UObject/NameTypes.h"

namespace SDKMgr {
	uintptr_t* SDK_StaticFindObject(uintptr_t* ObjectClass, uintptr_t* InObjectPackage, const wchar_t* OrigInName, bool ExactClass);
	void SDK_ProcessEvent(void* pObject, void* pFunction, void* params);

	namespace UKismetStringLibrary {
		extern inline uintptr_t* KismetStringLibrary = 0;
		extern inline uintptr_t* _Conv_NameToString = 0;
		extern inline uintptr_t* _Conv_StringToName = 0;

		extern inline bool Init() {
			if (!KismetStringLibrary) {
				KismetStringLibrary = SDK_StaticFindObject(0,0,L"Engine.KismetStringLibrary",0);
			}

			if (!_Conv_NameToString) {
				_Conv_NameToString = SDK_StaticFindObject(0,0,L"Engine.KismetStringLibrary.Conv_NameToString",0);
			}

			if (!_Conv_StringToName) {
				_Conv_StringToName = SDK_StaticFindObject(0,0,L"Engine.KismetStringLibrary.Conv_StringToName",0);
			}

			return (
				KismetStringLibrary != 0 &&
				_Conv_NameToString != 0 &&
				_Conv_StringToName != 0
				);
		}

		extern inline struct FString Conv_NameToString(FName* inName);
		extern inline struct FString Conv_NameToString(uint64_t inName);
		extern inline FName Conv_StringToName(struct FString string);
		extern inline uint64_t Conv_StringToName_G(struct FString string);
	}

	namespace UKismetSystemLibrary {
		extern inline uintptr_t* KismetSystemLibrary = 0;
		extern inline uintptr_t* _GetObjectName = 0;
		extern inline uintptr_t* _GetPathName = 0;

		extern inline bool Init() {
			if (!KismetSystemLibrary) {
				KismetSystemLibrary = SDK_StaticFindObject(0,0,L"Engine.KismetSystemLibrary",0);
				//printf("KismetSystemLibrary: %p\n", KismetSystemLibrary);
			}

			if (!_GetObjectName) {
				_GetObjectName = SDK_StaticFindObject(0,0,L"Engine.KismetSystemLibrary.GetObjectName",0);
			}

			if (!_GetPathName) {
				_GetPathName = SDK_StaticFindObject(0,0,L"Engine.KismetSystemLibrary.GetPathName",0);
				//printf("_GetPathName: %p\n", _GetPathName);
			}

			return (
				KismetSystemLibrary != 0 &&
				_GetObjectName != 0 &&
				_GetPathName != 0
				);
		}

		extern inline FString GetObjectName(uintptr_t* Object);
		extern inline FString GetPathName(uintptr_t* Object);
	}

}