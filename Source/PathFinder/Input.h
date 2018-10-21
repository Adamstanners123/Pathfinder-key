using namespace std;

#pragma once
class Input
{
public:
	Input();
	~Input();

	void setKeyDown(int key);
	void setKeyUp(int key);
	bool isKeyDown(int key);

private:
	bool keys[256]{ false };

};
