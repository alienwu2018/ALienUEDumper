#pragma once

namespace Offsets {
	extern inline uintptr_t ProcessEvent = 0;                //done
	extern inline uintptr_t StaticFindObject = 0;            //done
	extern inline uintptr_t GObjects = 0;                    //done

	// Not all are used, offets are just examples ofc
	namespace UFunction {
		extern inline uint16_t FunctionFlags = 0;
		extern inline uint16_t NumParms = 0;
		extern inline uint16_t ParmsSize = 0;
		extern inline uint16_t ReturnValueOffset = 0;
		extern inline uint16_t RPCId = 0;
		extern inline uint16_t RPCResponseId = 0;
		extern inline uint16_t FirstPropertyToInit = 0;
		extern inline uint16_t Func = 0xC0;
	}

	namespace UObject {
		extern inline uint16_t InternalIndex = 0x0C;

		// VTable
		extern inline uint16_t ProcessEvent = 0;
	}

	namespace UObjectBase {
		extern inline uint16_t ClassPrivate = 0;
		extern inline uint16_t NamePrivate = 0;
	}

	namespace UClass {

	}

	namespace FFieldClass {
		extern inline uint16_t Name = 0; // I think this should even be right all the time
	}

	namespace FField {
		extern inline uint16_t Next = 0;
		extern inline uint16_t Owner = 0;
		extern inline uint16_t NamePrivate = 0;
		extern inline uint16_t FlagsPrivate = 0;
	}

	namespace UEnum {
		extern inline uint16_t Names = 0x40;
	}

	namespace UField {
		extern inline uint16_t Next = 0x20;
	};

	namespace UStruct {
		extern inline uint16_t Children = 0;
		extern inline uint16_t SuperStruct = 48;
		extern inline uint16_t ChildProperties = 0;
		extern inline uint16_t PropertiesSize = 0;
	}

	namespace FName {
		extern inline uint16_t ComparisonIndex = 0;
		extern inline uint16_t DisplayIndex = 0x04;
		extern inline uint16_t Number = 0x04;
	}

	namespace UObjectPropertyBase {
		extern inline uint16_t PropertyClass = 0x70;
	}

	namespace UClassProperty {
		extern inline uint16_t MetaClass = 0x78;
	}

	namespace UEnumProperty {
		extern inline uint16_t UnderlyingProp = 0x70;
		extern inline uint16_t Enum = 0;
	}

	namespace UMulticastDelegateProperty {
		extern inline uint16_t SignatureFunction = 0;
	}

	namespace UDelegateProperty {
		extern inline uint16_t SignatureFunction = 0;
	}

	namespace UStructProperty {
		extern inline uint16_t Struct = 0;
	}

	namespace UArrayProperty {
		extern inline uint16_t Inner = 0;
	}

	namespace UBoolProperty {
		extern inline uint16_t FieldSize = 0;
		extern inline uint16_t ByteOffset = 0;
		extern inline uint16_t ByteMask = 0;
		extern inline uint16_t FieldMask = 0;
	}

	namespace UProperty {
		extern inline uint16_t ArrayDim = 0;
		extern inline uint16_t PropertyFlags = 0;
		extern inline uint16_t Offset_Internal = 0;
		extern inline uint16_t ElementSize = 0;
	}
}

namespace OffsetsFinder {
	extern uintptr_t FindProcessEvent();
	extern uint16_t FindUObject_PEVTableIndex();
	extern uintptr_t FindGObjects();
	extern bool FindAll();
}