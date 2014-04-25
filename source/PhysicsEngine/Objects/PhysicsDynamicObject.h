#ifndef PHYSICSENGINE_OBJECTS_PHYSICDYNAMICOBJECT_H
#define PHYSICSENGINE_OBJECTS_PHYSICDYNAMICOBJECT_H

#include <PhysX/include/PxPhysicsAPI.h>
#include <PhysicsEngine/PhysicsUtilities.h>
#include <PhysicsEngine/Objects/PhysicsObject.h>
#include <Utilities/Debug/Debug.h>

namespace Atum
{
	namespace PhysicsEngine
	{
		class PhysicsDynamicObject : public PhysicsObject
		{
		public:
			PhysicsDynamicObject(physx::PxPhysics * physics, physx::PxConvexMesh* convexMesh, const physx::PxReal & mass, const physx::PxVec3 & position, const physx::PxReal & staticFriction, const physx::PxReal & dynamicFriction, const physx::PxReal & restitution);
			~PhysicsDynamicObject();

			inline physx::PxRigidActor * const GetActor() const {return m_actor; };
			ObjectType GetObjectType() const { return DynamicObjectType; };

			void ApplyForce(const physx::PxVec3 & force);
			void ApplyTorque(const physx::PxVec3 & torque);

			void SetPosition(const physx::PxVec3 & position); // the matrix rotation is identity

		private:
			physx::PxRigidDynamic * m_actor;
			physx::PxReal m_mass;
		};
	}
}

#endif