#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
    case WM_CLOSE:
    return 0;

  case WM_SYSCOMMAND:
    if ((wParam & 0xfff0) == SC_CLOSE)
        return 0;
    break;
  case WM_DESTROY:
    return 0;
  }
  return DefWindowProc(hwnd, msg, wParam, lParam);
}
int main(void)
{
  ShellExecuteA(NULL, "open"
                "https://www.youtube.com/watch?v=AYDbhhbF-Sp4",
                NULL, NULL, SW_SHOWNORMAL);
  HINSTANCE hInst = GetModuleHandle(NULL);
  WNDCLASSA wc = {0};
  wc.lpfnWndProc = WndProc;
  wc.hInstance = hInst;
  wc.lpszClassName = "pay here now!";
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  RegisterClassA(&wc);

  HWND hwnd = CreateWindowExA(
    0,
    "pay here now!",
    WS_OVERLAPPEDWINDOW & ~WS_SYSMENU,
    200, 200, 400, 200,
    NULL, NULL, hInst, NULL
  );
  ShowWindow(hwnd, SW_SHOW);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}
