#ifndef UI_PANEL_H
#define UI_PANEL_H

#include <string>
#include "AntTweakBar/include/AntTweakBar.h"
#include "UiElement.h"
#include "UiUtilities.h"

namespace Atum
{
namespace UserInterface
{

class UiPanel
{
	public:
		UiPanel( const std::string& pName );
		virtual ~UiPanel();

		virtual void Init();
		void RefreshPanel();

		std::string GetName() const { return m_name; }
		TwBar* const GetPanel() const { return m_panel; }

		void SetHelpText( const std::string& helpText );
		void SetSize( int width, int height );
		void SetColor( int R, int G, int B );
		void SetHidden( bool state );
		void SetPosition( int x, int y );

		void AddSeparator( const std::string& parameters="" );
		void AddReadOnlyString( const std::string& roString, const std::string& parameters="" );
		void FitColumnContent();

		bool RemoveAllElements();
		bool RemoveElement( const std::string& name );
		bool FoldGroup( bool foldStatus, const std::string& groupName );

		static void TW_CALL CopyStdStringToClient(std::string& destinationClientString, const std::string& sourceLibraryString);

	protected:
		TwBar* m_panel;
		std::string m_name;
};

}
}

#endif //UI_PANEL_H
