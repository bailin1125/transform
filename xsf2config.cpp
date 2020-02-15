#include <iostream>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <vector>
#pragma warning(disable : 4996)
using namespace std;
int reverse_matrix(double **a, int num, double **b);
void getastar(double **a, int num, double **b);
double det(double **a, int num);
const char atom_name[120][3] = { " ", "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg" };
void  poscar2config(string& file_name, string & outpath, string & head);
int find_element(char* str);
bool poscarexchange = true;//是否进行poscar的转化
int R;
int total = 1;
void get_listnum(char*str, int*number);
int main(int argv, char*argc[])
{
	int i = 0, j = 0;
	

	if (poscarexchange == true)
	{
		cout << "This code : poscar2onfig, created by the Zhi Wang!" << endl;
		string file_name = "C:\\Users\\王志\\Desktop\\0103基元分类及检查\\sinpore\\output_poscar(1).txt";
		string path = "C:\\Users\\王志\\Desktop\\0103去重后data\\singpore\\";
		string head = "SP_";
		poscar2config(file_name, path, head);
		cout << "all total work done!" << endl;
		cin.get();
		return 0;
		
	}











	string name="ZrSe2-2f549b91.xsf";
	name.resize(100);
	for (i = 0; i < argv; i++)
	{
		if (i == 1)
		{
			for (j = 0; j < strlen(argc[i]); j++)
			{
				name[j] = argc[i][j];
			}
			name[strlen(argc[i])] = '\0';
		}
	}
	cout << "This code : xsf2onfig, created by the Zhi Wang!" << endl;
	ifstream fin;
	fin.open(name.c_str(), ios::in);
	if (!fin.is_open())
	{
		cout << "i can not find the file:" << name << endl;
		cin.get();
		return 0;
	}

	int num;
	string temp;
	double ** letice = new double*[3];
	for (i = 0; i < 3; i++)
	{
		letice[i] = new double[3];
	}
	
	//vector <vector<double>>  letice(3);//用来储存晶格矢量
	//
	//for (i = 0; i < letice.size(); i++)
	//{
	//	letice[i].resize(3);
	//}

	getline(fin, temp);
	getline(fin, temp);
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			fin >> letice[i][j];
		}
		
	}
	getline(fin, temp);
	getline(fin, temp);
	fin >> num;

	vector<vector<double>> rp(num);
	for (i = 0; i < num; i++)
	{
		rp[i].resize(3);
	}
	
	vector<int> type(num);//储存类型
	while (fin.good() && fin.peek() != EOF)
	{		
		fin >> temp;		
		for (i = 0; i < num; i++)
		{
			fin >> type[i];
			for (j = 0; j < 3; j++)
			{
				fin >> rp[i][j];
			}
		}
	}
	fin.close();
	//然后我们需要根据计算方程得到分数坐标
	double ** lr = new double*[3];
	for (i = 0 ;i < 3; i++)
	{
		lr[i] = new double[3];
	}
	if (reverse_matrix(letice, 3, lr)==0)
	{
		cout << "wrong transform ,please check!" << endl;
		return 0;
	}
	vector<vector<double>> res(num);//储存转化过后的分数坐标
	for (i = 0; i < num; i++)
	{
		res[i].resize(3);
		for (j = 0; j < 3; j++)
		{
			res[i][j] = rp[i][0] * lr[0][j] + rp[i][1] * lr[1][j] + rp[i][2] * lr[2][j];
		}
	}
	ofstream fout;
	fout.open("atom.config", ios::out);
	//开始正式写入aotm.config
	fout << "           " << num << endl;
	fout << "Lattice vector" << endl;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			fout << "      " << letice[i][j];
		}
		fout << endl;
	}
	fout << "Position move_x, move_y, move_z" << endl;
	fout.setf(ios::fixed, ios::floatfield);  // 设定为 fixed 模式，以小数点表示浮点数
	fout.precision(12);
	for (i = 0; i < num; i++)
	{
		fout << "   " << type[i] << "    ";
		for (j = 0; j < 3; j++)
		{
			fout << res[i][j] << "    ";
		}
		fout << "1  1  1" << endl;

	}
	fout.close();
	for (i = 0; i < 3; i++)
	{
		delete[]lr[i];
		delete[]letice[i];
	}
	delete[]lr;
	delete[]letice;
	return 0;
}
int reverse_matrix(double **a, int num, double **b)
{
	int i = 0, j = 0;
	double **temp = new double *[num];
	for (i = 0; i < num; i++)
	{
		temp[i] = new double[num];
	}
	getastar(a, num, temp);
	double value = det(a, num);
	if (abs(value) < 1e-4)
	{
		cout << "can not reverse!please check!" << endl;
		return 0;
	}
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < num; j++)
		{
			b[i][j] = temp[i][j] / value;
		}
	}
	return 1;
}
void getastar(double **a, int num, double **b)
{
	int i = 0, j = 0, k = 0, m = 0;
	if (num == 1)
	{
		b[0][0] = 1;
		return;
	}
	double **temp = new double *[num];
	for (i = 0; i < num; i++)
	{
		temp[i] = new double[num];
	}
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < num; j++)
		{
			for (k = 0; k < num - 1; k++)
			{
				for (m = 0; m < num - 1; m++)
				{
					temp[k][m] = a[(k >= i) ? k + 1 : k][(m >= j) ? m + 1 : m];
				}
			}

			b[j][i] = det(temp, num - 1);
			if ((i + j) % 2 != 0)
			{
				b[j][i] = -b[j][i];
			}
		}
	}
	for (i = 0; i < num; i++)
	{
		delete[] temp[i];
	}
	delete[] temp;
	return;
}
double det(double **a, int num)
{
	int i = 0, j = 0, k = 0;
	if (num == 1)
	{
		return a[0][0];
	}
	double ans = 0;
	double **temp_det = new double *[num];
	for (i = 0; i < num; i++)
	{
		temp_det[i] = new double[num];
	}

	for (i = 0; i < num; i++)
	{
		for (j = 0; j < num - 1; j++)
		{
			for (k = 0; k < num - 1; k++)
			{
				temp_det[j][k] = a[j + 1][(k >= i) ? k + 1 : k];
			}
		}
		double t = det(temp_det, num - 1);

		if (i % 2 == 0)
		{
			ans = ans + a[0][i] * t;
		}
		else
		{
			ans = ans - a[0][i] * t;
		}
	}
	return ans;
}

void  poscar2config(string& file_name, string & outpath,string & head)
{
	//输入是一个文件名，输出是在指定的路径上转化后的系列config文件
	int i = 0, j = 0;
	ifstream fin;
	fin.open(file_name, ios::in);
	if (!fin.is_open())
	{
		cout << "unkonwn the datafile!" << endl;
		cin.get();
	}

	char temp[100];
	double letice[3][3];
	char config_name[50];
	char config_name_temp[50];
	double ratio = 0;

	char save_element[50][3];
	int number[50];
	int count = 0, loca = 0;
	double location[50][3];
	int xuhao[50];
	bool check_flag = false;
	int name_tail = 1;
	while (fin.good() && fin.peek() != EOF)
	{
		fin.getline(config_name_temp, 30);
		//cout << config_name_temp << endl;
		//这里需要做一点，去掉名字中的括号
		j = 0;
		for (i = 0; i < strlen(config_name_temp); i++)
		{
			if (config_name_temp[i] == '(')
			{
				cout << config_name_temp << endl;
				check_flag = true;
			}
			if (config_name_temp[i] != '(' && config_name_temp[i] != ')')
			{
				config_name[j++] = config_name_temp[i];
			}
			
		}
		config_name[j] = '\0';
		if (check_flag == true)
		{
			//cout << config_name << endl;
			check_flag = false;
			//cin.get();
		}
		fin >> ratio;
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				fin >> letice[i][j];
			}
			fin.getline(temp, 90);
		}
		
		while (fin.getline(temp, 90))
		{
			
			//cout << temp << endl;
			int start;
			for (i = 0; i < strlen(temp) - 1; i++)
			{
				if (temp[i] != ' '&&temp[i] != '\t')
					break;
			}
			start = i;
			//先找到第一个不为空的字符

			if (strstr(temp, "Direct") != NULL)			
				break;
			else if (temp[start]-'0'>=0 && temp[start] - '0' <= 9)
			{
				//说明开始读数字
				//cout << strlen(temp) << endl;
				//int length = 2*strlen(temp)-3;
				//R = R - (sizeof(char)*8);
				//total++;
				//fin.seekg(R, ios::beg);
				////fin.getline(temp, 90);
				//cout << temp << endl;
				get_listnum(temp, number);
				//fin.getline(temp, 90);
			}
			else
			{
				//读元素字符串
				//去掉后面的空字符
				//cout << temp << endl;
				/*R = fin.tellg();
				cout << R << endl;*/
				int start, end;
				for (i = strlen(temp) - 1; i > 0; i--)
				{
					if (temp[i] != ' '&&temp[i] != '\t')
						break;
					else
					{
						temp[i] = '\0';
					}
				}
				end = i + 1;
				//去掉后面的空字符
				for (i =0 ; i <strlen(temp) - 1; i++)
				{
					if (temp[i] != ' '&&temp[i] != '\t')
						break;					
				}
				start = i;
				//cout << temp << endl;
				for (i = start; i < end; i++)
				{
					if (temp[i] != '\0' &&temp[i] != ' '&&temp[i] != '\t')
					{
						//cout << temp[i] << endl;
						save_element[count][loca++] = temp[i];
						save_element[count][loca] = '\0';
					}
					else
					{
						count++;
						loca = 0;
						for (j = i; j < end; j++)
						{
							if (temp[j] != '\0' &&temp[j] != ' '&&temp[j] != '\t')
								break;
						}
						i = j - 1;
					}
				}
				for (i = 0; i < count + 1; i++)
				{
					xuhao[i] = find_element(save_element[i]);
				}
			}
			
		}
		//先继续读取每个原子的位置
		if (count >= 50)
		{
			cout << "too many atoms!please checke!" <<config_name<< endl;
			cin.get();
		}
		int cell_num = 0;
		for (i = 0; i < count + 1; i++)
		{
			cell_num += number[i];
		}
		for (i = 0; i < cell_num; i++)
		{
			for (j = 0; j < 3; j++)
			{
				fin >> location[i][j];
			}
			fin.getline(temp, 90);
		}
		//到这里结构的基本信息读取完成，开始写入结构文件
		
		ofstream fout;
		fout.open(outpath + head + config_name + "_"+to_string(name_tail++)+".config", ios::out);
		fout << cell_num << endl;
		fout << "Lattice vector" << endl;
		fout.setf(ios::fixed, ios::floatfield);  // 设定为 fixed 模式，以小数点表示浮点数
		fout.precision(8);
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				fout << ratio * letice[i][j] << "    ";
			}
			fout << endl;
		}
		int flag = 0;
		fout << "Position move_x, move_y, move_z" << endl;
		for (i = 0; i < count + 1; i++)
		{
			for (j = 0; j < number[i]; j++)
			{
				fout << xuhao[i] << "    ";
				for (int k = 0; k < 3; k++)
				{
					fout << location[flag][k] << "    ";					
				}
				fout << "1  1  1" << endl;
				flag++;
			}
		}
		fout.close();
		cout << "generate the file:" << config_name << endl;
		cout << name_tail - 1 << endl;
		//然后这里归零相关变量
		flag = 0;
		count = 0;
		loca = 0;
		for (i = 0; i < 50; i++)
		{
			number[i] = 0;
			xuhao[i] = 0;
			config_name[i] = '\0';
			save_element[i][0] = save_element[i][1] =  save_element[i][2] = '\0';
			for (j = 0; j < 3; j++)
			{
				location[i][j] = 0;
			}
		}
	}

	fin.close();
	return;



	
}

int find_element(char* str)
{
	int i = 0, j = 0;
	int length = strlen(str);
	
	for (i = 0; i < 120; i++)
	{
		if (length==2&&str[0] == atom_name[i][0] && str[1] == atom_name[i][1])
		{
			return i;
		}
		if (length==1&& str[0] == atom_name[i][0] && str[1] == '\0')
		{
			return i;
		}
	}
	if (i == 120)
	{
		cout << "i cann not find the element!" << str << endl;
		cin.get();
	}
	return -1;
}








void get_listnum(char*str, int*number)
{
	int i = 0, j = 0;
	int max_num = 50;
	char temp[5];
	for (i = 0; i < strlen(str) - 1; i++)
	{
		if (str[i] != ' '&&str[i] != '\t'&&str[i] != '\0')
			break;
	}
	j = i;
	int count = 0;
	int total = 0;
	for (i = j; i < strlen(str) - 1; i++)
	{
		if (str[i] != '\0' &&str[i] != ' '&&str[i] != '\t')
		{
			//cout << temp[i] << endl;
			temp[count++] = str[i];
			temp[count] = '\0';
		}
		else
		{
			//将上面的储存变成数字
			count = 0;
			number[total++] = atoi(temp);
			//cout << number[total - 1] << endl;
			for (j = i; j < strlen(str) - 1; j++)
			{
				if (str[j] != '\0' &&str[j] != ' '&&str[j] != '\t')
					break;
			}
			i = j - 1;
		}
	}
	return;
}
