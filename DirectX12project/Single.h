#pragma once

template <typename T>
class Single
{
public:
	// �C���X�^���X�ϐ��̎擾
	static T& Get(void)
	{
		static T instance;
		return instance;
	}

protected:
	// �R���X�g���N�^
	Single() {}

	// �f�X�g���N�^
	virtual ~Single() {}

private:
	Single(const Single&) = delete;
	void operator=(const Single&) = delete;

};