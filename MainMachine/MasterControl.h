#pragma once
#include "Lock.h"
#include <windows.h> 
#include <string>
#include <vector>
#include <map>
#include <time.h> 
using namespace std;

/*������require�������л�ȡ�ӻ������󣬽�������¹���״̬����*/
/*���ݹ���״̬��������ȹ������������������޸�*/
/*����ÿ���ӿص����command��������*/

/*ͨ��Э���еķָ���*/
const string SEPARATOR = " ";
/*�ӿػ���������Ϣ����---��־λ ����� ��ǰ�¶� Ŀ���¶� Ŀ�����*/
enum from_array { FROM_FLAG, FROM_ROOM_NUMBER, FROM_PRESENT_TEMPERATURE, FROM_TARGET_TEMPERATURE, FROM_TARGET_SPEED };
const int SOCKET_ARRAY_LENGTH = 5;
/*�ӿط����ı�־λ˵��---ÿˢ����ʱ�������ͨ�ţ�����ͨ�ţ��ػ�ͨ�ţ��ﵽ�¶�ʱ֪ͨ�������ӻ�Ҫ��ı�Ŀ���¶Ȼ���Ŀ�����*/
enum from_flag { FROM_NORMAL, FROM_OPEN, FROM_CLOSE, FROM_INFORM, FROM_CHANGE };

/*���ط����ı�־λ˵��---��־λ0���������صĲ�������ͨ�ţ�1���������ص�������ͨ��*/
enum to_flag { TO_NOT_NORMAL, TO_NORMAL };

/*Э��˵��*/
enum speed { LOW = 1, MIDDLE, HIGH };
enum mode { COLD = 1, HOT };
enum send_wind { NO_WIND, SEND_WIND };

/*��������״̬�����е���Ϣ����---�Ƿ񿪻�����ǰ�¶ȣ�Ŀ���¶ȣ�Ŀ����٣��ܺ����������ý��, �ϴμ����ܺ�ʱ��*/
enum work_state_array_info { IS_OPEN, STATE_PRESENT_TEMPERATURE, STATE_TARGET_TEMPERATURE, STATE_TARGET_SPEED, STATE_ENERGY_USE, STATE_PRICE , BEGIN_CLOCK};
/*����״̬����˵��*/
enum is_open { CLOSED, OPENING };
const int STATE_ARRAY_LENGTH = 7;
/*����ģʽ���¶ȷ�Χ*/
const int cold_down = 18;
const int cold_up = 25;
const int hot_up = 30;
const int hot_down = 25;
/*��׼����*/
const int temperature = 25;
const int speed = LOW;
const int energy_use_count[] = { 0, 10, 20, 30 };
const int normal_time = 2000;

class MasterControl
{
private:
	/*�ж�test�Ƿ�Ϊ����*/
	bool isInt(string test);
	/*��stringתΪint����isInt()֮�����*/
	int stringToInt(string in);
	/*��intתΪstring*/
	string intToString(int in);

	/*��������ģʽ*/
	int mode;
	/*ˢ����ʱ�� ��λΪ��*/
	int refresh_rate = 1;
	/*�洢����ŵ����������±��ӳ��*/
	map<int, int> room_map;
	/*���������*/
	const int max_working_slave = 3;
	/*����������*/
	vector<bool> work_allow_array;
	/*����״̬����*/
	vector<string> work_state_array;
	/*�Թ�������Ļ�����*/
	Mutex work_lock;


	/*�洢���ص��ӿص��������Ϊ������Դ*/
	vector<string> command_buffer;
	/*�洢�ӿص����ص��������Ϊ������Դ*/
	vector<string> require_buffer;
	/*��command_buffer�Ļ�����*/
	Mutex command_lock;
	/*��require_buffer�Ļ�����*/
	Mutex require_lock;
	
	/*���ӿط�����socket�ַ���ת��Ϊ������ʽ��������false˵��socket���淶*/
	/*ʹ��ǰȷ��buffer��СΪSOCKET_ARRAY_LENGTH*/
	bool convertSocketToArray(string socket, int buffer[]);
	/*������״̬�����е��ַ�����Ϣת��Ϊ������ʽ*/
	/*ʹ��ǰȷ��buffer��СΪSTATE_ARRAY_LENGTH*/
	bool convertStateToArray(string state, int buffer[]);
	/*����һ��״̬��Ϣ*/
	string createStateInfo();
	/*���������Ϣ���������*/
	string convertArrayToCommand(int room_number);

	/*�жϷ����Ƿ�����ͷ�*/
	bool shouldSendWind(int room_number);

	/*�޸ķ����Ŀ���¶�*/
	bool setTargetTemperature(int room_number, int temperature);
	/*�޸ķ����Ŀ�����*/
	bool setTargetSpeed(int room_number, int speed);
	/*�޸ķ���Ŀ��ػ�״̬*/
	bool setOpenOrClosed(int room_number, int open_or_not);
	/*�޸ķ��䵱ǰ�¶�*/
	bool setPresentTemperature(int room_number, int temperature);
	/*���㷿���ܺ�������۸�
		���ҽ��÷���ļ�ʱ����Ϊ��ǰʱ��
	*/
	bool calculateEnergyAndPrice(int room_number);
	/*�޸ķ��������������Ϊfalse*/
	bool setRoomNotAllow(int room_number);
	
    int unit_price = 5;
	
	

public:
	/*���Դӿص���������buffer������*/
	bool writeCommand(string command);
	/*��buffer�ж�ȡһ���ӿص�����*/
	string readRequire();

	/*�����ӿص�����:
	����ͨ�ţ���ǰ�¶�
	����ͨ�ţ����ػ���־��Ŀ���¶ȣ�Ŀ����٣���ǰ�¶�
	�ػ�ͨ�ţ����ػ���־
	�¶ȵ���ͨ�ţ���ǰ�¶�
	����ͨ�ţ�Ŀ���¶ȣ�Ŀ�����

	���ĺ�������������֪ͨ�������
	�����е���
	*/
	bool analyzeRequire(string require_string);
	/*���ȣ�
	�������ͷ�ģ����Ѿ��ػ������߲������ͷ��׼�Ĵӻ�����Ϊ���ͷ�
	��û���ͷ�ģ��ڿ���״̬���Ҵﵽ�ͷ��׼�Ĵӻ�����Ϊ�ͷ�
	�ڴӻ����ͷ�״̬�ı�ʱ������������
	*/
	bool dispatch();
	/*��������ͨ��*/
	bool normalCommunicate();

	/*socket��buffer�ж�ȡһ�������buffer���������򷵻�""*/
	string readCommand();
	/*socket��buffer��д��һ������*/
	bool writeRequire(string require);
    /*�鿴���з����״̬��Ϣ*/
    void seeAllRoom();


    //the following is usable
	/*���һ������*/
    bool addRoom(int room_number);
	/*��ȡ���з����*/
	vector<int> getAllRoomNumber();
	/*�鿴�����Ŀ���¶�*/
	int getTargetTemperature(int room_number);
	/*�鿴�����Ŀ�����*/
    int getTargetSpeed(int room_number);
	/*�鿴����Ŀ��ػ�״̬*/
    int getOpenOrClosed(int room_number);
	/*�鿴���䵱ǰ�¶�*/
    int getPresentTemperature(int room_number);
	/*�鿴�����ܺ�����*/
    int getEnergy(int room_number);
	/*�鿴������ý��*/
    int getPrice(int room_number);
	/*�鿴�����ͷ�״̬*/
	bool isRoomSendWind(int room_number);
    /*change price rate*/
    bool setPriceRate(int rate);
	
	/*��������ģʽ��
		ģʽ���ĺ��������е���
		��������֪ͨ���ӻ�ģʽ�ı�
	*/
	bool setMode(int mode);
	/*����ˢ���ʣ�
		ˢ�����޸ĺ�������������֪ͨ���ӻ�ˢ���ʸı�
	*/
	bool setRefreshRate(int refresh_rate);
	
	MasterControl();
	~MasterControl();
};

