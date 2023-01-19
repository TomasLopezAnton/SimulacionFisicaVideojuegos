// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2018 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  



#include "Camera.h"
#include <ctype.h>
#include "foundation/PxMat33.h"
#include <iostream>

using namespace physx;

namespace Snippets
{

Camera::Camera(const PxVec3& eye, const PxVec3& dir)
{
	mEye = eye;
	mDir = dir.getNormalized();
	mMouseX = 0;
	mMouseY = 0;
}

void Camera::handleMouse(int button, int state, int x, int y)
{
	PX_UNUSED(state);
	PX_UNUSED(button);
	mMouseX = x;
	mMouseY = y;
}

physx::PxVec3 Camera::handleKey(unsigned char key, int x, int y, physx::PxVec3 d, physx::PxTransform* target = nullptr, float speed)
{
	PX_UNUSED(x);
	PX_UNUSED(y);

	float distance = 1;
	float hSpeed = 1;
	PxVec3 v;

	if (target != nullptr)
	{
		distance = (target->p - mEye).magnitude();
		//std::cout << "Initial distance: " << distance << "\n";

	    hSpeed = speed * physx::PxClamp(distance / 10, (float)1.0, (float)100.0);
	}


	PxVec3 viewY = mDir.cross(PxVec3(0,1,0)).getNormalized();
	switch(toupper(key))
	{
	case 'W':	mEye += mDir*0.1f*speed;		break;
	case 'S':	mEye -= mDir*0.1f*speed;		break;
	case 'A':
		v = (d - (viewY * hSpeed * speed)).getNormalized() * distance;
		mEye = PxVec3( v.x, d.y, v.z) + target->p;
		break;
	case 'D':
		v = (d + (viewY * hSpeed * speed)).getNormalized() * distance;
		mEye = PxVec3(v.x, d.y, v.z) + target->p;
		break;
	default:							return physx::PxVec3(-10e6, 0, 0);
	}

	//std::cout << "Final distance: " << (target->p - mEye).magnitude() << "\n\n";

	if (target != nullptr)
	{
		//if ((target->p - mEye).magnitude() < 5)
		//{
		//	PxVec3 pos = -(target->p - mEye).getNormalized() * 5.0;
		//	mEye = { pos.x, mEye.y, pos.z };
		//}
		//else if ((target->p - mEye).magnitude() > 50)
		//{
		//	PxVec3 pos = -(target->p - mEye).getNormalized() * 50.0;
		//	mEye = { pos.x, mEye.y, pos.z };
		//}
		mDir = target->p - mEye;
	}

	d = mEye - target->p;

	return d;
}

void Camera::handleAnalogMove(float x, float y)
{
	PxVec3 viewY = mDir.cross(PxVec3(0,1,0)).getNormalized();
	mEye += mDir*y;
	mEye += viewY*x;
}

void Camera::handleMotion(int x, int y)
{
	int dx = mMouseX - x;
	int dy = mMouseY - y;

	PxVec3 viewY = mDir.cross(PxVec3(0,1,0)).getNormalized();

	PxQuat qx(PxPi * dx / 180.0f, PxVec3(0,1,0));
	mDir = qx.rotate(mDir);
	PxQuat qy(PxPi * dy / 180.0f, viewY);
	mDir = qy.rotate(mDir);

	mDir.normalize();

	mMouseX = x;
	mMouseY = y;
}

void Camera::update(physx::PxVec3 distance, physx::PxTransform* target = nullptr)
{
	if (target != nullptr)
	{
		//std::cout << target->p.x << " " << target->p.y << " " << target->p.z << "\n";
		mEye = target->p + distance;
	}
}

PxTransform Camera::getTransform() const
{
	PxVec3 viewY = mDir.cross(PxVec3(0,1,0));

	if(viewY.normalize()<1e-6f) 
		return PxTransform(mEye);

	PxMat33 m(mDir.cross(viewY), viewY, -mDir);
	return PxTransform(mEye, PxQuat(m));
}

PxVec3 Camera::getEye() const
{ 
	return mEye; 
}

PxVec3 Camera::getDir() const
{ 
	return mDir; 
}


}

