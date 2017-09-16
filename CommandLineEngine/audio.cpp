#pragma comment( lib, "Winmm.lib" )

#include "audio.h"
#include <windows.h>

//void Audio::Play(WCHAR filename)
//{
// 	PlaySound((LPCWSTR)filename, NULL, SND_FILENAME | SND_ASYNC);
//}

void Audio::Play(std::wstring  filename)
{
	PlaySound(filename.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}
