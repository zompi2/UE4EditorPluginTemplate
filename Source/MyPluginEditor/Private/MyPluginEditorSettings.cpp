// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "MyPluginEditorSettings.h"
#include "Runtime/Launch/Resources/Version.h"

bool UMyPluginEditorSettings::GetIsCheckboxChecked()
{
	return GetDefault<UMyPluginEditorSettings>()->bIsCheckboxChecked;
}

void UMyPluginEditorSettings::SetIsCheckboxChecked(bool bInIsCheckboxChecked)
{
	UMyPluginEditorSettings* Settings = GetMutableDefault<UMyPluginEditorSettings>();
	Settings->bIsCheckboxChecked = bInIsCheckboxChecked;

#if (ENGINE_MAJOR_VERSION == 5)
	Settings->TryUpdateDefaultConfigFile();
#else
	Settings->UpdateDefaultConfigFile();
#endif
}

