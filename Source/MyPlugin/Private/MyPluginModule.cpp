// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "Modules/ModuleManager.h"

/**
 * Just a module, nothing to see here.
 */

class FMyPluginModule : public IModuleInterface
{};

IMPLEMENT_MODULE(FMyPluginModule, MyPlugin)