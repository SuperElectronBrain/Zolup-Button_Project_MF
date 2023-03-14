// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PROJECT_MF_MainLevelUICanvasWidget_generated_h
#error "MainLevelUICanvasWidget.generated.h already included, missing '#pragma once' in MainLevelUICanvasWidget.h"
#endif
#define PROJECT_MF_MainLevelUICanvasWidget_generated_h

#define Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_SPARSE_DATA
#define Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnEditButtonClicked); \
	DECLARE_FUNCTION(execOnQuitButtonClicked); \
	DECLARE_FUNCTION(execOnStartButtonClicked); \
	DECLARE_FUNCTION(execEnterEditMode); \
	DECLARE_FUNCTION(execGameQuit); \
	DECLARE_FUNCTION(execGameStart);


#define Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnEditButtonClicked); \
	DECLARE_FUNCTION(execOnQuitButtonClicked); \
	DECLARE_FUNCTION(execOnStartButtonClicked); \
	DECLARE_FUNCTION(execEnterEditMode); \
	DECLARE_FUNCTION(execGameQuit); \
	DECLARE_FUNCTION(execGameStart);


#define Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMainLevelUICanvasWidget(); \
	friend struct Z_Construct_UClass_UMainLevelUICanvasWidget_Statics; \
public: \
	DECLARE_CLASS(UMainLevelUICanvasWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(UMainLevelUICanvasWidget)


#define Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_INCLASS \
private: \
	static void StaticRegisterNativesUMainLevelUICanvasWidget(); \
	friend struct Z_Construct_UClass_UMainLevelUICanvasWidget_Statics; \
public: \
	DECLARE_CLASS(UMainLevelUICanvasWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Project_MF"), NO_API) \
	DECLARE_SERIALIZER(UMainLevelUICanvasWidget)


#define Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMainLevelUICanvasWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMainLevelUICanvasWidget) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMainLevelUICanvasWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMainLevelUICanvasWidget); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMainLevelUICanvasWidget(UMainLevelUICanvasWidget&&); \
	NO_API UMainLevelUICanvasWidget(const UMainLevelUICanvasWidget&); \
public:


#define Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMainLevelUICanvasWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMainLevelUICanvasWidget(UMainLevelUICanvasWidget&&); \
	NO_API UMainLevelUICanvasWidget(const UMainLevelUICanvasWidget&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMainLevelUICanvasWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMainLevelUICanvasWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMainLevelUICanvasWidget)


#define Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__GameStartButton() { return STRUCT_OFFSET(UMainLevelUICanvasWidget, GameStartButton); } \
	FORCEINLINE static uint32 __PPO__GameQuitButton() { return STRUCT_OFFSET(UMainLevelUICanvasWidget, GameQuitButton); } \
	FORCEINLINE static uint32 __PPO__GameEditButton() { return STRUCT_OFFSET(UMainLevelUICanvasWidget, GameEditButton); }


#define Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_12_PROLOG
#define Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_SPARSE_DATA \
	Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_RPC_WRAPPERS \
	Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_INCLASS \
	Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_PRIVATE_PROPERTY_OFFSET \
	Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_SPARSE_DATA \
	Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_INCLASS_NO_PURE_DECLS \
	Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECT_MF_API UClass* StaticClass<class UMainLevelUICanvasWidget>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Project_MF_Source_Project_MF_MainLevelUICanvasWidget_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
