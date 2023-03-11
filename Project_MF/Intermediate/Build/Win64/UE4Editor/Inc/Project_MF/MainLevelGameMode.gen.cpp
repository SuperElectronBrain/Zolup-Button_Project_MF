// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/MainLevelGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMainLevelGameMode() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_AMainLevelGameMode_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_AMainLevelGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
// End Cross Module References
	void AMainLevelGameMode::StaticRegisterNativesAMainLevelGameMode()
	{
	}
	UClass* Z_Construct_UClass_AMainLevelGameMode_NoRegister()
	{
		return AMainLevelGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AMainLevelGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMainLevelGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMainLevelGameMode_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "MainLevelGameMode.h" },
		{ "ModuleRelativePath", "MainLevelGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMainLevelGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMainLevelGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AMainLevelGameMode_Statics::ClassParams = {
		&AMainLevelGameMode::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_AMainLevelGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AMainLevelGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMainLevelGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AMainLevelGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AMainLevelGameMode, 399231879);
	template<> PROJECT_MF_API UClass* StaticClass<AMainLevelGameMode>()
	{
		return AMainLevelGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AMainLevelGameMode(Z_Construct_UClass_AMainLevelGameMode, &AMainLevelGameMode::StaticClass, TEXT("/Script/Project_MF"), TEXT("AMainLevelGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMainLevelGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
