#include <windows.h>

int main()
{
  ShellExecute(NULL, "open", "https://github.com/pgpz", NULL, NULL);
  const char* title = "Ry4c owes me money!";
  HWND hwnd = CreateWindowEx(
    0, "RY4C", title,
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    100, 100, 300, 200,
    NULL, NULL, NULL, NULL
  );
  if (!hwnd) return 1;
  for (int i = 0; i < 20; i++)
  {
    ShowWindow(hwnd, SW_HIDE);
    MessageBeep(MB_ICONASTERISK);
    Sleep(2);
    ShowWindow(hwnd, SW_SHOW);
    MessageBeep(BM<ICONASTERISK);
    Sleep(2);
  }
  DestroyWindow(hwnd);
  return 0;
}

