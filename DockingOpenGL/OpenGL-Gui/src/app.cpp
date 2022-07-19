#include "GLCore.h"
#include "ContainerLayer.h"
#include "../LayerRenderer.h"

using namespace GLCore;

class MyGUI : public Application
{
public:
	MyGUI()
		:Application("demo")
	{
		PushLayer(new ContainerLayer());
		PushLayer(new LayerRenderer());
	}
};

int main()
{
	std::unique_ptr<MyGUI> app = std::make_unique<MyGUI>();
	app->Run();
}