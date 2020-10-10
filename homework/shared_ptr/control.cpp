#include "control.hpp"

int cs::control_block::getSharedRef() const noexcept
{
    return sharedRef_;
}
int cs::control_block::getWeakRef() const noexcept
{
    return weakRef_;
}
void cs::control_block::incrementSharedRef() noexcept
{
    sharedRef_++;
}
void cs::control_block::decrementSharedRef() noexcept
{
    sharedRef_--;
}
void cs::control_block::incrementWeakRef() noexcept
{
    weakRef_++;
}

void cs::control_block::decrementWeakRef() noexcept {
    weakRef_--;
}
