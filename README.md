# Unreal Engine Editor Plugin Template

![mypluginscreen](https://github.com/zompi2/UE4EditorPluginTemplate/assets/7863125/1f97fac7-6369-431a-8446-e38c1a16c484)

This is a template of a plugin for UE4 that contains an Editor Utility Widget and can be opened via drop-down menu or a keyboard shortcut.  
It works on UE4.27, UE5.0, UE5.1, UE5.2, UE5.3 and UE5.4.

## Plugin structure

The plugin template is made of the following classes:

* **FMyPluginEditorModule**
Contains a logic that registers every needed component when started. It has a function for invoking the spawn of the editor's window and it constructs the plugin's logic object.
* **UMyPluginEditorBase**
The base of the object that contains the plugin's logic. This base handles only the widget creation and travels between levels. Any additional logic is handled by it's extension.
* **UMyPluginEditor**
The extension of the base object. **Any logic that the plugin does should ends up here**.
* **UMyPluginEditorWidget**
The base class of the widget which is stored inside the plugin's content directory and which is displayed in the editors window.
* **UMyPluginEditorSettings**
Settings. The object that reads and writes the values from the DefaultEditor.ini file.
* **FMyPluginEditorStyle**
Plugin style handle. Used to set the icon inside the Editor's UI.
* **FMyPluginEditorCommands**
Commands handle. Used to register a keyboard shortcut that opens the plugin's window.

## Changing the plugin widget
Inside the plugin's content directory there is a `MyPluginWidget_BP` Editor Utility Widget which is opened when the plugin is invoked. The base class of this widget is `UMyPluginEditorWidget`. When the name of the widget is changed the following path in the `UMyPluginEditorBase` must bechanged:

``` cpp
#if ((ENGINE_MAJOR_VERSION == 5) && (ENGINE_MINOR_VERSION >= 1))
    FAssetData AssetData = AssetRegistryModule.Get().GetAssetByObjectPath(FSoftObjectPath("/MyPlugin/MyPluginWidget_BP.MyPluginWidget_BP"));
#else
    FAssetData AssetData = AssetRegistryModule.Get().GetAssetByObjectPath("/MyPlugin/MyPluginWidget_BP.MyPluginWidget_BP");
#endif
```

## UI and Logic separation
This plugin template separates the UI and the Logic layers. All the UI part is inside the `UMyPluginEditorWidget`. All the logic part is inside the `UMyPluginEditor` object. Communication between these elements is handled by the following scheme:
 * UI -> Logic : by delegates
 ``` cpp
// MyPluginEditor.cpp
void UMyPluginEditor::InitializeTheWidget()
{
    EditorWidget->OnTestButtonPressedDelegate.BindUObject(this, &UMyPluginEditor::OnTestButtonPressed);
    EditorWidget->OnTestCheckboxDelegate.BindUObject(this, &UMyPluginEditor::OnTestCheckboxChanged);
}

// MyPluginEditorWidget.cpp
void UMyPluginEditorWidget::TestButtonPressed()
{
    OnTestButtonPressedDelegate.ExecuteIfBound();
}
void UMyPluginEditorWidget::TestCheckBoxCheckChanged(bool bIsChecked)
{
    OnTestCheckboxDelegate.ExecuteIfBound(bIsChecked);
}

```
 * Logic -> UI : by direct function call
``` cpp
// MyPluginEditor.cpp
void UMyPluginEditor::OnTestButtonPressed()
{
    EditorWidget->SetNumberOfTestButtonPressed(NumberOfTestButtonPressed);
}
void UMyPluginEditor::OnTestCheckboxChanged(bool bIsChecked)
{
    UMyPluginEditorSettings::SetIsCheckboxChecked(bIsChecked);
}
```

## Changing plugin name and description
The name and the description of the plugin inside the Plugins Browser is controlled by the `MyPlugin.uplugin` file.  
To change the name and the description and the location of the plugin's button in the drop-down menu the following code in the `FMyPluginEditorModule::OnPostEngineInit()` must be changed:

For Unreal Engine **5.4**:

``` cpp
UToolMenu* Menu = UToolMenus::Get()->FindMenu("LevelEditor.MainMenu.Tools"); // The category under which the button will be placed
if (Menu)
{
    Menu->AddMenuEntry(NAME_None, FToolMenuEntry::InitMenuEntryWithCommandList(
        FMyPluginEditorCommands::Get().OpenMyPluginWindow,
        Commands,
        FText::FromString(TEXT("My Plugin")), // Name of the plugin
        FText::FromString(TEXT("Opens My Plugin Window")), // Description of the plugin
        FSlateIcon(FMyPluginEditorStyle::GetStyleSetName(), "MyPluginEditorStyle.MenuIcon")
    ));
}
```

For Unreal Engine **4.27-5.3**:

``` cpp
MainMenuExtender->AddMenuExtension(
#if (ENGINE_MAJOR_VERSION == 5)
    FName(TEXT("Tools")), // The category under which the button will be placed
#else
    FName(TEXT("General")), // The category under which the button will be placed
#endif
    EExtensionHook::After,  // The order in which the button will be placed in the pointed category
    Commands,
    FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& MenuBuilder)
    {
        MenuBuilder.AddMenuEntry(
            FMyPluginEditorCommands::Get().OpenMyPluginWindow,
            NAME_None,
            FText::FromString(TEXT("My Plugin")), // Name of the plugin
            FText::FromString(TEXT("Opens My Plugin Window")), // Description of the plugin
            FSlateIcon(FMyPluginEditorStyle::GetStyleSetName(), "MyPluginEditorStyle.MenuIcon")
        );
    })
);
```

## Changing plugin name and description and default keyboard shortcut in the shortcut settings

![shortcut](https://github.com/zompi2/UE4EditorPluginTemplate/assets/7863125/077bdac3-e531-48c1-9fd8-403381196496)

In order to change name and description and the default value of the keyboard shortcut in the Editors Settings the following line in `FMyPluginEditorCommands::RegisterCommands()` must be changed.
``` cpp
UI_COMMAND(OpenMyPluginWindow, "My Plugin", "Opens My Plugin Window", EUserInterfaceActionType::Check, FInputChord(EModifierKey::Shift | EModifierKey::Alt, EKeys::M));
```
If you don't want to use keyboard shortcut simply leave the `FInputChord()` empty.

## Support and contribution

This plugin template is free and opensource forever, but any contribution is welcomed and will warm my heart.

## Final words

I wish to send special thanks to Monika, because she always supports me and believes in me (even if I don't), to Pawel, who gave me an opportunity to write and test new solutions on his project with the believe it won't break anything (too much).

This template is free to use by anybody, I hope it will help at least a little. Cheers! <3
