#pragma once
#include "Lock.h"
#include <windows.h> 
#include <string>
#include <vector>
#include <map>
#include <time.h> 
using namespace std;

/*主机从require缓冲区中获取从机的请求，解析后更新工作状态链表*/
/*根据工作状态链表与调度规则对允许工作链表进行修改*/
/*发送每个从控的命令到command缓冲区中*/

/*通信协议中的分隔符*/
const string SEPARATOR = " ";
/*从控机发来的信息数组---标志位 房间号 当前温度 目标温度 目标风速*/
enum from_array { FROM_FLAG, FROM_ROOM_NUMBER, FROM_PRESENT_TEMPERATURE, FROM_TARGET_TEMPERATURE, FROM_TARGET_SPEED };
const int SOCKET_ARRAY_LENGTH = 5;
/*从控发来的标志位说明---每刷新率时间的例行通信，开机通信，关机通信，达到温度时通知主机，从机要求改变目标温度或者目标风速*/
enum from_flag { FROM_NORMAL, FROM_OPEN, FROM_CLOSE, FROM_INFORM, FROM_CHANGE };

/*主控发出的标志位说明---标志位0代表主机回的不是例行通信，1代表主机回的是例行通信*/
enum to_flag { TO_NOT_NORMAL, TO_NORMAL };

/*协议说明*/
enum speed { LOW = 1, MIDDLE, HIGH };
enum mode { COLD = 1, HOT };
enum send_wind { NO_WIND, SEND_WIND };

/*主机工作状态数组中的信息数组---是否开机，当前温度，目标温度，目标风速，能耗用量，费用金额, 上次计算能耗时间*/
enum work_state_array_info { IS_OPEN, STATE_PRESENT_TEMPERATURE, STATE_TARGET_TEMPERATURE, STATE_TARGET_SPEED, STATE_ENERGY_USE, STATE_PRICE , BEGIN_CLOCK};
/*工作状态数组说明*/
enum is_open { CLOSED, OPENING };
const int STATE_ARRAY_LENGTH = 7;
/*主机模式的温度范围*/
const int cold_down = 18;
const int cold_up = 25;
const int hot_up = 30;
const int hot_down = 25;
/*标准条件*/
const int temperature = 25;
const int speed = LOW;
const int energy_use_count[] = { 0, 10, 20, 30 };
const int normal_time = 2000;

class MasterControl
{
private:
	/*判断test是否为整型*/
	bool isInt(string test);
	/*将string转为int，在isInt()之后调用*/
	int stringToInt(string in);
	/*将int转为string*/
	string intToString(int in);

	/*主机工作模式*/
	int mode;
	/*刷新率时间 单位为秒*/
	int refresh_rate = 1;
	/*存储房间号到工作数组下标的映射*/
	map<int, int> room_map;
	/*最大允许负载*/
	const int max_working_slave = 3;
	/*允许工作数组*/
	vector<bool> work_allow_array;
	/*工作状态数组*/
	vector<string> work_state_array;
	/*对工作数组的互斥锁*/
	Mutex work_lock;


	/*存储主控到从控的命令，设置为互斥资源*/
	vector<string> command_buffer;
	/*存储从控到主控的命令，设置为互斥资源*/
	vector<string> require_buffer;
	/*对command_buffer的互斥锁*/
	Mutex command_lock;
	/*对require_buffer的互斥锁*/
	Mutex require_lock;
	
	/*将从控发来的socket字符串转换为数组形式，若返回false说明socket不规范*/
	/*使用前确保buffer大小为SOCKET_ARRAY_LENGTH*/
	bool convertSocketToArray(string socket, int buffer[]);
	/*将工作状态数组中的字符串信息转换为数组形式*/
	/*使用前确保buffer大小为STATE_ARRAY_LENGTH*/
	bool convertStateToArray(string state, int buffer[]);
	/*创建一个状态信息*/
	string createStateInfo();
	/*将房间的信息打包成命令*/
	string convertArrayToCommand(int room_number);

	/*判断房间是否可以送风*/
	bool shouldSendWind(int room_number);

	/*修改房间的目标温度*/
	bool setTargetTemperature(int room_number, int temperature);
	/*修改房间的目标风速*/
	bool setTargetSpeed(int room_number, int speed);
	/*修改房间的开关机状态*/
	bool setOpenOrClosed(int room_number, int open_or_not);
	/*修改房间当前温度*/
	bool setPresentTemperature(int room_number, int temperature);
	/*计算房间能耗用量与价格
		并且将该房间的计时器置为当前时刻
	*/
	bool calculateEnergyAndPrice(int room_number);
	/*修改房间的允许工作数组为false*/
	bool setRoomNotAllow(int room_number);
	
    int unit_price = 5;
	
	

public:
	/*将对从控的命令输入buffer缓冲区*/
	bool writeCommand(string command);
	/*从buffer中读取一个从控的命令*/
	string readRequire();

	/*分析从控的请求:
	例行通信：当前温度
	开机通信：开关机标志，目标温度，目标风速，当前温度
	关机通信：开关机标志
	温度到达通信：当前温度
	更改通信：目标温度，目标风速

	更改后立即发送命令通知更改完成
	并进行调度
	*/
	bool analyzeRequire(string require_string);
	/*调度：
	将正在送风的，但已经关机、或者不符合送风标准的从机设置为不送风
	将没有送风的，在开机状态并且达到送风标准的从机设置为送风
	在从机的送风状态改变时立即发送命令
	*/
	bool dispatch();
	/*主机例行通信*/
	bool normalCommunicate();

	/*socket从buffer中读取一个命令，若buffer中无内容则返回""*/
	string readCommand();
	/*socket向buffer中写入一个请求*/
	bool writeRequire(string require);
    /*查看所有房间的状态信息*/
    void seeAllRoom();


    //the following is usable
	/*添加一个房间*/
    bool addRoom(int room_number);
	/*获取所有房间号*/
	vector<int> getAllRoomNumber();
	/*查看房间的目标温度*/
	int getTargetTemperature(int room_number);
	/*查看房间的目标风速*/
    int getTargetSpeed(int room_number);
	/*查看房间的开关机状态*/
    int getOpenOrClosed(int room_number);
	/*查看房间当前温度*/
    int getPresentTemperature(int room_number);
	/*查看房间能耗用量*/
    int getEnergy(int room_number);
	/*查看房间费用金额*/
    int getPrice(int room_number);
	/*查看房间送风状态*/
	bool isRoomSendWind(int room_number);
    /*change price rate*/
    bool setPriceRate(int rate);
	
	/*主机设置模式：
		模式更改后立即进行调度
		发送命令通知各从机模式改变
	*/
	bool setMode(int mode);
	/*设置刷新率：
		刷新率修改后立即发送命令通知各从机刷新率改变
	*/
	bool setRefreshRate(int refresh_rate);
	
	MasterControl();
	~MasterControl();
};

