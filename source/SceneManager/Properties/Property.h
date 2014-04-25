#ifndef PROPERTY_T_H
#define PROPERTY_T_H

#include <string>
#include <list>
#include <utility>
#include "GLM/include/glm/glm.hpp"
#include "GLM/include/glm/gtx/quaternion.hpp"

namespace Atum
{
namespace SceneManager
{
	enum PropertyType {
		PROPERTY_NO_TYPE = 0,
		PROPERTY_INT,
		PROPERTY_DOUBLE,
		PROPERTY_FLOAT,
		PROPERTY_STRING,
		PROPERTY_BOOL,
		PROPERTY_VECTOR3F,
		PROPERTY_VECTOR4F,
		PROPERTY_QUATERNION,
		PROPERTY_COLOR,
		PROPERTY_TEXTURE,
		PROPERTY_SELECTION_LIST
	};

	enum PropertyVectorType {
		VECTORTYPE_VEC3 = PROPERTY_VECTOR3F,
		VECTORTYPE_COLOR = PROPERTY_COLOR
	};

	class Property
	{
		public:

			Property( const std::string& pName, const int pValue );
			Property( const std::string& pName, const float pValue );
			Property( const std::string& pName, const float pValue, const std::string& parameters );
			Property( const std::string& pName, const double pValue );
			Property( const std::string& pName, const bool pValue );
			Property( const std::string& pName, const std::string& pValue );
			Property( const std::string& pName, const glm::vec3& pValue, const PropertyVectorType& vectorType=VECTORTYPE_VEC3 );
			Property( const std::string& pName, const glm::vec4& pValue );
			Property( const std::string& pName, const glm::quat& pValue );
			virtual ~Property();

			std::string GetName() const { return m_name; }
			PropertyType GetType() const { return m_type; }
			std::string GetParameters() const { return m_parameters; }
			void* GetValue() const { return m_value; }
			void AddParameter( const std::string& parameter );

			bool GetValue ( int& o_value ) const;
			bool GetValue ( float& o_value ) const;
			bool GetValue ( double& o_value ) const;
			bool GetValue ( bool& o_value ) const;
			bool GetValue ( std::string& o_value ) const;
			bool GetValue ( glm::vec3& o_value ) const;
			bool GetValue ( glm::vec4& o_value ) const;
			bool GetValue ( glm::quat& o_value ) const;

			bool SetValue ( const int i_value );
			bool SetValue ( const float i_value );
			bool SetValue ( const double i_value );
			bool SetValue ( const bool i_value );
			bool SetValue ( const std::string& i_value );
			bool SetValue ( const glm::vec3& i_value );
			bool SetValue ( const glm::vec4& i_value );
			bool SetValue ( const glm::quat& i_value );
	
		private:
			bool IsIntValue			() const;
			bool IsFloatValue		() const;
			bool IsDoubleValue		() const;
			bool IsStringValue		() const;
			bool IsBoolValue		() const;
			bool IsVector3FValue	() const;
			bool IsVector4FValue	() const;
			bool IsQuaternionValue	() const;

		protected:
			void DeleteValue();

			std::string m_name;
			void* m_value;
			PropertyType m_type;
			std::string m_parameters;
	};
}
}

#endif //PROPERTY_T_H