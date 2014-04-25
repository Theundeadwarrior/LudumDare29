#ifndef PROPERTY_T_CPP
#define PROPERTY_T_CPP

#include "Property.h"

#include "UserInterface/Ui/UiUtilities.h"
#include "Utilities/Debug/Debug.h"

namespace Atum
{
namespace SceneManager
{

Property::Property( const std::string& pName, const int pValue )
	:m_name(pName)
{
	m_type = PROPERTY_INT;
	m_value = new int(pValue);
}

Property::Property( const std::string& pName, const float pValue )
	:m_name(pName)
{
	m_type = PROPERTY_FLOAT;
	m_value = new float(pValue);
}

Property::Property( const std::string& pName, const float pValue, const std::string& parameters )
	:m_name(pName)
{
	m_type = PROPERTY_FLOAT;
	m_value = new float(pValue);
	m_parameters = parameters;
}

Property::Property( const std::string& pName, const double pValue )
	:m_name(pName)
{
	m_type = PROPERTY_DOUBLE;
	m_value = new double(pValue);
}

Property::Property( const std::string& pName, const bool pValue )
	:m_name(pName)
{
	m_type = PROPERTY_BOOL;
	m_value = new bool(pValue);
}

Property::Property( const std::string& pName, const std::string& pValue )
	:m_name(pName)
{
	m_type = PROPERTY_STRING;
	m_value = new std::string(pValue);
}

Property::Property( const std::string& pName, const glm::vec3& pValue, const PropertyVectorType& vectorType )
	:m_name(pName)
{
	m_type = PropertyType(vectorType);
	m_value = new glm::vec3(pValue);
}

Property::Property( const std::string& pName, const glm::quat& pValue )
	:m_name(pName)
{
	m_type = PROPERTY_QUATERNION;
	m_value = new glm::quat(pValue);
}

Property::Property( const std::string& pName, const glm::vec4& pValue )
	:m_name(pName)
{
	m_type = PROPERTY_VECTOR4F;
	m_value = new glm::vec4(pValue);
}

Property::~Property()
{
	DeleteValue();
}

void Property::AddParameter( const std::string& parameter )
{
	m_parameters += (" " + parameter);
}

/////////////////// Add new types here ///////////////////
void Property::DeleteValue()
{
	if ( IsIntValue() )
	{
		int* value( reinterpret_cast<int*>(m_value) );
		delete value;
	}
	else if ( IsFloatValue() )
	{
		float* value( reinterpret_cast<float*>(m_value) );
		delete value;
	}
	else if ( IsDoubleValue() )
	{
		double* value( reinterpret_cast<double*>(m_value) );
		delete value;
	}
	else if ( IsBoolValue() )
	{
		bool* value( reinterpret_cast<bool*>(m_value) );
		delete value;
	}
	else if ( IsStringValue() )
	{
		std::string* value( reinterpret_cast<std::string*>(m_value) );
		delete value;
	}
	else if ( IsVector3FValue() )
	{
		glm::vec3* value( reinterpret_cast<glm::vec3*>(m_value) );
		delete value;
	}
	else if ( IsVector4FValue() )
	{
		glm::vec4* value( reinterpret_cast<glm::vec4*>(m_value) );
		delete value;
	}
	else if ( IsQuaternionValue() )
	{
		glm::quat* value( reinterpret_cast<glm::quat*>(m_value) );
		delete value;
	}
	else {
		ATUM_ASSERT_MESSAGE(true, "Cannot Delete Property: No type defined.");
	}
}

bool Property::GetValue( int& o_value ) const
{
	if ( IsIntValue() )
	{
		o_value = *(reinterpret_cast<int*>(m_value));
		return true;
	}
	return false;
}

bool Property::GetValue( float& o_value ) const
{
	if ( IsFloatValue() )
	{
		o_value = *(reinterpret_cast<float*>(m_value));
		return true;
	}
	return false;
}

bool Property::GetValue( double& o_value ) const
{
	if ( IsDoubleValue() )
	{
		o_value = *(reinterpret_cast<double*>(m_value));
		return true;
	}
	return false;
}

bool Property::GetValue( bool& o_value ) const
{
	if ( IsBoolValue() )
	{
		o_value = *(reinterpret_cast<bool*>(m_value));
		return true;
	}
	return false;
}

bool Property::GetValue( std::string& o_value ) const
{
	if ( IsStringValue() )
	{
		o_value = *(reinterpret_cast<std::string*>(m_value));
		return true;
	}
	return false;
}

bool Property::GetValue( glm::vec3& o_value ) const
{
	if ( IsVector3FValue() )
	{
		o_value = *(reinterpret_cast<glm::vec3*>(m_value));
		return true;
	}
	return false;
}

bool Property::GetValue( glm::quat& o_value ) const
{
	if ( IsQuaternionValue() )
	{
		o_value = *(reinterpret_cast<glm::quat*>(m_value));
		return true;
	}
	return false;
}

bool Property::GetValue( glm::vec4& o_value ) const
{
	if ( IsVector4FValue() )
	{
		o_value = *(reinterpret_cast<glm::vec4*>(m_value));
		return true;
	}
	return false;
}

bool Property::SetValue( const int i_value )
{
	if ( IsIntValue() )
	{
		DeleteValue();
		int* value = new int(i_value);
		m_value = value;
		return true;
	}

	return false;
}

bool Property::SetValue( const float i_value )
{
	if ( IsFloatValue() )
	{
		DeleteValue();
		float* value = new float(i_value);
		m_value = value;
		return true;
	}

	return false;
}

bool Property::SetValue( const double i_value )
{
	if ( IsDoubleValue() )
	{
		DeleteValue();
		double* value = new double(i_value);
		m_value = value;
		return true;
	}

	return false;
}

bool Property::SetValue( const bool i_value )
{
	if ( IsBoolValue() )
	{
		DeleteValue();
		bool* value = new bool(i_value);
		m_value = value;
		return true;
	}

	return false;
}

bool Property::SetValue( const std::string& i_value )
{
	if ( IsStringValue() )
	{
		DeleteValue();
		std::string* value = new std::string(i_value);
		m_value = value;
		return true;
	}

	return false;
}

bool Property::SetValue( const glm::vec3& i_value )
{
	if ( IsVector3FValue() )
	{
		DeleteValue();
		glm::vec3* value = new glm::vec3(i_value);
		m_value = value;
		return true;
	}

	return false;
}

bool Property::SetValue( const glm::quat& i_value )
{
	if ( IsQuaternionValue() )
	{
		DeleteValue();
		glm::quat* value = new glm::quat(i_value);
		m_value = value;
		return true;
	}

	return false;
}

bool Property::SetValue( const glm::vec4& i_value )
{
	if ( IsVector4FValue() )
	{
		DeleteValue();
		glm::vec4* value = new glm::vec4(i_value);
		m_value = value;
		return true;
	}

	return false;
}

/////////////////////////////////////////////

bool Property::IsIntValue() const
{
	return (m_type == PROPERTY_INT || m_type == PROPERTY_SELECTION_LIST);
}

bool Property::IsFloatValue() const
{
	 return (m_type == PROPERTY_FLOAT);
}

bool Property::IsDoubleValue() const
{
	 return (m_type == PROPERTY_DOUBLE);
}

bool Property::IsStringValue() const
{
	 return (m_type == PROPERTY_STRING || m_type == PROPERTY_TEXTURE );
}

bool Property::IsBoolValue() const
{
	 return (m_type == PROPERTY_BOOL);
}

bool Property::IsVector3FValue() const
{
	return (m_type == PROPERTY_VECTOR3F || m_type == PROPERTY_COLOR);
}

bool Property::IsQuaternionValue() const
{
	return (m_type == PROPERTY_QUATERNION);
}

bool Property::IsVector4FValue() const
{
	return (m_type == PROPERTY_VECTOR4F);
}


}
}
#endif //PROPERTY_T_CPP
