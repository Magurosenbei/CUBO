#pragma once

#include <math.h>
#include <xmath.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <istream>

#define v128f	__m128
#define v128i	__m128i

#pragma region v128 constants
#define _PS_CONST(Name, Val)                                            \
	static const __declspec(align(16)) float _ps_##Name[4]  = { Val, Val, Val, Val }
#define _PI32_CONST(Name, Val)                                            \
	static const __declspec(align(16)) int _pi32_##Name[4]  = { Val, Val, Val, Val }
#define _PS_CONST_TYPE(Name, Type, Val)                                 \
	static const __declspec(align(16)) Type _ps_##Name[4]  = { Val, Val, Val, Val }

_PS_CONST(1  , 1.0f);
_PS_CONST(0p5, 0.5f);
/* the smallest non denormalized float number */
_PS_CONST_TYPE(min_norm_pos, int, 0x00800000);
_PS_CONST_TYPE(mant_mask, int, 0x7f800000);
_PS_CONST_TYPE(inv_mant_mask, int, ~0x7f800000);

_PS_CONST_TYPE(sign_mask, int, 0x80000000);
_PS_CONST_TYPE(inv_sign_mask, int, ~0x80000000);

_PI32_CONST(1, 1);
_PI32_CONST(inv1, ~1);
_PI32_CONST(2, 2);
_PI32_CONST(4, 4);
_PI32_CONST(0x7f, 0x7f);

_PS_CONST(cephes_SQRTHF, 0.707106781186547524f);
_PS_CONST(cephes_log_p0, 7.0376836292E-2f);
_PS_CONST(cephes_log_p1, - 1.1514610310E-1f);
_PS_CONST(cephes_log_p2, 1.1676998740E-1f);
_PS_CONST(cephes_log_p3, - 1.2420140846E-1f);
_PS_CONST(cephes_log_p4, + 1.4249322787E-1f);
_PS_CONST(cephes_log_p5, - 1.6668057665E-1f);
_PS_CONST(cephes_log_p6, + 2.0000714765E-1f);
_PS_CONST(cephes_log_p7, - 2.4999993993E-1f);
_PS_CONST(cephes_log_p8, + 3.3333331174E-1f);
_PS_CONST(cephes_log_q1, -2.12194440E-4f);
_PS_CONST(cephes_log_q2, 0.693359375f);

_PS_CONST(minus_cephes_DP1, -0.78515625f);
_PS_CONST(minus_cephes_DP2, -2.4187564849853515625E-4f);
_PS_CONST(minus_cephes_DP3, -3.77489497744594108E-8f);
_PS_CONST(sincof_p0, -1.9515295891E-4f);
_PS_CONST(sincof_p1,  8.3321608736E-3f);
_PS_CONST(sincof_p2, -1.6666654611E-1f);
_PS_CONST(coscof_p0,  2.443315711809948E-005f);
_PS_CONST(coscof_p1, -1.388731625493765E-003f);
_PS_CONST(coscof_p2,  4.166664568298827E-002f);
_PS_CONST(cephes_FOPI, 1.27323954473516f); // 4 / M_PI
#pragma endregion v128 constants


_declspec(align(16)) class SIMDVector
{	
public:
	union
	{
		_declspec(align(16)) struct {	float x, y, z, w;	};
		_declspec(align(16)) float	mfloats[4];
		_declspec(align(16)) v128f	m128;
	};
	__forceinline SIMDVector():x(0), y(0), z(0), w(1)						{	}
	__forceinline SIMDVector(const v128f & vm128)							{	m128 = vm128;				}
	__forceinline SIMDVector(const float *	floats)						{	m128 = _mm_load_ps(floats);	}
	__forceinline SIMDVector(const float &	value)						{	m128 = _mm_set1_ps(value);	}
	__forceinline SIMDVector(float _x, float _y, float _z, float _w = 1)	:x(_x), y(_y), z(_z), w(_w){}

	__forceinline	operator	float		*()					const	{	return	(float *)&x;		}
	__forceinline	operator	v128f		*()					const	{	return	(v128f *)&m128;	}
	__forceinline	operator	const	float	*()				const	{	return	&x;			}
	__forceinline	operator	const	v128f	*()				const	{	return	&m128;		}

	//inline	const	v128f	operator +()					const	{	return this->m128;	}
	//inline	const	v128f	operator -()					const	{	return -this->m128;	}
#pragma region compare operators
	__forceinline	const	v128f	operator==(const SIMDVector &v2)	const	{	return	_mm_cmpeq_ps(m128, v2.m128);	}
	__forceinline	const	v128f	operator!=(const SIMDVector &v2)	const	{	return	_mm_cmpneq_ps(m128, v2.m128);	}

	__forceinline	const	v128f	operator>(const SIMDVector	&v2)	const	{	return	_mm_cmpgt_ps(m128, v2.m128);	}
	__forceinline	const	v128f	operator<(const SIMDVector	&v2)	const	{	return	_mm_cmpgt_ps(v2.m128, m128);	}
	
	__forceinline	const	v128f	operator>=(const SIMDVector	&v2)	const	{	return	_mm_cmpge_ps(m128, v2.m128);	}
	__forceinline	const	v128f	operator<=(const SIMDVector	&v2)	const	{	return	_mm_cmpge_ps(v2.m128, m128);	}
#pragma endregion compare operators

#pragma region = operators
	__forceinline		void	operator =(const SIMDVector &v2)			{	this->m128 = v2.m128;				}
	__forceinline		void	operator =(const v128f	&v2)				{	this->m128 = v2;					}
	__forceinline		void	operator =(const float	*v2)				{	this->m128 = _mm_load_ps(v2);		}
	__forceinline		void	operator =(const float	&value)				{	this->m128 = _mm_set1_ps(value);	}
#pragma endregion	= operators

#pragma region	+= -= /= *= operators
	__forceinline		void	operator +=(const SIMDVector	&v2)		{	m128 = _mm_add_ps(m128, v2.m128);	}
	__forceinline		void	operator -=(const SIMDVector	&v2)		{	m128 = _mm_sub_ps(m128, v2.m128);	}
	__forceinline		void	operator *=(const SIMDVector	&v2)		{	m128 = _mm_mul_ps(m128, v2.m128);	}
	__forceinline		void	operator /=(const SIMDVector	&v2)		{	m128 = _mm_div_ps(m128, v2.m128);	}
	__forceinline		void	operator +=(const v128f		&v2)			{	m128 = _mm_add_ps(m128, v2);	}
	__forceinline		void	operator -=(const v128f		&v2)			{	m128 = _mm_sub_ps(m128, v2);	}
	__forceinline		void	operator *=(const v128f		&v2)			{	m128 = _mm_mul_ps(m128, v2);	}
	__forceinline		void	operator /=(const v128f		&v2)			{	m128 = _mm_div_ps(m128, v2);	}
	__forceinline		void	operator +=(const float			&value)		{	m128 = _mm_add_ps(m128,	_mm_set1_ps(value));	}
	__forceinline		void	operator -=(const float			&value)		{	m128 = _mm_sub_ps(m128, _mm_set1_ps(value));	}
	__forceinline		void	operator *=(const float			&value)		{	m128 = _mm_mul_ps(m128, _mm_set1_ps(value));	}
	__forceinline		void	operator /=(const float			&value)		{	m128 = _mm_div_ps(m128, _mm_set1_ps(value));	}
#pragma  endregion	+= -= /= *= operators

#pragma region + - / * operators
	__forceinline	const	v128f	operator +(const SIMDVector	&v2)	const	{	return _mm_add_ps(m128, v2.m128);	}
	__forceinline	const	v128f	operator -(const SIMDVector &v2)	const	{	return _mm_sub_ps(m128, v2.m128);	}
	__forceinline	const	v128f	operator *(const SIMDVector &v2)	const	{	return _mm_mul_ps(m128, v2.m128);	}
	__forceinline	const	v128f	operator /(const SIMDVector &v2)	const	{	return _mm_div_ps(m128, v2.m128);	}
	__forceinline	const	v128f	operator +(const v128f		&v2)	const	{	return _mm_add_ps(m128, v2);	}
	__forceinline	const	v128f	operator -(const v128f		&v2)	const	{	return _mm_sub_ps(m128, v2);	}
	__forceinline	const	v128f	operator *(const v128f		&v2)	const	{	return _mm_mul_ps(m128, v2);	}
	__forceinline	const	v128f	operator /(const v128f		&v2)	const	{	return _mm_div_ps(m128, v2);	}
	__forceinline	const	v128f	operator +(const float		&value)	const	{	return _mm_add_ps(m128,	_mm_set1_ps(value));	}
	__forceinline	const	v128f	operator -(const float		&value)	const	{	return _mm_sub_ps(m128, _mm_set1_ps(value));	}
	__forceinline	const	v128f	operator *(const float		&value)	const	{	return _mm_mul_ps(m128, _mm_set1_ps(value));	}
	__forceinline	const	v128f	operator /(const float		&value)	const	{	return _mm_div_ps(m128, _mm_set1_ps(value));	}
#pragma endregion + - / * operators

	__forceinline			void	SetZero()									{	this->m128 = _mm_setzero_ps();		}
	__forceinline			void	ReverseComponents()							{	this->m128 = _mm_loadr_ps(mfloats);	}
	__forceinline			void	FloodValue(const float &value)				{	this->m128 = _mm_set1_ps(value);	}
	
	__forceinline	const	float	Length()							const	{	return sqrtf(Dot_float3(*this));			}
	__forceinline	const	float	SquaredLength()						const	{	return Dot_float3(*this);					}

	__forceinline	const	v128f	SquareRoot()						const	{	return	_mm_sqrt_ps(this->m128);			}
	__forceinline	const	v128f	RSquareRoot()						const	{	return	_mm_rsqrt_ps(this->m128);			}

	__forceinline	const	v128f	Normalize()							const	{	float Divisor =  sqrtf(Dot_float3(*this));	/*ASSERT(Divisor != 0);*/	return *this / Divisor;	}

	__forceinline	const	float	Dot_float3(const SIMDVector &v2)	const	{	SIMDVector V = *this * v2;	return V.x + V.y + V.z;			}
	__forceinline	const	float	Dot_float4(const SIMDVector &v2)	const	{	SIMDVector V = *this * v2;	return V.x + V.y + V.z + V.w;	}

	__forceinline	const	v128f	Cross_float(const SIMDVector & v2)	const	{	return _mm_set_ps(y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x, 0.0f);	}
};

__forceinline	const	v128f	operator+	(const v128f & v2,		const SIMDVector & v)	{	return _mm_add_ps(v.m128, v2);	}
__forceinline	const	v128f	operator-	(const v128f & v2,		const SIMDVector & v)	{	return _mm_sub_ps(v.m128, v2);	}
__forceinline	const	v128f	operator*	(const v128f & v2,		const SIMDVector & v)	{	return _mm_mul_ps(v.m128, v2);	}
__forceinline	const	v128f	operator/	(const v128f & v2,		const SIMDVector & v)	{	return _mm_div_ps(v.m128, v2);	}

__forceinline	const	v128f	operator+	(const float & value,	const SIMDVector & v)	{	return _mm_add_ps(v.m128, _mm_set1_ps(value));	}
__forceinline	const	v128f	operator-	(const float & value,	const SIMDVector & v)	{	return _mm_sub_ps(v.m128, _mm_set1_ps(value));	}
__forceinline	const	v128f	operator*	(const float & value,	const SIMDVector & v)	{	return _mm_mul_ps(v.m128, _mm_set1_ps(value));	}
__forceinline	const	v128f	operator/	(const float & value,	const SIMDVector & v)	{	return _mm_div_ps(v.m128, _mm_set1_ps(value));	}

__forceinline	const	v128f	v128f_Dot_float3(const SIMDVector &x, const SIMDVector & y, const SIMDVector & z)
{
	v128f	xsq = _mm_mul_ps(x.m128, x.m128);
	v128f	ysq = _mm_mul_ps(y.m128, y.m128);
	v128f	zsq = _mm_mul_ps(z.m128, z.m128);

	 xsq = _mm_add_ps(xsq, ysq);
	 xsq = _mm_add_ps(xsq, zsq);

	return xsq;
}

__forceinline	const	v128f	v128f_Dot_float4(const SIMDVector &x, const SIMDVector & y, const SIMDVector & z, const SIMDVector & w)
{
	v128f	xsq = _mm_mul_ps(x.m128, x.m128);
	v128f	ysq = _mm_mul_ps(y.m128, y.m128);
	v128f	zsq = _mm_mul_ps(z.m128, z.m128);
	v128f	wsq = _mm_mul_ps(w.m128, w.m128);

	xsq = _mm_add_ps(xsq, ysq);
	xsq = _mm_add_ps(xsq, zsq);
	xsq = _mm_add_ps(xsq, wsq);

	return xsq;
}

__forceinline	const	v128f	v128f_Sin4f(v128f	x)
{
	v128f	xmm1, xmm2, xmm3, sign_bit, y;
	v128i	emm0, emm2;
	xmm2		=	_mm_setzero_ps();
	sign_bit	=	x;
	
	x = _mm_and_ps(sign_bit, *(v128f *)_ps_inv_sign_mask);
	sign_bit = _mm_and_ps(sign_bit, *(v128f *)_ps_sign_mask);
	y = _mm_mul_ps(x, *(v128f *)_ps_cephes_FOPI);

	emm2 = _mm_cvttps_epi32(y);
	emm2 = _mm_add_epi32(emm2, *(v128i *)_pi32_1);
	emm2 = _mm_and_si128(emm2, *(v128i *)_pi32_inv1);

	emm0 = _mm_and_si128(emm2, *(v128i*)_pi32_4);
	emm0 = _mm_slli_epi32(emm0, 29);

	emm2 = _mm_and_si128(emm2, *(v128i*)_pi32_2);
	emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());

	v128f swap_sign_bit = _mm_castsi128_ps(emm0);
	v128f poly_mask = _mm_castsi128_ps(emm2);
	sign_bit = _mm_xor_ps(sign_bit, swap_sign_bit);

	xmm1 = *(v128f*)_ps_minus_cephes_DP1;
	xmm2 = *(v128f*)_ps_minus_cephes_DP2;
	xmm3 = *(v128f*)_ps_minus_cephes_DP3;
	xmm1 = _mm_mul_ps(y, xmm1);
	xmm2 = _mm_mul_ps(y, xmm2);
	xmm3 = _mm_mul_ps(y, xmm3);
	x = _mm_add_ps(x, xmm1);
	x = _mm_add_ps(x, xmm2);
	x = _mm_add_ps(x, xmm3);

	y = *(v128f*)_ps_coscof_p0;
	v128f z = _mm_mul_ps(x,x);

	y = _mm_mul_ps(y, z);
	y = _mm_add_ps(y, *(v128f*)_ps_coscof_p1);
	y = _mm_mul_ps(y, z);
	y = _mm_add_ps(y, *(v128f*)_ps_coscof_p2);
	y = _mm_mul_ps(y, z);
	y = _mm_mul_ps(y, z);
	v128f tmp = _mm_mul_ps(z, *(v128f*)_ps_0p5);
	y = _mm_sub_ps(y, tmp);
	y = _mm_add_ps(y, *(v128f*)_ps_1);

	v128f y2 = *(v128f*)_ps_sincof_p0;
	y2 = _mm_mul_ps(y2, z);
	y2 = _mm_add_ps(y2, *(v128f*)_ps_sincof_p1);
	y2 = _mm_mul_ps(y2, z);
	y2 = _mm_add_ps(y2, *(v128f*)_ps_sincof_p2);
	y2 = _mm_mul_ps(y2, z);
	y2 = _mm_mul_ps(y2, x);
	y2 = _mm_add_ps(y2, x);
 
	xmm3 = poly_mask;
	y2 = _mm_and_ps(xmm3, y2);
	y = _mm_andnot_ps(xmm3, y);
	y = _mm_add_ps(y,y2);

	y = _mm_xor_ps(y, sign_bit);

	return y;
}

__forceinline	const	v128f	v128f_Cos4f(v128f	x)
{
	v128f xmm1, xmm2, xmm3, y;
	v128i emm0, emm2;

	xmm2 = _mm_setzero_ps();
	x = _mm_and_ps(x, *(v128f*)_ps_inv_sign_mask);
	y = _mm_mul_ps(x, *(v128f*)_ps_cephes_FOPI);

	emm2 = _mm_cvttps_epi32(y);
	emm2 = _mm_add_epi32(emm2, *(v128i*)_pi32_1);
	emm2 = _mm_and_si128(emm2, *(v128i*)_pi32_inv1);
	y = _mm_cvtepi32_ps(emm2);

	emm2 = _mm_sub_epi32(emm2, *(v128i*)_pi32_2);


	emm0 = _mm_andnot_si128(emm2, *(v128i*)_pi32_4);
	emm0 = _mm_slli_epi32(emm0, 29);

	emm2 = _mm_and_si128(emm2, *(v128i*)_pi32_2);
	emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());

	v128f sign_bit = _mm_castsi128_ps(emm0);
	v128f poly_mask = _mm_castsi128_ps(emm2);

	xmm1 = *(v128f*)_ps_minus_cephes_DP1;
	xmm2 = *(v128f*)_ps_minus_cephes_DP2;
	xmm3 = *(v128f*)_ps_minus_cephes_DP3;
	xmm1 = _mm_mul_ps(y, xmm1);
	xmm2 = _mm_mul_ps(y, xmm2);
	xmm3 = _mm_mul_ps(y, xmm3);
	x = _mm_add_ps(x, xmm1);
	x = _mm_add_ps(x, xmm2);
	x = _mm_add_ps(x, xmm3);

	y = *(v128f*)_ps_coscof_p0;
	v128f z = _mm_mul_ps(x,x);

	y = _mm_mul_ps(y, z);
	y = _mm_add_ps(y, *(v128f*)_ps_coscof_p1);
	y = _mm_mul_ps(y, z);
	y = _mm_add_ps(y, *(v128f*)_ps_coscof_p2);
	y = _mm_mul_ps(y, z);
	y = _mm_mul_ps(y, z);
	v128f tmp = _mm_mul_ps(z, *(v128f*)_ps_0p5);
	y = _mm_sub_ps(y, tmp);
	y = _mm_add_ps(y, *(v128f*)_ps_1);
	v128f y2 = *(v128f*)_ps_sincof_p0;
	y2 = _mm_mul_ps(y2, z);
	y2 = _mm_add_ps(y2, *(v128f*)_ps_sincof_p1);
	y2 = _mm_mul_ps(y2, z);
	y2 = _mm_add_ps(y2, *(v128f*)_ps_sincof_p2);
	y2 = _mm_mul_ps(y2, z);
	y2 = _mm_mul_ps(y2, x);
	y2 = _mm_add_ps(y2, x);
  
	xmm3 = poly_mask;
	y2 = _mm_and_ps(xmm3, y2);
	y = _mm_andnot_ps(xmm3, y);
	y = _mm_add_ps(y,y2);

	y = _mm_xor_ps(y, sign_bit);
	return y;
}


__forceinline	void			v128f_SinCos4f(v128f x, v128f * s, v128f * c) 
{
	v128f xmm1, xmm2, xmm3 = _mm_setzero_ps(), sign_bit_sin, y;

	v128i emm0, emm2, emm4;

	sign_bit_sin = x;

	x = _mm_and_ps(x, *(v128f*)_ps_inv_sign_mask);
	sign_bit_sin = _mm_and_ps(sign_bit_sin, *(v128f*)_ps_sign_mask);
	y = _mm_mul_ps(x, *(v128f*)_ps_cephes_FOPI);
	emm2 = _mm_cvttps_epi32(y);

	emm2 = _mm_add_epi32(emm2, *(v128i*)_pi32_1);
	emm2 = _mm_and_si128(emm2, *(v128i*)_pi32_inv1);
	y = _mm_cvtepi32_ps(emm2);

	emm4 = emm2;
	emm0 = _mm_and_si128(emm2, *(v128i*)_pi32_4);
	emm0 = _mm_slli_epi32(emm0, 29);
	v128f swap_sign_bit_sin = _mm_castsi128_ps(emm0);

	emm2 = _mm_and_si128(emm2, *(v128i*)_pi32_2);
	emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
	v128f poly_mask = _mm_castsi128_ps(emm2);

	xmm1 = *(v128f*)_ps_minus_cephes_DP1;
	xmm2 = *(v128f*)_ps_minus_cephes_DP2;
	xmm3 = *(v128f*)_ps_minus_cephes_DP3;
	xmm1 = _mm_mul_ps(y, xmm1);
	xmm2 = _mm_mul_ps(y, xmm2);
	xmm3 = _mm_mul_ps(y, xmm3);
	x = _mm_add_ps(x, xmm1);
	x = _mm_add_ps(x, xmm2);
	x = _mm_add_ps(x, xmm3);

	emm4 = _mm_sub_epi32(emm4, *(v128i*)_pi32_2);
	emm4 = _mm_andnot_si128(emm4, *(v128i*)_pi32_4);
	emm4 = _mm_slli_epi32(emm4, 29);
	v128f sign_bit_cos = _mm_castsi128_ps(emm4);

	sign_bit_sin = _mm_xor_ps(sign_bit_sin, swap_sign_bit_sin);

	v128f z = _mm_mul_ps(x,x);
	y = *(v128f*)_ps_coscof_p0;

	y = _mm_mul_ps(y, z);
	y = _mm_add_ps(y, *(v128f*)_ps_coscof_p1);
	y = _mm_mul_ps(y, z);
	y = _mm_add_ps(y, *(v128f*)_ps_coscof_p2);
	y = _mm_mul_ps(y, z);
	y = _mm_mul_ps(y, z);
	v128f tmp = _mm_mul_ps(z, *(v128f*)_ps_0p5);
	y = _mm_sub_ps(y, tmp);
	y = _mm_add_ps(y, *(v128f*)_ps_1);

	v128f y2 = *(v128f*)_ps_sincof_p0;
	y2 = _mm_mul_ps(y2, z);
	y2 = _mm_add_ps(y2, *(v128f*)_ps_sincof_p1);
	y2 = _mm_mul_ps(y2, z);
	y2 = _mm_add_ps(y2, *(v128f*)_ps_sincof_p2);
	y2 = _mm_mul_ps(y2, z);
	y2 = _mm_mul_ps(y2, x);
	y2 = _mm_add_ps(y2, x);

	xmm3 = poly_mask;
	v128f ysin2 = _mm_and_ps(xmm3, y2);
	v128f ysin1 = _mm_andnot_ps(xmm3, y);
	y2 = _mm_sub_ps(y2,ysin2);
	y = _mm_sub_ps(y, ysin1);

	xmm1 = _mm_add_ps(ysin1,ysin2);
	xmm2 = _mm_add_ps(y,y2);

	*s = _mm_xor_ps(xmm1, sign_bit_sin);
	*c = _mm_xor_ps(xmm2, sign_bit_cos);
}