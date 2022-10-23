// Copyright (c) 2022 Damian Nowakowski. All rights reserved.

#pragma once

#include "MyPluginEditorBase.h"
#include "MyPluginEditor.generated.h"

/**
 * Editor object which handles all of the logic of the Plugin.
 */

UCLASS()
class MYPLUGINEDITOR_API UMyPluginEditor : public UMyPluginEditorBase
{

	GENERATED_BODY()

public:

	// UMyPluginEditorBase implementation
	void Init() override;

protected:

	// UMyPluginEditorBase implementation
	void InitializeTheWidget();

public:

	/**
	 * Called when the test button has been pressed on the widget.
	 */
	void OnTestButtonPressed();

	// Test variable
	int32 NumberOfTestButtonPressed = 0;
};
