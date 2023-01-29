#ifndef BUTTON_h
#define BUTTON_h

#include <maya/MGlobal.h>
#include <QtCore/QPointer>
#include <QtWidgets/QPushButton>

class Button : public QPushButton{
	Q_OBJECT

    public:
        Button(const QString& text, QWidget* parent = 0);
        virtual	~Button();

    public Q_SLOTS:
        void clickHandler(bool checked);

    private:
        float fOffset;
};

#endif
