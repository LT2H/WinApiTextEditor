#pragma once

#include <windows.h>

namespace Core
{
class WinApp
{
  public:
    static int run();

  private:
    static MSG m_msg;
};
} // namespace Core