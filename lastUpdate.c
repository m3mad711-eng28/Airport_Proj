#include<stdio.h>
#define MAX_USERS 100 // Maximum number of users allowed
#define MAX_FLIGHTS 10 // Maximum number of flights allowed
#define MAX_PASSANGERS 100 // Maximum number of passengers per flight
short userCount = 0; // Global Counter to track the number of users
short flightCounter = 0; // Global Counter to track the number of flights
short SuccSignUp = 0; // Flag to track successful user signup, will be used in redirecting 

void LogInOrSignUpCheck();
void AddNewFlightSchedule();
void DeleteExistingFlightSchedule();
void ShowUserFlights(short userID);
void FlightManagementAdmin();
void FlightManagementUser();
void SignUpUser();
void LogInUser();
void CancelReservation(short userID);
void AddNewReservation(short userID);

struct Passenger{ // Structure to store passenger details
    char name[50];
    short ID;
    long long PhoneNumber;
    int TripsCounter;
} passengers[MAX_USERS]; // To store more than user at the same time

struct Flights{ // Structure to store flight detail
    int FlightNumber;
    short AvaliableTickets;
    char ArrivalGate[20];
    char DepatureGate[20];
    float Depatureime;
    float ArrivalTime;
    short flightDay;
    short flightMonth;
} flights[MAX_FLIGHTS];  // To store more than flight at the same time

int main(){
    passengers[userCount].TripsCounter = 0; // To be used in reservation log
    LogInOrSignUpCheck();
    return 0;
}

void LogInOrSignUpCheck(){ // Function to check whether the user is an Admin or a Passenger
    short UserOrAdmin;
    do{
        printf("Enter 1 for Admins, 2 for Users: ");
        scanf("%hd", &UserOrAdmin);
    }while(UserOrAdmin != 1 && UserOrAdmin != 2); // Infinity loop until a valid input is given
    
    if(UserOrAdmin == 1){
        printf("Admin mode started..\n");
        FlightManagementAdmin();  // Redirect to Admin functionalities
    }else{
        printf("User mode started..\n");
        FlightManagementUser();  // // Redirect to user functionalities
    }
}

/************************ Admin ************************/

void FlightManagementAdmin(){ // Function to control Admin operations
    short SelectAdmin;
    do{
        printf("Enter 1 to add new flight schedule, 2 to Delete existing flight schedule, 3 to go back, 4 to exit: ");
        scanf("%hd", &SelectAdmin);
        
        switch(SelectAdmin){
            case 1: AddNewFlightSchedule(); // Add new flight method
                    break;
            case 2: DeleteExistingFlightSchedule();  // Delete existing flight
                    break;
            case 3: LogInOrSignUpCheck(); // To go back to main menu
                    break;
            case 4: printf("Exiting Admin mode.\n"); // To exit the program
                    break;
            default: printf("Invalid input!!..Try again.\n");
        }
    }while(SelectAdmin != 4); // If 4 it exits
}

void AddNewFlightSchedule(){ // Function to add a new flight schedule as admin
    if(flightCounter < MAX_FLIGHTS){
        printf("Enter departure gate: ");
        scanf("%s", flights[flightCounter].DepatureGate);
        printf("Enter arrival gate: ");
        scanf("%s", flights[flightCounter].ArrivalGate);

        do{
            printf("Enter departure time (00.00 - 23.59): ");
            scanf("%f", &flights[flightCounter].Depatureime);
        }while(flights[flightCounter].Depatureime < 0 || flights[flightCounter].Depatureime > 23.59);  // Infinity loop until a valid input is given

        do{
            printf("Enter arrival time (00.00 - 23.59): ");
            scanf("%f", &flights[flightCounter].ArrivalTime);
        }while(flights[flightCounter].ArrivalTime < 0 || flights[flightCounter].ArrivalTime > 23.59); // Infinity loop until a valid input is given
        
        printf("Enter flight number: ");
        scanf("%d", &flights[flightCounter].FlightNumber);
        
        do{
            printf("Enter flight day (1 - 31): ");
            scanf("%hd", &flights[flightCounter].flightDay);
        }while(flights[flightCounter].flightDay < 1 || flights[flightCounter].flightDay > 31); // Infinity loop until a valid input is given
        
        do{
            printf("Enter flight month (1 - 12): ");
            scanf("%hd", &flights[flightCounter].flightMonth);
        }while(flights[flightCounter].flightMonth < 1 || flights[flightCounter].flightMonth > 12); // Infinity loop until a valid input is given
        
        do{
            printf("Enter number of available seats (max 100): ");
            scanf("%hd", &flights[flightCounter].AvaliableTickets);
        }while(flights[flightCounter].AvaliableTickets > 100); // MAX_USERS 100, Infinity loop until a valid input is given

        flightCounter++;
        printf("Flight added successfully!\n");
    }else{
        printf("Flight limit reached!\n"); // Actual fligths counter 10
    }
}

void DeleteExistingFlightSchedule(){
    struct Flights tempFlight; // 2nd object to store in to compare with the 1st
    printf("Enter full flight details to delete:\n");
    printf("Enter flight number: ");
    scanf("%d", &tempFlight.FlightNumber);
    printf("Enter departure gate: ");
    scanf("%s", tempFlight.DepatureGate);
    printf("Enter arrival gate: ");
    scanf("%s", tempFlight.ArrivalGate);
    printf("Enter departure time: ");
    scanf("%f", &tempFlight.Depatureime);
    printf("Enter arrival time: ");
    scanf("%f", &tempFlight.ArrivalTime);
    printf("Enter flight day: ");
    scanf("%hd", &tempFlight.flightDay);
    printf("Enter flight month: ");
    scanf("%hd", &tempFlight.flightMonth);
    
    for(short i = 0; i < flightCounter; i++){ // To check all flights
        int depMatch = 1, arrMatch = 1;
        for(int j = 0; tempFlight.DepatureGate[j] != '\0' || flights[i].DepatureGate[j] != '\0'; j++){ // Nested for, To check all flights gates
            if(tempFlight.DepatureGate[j] != flights[i].DepatureGate[j]){
                depMatch = 0;
                break;
            }
        }
        for(int j = 0; tempFlight.ArrivalGate[j] != '\0' || flights[i].ArrivalGate[j] != '\0'; j++){  // Nested for, To check all flights gates
            if(tempFlight.ArrivalGate[j] != flights[i].ArrivalGate[j]){
                arrMatch = 0;
                break;
            }
        }
        
        if(flights[i].FlightNumber == tempFlight.FlightNumber && 
           flights[i].Depatureime == tempFlight.Depatureime &&
           flights[i].ArrivalTime == tempFlight.ArrivalTime &&
           flights[i].flightDay == tempFlight.flightDay &&
           flights[i].flightMonth == tempFlight.flightMonth &&
           depMatch && arrMatch){
            
            printf("Flight found: %s to %s on %02hd/%02hd at %.2f\n", flights[i].DepatureGate, flights[i].ArrivalGate, flights[i].flightDay, flights[i].flightMonth, flights[i].Depatureime);
            printf("Are you sure you want to delete this flight? (1 for Yes, 2 for No): ");
            short confirm;
            scanf("%hd", &confirm);
            if(confirm == 1){
                for(short j = i; j < flightCounter - 1; j++){
                    flights[j] = flights[j + 1];
                }
                flightCounter--;
                printf("Flight deleted successfully!\n");
            }else{
                printf("Flight deletion canceled.\n");
            }
            return;
        }
    }
    printf("Flight not found or details incorrect!\n");
}


/* *********************** User ************************/

void FlightManagementUser(){ // Function to control Admin operations
    short SelectUser;
    do{
        printf("Enter 1 to Sign Up, 2 to Log In, 3 to exit: ");
        scanf("%hd", &SelectUser);
        
        switch(SelectUser){
            case 1: SignUpUser(); // To be redirected
                    break;
            case 2: LogInUser(); // To be redirected
                    break;
            case 3: printf("Exiting User mode.\n");
                    break;
            default: printf("Invalid input!!..Try again.\n");
        }
    }while(SelectUser != 3); // Exits if 3
}

void SignUpUser(){
    if(userCount >= MAX_USERS){
        printf("User limit reached!\n"); // Actual users 100
    }
    else{
        printf("Enter your ID: ");
        scanf("%hd", &passengers[userCount].ID);
        printf("Enter your Name: ");
        scanf("%s", &passengers[userCount].name);
        printf("Enter phone number: ");
        scanf("%lld", &passengers[userCount].PhoneNumber);
        printf("Signed Up Successfully, Welcome %s!\n", passengers[userCount].name);
        userCount++;
        SuccSignUp = 1; // To be used nxt line
        if(SuccSignUp) LogInUser; // To be redirected
    }
}

void LogInUser(){ // Function to log in an existing user
    char loginName[50];
    short loginID;
    long long loginPhone;
    short found = 0;

    while(!found){
        printf("Welcome to login gate..\n"); // To inform user that is switched
        printf("Enter ID: ");
        scanf("%hd", &loginID);
        printf("Enter your name: ");
        scanf("%s", loginName);
        printf("Enter phone number: ");
        scanf("%lld", &loginPhone);

        for(short i = 0; i < userCount; i++){
            int isSame = 1;
            for(int j = 0; passengers[i].name[j] != '\0' || loginName[j] != '\0'; j++){
                if(passengers[i].name[j] != loginName[j]){
                    isSame = 0;
                    break;
                }
            }
            if(passengers[i].ID == loginID && passengers[i].PhoneNumber == loginPhone && isSame){
                printf("Welcome back, %s!\n", passengers[i].name);
                found = 1;
                break;
            }
        }

        if(!found){
            printf("Invalid ID, name, or phone number. Try again.\n");
        }else{
            short WhileUserInInput;
            do{
                printf("Enter 1 to add new reservation, 2 to cancel reservation, 3 to modify reservation, 4 to show reservation log, 5 to exit: ");
                scanf("%hd", &WhileUserInInput);
                switch(WhileUserInInput){
                    case 1: AddNewReservation(loginID);
                        break;
                    case 2: CancelReservation(loginID);
                        break;
                    case 3: break;
                    case 4: ShowUserFlights(loginID);
                        break;
                }
            } while(WhileUserInInput != 5);
            
        }
    }
}

void ShowUserFlights(short userID){
    short found = 0;
    for(short i = 0; i < userCount; i++){
        if(passengers[i].ID == userID){
            found = 1;
            if(passengers[i].TripsCounter > 0){
                printf("Your past flights:\n");
                for(int j = 0; j <passengers[i].TripsCounter; j++){
                    printf("Flight %d:\n", j + 1);
                    printf("From: %s To: %s\n", flights[j].DepatureGate, flights[j].ArrivalGate);
                    printf("Departure Time: %.2f | Arrival Time: %.2f\n", flights[j].Depatureime, flights[j].ArrivalTime);
                    printf("Flight Number: %d | Date: %02hd/%02hd\n", flights[j].FlightNumber, flights[j].flightDay, flights[j].flightMonth);
                    printf("-------------------------------------------------\n");
                }
            }else{
                printf("You have no past flights recorded.\n");
            }
            break;
        }
    }
    if(!found){
        printf("User not found!\n");
    }
}

void CancelReservation(short userID){
    short found = 0;
    for(short i = 0; i < userCount; i++){
        if(passengers[i].ID == userID){
            found = 1;
            if(passengers[i].TripsCounter > 0){
                printf("Enter flight number to cancel: ");
                int flightNumber;
                scanf("%d", &flightNumber);
                
                short flightFound = 0;
                for(int j = 0; j < passengers[i].TripsCounter; j++){
                    if(flights[j].FlightNumber == flightNumber){
                        flightFound = 1;
                        for(int k = j; k < passengers[i].TripsCounter - 1; k++){
                            flights[k] = flights[k + 1];
                        }
                        passengers[i].TripsCounter--;
                        printf("Reservation canceled successfully!\n");
                        break;
                    }
                }
                if(!flightFound){
                    printf("Flight not found in your reservations!\n");
                }
            }else{
                printf("You have no reservations to cancel.\n");
            }
            break;
        }
    }
    if(!found){
        printf("User not found!\n");
    }
}

void AddNewReservation(short userID){
    if(flightCounter>0){
        printf("Select the flight you want to be in: \n");
        // Show avaliable flights function
    }

    short Selectedflight;
    do{
        printf("Select a flight by entering its number (1 - %hd): ", flightCounter);
        scanf("%hd", &Selectedflight);
    }while(Selectedflight < 1 || Selectedflight > flightCounter);

    if (flights[Selectedflight].AvaliableTickets > 0) {
        flights[Selectedflight].AvaliableTickets--;
        passengers[userID].TripsCounter++;
        printf("Reservation was done successfully! Flight %d booked.\n", flights[Selectedflight].FlightNumber);
    } else {
        printf("Sorry, no available seats on this flight.\n");
    }
}
