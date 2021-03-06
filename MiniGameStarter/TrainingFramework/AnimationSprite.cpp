#include "AnimationSprite.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "Application.h"
AnimationSprite::AnimationSprite()
	:m_currentFrame(0),m_frameTime(0),m_numFrames(0),m_currentFrameTime(0),m_numFramesInLine(0), m_currentColumn(0),m_currentLine(0)
{
}

AnimationSprite::AnimationSprite( std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, float x, float y)
	:Sprite2D(model,shader,texture), m_numFrames(numFrames), m_frameTime(frameTime),m_currentFrame(0), m_currentFrameTime(0)
{
	Set2DPosition(Vector2(x, y));
	Init();
}
AnimationSprite::AnimationSprite(int numFrames, float frameTime, float numFramesInLine,float x, float y)
	: m_numFrames(numFrames), m_frameTime(frameTime),m_numFramesInLine(numFramesInLine), m_currentFrame(0), m_currentFrameTime(0), m_currentColumn(0), m_currentLine(0)
{
	Set2DPosition(Vector2(x, y));
	Init();
}
AnimationSprite::~AnimationSprite()
{
}

void AnimationSprite::Init()
{
	SetCamera(Application::GetInstance()->GetCamera());
	CalculateWorldMatrix();
}

void AnimationSprite::Draw()
{
	if (m_pCamera == nullptr) return;
	glUseProgram(m_pShader->m_program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

	GLuint iTempShaderVaribleGLID = -1;
	Matrix wvpMatrix;

	wvpMatrix = m_worldMatrix * m_pCamera->GetLookAtCameraMatrix();

	if (m_pTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
		if (m_pShader->m_iTextureLoc[0] != -1)
			glUniform1i(m_pShader->m_iTextureLoc[0], 0);
	}
	else
	{
		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_color");
		if (iTempShaderVaribleGLID != -1)
			glUniform4f(iTempShaderVaribleGLID, m_color.x, m_color.y, m_color.z, m_color.w);
	}


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_uv");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_UV);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_alpha");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, 1.0);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_wvpMatrix");
	if (iTempShaderVaribleGLID != -1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, wvpMatrix.m[0]);


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentFrame");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float)m_currentFrame);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_numFrames");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float)m_numFrames);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_numFramesInLine");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float)m_numFramesInLine);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_numLines");
	if (iTempShaderVaribleGLID != -1)
 		glUniform1f(iTempShaderVaribleGLID, (float)(m_numFrames/m_numFramesInLine));

	
	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentColumn");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float)m_currentColumn);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentLine");
	if (iTempShaderVaribleGLID != -1)
 		glUniform1f(iTempShaderVaribleGLID, (float)m_currentLine);

	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void AnimationSprite::Update(GLfloat deltatime)
{
	m_currentFrameTime += deltatime;
	if (m_currentFrameTime >= m_frameTime) {
		m_currentFrame++;	
		m_currentColumn = (m_currentFrame % m_numFramesInLine);
		m_currentLine = (m_currentFrame / m_numFramesInLine);
		if (m_currentFrame >= m_numFrames) {
			m_currentFrame = 0;
		}
		m_currentFrameTime -= m_frameTime;
	}
}

