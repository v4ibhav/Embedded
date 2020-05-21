//Messi counter
//this code give the number of times a switch is pressed
#include <Reg52.h>

#define count_port P3
sbit Switch_pin = P1^0;

#define Switch_not_pressed (bit) 0
#define Switch_pressed (bit) 1

// function prototypes

void Switch_init(void);
bit get_input(const unsigned char);
void Display_Count_init(void);
void Display_Count_Update(const unsigned char );
void Delay_Loop(const unsigned int);

// main funtion
void main(void){
	// counter for switch press
	unsigned char Sw_press = 0;
    
    Switch_init();
    Display_Count_init();
    while(1){

    	if(get_input(30) == Switch_pressed){
    		Sw_press++;
    	}
    	Display_Count_Update(Sw_press);
    } 
}

// funtion definitions

void Switch_init(void){
	Switch_pin = 1;

}

bit get_input(const unsigned char Debounce_period){
	// this will tell me if switch is on or not 
	bit return_value = Switch_not_pressed;
	if(Switch_pin == 0){
		Delay_Loop(Debounce_period);

		if(Switch_pin == 0){
			while(Switch_pin==0);
			return_value = Switch_pressed;
		}


	}
	return return_value;
}

void Display_Count_init(void){
	count_port = 0x00;
}

void Display_Count_Update(const unsigned char COUNT ){
	count_port = COUNT;

}

void Delay_Loop(const unsigned int Delay_MS){

	unsigned int x,y;
	for(x = 0;x <= Delay_MS; x++)
	{
		for(y = 0; y <= 120 ; y++);
	}
}




