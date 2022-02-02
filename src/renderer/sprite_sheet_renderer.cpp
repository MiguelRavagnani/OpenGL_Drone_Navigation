#include "sprite_sheet_renderer.h"

SpriteSheetRenderer::SpriteSheetRenderer(const Shader &param_shader)
    : SpriteRenderer::SpriteRenderer(param_shader) {}

SpriteSheetRenderer::~SpriteSheetRenderer()
{
    glDeleteVertexArrays(1, &this->m_quad_VAO);
}

void SpriteSheetRenderer::DrawSheet(
    const Texture2D &param_texture, 
    glm::vec2 param_position,
    GLuint param_frame_index,
    glm::vec2 param_sheet_size = glm::vec2(10.0f, 10.0f), 
    glm::vec2 param_sprite_size = glm::vec2(10.0f, 10.0f),
    GLfloat param_rotate = 0.0f, 
    glm::vec3 param_color = glm::vec3(1.0f))
{
    this->m_shader.Use();

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(param_position, 0.0f));
    model = glm::rotate(model, glm::radians(param_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(param_sheet_size, 1.0f));

    this->m_shader.SetMatrix4("model", model);

    this->m_shader.SetVector3f("spriteColor", param_color);

    glActiveTexture(GL_TEXTURE0);
    param_texture.Bind();

    glBindVertexArray(this->m_quad_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteSheetRenderer::UpdateRenderData(GLuint param_sprite_widht, GLuint param_sprite_hight)
{
    unsigned int VBO;
    GLfloat vertices[] = { 
    /*  pos         tex       */
        0.0f, 1.0f, 0.0f + param_sprite_widht, 1.0f,
        1.0f, 0.0f, 1.0f + param_sprite_widht, 0.0f,
        0.0f, 0.0f, 0.0f + param_sprite_widht, 0.0f, 

        0.0f, 1.0f, 0.0f + param_sprite_widht, 1.0f,
        1.0f, 1.0f, 1.0f + param_sprite_widht, 1.0f,
        1.0f, 0.0f, 1.0f + param_sprite_widht, 0.0f
    };

    glGenVertexArrays(1, &this->m_quad_VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->m_quad_VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}