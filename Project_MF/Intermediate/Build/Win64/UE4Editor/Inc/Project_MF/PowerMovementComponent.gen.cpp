// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/PowerMovementComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePowerMovementComponent() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_UPowerMovementComponent_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_UPowerMovementComponent();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
// End Cross Module References
	DEFINE_FUNCTION(UPowerMovementComponent::execEndAction)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->EndAction();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UPowerMovementComponent::execStartAction)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StartAction();
		P_NATIVE_END;
	}
	void UPowerMovementComponent::StaticRegisterNativesUPowerMovementComponent()
	{
		UClass* Class = UPowerMovementComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "EndAction", &UPowerMovementComponent::execEndAction },
			{ "StartAction", &UPowerMovementComponent::execStartAction },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UPowerMovementComponent_EndAction_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UPowerMovementComponent_EndAction_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "PowerMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UPowerMovementComponent_EndAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPowerMovementComponent, nullptr, "EndAction", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UPowerMovementComponent_EndAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerMovementComponent_EndAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UPowerMovementComponent_EndAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UPowerMovementComponent_EndAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UPowerMovementComponent_StartAction_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UPowerMovementComponent_StartAction_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "PowerMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UPowerMovementComponent_StartAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPowerMovementComponent, nullptr, "StartAction", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UPowerMovementComponent_StartAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerMovementComponent_StartAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UPowerMovementComponent_StartAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UPowerMovementComponent_StartAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UPowerMovementComponent_NoRegister()
	{
		return UPowerMovementComponent::StaticClass();
	}
	struct Z_Construct_UClass_UPowerMovementComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ActingRange_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ActingRange;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ActingSpeed_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ActingSpeed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OriginPosition_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_OriginPosition;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrentMovement_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_CurrentMovement;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bActingState_MetaData[];
#endif
		static void NewProp_bActingState_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bActingState;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UPowerMovementComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UPowerMovementComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UPowerMovementComponent_EndAction, "EndAction" }, // 2738103295
		{ &Z_Construct_UFunction_UPowerMovementComponent_StartAction, "StartAction" }, // 1372062703
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerMovementComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "PowerMovementComponent.h" },
		{ "ModuleRelativePath", "PowerMovementComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_ActingRange_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "PowerMovementComponent" },
		{ "ModuleRelativePath", "PowerMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_ActingRange = { "ActingRange", nullptr, (EPropertyFlags)0x0040000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UPowerMovementComponent, ActingRange), METADATA_PARAMS(Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_ActingRange_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_ActingRange_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_ActingSpeed_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "PowerMovementComponent" },
		{ "ModuleRelativePath", "PowerMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_ActingSpeed = { "ActingSpeed", nullptr, (EPropertyFlags)0x0040000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UPowerMovementComponent, ActingSpeed), METADATA_PARAMS(Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_ActingSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_ActingSpeed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_OriginPosition_MetaData[] = {
		{ "ModuleRelativePath", "PowerMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_OriginPosition = { "OriginPosition", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UPowerMovementComponent, OriginPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_OriginPosition_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_OriginPosition_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_CurrentMovement_MetaData[] = {
		{ "ModuleRelativePath", "PowerMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_CurrentMovement = { "CurrentMovement", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UPowerMovementComponent, CurrentMovement), METADATA_PARAMS(Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_CurrentMovement_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_CurrentMovement_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_bActingState_MetaData[] = {
		{ "ModuleRelativePath", "PowerMovementComponent.h" },
	};
#endif
	void Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_bActingState_SetBit(void* Obj)
	{
		((UPowerMovementComponent*)Obj)->bActingState = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_bActingState = { "bActingState", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UPowerMovementComponent), &Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_bActingState_SetBit, METADATA_PARAMS(Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_bActingState_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_bActingState_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UPowerMovementComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_ActingRange,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_ActingSpeed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_OriginPosition,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_CurrentMovement,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerMovementComponent_Statics::NewProp_bActingState,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UPowerMovementComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPowerMovementComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UPowerMovementComponent_Statics::ClassParams = {
		&UPowerMovementComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UPowerMovementComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UPowerMovementComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UPowerMovementComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerMovementComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UPowerMovementComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UPowerMovementComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UPowerMovementComponent, 2624436407);
	template<> PROJECT_MF_API UClass* StaticClass<UPowerMovementComponent>()
	{
		return UPowerMovementComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UPowerMovementComponent(Z_Construct_UClass_UPowerMovementComponent, &UPowerMovementComponent::StaticClass, TEXT("/Script/Project_MF"), TEXT("UPowerMovementComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UPowerMovementComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
