// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/Project_MFGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProject_MFGameModeBase() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_AProject_MFGameModeBase_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_AProject_MFGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
// End Cross Module References
	void AProject_MFGameModeBase::StaticRegisterNativesAProject_MFGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_AProject_MFGameModeBase_NoRegister()
	{
		return AProject_MFGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AProject_MFGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AProject_MFGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_MFGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "Project_MFGameModeBase.h" },
		{ "ModuleRelativePath", "Project_MFGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AProject_MFGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProject_MFGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AProject_MFGameModeBase_Statics::ClassParams = {
		&AProject_MFGameModeBase::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_AProject_MFGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AProject_MFGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AProject_MFGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AProject_MFGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AProject_MFGameModeBase, 914341745);
	template<> PROJECT_MF_API UClass* StaticClass<AProject_MFGameModeBase>()
	{
		return AProject_MFGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AProject_MFGameModeBase(Z_Construct_UClass_AProject_MFGameModeBase, &AProject_MFGameModeBase::StaticClass, TEXT("/Script/Project_MF"), TEXT("AProject_MFGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AProject_MFGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
