// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/MainLevelPawnController.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMainLevelPawnController() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_AMainLevelPawnController_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_AMainLevelPawnController();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
// End Cross Module References
	void AMainLevelPawnController::StaticRegisterNativesAMainLevelPawnController()
	{
	}
	UClass* Z_Construct_UClass_AMainLevelPawnController_NoRegister()
	{
		return AMainLevelPawnController::StaticClass();
	}
	struct Z_Construct_UClass_AMainLevelPawnController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMainLevelPawnController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMainLevelPawnController_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "MainLevelPawnController.h" },
		{ "ModuleRelativePath", "MainLevelPawnController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMainLevelPawnController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMainLevelPawnController>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AMainLevelPawnController_Statics::ClassParams = {
		&AMainLevelPawnController::StaticClass,
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
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AMainLevelPawnController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AMainLevelPawnController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMainLevelPawnController()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AMainLevelPawnController_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AMainLevelPawnController, 575889002);
	template<> PROJECT_MF_API UClass* StaticClass<AMainLevelPawnController>()
	{
		return AMainLevelPawnController::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AMainLevelPawnController(Z_Construct_UClass_AMainLevelPawnController, &AMainLevelPawnController::StaticClass, TEXT("/Script/Project_MF"), TEXT("AMainLevelPawnController"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMainLevelPawnController);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
