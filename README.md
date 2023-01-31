# Maya UI Plug-in Template
This is a template repo for creating a Maya command plugin.

## Setup

### Install devkit
In order to build plugins for Maya, you need to install the devkit for the version of Maya you are using. To install the devkit, locate your OS and version [here](https://www.autodesk.com/developer-network/platform-technologies/maya).

### Setup devkit
Once you install the devkit, you need to set it up for your OS. You can find instructions [here](https://help.autodesk.com/view/MAYAUL/2023/ENU/?guid=Maya_SDK_Setting_up_your_build_html).

For UI plugin you need to extract the following folders within the devkit
```
export DEVKIT_LOCATION=<path>/Extra/devkitBase
export MAYA_LOCATION=<path>/runTime

cd $DEVKIT_LOCATION/include
tar -xzvf qt_5.15.2-include.tar.gz

cd $DEVKIT_LOCATION/mkspecs
tar -xzvf qt_5.15.2-mkspecs.tar.gz
```

## Build Project

After running `make` you need to update the *.mak file with the following for MacOS.

#### Before
```
TARGET        = mayaUiPluginTemplate.dylib
TARGETD       = mayaUiPluginTemplate.dylib
```

#### After
```
TARGET        = mayaUiPluginTemplate.bundle
TARGETD       = mayaUiPluginTemplate.bundle
```

Once update is run the following command `make -f main.mak` update *.mak name to reflect the name you use for it.

## Project scripts
```bash
// Removes build directory
make clean

// Generates makefile + build directory
make generate

// Runs make clean and generate
make

// builds a new project
make build-plugin
```

## Launching the Maya plugin

Once the plugin is complete, follow this [doc](https://help.autodesk.com/view/MAYAUL/2023/ENU/?guid=Maya_SDK_LoadingAndUnloadingPlugins_Loading_Samples_Plug_ins_Into_Maya_html) to load the plugin. Once you load the plugin, you can run a MEL script to open the template plugin. Example `qtPlugin`


### Working on the UI within Maya

```
string $dialog = `loadUI -uiFile "{path}/maya-ui-plugin-template/main.ui"`;
showWindow $dialog;
```