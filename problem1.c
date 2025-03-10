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
	int alphabet[60] = { 0, };

	printf("Enter the sentense: ");
	gets(str);
	printf("%s\n", str);
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
			printf("%s\n", str);
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
			printf("%s\n", str);
		}
		else if (command == '1') {
			
			printf("%s\n", str);
		}
		else if (command == '2') {
			printf("%s\n", str);
		}
		else if (command == '3') {
			printf("%s\n", str);
		}
		else if (command == '4') {
			printf("%s\n", str);
		}
		else if (command == '5') {
			for (i = 0; str[i] == '.'; i++) {
				if (str[i] >= 'a' && str[i] <= 'z') {
					alphabet[str[i] - 'a']++;
				}
				else if (str[i] >= 'A' && str[i] <= 'Z') {
					alphabet[str[i] - 'A' + 26]++;
				}
			}
			for (i = 0; i < 52; i++) {
				if (i <= 25) {
					printf("%c: %d ", i + 'a', alphabet[i]);
				}
				else if (i > 25) {
					printf("%c: %d ", i - 26 + 'A', alphabet[i]);
				}
			}
		}
		printf("command: ");
		command = getchar();
	}

	return 0;
}