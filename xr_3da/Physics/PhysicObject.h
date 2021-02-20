#ifndef PHYSIC_OBJECT_H
#define PHYSIC_OBJECT_H

class CPhysicsObject{
	float		fMass, fMassInv;
	Fvector		vOriginal;
	Fmatrix33	mInertiaTensor, mInertiaTensorInv;
	BOOL		bIsAffectedByGravity;
	BOOL		bRespondsToForces;
	float		fLinearDamping;
	float		fAngularDamping;

	struct SConfiguration{
		Fmatrix mXForm; // includes location and rotation matrix
		Fvector vLinearVelocity;
		Fvector vAngularVelocity;
		Fvector vForce, vAppliedForce;
		Fvector vTorque, vAppliedTorque;
		Fquaternion qOrientation;
	}configs[2];
	int			iActiveConfig;

public:	
				CPhysicsObject			();
	virtual		~CPhysicsObject			();

	void		Init					(const Fvector& orig, float mass,
										 BOOL IsAffectedByGravity, BOOL RespondsToForces,
										 float linearDamping,	   float angularDamping,
										 const Fbox& bb);

	void		ApplyGlobalFrameForce	(const Fvector& force, const Fvector& pRadVec, BOOL isAppliedForce);
	void		ApplyGlobalFrameImpulse	(const Fvector& pImpulse, const Fvector& pRadVec);
	void		ComputeForces			();
	void		Integrate				(float deltaTime);
	void		ChangeConfig			(){iActiveConfig = (iActiveConfig==0?1:0);}
};

#endif
