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
#include <QtWidgets/QComboBox>
#include <QtCore/QFile>
#include <QtCore/QLocale>
#include <QtUiTools/QtUiTools>
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MObject.h>

#include <main.h>

// ==========================================================================
//
//			Window class
//
// ==========================================================================
Window::Window(QWidget* parent) : QDialog(parent) {
	//	Load the form from its resource.
	QUiLoader loader;
	QFile file(":/main.ui");

	file.open(QFile::ReadOnly);
	_window = loader.load(&file, this);
	file.close();

    if (_window) {
		//	Destroy the dialog when it is closed.
		_window->setAttribute(Qt::WA_DeleteOnClose, true);

		//	Locate the various widgets inside the form.
		_buttonBox = _window->findChild<QDialogButtonBox*>("buttonBox");

		//	Connect to the buttonBox's 'accepted' signal, which indicates
		//	that the Ok button has been clicked.
		connect(_buttonBox, SIGNAL(accepted()), this, SLOT(clickHandler()));

		//	When the form is destroyed, destroy us as well.
		connect(
			_window, SIGNAL(destroyed(QObject*)), this, SLOT(deleteLater())
		);

		_window->show();
    }
}

void Window::clickHandler() {
     MGlobal::displayInfo("Button clicked!");
}

// ==========================================================================
//
//			Window class
//
// ==========================================================================
// Window::Window(QWidget* parent) : QDialog(parent) {
// 	//	Load the form from its resource.
// 	QUiLoader loader;
// 	QFile file(":/main.ui");

// 	file.open(QFile::ReadOnly);
// 	_window = loader.load(&file, this);
// 	file.close();

//     if (_window) {
// 		//	Destroy the dialog when it is closed.
// 		_window->setAttribute(Qt::WA_DeleteOnClose, true);

// 		//	Locate the various widgets inside the form.
// 		_buttonBox = _window->findChild<QDialogButtonBox*>("buttonBox");

// 		//	Connect to the buttonBox's 'accepted' signal, which indicates
// 		//	that the Ok button has been clicked.
// 		connect(_buttonBox, SIGNAL(accepted()), this, SLOT(clickHandler()));

// 		//	When the form is destroyed, destroy us as well.
// 		connect(
// 			_window, SIGNAL(destroyed(QObject*)), this, SLOT(deleteLater())
// 		);

// 		_window->show();
//     }
// }

// void Window::clickHandler() {
//      MGlobal::displayInfo("Button clicked!");
// }

// ==========================================================================
//
//			mayaUiPluginTemplate class
//
// ==========================================================================

//	We store a pointer to the button window in a static QPointer so that we
//	can destroy it if the plugin is unloaded. The QPointer will
//	automatically set itself to zero if the button window is destroyed
//	for any reason.
QPointer<Window> mayaUiPluginTemplate::fCurrentDialog;

const MString mayaUiPluginTemplate::commandName("qtPlugin");

void mayaUiPluginTemplate::cleanup() { if (!fCurrentDialog.isNull()) delete fCurrentDialog; }

MStatus mayaUiPluginTemplate::doIt(const MArgList& /* args */) {
	//	Create the Object Creator window, if it does not already exist
	//	Otherwise just make sure that the existing window is visible.
    if (fCurrentDialog.isNull()) {
		fCurrentDialog = new Window();
	} else {
		fCurrentDialog->showNormal();
		fCurrentDialog->raise();
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
