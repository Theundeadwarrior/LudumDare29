#ifndef PHYSICSENGINE_OBJECTS_PHYSICSTATICOBJECT_H
#define PHYSICSENGINE_OBJECTS_PHYSICSTATICOBJECT_H

#include <PhysX/include/PxPhysicsAPI.h>
#include <PhysicsEngine/PhysicsUtilities.h>
#include <PhysicsEngine/Objects/PhysicsObject.h>
#include <Utilities/Debug/Debug.h>

namespace Atum
{
	namespace PhysicsEngine
	{
		class PhysicsStaticObject : public PhysicsObject
		{
		public:
			PhysicsStaticObject(physx::PxPhysics * physics, physx::PxConvexMesh* convexMesh, const physx::PxVec3 & position, const physx::PxReal & staticFriction, const physx::PxReal & dynamicFriction, const physx::PxReal & restitution);
			PhysicsStaticObject(physx::PxPhysics * physics, physx::PxRigidStatic * actor, physx::PxShape * shape, physx::PxMaterial * material);
			~PhysicsStaticObject();

			inline physx::PxRigidActor * const GetActor() const {return m_actor; };
			ObjectType GetObjectType() const { return StaticObjectType; };

			void SetPosition(const physx::PxVec3 & position); // the matrix rotation is identity

		private:

			physx::PxRigidStatic * m_actor;
		};
	}
}

#endif