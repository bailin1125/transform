#include <iostream>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#pragma warning(disable : 4996)
using namespace std;
const double pi = 3.1415926;
const int cengshu = 3;
const double zoom_factor = 1.2;
const int yanshen = cengshu*cengshu*cengshu;
const char a[120][3] = { " ", "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lw", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg" };
double dist[120][120];
int meatal_xuhao[86] = { 3, 4, 11, 12, 13, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 37, 38, 39, 40, 41, 42, 43, 44,45, 46, 47, 48, 49, 50, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111 };
double dis(double *p1, double *p2)
{
	return sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2) + pow(p1[2] - p2[2], 2));
}
void new_get_style(char *style)
{
	ifstream fin;
	fin.open(style, ios::in);
	if (!fin.is_open())
	{
		cout << "i can not find the file:" << style << endl;
		cin.get();
	}
	while (fin.good())
	{
		for (int i = 1; i < 112; i++)
		{
			for (int j = 1; j < 112; j++)
			{
				fin >> dist[i][j];
			}
		}
	}
	fin.close();
	return;
}
class cell
{
public:
	cell(const char *jiegou_name,int flag=0);
	int num = 0;
	double *ridus;
	double **letice;
	double **p;
	double ***p_real;
	double ***real_position;
	int *type;
};
int atom2vesta(cell cell_a, string name, string* input, string dir_path, string head_1layer_path);
cell::cell(const char *name,int falg)
{
	int i, j, k;
	//cout << "expand the :" << cengshu << "layer" << endl;
	char temp[300];
	double x_pian = 0.0;
	double y_pian = 0.0;
	double z_pian = 0.0;
	//strcpy(wenjian, "atom1.config");
	FILE *in;
	in = fopen(name, "rt");
	//system("pause");
	if (in == NULL)
	{
		printf("error of rading atom.config!\n");
		printf("the filename is :%s\n", name);
		//cin.get();
		return;
	}
	fscanf(in, "%d", &num);
	if (falg == 1)
	{
		ridus = new double[num];
	}	
	type = (int *)malloc(num * sizeof(int));
	letice = (double **)malloc(3 * sizeof(double *));
	for (i = 0; i < 3; i++)
	{
		letice[i] = (double *)malloc(3 * sizeof(double));
	}
	p = (double **)malloc(num * sizeof(double *));
	for (i = 0; i < num; i++)
	{
		p[i] = (double *)malloc(3 * sizeof(double));
	}
	real_position = (double ***)malloc(yanshen * sizeof(double **));
	for (i = 0; i < yanshen; i++)
	{
		real_position[i] = (double **)malloc(num * sizeof(double *));
		for (k = 0; k < num; k++)
			real_position[i][k] = (double *)malloc(3 * sizeof(double));
	}

	p_real = new double **[yanshen];
	for (i = 0; i < yanshen; i++)
	{
		p_real[i] = new double *[num];
		for (k = 0; k < num; k++)
		{
			p_real[i][k] = new double[3];
		}
	}
	while (fgets(temp, 300, in) != NULL)
	{
		if (strstr(temp, "VECTOR") != NULL || strstr(temp, "vector") != NULL)
			break;
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			fscanf(in, "%lf", &letice[i][j]);
		}
	}

	fgets(temp, 300, in);
	fgets(temp, 300, in);
	for (i = 0; i < num; i++)
	{

		fscanf(in, "%d", &type[i]);
		fscanf(in, "%lf", &p[i][0]);
		fscanf(in, "%lf", &p[i][1]);
		fscanf(in, "%lf", &p[i][2]);
		if (falg == 1)
		{
			fscanf(in, "%lf", &ridus[i]);
		}		
		fgets(temp, 300, in);
	}
	//int x_xishu = 0;
	//int y_xishu = 0;
	//int z_zishu = 0;

	for (i = 0; i < yanshen; i++)
	{

		for (j = 0; j < num; j++)
		{
			//x_xishu = i/3;
			//y_xishu = i / 3;
			//z_zishu = (i % 9) / 3;

			real_position[i][j][0] = letice[0][0] * p[j][0] + letice[1][0] * p[j][1] + letice[2][0] * p[j][2] + (i % cengshu - ((cengshu - 1) / 2)) * letice[0][0] + (i % (cengshu * cengshu) / cengshu - ((cengshu - 1) / 2)) * letice[1][0] - (i / (cengshu * cengshu) - ((cengshu - 1) / 2)) * letice[2][0];
			real_position[i][j][1] = letice[0][1] * p[j][0] + letice[1][1] * p[j][1] + letice[2][1] * p[j][2] + (i % cengshu - ((cengshu - 1) / 2)) * letice[0][1] + (i % (cengshu * cengshu) / cengshu - ((cengshu - 1) / 2)) * letice[1][1] - (i / (cengshu * cengshu) - ((cengshu - 1) / 2)) * letice[2][1];
			real_position[i][j][2] = letice[0][2] * p[j][0] + letice[1][2] * p[j][1] + letice[2][2] * p[j][2] + (i % cengshu - ((cengshu - 1) / 2)) * letice[0][2] + (i % (cengshu * cengshu) / cengshu - ((cengshu - 1) / 2)) * letice[1][2] - (i / (cengshu * cengshu) - ((cengshu - 1) / 2)) * letice[2][2];
		}
	}
	for (i = 0; i < yanshen; i++)
	{
		for (j = 0; j < num; j++)
		{
			p_real[i][j][0] = (i % cengshu - ((cengshu - 1) / 2)) + p[j][0];
			p_real[i][j][1] = (i % (cengshu * cengshu) / cengshu - ((cengshu - 1) / 2)) + p[j][1];
			p_real[i][j][2] = -(i / (cengshu * cengshu) - ((cengshu - 1) / 2)) + p[j][2];
		}
	}

	fclose(in);
}
inline double vector_angle(double**a);
inline double vector_length(double*a);
inline int judge_metal(int& xuhao);
const int puls_falg = 1;//是否启用复杂的程序，0表示不启动，1表示启动，即每次生成vesta时向
int main(int argc, char*argv[])
{
	int i = 0, j = 0;	

	string org_path = "/share/home/wangz/2d_search/ridus_cut/analyse/2/2d/config/";//储存原来的atom.config文件的位置
	string dir_path= "/share/home/wangz/2d_search/ridus_cut/analyse/2/2d/vesta/";//产生的.vesta文件放到哪里去
	string head_1layer_path = "/share/home/wangz/2d_search/ridus_cut/analyse/2/bulk/config/";
	/*org_path.clear();
	dir_path.clear();*/
	char filename[100] = "2_2dname";//储存了所有的atom.config
	for (i = 0; i < argc; i++)
		{
		if (i == 1)
		{
			for (j = 0; j < strlen(argv[i]); j++)
			{
				filename[j] = argv[i][j];
				//cout<<argv[i][j]<<endl;
				//cout<<wenjian[j]<<endl;
			}
			filename[strlen(argv[i])] = '\0';
		}
		if (i == 2)
		{
			for (j = 0; j < strlen(argv[i]); j++)
			{
				org_path[j] = argv[i][j];
				//cout<<argv[i][j]<<endl;
				//cout<<wenjian[j]<<endl;
			}
			org_path[strlen(argv[i])] = '\0';
		}
		if (i == 3)
		{
			for (j = 0; j < strlen(argv[i]); j++)
			{
				dir_path[j] = argv[i][j];
				//cout<<argv[i][j]<<endl;
				//cout<<wenjian[j]<<endl;
			}
			dir_path[strlen(argv[i])] = '\0';
		}
		
	}
	int atom_file_num;
	string temp;	
	ifstream fin;
	fin.open(filename, ios::in);
	if (!fin.is_open())
	{
		cout << "i can not find the file:" << filename << endl;
		cin.get();
		return 0;
	}
	while (fin.good())
	{
		fin >> temp;
		i++;
	}
	atom_file_num = i - 2;
	cout << "has " << atom_file_num << " lines!" << endl;

	cout << "this software can change atom.comnfig to vesta file!" << endl;
	string org_name = "rule_noorg_for_pc_10-8.txt";
	//new_get_style(const_cast<char*>(org_name.c_str()));


	//看看是不是读对了
	//cout << "li -li :"<<dist[3][3] << endl;
	//cin.get();
	//只用修改bond和替换对称操作即可
	
	fin.close();
	fin.open(filename, ios::in);
	string * file_name = new string[atom_file_num];
	fin.seekg(0, ios::beg);
	for (i = 0; i < atom_file_num; i++)
	{
		fin >> file_name[i];
		cout << file_name[i] << endl;

	}
	fin.close();
	//cin.get();
	//读取结构文件名字完成

	//然后开始定义需要相关的输入信息
	string input[20];
	input[0] = "TITLE";
	input[1] = "GROUP";
	input[2] = "CELLP";
	input[3] = "STRUC";
	input[4] = "THERI 0";
	input[5] = "SBOND";
	input[6] = "2	1	P	-1";//这个是定义每个就是规定为最小的对称操作
	input[7] = "0  1  1  0  1  0.250  2.000 127 127 127";
	input[8] = "SCENE";
	input[9] = "HBOND 0 2";


	//观看的角度
	input[10] = "1.000000 -0.000000 -0.000000  0.000000";
	input[11] = "0.000000  1.000000 -0.000000  0.000000";
	input[12] = "0.000000  0.000000  1.000000  0.000000";
	input[13] = "0.000000  0.000000  0.000000  1.000000";
	input[14] = "0.000000   0.000000   0.000000   0.000000   0.000000   0.000000";
	
	input[15] = "#VESTA_FORMAT_VERSION 3.3.0";
	input[16] = "CRYSTAL";
	
	//下面开始批量输出
	for (i = 0; i < atom_file_num; i++)
	{
		cell cell_a((org_path+file_name[i]).c_str(),0);
		atom2vesta(cell_a, file_name[i],input,dir_path,head_1layer_path);
		for (int i = 0; i < 120; i++)
		{
			for (int j = 0; j < 120; j++)
			{
				dist[i][j] = 0;
			}
		}
		cout << "has genereated the :" << i+1 << " files" << endl;

	}
	
	
	cout << "all total work done!" << endl;
	cin.get();

	delete[]file_name;
	return 0;
}
int atom2vesta(cell cell_a, string name,string* input,string dir_path, string head_1layer_path)//输入一个atom.config,输出一个vesta文件
{
	int i = 0, j = 0,k=1,m=0;
	int bianli = 0;


	//这里对于dist进行修改，基于给定的半径形成dist
	if (puls_falg == 0)
	{
		for (i = 0; i < cell_a.num; i++)
		{
			for (j = 0; j < cell_a.num; j++)
			{
				dist[cell_a.type[i]][cell_a.type[j]] = cell_a.ridus[i] + cell_a.ridus[j];
			}
		}

	}
	else
		//否则我们需要向上一次去寻找对应体材料的rule是什么
	{
		char real_bulk[200];
		i = name.find('-');
		for (j = 0; j < i; j++)
		{
			real_bulk[j] = name[j];
		}
		real_bulk[j] = '\0';
		strcat(real_bulk, ".config");
		real_bulk[j+8] = '\0';
		//cout << "the real bulk is:" << real_bulk << endl;
		string bulk = head_1layer_path + real_bulk;
		cell cell_b(bulk.c_str(),1);
		//下面开始要读体材料的rule了
		double *rule = new double[cell_a.num];
		for (i = 0; i < cell_a.num; i++)
		{
			for (j = 0; j < cell_b.num; j++)
			{
				if (cell_a.type[i] == cell_b.type[j])
				{
					rule[i] = cell_b.ridus[j];
					break;
				}
			}
		}
		for (i = 0; i < cell_a.num; i++)
		{
			for (j = 0; j < cell_b.num; j++)
			{
				dist[cell_a.type[i]][cell_a.type[j]] = rule[i] + rule[j];
			}
		}
		delete[]rule;
	}
	

	ofstream fout;
	fout.open(dir_path+name + ".vesta",ios::out);
	int front = 0;
	int element_flag[120] = { 0 };
	for (i = 0; i < cell_a.num; i++)
	{
		element_flag[cell_a.type[i]]++;
	}
	int **save_element = new int*[cell_a.num];
	for (i = 0; i < cell_a.num; i++)
	{
		save_element[i] = new int[2];
	}
	for (i = 0; i < 120; i++)
	{
		if (element_flag[i] != 0)
		{
			save_element[front][0] = i;
			save_element[front][1] = element_flag[i];
			//cout << save_element[front][1] << endl;
			front++;
		}
		
	}
	fout << input[15] << endl;
	fout << endl << endl;
	fout << input[16] << endl;
	fout << endl;
	fout << input[0] << endl;
	for (j = 0; j < front; j++)
	{
		fout << a[save_element[j][0]] << save_element[j][1] << '\t';
	}
	fout << endl;
	fout << endl;

	//fout << input[1] << endl;
	//fout << input[6] << endl;
	//fout << endl;
	//下面是晶格参数，整整吧
	double lattice_length[3] = { 0 };
	double lattice_angle[3] = { 0 };
	for (i = 0; i < 3; i++)
	{
		lattice_length[i] = vector_length(cell_a.letice[i]);
	}

	double **temp_angle = new double*[2];
	for (i = 0; i < 2; i++)
	{
		temp_angle[i] = new double[3];
	}
	int loop = 1;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			temp_angle[0][j] = cell_a.letice[loop%3][j];
			temp_angle[1][j]= cell_a.letice[(loop+1)%3][j];
		}
		lattice_angle[i] = vector_angle(temp_angle);
		loop++;
	}


	//开始输出晶格信息
	fout.setf(ios::fixed);
	fout.precision(6);
	fout << input[2] << endl;
	for (i = 0; i < 3; i++)
	{
		fout << "  "<<lattice_length[i] << "  ";
	}
	for (i = 0; i < 3; i++)
	{
		fout << lattice_angle[i] << "  ";
	}
	fout << endl;
	fout << "  " << input[14] << endl;
	fout << endl;


	//这里要开始输出每个原子的位置坐标信息
	bool* use_falg = new bool[cell_a.num];
	for (i = 0; i < cell_a.num; i++)
	{
		use_falg[i] = false;
	}
	j = 0;
	fout << input[3] << endl;
	for (i = 0; i < front; i++)
	{
		for (bianli = 0; bianli < cell_a.num; bianli++)
		{
			if (use_falg[bianli] == false && cell_a.type[bianli] ==save_element[i][0])
			{
				fout << "  " << k++ << "  ";

				

				fout << a[save_element[i][0]] << "\t\t" << a[save_element[i][0]] << j + 1 << "\t\t" << "1.0000" << "\t";
				for (m = 0; m < 3; m++)
				{
				    fout << cell_a.p[bianli][m] << "\t";
				}
				fout << endl;
				fout << "\t\t\t\t\t\t\t\t" << double(0) << "\t" << double(0) << "\t" << double(0) << endl;
				use_falg[bianli] = true;
				j++;
			}				
		}
		j = 0;
	}	
	fout << "0 0 0 0 0 0 0" << endl;
	k = 1;
	fout << input[4] << endl;
	for (i = 0; i < front; i++)
	{
		for (j = 0; j < save_element[i][1]; j++)
		{
			
			fout << " " << k++ << "\t\t" << a[save_element[i][0]] << j+1 << "\t" << double(1) << endl;
		}
	}
	fout << " 0 0 0" << endl;

	k = 1;
	fout << input[5] << endl;
	int pair_num = cell_a.num*(cell_a.num - 1) / 2 + cell_a.num;
	int metal_sure[2] = { 0 };
	for (i = 0; i < front; i++)
	{
		for (j = i; j < front; j++)
		{
			//这里修改，金属在前，非金属在后
			//metal_sure[0] = judge_metal(save_element[i][0]);
			//修改1：这里的成键判断基于给定的半径之和
			metal_sure[1] = judge_metal(save_element[j][0]);
			if (metal_sure[1] == 1)
			{
				fout << k++ << "\t" << a[save_element[j][0]] << "\t" << a[save_element[i][0]] << "\t" << 0.0 << "\t";
				fout << dist[save_element[i][0]][save_element[j][0]] << "\t" << input[7] << endl;
			}
			else
			{
				fout << k++ << "\t" << a[save_element[i][0]] << "\t" << a[save_element[j][0]] << "\t" << 0.0 << "\t";
				fout << dist[save_element[i][0]][save_element[j][0]] << "\t" << input[7] << endl;
			}
			
		}
		
	}
	fout << "0 0 0 0" << endl;

	//最后我们定义几个视角
	fout << input[8] << endl;
	fout <<" "<<input[10] << endl;
	fout << " " << input[11] << endl;
	fout << " " << input[12] << endl;
	fout << " " << input[13] << endl;
	fout << "  0.000   0.000" << endl;
	fout << "  0.000" << endl;
	fout << "  "<<zoom_factor<<endl;
	fout << input[9] << endl;
	for (i = 0; i < 2; i++)
	{
		delete[]temp_angle[i];
	}
	delete[]temp_angle;



	for (i = 0; i < cell_a.num; i++)
	{
		delete[]save_element[i];
	}
	delete[]save_element;
	delete[]use_falg;
	fout.unsetf(ios::fixed);
	return 0;
}
inline double vector_angle(double**a)
{
	//用来求两个向量的夹角，结果以角度制返回

	double a_mu = pow(pow(a[0][0], 2) + pow(a[0][1], 2) + pow(a[0][2], 2), 0.5);
	double b_mu = pow(pow(a[1][0], 2) + pow(a[1][1], 2) + pow(a[1][2], 2), 0.5);
	double diancheng = a[0][0] * a[1][0] + a[0][1] * a[1][1] + a[0][2] * a[1][2];
	double jungel_orig = acos(diancheng / (a_mu*b_mu)) * 180 / pi;
	//cout << "the judge angle is:" << jungel_orig << endl;
	return jungel_orig;
}
inline double vector_length(double*a)
{
	double result;
	result = pow(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2), 0.5);
	return result;
}

inline int judge_metal(int& xuhao)
{
	int i = 0;
	for (i = 0; i < 86; i++)
	{
		if (meatal_xuhao[i] == xuhao)
			break;
	}
	if (i == 86)
		return 0;
	else
		return 1;
}