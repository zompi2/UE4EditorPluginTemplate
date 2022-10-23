// Copyright (c) 2022 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

/**
 * Class handling UICommands of the editor.
 * Currently only "Open My Plugin" commands is required.
 * It is done via commands, because we want to have a keyboard shortcut for it.
 */

class MYPLUGINEDITOR_API FMyPluginEditorCommands : public TCommands<FMyPluginEditorCommands>
{

public:

	FMyPluginEditorCommands();
	void RegisterCommands() override;
	TSharedPtr<FUICommandInfo> OpenMyPluginWindow;
};
