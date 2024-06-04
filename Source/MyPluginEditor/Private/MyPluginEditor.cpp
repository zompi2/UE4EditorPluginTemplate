// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "MyPluginEditor.h"
#include "MyPluginEditorWidget.h"
#include "MyPluginEditorSettings.h"

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
	EditorWidget->SetTestCheckboxIsChecked(UMyPluginEditorSettings::GetIsCheckboxChecked());

	// Bind all required delegates to the Widget.
	EditorWidget->OnTestButtonPressedDelegate.BindUObject(this, &UMyPluginEditor::OnTestButtonPressed);
	EditorWidget->OnTestCheckboxDelegate.BindUObject(this, &UMyPluginEditor::OnTestCheckboxChanged);
}

void UMyPluginEditor::OnTestButtonPressed()
{
	// Button on the widget has been pressed. Increase the counter and inform the widget about it.
	NumberOfTestButtonPressed++;
	EditorWidget->SetNumberOfTestButtonPressed(NumberOfTestButtonPressed);
}

void UMyPluginEditor::OnTestCheckboxChanged(bool bIsChecked)
{
	// Checkbox on  the widget has been changed. Save it's state to the settings.
	UMyPluginEditorSettings::SetIsCheckboxChecked(bIsChecked);
}