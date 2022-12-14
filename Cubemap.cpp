#include "Cubemap.h"

Cubemap::Cubemap()
{
	const std::vector<const char*> faces =
	{
		"assets\\rightish.png",
		"assets\\leftish.png",
		"assets\\topish.png",
		"assets\\bottomish.png",
		"assets\\frontish.png",
		"assets\\backish.png"
	};
	texture = new Texture(faces);

	glGenVertexArrays(1, &CubemapVAO);
	glGenBuffers(1, &CubemapVBO);
	glBindVertexArray(CubemapVAO);
	glBindBuffer(GL_ARRAY_BUFFER, CubemapVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubemapVertices), &CubemapVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

Cubemap::~Cubemap() = default;

void Cubemap::Render(Shader* shader, Camera* camera)
{
	glDepthFunc(GL_LEQUAL);
	shader->Enable();
	glm::mat4 view = glm::mat4(glm::mat3(camera->GetView()));
	glm::mat4 projection = camera->GetProjection();
	glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(CubemapVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->getTextureID());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}
