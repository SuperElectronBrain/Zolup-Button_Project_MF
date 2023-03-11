// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PROJECT_MF_CustomGameInstance_generated_h
#error "CustomGameInstance.generated.h already included, missing '#pragma once' in CustomGameInstance.h"
#endif
#define PROJECT_MF_CustomGameInstance_generated_h

#define Project_MF_Source_Project_MF_CustomGameInstance_h_15_SPARSE_DATA
#define Project_MF_Source_Project_MF_CustomGameInstance_h_15_RPC_WRAPPERS
#define Project_MF_Source_Project_MF_CustomGameInstance_h_15_RPC_WRAPPERS_NO_PURE_DECLS
#define Project_MF_Source_Project_MF_CustomGameInstance_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCustomGameInstance(); \
	friend struct Z_Construct_UClass_UCustomGameInstance_Statics; \
public: \
	DECLARE_CLASS(UCustomGameInstance, UGameInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(UCustomGameInstance)


#define Project_MF_Source_Project_MF_CustomGameInstance_h_15_INCLASS \
private: \
	static void StaticRegisterNativesUCustomGameInstance(); \
	friend struct Z_Construct_UClass_UCustomGameInstance_Statics; \
public: \
	DECLARE_CLASS(UCustomGameInstance, UGameInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(UCustomGameInstance)


#define Project_MF_Source_Project_MF_CustomGameInstance_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCustomGameInstance(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCustomGameInstance) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCustomGameInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCustomGameInstance); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCustomGameInstance(UCustomGameInstance&&); \
	NO_API UCustomGameInstance(const UCustomGameInstance&); \
public:


#define Project_MF_Source_Project_MF_CustomGameInstance_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCustomGameInstance(UCustomGameInstance&&); \
	NO_API UCustomGameInstance(const UCustomGameInstance&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCustomGameInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCustomGameInstance); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UCustomGameInstance)


#define Project_MF_Source_Project_MF_CustomGameInstance_h_15_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__bEditmode() { return STRUCT_OFFSET(UCustomGameInstance, bEditmode); }


#define Project_MF_Source_Project_MF_CustomGameInstance_h_12_PROLOG
#define Project_MF_Source_Project_MF_CustomGameInstance_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_CustomGameInstance_h_15_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_CustomGameInstance_h_15_SPARSE_DATA \
	Project_MF_Source_Project_MF_CustomGameInstance_h_15_RPC_WRAPPERS \
	Project_MF_Source_Project_MF_CustomGameInstance_h_15_INCLASS \
	Project_MF_Source_Project_MF_CustomGameInstance_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Project_MF_Source_Project_MF_CustomGameInstance_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_CustomGameInstance_h_15_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_CustomGameInstance_h_15_SPARSE_DATA \
	Project_MF_Source_Project_MF_CustomGameInstance_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_CustomGameInstance_h_15_INCLASS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_CustomGameInstance_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECT_MF_API UClass* StaticClass<class UCustomGameInstance>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Project_MF_Source_Project_MF_CustomGameInstance_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
