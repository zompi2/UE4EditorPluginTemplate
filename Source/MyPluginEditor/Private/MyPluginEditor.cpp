// Copyright (c) 2022 Damian Nowakowski. All rights reserved.

#include "MyPluginEditor.h"
#include "MyPluginEditorWidget.h"

#include "AssetRegistryModule.h"
#include "EditorUtilityWidget.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "LevelEditor.h"

void UMyPluginEditor::Init()
{
	// Put initialization code here
}

void UMyPluginEditor::InitializeTheWidget()
{
	// Initialize the widget here
	EditorWidget->SetNumberOfTestButtonPressed(NumberOfTestButtonPressed);

	// Bind all required delegates to the Widget.
	EditorWidget->OnTestButtonPressedDelegate.BindUObject(this, &UMyPluginEditor::OnTestButtonPressed);
}

void UMyPluginEditor::OnTestButtonPressed()
{
	// Button on the widget has been pressed. Increase the counter and inform the widget about it.
	NumberOfTestButtonPressed++;
	EditorWidget->SetNumberOfTestButtonPressed(NumberOfTestButtonPressed);
}


