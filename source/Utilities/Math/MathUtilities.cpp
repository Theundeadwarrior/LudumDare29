#include "MathUtilities.h"

#include "SceneManager/Scene/Scene.h"
#include "SceneManager/SceneManager.h"
#include "LowLevelGraphics/WindowManager/WindowManager.h"
#include "SceneManager/Camera/Camera.h"
#include "SceneManager/Camera/PerspectiveCamera.h"

namespace Atum
{
namespace Utilities
{
	
glm::vec3 WindowToWorldCoordinates( glm::uvec2 mousePos )
{
	glm::uvec2 windowSize( LowLevelGraphics::WindowManager::GetInstance().GetCurrentWindowSize() );
	float xNDC = 2.0f *mousePos.x / windowSize.x -1;
	float yNDC = 2.0f *mousePos.y / windowSize.y -1;
	glm::vec4 normalizedPixelPos( xNDC, -yNDC, 1.0f, 1.0f );

	SceneManager::Camera* camera ( SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetCurrentCamera() );
	SceneManager::PerspectiveCamera* pCamera( dynamic_cast<SceneManager::PerspectiveCamera*>(camera) );
	ATUM_ASSERT( pCamera != 0);

	glm::mat4x4 perspective = *pCamera->GetPerspectiveMat();
	glm::mat4x4 invPerspectiveCameraProjectionMatrix( glm::inverse(*pCamera->GetPerspectiveMat()) );
	glm::mat4x4 invCameraViewMatrix ( glm::inverse(pCamera->GetViewMatrix()) );

	glm::vec4 pCameraPosition ( pCamera->GetPosition(), 1.0f );
	glm::vec4 pixelEyePosition ( invPerspectiveCameraProjectionMatrix * normalizedPixelPos );
	glm::vec4 worldPosition ( invCameraViewMatrix * pixelEyePosition /*- pCameraPosition*/ );

	return glm::vec3( worldPosition.x, worldPosition.y, worldPosition.z );
}

float UniformProbability(const float& a, const float& b)
{	
	float seedri;
	seedri=(float) rand() / RAND_MAX;
	return(seedri*(b-a) + a);
}

} // namespace Utilities
} // namespace Atum
