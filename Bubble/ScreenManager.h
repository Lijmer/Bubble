#pragma once
class ScreenManager
{
public:
	ScreenManager(void);
	~ScreenManager(void);

	static ScreenManager& GetInstance();

private:
	int state;
};

