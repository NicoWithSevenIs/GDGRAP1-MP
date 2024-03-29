#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
//#define _USE_MATH_DEFINES
#include "Workspace/Workspace.hpp"
/*

	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
	"League Of Legends - Akali V3" (https://skfb.ly/ooKK6)
	by 1FENIL is licensed under Creative Commons Attribution
	(http://creativecommons.org/licenses/by/4.0/).

	Modified in blender to remove her weapons and scale her down (she was really big)

	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	 
	"Anemo Slime" (https://skfb.ly/oR8Kx)
	by LinjieFan is licensed under Creative Commons Attribution-NonCommercial
	(http://creativecommons.org/licenses/by-nc/4.0/).
	
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

*/

int main(void)
{
    Workspace::getInstance()->run();
    return 0;
}

