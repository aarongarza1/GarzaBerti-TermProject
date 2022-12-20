#ifndef LIGHT_H
#define LIGHT_H
#include "graphics_headers.h"

class Light
{
	public:
		Light(float lightAmb[], float lightDiff[], float lightSpec[], float gAmb[], float lightPos[]);
		float* getAmbient() { return m_lightAmbient;  }
		float* getDiffuse() { return m_lightDiffuse; }
		float* getSpec() { return m_lightSpec; }
		float* getGlobal() { return m_globalAmbient;  }
		float* getPosition() { return m_lightPos; }
	private:
		float m_lightAmbient[4];
		float m_lightDiffuse[4];
		float m_lightSpec[4];
		float m_globalAmbient[4];
		float m_lightPos[3];
};


#endif