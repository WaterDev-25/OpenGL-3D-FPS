#include "game.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CGame::CGame(SDL_Window* window) :
	m_pWindow(window),
	m_event({ 0 }),
    m_deltaTime(0),
    m_lastFrame(0),
    m_lightPos(glm::vec3(4.0f, 14.0f, 5.0f))
{
    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize shader
	std::string vertexShader =
#include "shaders/vs_shader.glsl"
		;

	std::string fragmentShader =
#include "shaders/fs_shader.glsl"
		;

	this->m_pShader = new CGLShader(vertexShader.c_str(), fragmentShader.c_str());

    // Initialize skybox shader
    vertexShader =
#include "shaders/vs_skybox.glsl"
        ;

    fragmentShader =
#include "shaders/fs_skybox.glsl"
        ;

    this->m_pSkyboxShader = new CGLShader(vertexShader.c_str(), fragmentShader.c_str());

    // Initialize shadow map shader
    vertexShader =
#include "shaders/vs_shadow_map.glsl"
        ;

    fragmentShader =
#include "shaders/fs_shadow_map.glsl"
        ;

    this->m_pShadowMapShader = new CGLShader(vertexShader.c_str(), fragmentShader.c_str());

    // Initialize text rendering shader
    vertexShader =
#include "shaders/vs_text_rendering.glsl"
        ;

    fragmentShader =
#include "shaders/fs_text_rendering.glsl"
        ;

    this->m_pTextRenderingShader = new CGLShader(vertexShader.c_str(), fragmentShader.c_str());

    this->m_pTextRendering = new CTextRendering("res/fonts/arial.ttf");

    this->m_pDebug = new CDebug(this->m_pTextRenderingShader, this->m_pTextRendering, this->m_pWindow);

    this->m_pPhysics = new CPhysics();

    this->m_pMap = new CMap("res/maps/deathmatch/deathmatch.obj");

    // Load cubemap
    std::vector<std::string> faces
    {
        "res/skyboxes/cloud/right.png",
        "res/skyboxes/cloud/left.png",
        "res/skyboxes/cloud/top.png",
        "res/skyboxes/cloud/bottom.png",
        "res/skyboxes/cloud/front.png",
        "res/skyboxes/cloud/back.png"
    };

    this->m_pCubeMap = new CCubeMap(faces);

    this->m_pShadowMap = new CShadowMap(2048, 2048, this->m_lightPos);

    this->m_pPlayer = new CPlayer(glm::vec3(0.0f, 10.0f, 0.0f), this->m_pDebug, this->m_pMap, this->m_pPhysics);

    // Shader configuration
    this->m_pShader->Use();
    this->m_pShader->SetInt("diffuseTexture", 0);
    this->m_pShader->SetInt("shadowMap", 1);

    this->m_pSkyboxShader->Use();
    this->m_pSkyboxShader->SetInt("skybox", 0);
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CGame::~CGame()
{
	// RAII
	delete this->m_pShader;
    delete this->m_pSkyboxShader;
    delete this->m_pShadowMapShader;
    delete this->m_pTextRenderingShader;
    delete this->m_pTextRendering;
    delete this->m_pDebug;
    delete this->m_pPhysics;
    delete this->m_pMap;
    delete this->m_pPlayer;
    delete this->m_pCubeMap;
    delete this->m_pShadowMap;
}

// ------------------------------------------------------
// Purpose: Render, game logic...
// ------------------------------------------------------
void CGame::Update(bool* isRunning)
{
    // Pre-frame time logic
    float currentFrame = (float)SDL_GetTicks() / 1000.0f;
    this->m_deltaTime = currentFrame - this->m_lastFrame;
    this->m_lastFrame = currentFrame;

	// Handle event
	while (SDL_PollEvent(&this->m_event))
	{
		// Close window event
		if (this->m_event.type == SDL_QUIT)
			*isRunning = false;
	}

    // Clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Shadow map painting
    this->m_pShadowMap->ShadowMapPainting(this->m_pShadowMapShader);

    // Draw map
    this->m_pMap->Draw(this->m_pShadowMapShader);
    
    // Back to default viewport
    this->m_pShadowMap->Reset(this->m_pWindow);

    // Activate shader
    this->m_pShader->Use();

    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    
    // Get current window width and height
    int w = 0;
    int h = 0;

    SDL_GetWindowSize(this->m_pWindow, &w, &h);

    projection = glm::perspective(glm::radians(this->m_pPlayer->GetCamera()->GetFov()), (float)w / (float)h, 0.1f, 100.0f);
    view = this->m_pPlayer->GetCamera()->GetViewMatrix();

    // Pass projection and view matrix to shader
    this->m_pShader->SetMat4("projection", projection);
    this->m_pShader->SetMat4("view", view);

    // Pass view position, light position and light space matrix to shader
    this->m_pShader->SetVec3("viewPos", this->m_pPlayer->GetPosition());

    // Scene rendering using shadow map
    this->m_pShadowMap->SceneRendering(this->m_pShader);

    // Draw map
    this->m_pMap->Draw(this->m_pShader);

    // Call player update function
    this->m_pPlayer->Update(this->m_deltaTime);

    this->m_pPlayer->RenderWeapon(this->m_pShader);

    // Draw cubemap
    this->m_pSkyboxShader->Use();

    view = glm::mat4(glm::mat3(this->m_pPlayer->GetCamera()->GetViewMatrix()));

    // Pass view and projection matrix to shader
    this->m_pSkyboxShader->SetMat4("view", view);
    this->m_pSkyboxShader->SetMat4("projection", projection);

    // Draw cubemap
    this->m_pCubeMap->Draw();

    // Render debug message
    this->m_pDebug->Render();
}
