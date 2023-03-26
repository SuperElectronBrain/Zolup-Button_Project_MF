// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FHitResult;
#ifdef PROJECT_MF_PowerExecutionComponent_generated_h
#error "PowerExecutionComponent.generated.h already included, missing '#pragma once' in PowerExecutionComponent.h"
#endif
#define PROJECT_MF_PowerExecutionComponent_generated_h

#define Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_SPARSE_DATA
#define Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnOverlapEnd); \
	DECLARE_FUNCTION(execOnOverlapBegin);


#define Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnOverlapEnd); \
	DECLARE_FUNCTION(execOnOverlapBegin);


#define Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPowerExecutionComponent(); \
	friend struct Z_Construct_UClass_UPowerExecutionComponent_Statics; \
public: \
	DECLARE_CLASS(UPowerExecutionComponent, UPowerComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(UPowerExecutionComponent)


#define Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_INCLASS \
private: \
	static void StaticRegisterNativesUPowerExecutionComponent(); \
	friend struct Z_Construct_UClass_UPowerExecutionComponent_Statics; \
public: \
	DECLARE_CLASS(UPowerExecutionComponent, UPowerComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(UPowerExecutionComponent)


#define Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UPowerExecutionComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPowerExecutionComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPowerExecutionComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPowerExecutionComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UPowerExecutionComponent(UPowerExecutionComponent&&); \
	NO_API UPowerExecutionComponent(const UPowerExecutionComponent&); \
public:


#define Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UPowerExecutionComponent(UPowerExecutionComponent&&); \
	NO_API UPowerExecutionComponent(const UPowerExecutionComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPowerExecutionComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPowerExecutionComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UPowerExecutionComponent)


#define Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Mesh() { return STRUCT_OFFSET(UPowerExecutionComponent, Mesh); } \
	FORCEINLINE static uint32 __PPO__Collider() { return STRUCT_OFFSET(UPowerExecutionComponent, Collider); }


#define Project_MF_Source_Project_MF_PowerExecutionComponent_h_12_PROLOG
#define Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_SPARSE_DATA \
	Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_RPC_WRAPPERS \
	Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_INCLASS \
	Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_SPARSE_DATA \
	Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_INCLASS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_PowerExecutionComponent_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECT_MF_API UClass* StaticClass<class UPowerExecutionComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Project_MF_Source_Project_MF_PowerExecutionComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
