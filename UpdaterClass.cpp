//�������е��õ��ࡢ�������Ա
//���ߣ�����
//�޸����ڣ�2017��07��05��

class Course {
private:
	string name;
	unsigned short dateB, dateF, dateJ, day1, less1B, less1F, day2, less2B, less2F, day3, less3B, less3F, day4, less4B, less4F;
	int count = 0;
public:
	Course();
	void download(string Xname , unsigned short Xdata[15]);	//����ȡ�Ĳ���ֵд���Ա����
	unsigned short checkrea();	//����Ա��ֵ�Ƿ����
	bool showcourse(string& Yname , unsigned short Ydata[15]);	//�����ⷵ�ض����Ա��ֵ
	void update();	//ˢ�³�Ա��ֵ
};

Course::Course()
{
	name = "NULL";
	dateB = 0;
	dateF = 0;
	dateJ = 0;
	day1 = 0;
	less1B = 0;
	less1F = 0;
	day2 = 0;
	less2B = 0;
	less2F = 0;
	day3 = 0;
	less3B = 0;
	less3F = 0;
	day4 = 0;
	less4B = 0;
	less4F = 0;
}

void Course::download(string Xname, unsigned short Xdata[15])
{
	name = Xname;
	dateB = Xdata[0];
	dateF = Xdata[1];
	dateJ = Xdata[2];
	day1 = Xdata[3];
	less1B = Xdata[4];
	less1F = Xdata[5];
	day2 = Xdata[6];
	less2B = Xdata[7];
	less2F = Xdata[8];
	day3 = Xdata[9];
	less3B = Xdata[10];
	less3F = Xdata[11];
	day4 = Xdata[12];
	less4B = Xdata[13];
	less4F = Xdata[14];
}

unsigned short Course::checkrea()//����ֵΪ��0����ǰ����Ϊ�գ�����ֵΪ��1����Ϸ�������ֵΪ��2���򲻺Ϸ�
{
	if (name != "NULL")
	{
		if (dateB <= dateF && dateB > 0 && dateF <= 22)//�ж�������ֹ�Ƿ�Ϸ�
		{
			if (dateJ >= 0 && dateJ <= 2)//�жϵ�˫�ܲ����Ƿ�Ϸ�
			{
				if (day1 > 0 && day1 <= 7 && less1B <= less1F && less1B > 0 && less1F <= 12)
				{
					if (day2 > 0 && day2 <= 7 && less2B <= less2F && less2B > 0 && less2F <= 12)
					{
						if (day3 > 0 && day3 <= 7 && less3B <= less3F && less3B > 0 && less3F <= 12)
						{
							if (day4 > 0 && day4 <= 7 && less4B <= less4F && less4B > 0 && less4F <= 12)
							{
								return 1;
							}
							else { return 2; }
						}
						else { return 2; }
					}
					else { return 2; }
				}
				else { return 2; }
			}
			else { return 2; }
		}
		else { return 2; }
	}
	else if (name == "NULL" && dateB == dateF == dateJ == day1 == less1B == less1F == day2 == less2B == less2F == day3 == less3B == less3F == day4 == less4B == less4F == 0)
	{
		return 0;
	}
	else { return 2; }
}

bool Course::showcourse(string& Yname, unsigned short Ydata[15])
{
	 Yname = name;
	 Ydata[0] = dateB;
	 Ydata[1] = dateF;
	 Ydata[2] = dateJ;
	 Ydata[3] = day1;
	 Ydata[4] = less1B;
	 Ydata[5] = less1F;
	 Ydata[6] = day2;
	 Ydata[7] = less2B;
	 Ydata[8] = less2F;
	 Ydata[9] = day3;
	 Ydata[10] = less3B;
	 Ydata[11] = less3F;
	 Ydata[12] = day4;
	 Ydata[13] = less4B;
	 Ydata[14] = less4F;
	 if (name == "NULL")//�жϴ˶����Ƿ�洢����Ч�γ�
	 {
		 return false;
	 }
	 else { return true; }
}

void Course::update()
{
	//TODO
}