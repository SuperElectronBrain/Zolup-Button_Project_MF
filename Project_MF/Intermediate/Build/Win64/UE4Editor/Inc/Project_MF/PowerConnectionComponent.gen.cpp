// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/PowerConnectionComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePowerConnectionComponent() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_UPowerConnectionComponent_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_UPowerConnectionComponent();
	PROJECT_MF_API UClass* Z_Construct_UClass_UPowerComponent();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
	ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UPowerConnectionComponent::execOnOverlapEnd)
	{
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComp);
		P_GET_OBJECT(AActor,Z_Param_OtherActor);
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
		P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnOverlapEnd(Z_Param_OverlappedComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UPowerConnectionComponent::execOnOverlapBegin)
	{
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComp);
		P_GET_OBJECT(AActor,Z_Param_OtherActor);
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
		P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
		P_GET_UBOOL(Z_Param_bFromSweep);
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnOverlapBegin(Z_Param_OverlappedComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UPowerConnectionComponent::execSetPowerState)
	{
		P_GET_UBOOL(Z_Param_param);
		P_GET_UBOOL(Z_Param_IsGenerator);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetPowerState(Z_Param_param,Z_Param_IsGenerator);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UPowerConnectionComponent::execSetTriggerSize)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_param);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetTriggerSize(Z_Param_param);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UPowerConnectionComponent::execSetObjectLength)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_param);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetObjectLength(Z_Param_param);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UPowerConnectionComponent::execUpdateMaterialColor)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdateMaterialColor();
		P_NATIVE_END;
	}
	void UPowerConnectionComponent::StaticRegisterNativesUPowerConnectionComponent()
	{
		UClass* Class = UPowerConnectionComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnOverlapBegin", &UPowerConnectionComponent::execOnOverlapBegin },
			{ "OnOverlapEnd", &UPowerConnectionComponent::execOnOverlapEnd },
			{ "SetObjectLength", &UPowerConnectionComponent::execSetObjectLength },
			{ "SetPowerState", &UPowerConnectionComponent::execSetPowerState },
			{ "SetTriggerSize", &UPowerConnectionComponent::execSetTriggerSize },
			{ "UpdateMaterialColor", &UPowerConnectionComponent::execUpdateMaterialColor },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics
	{
		struct PowerConnectionComponent_eventOnOverlapBegin_Parms
		{
			UPrimitiveComponent* OverlappedComp;
			AActor* OtherActor;
			UPrimitiveComponent* OtherComp;
			int32 OtherBodyIndex;
			bool bFromSweep;
			FHitResult SweepResult;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OverlappedComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OverlappedComp;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
		static void NewProp_bFromSweep_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bFromSweep;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SweepResult_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_SweepResult;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OverlappedComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OverlappedComp = { "OverlappedComp", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PowerConnectionComponent_eventOnOverlapBegin_Parms, OverlappedComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OverlappedComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OverlappedComp_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PowerConnectionComponent_eventOnOverlapBegin_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PowerConnectionComponent_eventOnOverlapBegin_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OtherComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OtherComp_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PowerConnectionComponent_eventOnOverlapBegin_Parms, OtherBodyIndex), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_bFromSweep_SetBit(void* Obj)
	{
		((PowerConnectionComponent_eventOnOverlapBegin_Parms*)Obj)->bFromSweep = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_bFromSweep = { "bFromSweep", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(PowerConnectionComponent_eventOnOverlapBegin_Parms), &Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_bFromSweep_SetBit, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_SweepResult_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_SweepResult = { "SweepResult", nullptr, (EPropertyFlags)0x0010008008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PowerConnectionComponent_eventOnOverlapBegin_Parms, SweepResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_SweepResult_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_SweepResult_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OverlappedComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OtherActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OtherComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_OtherBodyIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_bFromSweep,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::NewProp_SweepResult,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "PowerConnectionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPowerConnectionComponent, nullptr, "OnOverlapBegin", nullptr, nullptr, sizeof(PowerConnectionComponent_eventOnOverlapBegin_Parms), Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics
	{
		struct PowerConnectionComponent_eventOnOverlapEnd_Parms
		{
			UPrimitiveComponent* OverlappedComp;
			AActor* OtherActor;
			UPrimitiveComponent* OtherComp;
			int32 OtherBodyIndex;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OverlappedComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OverlappedComp;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OverlappedComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OverlappedComp = { "OverlappedComp", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PowerConnectionComponent_eventOnOverlapEnd_Parms, OverlappedComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OverlappedComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OverlappedComp_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PowerConnectionComponent_eventOnOverlapEnd_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PowerConnectionComponent_eventOnOverlapEnd_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OtherComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OtherComp_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PowerConnectionComponent_eventOnOverlapEnd_Parms, OtherBodyIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OverlappedComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OtherActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OtherComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::NewProp_OtherBodyIndex,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "PowerConnectionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPowerConnectionComponent, nullptr, "OnOverlapEnd", nullptr, nullptr, sizeof(PowerConnectionComponent_eventOnOverlapEnd_Parms), Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UPowerConnectionComponent_SetObjectLength_Statics
	{
		struct PowerConnectionComponent_eventSetObjectLength_Parms
		{
			int32 param;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_param;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_SetObjectLength_Statics::NewProp_param = { "param", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PowerConnectionComponent_eventSetObjectLength_Parms, param), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPowerConnectionComponent_SetObjectLength_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_SetObjectLength_Statics::NewProp_param,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UPowerConnectionComponent_SetObjectLength_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "PowerConnectionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UPowerConnectionComponent_SetObjectLength_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPowerConnectionComponent, nullptr, "SetObjectLength", nullptr, nullptr, sizeof(PowerConnectionComponent_eventSetObjectLength_Parms), Z_Construct_UFunction_UPowerConnectionComponent_SetObjectLength_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_SetObjectLength_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UPowerConnectionComponent_SetObjectLength_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_SetObjectLength_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UPowerConnectionComponent_SetObjectLength()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UPowerConnectionComponent_SetObjectLength_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics
	{
		struct PowerConnectionComponent_eventSetPowerState_Parms
		{
			bool param;
			bool IsGenerator;
		};
		static void NewProp_param_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_param;
		static void NewProp_IsGenerator_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsGenerator;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::NewProp_param_SetBit(void* Obj)
	{
		((PowerConnectionComponent_eventSetPowerState_Parms*)Obj)->param = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::NewProp_param = { "param", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(PowerConnectionComponent_eventSetPowerState_Parms), &Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::NewProp_param_SetBit, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::NewProp_IsGenerator_SetBit(void* Obj)
	{
		((PowerConnectionComponent_eventSetPowerState_Parms*)Obj)->IsGenerator = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::NewProp_IsGenerator = { "IsGenerator", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(PowerConnectionComponent_eventSetPowerState_Parms), &Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::NewProp_IsGenerator_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::NewProp_param,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::NewProp_IsGenerator,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "PowerConnectionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPowerConnectionComponent, nullptr, "SetPowerState", nullptr, nullptr, sizeof(PowerConnectionComponent_eventSetPowerState_Parms), Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UPowerConnectionComponent_SetTriggerSize_Statics
	{
		struct PowerConnectionComponent_eventSetTriggerSize_Parms
		{
			int32 param;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_param;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UPowerConnectionComponent_SetTriggerSize_Statics::NewProp_param = { "param", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PowerConnectionComponent_eventSetTriggerSize_Parms, param), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPowerConnectionComponent_SetTriggerSize_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPowerConnectionComponent_SetTriggerSize_Statics::NewProp_param,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UPowerConnectionComponent_SetTriggerSize_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "PowerConnectionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UPowerConnectionComponent_SetTriggerSize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPowerConnectionComponent, nullptr, "SetTriggerSize", nullptr, nullptr, sizeof(PowerConnectionComponent_eventSetTriggerSize_Parms), Z_Construct_UFunction_UPowerConnectionComponent_SetTriggerSize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_SetTriggerSize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UPowerConnectionComponent_SetTriggerSize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_SetTriggerSize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UPowerConnectionComponent_SetTriggerSize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UPowerConnectionComponent_SetTriggerSize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UPowerConnectionComponent_UpdateMaterialColor_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UPowerConnectionComponent_UpdateMaterialColor_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Called every frame\n//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;\n" },
		{ "ModuleRelativePath", "PowerConnectionComponent.h" },
		{ "ToolTip", "Called every frame\nvirtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UPowerConnectionComponent_UpdateMaterialColor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPowerConnectionComponent, nullptr, "UpdateMaterialColor", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UPowerConnectionComponent_UpdateMaterialColor_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UPowerConnectionComponent_UpdateMaterialColor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UPowerConnectionComponent_UpdateMaterialColor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UPowerConnectionComponent_UpdateMaterialColor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UPowerConnectionComponent_NoRegister()
	{
		return UPowerConnectionComponent::StaticClass();
	}
	struct Z_Construct_UClass_UPowerConnectionComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Meshs_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Meshs_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Meshs;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Colliders_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Colliders_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Colliders;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Triggers_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Triggers_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Triggers;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ObjectLength_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ObjectLength;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UPowerConnectionComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UPowerComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UPowerConnectionComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapBegin, "OnOverlapBegin" }, // 2860824405
		{ &Z_Construct_UFunction_UPowerConnectionComponent_OnOverlapEnd, "OnOverlapEnd" }, // 3388208389
		{ &Z_Construct_UFunction_UPowerConnectionComponent_SetObjectLength, "SetObjectLength" }, // 4033917726
		{ &Z_Construct_UFunction_UPowerConnectionComponent_SetPowerState, "SetPowerState" }, // 958260361
		{ &Z_Construct_UFunction_UPowerConnectionComponent_SetTriggerSize, "SetTriggerSize" }, // 2752693993
		{ &Z_Construct_UFunction_UPowerConnectionComponent_UpdateMaterialColor, "UpdateMaterialColor" }, // 2495777075
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerConnectionComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Power" },
		{ "HideCategories", "Object LOD Lighting TextureStreaming Object LOD Lighting TextureStreaming Activation Components|Activation Trigger VirtualTexture" },
		{ "IncludePath", "PowerConnectionComponent.h" },
		{ "ModuleRelativePath", "PowerConnectionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Meshs_Inner = { "Meshs", nullptr, (EPropertyFlags)0x00000000000a0008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Meshs_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "PowerConnectionComponent" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "PowerConnectionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Meshs = { "Meshs", nullptr, (EPropertyFlags)0x004000800002200d, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UPowerConnectionComponent, Meshs), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Meshs_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Meshs_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Colliders_Inner = { "Colliders", nullptr, (EPropertyFlags)0x00000000000a0008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Colliders_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "PowerConnectionComponent" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "PowerConnectionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Colliders = { "Colliders", nullptr, (EPropertyFlags)0x004000800002200d, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UPowerConnectionComponent, Colliders), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Colliders_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Colliders_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Triggers_Inner = { "Triggers", nullptr, (EPropertyFlags)0x00000000000a0008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Triggers_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "PowerConnectionComponent" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "PowerConnectionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Triggers = { "Triggers", nullptr, (EPropertyFlags)0x004000800002200d, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UPowerConnectionComponent, Triggers), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Triggers_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Triggers_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_ObjectLength_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "PowerConnectionComponent" },
		{ "ModuleRelativePath", "PowerConnectionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_ObjectLength = { "ObjectLength", nullptr, (EPropertyFlags)0x0040000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UPowerConnectionComponent, ObjectLength), METADATA_PARAMS(Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_ObjectLength_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_ObjectLength_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UPowerConnectionComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Meshs_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Meshs,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Colliders_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Colliders,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Triggers_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_Triggers,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerConnectionComponent_Statics::NewProp_ObjectLength,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UPowerConnectionComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPowerConnectionComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UPowerConnectionComponent_Statics::ClassParams = {
		&UPowerConnectionComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UPowerConnectionComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UPowerConnectionComponent_Statics::PropPointers),
		0,
		0x00B010A4u,
		METADATA_PARAMS(Z_Construct_UClass_UPowerConnectionComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerConnectionComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UPowerConnectionComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UPowerConnectionComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UPowerConnectionComponent, 274055673);
	template<> PROJECT_MF_API UClass* StaticClass<UPowerConnectionComponent>()
	{
		return UPowerConnectionComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UPowerConnectionComponent(Z_Construct_UClass_UPowerConnectionComponent, &UPowerConnectionComponent::StaticClass, TEXT("/Script/Project_MF"), TEXT("UPowerConnectionComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UPowerConnectionComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
