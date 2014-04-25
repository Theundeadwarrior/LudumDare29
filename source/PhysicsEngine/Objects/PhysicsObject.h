#ifndef PHYSICSENGINE_OBJECTS_PHYSICRIGIDOBJECT_H
#define PHYSICSENGINE_OBJECTS_PHYSICRIGIDOBJECT_H

#include <PhysicsEngine/PhysicsUtilities.h>
#include <PhysX/include/PxPhysicsAPI.h>
#include <Utilities/Debug/Debug.h>

namespace Atum
{
	namespace PhysicsEngine
	{
		class PhysicsObject
		{
		public:
			PhysicsObject(physx::PxPhysics * physics, const physx::PxReal & staticFriction, const physx::PxReal & dynamicFriction, const physx::PxReal & restitution);
			PhysicsObject(physx::PxPhysics * physics, physx::PxMaterial * material);
			virtual ~PhysicsObject();

			virtual ObjectType GetObjectType() const = 0;
			virtual physx::PxRigidActor * const GetActor() const = 0;
			inline physx::PxMaterial * const GetMaterial() const {return m_material; };
			virtual void SetPosition(const physx::PxVec3 & position) = 0; // the matrix rotation is identity

		protected:
			physx::PxMaterial * m_material;
			physx::PxShape * m_shape;
			physx::PxPhysics * m_physics;
			physx::PxCooking * m_cooking;

			physx::PxReal m_staticFriction;
			physx::PxReal m_dynamicFriction;
			physx::PxReal m_restitution;
		};
	}
}

#endif