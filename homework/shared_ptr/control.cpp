#include "control.hpp"

int control_block::getSharedRef() const noexcept
{
    return sharedRef_;
}
int control_block::getWeakRef() const noexcept
{
    return weakRef_;
}
void control_block::incrementSharedRef() noexcept
{
    sharedRef_++;
}
void control_block::decrementSharedRef() noexcept
{
    sharedRef_--;
}
void control_block::incrementWeakRef() noexcept
{
    weakRef_++;
}
