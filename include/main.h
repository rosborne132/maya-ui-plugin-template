#ifndef mayaUiPluginTemplate_h
#define mayaUiPluginTemplate_h

// Copyright 2015 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.

#include <maya/MPxCommand.h>
#include <vector>

#include "button.h"

class mayaUiPluginTemplate : public MPxCommand {
    public:
        static void	cleanup();
        static void* creator() { return new mayaUiPluginTemplate(); }

        MStatus doIt(const MArgList& args);

        static QPointer<Button> button;
        static const MString commandName;
};

#endif
