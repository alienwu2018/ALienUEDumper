#pragma once

//定义组件名称
#define ZuoQi  L"/Engine/Transient.RNGameEngine_0:RNGameInstance_BP_C_0.RNSkillPanel_BP_C_0.WidgetTree_0.VehicleButton"

//游戏内的功能call
namespace GameCall {
	EXTERN_C __int64 ComponentCall(uintptr_t * Object);
}

namespace GameHook {
	typedef  VOID(*t_ProcessEvent)(void*, void*, void*);
	VOID HookedProcessEvent(uintptr_t* pObject, void* pFunction, void* params);

	VOID StartHook();
	VOID StopHook();
}