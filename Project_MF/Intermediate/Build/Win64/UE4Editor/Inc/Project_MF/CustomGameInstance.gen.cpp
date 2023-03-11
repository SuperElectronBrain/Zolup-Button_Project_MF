// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/CustomGameInstance.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCustomGameInstance() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_UCustomGameInstance_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_UCustomGameInstance();
	ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
// End Cross Module References
	void UCustomGameInstance::StaticRegisterNativesUCustomGameInstance()
	{
	}
	UClass* Z_Construct_UClass_UCustomGameInstance_NoRegister()
	{
		return UCustomGameInstance::StaticClass();
	}
	struct Z_Construct_UClass_UCustomGameInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEditmode_MetaData[];
#endif
		static void NewProp_bEditmode_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEditmode;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCustomGameInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomGameInstance_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "CustomGameInstance.h" },
		{ "ModuleRelativePath", "CustomGameInstance.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomGameInstance_Statics::NewProp_bEditmode_MetaData[] = {
		{ "Category", "CustomGameInstance" },
		{ "ModuleRelativePath", "CustomGameInstance.h" },
	};
#endif
	void Z_Construct_UClass_UCustomGameInstance_Statics::NewProp_bEditmode_SetBit(void* Obj)
	{
		((UCustomGameInstance*)Obj)->bEditmode = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCustomGameInstance_Statics::NewProp_bEditmode = { "bEditmode", nullptr, (EPropertyFlags)0x0040000000020001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCustomGameInstance), &Z_Construct_UClass_UCustomGameInstance_Statics::NewProp_bEditmode_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCustomGameInstance_Statics::NewProp_bEditmode_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCustomGameInstance_Statics::NewProp_bEditmode_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCustomGameInstance_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomGameInstance_Statics::NewProp_bEditmode,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCustomGameInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCustomGameInstance>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCustomGameInstance_Statics::ClassParams = {
		&UCustomGameInstance::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCustomGameInstance_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCustomGameInstance_Statics::PropPointers),
		0,
		0x009000A8u,
		METADATA_PARAMS(Z_Construct_UClass_UCustomGameInstance_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCustomGameInstance_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCustomGameInstance()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCustomGameInstance_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCustomGameInstance, 901655515);
	template<> PROJECT_MF_API UClass* StaticClass<UCustomGameInstance>()
	{
		return UCustomGameInstance::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCustomGameInstance(Z_Construct_UClass_UCustomGameInstance, &UCustomGameInstance::StaticClass, TEXT("/Script/Project_MF"), TEXT("UCustomGameInstance"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCustomGameInstance);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
