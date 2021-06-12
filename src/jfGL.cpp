#include "jfGL.h"

int main(int argc, char **argv)
{
	Render render(640, 480);
	jfWindow window(render, "jfGL is awesome!", 0, 0, 640, 480);

	Timing timing;
	while (true)
	{
		render.Clear();

		window.SwapBuffers();

		XEvent xEvent;
		XCheckTypedEvent(window.getDisplay(), ClientMessage, &xEvent);
		if (xEvent.type == ClientMessage)
		{
			if ((Atom)xEvent.xclient.data.l[0] == window.wm_delete_window)
			{
				// TODO: Break if you want to exit
				break;
			}
		}
		timing.Reset();
	}

	return 0;
}
