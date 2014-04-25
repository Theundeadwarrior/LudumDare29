#ifndef FUNCTIONNALTEST_MATERIAL_H
#define FUNCTIONNALTEST_MATERIAL_H

namespace Atum
{
namespace SceneManager{class Scene;}

namespace FunctionnalTest
{

void MaterialTextureTest(SceneManager::Scene& scene);
void MaterialParallaxMapTest(SceneManager::Scene& scene);
void MaterialSkyboxUpperRightTest(SceneManager::Scene& scene);
void MaterialSkyboxLowerLeftTest(SceneManager::Scene& scene);
void MaterialVariationTest(SceneManager::Scene& scene);

}
}

#endif