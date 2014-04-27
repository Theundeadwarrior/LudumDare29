#ifndef SCENEMANAGER_FOREGROUND_H
#define SCENEMANAGER_FOREGROUND_H

#include "SceneManager/Objects/GameplayObjects/GamePlayObject.h"
#include "SceneManager/Manager/TypedefID.h"

namespace Atum
{
namespace SceneManager
{
    
class Foreground : public GamePlayObject
{
public:
    Foreground();   
    ~Foreground();

	virtual const GamePlayObject::GamePlayObjectType GetGameplayObjectType()const{return GamePlayObject::GamePlayObjectType_Invalid;}

	ShaderListID GetShaderID();

	virtual TextureId GetTextureID();
	virtual MaterialID GetMaterialID();

	void Move();

	virtual void BindShaderParameters() override;

private:
	float m_uOffset;
};

} // namespace SceneManager
} // namespace Atum


#endif
