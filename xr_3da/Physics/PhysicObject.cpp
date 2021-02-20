#include "stdafx.h"
#pragma hdrstop

#include "PhysicObject.h"

#define PHYSICSOBJECT_GRAVITY (-9.81f)

CPhysicsObject::CPhysicsObject()
{
}

CPhysicsObject::~CPhysicsObject()
{
}

void CPhysicsObject::Init(const Fvector& orig, float mass, BOOL IsAffectedByGravity, BOOL RespondsToForces,
						  float linearDamping, float angularDamping, const Fbox& bb)
{
	Fvector defaultAxis;
	Fvector	bbScale;

// fill user data with relevant class data
	bRespondsToForces = RespondsToForces;
	bIsAffectedByGravity = IsAffectedByGravity;

	fLinearDamping = linearDamping;
	fAngularDamping = angularDamping;

	vOriginal.set(orig);

	VERIFY(mass >= 0.1f);

	fMass = mass;
	fMassInv = 1.f / mass;	

// initialize Physics state
	defaultAxis.set(0.f,0.f,1.f);
	for (int i=0; i<2; i++){		
		configs[i].vLinearVelocity.set(0,0,0);
		configs[i].vAngularVelocity.set(0,0,0);
		configs[i].vForce.set(0,0,0);
		configs[i].vTorque.set(0,0,0);
		configs[i].vAppliedForce.set(0,0,0);
		configs[i].vAppliedTorque.set(0,0,0);
		configs[i].qOrientation.rotation( defaultAxis, 0.f );
		configs[i].mXForm.identity();
	}

	mInertiaTensor.identity();
	mInertiaTensorInv.identity();

	bbScale.sub(bb.max,bb.min);

// compute Physics inertia tensor and inverse
// we assume the Physics is an axis-aligned box
	mInertiaTensor.m[0][0] = mass / 12.f * (bbScale.y * bbScale.y + bbScale.z * bbScale.z);
	mInertiaTensor.m[1][1] = mass / 12.f * (bbScale.x * bbScale.x + bbScale.z * bbScale.z);
	mInertiaTensor.m[2][2] = mass / 12.f * (bbScale.x * bbScale.x + bbScale.y * bbScale.y);

	VERIFY(mInertiaTensor.m[0][0] > EPS);
	VERIFY(mInertiaTensor.m[1][1] > EPS);
	VERIFY(mInertiaTensor.m[2][2] > EPS);

	mInertiaTensorInv.m[0][0] = 1/mInertiaTensor.m[0][0];
	mInertiaTensorInv.m[1][1] = 1/mInertiaTensor.m[1][1];
	mInertiaTensorInv.m[2][2] = 1/mInertiaTensor.m[2][2];

	iActiveConfig = 0;
}

// apply force in global frame with changes taking effect on next iteration of gePhysicsObject's owner
void CPhysicsObject::ApplyGlobalFrameForce(const Fvector& force, const Fvector& radiusVector, BOOL isAppliedForce)
{
	Fvector torqueToAdd;
	SConfiguration& cur_config = configs[iActiveConfig];

	if (!isAppliedForce){
		cur_config.vForce.add(force);
		torqueToAdd.crossproduct(radiusVector, force);
		cur_config.vTorque.add(torqueToAdd);
	}else{
		cur_config.vAppliedForce.add(force);
		torqueToAdd.crossproduct(radiusVector, force);
		cur_config.vAppliedTorque.add(torqueToAdd);
	}
}

// apply impulse in global frame with immediate change in velocities
void CPhysicsObject::ApplyGlobalFrameImpulse(const Fvector& Impulse, const Fvector& radiusVector)
{
	Fmatrix33 R, Rt;
	Fvector rCrossRW, rCrossRL, dv, dw;
	SConfiguration& cur_config = configs[iActiveConfig];

	dv.mul(Impulse, fMassInv);
	cur_config.vLinearVelocity.add(dv);

	rCrossRW.crossproduct(radiusVector, Impulse);

	R.set(cur_config.mXForm);
	Rt.transpose(R);

	rCrossRL.MxV(Rt,rCrossRW);
//		Matrix33_MultiplyVec3d(&Rt, &rCrossRW, &rCrossRL);
	dw.MxV(mInertiaTensorInv,rCrossRL);
//		Matrix33_MultiplyVec3d(&pPhysob->vInertiaTensorInverse, &rCrossRL, &dw);
	cur_config.vAngularVelocity.add(dw);
//		Fvector_Add(&dw, &pConfig->angularVelocity, &pConfig->angularVelocity);
}

void CPhysicsObject::ComputeForces()
{
	SConfiguration& cur_config = configs[iActiveConfig];

	// add damping
	cur_config.vLinearVelocity.mul(cur_config.vLinearVelocity, 1.f-fLinearDamping);
	cur_config.vAngularVelocity.mul(cur_config.vAngularVelocity, 1.f-fAngularDamping);

	// clear force and torque accumulators
	cur_config.vForce.set(0,0,0);
	cur_config.vTorque.set(0,0,0);
	
	// add gravity
	if (bIsAffectedByGravity)
		cur_config.vForce.set(0.f, PHYSICSOBJECT_GRAVITY * fMass, 0.f);

	// add forces
	if (!bRespondsToForces) return;

	cur_config.vForce.add(cur_config.vAppliedForce);
	cur_config.vTorque.add(cur_config.vAppliedTorque);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// integrate a gePhysicsObject's equations of motion by time step deltaTime
void CPhysicsObject::Integrate(float dt)
{
	Fvector tau;
	Fvector a, dv;
	Fvector angularMomentum, angularAcceleration;
	Fvector omega_x_L, term1, dtTimesOmega;
	Fmatrix33 R, Rt;
	
	Fquaternion qdot;
	float G[3][4], Gt[4][3];
	float dt2 = 0.5f * (dt * dt);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SConfiguration &src_config = configs[iActiveConfig];
	SConfiguration &tgt_config = configs[1 - iActiveConfig];

	a.mul(src_config.vForce, fMassInv);
	dv.mul(a,dt);
	tgt_config.vLinearVelocity.add(src_config.vLinearVelocity,dv);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	angularMomentum.MxV(mInertiaTensor, src_config.vAngularVelocity);
	omega_x_L.crossproduct(src_config.vAngularVelocity, angularMomentum);

	// compute torque in body frame (= R ^ T * torque)
	R.set(src_config.mXForm);
	Rt.transpose(R);
	tau.MxV(Rt, src_config.vTorque);

	term1.sub(tau, omega_x_L);

	angularAcceleration.MxV(mInertiaTensorInv, term1);

	dtTimesOmega.MxV(R,src_config.vAngularVelocity);
	//geXForm3d_Rotate(&src_config.xform, &src_config.angularVelocity, &dtTimesOmega);
	dtTimesOmega.mul(dt);

	G[0][0] = -src_config.qOrientation.x; 
	G[0][1] = src_config.qOrientation.w; 
	G[0][2] = -src_config.qOrientation.z; 
	G[0][3] = src_config.qOrientation.y;

	G[1][0] = -src_config.qOrientation.y; 
	G[1][1] = src_config.qOrientation.z; 
	G[1][2] = src_config.qOrientation.w; 
	G[1][3] = -src_config.qOrientation.x;

	G[2][0] = -src_config.qOrientation.z; 
	G[2][1] = -src_config.qOrientation.y; 
	G[2][2] = src_config.qOrientation.x; 
	G[2][3] = src_config.qOrientation.w;

	for (int i=0; i<3; i++)
		for (int j=0; j<4; j++)
			Gt[j][i] = 0.5f * G[i][j];

	qdot.w = Gt[0][0] * dtTimesOmega.x + Gt[0][1] * dtTimesOmega.y + Gt[0][2] * dtTimesOmega.z;
	qdot.x = Gt[1][0] * dtTimesOmega.x + Gt[1][1] * dtTimesOmega.y + Gt[1][2] * dtTimesOmega.z;
	qdot.y = Gt[2][0] * dtTimesOmega.x + Gt[2][1] * dtTimesOmega.y + Gt[2][2] * dtTimesOmega.z;
	qdot.z = Gt[3][0] * dtTimesOmega.x + Gt[3][1] * dtTimesOmega.y + Gt[3][2] * dtTimesOmega.z;

	tgt_config.qOrientation.w = src_config.qOrientation.w + qdot.w;
	tgt_config.qOrientation.x = src_config.qOrientation.x + qdot.x;
	tgt_config.qOrientation.y = src_config.qOrientation.y + qdot.y;
	tgt_config.qOrientation.z = src_config.qOrientation.z + qdot.z;

	tgt_config.qOrientation.normalize();
	tgt_config.mXForm.rotation(tgt_config.qOrientation);
	
	tgt_config.vAngularVelocity.x = src_config.vAngularVelocity.x + dt * angularAcceleration.x;	
	tgt_config.vAngularVelocity.y = src_config.vAngularVelocity.y + dt * angularAcceleration.y;
	tgt_config.vAngularVelocity.z = src_config.vAngularVelocity.z + dt * angularAcceleration.z;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tgt_config.mXForm.c.x =	src_config.mXForm.c.x + dt * src_config.vLinearVelocity.x + dt2 * a.x;
	tgt_config.mXForm.c.y =	src_config.mXForm.c.y + dt * src_config.vLinearVelocity.y + dt2 * a.y;
	tgt_config.mXForm.c.z =	src_config.mXForm.c.z + dt * src_config.vLinearVelocity.z + dt2 * a.z;
}
