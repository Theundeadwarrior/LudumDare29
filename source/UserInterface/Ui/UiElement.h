#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include "AntTweakBar/include/AntTweakBar.h"
#include <string>

namespace Atum
{
namespace UserInterface
{

class UiPanel;

class UiElement
{ 
	public:
		UiElement( const std::string& pName );
		virtual ~UiElement() {};

		void SetLabel( const std::string& pLabel ) { m_label = pLabel; }
		void SetHelp( const std::string& pHelp ) { m_help = pHelp; }
		void SetGroup( const std::string& pGroup ) { m_group = pGroup; }
		void SetVisible( bool pVisible ) { m_visible = pVisible; }
		void SetReadOnly( bool ro ) { m_readOnly = ro; }

		std::string GetName() const { return m_name; }
		TwType GetType() const { return m_type; }
		void AddStringParameters( const std::string& stringToAdd ); 

		virtual bool AddToPanel( const UiPanel& panel ) = 0;
		virtual std::string GetParameters() const;

	protected:
		TwType m_type;
		std::string m_name;
		std::string m_label;
		std::string m_help;
		std::string m_group;
		bool m_visible;
		bool m_readOnly;
};

///////// FLOAT ////////////////////
class UiElementFloat: public UiElement
{ 
public:
	UiElementFloat( const std::string& p_name, float* pValue );
	~UiElementFloat() {};

	void SetMin( float pMin ) { m_min = pMin; }
	void SetMax( float pMax ) { m_max = pMax; }
	void SetStep( float pStep ) { m_step = pStep; }
	void SetKeyIncr( char pKeyIncr ) { m_keyIncr = pKeyIncr; }
	void SetKeyDecr( char pKeyDecr ) { m_keyDecr = pKeyDecr; }
	void SetPrecision( int precision) { m_precision = precision; }

	bool AddToPanel( const UiPanel& panel );
	std::string GetParameters() const;

private:
	float m_min;
	float m_max;
	float m_step;
	char m_keyIncr;
	char m_keyDecr;
	int m_precision;

	float* m_valuePtr;
};

////////////// BOOL /////////////////////
class UiElementBool: public UiElement
{ 
public:
	UiElementBool( const std::string& p_name, bool* pValue );
	~UiElementBool() {};

	bool AddToPanel( const UiPanel& panel );

private:
	bool* m_valuePtr;
};


////////////// STRING /////////////////////
class UiElementString: public UiElement
{ 
public:
	UiElementString( const std::string& p_name, std::string* pValue );
	~UiElementString() {};

	bool AddToPanel( const UiPanel& panel );

private:
	std::string* m_valuePtr;
};


}
}

#endif //UI_ELEMENT_H


