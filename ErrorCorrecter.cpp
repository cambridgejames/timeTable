//输入规范性判断、错误监控和错误处理程序
//作者：彭剑桥
//修改日期：2017年07月06日

bool solve(int code);	//错误处理程序

bool solve(int code)
{
	switch (code)	//返回值为true时错误完全解决
	{
	case 1:	//文件读取失败
		if (MessageBox(NULL, TEXT("错误代码：#b0x01-rea\n文件读取失败！"), TEXT("程序运行时出现错误"), MB_OK | MB_ICONERROR) == 1)
		{ return true; }
		else {return solve(3); }
		break;
	case 2:	//文件写入失败
		if (MessageBox(NULL, TEXT("错误代码：#b0x02-wri\n文件写入失败！"), TEXT("程序运行时出现错误"), MB_OK | MB_ICONERROR) == 1)
		{
			return true;
		}
		else {return solve(3); }
		break;
	case 3:	//消息弹窗错误
		while (MessageBox(NULL, TEXT("错误代码：#b0x03-win\n程序运行时出现错误！"), TEXT("程序运行时出现错误"), MB_OK | MB_ICONERROR) == 1);
		return true;
		break;
	default:return false;
	}
}