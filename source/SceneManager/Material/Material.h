#ifndef SCENEMANAGER_MATERIAL_H
#define SCENEMANAGER_MATERIAL_H

#include <vector>
#include <bitset>

#include "GLM/include/glm/glm.hpp"
#include "Utilities/Color/Color.h"
#include "SceneManager/Manager/TypedefID.h"
#include "SceneManager/Material/MaterialParameters.h"
#include "LowLevelGraphics/Material/Texture/Texture.h"
#include "LowLevelGraphics/Material/Texture/TextureSkyBox.h"
#include "LowLevelGraphics/Material/Shader/ShaderProgram.h"

namespace Atum
{

namespace SceneManager
{
	class MaterialManager;
	class ShaderListManager;
	class PropertyList; 

	//-----------------------------------------------------------------------------
	class ShaderList
	{
		friend class ShaderListManager;

	public:
		~ShaderList();
		LowLevelGraphics::ShaderProgram* const GetShaderProgram() {return m_shaderProgram;}

	private:
		ShaderList( const char* vertexShaderFileName, const char* fragmentShaderFileName, std::string args); //called by the ShaderList manager

	private:
		LowLevelGraphics::ShaderProgram* m_shaderProgram;

	};

	//-----------------------------------------------------------------------------
	enum MaterialEffectsFlags
	{
		NO_ILLUMINATION = 1,
		PHONG_SHADING = 1 << 1,
		DIFFUSE_MAP = 1 << 2,
		SPECULAR_MAP = 1 << 3,
		PARALLAX_MAP = 1 << 4,
		MATERIALEFFECT_COUNT = 5
	};

	static char* MaterialEffectsName[] = {"PARALLAXMAP", "SPECULARMAP", "DIFFUSEMAP", "PHONG", "NO_LIGHT"};

	//-----------------------------------------------------------------------------
	struct MaterialParameters
	{
		MaterialParameters()
		{}

		~MaterialParameters()
		{
		}

		PhongParameter phongParam;
		PlainColorParameter plainColorParam;
		TextureParameter diffuseMapParam;
		TextureParameter skyBoxParam;
		TextureParameter specularTextureParam;
		ParallaxMapParameters parallaxParam;
	};

	//-----------------------------------------------------------------------------
	// We should have Material as base class over a series of subclass. We could 
	// have a GenericMaterial that would contain all the infos related to the
	// generic shader. The base class would have the methods BindShaderParam and
	// UnbindShaderParam which send the params / textures to the shader. It would
	// also contain a ShaderListID. 
	// 
	// In long term, we could have a system where we can choose a type of Material
	// and the shader is set accordingly to the material. When we build the
	// material, we would have to pass only the parameters and not the shaderList
	// so the shader and param would always be "in sync".
	//-----------------------------------------------------------------------------
	class Material
	{
	friend class MaterialManager;

	public:
		~Material();

		ShaderList* const GetShaderList() const;
		MaterialParameters GetMaterialParameters() const {return m_materialParameters;}

		// Activate Parameters
		void ActivateEffect(MaterialEffectsFlags effect, MaterialParameterBase* parameter);
		void DeactivateEffect(MaterialEffectsFlags effect);

		// Send parameters to shader
        void BindShaderParameters();
        void UnbindShaderParameters();
    		
		// UI Properties
		void GetLightingPropertyList(PropertyList& o_properties);
		void UpdateLightingPropertyList(PropertyList& properties);

		void GetEffectPropertyList(PropertyList& o_properties);
		void UpdateEffectPropertyList(PropertyList& properties);

		void BindDiffuseMapToShader();

    private:
		Material(ShaderListID shaderListId); //use the MaterialManager to create a material
		Material(const MaterialParameters& materialParameters, ShaderListID shaderListId);
		void InitDefaultParameters();
		void UpdateShaderListID();

		// Binding parameters to shader
		
		void BindSkyBoxToShader();
		void BindParallaxToShader();
		void BindPhongToShader();
		void BindPlainColorToShader();

		// Internal Getters
		LowLevelGraphics::Texture* const GetDiffuseMap() const;
		LowLevelGraphics::Texture* const GetParallaxMap() const;
		LowLevelGraphics::TextureSkyBox* const GetSkyBox() const;
			
	private:
		ShaderListID m_shaderListID;
		MaterialParameters m_materialParameters;
	};

} // namespace SceneManager
} // namespace Atum


#endif
