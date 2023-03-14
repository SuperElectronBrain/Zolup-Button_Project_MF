// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/EditLevelScriptActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEditLevelScriptActor() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_AEditLevelScriptActor_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_AEditLevelScriptActor();
	ENGINE_API UClass* Z_Construct_UClass_ALevelScriptActor();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
// End Cross Module References
	void AEditLevelScriptActor::StaticRegisterNativesAEditLevelScriptActor()
	{
	}
	UClass* Z_Construct_UClass_AEditLevelScriptActor_NoRegister()
	{
		return AEditLevelScriptActor::StaticClass();
	}
	struct Z_Construct_UClass_AEditLevelScriptActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AEditLevelScriptActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ALevelScriptActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEditLevelScriptActor_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "EditLevelScriptActor.h" },
		{ "ModuleRelativePath", "EditLevelScriptActor.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEditLevelScriptActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEditLevelScriptActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AEditLevelScriptActor_Statics::ClassParams = {
		&AEditLevelScriptActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AEditLevelScriptActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AEditLevelScriptActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AEditLevelScriptActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AEditLevelScriptActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AEditLevelScriptActor, 1434398291);
	template<> PROJECT_MF_API UClass* StaticClass<AEditLevelScriptActor>()
	{
		return AEditLevelScriptActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AEditLevelScriptActor(Z_Construct_UClass_AEditLevelScriptActor, &AEditLevelScriptActor::StaticClass, TEXT("/Script/Project_MF"), TEXT("AEditLevelScriptActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEditLevelScriptActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
