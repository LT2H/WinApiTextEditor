#include "WinApp.h"

namespace Core
{
MSG WinApp::m_msg{};

int WinApp::run()
{
    while (GetMessage(&m_msg, nullptr, 0, 0))
    {
        TranslateMessage(&m_msg);
        DispatchMessage(&m_msg);
    }
    return 0;
}
} // namespace Core
