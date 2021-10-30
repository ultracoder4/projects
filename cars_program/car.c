#include "car.h"


static car *db[MAX_CARS]; // Internal representation of the database.
static int num_cars = 0; // Number of cars in db


/*
 * function to read in file name
 * returns 0 on success, -1 on error
*/
int initialize_db(char *filename){
	FILE *fin = fopen(filename, "r");
	if(fin==NULL){
 		return -1; 
	}
	/* static car* db is the internal representation of the database so read the file and
	store the cars in that variable */
    	//file format: carnum year make category miles cost

	// read up to the maximum amount of cars
	// read until there's no more cars to read in the file
	int i;
	for(i=0;i<MAX_CARS;i++){
		// make a new car
		car* newCar = malloc(sizeof(car));;

		// declare variables to read for readability
		int carnum, year, miles, cost;
    		char make1[50];
    		char categoryVal[50];

		// scan the next car and update the new car
		int result = fscanf(fin, "%d %d %49s %49s %d %d", &carnum, &year, make1, categoryVal, &miles, &cost); 
		if(result==EOF){
			// if we're at the end of the file break the loop ex. only read a file with 20 cars
			break;
		}

		// update values on new car
		newCar->carnum=carnum;
		newCar->year = year;
		strcpy(newCar->make, make1);
		// category must be translated from string to int
		char* categories[] = {"sedan", "suv", "truck", "hybrid"};
		int j;
		for(j=0;j<4;j++){
			if(strcmp(categories[j], categoryVal)==0){
//printf("categoryVal that matched: %s\n", categoryVal);
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
				newCar->category = categoryForCar;
//printf("newCar->carnum: %d\n", newCar->carnum);
//printf("newCar->category: %d\n", (newCar->category) );
			}
		}
		newCar->miles = miles;
		newCar->cost = cost;


		// set address of newest car (add it to the db)
		db[i]=newCar;

		// increment count
		num_cars++;

/*		// print db array
		int p;
		for(p=0;p<num_cars;p++){
			printf("\nindex: %d, address: %d, make: %s", p, db[p], db[p]->make);
		}
		printf("\n");
*/

	} // end for loop


    fclose(fin);
    return 0;
}

/*
Write db to filename. Returns 0 on success and -1 on error
*/
int write_db(char *filename){
	FILE *fout = fopen(filename, "w+");
	if(fout==NULL){
 		return -1; // failure
	}

	int i;
	for(i=0;i<num_cars;i++){
		// print each car
		// print first three values
		fprintf(fout, "%d %d %s ", db[i]->carnum, db[i]->year, db[i]->make);
		// print category
		// translate from category int to string
		char* categories[] = {"sedan", "suv", "truck", "hybrid"};
		char* categoryString = categories[db[i]->category];
		fprintf(fout, "%s ", categoryString);
		// print last two values
		fprintf(fout, "%d %d", db[i]->miles, db[i]->cost);
		// print newline only if it's not the last line
		if(i!=(num_cars-1)){ fprintf(fout, "\n");}
	} // end for loop
	
	fclose(fout);
	return 0;	   // success
}

/*
displays cars in db on stdout
*/
void show_cars(){
	int p;
    	for(p=0;p<num_cars;p++){

	// translate from category int to string
	char* categories[] = {"sedan", "suv", "truck", "hybrid"};
	char* categoryString = categories[db[p]->category];

           fprintf(stdout,"carnum: %d, year: %d, make: %s, category: %s, miles: %d, cost: %d\n", db[p]->carnum, db[p]->year, db[p]->make, categoryString, db[p]->miles, db[p]->cost);
	}
}

/*
displays c on stdout.
*/
void print_car(car *c){
	// file format: carnum year make category miles cost
	// translate from category int to string
	char* categories[] = {"sedan", "suv", "truck", "hybrid"};
	char* categoryString = categories[c->category];

	fprintf(stdout, "car number: %d, year: %d, make: %s, category: %s, miles: %d, cost: %d\n",
		c->carnum, c->year, c->make, categoryString, c->miles, c->cost);
}

/* returns car* with carnum in db, returns NULL if carnum is not in db */
car *find_car(int carnum){
	int i;
	for(i=0;i<num_cars;i++){
		if(db[i]->carnum==carnum){
			return db[i];
		}
	}
	// no cars matched so return null
	return NULL;
}

/*
Adds a new car to db. Returns car* of the car added. Returns 0 if carnum is already in the db
*/
car *add_car(int carnum, int year,char* make, category category, int miles, int cost){
	// check if the car is already in the list, if it is return 0
	if(find_car(carnum)!=NULL){
		return 0;
	}
	// it's not in the database, so add the car
	// if there's room in the array, add the car
	if(num_cars<MAX_CARS){
		car* newCar = malloc(sizeof(car));

		// set values
		newCar->carnum=carnum;
		newCar->year=year;
		strcpy(newCar->make, make);
		newCar->category=category;
		newCar->miles=miles;
		newCar->cost=cost;
		// add the car
		db[num_cars]=newCar;
		// increment counter
		num_cars++;
		// return pointer to car added
		return newCar;
	} else{
		// not enough room
		printf("not enough room to add another car");
		return 0;
	}
}

/*
Updates cost of carnum in db. Returns car* with carnum. Returns NULL if carnum is not in db.
*/
car *update_cost(int carnum, int cost){
	car* c=find_car(carnum);
	if(c==NULL){
		return NULL;
	}

	// it was found so update the cost
	c->cost=cost;

	return c;
}

/*
Updates miles of carnum in db. Returns car* with carnum. Returns NULL if carnum is not in db
*/
car *update_miles(int carnum, int miles){
	car* c=find_car(carnum);
	if(c==NULL){
		return NULL;
	}

	// it was found so update the miles
	c->miles=miles;

	return c;
}

/*
Fills in cars with an array of car pointers for all cars in db with year > year. Returns number of 
cars in cars. User argument must be the address of car cars[MAX_CARS] to receive the array.
*/
int get_year(car **cars, int year){
	// cars is an array of car pointers
	int count=0;
	// search the db for appropriate cars
	int i;
	for(i=0;i<num_cars;i++){
		// fill the cars array with appropriate cars
		if( (db[i]->year) > year){
			// add pointer to the array
			cars[count]=db[i];
			count++;
		}
	}

	return count;
}

/*
Fills in cars with an array of car pointers for all cars in db with cost < cost. Returns number of cars in cars. 
User argument must be the address of car cars[MAX_CARS] to receive the array.
*/
int get_cost(car **cars, int cost){
	// cars is an array of car pointers
	int count=0;
	// search the db for appropriate cars
	int i;
	for(i=0;i<num_cars;i++){
		// fill the cars array with appropriate cars
		if( (db[i]->cost) < cost){
			// add pointer to the array
			cars[count]=db[i];
			count++;
		}
	}

	return count;
}

/*
Fills in cars with an array of car pointers for all cars in db with category == c. Returns number of cars in
cars. User argument must be the address of car cars[MAX_CARS] to receive the array
*/
int get_category(car **cars, category c){

	// cars is an array of car pointers
	int count=0;
	// search the db for appropriate cars
	int i;
	for(i=0;i<num_cars;i++){
		// fill the cars array with appropriate cars
		// if category matches, add it to the list
		if( (db[i]->category) == c ){
			// add pointer to the array
			cars[count]=db[i];
			count++;
		}
	}

	return count;
}

/*
Fills in cars with an array of car pointers for all cars in db where the string in make matches the string in the car
entry. Returns number of cars in cars. User argument must be the address of car cars[MAX_CARS] to receive the array.
*/
int get_make(car **cars, char *make){
	// cars is an array of car pointers
	int count=0;
	// search the db for appropriate cars
	int i;
	for(i=0;i<num_cars;i++){
		// fill the cars array with appropriate cars
		if( strcmp( (db[i]->make),make) == 0 ){
			// add pointer to the array
			cars[count]=db[i];
			count++;
		}
	}

	return count;
}

/*
Purchases carnum. Removes the car from db. Returns car* with carnum. Returns NULL if carnum is not in db.
*/
car *purchase(int carnum){
	car* p= find_car(carnum);
	if(p==NULL) return NULL;

	// the car is in db, so remove it; p is the element we want to remove
	// db can have one element
	if(num_cars==1){
		db[0]=0;
		num_cars--;
		return p;
	}
	// db can have many elements
	// remove at end
	if(p==db[num_cars-1]){
		db[num_cars-1]=0;
		num_cars--;
		return p;
	}
	// remove at beginning of array
	else if(p==db[0]){
		swap( &(db[0]), &(db[num_cars-1]) );
		db[num_cars-1]=0;
		num_cars--;
		return p;
	}
	// remove in middle
	else{
		int pos;
		int j;
		for(j=0;j<num_cars;j++){
			if(p==db[j]){
			pos=j;
			}
		}
		swap( &(db[pos]), &(db[num_cars-1]) );
		db[num_cars-1]=0;
		num_cars--;
printf("num_cars: %d\n", num_cars);
		return p;
	}
}
// helper method for purchase
/*
* swaps car pointers; arguments are the addresses of two car pointers
*/
void swap(car** x, car** y){
	car* z= *x;
	*x=*y;
	*y=z;
}