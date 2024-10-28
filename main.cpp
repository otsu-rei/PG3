//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* c++
#include <cstdint>
#include <vector>

#include <Shape.h>

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	Circle circle;
	circle.radius = 2.0f;

	circle.Size();
	circle.Draw();

	Rectangle rectangle;
	rectangle.width  = 2.0f;
	rectangle.height = 4.0f;

	rectangle.Size();
	rectangle.Draw();

	return 0;
}