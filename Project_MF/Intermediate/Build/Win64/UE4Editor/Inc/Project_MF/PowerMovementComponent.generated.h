// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PROJECT_MF_PowerMovementComponent_generated_h
#error "PowerMovementComponent.generated.h already included, missing '#pragma once' in PowerMovementComponent.h"
#endif
#define PROJECT_MF_PowerMovementComponent_generated_h

#define Project_MF_Source_Project_MF_PowerMovementComponent_h_13_SPARSE_DATA
#define Project_MF_Source_Project_MF_PowerMovementComponent_h_13_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execEndAction); \
	DECLARE_FUNCTION(execStartAction);


#define Project_MF_Source_Project_MF_PowerMovementComponent_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execEndAction); \
	DECLARE_FUNCTION(execStartAction);


#define Project_MF_Source_Project_MF_PowerMovementComponent_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPowerMovementComponent(); \
	friend struct Z_Construct_UClass_UPowerMovementComponent_Statics; \
public: \
	DECLARE_CLASS(UPowerMovementComponent, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(UPowerMovementComponent)


#define Project_MF_Source_Project_MF_PowerMovementComponent_h_13_INCLASS \
private: \
	static void StaticRegisterNativesUPowerMovementComponent(); \
	friend struct Z_Construct_UClass_UPowerMovementComponent_Statics; \
public: \
	DECLARE_CLASS(UPowerMovementComponent, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(UPowerMovementComponent)


#define Project_MF_Source_Project_MF_PowerMovementComponent_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UPowerMovementComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPowerMovementComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPowerMovementComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPowerMovementComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UPowerMovementComponent(UPowerMovementComponent&&); \
	NO_API UPowerMovementComponent(const UPowerMovementComponent&); \
public:


#define Project_MF_Source_Project_MF_PowerMovementComponent_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UPowerMovementComponent(UPowerMovementComponent&&); \
	NO_API UPowerMovementComponent(const UPowerMovementComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPowerMovementComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPowerMovementComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UPowerMovementComponent)


#define Project_MF_Source_Project_MF_PowerMovementComponent_h_13_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ActingRange() { return STRUCT_OFFSET(UPowerMovementComponent, ActingRange); } \
	FORCEINLINE static uint32 __PPO__ActingSpeed() { return STRUCT_OFFSET(UPowerMovementComponent, ActingSpeed); } \
	FORCEINLINE static uint32 __PPO__OriginPosition() { return STRUCT_OFFSET(UPowerMovementComponent, OriginPosition); } \
	FORCEINLINE static uint32 __PPO__CurrentMovement() { return STRUCT_OFFSET(UPowerMovementComponent, CurrentMovement); } \
	FORCEINLINE static uint32 __PPO__bActingState() { return STRUCT_OFFSET(UPowerMovementComponent, bActingState); }


#define Project_MF_Source_Project_MF_PowerMovementComponent_h_10_PROLOG
#define Project_MF_Source_Project_MF_PowerMovementComponent_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_PowerMovementComponent_h_13_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_PowerMovementComponent_h_13_SPARSE_DATA \
	Project_MF_Source_Project_MF_PowerMovementComponent_h_13_RPC_WRAPPERS \
	Project_MF_Source_Project_MF_PowerMovementComponent_h_13_INCLASS \
	Project_MF_Source_Project_MF_PowerMovementComponent_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Project_MF_Source_Project_MF_PowerMovementComponent_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_PowerMovementComponent_h_13_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_PowerMovementComponent_h_13_SPARSE_DATA \
	Project_MF_Source_Project_MF_PowerMovementComponent_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_PowerMovementComponent_h_13_INCLASS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_PowerMovementComponent_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECT_MF_API UClass* StaticClass<class UPowerMovementComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Project_MF_Source_Project_MF_PowerMovementComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
