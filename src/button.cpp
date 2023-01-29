#include <button.h>

// ==========================================================================
//
//			Button class
//
// ==========================================================================

Button::Button(const QString& text, QWidget* parent) : QPushButton(text, parent) {}
Button::~Button() {}


//	This is a slot which is called whenever the button is pushed.
void Button::clickHandler(bool /* checked */) {
     MGlobal::displayInfo("Button clicked!");
}