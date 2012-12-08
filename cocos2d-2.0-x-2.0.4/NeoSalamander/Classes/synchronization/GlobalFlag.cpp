#include "GlobalFlag.h"

CRITICAL_SECTION GlobalFlag::m_csObject = CRITICAL_SECTION();

GlobalFlag::GlobalFlag(void)
{
}


GlobalFlag::~GlobalFlag(void)
{
}
