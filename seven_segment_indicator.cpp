#define SEG_A Seg_0_Pin
#define SEG_B Seg_1_Pin
#define SEG_C Seg_2_Pin
#define SEG_D Seg_3_Pin
#define SEG_E Seg_4_Pin
#define SEG_F Seg_5_Pin
#define SEG_G Seg_6_Pin
#define SEG_H Seg_7_Pin

// Common anode, all NOT activated segments of digit
#define DIG0 ( SEG_G | SEG_H)
#define DIG1 ( SEG_A | SEG_B | SEG_E | SEG_F | SEG_G | SEG_H)
#define DIG2 ( SEG_C | SEG_F | SEG_H)
#define DIG3 ( SEG_B | SEG_F | SEG_H)
#define DIG4 ( SEG_A | SEG_B | SEG_E | SEG_H)
#define DIG5 ( SEG_B | SEG_D | SEG_H)
#define DIG6 ( SEG_D | SEG_H)
#define DIG7 ( SEG_A | SEG_B | SEG_F | SEG_G | SEG_H)
#define DIG8 ( SEG_H )
#define DIG9 ( SEG_B | SEG_H)
#define SYMB_A ( SEG_A | SEG_H)
#define SYMB_B ( SEG_D | SEG_E | SEG_H)
#define SYMB_C ( SEG_C | SEG_D | SEG_G | SEG_H)
#define SYMB_D ( SEG_F | SEG_E | SEG_H)
#define SYMB_E ( SEG_C | SEG_D | SEG_H)
#define SYMB_F ( SEG_A | SEG_C | SEG_D | SEG_H)
#define EMPTY_SYMB ( SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_H )
#define MINUS_SYMB ( SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_H )
#define POINT_SYMB ( SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G )
#define BIND_SYMB ( SEG_D | SEG_E | SEG_F | SEG_G )

class indicator{
private:
	int i, j;
public:
	uint16_t ind_out[8];
	indicator (){
		j = 0;
		for (i = 0; i < 8; i++){
			ind_out[i] = EMPTY_SYMB;
		}
	}

	void display(){
		switch(j){
		case 0:
			Anode_ssi1_0_GPIO_Port->ODR = Anode_ssi1_0_Pin | ind_out[0];
			break;
		case 1:
			Anode_ssi1_1_GPIO_Port->ODR = Anode_ssi1_1_Pin | ind_out[1];
			break;
		case 2:
			Anode_ssi1_2_GPIO_Port->ODR = Anode_ssi1_2_Pin | ind_out[2];
			break;
		case 3:
			Anode_ssi1_3_GPIO_Port->ODR = Anode_ssi1_3_Pin | ind_out[3];
			break;
		case 4:
			Anode_ssi2_0_GPIO_Port->ODR = Anode_ssi2_0_Pin | ind_out[4];
			break;
		case 5:
			Anode_ssi2_1_GPIO_Port->ODR = Anode_ssi2_1_Pin | ind_out[5];
			break;
		case 6:
			Anode_ssi2_2_GPIO_Port->ODR = Anode_ssi2_2_Pin | ind_out[6];
			break;
		case 7:
			Anode_ssi2_3_GPIO_Port->ODR = Anode_ssi2_3_Pin | ind_out[7];
			break;
		default:
			break;
		}
		(j == 7) ? j = 0: j++;
	}

	void write(uint8_t from, uint8_t to, uint16_t values[]){
		for (i = from; i <= to; i++){
			ind_out[i] = values[i-from];
		}
	}
};

int ssi_digits_f(char smb){
	switch (smb){
		case '0':
			return DIG0;
			break;
		case '1':
			return DIG1;
			break;
		case '2':
			return DIG2;
			break;
		case '3':
			return DIG3;
			break;
		case '4':
			return DIG4;
			break;
		case '5':
			return DIG5;
			break;
		case '6':
			return DIG6;
			break;
		case '7':
			return DIG7;
			break;
		case '8':
			return DIG8;
			break;
		case '9':
			return DIG9;
			break;
		case 'a':
			return SYMB_A;
			break;
		case 'b':
			return SYMB_B;
			break;
		case 'c':
			return SYMB_C;
			break;
		case 'd':
			return SYMB_D;
			break;
		case 'e':
			return SYMB_E;
			break;
		case 'f':
			return SYMB_F;
			break;
		case '.':
			return POINT_SYMB;
			break;
		case '-':
			return MINUS_SYMB;
			break;
		case 'o':
			return BIND_SYMB;
			break;
		case ' ':
			return EMPTY_SYMB;
			break;
		default:
			return SYMB_D;
			break;
	}
}


class input_screen {
private:
	int i, lng;
	std::string screen;
public:
	input_screen (int lng){
		this->lng = lng;
		screen = "";
		for (i = 0; i < lng; i++){
			screen += " ";
		}
	}

	void clear(){
		screen = "";
		for (i = 0; i < lng; i++){
			screen += " ";
		}
	}

	void enter(int n){
		for (i = 0; i < lng-1; i++){
			if (screen[lng-1] == '0' && screen[lng-2] == ' '){
				break;
			} else {
				screen[i] = screen[i+1];
			}
		}
		for (i = 0; i < lng-1; i++){
			if (screen[i] == '0'){
				screen[i] = ' ';
			} else {
				break;
			}
		}
		screen[lng-1] = std::to_string(n)[0];
	}

	std::string get(){
		return screen;
	}
};


void convert_to_ssi_code(int val, uint8_t lng, uint16_t * out_vals){
	std::string buf = std::to_string(val), res = "";
	uint8_t i, val_len = buf.length();
	if (val_len < lng){
		for (i = 0; i < lng - val_len; i++){
			res += ' ';
		}
		res += buf;
	}
	for (i = 0; i < lng; i++){
		out_vals[i] = ssi_digits_f(res[i]);
	}
}


void convert_to_ssi_code(float val, uint8_t point, uint16_t * out_vals){
	std::string buf = std::to_string(val), res = "";
	uint8_t i, p_flag = 0, int_part_len = std::to_string(int(val)).length();
	if (int_part_len < point){
		for (i = 0; i < point - int_part_len; i++){
			res += ' ';
		}
		res += buf;
	}
	for (i = 0; i < 8; i++){
		if (res[i] == '.'){
			p_flag = 1;
			out_vals[i - 1] = out_vals[i - 1] ^ SEG_H;
		}
		out_vals[i] = ssi_digits_f(res[i+p_flag]);
	}
}


void convert_to_ssi_code(std::string val, uint16_t * out_vals){
	uint8_t i;
	for (i = 0; i < val.length(); i++){
		out_vals[i] = ssi_digits_f(val[i]);
	}
}
