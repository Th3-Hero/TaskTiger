#include <stdio.h>
#include <stdbool.h>
#include "user.h"
#include "TaskMenu.h"
#include "DisplayTaskMenu.h"
#include "input_handler.h"
#include "taskAPI.h"
#include "list.h"

/*printf("-----------------------------------------------\n");
	printf("				Task Menu\n");
	printf("-----------------------------------------------\n");
	printf("a) View Tasks\n");
	printf("b) Mark Task as Complete\n"); //award tiger points!
	printf("c) Create Task\n");
	printf("d) Edit Task\n");
	printf("e) Delete Task\n");

	printf("\nw) Back\n");*/

bool TaskMenu(Folder* folder, User* user) {

	bool inMenu = true;
	char input;
	while (inMenu) {
		DisplayTaskMenu();
		bool inputCheck = getCharFromUser(&input, "Please enter your choice: ");
		if (!inputCheck) {
			printf("error taking input.\n");
		}

		switch (input) {
		case 'a':
			PrintTasks(*folder->list);
			break;
		case 'b':
			markTaskAsComplete(user, folder->list);
			break;
		case 'c':
			append(folder->list, CreateTaskFromUser()); 
			break;
		case 'd':
			EditExistingTask(user, folder);
			break;
		case 'e':
			DeleteExistingTask(user, folder);
			break;

		case 'w': //back
			return true;
			break;

		}

	}
	return true;
}