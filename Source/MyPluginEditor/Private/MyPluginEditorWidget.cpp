// Copyright (c) 2022 Damian Nowakowski. All rights reserved.

#include "MyPluginEditorWidget.h"

void UMyPluginEditorWidget::TestButtonPressed()
{
	OnTestButtonPressedDelegate.ExecuteIfBound();
}
