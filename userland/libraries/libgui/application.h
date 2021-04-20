#ifndef HYPEROS_USERLAND_LIBRARIES_LIBGUI_APPLICATION_H_
#define HYPEROS_USERLAND_LIBRARIES_LIBGUI_APPLICATION_H_

struct hypergui_application
{
	int i;
};

int hypergui_application_execute(struct hypergui_application application);

#endif // HYPEROS_USERLAND_LIBRARIES_LIBGUI_APPLICATION_H_
