#include<stdio.h>
int main(){
    char UserOrAdmin = 0;
    printf("Enter 1 for Admins, 2 for users: ");
    UserAdminInvalid:
    scanf("%d", &UserOrAdmin);
    switch(UserOrAdmin){
        case 1:
        printf("Iam an admin\n");
        break;
        case 2:
        printf("Iam a user\n");
        break;
        default:
        printf("Invalid input!!\n");
        goto UserAdminInvalid;
        break;
    }
    return 0;
}