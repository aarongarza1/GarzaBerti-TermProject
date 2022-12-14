#include "graphics.h"

Graphics::Graphics(int x)
{
	gameMode = x;
}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height)
{
	// Used for the linux OS
#if !defined(__APPLE__) && !defined(MACOSX)
  // cout << glewGetString(GLEW_VERSION) << endl;
	glewExperimental = GL_TRUE;

	auto status = glewInit();

	// This is here to grab the error that comes from glew init.
	// This error is an GL_INVALID_ENUM that has no effects on the performance
	glGetError();

	//Check for error
	if (status != GLEW_OK)
	{
		std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
		return false;
	}
#endif



	// Init Camera
	m_camera = new Camera();
	if (!m_camera->Initialize(width, height))
	{
		printf("Camera Failed to Initialize\n");
		return false;
	}

	// Set up the shaders
	m_shader = new Shader("assets\\shaderFiles\\vert.vs", "assets\\shaderFiles\\vert.frag");
	if (!m_shader->Initialize())
	{
		printf("Shader Failed to Initialize\n");
		return false;
	}

	// Add the vertex shader
	if (!m_shader->AddShader(GL_VERTEX_SHADER))
	{
		printf("Vertex Shader failed to Initialize\n");
		return false;
	}

	// Add the fragment shader
	if (!m_shader->AddShader(GL_FRAGMENT_SHADER))
	{
		printf("Fragment Shader failed to Initialize\n");
		return false;
	}

	// Connect the program
	if (!m_shader->Finalize())
	{
		printf("Program to Finalize\n");
		return false;
	}
	m_shaderCubemap = new Shader("assets\\shaderFiles\\skybox.vs", "assets\\shaderFiles\\skybox.frag");
	if (!m_shaderCubemap->Initialize())
	{
		printf("Shader Failed to Initialize\n");
		return false;
	}

	// Add the vertex shader
	if (!m_shaderCubemap->AddShader(GL_VERTEX_SHADER))
	{
		printf("Vertex Shader failed to Initialize\n");
		return false;
	}

	// Add the fragment shader
	if (!m_shaderCubemap->AddShader(GL_FRAGMENT_SHADER))
	{
		printf("Fragment Shader failed to Initialize\n");
		return false;
	}

	// Connect the program
	if (!m_shaderCubemap->Finalize())
	{
		printf("cubeProgram to Finalize\n");
		return false;
	}

	// Populate location bindings of the shader uniform/attribs
	if (!collectShPrLocs()) {
		printf("Some shader attribs not located!\n");
	}

	// Starship
	m_mesh = new Mesh(glm::vec3(2.0f, 3.0f, -5.0f), "assets\\SpaceShip-1.obj", "assets\\SpaceShip-1.png");

	// The Sun
	m_sun = new Sphere(64, "assets\\2k_sun.jpg");

	// The Earth
	m_earth = new Sphere(48, "assets\\2k_earth_daymap.jpg");
	
	// The moon
	m_moon = new Sphere(48, "assets\\2k_moon.jpg");

	m_ceres = new Sphere(48, "assets\\Ceres.jpg");
	m_eris = new Sphere(48, "assets\\Eris.jpg");
	m_jupiter = new Sphere(48, "assets\\Jupiter.jpg");
	m_mars = new Sphere(48, "assets\\Mars.jpg");
	m_mercury = new Sphere(48, "assets\\Mercury.jpg");
	m_neptune = new Sphere(48, "assets\\Neptune.jpg");
	m_saturn = new Sphere(48, "assets\\Saturn.jpg");
	m_uranus = new Sphere(48, "assets\\Uranus.jpg");
	m_venus = new Sphere(48, "assets\\Venus.jpg");
	m_skybox = new Cubemap();
	//m_skybox = new Cubemap(glm::vec3(0., 0., 0.), "assets\\17520.jpg");
	for (int i = 0; i < 6; i++)
	{
		Mesh* aster = new Mesh(glm::vec3(2.0f, 3.0f, -5.0f), "assets\\ast1.obj", "assets\\ast1tex.png");
		asteroidBelt.push_back(aster);
		Mesh* aster2 = new Mesh(glm::vec3(2.0f, 3.0f, -5.0f), "assets\\ast1.obj", "assets\\ast1tex.png");
		asteroidBelt2.push_back(aster2);
	}
	for (int i = 0; i < 6; i++)
	{
		Mesh* aster = new Mesh(glm::vec3(2.0f, 3.0f, -5.0f), "assets\\ast2.obj", "assets\\ast2tex.png");
		asteroidBelt.push_back(aster);
		Mesh* aster2 = new Mesh(glm::vec3(2.0f, 3.0f, -5.0f), "assets\\ast1.obj", "assets\\ast1tex.png");
		asteroidBelt2.push_back(aster2);
	}
	for (int i = 0; i < 6; i++)
	{
		Mesh* aster = new Mesh(glm::vec3(2.0f, 3.0f, -5.0f), "assets\\ast3.obj", "assets\\ast3tex.png");
		asteroidBelt.push_back(aster);
		Mesh* aster2 = new Mesh(glm::vec3(2.0f, 3.0f, -5.0f), "assets\\ast1.obj", "assets\\ast1tex.png");
		asteroidBelt2.push_back(aster2);
	}
	for (int i = 0; i < 6; i++)
	{
		Mesh* aster = new Mesh(glm::vec3(2.0f, 3.0f, -5.0f), "assets\\ast4.obj", "assets\\ast4tex.png");
		asteroidBelt.push_back(aster);
		Mesh* aster2 = new Mesh(glm::vec3(2.0f, 3.0f, -5.0f), "assets\\ast1.obj", "assets\\ast1tex.png");
		asteroidBelt2.push_back(aster2);
	}
	for (int i = 0; i < asteroidBelt.size(); i++)
	{
		randomFloats1.push_back(((float(rand()) / float(RAND_MAX)) * (.07 - -.07)) + -.07);
	}
	for (int i = 0; i < asteroidBelt.size(); i++)
	{
		randomFloats2.push_back(((float(rand()) / float(RAND_MAX)) * (1 - -1)) + -1);
	}
	for (int i = 0; i < asteroidBelt.size(); i++)
	{
		randomFloats3.push_back(((float(rand()) / float(RAND_MAX)) * (.7 - -.7)) + -.7);
	}
	//enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	return true;
}

void Graphics::HierarchicalUpdate2(double dt) {
	m_skybox->Render(m_shaderCubemap, m_camera);
	// Update your animation for the solar system here.
	std::vector<float> speed, dist, rotSpeed, scale;
	glm::vec3 rotVector;
	glm::mat4 localTransform;
	// position of the sun	
	modelStack.push(glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0)));  // sun's coordinate
	localTransform = modelStack.top();		// The sun origin
	localTransform *= glm::rotate(glm::mat4(1.0f), (float)dt, glm::vec3(0.f, 1.f, 0.f));
	localTransform *= glm::scale(glm::vec3(1., 1., 1.));
	if (m_sun != NULL)
		m_sun->Update(localTransform);

	//position of the spaceship
	speed = { 0, -1, -1 };
	dist = { 0., 1.5, 1.5 };
	rotVector = { -1.,0.,0. };
	rotSpeed = { 1, .3, -3 };
	scale = { .012f, .012f, .012f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], cos(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_mesh != NULL)
		m_mesh->Update(localTransform);


	modelStack.pop();
		// position of the first planet
	speed = { .3, .3, .3 };
	dist = { -6., 0, -6. };
	rotVector = { 0.,1.,0. };
	rotSpeed = { 1., 1., 1. };
	scale = { .5,.5,.5 };
	localTransform = modelStack.top();				// start with sun's coordinate
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3((.73 * cos(speed[0] * dt)) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_mercury != NULL)
		m_mercury->Update(localTransform);
	modelStack.pop();
	std::vector<int> indices;
	for (int i = 0; i < asteroidBelt.size(); i++)
	{
		indices.push_back(i);
	}
	
	for(int i = 0; i < asteroidBelt.size(); i++){
		
		// position of the first planet
		speed = { float(.2 + randomFloats1[i]), float(.2 + randomFloats1[i]), float(.2 + randomFloats1[i])};
		dist = { float( - 30. + randomFloats2[i] * 2), 9, float(-30. + randomFloats2[i] * 2)};
		rotVector = { 1.,1.,1. };
		rotSpeed = { float(1.+ randomFloats3[i]), float(1. + randomFloats3[i]), float(1.)};
		scale = { .25,.25,.25 };
		localTransform = modelStack.top();				// start with sun's coordinate
		localTransform *= glm::translate(glm::mat4(1.f),
			glm::vec3((.73 * cos(speed[0] * dt)) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
		modelStack.push(localTransform);			// store planet-sun coordinate
		localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
		localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
		if (asteroidBelt[indices[i]] != NULL)
			asteroidBelt[indices[i]]->Update(localTransform);
		modelStack.pop();
	}

	for (int i = 0; i < asteroidBelt2.size(); i++) {

		// position of the first planet
		speed = { float(.2 + randomFloats1[i]), float(.2 + randomFloats1[i]), float(.2 + randomFloats1[i]) };
		dist = { float(-17. + randomFloats2[i] * 2), -6, float(-17. + randomFloats2[i] * 2) };
		rotVector = { 1.,1.,1. };
		rotSpeed = { float(1. + randomFloats3[i]), float(1. + randomFloats3[i]), float(1.) };
		scale = { .25,.25,.25 };
		localTransform = modelStack.top();				// start with sun's coordinate
		localTransform *= glm::translate(glm::mat4(1.f),
			glm::vec3((.73 * cos(speed[0] * dt)) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
		modelStack.push(localTransform);			// store planet-sun coordinate
		localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
		localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
		if (asteroidBelt2[asteroidBelt2.size() - 1 - i] != NULL)
			asteroidBelt2[asteroidBelt2.size() - 1 - i]->Update(localTransform);
		modelStack.pop();
	}

	// position of the second planet
	speed = { .26, .26, .26 };
	dist = { 10., 0, 10. };
	rotVector = { 0.,1.,0. };
	rotSpeed = { -1., -1., -1. };
	scale = { .5,.5,.5 };
	localTransform = modelStack.top();				// start with sun's coordinate
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(.73*cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_venus != NULL)
		m_venus->Update(localTransform);
	modelStack.pop();

	// position of the third planet
	speed = { .22, .22, .22 };
	dist = { 14., 0, 14. };
	rotVector = { 0.,1.,0. };
	rotSpeed = { 1., 1., 1. };
	scale = { .5,.5,.5 };
	localTransform = modelStack.top();				// start with sun's coordinate
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(.89 * cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_earth != NULL)
		m_earth->Update(localTransform);
	
	// position of the first moon
	speed = { -.5, -.5, -.5 };
	dist = { 1.0, 1.0, 1. };
	rotVector = { 0.,0.,-1. };
	rotSpeed = { 1, .25, -2.5 };
	scale = { .1f, .1f, .1f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_moon != NULL)
		m_moon->Update(localTransform);


	modelStack.pop(); 	// back to the planet coordinate

	modelStack.pop(); 	// back to the sun coordinate
	modelStack.pop();

	// position of the sun	
	modelStack.push(glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0)));  // sun's coordinate
	localTransform = modelStack.top();		// The sun origin
	localTransform *= glm::rotate(glm::mat4(1.0f), (float)(dt*1.65), glm::vec3(0.f, 1.f, 0.f));
	localTransform *= glm::scale(glm::vec3(1., 1., 1.));

	// position of the fourth planet
	speed = { .18, .18, .18 };
	dist = { -16., 0, -16. };
	rotVector = { 0.,1.,0. };
	rotSpeed = { 1., 1., 1. };
	scale = { .5,.5,.5 };
	localTransform = modelStack.top();				// start with sun's coordinate
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(.66 * cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_mars != NULL)
		m_mars->Update(localTransform);
	modelStack.pop();

	// position of the fifth planet
	speed = { .13, .13, .13 };
	dist = { 20., 0, -20. };
	rotVector = { 0.,1.,0. };
	rotSpeed = { 1., 1., 1. };
	scale = { .5,.5,.5 };
	localTransform = modelStack.top();				// start with sun's coordinate
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(-.73 * cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_jupiter != NULL)
		m_jupiter->Update(localTransform);
	modelStack.pop();

	// position of the sixth planet
	speed = { .10, .10, .10 };
	dist = { 23., 0, 23. };
	rotVector = { 0.,1.,0. };
	rotSpeed = { -1., -1., -1. };
	scale = { .5,.5,.5 };
	localTransform = modelStack.top();				// start with sun's coordinate
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(.73 * cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_saturn != NULL)
		m_saturn->Update(localTransform);
	modelStack.pop();

	// position of the seventh planet
	speed = { .06, .06, .06 };
	dist = { 27., 0, 27. };
	rotVector = { 0.,1.,0. };
	rotSpeed = { -1., -1., -1. };
	scale = { .5,.5,.5 };
	localTransform = modelStack.top();				// start with sun's coordinate
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(.69 * cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_uranus != NULL)
		m_uranus->Update(localTransform);
	modelStack.pop();

	// position of the eighth planet
	speed = { .02, .02, .02 };
	dist = { 31., 0, 31. };
	rotVector = { 0.,1.,0. };
	rotSpeed = { 1., 1., 1. };
	scale = { .5,.5,.5 };
	localTransform = modelStack.top();				// start with sun's coordinate
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(.81 * cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_neptune != NULL)
		m_neptune->Update(localTransform);
	modelStack.pop();


	modelStack.pop();	// empy stack

	/*modelStack.push(glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0)));  // sun's coordinate
	localTransform = modelStack.top();		// The sun origin
	//localTransform *= glm::rotate(glm::mat4(1.0f), (float)dt, glm::vec3(0.f, 1.f, 0.f));
	localTransform *= glm::scale(glm::vec3(50., 50., 50.));
	if (m_skybox != NULL)
		m_skybox->Update(localTransform);
	modelStack.pop(); */
}


void Graphics::ComputeTransforms(double dt, std::vector<float> speed, std::vector<float> dist, 
	std::vector<float> rotSpeed, glm::vec3 rotVector, std::vector<float> scale, glm::mat4& tmat, glm::mat4& rmat, glm::mat4& smat) {
	tmat = glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2])
	);
	rmat = glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	smat = glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
}

void Graphics::Render()
{
	//clear the screen
	glClearColor(0.5, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_skybox->Render(m_shaderCubemap, m_camera);
	// Start the correct program
	m_shader->Enable();

	// Send in the projection and view to the shader (stay the same while camera intrinsic(perspective) and extrinsic (view) parameters are the same
	glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
	glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

	// Render the objects
	/*if (m_cube != NULL){
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
		m_cube->Render(m_positionAttrib,m_colorAttrib);
	}*/

	if (m_mesh != NULL) {
		glUniform1i(m_hasTexture, false);
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_mesh->GetModel()));
		if (m_mesh->hasTex) {
			//glUniform1i(m_hasTexture, true);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_mesh->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("sp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			m_mesh->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}

	/*if (m_pyramid != NULL) {
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_pyramid->GetModel()));
		m_pyramid->Render(m_positionAttrib, m_colorAttrib);
	}*/

	if (m_sun != NULL) {
		glUniform1i(m_hasTexture, false);
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_sun->GetModel()));
		if (m_sun->hasTex) {
			glUniform1i(m_hasTexture, true);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_sun->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("sp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			m_sun->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}
	for (int i = 0; i < asteroidBelt.size(); i++) {
		if (asteroidBelt[i] != NULL){}
			glUniform1i(m_hasTexture, false);
			glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(asteroidBelt[i]->GetModel()));
			if (asteroidBelt[i]->hasTex) {
				glUniform1i(m_hasTexture, true);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, asteroidBelt[i]->getTextureID());
				GLuint sampler = m_shader->GetUniformLocation("sp");
				if (sampler == INVALID_UNIFORM_LOCATION)
				{
					printf("Sampler Not found not found\n");
				}
				glUniform1i(sampler, 0);
				asteroidBelt[i]->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
			}
	}
	for (int i = 0; i < asteroidBelt2.size(); i++) {
		if (asteroidBelt2[i] != NULL) {}
		glUniform1i(m_hasTexture, false);
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(asteroidBelt2[i]->GetModel()));
		if (asteroidBelt2[i]->hasTex) {
			glUniform1i(m_hasTexture, true);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, asteroidBelt2[i]->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("sp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			asteroidBelt2[i]->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}
	
	if (m_venus != NULL) {
		glUniform1i(m_hasTexture, false);
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_venus->GetModel()));
		if (m_venus->hasTex) {
			//glUniform1i(m_hasTexture, true);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_venus->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("sp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			m_venus->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}
	if (m_mercury != NULL) {
		glUniform1i(m_hasTexture, false);
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_mercury->GetModel()));
		if (m_mercury->hasTex) {
			//glUniform1i(m_hasTexture, true);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_mercury->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("sp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			m_mercury->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}
	if (m_earth != NULL) {
		glUniform1i(m_hasTexture, false);
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_earth->GetModel()));
		if (m_earth->hasTex) {
			glUniform1i(m_hasTexture, true);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_earth->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("sp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			m_earth->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}
	if (m_mars != NULL) {
		glUniform1i(m_hasTexture, false);
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_mars->GetModel()));
		if (m_mars->hasTex) {
			//glUniform1i(m_hasTexture, true);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_mars->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("sp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			m_mars->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}

	// Render Moon
	if (m_moon != NULL) {
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_moon->GetModel()));
		if (m_moon->hasTex) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_moon->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("sp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			m_moon->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}
	if (m_jupiter != NULL) {
		glUniform1i(m_hasTexture, false);
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_jupiter->GetModel()));
		if (m_jupiter->hasTex) {
			//glUniform1i(m_hasTexture, true);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_jupiter->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("sp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			m_jupiter->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}
	if (m_saturn != NULL) {
		glUniform1i(m_hasTexture, false);
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_saturn->GetModel()));
		if (m_saturn->hasTex) {
			//glUniform1i(m_hasTexture, true);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_saturn->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("sp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			m_saturn->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}
	if (m_uranus != NULL) {
		glUniform1i(m_hasTexture, false);
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_uranus->GetModel()));
		if (m_uranus->hasTex) {
			//glUniform1i(m_hasTexture, true);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_uranus->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("sp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			m_uranus->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}
	if (m_neptune != NULL) {
		glUniform1i(m_hasTexture, false);
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_neptune->GetModel()));
		if (m_neptune->hasTex) {
			//glUniform1i(m_hasTexture, true);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_neptune->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("sp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			m_neptune->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}
	

	
	// Get any errors from OpenGL
	auto error = glGetError();
	if (error != GL_NO_ERROR)
	{
		string val = ErrorString(error);
		std::cout << "Error initializing OpenGL! " << error << ", " << val << std::endl;
	}
}


bool Graphics::collectShPrLocs() {
	bool anyProblem = true;
	// Locate the projection matrix in the shader
	m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
	if (m_projectionMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_projectionMatrix not found\n");
		anyProblem = false;
	}

	// Locate the view matrix in the shader
	m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
	if (m_viewMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_viewMatrix not found\n");
		anyProblem = false;
	}

	// Locate the model matrix in the shader
	m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
	if (m_modelMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_modelMatrix not found\n");
		anyProblem = false;
	}

	// Locate the position vertex attribute
	m_positionAttrib = m_shader->GetAttribLocation("v_position");
	if (m_positionAttrib == -1)
	{
		printf("v_position attribute not found\n");
		anyProblem = false;
	}

	// Locate the color vertex attribute
	m_colorAttrib = m_shader->GetAttribLocation("v_color");
	if (m_colorAttrib == -1)
	{
		printf("v_color attribute not found\n");
		anyProblem = false;
	}

	// Locate the texture coord vertex attribute
	m_tcAttrib = m_shader->GetAttribLocation("v_tc");
	if (m_tcAttrib == -1)
	{
		printf("v_texcoord attribute not found\n");
		anyProblem = false;
	}
	//Whether our item has a texture
	m_hasTexture = m_shader->GetUniformLocation("hasTexture");
	if (m_hasTexture == INVALID_UNIFORM_LOCATION) {
		printf("hasTexture uniform not found\n");
		anyProblem = false;
	}

	return anyProblem;
}

std::string Graphics::ErrorString(GLenum error)
{
	if (error == GL_INVALID_ENUM)
	{
		return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
	}

	else if (error == GL_INVALID_VALUE)
	{
		return "GL_INVALID_VALUE: A numeric argument is out of range.";
	}

	else if (error == GL_INVALID_OPERATION)
	{
		return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
	}

	else if (error == GL_INVALID_FRAMEBUFFER_OPERATION)
	{
		return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
	}

	else if (error == GL_OUT_OF_MEMORY)
	{
		return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
	}
	else
	{
		return "None";
	}
}

