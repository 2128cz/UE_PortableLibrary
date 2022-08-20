// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionSystem.h"
#include "MissionSystemStyle.h"
#include "MissionSystemCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName MissionSystemTabName("MissionSystem");

#define LOCTEXT_NAMESPACE "FMissionSystemModule"

void FMissionSystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMissionSystemStyle::Initialize();
	FMissionSystemStyle::ReloadTextures();

	FMissionSystemCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMissionSystemCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FMissionSystemModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMissionSystemModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MissionSystemTabName, FOnSpawnTab::CreateRaw(this, &FMissionSystemModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMissionSystemTabTitle", "MissionSystem"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FMissionSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FMissionSystemStyle::Shutdown();

	FMissionSystemCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MissionSystemTabName);
}

TSharedRef<SDockTab> FMissionSystemModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FMissionSystemModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("MissionSystem.cpp"))
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

void FMissionSystemModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(MissionSystemTabName);
}

void FMissionSystemModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FMissionSystemCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMissionSystemCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMissionSystemModule, MissionSystem)