// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/MainLevelPawn.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMainLevelPawn() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_AMainLevelPawn_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_AMainLevelPawn();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
// End Cross Module References
	void AMainLevelPawn::StaticRegisterNativesAMainLevelPawn()
	{
	}
	UClass* Z_Construct_UClass_AMainLevelPawn_NoRegister()
	{
		return AMainLevelPawn::StaticClass();
	}
	struct Z_Construct_UClass_AMainLevelPawn_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMainLevelPawn_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMainLevelPawn_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "MainLevelPawn.h" },
		{ "ModuleRelativePath", "MainLevelPawn.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMainLevelPawn_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMainLevelPawn>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AMainLevelPawn_Statics::ClassParams = {
		&AMainLevelPawn::StaticClass,
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
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AMainLevelPawn_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AMainLevelPawn_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMainLevelPawn()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AMainLevelPawn_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AMainLevelPawn, 2630463174);
	template<> PROJECT_MF_API UClass* StaticClass<AMainLevelPawn>()
	{
		return AMainLevelPawn::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AMainLevelPawn(Z_Construct_UClass_AMainLevelPawn, &AMainLevelPawn::StaticClass, TEXT("/Script/Project_MF"), TEXT("AMainLevelPawn"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMainLevelPawn);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
