#pragma once

class MatrixHelper
{
protected:
	static D3DXMATRIX	mat_IDENTITY;
public:
	static void			Initialize();

	inline static D3DXMATRIX	*IDENTITY()		{	return	&mat_IDENTITY;	}
	inline static D3DXMATRIX	CreateWorldMatrix(const VECTOR3 & Point, const D3DXQUATERNION & Q, const VECTOR3 & Scale)
	{
		D3DXMATRIX T, R, S;
		D3DXMatrixTranslation(&T, Point.x, Point.y, Point.z);
		D3DXMatrixRotationQuaternion(&R, &Q);
		D3DXMatrixScaling(&S, Scale.x, Scale.y, Scale.z);

		D3DXMatrixMultiply(&T, &R, &T);
		D3DXMatrixMultiply(&T, &S, &T);
		return T;
	}

	inline	static D3DXMATRIX	Convert(const btTransform & T)
	{
		D3DXMATRIX M;
		T.getOpenGLMatrix((float * )M.m);
		return M;
	}
};