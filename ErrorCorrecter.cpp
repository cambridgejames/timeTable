//����淶���жϡ������غʹ��������
//���ߣ�����
//�޸����ڣ�2017��07��06��

bool solve(int code);	//���������

bool solve(int code)
{
	switch (code)	//����ֵΪtrueʱ������ȫ���
	{
	case 1:	//�ļ���ȡʧ��
		if (MessageBox(NULL, TEXT("������룺#b0x01-rea\n�ļ���ȡʧ�ܣ�"), TEXT("��������ʱ���ִ���"), MB_OK | MB_ICONERROR) == 1)
		{ return true; }
		else {return solve(3); }
		break;
	case 2:	//�ļ�д��ʧ��
		if (MessageBox(NULL, TEXT("������룺#b0x02-wri\n�ļ�д��ʧ�ܣ�"), TEXT("��������ʱ���ִ���"), MB_OK | MB_ICONERROR) == 1)
		{
			return true;
		}
		else {return solve(3); }
		break;
	case 3:	//��Ϣ��������
		while (MessageBox(NULL, TEXT("������룺#b0x03-win\n��������ʱ���ִ���"), TEXT("��������ʱ���ִ���"), MB_OK | MB_ICONERROR) == 1);
		return true;
		break;
	default:return false;
	}
}