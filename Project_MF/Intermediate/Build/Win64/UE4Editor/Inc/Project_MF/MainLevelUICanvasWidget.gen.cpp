// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_MF/MainLevelUICanvasWidget.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMainLevelUICanvasWidget() {}
// Cross Module References
	PROJECT_MF_API UClass* Z_Construct_UClass_UMainLevelUICanvasWidget_NoRegister();
	PROJECT_MF_API UClass* Z_Construct_UClass_UMainLevelUICanvasWidget();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_Project_MF();
	UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UMainLevelUICanvasWidget::execOnEditButtonClicked)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnEditButtonClicked();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMainLevelUICanvasWidget::execOnQuitButtonClicked)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnQuitButtonClicked();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMainLevelUICanvasWidget::execOnStartButtonClicked)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnStartButtonClicked();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMainLevelUICanvasWidget::execEnterEditMode)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->EnterEditMode();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMainLevelUICanvasWidget::execGameStart)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GameStart();
		P_NATIVE_END;
	}
	void UMainLevelUICanvasWidget::StaticRegisterNativesUMainLevelUICanvasWidget()
	{
		UClass* Class = UMainLevelUICanvasWidget::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "EnterEditMode", &UMainLevelUICanvasWidget::execEnterEditMode },
			{ "GameStart", &UMainLevelUICanvasWidget::execGameStart },
			{ "OnEditButtonClicked", &UMainLevelUICanvasWidget::execOnEditButtonClicked },
			{ "OnQuitButtonClicked", &UMainLevelUICanvasWidget::execOnQuitButtonClicked },
			{ "OnStartButtonClicked", &UMainLevelUICanvasWidget::execOnStartButtonClicked },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UMainLevelUICanvasWidget_EnterEditMode_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainLevelUICanvasWidget_EnterEditMode_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainLevelUICanvasWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainLevelUICanvasWidget_EnterEditMode_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainLevelUICanvasWidget, nullptr, "EnterEditMode", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UMainLevelUICanvasWidget_EnterEditMode_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UMainLevelUICanvasWidget_EnterEditMode_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UMainLevelUICanvasWidget_EnterEditMode()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UMainLevelUICanvasWidget_EnterEditMode_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMainLevelUICanvasWidget_GameStart_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainLevelUICanvasWidget_GameStart_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainLevelUICanvasWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainLevelUICanvasWidget_GameStart_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainLevelUICanvasWidget, nullptr, "GameStart", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UMainLevelUICanvasWidget_GameStart_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UMainLevelUICanvasWidget_GameStart_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UMainLevelUICanvasWidget_GameStart()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UMainLevelUICanvasWidget_GameStart_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMainLevelUICanvasWidget_OnEditButtonClicked_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainLevelUICanvasWidget_OnEditButtonClicked_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainLevelUICanvasWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainLevelUICanvasWidget_OnEditButtonClicked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainLevelUICanvasWidget, nullptr, "OnEditButtonClicked", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UMainLevelUICanvasWidget_OnEditButtonClicked_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UMainLevelUICanvasWidget_OnEditButtonClicked_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UMainLevelUICanvasWidget_OnEditButtonClicked()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UMainLevelUICanvasWidget_OnEditButtonClicked_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMainLevelUICanvasWidget_OnQuitButtonClicked_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainLevelUICanvasWidget_OnQuitButtonClicked_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainLevelUICanvasWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainLevelUICanvasWidget_OnQuitButtonClicked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainLevelUICanvasWidget, nullptr, "OnQuitButtonClicked", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UMainLevelUICanvasWidget_OnQuitButtonClicked_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UMainLevelUICanvasWidget_OnQuitButtonClicked_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UMainLevelUICanvasWidget_OnQuitButtonClicked()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UMainLevelUICanvasWidget_OnQuitButtonClicked_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMainLevelUICanvasWidget_OnStartButtonClicked_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainLevelUICanvasWidget_OnStartButtonClicked_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainLevelUICanvasWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainLevelUICanvasWidget_OnStartButtonClicked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainLevelUICanvasWidget, nullptr, "OnStartButtonClicked", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UMainLevelUICanvasWidget_OnStartButtonClicked_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UMainLevelUICanvasWidget_OnStartButtonClicked_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UMainLevelUICanvasWidget_OnStartButtonClicked()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UMainLevelUICanvasWidget_OnStartButtonClicked_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UMainLevelUICanvasWidget_NoRegister()
	{
		return UMainLevelUICanvasWidget::StaticClass();
	}
	struct Z_Construct_UClass_UMainLevelUICanvasWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GameStartButton_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_GameStartButton;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GameQuitButton_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_GameQuitButton;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GameEditButton_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_GameEditButton;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_MF,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UMainLevelUICanvasWidget_EnterEditMode, "EnterEditMode" }, // 3281878600
		{ &Z_Construct_UFunction_UMainLevelUICanvasWidget_GameStart, "GameStart" }, // 28489809
		{ &Z_Construct_UFunction_UMainLevelUICanvasWidget_OnEditButtonClicked, "OnEditButtonClicked" }, // 381018037
		{ &Z_Construct_UFunction_UMainLevelUICanvasWidget_OnQuitButtonClicked, "OnQuitButtonClicked" }, // 2989830623
		{ &Z_Construct_UFunction_UMainLevelUICanvasWidget_OnStartButtonClicked, "OnStartButtonClicked" }, // 1536730268
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "MainLevelUICanvasWidget.h" },
		{ "ModuleRelativePath", "MainLevelUICanvasWidget.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameStartButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MainLevelUICanvasWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameStartButton = { "GameStartButton", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UMainLevelUICanvasWidget, GameStartButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameStartButton_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameStartButton_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameQuitButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MainLevelUICanvasWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameQuitButton = { "GameQuitButton", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UMainLevelUICanvasWidget, GameQuitButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameQuitButton_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameQuitButton_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameEditButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MainLevelUICanvasWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameEditButton = { "GameEditButton", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UMainLevelUICanvasWidget, GameEditButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameEditButton_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameEditButton_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameStartButton,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameQuitButton,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::NewProp_GameEditButton,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMainLevelUICanvasWidget>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::ClassParams = {
		&UMainLevelUICanvasWidget::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UMainLevelUICanvasWidget()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UMainLevelUICanvasWidget_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UMainLevelUICanvasWidget, 1452429801);
	template<> PROJECT_MF_API UClass* StaticClass<UMainLevelUICanvasWidget>()
	{
		return UMainLevelUICanvasWidget::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UMainLevelUICanvasWidget(Z_Construct_UClass_UMainLevelUICanvasWidget, &UMainLevelUICanvasWidget::StaticClass, TEXT("/Script/Project_MF"), TEXT("UMainLevelUICanvasWidget"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMainLevelUICanvasWidget);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
