#pragma once

// �̱��� ����
// ��ü�� ������ 1���� ����
// ��𼭵� ���� ���� ����

class CCore
{
private:
	static CCore* g_pInst;

public:
	// ���� ����Լ�, ��ü���� ȣ�� ����, this�� ���� (��� ���� �Ұ�), ���� ����� ���� ����
	static void FUNC() {}

	// ���� ����Լ�
	static CCore* GetInstance()
	{
		// ���� ȣ�� �� ���
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
