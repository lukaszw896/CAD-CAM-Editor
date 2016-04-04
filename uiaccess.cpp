#include "uiaccess.h"

UiAccess::UiAccess()
{

}

UiAccess& UiAccess::getInstance()
{

    static UiAccess instance;

    return instance;
}
