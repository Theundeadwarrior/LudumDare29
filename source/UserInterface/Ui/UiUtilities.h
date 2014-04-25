#ifndef UI_UTILITIES_H
#define UI_UTILITIES_H

#include <string>
#include <vector>

#define UI_PARAM_GLOBAL		"GLOBAL"
#define UI_PARAM_MIN		"min="
#define UI_PARAM_MAX		"max="
#define UI_PARAM_STEP		"step="
#define UI_PARAM_KEY_INCR	"keyIncr="
#define UI_PARAM_KEY_DECR	"keyDecr="
#define UI_PARAM_HELP		"help="
#define UI_PARAM_GROUP		"group="
#define UI_PARAM_OPENED		"opened="
#define UI_PARAM_LABEL		"label="
#define UI_PARAM_SIZE		"size="
#define UI_PARAM_COLOR		"color="
#define UI_PARAM_PRECISION	"precision="
#define UI_PARAM_VISIBLE	"visible="
#define UI_PARAM_ARROW		"arrowcolor="
#define UI_PARAM_READ_ONLY	"readonly="
#define UI_PARAM_POSITION	"position="
#define UI_PARAM_FIT_COLUMN	"valueswidth="
#define UI_PARAM_HIDDEN	"iconified="

#define UI_LIGHTING_TECH_GROUP "Lighting_technique"
#define UI_EFFECTS_GROUP		"Effects"

namespace Atum
{
namespace UserInterface
{

	namespace UiUtilities{
		int strToInt( const std::string& toConvert );
		std::string intToStr( int toConvert );

		float strToFloat( const std::string toConvert );
		std::string floatToStr( float toConvert );

		double strToDouble( const std::string toConvert );
		std::string doubleToStr( double toConvert );

		std::string DisplayOpenFileDialog( const std::vector<std::string>& extensionList );

		std::string GetFileFromPath( const std::string& fullPath );
	}

}
}

#endif //UI_UTILITIES_H