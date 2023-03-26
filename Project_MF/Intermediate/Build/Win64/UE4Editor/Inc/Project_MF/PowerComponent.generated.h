// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PROJECT_MF_PowerComponent_generated_h
#error "PowerComponent.generated.h already included, missing '#pragma once' in PowerComponent.h"
#endif
#define PROJECT_MF_PowerComponent_generated_h

#define Project_MF_Source_Project_MF_PowerComponent_h_13_SPARSE_DATA
#define Project_MF_Source_Project_MF_PowerComponent_h_13_RPC_WRAPPERS
#define Project_MF_Source_Project_MF_PowerComponent_h_13_RPC_WRAPPERS_NO_PURE_DECLS
#define Project_MF_Source_Project_MF_PowerComponent_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPowerComponent(); \
	friend struct Z_Construct_UClass_UPowerComponent_Statics; \
public: \
	DECLARE_CLASS(UPowerComponent, UBoxComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(UPowerComponent)


#define Project_MF_Source_Project_MF_PowerComponent_h_13_INCLASS \
private: \
	static void StaticRegisterNativesUPowerComponent(); \
	friend struct Z_Construct_UClass_UPowerComponent_Statics; \
public: \
	DECLARE_CLASS(UPowerComponent, UBoxComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(UPowerComponent)


#define Project_MF_Source_Project_MF_PowerComponent_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UPowerComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPowerComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPowerComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPowerComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UPowerComponent(UPowerComponent&&); \
	NO_API UPowerComponent(const UPowerComponent&); \
public:


#define Project_MF_Source_Project_MF_PowerComponent_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UPowerComponent(UPowerComponent&&); \
	NO_API UPowerComponent(const UPowerComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPowerComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPowerComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UPowerComponent)


#define Project_MF_Source_Project_MF_PowerComponent_h_13_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__MeshOrigin() { return STRUCT_OFFSET(UPowerComponent, MeshOrigin); } \
	FORCEINLINE static uint32 __PPO__MaterialOrigin() { return STRUCT_OFFSET(UPowerComponent, MaterialOrigin); } \
	FORCEINLINE static uint32 __PPO__TriggerSize() { return STRUCT_OFFSET(UPowerComponent, TriggerSize); } \
	FORCEINLINE static uint32 __PPO__bPowerState() { return STRUCT_OFFSET(UPowerComponent, bPowerState); }


#define Project_MF_Source_Project_MF_PowerComponent_h_10_PROLOG
#define Project_MF_Source_Project_MF_PowerComponent_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_PowerComponent_h_13_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_PowerComponent_h_13_SPARSE_DATA \
	Project_MF_Source_Project_MF_PowerComponent_h_13_RPC_WRAPPERS \
	Project_MF_Source_Project_MF_PowerComponent_h_13_INCLASS \
	Project_MF_Source_Project_MF_PowerComponent_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Project_MF_Source_Project_MF_PowerComponent_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_PowerComponent_h_13_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_PowerComponent_h_13_SPARSE_DATA \
	Project_MF_Source_Project_MF_PowerComponent_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_PowerComponent_h_13_INCLASS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_PowerComponent_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECT_MF_API UClass* StaticClass<class UPowerComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Project_MF_Source_Project_MF_PowerComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
