#include<stdio.h>
#define MAX_USERS 100
#define MAX_FLIGHTS 10
#define MAX_PASSANGERS 100
short userCount = 0;
short flightCounter = 0;

void LogInOrSignUpCheck();
void AddNewFlightSchedule();
void DeleteExistingFlightSchedule();
void ShowUserFlights(short userID);

struct Passenger{
    char name[50];
    short ID;
    long long PhoneNumber;
    int TripsCounter;
} passengers[MAX_USERS];;

struct Flights{
    int FlightNumber;
    short AvaliableTickets;
    char ArrivalGate[20];
    char DepatureGate[20];
    float Depatureime;
    float ArrivalTime;
    short flightDay;
    short flightMonth;
} flights[MAX_FLIGHTS];

int main(){
    passengers[userCount].TripsCounter = 0;
    LogInOrSignUpCheck();
    return 0;
}

void LogInOrSignUpCheck(){
    short UserOrAdmin;
    printf("Enter 1 for Admins, 2 for Users: ");
    UserAdminInvalid:
    scanf("%hd", &UserOrAdmin);
    switch(UserOrAdmin){
        case 1:
        short SelectAdmin;
            printf("Admin mode started..\n");
            ReEnterSelectAdmin:
            if(flightCounter >= 0 && flightCounter < MAX_FLIGHTS){
                printf("Enter 1 to add new flight schedule, 2 to Delete existing flight schedule, 3 to Update existing flight schedule: ");
                scanf("%hd", &SelectAdmin);
                switch(SelectAdmin){
                    case 1: AddNewFlightSchedule();
                    break;
                    case 2: DeleteExistingFlightSchedule();
                    break;
                    case 3:
                    break;
                    default:{
                        printf("Invalid input!!..Try again.\n");
                        goto ReEnterSelectAdmin;
                    }
                }
            }
            break;
        case 2: {
            printf("User mode started..\n");
            short SignOrLog;
            ReChooseLogOrSign:
            printf("Choose 1 to Sign Up, 2 to Log in: ");
            scanf("%hd", &SignOrLog);
            switch(SignOrLog){
                case 1:
                    if(userCount >= MAX_USERS){
                        printf("User limit reached!\n");
                        break;
                    }
                    printf("Enter your ID: ");
                    scanf("%hd", &passengers[userCount].ID);
                    printf("Enter your Name: ");
                    scanf("%s", &passengers[userCount].name);
                    printf("Enter phone number: ");
                    scanf("%lld", &passengers[userCount].PhoneNumber);
                    printf("Signed Up Successfully, Welcome %s!\n", passengers[userCount].name);
                    userCount++;
                    goto SwitchToLogin;
                case 2:{
                SwitchToLogin:
                    char loginName[50];
                    short loginID;
                    long long loginPhone;
                    short found = 0;
                SignInFail:
                    printf("Welcome to login gate..\n");
                    printf("Enter ID: ");
                    scanf("%hd", &loginID);
                    printf("Enter your name: ");
                    scanf("%s", &loginName);
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
                        goto SignInFail;
                    }else{
                        RechooseAvaOrOld:
                        printf("Enter 1 to search available flights, 2 to show reservation history: ");
                        short choice;
                        scanf("%hd", &choice);
                        if(choice == 1){
                            printf("Searching available flights...\n");
                        }else if(choice == 2){
                            printf("Showing reservation history...\n");
                            ShowUserFlights(loginID);
                        }else{
                            printf("Invalid input. Try again.\n");
                            goto RechooseAvaOrOld;
                        }
                    }
                    break;
                }
                default:
                    printf("Invalid input!!..Try again.\n");
                    goto ReChooseLogOrSign;
                    break;
            }
            break;
        }
        default:
            printf("Invalid input!..Try again: ");
            goto UserAdminInvalid;
            break;
    }

}

void AddNewFlightSchedule(){
    printf("Enter required to add a flight: \n");
    if(flightCounter <= MAX_FLIGHTS){
    printf("Enter depature gate: ");
    scanf("%s", &flights[flightCounter].DepatureGate);
    printf("Enter arrival gate: ");
    scanf("%s", &flights[flightCounter].ArrivalGate);
    ReEnterTime1:
    printf("Enter depature time ( 00.00 : 23.59 ): ");
    scanf("%f", &flights[flightCounter].Depatureime);
    if(flights[flightCounter].Depatureime > 23.59 && flights[flightCounter].Depatureime < 0){
        printf("Invalid input!!..Try again.\n");
        goto ReEnterTime1;
    }
    ReEnterTime2:
    printf("Enter Arrival time ( 00.00 : 23.59 ): ");
    scanf("%f", &flights[flightCounter].ArrivalTime);
    if(flights[flightCounter].ArrivalTime > 23.59 && flights[flightCounter].ArrivalTime < 0){
        printf("Invalid input!!..Try again.\n");
        goto ReEnterTime2;
    }
    printf("Enter flight number: ");
    scanf("%d", &flights[flightCounter].FlightNumber);
    ReEnterDay:
    printf("Enter flight day with numbers (1 : 31): ");
    scanf("%hd", &flights[flightCounter].flightDay);
    if( flights[flightCounter].flightDay > 31 && flights[flightCounter].flightDay < 1 ){
        printf("Invalid input!!..Try again.\n");
        goto ReEnterDay;
    }
    ReEnterMonth:
    printf("Enter flight month with numbers (1 : 12): ");
    scanf("%hd", &flights[flightCounter].flightMonth);
    if( flights[flightCounter].flightMonth > 12 && flights[flightCounter].flightMonth < 1 ){
        printf("Invalid input!!..Try again.\n");
        goto ReEnterMonth;
    }
    ReEnterSeats:
    printf("Enter number of avaliable seats: ");
    scanf("%hd", &flights[flightCounter].AvaliableTickets);
    if(flights[flightCounter].AvaliableTickets > 100 ){
        printf("Maximum allowed seats is 100\n");
        goto ReEnterSeats;
    }
    }
    flightCounter++;
    short GoBackOrEit1;
    printf("Enter 1 to go back, 2 to exit: ");
        scanf("%hd", &GoBackOrEit1);
    ReEnterGoBackOrEit1:
    switch(GoBackOrEit1){
        case 1: LogInOrSignUpCheck();
        break;
        case 2: break;
        default: goto ReEnterGoBackOrEit1;
        break;
    }
}

void DeleteExistingFlightSchedule(){
    int FlightNumberDel;
    char ArrivalGateDel[20];
    char DepatureGateDel[20];
    float DepatureimeDel;
    float ArrivalTimeDel;
    short flightDayDel;
    short flightMonthDel;
    short flightFound = 0;
    short ALike = 0;
    if(flightCounter > 0){
        printf("Enter depature gate: ");
        scanf("%s", &DepatureGateDel);
        printf("Enter arrival gate: ");
        scanf("%s", &ArrivalGateDel);
        ReEnterTime3:
        printf("Enter depature time ( 00.00 : 23.59 ): ");
        scanf("%f", &DepatureimeDel);
        if(DepatureimeDel > 23.59 || DepatureimeDel < 0){
            printf("Invalid input!!..Try again.\n");
            goto ReEnterTime3;
        }
        ReEnterTime4:
        printf("Enter Arrival time ( 00.00 : 23.59 ): ");
        scanf("%f", &ArrivalTimeDel);
        if(ArrivalTimeDel > 23.59 || ArrivalTimeDel < 0){
            printf("Invalid input!!..Try again.\n");
            goto ReEnterTime4;
        }
        printf("Enter flight number: ");
        scanf("%d", &FlightNumberDel);
        ReEnterDayDel:
        printf("Enter flight day with numbers (1 : 31): ");
        scanf("%hd", &flightDayDel);
        if( flightDayDel > 31 && flightDayDel < 1 ){
            printf("Invalid input!!..Try again.\n");
            goto ReEnterDayDel;
        }
        ReEnterMonthDel:
        printf("Enter flight month with numbers (1 : 12): ");
        scanf("%hd", &flightMonthDel);
        if( flightMonthDel > 12 || flightMonthDel < 1 ){
            printf("Invalid input!!..Try again.\n");
            goto ReEnterMonthDel;
        }
        for(short d = 0; flights[d].ArrivalGate == "\0" || flights[d].DepatureGate == "\0"; d++){
            ALike = 1;
        }
        for(short i = 0; i < MAX_FLIGHTS; i++){
            if((flights[i].Depatureime == DepatureimeDel)
             && (flights[i].ArrivalTime == ArrivalTimeDel)
             && (flights[i].flightDay == flightDayDel)
             && (flights[i].flightMonth == flightMonthDel)
             && (flights[i].FlightNumber == FlightNumberDel)
             && ALike){
                flightFound = i;
             } 
        }
        for(short j = 0; j < MAX_FLIGHTS; j++){
            if(j = flightFound){
                for(short x = flightFound; x < MAX_FLIGHTS; x++){
                    flights[x] = flights[x+1];
                }
                printf("Flight has been deleted successfully..\n");
            }
            flightCounter--;
            short GoBackOrEit2;
            scanf("%hd", &GoBackOrEit2);
            ReEnterGoBackOrEit2If:
        printf("Enter 1 to go back, 2 to exit: ");
            switch(GoBackOrEit2){
                case 1: LogInOrSignUpCheck();
                break;
                case 2: break;
                default: goto ReEnterGoBackOrEit2If;
                break;
            }
        }
    }else{
        printf("There is no flights to be deleted"); 
        short GoBackOrEit2;
        scanf("%hd", &GoBackOrEit2);
        ReEnterGoBackOrEit2Else:
        switch(GoBackOrEit2){
            case 1: LogInOrSignUpCheck();
            break;
            case 2: break;
            default: goto ReEnterGoBackOrEit2Else;
            break;
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
