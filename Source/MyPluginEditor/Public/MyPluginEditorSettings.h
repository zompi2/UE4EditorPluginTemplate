// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MyPluginEditorSettings.generated.h"

/**
 * Storing settings in DefaultEditor.ini file.
 */
UCLASS(config = Editor, defaultconfig)
class MYPLUGINEDITOR_API UMyPluginEditorSettings : public UObject
{
    GENERATED_BODY()

public:

	/**
	 * Gets the value of the current  bIsCheckboxChecked.
	 */
	static bool GetIsCheckboxChecked();

	/**
	 * Sets and saves the value of the bIsCheckboxChecked.
	 */
	static void SetIsCheckboxChecked(bool bInIsCheckboxChecked);

private:

	// Remember if the test checkbox is checked
	UPROPERTY(config)
	bool bIsCheckboxChecked = false;
};
