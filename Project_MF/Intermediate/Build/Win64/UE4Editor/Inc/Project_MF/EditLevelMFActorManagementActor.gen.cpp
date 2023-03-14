// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/EditLevelMFActorManagementActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEditLevelMFActorManagementActor() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_AEditLevelMFActorManagementActor_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_AEditLevelMFActorManagementActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
	PROJECT_MF_API UClass* Z_Construct_UClass_AMFActor_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(AEditLevelMFActorManagementActor::execSpawnMFActor)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SpawnMFActor();
		P_NATIVE_END;
	}
	void AEditLevelMFActorManagementActor::StaticRegisterNativesAEditLevelMFActorManagementActor()
	{
		UClass* Class = AEditLevelMFActorManagementActor::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SpawnMFActor", &AEditLevelMFActorManagementActor::execSpawnMFActor },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AEditLevelMFActorManagementActor_SpawnMFActor_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEditLevelMFActorManagementActor_SpawnMFActor_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "EditLevelMFActorManagementActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AEditLevelMFActorManagementActor_SpawnMFActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AEditLevelMFActorManagementActor, nullptr, "SpawnMFActor", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AEditLevelMFActorManagementActor_SpawnMFActor_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AEditLevelMFActorManagementActor_SpawnMFActor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AEditLevelMFActorManagementActor_SpawnMFActor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AEditLevelMFActorManagementActor_SpawnMFActor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AEditLevelMFActorManagementActor_NoRegister()
	{
		return AEditLevelMFActorManagementActor::StaticClass();
	}
	struct Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ActorCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ActorCount;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_MFActorsArray_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MFActorsArray_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_MFActorsArray;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AEditLevelMFActorManagementActor_SpawnMFActor, "SpawnMFActor" }, // 17170717
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "EditLevelMFActorManagementActor.h" },
		{ "ModuleRelativePath", "EditLevelMFActorManagementActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::NewProp_ActorCount_MetaData[] = {
		{ "ModuleRelativePath", "EditLevelMFActorManagementActor.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::NewProp_ActorCount = { "ActorCount", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AEditLevelMFActorManagementActor, ActorCount), METADATA_PARAMS(Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::NewProp_ActorCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::NewProp_ActorCount_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::NewProp_MFActorsArray_Inner = { "MFActorsArray", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_AMFActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::NewProp_MFActorsArray_MetaData[] = {
		{ "ModuleRelativePath", "EditLevelMFActorManagementActor.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::NewProp_MFActorsArray = { "MFActorsArray", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AEditLevelMFActorManagementActor, MFActorsArray), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::NewProp_MFActorsArray_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::NewProp_MFActorsArray_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::NewProp_ActorCount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::NewProp_MFActorsArray_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::NewProp_MFActorsArray,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEditLevelMFActorManagementActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::ClassParams = {
		&AEditLevelMFActorManagementActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AEditLevelMFActorManagementActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AEditLevelMFActorManagementActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AEditLevelMFActorManagementActor, 2479419646);
	template<> PROJECT_MF_API UClass* StaticClass<AEditLevelMFActorManagementActor>()
	{
		return AEditLevelMFActorManagementActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AEditLevelMFActorManagementActor(Z_Construct_UClass_AEditLevelMFActorManagementActor, &AEditLevelMFActorManagementActor::StaticClass, TEXT("/Script/Project_MF"), TEXT("AEditLevelMFActorManagementActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEditLevelMFActorManagementActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
