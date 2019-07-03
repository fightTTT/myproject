#include "_DebugDispOut.h"

std::unique_ptr<_DebugDispOut, _DebugDispOut::_DebugDispOutDeletor> _DebugDispOut::s_Instance(new _DebugDispOut);

_DebugDispOut::_DebugDispOut()
{
}


_DebugDispOut::~_DebugDispOut()
{
}
