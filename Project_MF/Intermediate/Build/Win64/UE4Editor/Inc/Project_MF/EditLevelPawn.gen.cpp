// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/EditLevelPawn.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEditLevelPawn() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_AEditLevelPawn_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_AEditLevelPawn();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
	PROJECT_MF_API UClass* Z_Construct_UClass_AEditLevelMFActorManagementActor_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UFloatingPawnMovement_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(AEditLevelPawn::execSetEditLevelMFActorManagementActor)
	{
		P_GET_OBJECT(AEditLevelMFActorManagementActor,Z_Param_param);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetEditLevelMFActorManagementActor(Z_Param_param);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AEditLevelPawn::execHorizontalMovement)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_param);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->HorizontalMovement(Z_Param_param);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AEditLevelPawn::execVerticalMovement)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_param);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->VerticalMovement(Z_Param_param);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AEditLevelPawn::execSpawnMFActor)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SpawnMFActor();
		P_NATIVE_END;
	}
	void AEditLevelPawn::StaticRegisterNativesAEditLevelPawn()
	{
		UClass* Class = AEditLevelPawn::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "HorizontalMovement", &AEditLevelPawn::execHorizontalMovement },
			{ "SetEditLevelMFActorManagementActor", &AEditLevelPawn::execSetEditLevelMFActorManagementActor },
			{ "SpawnMFActor", &AEditLevelPawn::execSpawnMFActor },
			{ "VerticalMovement", &AEditLevelPawn::execVerticalMovement },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AEditLevelPawn_HorizontalMovement_Statics
	{
		struct EditLevelPawn_eventHorizontalMovement_Parms
		{
			float param;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_param;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AEditLevelPawn_HorizontalMovement_Statics::NewProp_param = { "param", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(EditLevelPawn_eventHorizontalMovement_Parms, param), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEditLevelPawn_HorizontalMovement_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEditLevelPawn_HorizontalMovement_Statics::NewProp_param,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEditLevelPawn_HorizontalMovement_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "EditLevelPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AEditLevelPawn_HorizontalMovement_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AEditLevelPawn, nullptr, "HorizontalMovement", nullptr, nullptr, sizeof(EditLevelPawn_eventHorizontalMovement_Parms), Z_Construct_UFunction_AEditLevelPawn_HorizontalMovement_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEditLevelPawn_HorizontalMovement_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AEditLevelPawn_HorizontalMovement_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AEditLevelPawn_HorizontalMovement_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AEditLevelPawn_HorizontalMovement()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AEditLevelPawn_HorizontalMovement_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AEditLevelPawn_SetEditLevelMFActorManagementActor_Statics
	{
		struct EditLevelPawn_eventSetEditLevelMFActorManagementActor_Parms
		{
			AEditLevelMFActorManagementActor* param;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_param;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AEditLevelPawn_SetEditLevelMFActorManagementActor_Statics::NewProp_param = { "param", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(EditLevelPawn_eventSetEditLevelMFActorManagementActor_Parms, param), Z_Construct_UClass_AEditLevelMFActorManagementActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEditLevelPawn_SetEditLevelMFActorManagementActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEditLevelPawn_SetEditLevelMFActorManagementActor_Statics::NewProp_param,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEditLevelPawn_SetEditLevelMFActorManagementActor_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "EditLevelPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AEditLevelPawn_SetEditLevelMFActorManagementActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AEditLevelPawn, nullptr, "SetEditLevelMFActorManagementActor", nullptr, nullptr, sizeof(EditLevelPawn_eventSetEditLevelMFActorManagementActor_Parms), Z_Construct_UFunction_AEditLevelPawn_SetEditLevelMFActorManagementActor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEditLevelPawn_SetEditLevelMFActorManagementActor_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AEditLevelPawn_SetEditLevelMFActorManagementActor_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AEditLevelPawn_SetEditLevelMFActorManagementActor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AEditLevelPawn_SetEditLevelMFActorManagementActor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AEditLevelPawn_SetEditLevelMFActorManagementActor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AEditLevelPawn_SpawnMFActor_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEditLevelPawn_SpawnMFActor_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "EditLevelPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AEditLevelPawn_SpawnMFActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AEditLevelPawn, nullptr, "SpawnMFActor", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AEditLevelPawn_SpawnMFActor_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AEditLevelPawn_SpawnMFActor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AEditLevelPawn_SpawnMFActor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AEditLevelPawn_SpawnMFActor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AEditLevelPawn_VerticalMovement_Statics
	{
		struct EditLevelPawn_eventVerticalMovement_Parms
		{
			float param;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_param;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AEditLevelPawn_VerticalMovement_Statics::NewProp_param = { "param", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(EditLevelPawn_eventVerticalMovement_Parms, param), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEditLevelPawn_VerticalMovement_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEditLevelPawn_VerticalMovement_Statics::NewProp_param,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEditLevelPawn_VerticalMovement_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "EditLevelPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AEditLevelPawn_VerticalMovement_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AEditLevelPawn, nullptr, "VerticalMovement", nullptr, nullptr, sizeof(EditLevelPawn_eventVerticalMovement_Parms), Z_Construct_UFunction_AEditLevelPawn_VerticalMovement_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEditLevelPawn_VerticalMovement_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AEditLevelPawn_VerticalMovement_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AEditLevelPawn_VerticalMovement_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AEditLevelPawn_VerticalMovement()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AEditLevelPawn_VerticalMovement_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AEditLevelPawn_NoRegister()
	{
		return AEditLevelPawn::StaticClass();
	}
	struct Z_Construct_UClass_AEditLevelPawn_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EditLevelMFActorManagementActor_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_EditLevelMFActorManagementActor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DefaultComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_DefaultComponent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Movement_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Movement;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AEditLevelPawn_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AEditLevelPawn_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AEditLevelPawn_HorizontalMovement, "HorizontalMovement" }, // 113393782
		{ &Z_Construct_UFunction_AEditLevelPawn_SetEditLevelMFActorManagementActor, "SetEditLevelMFActorManagementActor" }, // 1145552032
		{ &Z_Construct_UFunction_AEditLevelPawn_SpawnMFActor, "SpawnMFActor" }, // 1229897770
		{ &Z_Construct_UFunction_AEditLevelPawn_VerticalMovement, "VerticalMovement" }, // 482562048
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEditLevelPawn_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "EditLevelPawn.h" },
		{ "ModuleRelativePath", "EditLevelPawn.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_EditLevelMFActorManagementActor_MetaData[] = {
		{ "ModuleRelativePath", "EditLevelPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_EditLevelMFActorManagementActor = { "EditLevelMFActorManagementActor", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AEditLevelPawn, EditLevelMFActorManagementActor), Z_Construct_UClass_AEditLevelMFActorManagementActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_EditLevelMFActorManagementActor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_EditLevelMFActorManagementActor_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_DefaultComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "EditLevelPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_DefaultComponent = { "DefaultComponent", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AEditLevelPawn, DefaultComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_DefaultComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_DefaultComponent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_Movement_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "EditLevelPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_Movement = { "Movement", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AEditLevelPawn, Movement), Z_Construct_UClass_UFloatingPawnMovement_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_Movement_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_Movement_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEditLevelPawn_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_EditLevelMFActorManagementActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_DefaultComponent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEditLevelPawn_Statics::NewProp_Movement,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEditLevelPawn_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEditLevelPawn>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AEditLevelPawn_Statics::ClassParams = {
		&AEditLevelPawn::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AEditLevelPawn_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AEditLevelPawn_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AEditLevelPawn_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AEditLevelPawn_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AEditLevelPawn()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AEditLevelPawn_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AEditLevelPawn, 2711054294);
	template<> PROJECT_MF_API UClass* StaticClass<AEditLevelPawn>()
	{
		return AEditLevelPawn::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AEditLevelPawn(Z_Construct_UClass_AEditLevelPawn, &AEditLevelPawn::StaticClass, TEXT("/Script/Project_MF"), TEXT("AEditLevelPawn"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEditLevelPawn);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
