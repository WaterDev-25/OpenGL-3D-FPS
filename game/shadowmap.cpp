#include "shadowmap.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CShadowMap::CShadowMap(GLfloat shadowWidth, GLfloat shadowHeight, glm::vec3 lightPos) :
	m_shadowWidth(shadowWidth),
	m_shadowHeight(shadowHeight),
    m_lightPos(lightPos),
    m_lightSpaceMatrix(glm::mat4(1.0f))
{
    // Generate depth map framebuffer
    glGenFramebuffers(1, &this->m_depthMapFbo);

    // Generate and bind depth map texture
    glGenTextures(1, &this->m_depthMap);
    glBindTexture(GL_TEXTURE_2D, this->m_depthMap);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, (int)this->m_shadowWidth, (int)this->m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    // Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // Bind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, this->m_depthMapFbo);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->m_depthMap, 0);

    // Reset
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    // Unbind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CShadowMap::~CShadowMap()
{
	// RAII
	// --
}

// ------------------------------------------------------
// Purpose: Shadow map painting
// ------------------------------------------------------
void CShadowMap::ShadowMapPainting(CGLShader* shader)
{
    // Shadow map matrices
    glm::mat4 lightProjection = glm::mat4(1.0f);
    glm::mat4 lightView = glm::mat4(1.0f);

    float near_plane = 0.1f;
    float far_plane = 75.0f;

    // Define matrices
    lightProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, near_plane, far_plane);
    lightView = glm::lookAt(this->m_lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    this->m_lightSpaceMatrix = lightProjection * lightView;

    // Activate shader
    shader->Use();

    // Pass light space matrix to shader
    shader->SetMat4("lightSpaceMatrix", this->m_lightSpaceMatrix);

    // Set the viewport
    glViewport(0, 0, (int)this->m_shadowWidth, (int)this->m_shadowHeight);

    // Bind depth map framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, this->m_depthMapFbo);

    // Clear
    glClear(GL_DEPTH_BUFFER_BIT);
}

// ------------------------------------------------------
// Purpose: Scene rendering using shadow map
// ------------------------------------------------------
void CShadowMap::SceneRendering(CGLShader* shader)
{
    // Pass light position and light space matrix to shader
    shader->SetVec3("lightPos", this->m_lightPos);
    shader->SetMat4("lightSpaceMatrix", this->m_lightSpaceMatrix);

    // Bind depth map texture
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->m_depthMap);
}

// ------------------------------------------------------
// Purpose: Back to default viewport
// ------------------------------------------------------
void CShadowMap::Reset(SDL_Window* window)
{
    // Unbind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Get current window width and height
    int w = 0;
    int h = 0;

    SDL_GetWindowSize(window, &w, &h);

    // Viewport to default
    glViewport(0, 0, w, h);

    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
