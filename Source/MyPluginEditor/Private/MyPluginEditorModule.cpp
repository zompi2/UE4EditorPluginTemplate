// Copyright (c) 2022 Damian Nowakowski. All rights reserved.

#include "MyPluginEditorModule.h"
#include "MyPluginEditor.h"
#include "MyPluginEditorCommands.h"
#include "MyPluginEditorStyle.h"

#include "Widgets/Docking/SDockTab.h"
#include "Framework/Docking/TabManager.h"
#include "Interfaces/IMainFrameModule.h"

#include "PropertyEditorModule.h"
#include "LevelEditor.h"

IMPLEMENT_MODULE(FMyPluginEditorModule, FMyPluginEditor)

// Id of the MyPlugin Tab used to spawn and observe this tab.
const FName MyPluginTabId = FName(TEXT("MyPlugin"));

void FMyPluginEditorModule::StartupModule()
{
	// Register Styles.
	FMyPluginEditorStyle::Initialize();
	FMyPluginEditorStyle::ReloadTextures();

	// Register UICommands.
	FMyPluginEditorCommands::Register();

	// Register OnPostEngineInit delegate.
	OnPostEngineInitDelegateHandle = FCoreDelegates::OnPostEngineInit.AddRaw(this, &FMyPluginEditorModule::OnPostEngineInit);

	// Create and initialize Editor object.
	Editor = NewObject<UMyPluginEditorBase>(GetTransientPackage(), UMyPluginEditor::StaticClass());
	Editor->Init();

	// Register Tab Spawner. Do not show it in menu, as it will be invoked manually by a UICommand.
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		MyPluginTabId,
		FOnSpawnTab::CreateRaw(this, &FMyPluginEditorModule::SpawnEditor),
		FCanSpawnTab::CreateLambda([this](const FSpawnTabArgs& Args) -> bool { return CanSpawnEditor(); })
	)
	.SetMenuType(ETabSpawnerMenuType::Hidden)
	.SetIcon(FSlateIcon(FMyPluginEditorStyle::GetStyleSetName(), "MyPluginEditorStyle.MenuIcon"));
}

void FMyPluginEditorModule::ShutdownModule()
{
	// Unregister Tab Spawner
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MyPluginTabId);

	// Cleanup the Editor object.
	Editor = nullptr;

	// Remove OnPostEngineInit delegate
	FCoreDelegates::OnPostEngineInit.Remove(OnPostEngineInitDelegateHandle);

	// Unregister UICommands.
	FMyPluginEditorCommands::Unregister();

	// Unregister Styles.
	FMyPluginEditorStyle::Shutdown();
}

void FMyPluginEditorModule::OnPostEngineInit()
{
	// This function is for registering UICommand to the engine, so it can be executed via keyboard shortcut.
	// This will also add this UICommand to the menu, so it can also be executed from there.
	
	// This function is valid only if no Commandlet or game is running. It also requires Slate Application to be initialized.
	if ((IsRunningCommandlet() == false) && (IsRunningGame() == false) && FSlateApplication::IsInitialized())
	{
		if (FLevelEditorModule* LevelEditor = FModuleManager::LoadModulePtr<FLevelEditorModule>(TEXT("LevelEditor")))
		{
			// Create a UICommandList and map editor spawning function to the UICommand of opening My Plugin Editor.
			TSharedPtr<FUICommandList> Commands = MakeShareable(new FUICommandList());
			Commands->MapAction(
				FMyPluginEditorCommands::Get().OpenMyPluginWindow,
				FExecuteAction::CreateRaw(this, &FMyPluginEditorModule::InvokeEditorSpawn),
				FCanExecuteAction::CreateRaw(this, &FMyPluginEditorModule::CanSpawnEditor),
				FIsActionChecked::CreateRaw(this, &FMyPluginEditorModule::IsEditorSpawned)
			);

			// Register this UICommandList to the MainFrame.
			// Otherwise nothing will handle the input to trigger this command.
			IMainFrameModule& MainFrame = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
			MainFrame.GetMainFrameCommandBindings()->Append(Commands.ToSharedRef());

			// Create a Menu Extender, which adds a button that executes the UICommandList of opening My Plugin Window.
			TSharedPtr<FExtender> MainMenuExtender = MakeShareable(new FExtender);
			MainMenuExtender->AddMenuExtension(
				FName(TEXT("General")),
				EExtensionHook::After, 
				Commands,
				FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& MenuBuilder)
				{
					MenuBuilder.AddMenuEntry(
						FMyPluginEditorCommands::Get().OpenMyPluginWindow,
						NAME_None,
						FText::FromString(TEXT("My Plugin")),
						FText::FromString(TEXT("Opens My Plugin Window")),
						FSlateIcon(FMyPluginEditorStyle::GetStyleSetName(), "MyPluginEditorStyle.MenuIcon")
					);
				})
			);

			// Extend Editors menu with the created Menu Extender.
			LevelEditor->GetMenuExtensibilityManager()->AddExtender(MainMenuExtender);
		}
	}
}

void FMyPluginEditorModule::AddReferencedObjects(FReferenceCollector& Collector)
{
	// Prevent Editor Object from being garbage collected.
	if (Editor)
	{
		Collector.AddReferencedObject(Editor);
	}
}

bool FMyPluginEditorModule::CanSpawnEditor()
{
	// Editor can be spawned only when the Editor object say that UI can be created.
	if (Editor && Editor->CanCreateEditorUI())
	{
		return true;
	}
	return false;
}

TSharedRef<SDockTab> FMyPluginEditorModule::SpawnEditor(const FSpawnTabArgs& Args)
{	
	// Spawn the Editor only when we can.
	if (CanSpawnEditor())
	{
		// Spawn new DockTab and fill it with newly created editor UI.
		TSharedRef<SDockTab> NewTab = SAssignNew(EditorTab, SDockTab)
			.TabRole(ETabRole::NomadTab)
			[
				Editor->CreateEditorUI()
			];

		// Tell the Editor Object about newly spawned DockTab, as it will 
		// need it to handle various editor actions.
		Editor->SetEditorTab(NewTab);

		// Return the DockTab to the Global Tab Manager.
		return NewTab;
	}

	// If editor can't be spawned - create an empty tab.
	return SAssignNew(EditorTab, SDockTab).TabRole(ETabRole::NomadTab);
}

bool FMyPluginEditorModule::IsEditorSpawned()
{
	// Checks if the editor tab is already existing in the editor
	return FGlobalTabmanager::Get()->FindExistingLiveTab(MyPluginTabId).IsValid();
}

void FMyPluginEditorModule::InvokeEditorSpawn()
{
	// Tries to invoke opening a plugin tab
	FGlobalTabmanager::Get()->TryInvokeTab(MyPluginTabId);
}
