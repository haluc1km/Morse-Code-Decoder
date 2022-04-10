#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    char* morse;
    char* ascii;
} morse_table_t;

void menuInput();

#define BUTTON_A 23 //BCM/GPIO 13	INPUT
#define BUTTON_B 25 //BCM/GPIO 26	INPUT

#define LED_B 27	//BCM/GPIO 16	OUTPUT
char startinput =' ';
int go = 1;

unsigned long duration;
static unsigned long button_pressed_timestamp;
unsigned long duration1;
static unsigned long button_pressed_timestamp1;
unsigned long duration2;
static unsigned long button_pressed_timestamp2;

int main(void) {
	//check the wiringPi setup---always include this
	if (wiringPiSetup() == -1) {
		puts("Raspberry Pi setup failed. Unable to execute the program.");
		return 1; //terminate program if the Pi setup failed
	}
	//set pin mode 
    pinMode(BUTTON_A, INPUT);
	pinMode(BUTTON_B, INPUT);
	pinMode(LED_B, OUTPUT);
    char input[40] = "";
char output[40] = "";
char empty[40] = "";
char output1[40] = "";
    char input1[40];   
	puts("Welcome to my Morse Code Decoder!");
    int buttonPressed =0;
        while(go = 1){
            menuInput();
                switch(startinput){
        case '.': 
                printf("Please enter your message (Caps Only!): \n");
            strcpy(input, empty);
            strcpy(output, empty);
            strcpy(output1, empty);
            strcpy(input1, empty);
  scanf("%[^\n]%*c", input1);
   


    morse_table_t table1[] = { 
    {".-", "A"},
    {"-...", "B"},
    {"-.-.", "C"},
    {"-..", "D"},
    {".","E"},
    {"..-.","F"},
    {"--.","G"},
    {"....","H" },
    {"..","I"},
    {".---","J"},
    {"-.-","K"},
    {".-..","L"},
    {"--","M"},
    {"-.","N"},
    {"---","O"},
    {".--.","P"},
    {"--.-","Q"},
    {".-.","R"},
    {"...","S"},
    {"-","T"},
    {"..-","U"},
    {"...-","V"},
    {".--","W"},
    {"-..-","X"},
    {"-.--","Y"},
    {"--..","Z"},
    {"/", " "}
    };

    char* segment2;
    int j;
    char new [40] = "";
    char* dash;
    for ( dash = &input1[0]; *dash != '\0'; dash++ )
    {   
        strncat(new, dash, 1);
        strcat(new, "-");
    }

    char blink[] = "";
    segment2 = strtok(new, "-");
    int k =0;
    while(segment2)
    {
        for(j=0; j< 27; ++j)
        {
            if (!strcmp(segment2, table1[j].ascii)){
             strcat(output1, table1[j].morse);
             strcpy(blink, output1);
             strcat(output1, "\n");
            }
        }
        segment2 = strtok(NULL, "-");
    }
    puts(output1);
    char* s;
     for ( s=&blink[0]; *s != '\0'; s++ ) {
        if(*s == '.'){
	digitalWrite(LED_B, 1);
	delay(300);
	digitalWrite(LED_B, 0);
    delay(400);
        }
        if(*s =='-'){
	digitalWrite(LED_B, 1);
	delay(800);
	digitalWrite(LED_B, 0);
    delay(400);
        }
        if(*s =='/'){
    delay(1000);
        }

    }
                break;
        case '-':  
            button_pressed_timestamp = 0;
            buttonPressed = 0;
            duration1 = 0;
            int h = 0;
            strcpy(input, empty);
            strcpy(output, empty);
            strcpy(output1, empty);
            strcpy(input1, empty);
                puts("Start entering your message:");
                while(1 == 1){
                if(digitalRead(BUTTON_B) == HIGH){ //button pressed
                		if(buttonPressed == 0){
						//Turn on LED
                        button_pressed_timestamp = millis();
                        duration1 = millis()-button_pressed_timestamp1;
						digitalWrite(LED_B, 1);
                        if(duration1 > 1000){
                            if(duration1 < 2499){
                            strcat(input, "_");
                        }
                        }
                         if(duration1 > 2500){
                             if(h != 0){
                            strcat(input, "_/_");
                             }
                        }
						buttonPressed = 1;
					}					
				} 	else {
					 if(buttonPressed == 1){ //previous status is PRESSED
						//turn off the LED
                        button_pressed_timestamp1 = millis();
                        duration = millis()-button_pressed_timestamp;
                        if(duration < 200){
                        strcat(input, ".");
                        h++;
                        delay(100);
                        printf("Current input: %s \n", &input);
                        } else if(duration < 500){ 
                        strcat(input, "-");
                        delay(100);
                        h++;
                        printf("Current input: %s \n", &input);
                        }
                        if(duration > 1500){
                            digitalWrite(LED_B, 0);
                            puts(input);
                            break;
                     }
						digitalWrite(LED_B, 0);
						buttonPressed = 0;
					}
                    }
                }morse_table_t table[] = { 
    {".-", "A"},
    {"-...", "B"},
    {"-.-.", "C"},
    {"-..", "D"},
    {".","E"},
    {"..-.","F"},
    {"--.","G"},
    {"....","H" },
    {"..","I"},
    {".---","J"},
    {"-.-","K"},
    {".-..","L"},
    {"--","M"},
    {"-.","N"},
    {"---","O"},
    {".--.","P"},
    {"--.-","Q"},
    {".-.","R"},
    {"...","S"},
    {"-","T"},
    {"..-","U"},
    {"...-","V"},
    {".--","W"},
    {"-..-","X"},
    {"-.--","Y"},
    {"--..","Z"},
    {"/"," "}
    };

    char* segment;
    int i;
    segment = strtok(input, "_");

    while(segment)
    {
        for(i=0; i< 27; ++i)
        {
            if (!strcmp(segment, table[i].morse)) strcat(output, table[i].ascii);
        }
        segment = strtok(NULL, "_");
    }
             puts("Your message is: ");
             puts(output);
                break;
                
        }
}
}

void menuInput(){
     int buttonPressed1 =0;
    puts("-------------------------------------------------------------");
    puts("Press start button once for message to morse code translator");
    puts("Press button for a couple seconds to decode a morse code message");
    puts("Hold start button to exit program.");
    puts("-------------------------------------------------------------");

     while(1 == 1){

		if (digitalRead(BUTTON_A) == HIGH){//button pressed
                		if(buttonPressed1 == 0){
						digitalWrite(LED_B, 1);
						buttonPressed1 = 1;
                        button_pressed_timestamp2 = millis();
					}					
				} 	else {
					 if(buttonPressed1 == 1){ //previous status is PRESSED
                        duration2 = millis()-button_pressed_timestamp2;
                        if(duration2 < 200){
                        startinput = '.';
                        delay(100);
                        digitalWrite(LED_B, 0);
						buttonPressed1 = 0;
                        break;
                        } else if(duration2 < 500){
                        startinput = '-';
                        delay(100);
                        digitalWrite(LED_B, 0);
						buttonPressed1 = 0;
                        break;
                        }
                        if(duration2 > 1000){
                            go = 0;
                            digitalWrite(LED_B, 0);
                            exit(0);
                            break;
                        }
                        digitalWrite(LED_B, 0);
						buttonPressed1 = 0;
                     }
                }
     }
}
