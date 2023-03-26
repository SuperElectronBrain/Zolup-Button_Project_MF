// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UStaticMeshComponent;
#ifdef PROJECT_MF_MFActor_generated_h
#error "MFActor.generated.h already included, missing '#pragma once' in MFActor.h"
#endif
#define PROJECT_MF_MFActor_generated_h

#define Project_MF_Source_Project_MF_MFActor_h_12_SPARSE_DATA
#define Project_MF_Source_Project_MF_MFActor_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetMesh);


#define Project_MF_Source_Project_MF_MFActor_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetMesh);


#define Project_MF_Source_Project_MF_MFActor_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMFActor(); \
	friend struct Z_Construct_UClass_AMFActor_Statics; \
public: \
	DECLARE_CLASS(AMFActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(AMFActor)


#define Project_MF_Source_Project_MF_MFActor_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAMFActor(); \
	friend struct Z_Construct_UClass_AMFActor_Statics; \
public: \
	DECLARE_CLASS(AMFActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(AMFActor)


#define Project_MF_Source_Project_MF_MFActor_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AMFActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AMFActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMFActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMFActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMFActor(AMFActor&&); \
	NO_API AMFActor(const AMFActor&); \
public:


#define Project_MF_Source_Project_MF_MFActor_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMFActor(AMFActor&&); \
	NO_API AMFActor(const AMFActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMFActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMFActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMFActor)


#define Project_MF_Source_Project_MF_MFActor_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Mesh() { return STRUCT_OFFSET(AMFActor, Mesh); }


#define Project_MF_Source_Project_MF_MFActor_h_9_PROLOG
#define Project_MF_Source_Project_MF_MFActor_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_MFActor_h_12_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_MFActor_h_12_SPARSE_DATA \
	Project_MF_Source_Project_MF_MFActor_h_12_RPC_WRAPPERS \
	Project_MF_Source_Project_MF_MFActor_h_12_INCLASS \
	Project_MF_Source_Project_MF_MFActor_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Project_MF_Source_Project_MF_MFActor_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_MFActor_h_12_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_MFActor_h_12_SPARSE_DATA \
	Project_MF_Source_Project_MF_MFActor_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_MFActor_h_12_INCLASS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_MFActor_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECT_MF_API UClass* StaticClass<class AMFActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Project_MF_Source_Project_MF_MFActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
