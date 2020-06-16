#ifndef _ENTRY_H_
#define _ENTRY_H_

#include "Log.h"
#include "Application.h"

extern Application* CreateApplication();

int main(int argc, char** argv)
{
	Log::Init();

	auto app = CreateApplication();
	app->Run();
	delete app;
}


#endif // _ENTRY_H_