#include <libgui/application.h>

int main(int argc, char** argv)
{
	(void) argc;
	(void) argv;
	
	struct hypergui_application app;
	
	
	return hypergui_application_execute(app);
}