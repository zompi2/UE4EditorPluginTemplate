// Copyright (c) 2022 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MyPluginEditor.generated.h"

/**
 * Editor object handles all of the logic of the Plugin.
 * It's tasks are to create a widget which is put into the dock, it also 
 * reacts to the user's interaction with created widget.
 */

UCLASS()
class MYPLUGINEDITOR_API UMyPluginEditor : public UObject
{

	GENERATED_BODY()

public:

	/**
	 * Initializes the editor object. Runs right after
	 * it's creation.
	 */
	void Init();

	/**
	 * Sets up the EditorTab. Used by Editor Module right after a Tab is created.
	 */
	void SetEditorTab(const TSharedRef<class SDockTab>& NewEditorTab);

	/**
	 * Returns true if the Editor UI widget can be created.
	 */
	bool CanCreateEditorUI();

	/**
	 * Creates Editor UI widget and returns a reference to it.
	 * It is called from the Editor Module in a moment of Tab Creation.
	 */
	TSharedRef<class SWidget> CreateEditorUI();

private:

	/**
	 * Returns an Utility Widget Blueprint from Content directory which will
	 * be used to create an Editor options window. The widget must be located
	 * in the given in this function location.
	 */
	class UEditorUtilityWidgetBlueprint* GetUtilityWidgetBlueprint();

	/**
	 * Creates the Editor Utility Widget from the Utility Widget Blueprint.
	 * It can be called from CreateDitorUI() when it is opened by user,
	 * or it can be called from ChangeTabWorld() in a situation when a map is loaded 
	 * or created and an Editor Tab is valid (moving widget between maps).
	 */
	TSharedRef<class SWidget> CreateEditorWidget();

	/**
	 * Called when OnMapChanged event occurs. The EditorTab must be properly
	 * handled when the world is torn down or when a map is created or loaded.
	 */
	void ChangeTabWorld(UWorld* World, EMapChangeType MapChangeType);

	/**
	 * Initialize EditorWidget after it's creation. 
	 * Binds all required delegates and sets up default values to the Widget.
	 */
	void InitializeTheWidget();


	// ~~~~~~~~~ Events received from the Widget

	/**
	 * Called when Localization path has changed in the Widget.
	 */
	void OnTestButtonPressed();

	int32 NumberOfTestButtonPressed = 0;

	// ~~~~~~~~~ End of events received from the Widget


	// Handler of the created Editor Utility Widget. 
	// Is created in CreateEditorWidget().
	UPROPERTY()
	class UMyPluginEditorWidget* EditorWidget;

	// A pointer to the EditorTab in which the editor widget should be docked. 
	// It is set by an Editor Module by SetEditorTab() right after the dock is created.
	TWeakPtr<class SDockTab> EditorTab;
};
