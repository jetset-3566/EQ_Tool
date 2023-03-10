// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoundReflection.h"
#include "SoundReflectionStyle.h"
#include "SoundReflectionCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName SoundReflectionTabName("SoundReflection");

#define LOCTEXT_NAMESPACE "FSoundReflectionModule"

void FSoundReflectionModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSoundReflectionStyle::Initialize();
	FSoundReflectionStyle::ReloadTextures();

	FSoundReflectionCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSoundReflectionCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FSoundReflectionModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSoundReflectionModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SoundReflectionTabName, FOnSpawnTab::CreateRaw(this, &FSoundReflectionModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FSoundReflectionTabTitle", "SoundReflection"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FSoundReflectionModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FSoundReflectionStyle::Shutdown();

	FSoundReflectionCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SoundReflectionTabName);
}

TSharedRef<SDockTab> FSoundReflectionModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FSoundReflectionModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("SoundReflection.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FSoundReflectionModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(SoundReflectionTabName);
}

void FSoundReflectionModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FSoundReflectionCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FSoundReflectionCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSoundReflectionModule, SoundReflection)