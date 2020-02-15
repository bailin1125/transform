#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)
using namespace std;

int main(int argc, char*argv[])
{
	int i = 0, j = 0;

	//现在开始分两种情况
	int use_flag = 0;
	cout << "plese check the different use! 1 is compare_multi script and ,2 is structure script generate!" << endl;
	cin >> use_flag;
	if (use_flag == 1)
	{
		char start[10], step[10], end[10], total[10];
		int start_num = 0, step_num = 0, end_num = 0, total_num = 0;
		std::cout << "this code generate the compare multi script, needs the input file mult_compare.cpp!" << endl;
		std::cout << "please type the number start,step,end,total.  orderly!" << endl;
		cin >> start_num;
		cin >> step_num;
		cin >> end_num;
		cin >> total_num;
		cout << "start: " << start_num << " step: " << step_num << " end: " << end_num << " total: " << total_num << endl;

		int cycle = (end_num - start_num) / step_num + 1;
		cout << "now make sure the first num:" << endl;
		int first = 0;
		cin >> first;
		cout << "first is the :" << first << endl;
		int equal = total_num / cycle;
		int a = (2 * equal - 2 * first) / (cycle - 1);

		//然后开始建立数字
		int b = 0, c = first;
		int**num = new int*[cycle];
		for (i = 0; i < cycle; i++)
		{
			num[i] = new int[2];
			if (i == cycle - 1)
			{
				//说明是最后一个了
				num[i][0] = b;
				num[i][1] = total_num;
				cout << num[i][0] << "," << num[i][1] << endl;
				break;
			}
			num[i][0] = b;
			num[i][1] = c;
			b = c;
			c = a * (i + 1) + c + first;
			cout << num[i][0] << "," << num[i][1] << endl;
		}
		string com = "";
		string jump_name = "jump_str_name";
		j = 0;
		for (i = start_num; i <= end_num; i += step_num)
		{
			string now_name = "mult" + to_string(i) + ".cpp";
			//复制名字
			com = "cp mult_compare.cpp " + now_name;
			//cout << com.c_str() << endl;
			system(com.c_str());
			//更改跳出的名字
			com = "sed -i \"s/jump_str_name2.txt/jump_str_name" + to_string(i) + ".txt" + "/g\"" + " " + now_name;
			//cout << com.c_str() << endl;
			system(com.c_str());
			//更改总数
			com = "sed -i \"s/3781/" + to_string(total_num) + "/g\" " + now_name;
			//cout << com.c_str() << endl;
			system(com.c_str());

			//最后是改变数目
			com = "sed -i \"s/start=0/start=" + to_string(num[j][0]) + "/g\" " + now_name;
			//cout << com.c_str() << endl;
			system(com.c_str());
			com = "sed -i \"s/end=20/end=" + to_string(num[j][1]) + "/g\" " + now_name;
			//cout << com.c_str() << endl;
			system(com.c_str());
			j++;
			//补充一个编译结果
			com = "g++ -fopenmp -o mult" + to_string(i) + ".out" + " " + now_name;
			//cout << com.c_str() << endl;
			system(com.c_str());
		}




		for (i = 0; i < cycle; i++)
		{
			delete[]num[i];
		}
		delete[]num;
	}
	
	else if (use_flag == 2)
	{
		std::cout << "this code generate the structel multi script, needs the input file mult_str.cpp!" << endl;
		std::cout << "please type the number start,step,end,total.  orderly!" << endl;
		int start_num = 0, step_num = 0, end_num = 0, total_num = 0;
		cin >> start_num;
		cin >> step_num;
		cin >> end_num;
		cin >> total_num;
		cout << "start: " << start_num << " step: " << step_num << " end: " << end_num << " total: " << total_num << endl;

		int cycle = (end_num - start_num) / step_num + 1;
		int a = total_num / cycle;
		int b = 0, c = a;
		int**num = new int*[cycle];
		for (i = 0; i < cycle; i++)
		{
			num[i] = new int[2];
			if (i == cycle - 1)
			{
				//说明是最后一个了
				num[i][0] = b;
				num[i][1] = total_num;
				cout << num[i][0] << "," << num[i][1] << endl;
				break;
			}
			num[i][0] = b;
			num[i][1] = c;
			b = c;
			c = c+a;
			cout << num[i][0] << "," << num[i][1] << endl;
		}


		string com = "";		
		j = 0;
		for (i = start_num; i <= end_num; i += step_num)
		{
			string now_name = "mult" + to_string(i) + ".cpp";
			//复制名字
			com = "cp mult_str.cpp " + now_name;
			//cout << com.c_str() << endl;
			system(com.c_str());
			//更改跳出的名字
			com = "sed -i \"s/compare2/compare" + to_string(i)  + "/g\"" + " " + now_name;
			//cout << com.c_str() << endl;
			system(com.c_str());
			//更改总数
			com = "sed -i \"s/4349/" + to_string(total_num) + "/g\" " + now_name;
			//cout << com.c_str() << endl;
			system(com.c_str());

			//最后是改变数目
			com = "sed -i \"s/start=0/start=" + to_string(num[j][0]) + "/g\" " + now_name;
			//cout << com.c_str() << endl;
			system(com.c_str());
			com = "sed -i \"s/end=270/end=" + to_string(num[j][1]) + "/g\" " + now_name;
			//cout << com.c_str() << endl;
			system(com.c_str());
			j++;
			//补充一个编译结果
			com = "g++ -fopenmp -o mult" + to_string(i) + ".out" + " " + now_name;
			//cout << com.c_str() << endl;
			system(com.c_str());
		}




		for (i = 0; i < cycle; i++)
		{
			delete[]num[i];
		}
		delete[]num;
	}
	
	else
	{
		cout << "unkonwn flag name!" << endl;
	}
	cout << "all total work done!" << endl;
	return 0;
}