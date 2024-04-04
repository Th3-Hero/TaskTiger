#include <stdio.h>
#include <stdbool.h>
#include "TaskMenu.h"
#include "DisplayTaskMenu.h"
#include "input_handler.h"
#include "taskAPI.h"

/*printf("-----------------------------------------------\n");
	printf("				Task Menu\n");
	printf("-----------------------------------------------\n");
	printf("a) View Tasks\n");
	printf("b) Mark Task as Complete\n"); //award tiger points!
	printf("c) Create Task\n");
	printf("d) Edit Task\n");
	printf("e) Delete Task\n");

	printf("\nw) Back\n");
	printf("q) Save and Quit\n");*/
bool TaskMenuMenu(Folder folder) {
	DisplayTaskMenu();//changed up to here <
	bool inMenu = true;
	char input = { 0 };
	while (inMenu) {
		bool inputCheck = getCharFromUser(&input, "Please enter your choice: ");
		if (!inputCheck) {
			printf("error taking input.\n");
		}

		switch (input) {
		case 'a':
			//DisplayTasks(); //create
			break;
		case 'b':
			//MarkTaskAsComplete(); //create
			break;
		case 'c':
			append(folder.list, CreateTaskFromUser()); //CreateTask(); //create
			break;
		case 'd':
			SetOptional(searchTask(&(folder.list))); //EditTask(); //create
			break;
		case 'e':
			//DeleteTask(); //create
			break;

		case 'w': //back
			return true;
			break;
		case 'q': //quit
			//SaveAndQuit();
			inMenu = false;
		}

	}
}