#include "shift_rows.h"

string shift_rows(string buffer_data) {
	/**buffer data bytes order :
	*	0	1	2	3
	*	4	5	6	7
	*	8	9	10	11
	*	12	13	14	15
	*/
	string result_data;
	result_data.resize(16);
		
	for (size_t data_pos = 0; data_pos < 16; data_pos++) {
		if (data_pos < 4) {									//row1 : no change
			result_data[data_pos] = buffer_data[data_pos];
		}
		else if (data_pos < 8) {							//row2: shift 1
			if (data_pos + 1 >= 8) result_data[data_pos] = buffer_data[data_pos + 1 - 4];
			else result_data[data_pos] = buffer_data[data_pos+1];
		}
		else if (data_pos < 12) {							//row3: shift 2
			if (data_pos + 2 >= 12) result_data[data_pos] = buffer_data[data_pos + 2 - 4];
			else result_data[data_pos] = buffer_data[data_pos+2];
		}
		else {												//row4: shift 3
			if (data_pos + 3 >= 16) result_data[data_pos] = buffer_data[data_pos + 3 - 4];
			else result_data[data_pos] = buffer_data[data_pos+3];
		}
	}
	return result_data;
}