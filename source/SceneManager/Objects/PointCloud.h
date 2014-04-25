#ifndef SCENEMANAGER_POINTCLOUD_H
#define SCENEMANAGER_POINTCLOUD_H

#include "Object.h"
#include "Events/InputKeyboardListener.h"
#include "Events/InputMouseListener.h"
#include "Events/KeyboardEvent.h"

#define POINTCLOUD_XMIN_NAME "XMin"
#define POINTCLOUD_XMAX_NAME "XMax"
#define POINTCLOUD_YMIN_NAME "YMin"
#define POINTCLOUD_YMAX_NAME "YMax"
#define POINTCLOUD_ZMIN_NAME "ZMin"
#define POINTCLOUD_ZMAX_NAME "ZMax"
#define POINTCLOUD_DISTANCESHELLSPHERE_NAME "DistanceShellSphere"
#define POINTCLOUD_DISTANCEVIEWPLANE_NAME "DistanceViewPlane"

namespace Atum { namespace SceneManager { class PropertyList; }}

namespace Atum
{
namespace SceneManager
{
	enum SelectedAxe
	{
		XAXE_SELECTED = 0,
		YAXE_SELECTED,
		ZAXE_SELECTED,
		DISTANCESHELLSPHERE_SELECTED
	};

	const float DELTA = 0.05f;

	class PointCloud : public Object, public Events::InputKeyboardListener, public Events::InputMouseListener
	{
	public:
		PointCloud(MaterialID materialID, GeometryID geomId, const Transform & transform, const Utilities::AABB & aabb);
		~PointCloud();

		PropertyList GetPropertyList();
		virtual void NotifyKeyPressed( const Events::KeyboardEvent& event);

		virtual void NotifyMouseClicked( const Events::MouseEvent& event );
		virtual void NotifyMouseMoved( const Events::MouseEvent& event );

		void GetPropertyList ( PropertyList& o_properties ) const;
		void UpdatePropertyList ( const PropertyList& i_properties );

	private:
		float m_xMin;
		float m_xMax;
		float m_yMin;
		float m_yMax;
		float m_zMin;
		float m_zMax;
		float m_distanceShellSphere;
		float m_distanceViewPlane;
		SelectedAxe m_selectedAxe;

		std::string m_parametersXMin;
		std::string m_parametersXMax;
		std::string m_parametersYMin;
		std::string m_parametersYMax;
		std::string m_parametersZMin;
		std::string m_parametersZMax;
		std::string m_parametersDistanceShellSphere;
		std::string m_parametersDistanceViewPlane;
	};

} // namespace SceneManager
} // namespace Atum


#endif