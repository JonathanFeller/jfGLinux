#include "jfGL.h"
#include "Timing.h"
#include "WindowL.h"

int main(int argc, char **argv)
{
	Render render(640, 480);
	WindowL myWindow(render, "jfGL is awesome!", 0, 0, 640, 480);
	Timing timing;

	int pixelsCount = myWindow.getWidth() * myWindow.getHeight();

	XEvent event;
	int i = 0;
	while (i < pixelsCount)
	{
		render.Clear();

		((int32_t *)render.m_data)[i] = 0x000000FF | 0x00000F00;
		i++;

		myWindow.SwapBuffers();

		// XNextEvent(display, &event);
		// if (event.type == Expose)
		// {
		// }
		timing.Reset();
	}

	return 0;
}
