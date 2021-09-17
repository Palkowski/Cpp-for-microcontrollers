class Custom_LED_Matrix{
private:
	int j, k;
	uint16_t ar[7][8] = {
			{0, 0, 0, 0, 1, 1, 0, 0},
			{0, 0, 0, 1, 0, 0, 1, 0},
			{0, 0, 1, 0, 0, 0, 1, 0},
			{0, 1, 0, 0, 0, 1, 0, 0},
			{0, 0, 1, 0, 0, 0, 1, 0},
			{0, 0, 0, 1, 0, 0, 1, 0},
			{0, 0, 0, 0, 1, 1, 0, 0}
	};
public:
	Custom_LED_Matrix (){
		j = 0;
		k = 0;
	}

	void switch_cols(int j){
		switch(j){
		case 0:
			COL0_GPIO_Port->ODR = COL0_Pin & (0xFFFF * ar[k][j]);
			break;
		case 1:
			COL1_GPIO_Port->ODR = COL1_Pin & (0xFFFF * ar[k][j]);
			break;
		case 2:
			COL2_GPIO_Port->ODR = COL2_Pin & (0xFFFF * ar[k][j]);
			break;
		case 3:
			COL3_GPIO_Port->ODR = COL3_Pin & (0xFFFF * ar[k][j]);
			break;
		case 4:
			COL4_GPIO_Port->ODR = COL4_Pin & (0xFFFF * ar[k][j]);
			break;
		case 5:
			COL5_GPIO_Port->ODR = COL5_Pin & (0xFFFF * ar[k][j]);
			break;
		case 6:
			COL6_GPIO_Port->ODR = COL6_Pin & (0xFFFF * ar[k][j]);
			break;
		case 7:
			COL7_GPIO_Port->ODR = COL7_Pin & (0xFFFF * ar[k][j]);
			break;
		default:
			break;
		}
	}

	void display(){
		switch(k){
		case 0:
			ROW0_GPIO_Port->ODR = ~(ROW0_Pin & (0xFFFF * ar[k][j]));
			break;
		case 1:
			ROW1_GPIO_Port->ODR = ~(ROW1_Pin & (0xFFFF * ar[k][j]));
			break;
		case 2:
			ROW2_GPIO_Port->ODR = ~(ROW2_Pin & (0xFFFF * ar[k][j]));
			break;
		case 3:
			ROW3_GPIO_Port->ODR = ~(ROW3_Pin & (0xFFFF * ar[k][j]));
			break;
		case 4:
			ROW4_GPIO_Port->ODR = ~(ROW4_Pin & (0xFFFF * ar[k][j]));
			break;
		case 5:
			ROW5_GPIO_Port->ODR = ~(ROW5_Pin & (0xFFFF * ar[k][j]));
			break;
		case 6:
			ROW6_GPIO_Port->ODR = ~(ROW6_Pin & (0xFFFF * ar[k][j]));
			break;
		default:
			break;
		}
		switch_cols(this->j);
		if (j == 7){
			(k == 6) ? k = 0: k++;
		}
		(j == 7) ? j = 0: j++;
	}
};
