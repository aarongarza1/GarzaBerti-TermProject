#include "Light.h"




Light::Light(float lightAmb[], float lightDiff[], float lightSpec[], float gAmb[], float lightPos[])
{
	m_lightAmbient[0] = lightAmb[0];
	m_lightAmbient[1] = lightAmb[1];
	m_lightAmbient[2] = lightAmb[2];
	m_lightAmbient[3] = lightAmb[3];
	m_lightDiffuse[0] = lightDiff[0];
	m_lightDiffuse[1] = lightDiff[1];
	m_lightDiffuse[2] = lightDiff[2];
	m_lightDiffuse[3] = lightDiff[3];
	m_lightSpec[0] = lightSpec[0];
	m_lightSpec[1] = lightSpec[1];
	m_lightSpec[2] = lightSpec[2];
	m_lightSpec[3] = lightSpec[3];
	m_lightPos[0] = lightPos[0];
	m_lightPos[1] = lightPos[1];
	m_lightPos[2] = lightPos[2];
}




