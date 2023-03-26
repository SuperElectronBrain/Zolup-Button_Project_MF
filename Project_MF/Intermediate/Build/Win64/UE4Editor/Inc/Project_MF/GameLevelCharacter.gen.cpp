// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/GameLevelCharacter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameLevelCharacter() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_AGameLevelCharacter_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_AGameLevelCharacter();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
// End Cross Module References
	void AGameLevelCharacter::StaticRegisterNativesAGameLevelCharacter()
	{
	}
	UClass* Z_Construct_UClass_AGameLevelCharacter_NoRegister()
	{
		return AGameLevelCharacter::StaticClass();
	}
	struct Z_Construct_UClass_AGameLevelCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Camera;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGameLevelCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGameLevelCharacter_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "GameLevelCharacter.h" },
		{ "ModuleRelativePath", "GameLevelCharacter.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGameLevelCharacter_Statics::NewProp_Camera_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "GameLevelCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGameLevelCharacter_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGameLevelCharacter, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AGameLevelCharacter_Statics::NewProp_Camera_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGameLevelCharacter_Statics::NewProp_Camera_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AGameLevelCharacter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGameLevelCharacter_Statics::NewProp_Camera,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGameLevelCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGameLevelCharacter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AGameLevelCharacter_Statics::ClassParams = {
		&AGameLevelCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AGameLevelCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AGameLevelCharacter_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AGameLevelCharacter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AGameLevelCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGameLevelCharacter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGameLevelCharacter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGameLevelCharacter, 804774558);
	template<> PROJECT_MF_API UClass* StaticClass<AGameLevelCharacter>()
	{
		return AGameLevelCharacter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGameLevelCharacter(Z_Construct_UClass_AGameLevelCharacter, &AGameLevelCharacter::StaticClass, TEXT("/Script/Project_MF"), TEXT("AGameLevelCharacter"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGameLevelCharacter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
