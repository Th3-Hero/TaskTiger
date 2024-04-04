

#include <stdio.h>
#include <stdlib.h>

#include "pch.h"
#include "CppUnitTest.h"


#define TASK_TITLE_LENGTH 128
#define TASK_DESCRIPTION_LENGTH 512

#define TASK_EMPTY_DESCRIPTION_PLACEHOLDER "EMPTY_TASK_DESCRIPTION"

#define USERNAME_LENGTH 128
#define MAX_PASSWORD_LENGTH 64

#define MAX_TIGER_NAME 128

#define FOLDER_NAME_LENGTH 128

typedef struct Date {
	int day;
	int month;
	int year;
} Date;

typedef enum Status {
	UNSET_STATUS,
	IN_PROGRESS,
	ON_HOLD,
	BLOCKED,
	COMPLETED
} Status;

typedef enum Priority {
	UNSET_PRIORITY,
	LOW,
	MEDIUM,
	HIGH,
	URGENT
} Priority;

typedef struct Task {
	char title[TASK_TITLE_LENGTH];
	char description[TASK_DESCRIPTION_LENGTH];
	Status status;
	Priority priority;
	Date date;
} Task;

typedef struct List {
	size_t size;
	size_t capacity;
	Task* arr;
} List;

typedef struct Folder {
	char name[FOLDER_NAME_LENGTH];
	List* list;
} Folder;

typedef struct FolderNode {
	Folder folder;
	struct FolderNode* next;
} FolderNode, * pFolderNode;

typedef struct FolderList {
	FolderNode* head;
} FolderList;

typedef enum TigerStatus {
	SAD,
	HUNGRY,
	HAPPY
} TigerStatus;

typedef struct tiger {
	char name[MAX_TIGER_NAME];

	TigerStatus tigerMood;
	int hunger;
	Date lastFed;
	Date lastChecked;
} Tiger;

typedef struct User {
	char username[USERNAME_LENGTH];
	char passward[MAX_PASSWORD_LENGTH];
	FolderList folders;
	int points;
	int totalTasksCompleted;
	int tasksCompletedOnTime;
	Date lastTaskCompletedDate;
	Tiger tiger;
} User;

typedef enum SortOrder {
	ASCENDING,
	DESCENDING
} SortOrder;

typedef enum SortKey {
	TITLE,
	STATUS,
	PRIORITY,
	DATE
} SortKey;

extern "C" Date createDate(int day, int month, int year);
extern "C" Date createDate(int day, int month, int year);
extern "C" Date createDateBlank();
extern "C" bool equalDate(Date, Date);
extern "C" bool emptyDate(Date);
extern "C" Date copyDate(Date src);
extern "C" bool copyDateInPlace(Date* dest, Date src);
extern "C" Date getCurrentDate();
extern "C" void printDate(Date date, bool newLine);
extern "C" bool stringToDate(Date* output, const char* dateString);
extern "C" bool getDateFromUser(Date* output, const char* prompt, ...);
extern "C" int dateDifference(Date, Date);
extern "C" int dateDifferenceAbsolute(Date, Date);

extern "C" Task createTask(const char* title);
extern "C" bool equalTask(Task, Task);
extern "C" Task copyTask(Task src);
extern "C" bool copyTaskInPlace(Task* dest, Task src);
extern "C" bool setTitle(Task* task, const char* newName);
extern "C" bool setDescription(Task* task, const char* newDesc);
extern "C" bool setPriority(Task* task, Priority newPriority);
extern "C" bool setStatus(Task* task, Status newStatus);
extern "C" bool setDate(Task* task, Date newDate);

extern "C" User createUser(const char* username, const char* password);
extern "C" bool equalUser(User, User);
extern "C" User copyUser(User);
extern "C" bool copyUserInPlace(User* dest, User src);
extern "C" bool setUsername(User*, const char* newUsername);
extern "C" bool setPassword(User*, const char* newPassword);
extern "C" bool increasePoints(User*, int amount);
extern "C" bool decreasePoints(User*, int amount);
extern "C" bool taskCompleted(User*, Task);
extern "C" bool wipeProfile(User*, bool youSure);


extern "C" List* createList();
extern "C" List* copyList(const List*);
extern "C" bool equalList(const List*, const List*);
extern "C" bool append(List*, Task);
extern "C" bool insert(List*, size_t index, Task);
extern "C" bool removeTask(List*, Task);
extern "C" bool pop(List*, size_t index);
extern "C" bool clear(List*);
extern "C" bool set(List*, size_t index, Task);
extern "C" size_t size(const List*);
extern "C" bool isEmpty(const List*);
extern "C" bool contains(const List*, Task);
extern "C" List* filterByTitle(const List*, const char* title);
extern "C" List* filterByStatus(const List*, Status);
extern "C" List* filterByPriority(const List*, Priority);
extern "C" List* filterByDate(const List*, Date);
extern "C" List* filterByDateTimeRemaining(const List*, int daysRemaining);
extern "C" bool sortList(List*, SortKey, SortOrder);
extern "C" void destroyList(List*);

extern "C" bool stringCompare(const char*, const char*);
extern "C" bool stringCompareI(const char*, const char*);

extern "C" bool writeIntToFile(FILE* fp, int integer);
extern "C" bool getIntFromFile(FILE* fp, int* output);

bool getIntFromUser(int* output, const char* prompt, ...);
bool getIntFromUserWithRange(int min, int max, int* output, const char* prompt, ...);
bool getCharFromUser(char* outputChar, const char* prompt, ...);
bool getStringFromUser(int maxLength, char* output, const char* prompt, ...);

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ADTTesting {
	TEST_CLASS(DATE_TESTING) {
	public:
		TEST_METHOD(CreateDate_Test) {
			int day = 6;
			int month = 6;
			int year = 2024;
			
			Date result = createDate(day, month, year);

			Assert::AreEqual(result.day, day);
			Assert::AreEqual(result.month, month);
			Assert::AreEqual(result.year, year);
		}
		TEST_METHOD(EqualDate_Test) {
			Date d1 = createDate(5, 5, 2025);
			Date d2 = createDate(5, 5, 2025);

			bool result = equalDate(d1, d2);

			Assert::IsTrue(result);
		}
		TEST_METHOD(EqualDate_FalseDay_Test) {
			Date d1 = createDate(5, 5, 2025);
			Date d2 = createDate(7, 5, 2025);

			bool result = equalDate(d1, d2);

			Assert::IsFalse(result);
		}
		TEST_METHOD(EqualDate_FalseMonth_Test) {
			Date d1 = createDate(5, 5, 2025);
			Date d2 = createDate(5, 7, 2025);

			bool result = equalDate(d1, d2);

			Assert::IsFalse(result);
		}
		TEST_METHOD(EqualDate_FalseYear_Test) {
			Date d1 = createDate(5, 5, 2025);
			Date d2 = createDate(5, 5, 2027);

			bool result = equalDate(d1, d2);

			Assert::IsFalse(result);
		}
		TEST_METHOD(EmptyDate_Test) {
			Date date = createDateBlank();

			bool result = emptyDate(date);

			Assert::IsTrue(result);
		}
		TEST_METHOD(CopyDate_Test) {
			Date date = createDate(5, 5, 2025);

			Date copy = copyDate(date);

			Assert::AreEqual(date.day, copy.day);
			Assert::AreEqual(date.month, copy.month);
			Assert::AreEqual(date.year, copy.year);
		}
		TEST_METHOD(CopyDateInPlace_Test) {
			Date date = createDate(5, 5, 2025);

			Date copy;

			bool result = copyDateInPlace(&copy, date);

			Assert::IsTrue(result);
			Assert::AreEqual(date.day, copy.day);
			Assert::AreEqual(date.month, copy.month);
			Assert::AreEqual(date.year, copy.year);
		}
		TEST_METHOD(CopyDateInPlace_NullDest_Test) {
			Date date = createDate(5, 5, 2025);

			bool result = copyDateInPlace(NULL, date);

			Assert::IsFalse(result);
		}
		TEST_METHOD(StringToDate_Test) {
			Date targetDate = createDate(5, 5, 2025);
			Date date;
			const char* string = "5-5-2025";

			bool result = stringToDate(&date, string);

			Assert::IsTrue(result);
			Assert::IsTrue(equalDate(date, targetDate));
		}
		TEST_METHOD(StringToDate_Slash_Test) {
			Date targetDate = createDate(5, 5, 2025);
			Date date;
			const char* string = "5/5/2025";

			bool result = stringToDate(&date, string);

			Assert::IsTrue(result);
			Assert::IsTrue(equalDate(date, targetDate));
		}
		TEST_METHOD(StringToDate_InvalidDay_Test) {
			Date date1;
			Date date2;
			const char* string1 = "32-5-2025";
			const char* string2 = "0-5-2025";

			bool result1 = stringToDate(&date1, string1);
			bool result2 = stringToDate(&date2, string2);

			Assert::IsFalse(result1);
			Assert::IsFalse(result2);
		}
		TEST_METHOD(StringToDate_InvalidMonth_Test) {
			Date date1;
			Date date2;
			const char* string1 = "5-13-2025";
			const char* string2 = "5-0-2025";

			bool result1 = stringToDate(&date1, string1);
			bool result2 = stringToDate(&date2, string2);

			Assert::IsFalse(result1);
			Assert::IsFalse(result2);
		}
		TEST_METHOD(StringToDate_InvalidString_Test) {
			Date date1;
			Date date2;
			Date date3;
			const char* string1 = "552025";
			const char* string2 = "5-5";
			const char* string3 = "Hi Ethan";

			bool result1 = stringToDate(&date1, string1);
			bool result2 = stringToDate(&date2, string2);
			bool result3 = stringToDate(&date3, string3);

			Assert::IsFalse(result1);
			Assert::IsFalse(result2);
			Assert::IsFalse(result3);
		}
		TEST_METHOD(StringToDate_TwoDigitYear_Test) {
			Date targetDate1 = createDate(5, 5, 2025);
			Date targetDate2 = createDate(5, 5, 1985);
			Date date1;
			Date date2;
			const char* string1 = "5-5-25";
			const char* string2 = "5-5-85";

			bool result1 = stringToDate(&date1, string1);
			bool result2 = stringToDate(&date2, string2);

			Assert::IsTrue(result1);
			Assert::IsTrue(result2);
			Assert::IsTrue(equalDate(date1, targetDate1));
			Assert::IsTrue(equalDate(date2, targetDate2));
		}
		TEST_METHOD(DateDifference_Test) {
			Date date1 = createDate(5, 5, 2024);
			Date date2 = createDate(5, 5, 2025);
			
			int result = dateDifference(date2, date1);

			Assert::AreEqual(result, 365);
		}
		TEST_METHOD(DateDifference_Negative_Test) {
			Date date1 = createDate(5, 5, 2024);
			Date date2 = createDate(5, 5, 2025);

			int result = dateDifference(date1, date2);

			Assert::AreEqual(result, -365);
		}
		TEST_METHOD(DateDifference_EmptyDate_Test) {
			Date date1 = createDateBlank();

			int result = dateDifference(date1, date1);

			Assert::AreEqual(result, INT_MIN);
		}
		TEST_METHOD(DateDifferenceAbsolute_Test) {
			Date date1 = createDate(5, 5, 2024);
			Date date2 = createDate(5, 5, 2025);

			int result = dateDifferenceAbsolute(date2, date1);

			Assert::AreEqual(result, 365);
		}
		TEST_METHOD(DateDifferenceAbsolute_Negative_Test) {
			Date date1 = createDate(5, 5, 2024);
			Date date2 = createDate(5, 5, 2025);

			int result = dateDifferenceAbsolute(date1, date2);

			Assert::AreEqual(result, 365);
		}
	};

	TEST_CLASS(TASK_TESTING) {
	public:
		TEST_METHOD(CreateTask_Test) {
			const char* testTitle = "8 million things to-do";
			Task task = createTask(testTitle);

			bool equalStatus = (task.status == UNSET_STATUS);
			bool equalPriority = (task.priority == UNSET_PRIORITY);

			Assert::IsTrue(stringCompare(task.title, testTitle));
			Assert::IsTrue(stringCompare(task.description, TASK_EMPTY_DESCRIPTION_PLACEHOLDER));
			Assert::IsTrue(equalStatus);
			Assert::IsTrue(equalPriority);
			Assert::IsTrue(equalDate(task.date, createDateBlank()));
		}

		TEST_METHOD(EqualTask_Test) {
			const char* testTitle = "Title For Task";
			Task task1 = createTask(testTitle);
			strncpy(task1.description, "TestDesc", TASK_DESCRIPTION_LENGTH);
			task1.status = COMPLETED;
			task1.priority = HIGH;
			task1.date = createDate(5, 5, 2025);

			Task task2 = createTask(testTitle);
			strncpy(task2.description, "TestDesc", TASK_DESCRIPTION_LENGTH);
			task2.date = createDate(5, 5, 2025);
			task2.status = COMPLETED;
			task2.priority = HIGH;


			bool result = equalTask(task1, task2);

			Assert::IsTrue(result);
		}
		TEST_METHOD(EqualTask_False_Test) {
			// Base task
			Task baseTask = createTask("Title1");
			strncpy(baseTask.description, "TestDesc", TASK_DESCRIPTION_LENGTH);
			baseTask.status = COMPLETED;
			baseTask.priority = HIGH;
			baseTask.date = createDate(5, 5, 2025);

			// diff title
			Task task2 = createTask("Title2");
			strncpy(task2.description, "TestDesc", TASK_DESCRIPTION_LENGTH);
			task2.status = COMPLETED;
			task2.priority = HIGH;
			task2.date = createDate(5, 5, 2025);

			bool result1 = equalTask(baseTask, task2);

			// diff status
			Task task3 = createTask("Title1");
			strncpy(task3.description, "TestDesc", TASK_DESCRIPTION_LENGTH);
			task3.status = IN_PROGRESS;
			task3.priority = HIGH;
			task3.date = createDate(5, 5, 2025);

			bool result2 = equalTask(baseTask, task3);

			// diff priority
			Task task4 = createTask("Title1");
			strncpy(task4.description, "TestDesc", TASK_DESCRIPTION_LENGTH);
			task4.status = COMPLETED;
			task4.priority = MEDIUM;
			task4.date = createDate(5, 5, 2025);

			bool result3 = equalTask(baseTask, task4);

			// diff date
			Task task5 = createTask("Title1");
			strncpy(task5.description, "TestDesc", TASK_DESCRIPTION_LENGTH);
			task5.status = COMPLETED;
			task5.priority = HIGH;
			task5.date = createDate(5, 5, 1999);

			bool result4 = equalTask(baseTask, task5);

			// diff description
			Task task6 = createTask("Title1");
			strncpy(task6.description, "Some random task desc", TASK_DESCRIPTION_LENGTH);
			task6.status = COMPLETED;
			task6.priority = HIGH;
			task6.date = createDate(5, 5, 2025);

			bool result5 = equalTask(baseTask, task6);

			Assert::IsFalse(result1);
			Assert::IsFalse(result2);
			Assert::IsFalse(result3);
			Assert::IsFalse(result4);
			Assert::IsFalse(result5);
		}

		TEST_METHOD(CopyTask_Test) {
			Task task1 = createTask("Title1");
			task1.status = COMPLETED;
			task1.priority = HIGH;
			task1.date = createDate(5, 5, 2025);

			Task copy = copyTask(task1);

			bool result = equalTask(task1, copy);

			Assert::IsTrue(result);
		}

		TEST_METHOD(CopyTaskInPlace_Test) {
			Task task1 = createTask("Title1");
			task1.status = COMPLETED;
			task1.priority = HIGH;
			task1.date = createDate(5, 5, 2025);

			Task copy;

			bool result = copyTaskInPlace(&copy, task1);

			Assert::IsTrue(result);
			Assert::IsTrue(equalTask(task1, copy));
		}
		TEST_METHOD(CopyTaskInPlace_NULL_Test) {
			Task task1 = createTask("Title1");

			bool result = copyTaskInPlace(NULL, task1);

			Assert::IsFalse(result);
		}

		TEST_METHOD(SetTitle_Test) {
			Task task1 = createTask("Title1");

			bool result = setTitle(&task1, "NewTitle");

			Assert::IsTrue(result);
			Assert::AreEqual(task1.title, "NewTitle");
		}
		TEST_METHOD(SetTitle_NULL_Test) {
			Task task1 = createTask("Title1");

			bool result1 = setTitle(NULL, "NewTitle");
			bool result2 = setTitle(&task1, NULL);

			Assert::IsFalse(result1);
			Assert::IsFalse(result2);
		}

		TEST_METHOD(SetDesc_Test) {
			Task task1 = createTask("Title1");
			strncpy(task1.description, "TestDesc", TASK_DESCRIPTION_LENGTH);
			task1.status = COMPLETED;
			task1.priority = HIGH;
			task1.date = createDate(5, 5, 2025);

			bool result = setDescription(&task1, "NewDesc");

			Assert::IsTrue(result);
			Assert::AreEqual(task1.description, "NewDesc");
		}
		TEST_METHOD(SetDesc_NULL_Test) {
			Task task1 = createTask("Title1");
			strncpy(task1.description, "TestDesc", TASK_DESCRIPTION_LENGTH);

			bool result1 = setDescription(NULL, "NewDesc");
			bool result2 = setDescription(&task1, NULL);

			Assert::IsFalse(result1);
			Assert::IsFalse(result2);
		}

		TEST_METHOD(SetPriority_Test) {
			Priority newPriority = MEDIUM;

			Task task1 = createTask("Title1");
			task1.priority = HIGH;

			bool result = setPriority(&task1, newPriority);

			bool equal = (task1.priority == newPriority);

			Assert::IsTrue(result);
			Assert::IsTrue(equal);
		}
		TEST_METHOD(SetPriority_NULL_Test) {
			bool result = setPriority(NULL, MEDIUM);

			Assert::IsFalse(result);
		}

		TEST_METHOD(SetStatus_Test) {
			Status newStatus = IN_PROGRESS;

			Task task1 = createTask("Title1");
			task1.status = BLOCKED;

			bool result = setStatus(&task1, newStatus);

			bool equal = (task1.status == newStatus);

			Assert::IsTrue(result);
			Assert::IsTrue(equal);
		}
		TEST_METHOD(SetStatus_NULL_Test) {
			bool result = setStatus(NULL, IN_PROGRESS);

			Assert::IsFalse(result);
		}

		TEST_METHOD(SetDate_Test) {
			Date newDate = createDate(1, 1, 2111);

			Task task = createTask("Test");
			task.date = createDate(5, 5, 2025);

			bool result = setDate(&task, newDate);

			Assert::IsTrue(result);
			Assert::IsTrue(equalDate(task.date, newDate));
		}
		TEST_METHOD(SetDate_NULL_Test) {
			bool result = setDate(NULL, createDate(5, 5, 2025));

			Assert::IsFalse(result);
		}
	};

	TEST_CLASS(USER_TESTING) {
	public:
		TEST_METHOD(CreateUser_Test) {
			User user = createUser("Colin", "1234");

			Assert::IsTrue(stringCompare(user.username, "Colin"));
			Assert::IsTrue(stringCompare(user.passward, "1234"));
		}
	};


	TEST_CLASS(LIST_TESTING) {
	public:
		TEST_METHOD(CreateList_Test) {
			List* list = createList();

			Assert::IsNotNull(list);
			Assert::AreEqual(list->capacity, (size_t)10);
		}

		TEST_METHOD(CopyList_Test) {
			Task t1 = createTask("Test1");
			Task t2 = createTask("Test2");
			Task t3 = createTask("Test3");

			List* list = createList();
			append(list, t1);
			append(list, t2);
			append(list, t3);

			List* copy = copyList(list);

			Assert::IsNotNull(copy);
			Assert::IsTrue(equalList(list, copy));
			Assert::AreEqual(list->capacity, copy->capacity);
			Assert::AreEqual(list->size, copy->size);
		}
		TEST_METHOD(CopyList_NULL_Test) {
			List* copy = copyList(NULL);

			Assert::IsNull(copy);
		}
		TEST_METHOD(EqualList_Test) {
			Task t1 = createTask("Test1");
			Task t2 = createTask("Test2");
			Task t3 = createTask("Test3");

			List* list1 = createList();
			append(list1, t1);
			append(list1, t2);
			append(list1, t3);

			List* list2 = createList();
			append(list2, t1);
			append(list2, t2);
			append(list2, t3);

			Assert::IsTrue(equalList(list1, list2));
		}
		TEST_METHOD(EqualList_EqualItems_Test) {
			Task t1 = createTask("Test1");
			Task t2 = createTask("Test2");
			Task t3 = createTask("Test3");

			List* list1 = createList();
			append(list1, t1);
			append(list1, t2);
			append(list1, t3);

			List* list2 = createList();
			append(list2, t1);
			append(list2, t2);
			list2->size = 3; // spoofing size

			Assert::IsFalse(equalList(list1, list2));
		}
		TEST_METHOD(EqualList_NonEqual_Test) {
			Task t1 = createTask("Test1");
			Task t2 = createTask("Test2");
			Task t3 = createTask("Test3");
			Task t4 = createTask("Test4");

			List* list1 = createList();
			append(list1, t1);
			append(list1, t2);
			append(list1, t3);

			List* list2 = createList();
			append(list2, t1);
			append(list2, t2);
			append(list2, t3);
			append(list2, t4);

			Assert::IsFalse(equalList(list1, list2));
		}
		TEST_METHOD(EqualList_WrongOrder_Test) {
			Task t1 = createTask("Test1");
			Task t2 = createTask("Test2");
			Task t3 = createTask("Test3");

			List* list1 = createList();
			append(list1, t1);
			append(list1, t2);
			append(list1, t3);

			List* list2 = createList();
			append(list2, t2);
			append(list2, t3);
			append(list2, t1);

			Assert::IsFalse(equalList(list1, list2));
		}
		TEST_METHOD(EqualList_NULL_Test) {
			List* list = createList();

			bool result1 = equalList(NULL, list);
			bool result2 = equalList(list, NULL);

			Assert::IsFalse(result1);
			Assert::IsFalse(result2);
		}


		TEST_METHOD(Append_Test) {
			Task t1 = createTask("Test1");
			Task t2 = createTask("Test2");
			Task t3 = createTask("Test3");

			List* list = createList();
			append(list, t1);
			append(list, t2);
			append(list, t3);

			Assert::AreEqual(list->size, (size_t)3);
			Assert::IsTrue(equalTask(list->arr[0], t1));
			Assert::IsTrue(equalTask(list->arr[1], t2));
			Assert::IsTrue(equalTask(list->arr[2], t3));
		}
		TEST_METHOD(Append_Resize_Test) {
			Task t1 = createTask("Test1");

			List* list = createList();

			for (int i = 0; i < 15; i++) {
				append(list, t1);
			}

			Assert::AreEqual(list->size, (size_t)15);
		}
		TEST_METHOD(Append_NULL_Test) {
			Task task = createTask("Test");

			bool result = append(NULL, task);

			Assert::IsFalse(result);
		}

		TEST_METHOD(Insert_Test) {
			Task t1 = createTask("Test1");
			Task t2 = createTask("Test2");
			Task t3 = createTask("Test3");
			Task t4 = createTask("Task4");

			List* list = createList();
			append(list, t1);
			append(list, t2);
			append(list, t3);

			bool result = insert(list, 1, t4);

			for (int i = 0; i < list->size; i++) {
				fprintf(stderr, "%s", list->arr[i].title);
			}

			Assert::AreEqual(list->size, (size_t)4);
			Assert::IsTrue(equalTask(list->arr[0], t1));
			Assert::IsTrue(equalTask(list->arr[1], t4));
			Assert::IsTrue(equalTask(list->arr[2], t2));
			Assert::IsTrue(equalTask(list->arr[3], t3));
		}
		TEST_METHOD(Insert_NULL_Test) {
			Task t1 = createTask("Test1");

			bool result = insert(NULL, 1, t1);

			Assert::IsFalse(result);
		}
		TEST_METHOD(Insert_InvalidIndex_Test) {
			Task t1 = createTask("Test1");

			List* list = createList();

			bool result = insert(list, 5, t1);

			Assert::IsFalse(result);
		}

		TEST_METHOD(RemoveTask_Test) {
			Task t1 = createTask("Test1");
			Task t2 = createTask("Test2");
			Task t3 = createTask("Test3");

			List* list = createList();
			append(list, t1);
			append(list, t2);
			append(list, t3);

			Assert::AreEqual(list->size, (size_t)3);

			bool result = removeTask(list, t2);

			Assert::IsTrue(result);
			Assert::AreEqual(list->size, (size_t)2);
			Assert::IsTrue(equalTask(list->arr[0], t1));
			Assert::IsTrue(equalTask(list->arr[1], t3));
		}
		TEST_METHOD(RemoveTask_NULL_Test) {
			Task t1 = createTask("Test1");

			bool result = removeTask(NULL, t1);

			Assert::IsFalse(result);
		}
		TEST_METHOD(RemoveTask_NotInList_Test) {
			Task t1 = createTask("Test1");
			Task t2 = createTask("Test2");
			Task t3 = createTask("Test3");
			Task t4 = createTask("Test4");

			List* list = createList();
			append(list, t1);
			append(list, t2);
			append(list, t3);

			bool result = removeTask(list, t4);

			Assert::IsFalse(result);
		}

		TEST_METHOD(Pop_Test) {
			Task t1 = createTask("Test1");
			Task t2 = createTask("Test2");
			Task t3 = createTask("Test3");

			List* list = createList();
			append(list, t1);
			append(list, t2);
			append(list, t3);

			Assert::AreEqual(list->size, (size_t)3);

			bool result = pop(list, 1);

			Assert::IsTrue(result);
			Assert::AreEqual(list->size, (size_t)2);
			Assert::IsTrue(equalTask(list->arr[0], t1));
			Assert::IsTrue(equalTask(list->arr[1], t3));
		}
		TEST_METHOD(Pop_NULL_Test) {
			bool result = pop(NULL, 0);

			Assert::IsFalse(result);
		}
		TEST_METHOD(Pop_InvalidIndex_Test) {
			Task t1 = createTask("Test1");
			Task t2 = createTask("Test2");
			Task t3 = createTask("Test3");

			List* list = createList();
			append(list, t1);
			append(list, t2);
			append(list, t3);

			bool result = pop(NULL, 6);

			Assert::IsFalse(result);
		}

		TEST_METHOD(Clear_Test) {
			Task t1 = createTask("Test1");
			Task t2 = createTask("Test2");
			Task t3 = createTask("Test3");

			List* list = createList();
			append(list, t1);
			append(list, t2);
			append(list, t3);

			bool result = clear(list);

			Assert::IsTrue(result);
			Assert::IsNotNull(list);
			Assert::AreEqual(list->size, (size_t)0);
		}
		TEST_METHOD(Clear_Test) {
			Task t1 = createTask("Test1");
			Task t2 = createTask("Test2");
			Task t3 = createTask("Test3");

			List* list = createList();
			append(list, t1);
			append(list, t2);
			append(list, t3);

			bool result = clear(list);

			Assert::IsTrue(result);
			Assert::IsNotNull(list);
			Assert::AreEqual(list->size, (size_t)0);
		}
	};
}
