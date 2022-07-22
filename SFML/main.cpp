#include "App.h"

int main()
{
	App app;

	while (app.IsWindowOpen())
	{
		app.Update();
	}
}