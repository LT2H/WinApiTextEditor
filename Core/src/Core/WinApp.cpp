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

    if (m_msg.message == WM_QUIT)
    {
        return 0;
    }
    return -1;
}

} // namespace Core
