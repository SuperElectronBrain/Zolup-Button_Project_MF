// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AEditLevelMFActorManagementActor;
#ifdef PROJECT_MF_EditLevelPawn_generated_h
#error "EditLevelPawn.generated.h already included, missing '#pragma once' in EditLevelPawn.h"
#endif
#define PROJECT_MF_EditLevelPawn_generated_h

#define Project_MF_Source_Project_MF_EditLevelPawn_h_14_SPARSE_DATA
#define Project_MF_Source_Project_MF_EditLevelPawn_h_14_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetEditLevelMFActorManagementActor); \
	DECLARE_FUNCTION(execHorizontalMovement); \
	DECLARE_FUNCTION(execVerticalMovement); \
	DECLARE_FUNCTION(execSpawnMFActor);


#define Project_MF_Source_Project_MF_EditLevelPawn_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetEditLevelMFActorManagementActor); \
	DECLARE_FUNCTION(execHorizontalMovement); \
	DECLARE_FUNCTION(execVerticalMovement); \
	DECLARE_FUNCTION(execSpawnMFActor);


#define Project_MF_Source_Project_MF_EditLevelPawn_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEditLevelPawn(); \
	friend struct Z_Construct_UClass_AEditLevelPawn_Statics; \
public: \
	DECLARE_CLASS(AEditLevelPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(AEditLevelPawn)


#define Project_MF_Source_Project_MF_EditLevelPawn_h_14_INCLASS \
private: \
	static void StaticRegisterNativesAEditLevelPawn(); \
	friend struct Z_Construct_UClass_AEditLevelPawn_Statics; \
public: \
	DECLARE_CLASS(AEditLevelPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(AEditLevelPawn)


#define Project_MF_Source_Project_MF_EditLevelPawn_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AEditLevelPawn(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AEditLevelPawn) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEditLevelPawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEditLevelPawn); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEditLevelPawn(AEditLevelPawn&&); \
	NO_API AEditLevelPawn(const AEditLevelPawn&); \
public:


#define Project_MF_Source_Project_MF_EditLevelPawn_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEditLevelPawn(AEditLevelPawn&&); \
	NO_API AEditLevelPawn(const AEditLevelPawn&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEditLevelPawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEditLevelPawn); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEditLevelPawn)


#define Project_MF_Source_Project_MF_EditLevelPawn_h_14_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__EditLevelMFActorManagementActor() { return STRUCT_OFFSET(AEditLevelPawn, EditLevelMFActorManagementActor); } \
	FORCEINLINE static uint32 __PPO__DefaultComponent() { return STRUCT_OFFSET(AEditLevelPawn, DefaultComponent); } \
	FORCEINLINE static uint32 __PPO__Movement() { return STRUCT_OFFSET(AEditLevelPawn, Movement); }


#define Project_MF_Source_Project_MF_EditLevelPawn_h_11_PROLOG
#define Project_MF_Source_Project_MF_EditLevelPawn_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_EditLevelPawn_h_14_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_EditLevelPawn_h_14_SPARSE_DATA \
	Project_MF_Source_Project_MF_EditLevelPawn_h_14_RPC_WRAPPERS \
	Project_MF_Source_Project_MF_EditLevelPawn_h_14_INCLASS \
	Project_MF_Source_Project_MF_EditLevelPawn_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Project_MF_Source_Project_MF_EditLevelPawn_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_EditLevelPawn_h_14_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_EditLevelPawn_h_14_SPARSE_DATA \
	Project_MF_Source_Project_MF_EditLevelPawn_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_EditLevelPawn_h_14_INCLASS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_EditLevelPawn_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECT_MF_API UClass* StaticClass<class AEditLevelPawn>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Project_MF_Source_Project_MF_EditLevelPawn_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
