#pragma once
class LightFieldController
{
public:
	LightFieldController(const LightFieldController&) = delete;

	static LightFieldController& GetInstance() {
		static LightFieldController instance;
		return instance;
	}

	void CreateAffinityWindow(int positionX, int positionY, int width, int height);

private:
	LightFieldController();

};

