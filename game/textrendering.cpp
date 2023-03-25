#include "textrendering.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CTextRendering::CTextRendering(std::string filePath)
{
	FT_Library ft;
	
	// Init freetype lib
	if (FT_Init_FreeType(&ft))
	{
		std::cerr << "Could not init FreeType Library" << std::endl;
	}

	FT_Face face;

	// Load font
	if (FT_New_Face(ft, filePath.c_str(), 0, &face))
	{
		std::cerr << "Failed to load font: " << filePath << std::endl;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);
	
	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned char c = 0; c < 128; c++)
	{
		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cerr << "Failed to load glyph" << std::endl;
			continue;
		}

		GLuint id;

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SCharacter character = {
			id,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};

		this->m_characters.insert(std::pair<char, SCharacter>(c, character));
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &this->m_vao);
	glGenBuffers(1, &this->m_vbo);

	glBindVertexArray(this->m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CTextRendering::~CTextRendering()
{
	// RAII
	// --
}

// ------------------------------------------------------
// Purpose: Render text
// ------------------------------------------------------
void CTextRendering::RenderText(CGLShader* shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, GLuint width, GLuint height)
{
	shader->Use();

	glm::mat4 projection = glm::ortho(0.0f, (GLfloat)width, 0.0f, (GLfloat)height);
	shader->SetMat4("projection", projection);

	shader->SetVec3("textColor", color);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->m_vao);

	// Iterate through all characters
	std::string::const_iterator c;

	for (c = text.begin(); c != text.end(); c++)
	{
		SCharacter ch = this->m_characters[*c];

		float xpos = x + ch.bearing.x * scale;
		float ypos = y - (ch.size.y - ch.bearing.y) * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;

		// Update vbo for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};

		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.id);

		// Update content of vbo memory
		glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.advance >> 6) * scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
