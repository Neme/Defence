#include "BackgroundLayer.h"

using namespace cocos2d;

//---------------------------------------------------------------------//
BackgroundLayer::BackgroundLayer()
{
	if (!Layer::init())
		return;

	this->setAnchorPoint({ 0, 0 });


	//Create background sprite and add a shader
	m_backgroundSprite = util::create<Sprite>();
	m_backgroundSprite->setTextureRect({ 0, 0, this->getContentSize().width, this->getContentSize().height });
	m_backgroundSprite->setAnchorPoint({ 0, 0 });


	auto shader = GLProgram::createWithFilenames("shader/background.vert", "shader/background.frag");
	shader->link();

	auto glProgramState = GLProgramState::create(shader);
	glProgramState->setUniformVec2("resolution", Director::getInstance()->getWinSize());
	glProgramState->setUniformVec4("startColor", { 0.875f, 0.89f, 0.922f, 1.0f });
	glProgramState->setUniformVec4("endColor", { 0.804f, 0.847f, 0.937f, 1.0f });

	m_backgroundSprite->setGLProgram(shader);
	m_backgroundSprite->setGLProgramState(glProgramState);


	shader->updateUniforms();

	this->addChild(m_backgroundSprite);
}

//-----------------------------------------------------------//


