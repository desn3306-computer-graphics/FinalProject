#include "RandomMode.h"
#include <iostream> //Standard Header Files
using namespace std;

RandomMode::RandomMode()
{
	curVal = rand() / 32767.0f;
	maxValue = 1.0f;
	step = 0.001f;
	direction = true;
	spinn = false;
}

//Motion Pattern Explained...

//params are (initialValue, MaximumValue, stepSize, motionType)
//For translation flase will show pendulum motion (-1 to +1 and repeat) 
//For translation true will show reset motion (0 to +1 and repeat)

//For Rotation when flase will show periodic reverse motion or pendulum movement (0 to MAX then X to 0 and repeat)
//For Rotation when true will show jump motion or (0 to MAX and repeat)


//Special case 01:
//For Rotation when 2*PI is used as max value, true and positive step_size will show circular movement anti-clockwise (0 to 2*PI in radian and repeat) 
 //Special case 02:
//For Rotation when 2*PI is used as max value, true and negative step_size will show circular movement clockwise (0 to 2*PI in radian and repeat) 

RandomMode::RandomMode(GLfloat cv, GLfloat mv, GLfloat st, bool sp) :RandomMode()
{

	curVal = cv;
	maxValue = mv;
	step = st;
	spinn = sp;

}

GLfloat RandomMode::genCurrentValue()
{
	if (direction)
	{
		curVal += step;
	}
	else {
		curVal -= step;
	}

	if (abs(curVal) >= maxValue)
	{
		if (spinn)
		{
			curVal = 0;
		}
		else {
			direction = !direction;
		}

	}

	/* uncomment this code if you want to control in Degree rather than in Radian
	if (spinn == true)
		return curVal * toRadian;
	*/
	//cout<<curVal<<" ";
	return curVal;
}


RandomMode::~RandomMode()
{
}
