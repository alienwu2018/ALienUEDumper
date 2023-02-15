#include "../pch.h"
#include "SDKMgr.h"

uintptr_t* SDKMgr::SDK_StaticFindObject(uintptr_t* ObjectClass, uintptr_t* InObjectPackage, const wchar_t* OrigInName, bool ExactClass)
{
	if (!OrigInName) return nullptr;
	uintptr_t* (__fastcall * _StaticFindObject) (uintptr_t * ObjectClass, uintptr_t * InObjectPackage, const wchar_t* OrigInName, bool ExactClass);
	_StaticFindObject = decltype(_StaticFindObject)(Offsets::StaticFindObject);
	return _StaticFindObject(ObjectClass, InObjectPackage, OrigInName, ExactClass);
}

void SDKMgr::SDK_ProcessEvent(void* pObject, void* pFunction, void* params)
{
	void(__fastcall * _ProcessEvent)(void* pObject, void* pFunction, void* params);
	_ProcessEvent = decltype(_ProcessEvent)(Offsets::ProcessEvent);
	return _ProcessEvent(pObject, pFunction, params);
}


struct FString SDKMgr::UKismetStringLibrary::Conv_NameToString(FName* inName) {
	struct {
		uint64_t inName;
		struct FString ReturnValue;
	} params{ .inName = inName->GetComparisonIndex().Value };

	SDKMgr::SDK_ProcessEvent(SDKMgr::UKismetStringLibrary::KismetStringLibrary, SDKMgr::UKismetStringLibrary::_Conv_NameToString, &params);

	return params.ReturnValue;
}

struct FString SDKMgr::UKismetStringLibrary::Conv_NameToString(uint64_t inName) {
	struct {
		uint64_t inName;
		struct FString ReturnValue;
	} params{ .inName = inName };

	SDKMgr::SDK_ProcessEvent(SDKMgr::UKismetStringLibrary::KismetStringLibrary, SDKMgr::UKismetStringLibrary::_Conv_NameToString, &params);

	return params.ReturnValue;
}

FName  SDKMgr::UKismetStringLibrary::Conv_StringToName(struct FString string) {
	struct {
		struct FString string;
		FName ReturnValue;
	} params{ .string = string };

	SDKMgr::SDK_ProcessEvent(SDKMgr::UKismetStringLibrary::KismetStringLibrary, SDKMgr::UKismetStringLibrary::_Conv_StringToName, &params);

	return params.ReturnValue;
}

uint64_t  SDKMgr::UKismetStringLibrary::Conv_StringToName_G(struct FString string) {
	struct {
		struct FString string;
		uint64_t ReturnValue;
	} params{ .string = string };

	SDKMgr::SDK_ProcessEvent(SDKMgr::UKismetStringLibrary::KismetStringLibrary, SDKMgr::UKismetStringLibrary::_Conv_StringToName, &params);

	return params.ReturnValue;
}

FString  SDKMgr::UKismetSystemLibrary::GetPathName(uintptr_t* Object) {
	struct {
		uintptr_t* Object;
		struct FString ReturnValue;
	} params;

	params.Object = Object;

	SDKMgr::SDK_ProcessEvent(
		SDKMgr::UKismetSystemLibrary::KismetSystemLibrary,
		SDKMgr::UKismetSystemLibrary::_GetPathName,
		&params
	);

	return params.ReturnValue;
}

FString SDKMgr::UKismetSystemLibrary::GetObjectName(uintptr_t* Object) {
	struct {
		uintptr_t* Object;
		struct FString ReturnValue;
	} params;

	params.Object = Object;

	SDKMgr::SDK_ProcessEvent(
		SDKMgr::UKismetSystemLibrary::KismetSystemLibrary,
		SDKMgr::UKismetSystemLibrary::_GetObjectName,
		&params
	);

	return params.ReturnValue;
}