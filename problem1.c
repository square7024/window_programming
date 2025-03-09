#include <stdio.h>

int main() {
	char str[80];
	char str_backup3[80];
	char str_backup4[80];
	int backup3 = 0;
	int backup4 = 0;
	char command;
	int i;
	int j;

	printf("Enter the sentense: ");
	gets(str);
	printf("%s\n", str);
	printf("%d\n", str[0]);
	printf("command: ");
	command = getchar();
	while (command != '0') 
	{
		if (command >= 'a' && command <= 'z') {
			for (i = 0; i < 80; i++) {
				if (command == str[i] + 32) {
					str[i] = command;
				}
				else if (command == str[i]) {
					str[i] = command - 32;
				}
				else if (str[i] == '.') {
					break;
				}
			}
		}
		else if (command >= 'A' && command <= 'Z') {
			for (i = 0; i < 80; i++) {
				if (command + 32 == str[i]) {
					str[i] = command;
				}
				else if (command == str[i]) {
					str[i] = command + 32;
				}
				else if (str[i] == '.') {
					break;
				}
			}
		}
		else if (command == '1') {

		}
		else if (command == '2') {

		}
		else if (command == '3') {
			if (backup3 == 0) {

			}
			else if(backup3 == 1) {

			}
		}
		else if (command == '4') {

		}
		else if (command == '5') {

		}
		printf("%s\n", str);
		printf("command: ");
		command = getchar();
	}
	
	return 0;
}