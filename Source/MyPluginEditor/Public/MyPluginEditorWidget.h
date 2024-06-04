// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "MyPluginEditorWidget.generated.h"

/**
 * Widget code used to communicate between code and BP widget.
 */

/**
 * Declaration of all required delegates for a proper communication with UI.
 * They will be broadcasted to inform the plugin code about changes in UI.
 */
 
// Called when the button has been pressed.
DECLARE_DELEGATE(FOnTestButton);

// Called when the checkbox has been changed.
DECLARE_DELEGATE_OneParam(FOnTestCheckbox, bool /*bIsChecked*/);

UCLASS()
class MYPLUGINEDITOR_API UMyPluginEditorWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:

	/**
	 * Sets the number of test button pressed in the widget.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void SetNumberOfTestButtonPressed(int32 NewNumber);

	/**
	 * Called when the test button has been pressed.
	 */
	UFUNCTION(BlueprintCallable, Category = "My Plugin Editor Widget")
	void TestButtonPressed();

	/**
	 * Sets if the test checkbox should be checked.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void SetTestCheckboxIsChecked(bool bIsChecked);

	/**
	 * Called when the test checkbox has been checked.
	 */
	UFUNCTION(BlueprintCallable, Category = "My Plugin Editor Widget")
	void TestCheckBoxCheckChanged(bool bIsChecked);

	/**
	 * Callbacks to be binded to the MyPluginEditor methods.
	 */
	FOnTestButton OnTestButtonPressedDelegate;
	FOnTestCheckbox OnTestCheckboxDelegate;
};