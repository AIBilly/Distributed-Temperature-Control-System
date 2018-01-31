#include "MasterControl.h"


bool MasterControl::addRoom(int room_number)
{
	if (room_map.end() == room_map.find(room_number)) {
		room_map[room_number] = room_map.size();
		work_allow_array.push_back(false);
		string state = createStateInfo();
		work_state_array.push_back(state);
		return true;
	}
	else {
		return false;
	}
}

void MasterControl::seeAllRoom()
{
	for (map<int, int>::iterator iter = room_map.begin(); iter != room_map.end(); iter++) {
		cout << iter->first << " " << work_allow_array[iter->second] << endl;
		cout << work_state_array[iter->second] << endl;
	}
}

vector<int> MasterControl::getAllRoomNumber()
{
	vector<int> ans;
	for (map<int, int>::iterator iter = room_map.begin(); iter != room_map.end(); iter++) {
		ans.push_back(iter->first);
	}
	return ans;
}

int MasterControl::getTargetTemperature(int room_number)
{
	if (room_map.end() == room_map.find(room_number)) {
		return 0;
	}
	else {
		map<int, int>::iterator iter = room_map.find(room_number);
		string state = work_state_array[iter->second];
		int state_buffer[STATE_ARRAY_LENGTH];
		if (!convertStateToArray(state, state_buffer)) {
			return 0;
		}
		else {
			return state_buffer[STATE_TARGET_TEMPERATURE];
		}
	}
}

int MasterControl::getTargetSpeed(int room_number)
{
	if (room_map.end() == room_map.find(room_number)) {
		return 0;
	}
	else {
		map<int, int>::iterator iter = room_map.find(room_number);
		string state = work_state_array[iter->second];
		int state_buffer[STATE_ARRAY_LENGTH];
		if (!convertStateToArray(state, state_buffer)) {
			return 0;
		}
		else {
			return state_buffer[STATE_TARGET_SPEED];
		}
	}
}

int MasterControl::getOpenOrClosed(int room_number)
{
	if (room_map.end() == room_map.find(room_number)) {
		return 0;
	}
	else {
		map<int, int>::iterator iter = room_map.find(room_number);
		string state = work_state_array[iter->second];
		int state_buffer[STATE_ARRAY_LENGTH];
		if (!convertStateToArray(state, state_buffer)) {
			return 0;
		}
		else {
			return state_buffer[IS_OPEN];
		}
	}
}

int MasterControl::getPresentTemperature(int room_number)
{
	if (room_map.end() == room_map.find(room_number)) {
		return 0;
	}
	else {
		map<int, int>::iterator iter = room_map.find(room_number);
		string state = work_state_array[iter->second];
		int state_buffer[STATE_ARRAY_LENGTH];
		if (!convertStateToArray(state, state_buffer)) {
			return 0;
		}
		else {
			return state_buffer[STATE_PRESENT_TEMPERATURE];
		}
	}
}

int MasterControl::getEnergy(int room_number)
{
	if (room_map.end() == room_map.find(room_number)) {
		return 0;
	}
	else {
		map<int, int>::iterator iter = room_map.find(room_number);
		string state = work_state_array[iter->second];
		int state_buffer[STATE_ARRAY_LENGTH];
		if (!convertStateToArray(state, state_buffer)) {
			return 0;
		}
		else {
			return state_buffer[STATE_ENERGY_USE];
		}
	}
}

int MasterControl::getPrice(int room_number)
{
	if (room_map.end() == room_map.find(room_number)) {
		return 0;
	}
	else {
		map<int, int>::iterator iter = room_map.find(room_number);
		string state = work_state_array[iter->second];
		int state_buffer[STATE_ARRAY_LENGTH];
		if (!convertStateToArray(state, state_buffer)) {
			return 0;
		}
		else {
			return state_buffer[STATE_PRICE];
		}
	}
}

bool MasterControl::isRoomSendWind(int room_number)
{
	if (room_map.end() == room_map.find(room_number)) {
		return false;
	}
	else {
		map<int, int>::iterator iter = room_map.find(room_number);
		return work_allow_array[iter->second];
    }
}

bool MasterControl::setPriceRate(int rate)
{
    unit_price = rate;
}

bool MasterControl::isInt(string test)
{
	for (int i = 0; i <= (int)test.size() - 1; i++) {
		if ('0' > test[i] && '9' < test[i]) {
			return false;
		}
	}
	return true;
}

int MasterControl::stringToInt(string in)
{
	stringstream ss;
	ss << in;
	int out;
	ss >> out;
	return out;
}

string MasterControl::intToString(int in)
{
	stringstream ss;
	ss << in;
	string ans;
	ss >> ans;
	return ans;
}

bool MasterControl::writeCommand(string order)
{
	CLock lock(command_lock);
	command_buffer.push_back(order);
	lock.~CLock();
	return true;
}

string MasterControl::readRequire()
{
	string ans = "";
	CLock lock(require_lock);
	if (require_buffer.empty()) {
		return ans;
	}
	else {
		ans = *(require_buffer.begin());
		require_buffer.erase(require_buffer.begin());
	}
	lock.~CLock();
	return ans;
}

bool MasterControl::convertSocketToArray(string socket, int buffer[])
{
	int temp_pos = 0;
	for (int i = 0; i <= SOCKET_ARRAY_LENGTH - 1; i++) {
		if ((int)socket.size() <= temp_pos) {
			return false;
		}
		size_t pos;
		if (SOCKET_ARRAY_LENGTH - 1 == i) {
			pos = (int)socket.size();
		}
		else {
			pos = socket.find(SEPARATOR, temp_pos);
			if (string::npos == pos) {
				return false;
			}
		}
		if(!isInt(socket.substr(temp_pos, (int)pos - temp_pos))){
			return false;
		}
		else {
			buffer[i] = stringToInt(socket.substr(temp_pos, (int)pos - temp_pos));
			temp_pos = pos + 1;
		}
	}
	return true;
}

bool MasterControl::convertStateToArray(string state, int buffer[])
{
	int temp_pos = 0;
	for (int i = 0; i <= STATE_ARRAY_LENGTH - 1; i++) {
		if ((int)state.size() <= temp_pos) {
			return false;
		}
		size_t pos;
		if (STATE_ARRAY_LENGTH - 1 == i) {
			pos = (int)state.size();
		}
		else {
			pos = state.find(SEPARATOR, temp_pos);
			if (string::npos == pos) {
				return false;
			}
		}
		if (!isInt(state.substr(temp_pos, (int)pos - temp_pos))) {
			return false;
		}
		else {
			buffer[i] = stringToInt(state.substr(temp_pos, (int)pos - temp_pos));
			temp_pos = pos + 1;
		}
	}
	return true;
}

bool MasterControl::shouldSendWind(int room_number)
{
	if (room_map.end() == room_map.find(room_number)) {
		return false;
	}
	else {
		int pos = room_map.find(room_number)->second;
		int buffer[STATE_ARRAY_LENGTH];
		if (!convertStateToArray(work_state_array[pos], buffer)) {
			return false;
		}
		else if(buffer[STATE_PRESENT_TEMPERATURE] != buffer[STATE_TARGET_TEMPERATURE]){
			if (COLD == mode && buffer[STATE_TARGET_TEMPERATURE] >= cold_down &&
				buffer[STATE_TARGET_TEMPERATURE] <= cold_up && 
				buffer[STATE_PRESENT_TEMPERATURE] > buffer[STATE_TARGET_TEMPERATURE]) {
				return true;
			}
			else if (HOT == mode && buffer[STATE_TARGET_TEMPERATURE] >= hot_down &&
				buffer[STATE_TARGET_TEMPERATURE] <= hot_up &&
				buffer[STATE_PRESENT_TEMPERATURE] < buffer[STATE_TARGET_TEMPERATURE]) {
				return true;
			}
		}
		return false;
	}
}
/*�����ӿص�����:
	����ͨ�ţ���ǰ�¶�
	����ͨ�ţ����ػ���־��Ŀ���¶ȣ�Ŀ�����٣���ǰ�¶�
	�ػ�ͨ�ţ����ػ���־
	�¶ȵ���ͨ�ţ���ǰ�¶�
	����ͨ�ţ�Ŀ���¶ȣ�Ŀ������

	���ĺ�������������֪ͨ��������
	�����е���
*/
bool MasterControl::analyzeRequire(string require_string)
{
	int require[SOCKET_ARRAY_LENGTH];
	if (!convertSocketToArray(require_string, require)) {
		return false;
	}
	else {
		CLock lock(work_lock);
		int flag = require[FROM_FLAG];
		int room_number = require[FROM_ROOM_NUMBER];
		switch (flag)
		{
		case(FROM_NORMAL) :
			setPresentTemperature(room_number, require[FROM_PRESENT_TEMPERATURE]);
			break;
		case(FROM_OPEN) :
			setOpenOrClosed(room_number, OPENING);
			setTargetTemperature(room_number, require[FROM_TARGET_TEMPERATURE]);
			setTargetSpeed(room_number, require[FROM_TARGET_SPEED]);
			setPresentTemperature(room_number, require[FROM_PRESENT_TEMPERATURE]);
			break;
		case(FROM_CLOSE) :
			setOpenOrClosed(room_number, CLOSED);
			break;
		case(FROM_INFORM):
			setPresentTemperature(room_number, require[FROM_PRESENT_TEMPERATURE]);
			break;
		case(FROM_CHANGE) :
			setTargetTemperature(room_number, require[FROM_TARGET_TEMPERATURE]);
			setTargetSpeed(room_number, require[FROM_TARGET_SPEED]);
			break;
		default:
			lock.~CLock();
			return false;
		}
		string ans = convertArrayToCommand(room_number);
		ans = intToString(TO_NOT_NORMAL) + " " + ans;
		ans = intToString(room_number) + " " + ans;
		writeCommand(ans);
		dispatch();
		lock.~CLock();
		return true;
	}
}
/*���ȣ�
	�������ͷ��ģ����Ѿ��ػ������߲������ͷ���׼�Ĵӻ�����Ϊ���ͷ�
	��û���ͷ��ģ��ڿ���״̬���Ҵﵽ�ͷ���׼�Ĵӻ�����Ϊ�ͷ�
	�ڴӻ����ͷ�״̬�ı�ʱ������������
*/
bool MasterControl::dispatch()
{
	int work_count = 0; 
	for (map<int, int>::iterator iter = room_map.begin(); iter != room_map.end(); iter++) {
		int pos = iter->second;
		int buffer[STATE_ARRAY_LENGTH];
		if (!convertStateToArray(work_state_array[pos], buffer)) {
			return false;
		}
		calculateEnergyAndPrice(iter->first);
		if (CLOSED == buffer[IS_OPEN] && work_allow_array[pos]) {
			work_allow_array[pos] = false;
		}
		else if (!shouldSendWind(iter->first) && work_allow_array[pos]) {
			work_allow_array[pos] = false;
			string ans = convertArrayToCommand(iter->first);
			ans = intToString(TO_NOT_NORMAL) + " " + ans;
			ans = intToString(iter->first) + " " + ans;
			writeCommand(ans);
		}
		if (true == work_allow_array[pos]) {
			work_count++;
		}
	}
	if (max_working_slave <= work_count) {
		return false;
	}
	else {
		int buffer[STATE_ARRAY_LENGTH];
		for (map<int, int>::iterator iter = room_map.begin(); iter != room_map.end(); iter++) {
			int pos = iter->second;
			if (max_working_slave <= work_count) {
				break;
			}
			if (!convertStateToArray(work_state_array[pos], buffer)) {
				return false;
			}
			else {
				if (!work_allow_array[pos] && shouldSendWind(iter->first) && OPENING == buffer[IS_OPEN] ) {
					calculateEnergyAndPrice(iter->first);
					work_allow_array[pos] = true;
					string ans = convertArrayToCommand(iter->first);
					ans = intToString(TO_NOT_NORMAL) + " " + ans;
					ans = intToString(iter->first) + " " + ans;
					writeCommand(ans);
					work_count++;
				}
			}	
		}
		return true;
	}
}

bool MasterControl::normalCommunicate()
{
	CLock lock(work_lock);
	for (map<int, int>::iterator iter = room_map.begin(); iter != room_map.end(); iter++) {
		calculateEnergyAndPrice(iter->first);
		string ans = convertArrayToCommand(iter->first);
		ans = intToString(TO_NORMAL) + " " + ans;
		ans = intToString(iter->first) + " " + ans;
		writeCommand(ans);
	}
	lock.~CLock();
	return false;
}
/*��������ģʽ��
	ģʽ���ĺ��������е���
	��������֪ͨ���ӻ�ģʽ�ı�
*/
bool MasterControl::setMode(int mode)
{
	CLock lock(work_lock);
	this->mode = mode;
	dispatch();
	for (map<int, int>::iterator iter = room_map.begin(); iter != room_map.end(); iter++) {
		string ans = convertArrayToCommand(iter->first);
		ans = intToString(TO_NOT_NORMAL) + " " + ans;
		ans = intToString(iter->first) + " " + ans;
		writeCommand(ans);
	}
	lock.~CLock();
	return true;
}
/*����ˢ���ʣ�
	ˢ�����޸ĺ�������������֪ͨ���ӻ�ģʽ�ı�
*/
bool MasterControl::setRefreshRate(int refresh_rate)
{
	CLock lock(work_lock);
	this->refresh_rate = refresh_rate;
	for (map<int, int>::iterator iter = room_map.begin(); iter != room_map.end(); iter++) {
		string ans = convertArrayToCommand(iter->first);
		ans = intToString(TO_NOT_NORMAL) + " " + ans;
		ans = intToString(iter->first) + " " + ans;
		writeCommand(ans);
	}
	lock.~CLock();
	return true;
}

string MasterControl::convertArrayToCommand(int room_number)
{
	string ans = "";
	
	if (room_map.end() == room_map.find(room_number)) {
		return ans;
	}
	else {
		int pos = room_map.find(room_number)->second;
		
		int buffer[STATE_ARRAY_LENGTH];
		convertStateToArray(work_state_array[pos], buffer);
		if (work_allow_array[pos]) {
			ans += intToString(SEND_WIND) + " ";
		}
		else {
			ans += intToString(NO_WIND) + " ";
		}
		ans += intToString(mode) + " "; 
		ans += intToString(buffer[STATE_TARGET_TEMPERATURE]) + " ";
		ans += intToString(buffer[STATE_TARGET_SPEED]) + " ";
		ans += intToString(buffer[STATE_ENERGY_USE]) + " ";
		ans += intToString(buffer[STATE_PRICE]) + " ";
		ans += intToString(refresh_rate);
	}
	return ans;
}

string MasterControl::createStateInfo()
{
	string ans = "";
	ans += intToString(CLOSED);
	ans += SEPARATOR;
	ans += intToString(cold_up);
	ans += SEPARATOR;
	ans += intToString(cold_up);
	ans += SEPARATOR;
	ans += intToString(LOW);
	ans += SEPARATOR;
	ans += intToString(0);
	ans += SEPARATOR;
	ans += intToString(0);
	ans += SEPARATOR;
	ans += intToString(clock());
	return ans;
}

bool MasterControl::setTargetTemperature(int room_number, int temperature)
{
	if (room_map.end() == room_map.find(room_number)) {
		return false;
	}
	else {
		map<int, int>::iterator iter = room_map.find(room_number);
		string state = work_state_array[iter->second];
		int state_buffer[STATE_ARRAY_LENGTH];
		if (!convertStateToArray(state, state_buffer)) {
			return false;
		}
		else {
			state_buffer[STATE_TARGET_TEMPERATURE] = temperature;
			state = "";
			for (int i = 0; i <= STATE_ARRAY_LENGTH - 2; i++) {
				state += intToString(state_buffer[i]) + SEPARATOR;
			}
			state += intToString(state_buffer[STATE_ARRAY_LENGTH - 1]);
			work_state_array[iter->second] = state;
			return true;
		}		
	}
}

bool MasterControl::setTargetSpeed(int room_number, int speed)
{
	if (room_map.end() == room_map.find(room_number)) {
		return false;
	}
	else {
		map<int, int>::iterator iter = room_map.find(room_number);
		string state = work_state_array[iter->second];
		int state_buffer[STATE_ARRAY_LENGTH];
		if (!convertStateToArray(state, state_buffer)) {
			return false;
		}
		else {
			state_buffer[STATE_TARGET_SPEED] = speed;
			state = "";
			for (int i = 0; i <= STATE_ARRAY_LENGTH - 2; i++) {
				state += intToString(state_buffer[i]) + SEPARATOR;
			}
			state += intToString(state_buffer[STATE_ARRAY_LENGTH - 1]);
			work_state_array[iter->second] = state;
			return true;
		}
	}
}

bool MasterControl::setOpenOrClosed(int room_number, int open_or_not)
{
	if (room_map.end() == room_map.find(room_number)) {
		return false;
	}
	else {
		map<int, int>::iterator iter = room_map.find(room_number);
		string state = work_state_array[iter->second];
		int state_buffer[STATE_ARRAY_LENGTH];
		if (!convertStateToArray(state, state_buffer)) {
			return false;
		}
		else {
			state_buffer[IS_OPEN] = open_or_not;
			state = "";
			for (int i = 0; i <= STATE_ARRAY_LENGTH - 2; i++) {
				state += intToString(state_buffer[i]) + SEPARATOR;
			}
			state += intToString(state_buffer[STATE_ARRAY_LENGTH - 1]);
			work_state_array[iter->second] = state;
			return true;
		}
	}
}

bool MasterControl::setPresentTemperature(int room_number, int temperature)
{
	if (room_map.end() == room_map.find(room_number)) {
		return false;
	}
	else {
		map<int, int>::iterator iter = room_map.find(room_number);
		string state = work_state_array[iter->second];
		int state_buffer[STATE_ARRAY_LENGTH];
		if (!convertStateToArray(state, state_buffer)) {
			return false;
		}
		else {
			state_buffer[STATE_PRESENT_TEMPERATURE] = temperature;
			state = "";
			for (int i = 0; i <= STATE_ARRAY_LENGTH - 2; i++) {
				state += intToString(state_buffer[i]) + SEPARATOR;
			}
			state += intToString(state_buffer[STATE_ARRAY_LENGTH - 1]);
			work_state_array[iter->second] = state;
			return true;
		}
	}
}

bool MasterControl::calculateEnergyAndPrice(int room_number)
{
	if (room_map.end() == room_map.find(room_number)) {
		return false;
	}
	else {
		map<int, int>::iterator iter = room_map.find(room_number);
		string state = work_state_array[iter->second];
		int state_buffer[STATE_ARRAY_LENGTH];
		if (!convertStateToArray(state, state_buffer)) {
			return false;
		}
		else {
			if (!work_allow_array[iter->second] || CLOSED == state_buffer[IS_OPEN]) {
				clock_t now_clock = clock();
				state_buffer[BEGIN_CLOCK] = now_clock;
				state = "";
				for (int i = 0; i <= STATE_ARRAY_LENGTH - 2; i++) {
					state += intToString(state_buffer[i]) + SEPARATOR;
				}
				state += intToString(state_buffer[STATE_ARRAY_LENGTH - 1]);
				work_state_array[iter->second] = state;
				return false;
			}
			int energy = state_buffer[STATE_ENERGY_USE];
			clock_t begin_clock = state_buffer[BEGIN_CLOCK];
			clock_t now_clock = clock();
			int bet_clock = now_clock - begin_clock;
			energy += 0.0001 * bet_clock * energy_use_count[state_buffer[STATE_TARGET_SPEED]];
			int price = energy * unit_price;
			state_buffer[BEGIN_CLOCK] = now_clock;
			state_buffer[STATE_ENERGY_USE] = energy;
			state_buffer[STATE_PRICE] = price;
			state = "";
			for (int i = 0; i <= STATE_ARRAY_LENGTH - 2; i++) {
				state += intToString(state_buffer[i]) + SEPARATOR;
			}
			state += intToString(state_buffer[STATE_ARRAY_LENGTH - 1]);
			work_state_array[iter->second] = state;
			return true;
		}
	}
}

bool MasterControl::setRoomNotAllow(int room_number)
{
	if (room_map.end() == room_map.find(room_number)) {
		return false;
	}
	else {
		map<int, int>::iterator iter = room_map.find(room_number);
		work_allow_array[iter->second] = false;
		return true;
	}	
}

string MasterControl::readCommand()
{
	string ans = "";
	CLock lock(command_lock);
	if (command_buffer.empty()) {
		return ans;
	}
	else {
		ans = *(command_buffer.begin());
		command_buffer.erase(command_buffer.begin());
	}
	lock.~CLock();
	return ans;
}

bool MasterControl::writeRequire(string require)
{
	CLock lock(require_lock);
	require_buffer.push_back(require);
	lock.~CLock();
	return true;
}
/*���ع��캯����
	ģʽĬ��ΪCOLD����
*/
MasterControl::MasterControl()
{
	mode = COLD;
}


MasterControl::~MasterControl()
{
}
