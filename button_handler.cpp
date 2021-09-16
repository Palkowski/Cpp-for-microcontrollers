class TickCounter {
private:
	uint32_t cnt_value;
	bool is_cnt_started;
public:
	TickCounter(){
		cnt_value = 0;
		is_cnt_started = false;
	}
	
	void start(){
		cnt_value = HAL_GetTick();
		is_cnt_started = true;
	}
	
	bool check(int time_passed){
		if (HAL_GetTick() - cnt_value > time_passed && is_cnt_started){
			return true;
			is_cnt_started = false;
		} else {
			return false;
		}
	}
};


class ButtonRow {
private:
	bool button_value_to_handle;
	bool* is_pushed, is_pushed_old, button_value_to_handle;
	uint16_t* button_pins;
	GPIO_TypeDef* button_GPIO_port;
	TickCounter* cnt;
	int size;
public:
	ButtonRow (GPIO_TypeDef* button_GPIO_port, uint16_t button_pins[]){
		size = sizeof(button_pins)/sizeof(uint16_t);
		this->button_pins = new uint16_t[size];
		cnt = new TickCounter[size];
		is_pushed = new bool[size];
		is_pushed_old = new bool[size];
		for (int i = 0; i < size; i++){
			this->button_pins[i] = button_pins[i];
			is_pushed[i] = false;
			is_pushed_old[i] = false;
			button_value_to_handle[i] = false;
		}
		this->button_GPIO_port = button_GPIO_port;
	}
	
	void poll(){
		for (int i = 0; i < size; i++){
			HAL_GPIO_WritePin(button_GPIO_port, button_pin[i], GPIO_PIN_SET);
			is_pushed_old[i] = is_pushed[i];
			is_pushed[i] = ((button_GPIO_port->IDR & button_pin[i]) > 0);
			HAL_GPIO_WritePin(button_GPIO_port, button_pin[i], GPIO_PIN_RESET);
			if (!is_pushed_old[i] && is_pushed[i]){
				cnt[i].start();
			}
			if (is_pushed[i] && cnt[i].check(150)){
				button_value_to_handle[i] = true;
			}
		}
	}
	
	bool read(int col){
		bool to_return = button_value_to_handle[col];
		button_value_to_handle[col] = false;
		return to_return;
	}
};
