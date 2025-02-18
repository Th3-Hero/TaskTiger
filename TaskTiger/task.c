
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "file_io.h"
#include "string_utils.h"


Task createTask(const char* title) {
	Task newTask;
	strncpy(newTask.title, title, TASK_TITLE_LENGTH);
	strncpy(newTask.description, TASK_EMPTY_DESCRIPTION_PLACEHOLDER, TASK_DESCRIPTION_LENGTH);
	newTask.status = UNSET_STATUS;
	newTask.priority = UNSET_PRIORITY;
	newTask.date = createDateBlank();
	return newTask;
}

bool equalTask(Task t1, Task t2) {
	return (
		stringCompare(t1.title, t2.title) &&
		stringCompare(t1.description, t2.description) &&
		t1.status == t2.status &&
		t1.priority == t2.priority && 
		equalDate(t1.date, t2.date)
	);
}

Task copyTask(Task src) {
	Task newTask = createTask(src.title);
	strncpy(newTask.description, src.description, TASK_DESCRIPTION_LENGTH);
	newTask.status = src.status;
	newTask.priority = src.priority;
	newTask.date = copyDate(src.date);
	return newTask;
}
bool copyTaskInPlace(Task* dest, Task src) {
	if (dest == NULL) {
		fprintf(stderr, "Null pointer when trying to copy task\n");
		return false;
	}
	strncpy(dest->title, src.title, TASK_TITLE_LENGTH);
	strncpy(dest->description, src.description, TASK_DESCRIPTION_LENGTH);
	dest->status = src.status;
	dest->priority = src.priority;
	dest->date = copyDate(src.date);
	return true;
}

bool setTitle(Task* task, const char* newName) {
	if (task == NULL || newName == NULL) {
		fprintf(stderr, "Setter failed, NULL task or name\n");
		return false;
	}
	strncpy(task->title, newName, TASK_TITLE_LENGTH);
	return true;
}
bool setDescription(Task* task, const char* newDesc) {
	if (task == NULL || newDesc == NULL) {
		fprintf(stderr, "Setter failed, NULL task or desc\n");
		return false;
	}
	strncpy(task->description, newDesc, TASK_DESCRIPTION_LENGTH);
	return true;
}
bool setPriority(Task* task, Priority newPriority) {
	if (task == NULL) {
		fprintf(stderr, "Setter failed, NULL Task\n");
		return false;
	}
	task->priority = newPriority;
	return true;
}
bool setStatus(Task* task, Status newStatus) {
	if (task == NULL) {
		fprintf(stderr, "Setter failed, NULL Task\n");
		return false;
	}
	task->status = newStatus;
	return true;
}
bool setDate(Task* task, Date newDate) {
	if (task == NULL) {
		fprintf(stderr, "Setter failed, NULL Task\n");
		return false;
	}
	task->date = newDate;
	return true;
}


void printStatus(Status s, bool newLine) {
	switch (s) {
	case UNSET_STATUS:
		printf("Unset");
		break;
	case IN_PROGRESS:
		printf("In Progress");
		break;
	case ON_HOLD:
		printf("On Hold");
		break;
	case BLOCKED:
		printf("Blocked");
		break;
	case COMPLETED:
		printf("Completed");
		break;
	default:
		break;
	}
	if (newLine) {
		printf("\n");
	}
}
void printStatusT(Task t, bool newLine) {
	printStatus(t.status, newLine);
}
void printPriority(Priority p, bool newLine) {
	switch (p) {
	case UNSET_PRIORITY:
		printf("Unset");
		break;
	case LOW:
		printf("Low");
		break;
	case MEDIUM:
		printf("Medium");
		break;
	case HIGH:
		printf("High");
		break;
	case URGENT:
		printf("Urgent");
		break;
	default:
		break;
	}
	if (newLine) {
		printf("\n");
	}
}
void printPriorityT(Task t, bool newLine) {
	printPriority(t.priority, newLine);
}


bool saveTask(FILE* fp, Task task) {
	if (fp == NULL) {
		fprintf(stderr, "Null file pointer passed\n");
		return false;
	}

	writeStringToFile(fp, task.title);
	writeStringToFile(fp, task.description);
	writeIntToFile(fp, task.status);
	writeIntToFile(fp, task.priority);
	saveDate(fp, task.date);

	return true;
}
Task loadTask(FILE* fp) {
	if (fp == NULL) {
		fprintf(stderr, "Null file pointer passed\n");
		exit(-1);
	}

	Task newTask;

	getStringFromFile(fp, newTask.title, TASK_TITLE_LENGTH);
	getStringFromFile(fp, newTask.description, TASK_DESCRIPTION_LENGTH);
	getIntFromFile(fp, (int*)&newTask.status);
	getIntFromFile(fp, (int*)&newTask.priority);
	newTask.date = loadDate(fp);

	return newTask;
}




void debugPrintTask(Task t) {
	printf("=== DEBUG PRINT TASK ===\n");
	printf("Title: %s\n", t.title);
	printf("Description: %s\n", t.description);
	printf("Status: ");
	printStatus(t.status, true);
	printf("Priority: ");
	printPriority(t.priority, true);
	printf("Date: ");
	printDate(t.date, true);
}