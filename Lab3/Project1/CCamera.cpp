#include "CCamera.h"

//конструктор
 CCamera::CCamera( void) {
	radius = sqrt(625);
	for (int i = 0; i < 9; i++)
		CameraMatrix[i] = 0;
	CameraMatrix[7] = 1;
	CameraMatrix[0] = cos(angle_vertical) * radius * cos(angle_horizon);
	CameraMatrix[1] = sin(angle_vertical) * radius;
	CameraMatrix[2] = cos(angle_vertical) * radius * sin(angle_horizon);

}
CCamera::~CCamera() {
}

//	установка признаков нажатия клавиш
void CCamera::SetKey(bool left, bool right,
	bool up, bool down,
	bool forward, bool backward)
{
	CameraLeft = left;
	CameraRight = right;
	CameraUp = up;
	CameraDown = down;
	CameraForward = forward;
	CameraBackward = backward;
}

//	движение камеры в ранее выбранном направлении
//	sec - количество секунд прошедших с момента последнего вызова
void CCamera::Simulate(float sec)
{

	if (CameraBackward) {
		if (radius < 50)
		{
			radius += 50 * sec;
		}
	}
	if (CameraForward) {
		if (radius > 10)
		{
			radius += -20 * sec;
		}
	}
	if (CameraUp) {
		if (angle_vertical < 1.225)
		{
			angle_vertical += 1.225 * sec;
		}
	}
	if (CameraDown) {
		if (angle_vertical > -1.225)
		{
			angle_vertical += -1.225 * sec;
		}
	}
	if (CameraLeft) {
		{
			angle_horizon += 1.225 * sec;
		}
	}
		if (CameraRight){
		{
			angle_horizon += -1.225 * sec;
		}
	}
}



//	функция для установки матрицы камеры
void CCamera::Apply()
{
	CCamera();
	CameraMatrix[0] = cos(angle_vertical) * radius * cos(angle_horizon);//позиция камеры x
	CameraMatrix[1] = sin(angle_vertical) * radius;//позиция камеры y
	CameraMatrix[2] = cos(angle_vertical) * radius * sin(angle_horizon);//позиция камеры z
	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(CameraMatrix[0], CameraMatrix[1], CameraMatrix[2],
		CameraMatrix[3], CameraMatrix[4], CameraMatrix[5],
		CameraMatrix[6], CameraMatrix[7], CameraMatrix[8]);
}