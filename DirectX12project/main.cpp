#include "MainLib/MainLib.h"

int main()
{
	create::Init(640);

	int image = create::LoadImg("test.png");
	float a = 0.0f;

	while (create::CheckMsg())
	{
		create::Clear();
		create::DrawImg(image, 0, create::Rad(a++));
		create::Execution();
		create::DeletePrim();
	}
}