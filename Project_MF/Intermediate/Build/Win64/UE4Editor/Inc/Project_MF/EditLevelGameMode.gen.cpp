// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/EditLevelGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEditLevelGameMode() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_AEditLevelGameMode_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_AEditLevelGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
// End Cross Module References
	void AEditLevelGameMode::StaticRegisterNativesAEditLevelGameMode()
	{
	}
	UClass* Z_Construct_UClass_AEditLevelGameMode_NoRegister()
	{
		return AEditLevelGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AEditLevelGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AEditLevelGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEditLevelGameMode_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "EditLevelGameMode.h" },
		{ "ModuleRelativePath", "EditLevelGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEditLevelGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEditLevelGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AEditLevelGameMode_Statics::ClassParams = {
		&AEditLevelGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AEditLevelGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AEditLevelGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AEditLevelGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AEditLevelGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AEditLevelGameMode, 3482600202);
	template<> PROJECT_MF_API UClass* StaticClass<AEditLevelGameMode>()
	{
		return AEditLevelGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AEditLevelGameMode(Z_Construct_UClass_AEditLevelGameMode, &AEditLevelGameMode::StaticClass, TEXT("/Script/Project_MF"), TEXT("AEditLevelGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEditLevelGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
