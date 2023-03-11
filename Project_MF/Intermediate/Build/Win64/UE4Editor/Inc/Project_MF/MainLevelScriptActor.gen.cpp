// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/MainLevelScriptActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMainLevelScriptActor() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_AMainLevelScriptActor_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_AMainLevelScriptActor();
	ENGINE_API UClass* Z_Construct_UClass_ALevelScriptActor();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
	UMG_API UClass* Z_Construct_UClass_UUserWidget_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
// End Cross Module References
	void AMainLevelScriptActor::StaticRegisterNativesAMainLevelScriptActor()
	{
	}
	UClass* Z_Construct_UClass_AMainLevelScriptActor_NoRegister()
	{
		return AMainLevelScriptActor::StaticClass();
	}
	struct Z_Construct_UClass_AMainLevelScriptActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MainLevelUICanvasInstance_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_MainLevelUICanvasInstance;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MainLevelUICanvasClass_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_MainLevelUICanvasClass;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMainLevelScriptActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ALevelScriptActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMainLevelScriptActor_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "MainLevelScriptActor.h" },
		{ "ModuleRelativePath", "MainLevelScriptActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMainLevelScriptActor_Statics::NewProp_MainLevelUICanvasInstance_MetaData[] = {
		{ "Category", "UI" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MainLevelScriptActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMainLevelScriptActor_Statics::NewProp_MainLevelUICanvasInstance = { "MainLevelUICanvasInstance", nullptr, (EPropertyFlags)0x00400000000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMainLevelScriptActor, MainLevelUICanvasInstance), Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AMainLevelScriptActor_Statics::NewProp_MainLevelUICanvasInstance_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMainLevelScriptActor_Statics::NewProp_MainLevelUICanvasInstance_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMainLevelScriptActor_Statics::NewProp_MainLevelUICanvasClass_MetaData[] = {
		{ "Category", "UI" },
		{ "ModuleRelativePath", "MainLevelScriptActor.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AMainLevelScriptActor_Statics::NewProp_MainLevelUICanvasClass = { "MainLevelUICanvasClass", nullptr, (EPropertyFlags)0x0024080000020001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMainLevelScriptActor, MainLevelUICanvasClass), Z_Construct_UClass_UUserWidget_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AMainLevelScriptActor_Statics::NewProp_MainLevelUICanvasClass_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMainLevelScriptActor_Statics::NewProp_MainLevelUICanvasClass_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMainLevelScriptActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMainLevelScriptActor_Statics::NewProp_MainLevelUICanvasInstance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMainLevelScriptActor_Statics::NewProp_MainLevelUICanvasClass,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMainLevelScriptActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMainLevelScriptActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AMainLevelScriptActor_Statics::ClassParams = {
		&AMainLevelScriptActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AMainLevelScriptActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AMainLevelScriptActor_Statics::PropPointers),
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AMainLevelScriptActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AMainLevelScriptActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMainLevelScriptActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AMainLevelScriptActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AMainLevelScriptActor, 1835021898);
	template<> PROJECT_MF_API UClass* StaticClass<AMainLevelScriptActor>()
	{
		return AMainLevelScriptActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AMainLevelScriptActor(Z_Construct_UClass_AMainLevelScriptActor, &AMainLevelScriptActor::StaticClass, TEXT("/Script/Project_MF"), TEXT("AMainLevelScriptActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMainLevelScriptActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
