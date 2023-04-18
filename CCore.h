#pragma once

// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능

class CCore
{
private:
	static CCore* g_pInst;

public:
	// 정적 멤버함수, 객체없이 호출 가능, this가 없다 (멤버 접근 불가), 정적 멤버는 접근 가능
	static void FUNC() {}

	// 정적 멤버함수
	static CCore* GetInstance()
	{
		// 최초 호출 된 경우
		if (nullptr == g_pInst)
		{
			g_pInst = new CCore;
		}

		return g_pInst;
	}

	static void Release()
	{
		if (g_pInst != nullptr)
		{
			delete g_pInst;
			g_pInst = nullptr;
		}
	}

private:
	CCore();
	~CCore();
};
