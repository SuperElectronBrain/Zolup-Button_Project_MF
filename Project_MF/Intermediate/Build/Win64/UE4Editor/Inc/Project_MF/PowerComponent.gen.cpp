// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/PowerComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePowerComponent() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_UPowerComponent_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_UPowerComponent();
	ENGINE_API UClass* Z_Construct_UClass_UBoxComponent();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UMaterial_NoRegister();
// End Cross Module References
	void UPowerComponent::StaticRegisterNativesUPowerComponent()
	{
	}
	UClass* Z_Construct_UClass_UPowerComponent_NoRegister()
	{
		return UPowerComponent::StaticClass();
	}
	struct Z_Construct_UClass_UPowerComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MeshOrigin_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_MeshOrigin;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaterialOrigin_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_MaterialOrigin;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TriggerSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_TriggerSize;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bPowerState_MetaData[];
#endif
		static void NewProp_bPowerState_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bPowerState;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UPowerComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBoxComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerComponent_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Object LOD Lighting TextureStreaming Object LOD Lighting TextureStreaming Activation Components|Activation Trigger VirtualTexture" },
		{ "IncludePath", "PowerComponent.h" },
		{ "ModuleRelativePath", "PowerComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerComponent_Statics::NewProp_MeshOrigin_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "PowerComponent" },
		{ "ModuleRelativePath", "PowerComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPowerComponent_Statics::NewProp_MeshOrigin = { "MeshOrigin", nullptr, (EPropertyFlags)0x0020080000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UPowerComponent, MeshOrigin), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UPowerComponent_Statics::NewProp_MeshOrigin_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerComponent_Statics::NewProp_MeshOrigin_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerComponent_Statics::NewProp_MaterialOrigin_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "PowerComponent" },
		{ "ModuleRelativePath", "PowerComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPowerComponent_Statics::NewProp_MaterialOrigin = { "MaterialOrigin", nullptr, (EPropertyFlags)0x0020080000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UPowerComponent, MaterialOrigin), Z_Construct_UClass_UMaterial_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UPowerComponent_Statics::NewProp_MaterialOrigin_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerComponent_Statics::NewProp_MaterialOrigin_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerComponent_Statics::NewProp_TriggerSize_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "PowerComponent" },
		{ "ModuleRelativePath", "PowerComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UPowerComponent_Statics::NewProp_TriggerSize = { "TriggerSize", nullptr, (EPropertyFlags)0x0020080000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UPowerComponent, TriggerSize), METADATA_PARAMS(Z_Construct_UClass_UPowerComponent_Statics::NewProp_TriggerSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerComponent_Statics::NewProp_TriggerSize_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPowerComponent_Statics::NewProp_bPowerState_MetaData[] = {
		{ "Category", "PowerComponent" },
		{ "ModuleRelativePath", "PowerComponent.h" },
	};
#endif
	void Z_Construct_UClass_UPowerComponent_Statics::NewProp_bPowerState_SetBit(void* Obj)
	{
		((UPowerComponent*)Obj)->bPowerState = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UPowerComponent_Statics::NewProp_bPowerState = { "bPowerState", nullptr, (EPropertyFlags)0x0020080000020001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UPowerComponent), &Z_Construct_UClass_UPowerComponent_Statics::NewProp_bPowerState_SetBit, METADATA_PARAMS(Z_Construct_UClass_UPowerComponent_Statics::NewProp_bPowerState_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerComponent_Statics::NewProp_bPowerState_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UPowerComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerComponent_Statics::NewProp_MeshOrigin,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerComponent_Statics::NewProp_MaterialOrigin,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerComponent_Statics::NewProp_TriggerSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPowerComponent_Statics::NewProp_bPowerState,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UPowerComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPowerComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UPowerComponent_Statics::ClassParams = {
		&UPowerComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UPowerComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UPowerComponent_Statics::PropPointers),
		0,
		0x00B010A4u,
		METADATA_PARAMS(Z_Construct_UClass_UPowerComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UPowerComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UPowerComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UPowerComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UPowerComponent, 3600130190);
	template<> PROJECT_MF_API UClass* StaticClass<UPowerComponent>()
	{
		return UPowerComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UPowerComponent(Z_Construct_UClass_UPowerComponent, &UPowerComponent::StaticClass, TEXT("/Script/Project_MF"), TEXT("UPowerComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UPowerComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
