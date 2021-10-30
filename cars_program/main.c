#include "car.h"

void handleCommands(char cmd, char* userType);


int main(int argc, char* argv[]) {
	// initialize db
	/* end the program if there are no arguments or too many arguments */
	if(argc!=2){
		printf("File not found!");
		exit(EXIT_FAILURE);
	}

	if(initialize_db(argv[1])==-1){
		printf("File not found!");
		exit(EXIT_FAILURE);
	}

	// printf("\ninitialize_db() passed");


	char userType[50];
	char response[50];

	//prompt user for username
	printf("Enter user name: ");
	scanf("%49s", response);

	if(strcmp(response, "owner")==0 || strcmp(response, "shopper")==0){
		// set user type
		strcpy(userType, response);
	} else{
		printf("Invalid user!");
		exit(EXIT_FAILURE);
	}

	// prompt user based on user type
	while(1){
			if(strcmp(userType, "owner")==0){
				printf("\nowner options: a: list, b: add car, c: delete car, d: update cost, e: update miles, f: save, g: quit");
			}
			// print normal options
			printf("\noptions: h: show year, i: show make, j: show cost, k: show category, l: purchase car, m: exit");

			printf("\nEnter a command: ");
			scanf("%49s", response);
			printf("\n");

			// handle command
			char cmd=response[0];
			handleCommands(cmd, userType);
	}





/*
// the following TESTS are for the file file.txt

// test show_cars()
show_cars();
printf("show_cars() passed\n");

// test print_car()
car testCar;
testCar.carnum=99;
testCar.year=1999;
strcpy(testCar.make, "Ferrari");
testCar.category= (category) "sedan";
testCar.miles=100;
testCar.cost=999999;
print_car(&testCar);
printf("print_car() passed\n");

int testNumExists=10;
int testNumDoesNotExist=999;
int value;
if(find_car(testNumExists)!=NULL){
	printf("find_car() that exists passes\n");
}
if(find_car(testNumDoesNotExist)==NULL){
	printf("find_car() that doesn't exist passes\n");
}

car* carWeHave=add_car(4, 2004, "Kia", (category)truck, 1689, 8000);
if(carWeHave==0){
	printf("add_car() for a car already in db passes\n");
	free(carWeHave);
}
car* carWeDoNotHave=add_car(21, 2001, "Mitsubishi", (category)sedan, 900, 15000);
if(carWeDoNotHave!=NULL){
	printf("new car's make: %s\n", carWeDoNotHave->make);
	printf("add_car() for a car not already in db passes\n");
	free(carWeDoNotHave);
}

car* c1=update_cost(950, 1000);
if(c1==NULL){
	printf("update_cost() for a car not in db passes\n");
}
car* c2=update_cost(2, 1000);
if(c2->cost==1000){
	printf("car #2's new cost value: %d\n", c2->cost);
	printf("update_cost() for a car that is in db passes\n");
}
car* c3=update_miles(950, 1000);
if(c3==NULL){
	printf("update_miles() for a car not in db passes\n");
}
car* c4=update_miles(2, 100000);
if(c4->miles==100000){
	printf("car #2's new miles value: %d\n", c4->miles);
	printf("update_miles() for a car that is in db passes\n");
}
// test get_year()
car* test_cars[MAX_CARS];
int ct=get_year(test_cars, 2019);
if(ct==2){
	printf("cars found in test_cars[]:\n");
	int j;
	for(j=0;j<ct;j++){
		print_car(test_cars[j]);
	}
	printf("value of ct: %d\n", ct);
	printf("get_year() passes\n");
}

// test get_cost()
car* test_cars_cost[MAX_CARS];
int ct_cost=get_cost(test_cars_cost, 1100);
if(ct_cost==2){
	printf("cars found in test_cars_cost[]:\n");
	int j;
	for(j=0;j<ct_cost;j++){
		print_car(test_cars_cost[j]);
	}
	printf("value of ct_cost: %d\n", ct_cost);
	printf("get_cost() passes\n");
}

// test get_category()
car* test_cars_3[MAX_CARS];
int ct_3=get_category(test_cars_3, (category)truck);
if(ct_3==5){
	printf("cars found in test_cars_3[]:\n");
	int j;
	for(j=0;j<ct_3;j++){
		print_car(test_cars_3[j]);
	}
	printf("value of ct_3: %d\n", ct_3);
	printf("get_category() passes\n");
}

// test get_make()
car* test_cars_4[MAX_CARS];
int ct_4=get_make(test_cars_4, "BMW");
if(ct_4==3){
	printf("cars found in test_cars_4[]:\n");
	int j;
	for(j=0;j<ct_4;j++){
		print_car(test_cars_4[j]);
	}
	printf("value of ct_4: %d\n", ct_4);
	printf("get_make() passes\n");
}

// test purchase
// test purchasing car that is not in db
car* result=purchase(950);
if(result==NULL){
	printf("purchase() for a car that is not in db passes\n");
}

// test swap
car car1;
car car2;
car car3;
car* car_array[3]={&car1, &car2, &car3};
printf("before swapping 2nd and 3rd elements:\n");
printf("array: {%d, %d, %d}\n", car_array[0], car_array[1], car_array[2]); 
swap(&car_array[1], &car_array[2]);
printf("after swapping 2nd and 3rd elements:\n");
printf("array: {%d, %d, %d}\n", car_array[0], car_array[1], car_array[2]); 

// test purchasing a car that is in db
printf("before purchases for cars in db:\n");
show_cars();
//test purchase car at end of db array
purchase(21);
printf("after purchase car at end of db array:\n");
show_cars();
purchase(1);
printf("after purchase car at beginning of db array:\n");
show_cars();
purchase(10);
printf("after purchase car in middle of db array:\n");
show_cars();
car* test_car_removed=purchase(18);
printf("carnum of car removed: %d\n", test_car_removed->carnum);
if(test_car_removed->carnum==18){
	printf("purchase() passes\n");
}

*/

return 0;
}

// helper methods
void handleCommands(char cmd, char* userType){
			// options: h: show year, i: show make, j: show cost, k: show category, l: purchase car, m: exit
			if(cmd=='h'){
				// show year
				int year;
				car* newerCars[MAX_CARS];
				printf("Show cars newer than specified year:");
				printf("\nEnter year: ");
				scanf("%d", &year);

				int ct=get_year(newerCars, year);
				if(ct==0){
					printf("No cars newer than year!\n");
				} else{
					// print all the cars newer than specified year
					int j;
					for(j=0;j<ct;j++){
						print_car(newerCars[j]);
					}
				}
			} else if(cmd=='i'){
				// show make
				char make[MAX_MAKE_CHARS];	
				car* make_cars[MAX_CARS];

				printf("Show all cars of type make:");
				printf("\nEnter make: ");
				scanf("%31s", make);

				int ct=get_make(make_cars, make);
				if(ct==0){
					printf("No cars of make!\n");
				} else{
					// print all the cars of specified make
					int j;
					for(j=0;j<ct;j++){
						print_car(make_cars[j]);
					}
				}
			}else if(cmd=='j'){
				// show cost
				int cost;
				car* make_cars[MAX_CARS];
				printf("Shows all cars that cost less than cost:");
				printf("\nEnter cost: ");
				scanf("%d", &cost);

				int ct=get_cost(make_cars, cost);
				if(ct==0){
					printf("No cars less than cost!\n");
				} else{
					// print all the cars of specified cost
					int j;
					for(j=0;j<ct;j++){
						print_car(make_cars[j]);
					}
				}
			}else if(cmd=='k'){
				// show category
				char categoryVal[MAX_MAKE_CHARS];
				category cat;
				car* make_cars[MAX_CARS];
				printf("Show all cars of specified category:");
				printf("\nEnter category: ");
				scanf("%31s", categoryVal);
				
				// translate from string to category
				char* categories[] = {"sedan", "suv", "truck", "hybrid"};
				int j;
				for(j=0;j<4;j++){
					if(strcmp(categories[j], categoryVal)==0){
						// translate from string to category
						category categoryForCar;
						if(strcmp(categoryVal, "sedan")==0){
							categoryForCar = sedan;
						} else if(strcmp(categoryVal, "suv")==0){
							categoryForCar = suv;
						} else if(strcmp(categoryVal, "truck")==0){
							categoryForCar = truck;
						} else if(strcmp(categoryVal, "hybrid")==0){
							categoryForCar = hybrid;
						}
					// assign enum value
					cat = categoryForCar;
					}
				}

				int ct=get_category(make_cars, cat);
				if(ct==0){
					printf("No cars of category!\n");
				} else{
					// print all the cars of specified category
					int j;
					for(j=0;j<ct;j++){
						print_car(make_cars[j]);
					}
				}
			}else if(cmd=='l'){
				// purchase
				int carnum;
				printf("Purchase the car with specified carnum:");
				printf("\nEnter carnum: ");
				scanf("%d", &carnum);

				car* result=purchase(carnum);
				if(result==NULL){
					printf("Invalid carnum!\n");
				} else{
					printf("car successfully purchased..");
				}
			}else if(cmd=='m'){
				// exit

				// save changes to db
				printf("saving program..\n");
				// save changes to database
				// write db to file
				if(write_db("fileout.txt")==-1){
					printf("Error writing db!");
					exit(EXIT_FAILURE);
				}
				printf("saving complete..\n");

				// exit the program
				printf("exiting program.. good bye!\n");
				exit(EXIT_SUCCESS);
			}else if(cmd=='a' && (strcmp(userType, "owner")==0)){
				show_cars();
			}else if(cmd=='b' && (strcmp(userType, "owner")==0)){
				// add car
				int carnum, year, miles, cost;
				char make[MAX_MAKE_CHARS];
				char categoryVal[MAX_MAKE_CHARS];
				category cat;
				
				printf("Add Car:");
				printf("\nEnter carnum: ");
				scanf("%d", &carnum);
				printf("\nEnter year: ");
				scanf("%d", &year);
				printf("\nEnter make: ");
				scanf("%s", make);
				printf("\nEnter category: ");
				scanf("%31s", categoryVal);

				// translate string to category
				char* categories[] = {"sedan", "suv", "truck", "hybrid"};
				category categoryForCar;
				if(strcmp(categoryVal, "sedan")==0){
					categoryForCar = sedan;
				} else if(strcmp(categoryVal, "suv")==0){
					categoryForCar = suv;
				} else if(strcmp(categoryVal, "truck")==0){
					categoryForCar = truck;
				} else if(strcmp(categoryVal, "hybrid")==0){
					categoryForCar = hybrid;
				}
				// assign enum value
				cat = categoryForCar;

				printf("\nEnter miles: ");
				scanf("%d", &miles);
				printf("\nEnter cost: ");
				scanf("%d", &cost);

				car* result = add_car(carnum, year, make, cat, miles, cost);
				if(result == 0) {
					printf("invalid add command!\n");
				} else{
					printf("car added successfully!\n");
				}

			}else if(cmd=='c' && (strcmp(userType, "owner")==0)){
				// delete car
				int carnum;

				printf("Delete Car:");
				printf("\nEnter carnum: ");
				scanf("%d", &carnum);

				car* result = purchase(carnum);
				if(result == NULL) {
					printf("invalid carnum!\n");
				} else{
					printf("car removed successfully!\n");
				}

			}else if(cmd=='d' && (strcmp(userType, "owner")==0)){
				// update cost
				int carnum;

				printf("Update Cost:");
				printf("\nEnter carnum: ");
				scanf("%d", &carnum);

				// check if car exists
				car* c=find_car(carnum);
				if(c==NULL){
					printf("invalid carnum!\n");
				} else{
					// get new cost
					int newCost;
					printf("\nEnter new cost: ");
					scanf("%d", &newCost);
						
					if(newCost < 1){
						printf("cost must be positive integer!\n");
					} else{
						// update the car
						car* result = update_cost(carnum, newCost);
						printf("cost updated successfully!\n");
					}		
				}
			}else if(cmd=='e' && (strcmp(userType, "owner")==0)){
				// update miles
				int carnum;

				printf("Update Miles:");
				printf("\nEnter carnum: ");
				scanf("%d", &carnum);

				// check if car exists
				car* c=find_car(carnum);
				if(c==NULL){
					printf("invalid carnum!\n");
				} else{
					// get new miles
					int newMiles;
					printf("\nEnter new Miles: ");
					scanf("%d", &newMiles);
						
					if(newMiles < 1){
						printf("miles must be positive integer!\n");
					} else{
						// update the car
						car* result = update_miles(carnum, newMiles);
						printf("miles updated successfully!\n");
					}		
				}
			}else if(cmd=='f' && (strcmp(userType, "owner")==0)){
				printf("saving program..\n");
				// save changes to database
				// write db to file
				if(write_db("fileout.txt")==-1){
					printf("Error writing db!");
					exit(EXIT_FAILURE);
				}
				printf("saving complete..\n");
			}else if(cmd=='g' && (strcmp(userType, "owner")==0)){
				printf("quitting program.. good bye!\n");
				exit(EXIT_SUCCESS);
			} else{
				printf("Invalid command!\n");
			}

}
