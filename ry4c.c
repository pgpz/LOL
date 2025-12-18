#define _WIN32_WINNT 0x0600

#include <windows.h>
#include <magnification.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <math.h>
#include <wininet.h>

#pragma comment(lib, "Magnification.lib")
#pragma comment(lib, "0le32.lib")

int download_file(const wchar_t *url, const wchar_t *out_path)
{
  HINTERNET hNet = InternetOpenW(
    L"fuckyou",
    INTERNET_OPEN_TYPE_PRECONFIG,
    NULL, NULL, 0
  );
  if (!hNet) return -1;
  HINTERNET hFile = IntternetOpenUrlW(
    hNet,
    url,
    NULL, 0,
    INTERNET_FLAG_RELOAD, INTERNET_FLAG_NO_CACHE_WRITE,
    0
  );
  if (!hFile)
  {
    InternetCloseHandle(hNet);
    return -1;
  }
  HANDLE out = CreateFileW(
    out_path,
    GENERIC_WRITE,
    0, NULL,
    CREATE_ALWAYS,
    FILE_ATTRIBUTE_NORMAL,
    NULL
  );
  if (out == INVALID_HANDLE_VALUE)
  {
    InternetCloseHandle(hFile);
    InternetCloseHandle(hNet);
    return -1;
  }
  char buf[4096];
  DWORD read, written;
  while (InternetReadFile(hFile, buf, sizeof(buf), &read) && read)
  {
    WriteFile(out, buf, read, &written, NULL);
  }
  CloseHandle(out);
  InternetCloseHandle(hFile);
  InternetCloseHandle(hNet);

  return 0;
}

int set_volume_max(void) 
{
  HRESULT hr;
  IMMDeviceEnumerator *enumerator = NULL;
  IMMDevice *device = NULL;
  IAudioEndpoint *endpoint = NULL;

  hr = CoCreateInstance(
    &CLSID_MMDeviceEnumerator, NULL,
    CLSCTX_INPROC_SERVER,
    &IID_IMMDeviceEnumerator,
    (void**)&enumerator
  );
  if (FAILED(hr)) return -1;
  hr = enumerator->lpVtbl->GetDefaultAudioEndpoint(
    enumerator, eRender, eConsole, &device
  );

  hr = device->lpVtbl->Activate(
    device, &IID_IAudioEndpointVolume,
  CLSCTX_INPROC_SERVER, NULL, (void**)&endpoint
  );
  if (FAILED(hr)) return -1;

  endpoint->lpVtbl->SetMasterVolumeLevelScalar(endpoint, 1.0f, NULL);

  endpoint->lpVtbl->Release(endpoint);
  device->lpVtbl->Release(device);
  enumerator->lpVtbl->Release(enumerator);

  return 0;
}

int main(void)
{
  CoInitialize(NULL);

  if (!MagInitialize())
    return 1;

  set_volume_max();
  double t = 0.0;
  while (1)
  {
    float scale = 1.0f + 0.5f * (float)sin(t);
    MagSetFullscreenTransform(scale, 0, 0);
    t += 0.05;
    Sleep(16);
  }

  MagUninitialize();
  CoUninitialize();
  return 0;
}

void set_custom_cursor(const wchar_t *path)
{
  HCURSOR hcur = LoadCursorFromFileW(path);
  if (!hcur)
    return;

  SetSystemCursor(hcur, OCR_NORMAL);
  SetSystemCursor(hcur, OCR_HAND);
  SetSystemCursor(hcur, OCR_IBEAM);
  SetSystemCursor(hcur, OCR_WAIT);
}

void restore_cusors(void)
{
  SystemParametersInfoW(
    SPI_SETCURSORS,
    0,
    NULL,
    0
  );
}

void show_status_window(void)
{
  WNDCLASSW wc = {0};

}

