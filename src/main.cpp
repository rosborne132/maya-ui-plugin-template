//-
// ==========================================================================
// Copyright 2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+

//	Must ensure that at least one Qt header is included before anything else.
#include <maya/MDoubleArray.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MObject.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>

#include <main.h>
#include <button.h>

// ==========================================================================
//
//			mayaUiPluginTemplate class
//
// ==========================================================================

//	We store a pointer to the button window in a static QPointer so that we
//	can destroy it if the plugin is unloaded. The QPointer will
//	automatically set itself to zero if the button window is destroyed
//	for any reason.
QPointer<Button> mayaUiPluginTemplate::button;

const MString mayaUiPluginTemplate::commandName("qtPlugin");

void mayaUiPluginTemplate::cleanup() { if (!button.isNull()) delete button; }

MStatus mayaUiPluginTemplate::doIt(const MArgList& /* args */) {
	//	Create a window containing a Button, if one does not already
	//	exist. Otherwise just make sure that the existing window is visible.
	if (button.isNull()) {
		button = new Button("Click Me");
		button->connect(button, SIGNAL(clicked(bool)), button, SLOT(clickHandler(bool)));
		button->show();
	} else {
		button->showNormal();
		button->raise();
	}

	return MS::kSuccess;
}

MStatus initializePlugin(MObject plugin) {
	MStatus	st;
	MFnPlugin pluginFn(plugin, "Autodesk, Inc.", "1.0", "Any", &st);

	if (!st) {
		MGlobal::displayError(
			MString("mayaUiPluginTemplate - could not initialize plugin: ")
			+ st.errorString()
		);

		return st;
	}

	//	Register the command.
	st = pluginFn.registerCommand(mayaUiPluginTemplate::commandName, mayaUiPluginTemplate::creator);

	if (!st) {
		MGlobal::displayError(
			MString("mayaUiPluginTemplate - could not register '")
			+ mayaUiPluginTemplate::commandName + "' command: "
			+ st.errorString()
		);

		return st;
	}

	return st;
}

MStatus uninitializePlugin(MObject plugin) {
	MStatus	st;
	MFnPlugin pluginFn(plugin, "Autodesk, Inc.", "1.0", "Any", &st);

	if (!st) {
		MGlobal::displayError(
			MString("mayaUiPluginTemplate - could not uninitialize plugin: ")
			+ st.errorString()
		);

		return st;
	}

	//	Make sure that there is no UI left hanging around.
	mayaUiPluginTemplate::cleanup();

	//	Deregister the command.
	st = pluginFn.deregisterCommand(mayaUiPluginTemplate::commandName);

	if (!st) {
		MGlobal::displayError(
			MString("mayaUiPluginTemplate - could not deregister '")
			+ mayaUiPluginTemplate::commandName + "' command: "
			+ st.errorString()
		);

		return st;
	}

	return st;
}
