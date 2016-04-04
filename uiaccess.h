#ifndef UIACCESS_H
#define UIACCESS_H
#include "window.h"

class UiAccess
{
public:

    Ui::Window* ui;

    static UiAccess& getInstance();

private:
    UiAccess();
};

#endif // UIACCESS_H
