// Process.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define MEMORY_SIZE 1000

int Memory[MEMORY_SIZE] = { 0 };//物理内存空间,为0表示此空间未被使用

/*将程序从磁盘读入内存，返回程序的逻辑地址到物理地址的映射表*/
bool GetProcessFromDisk(string FileName, vector<int>& VirtualMemory);

/*根据指令编号执行指令*/
bool ExcecuteProcess(int p_num);

/*将数据存入物理内存*/
int MemoryAllocation(int data);

/*释放指定物理地址的物理内存空间*/
bool MemoryFree(int address);

int main()
{
	while (true) {
		//外部调度，调度下一个要进入内存的程序
		cout << "请输入想执行的程序名:";
		string file_name;
		cin >> file_name;

		//从磁盘读取程序到内存
		vector<int> VirtualMemory;//逻辑内存到物理内存的映射表
		GetProcessFromDisk(file_name, VirtualMemory);

		//批处理，执行整个进程
		for (int i = 0; i < VirtualMemory.size(); i++)
			ExcecuteProcess(Memory[VirtualMemory[i]]);//从内存当中取出代码来执行

		//执行完后释放内存
		for (int i = 0; i < VirtualMemory.size(); i++)
			MemoryFree(VirtualMemory[i]);
	}
    return 0;
}

bool GetProcessFromDisk(string FileName, vector<int>& VirtualMemory) {
	//将程序从磁盘读入内存，返回程序的逻辑地址到物理地址的映射表
	//参数：程序文件名、映射表
	//返回值：true表示成功,false表示打开文件失败或内存空间不够

	string ProcessData;
	ifstream ProcessFile;
	ProcessFile.open(FileName, ios::in);
	if (ProcessFile.is_open()) {
		while (getline(ProcessFile, ProcessData)) {
			//将程序代码放入物理内存
			int PhysicalAddress = MemoryAllocation(atoi(ProcessData.c_str()));
			if (PhysicalAddress == -1) return false;

			//建立虚拟内存到物理内存的映射
			VirtualMemory.insert(VirtualMemory.end(), PhysicalAddress);
		}
		return true;
	}
	else {
		cout << "打开文件失败！" << endl;
		return false;
	}
}

int MemoryAllocation(int data) {
	//将数据存入物理内存
	//参数:要放入物理内存的数据
	//返回值:数据放在物理内存当中的地址,返回-1表示内存空间不够
	static int address = 0;
	
	//寻找空闲内存
	int old_address = address;
	while (Memory[address] != 0) {
		if (address < MEMORY_SIZE - 1)
			address++;
		else
			address = 0;

		if (old_address == address)
			return -1;//寻找空闲内存失败
	}

	//找到空闲内存，存入数据，返回此内存地址
	Memory[address] = data;
	return address;
}

bool MemoryFree(int address) {
	//释放指定物理地址的物理内存空间
	//参数：物理内存地址

	Memory[address] = 0;
	return true;
}

bool ExcecuteProcess(int p_num) {
	//根据指令编号执行指令
	switch (p_num) {
	case 1:
		cout << '1' << endl;
		break;
	case 2:
		cout << '2' << endl;
		break;
	case 3:
		cout << '3' << endl;
		break;
	case 4:
		cout << '4' << endl;
		break;
	case 5:
		cout << '5' << endl;
		break;
	case 6:
		cout << '6' << endl;
		break;
	case 7:
		cout << '7' << endl;
		break;
	case 8:
		cout << '8' << endl;
		break;
	default:
		cout << "error!" << endl;
		return false;
	}
	return true;
}