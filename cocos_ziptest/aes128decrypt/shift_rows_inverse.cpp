#include "shift_rows_inverse.h"

string shift_rows_inverse(string buffer_data) {
	/**buffer data bytes order :
	*	0	1	2	3
	*	4	5	6	7
	*	8	9	10	11
	*	12	13	14	15
	*/
	string result_data;
	result_data.resize(16);

	for (size_t data_position = 0; data_position < 16; data_position++) {
		if (data_position < 4) {									//row1 : no change
			result_data[data_position] = buffer_data[data_position];
		}
		else if (data_position < 8) {							//row2: shift 1
			if (data_position - 1 < 4) result_data[data_position] = buffer_data[data_position - 1 + 4];
			else result_data[data_position] = buffer_data[data_position - 1];
		}
		else if (data_position < 12) {							//row3: shift 2
			if (data_position - 2 < 8) result_data[data_position] = buffer_data[data_position - 2 + 4];
			else result_data[data_position] = buffer_data[data_position - 2];
		}
		else {												//row4: shift 3
			if (data_position - 3 < 12) result_data[data_position] = buffer_data[data_position - 3 + 4];
			else result_data[data_position] = buffer_data[data_position - 3];
		}
	}
	return result_data;
}