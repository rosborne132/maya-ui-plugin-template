#ifndef mayaUiPluginTemplate_h
#define mayaUiPluginTemplate_h

// Copyright 2015 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.

#include <maya/MPxCommand.h>
#include <QtWidgets/QDialog>
#include <QtCore/QPointer>

class QDialogButtonBox;

class Window : public QDialog {
	Q_OBJECT

    public:
        Window(QWidget* parent = 0);

    private Q_SLOTS:
        void clickHandler();

    private:
        QPointer<QWidget> _window;
        QDialogButtonBox* _buttonBox;
};


class QDialogButtonBox;

class mayaUiPluginTemplate : public MPxCommand {
    public:
        static void	cleanup();
        static void* creator() { return new mayaUiPluginTemplate(); }

        MStatus doIt(const MArgList& args);

        static QPointer<Window> fCurrentDialog;
        static const MString commandName;
};

#endif
