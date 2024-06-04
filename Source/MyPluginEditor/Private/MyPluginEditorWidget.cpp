// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "MyPluginEditorWidget.h"

void UMyPluginEditorWidget::TestButtonPressed()
{
	OnTestButtonPressedDelegate.ExecuteIfBound();
}

void UMyPluginEditorWidget::TestCheckBoxCheckChanged(bool bIsChecked)
{
	OnTestCheckboxDelegate.ExecuteIfBound(bIsChecked);
}