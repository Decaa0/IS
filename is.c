#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PASS "123213"
#define MAX 100

void option();
void shop();
void AdminLogin();
void CRUD();
void createpro();
void deletepro();
void editpro();
void viewpro();
bool check_duplicate(unsigned int id, const char *filename);
void restock();

void welcomeinput() {
    int num;

    while (1) {
        printf("HELLO! Please select a number:\n");
        printf("0 - Exit\n");
        printf("1 - Shop\n");
        printf("2 - Admin\n");
        printf("Select your choice: ");
        scanf("%d", &num);

        if (num == 0) {
            printf("Exiting program...\n");
            exit(0);
        } else if (num == 1) {
            printf("Welcome to Shop\n");
            shop();
        } else if (num == 2) {
            printf("Welcome to Admin\n");
            AdminLogin();
        } else {
            printf("Invalid number. Please try again.\n");
        }
    }
}

void shop() {
    printf("Shop is not implemented yet...\n");
    welcomeinput();
}

void AdminLogin() {
    char password[MAX];
    int attempts = 3;

    while (attempts > 0) {
        printf("Enter Admin Password: ");
        scanf("%s", password);

        if (strcmp(password, PASS) == 0) {
            printf("Access Granted.\n");
            option();
            return;
        } else {
            attempts--;
            printf("Incorrect password. Attempts remaining: %d\n", attempts);
        }
    }

    printf("No attempts left. Returning to main menu.\n");
    welcomeinput();
}

void option() {
    int num;

    while (1) {
        printf("\nAdmin Options:\n");
        printf("1 - View Report\n");
        printf("2 - CRUD Operations\n");
        printf("3 - Restock\n");
        printf("4 - Promotions\n");
        printf("0 - Return to Main Menu\n");
        printf("Select your choice: ");
        scanf("%d", &num);

        if (num == 0) {
            printf("Returning to Main Menu...\n");
            welcomeinput();
            return;
        } else if (num == 2) {
            CRUD();
        } else if (num == 3)    {
            restock();
        } else if (num == 1 || num == 3 || num == 4) {
            printf("This feature is not implemented yet.\n");
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void restock()  {
    
}

void CRUD() {
    int num;

    while (1) {
        printf("\nCRUD Options:\n");
        printf("1 - Create Products\n");
        printf("2 - View Products\n");
        printf("3 - Edit Products\n");
        printf("4 - Delete Products\n");
        printf("0 - Return to Admin Menu\n");
        printf("Select your choice: ");
        scanf("%d", &num);

        if (num == 0) {
            printf("Returning to Admin Menu...\n");
            option();
            return;
        } else if (num == 1) {
            createpro();
        } else if (num == 2) {
            viewpro();
        } else if (num == 3){
            editpro();   
        } else if (num == 4 ) {
            deletepro();
            
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void createpro() {
    unsigned int id;
    char name[MAX];
    char description[MAX];
    char exp[MAX];
    double price;
    int quantity;
    const char *filename = "Product.csv";

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    printf("Enter product details (ID, Name, Description, Price, Quantity, Expiration).\n");
   

    while (1) {
        printf("Type '0' as ID to stop adding products.\nEnter Product ID: ");
        scanf("%u", &id);
        if (id == 0) {
            break;
        }

        if (check_duplicate(id, filename)) {
            printf("Error: Product ID already exists. Try again.\n");
            continue;
        }

        printf("Enter Product Name: ");
        scanf("%s", name);

        printf("Enter Product Description: ");
        getchar();
        fgets(description, sizeof(description), stdin);
        description[strcspn(description, "\n")] = '\0';

        printf("Enter Product Price: ");
        scanf("%lf", &price);

        printf("Enter Product Quantity:");
        scanf("%d", &quantity);

        printf("Enter Product expiration Date (DD-MM-YYYY)\n :");
        scanf("%s", exp);

        fprintf(file, "%u,%s,\"%s\",%.2f,%s \n", id, name, description, price, exp);
        printf("Product added successfully!\n");

    }

    fclose(file);
    printf("All products saved to %s\n", filename);
}

bool check_duplicate(unsigned int id, const char *filename) {
    unsigned int existing_id;
    char existing_name[MAX], existing_description[MAX], existing_exp[MAX];
    double existing_price;
    int existing_quantity; 

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return false;
    }

 
    while (fscanf(file, "%u,%[^,],%[^,],%lf,%d,%[^\n]", 
                  &existing_id, existing_name, existing_description, 
                  &existing_price, &existing_quantity, existing_exp) == 6) {
        if (existing_id == id) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false; 
}

void deletepro() {
    
    unsigned int id;
    unsigned int targetid;
    char name[MAX], description[MAX], exp[MAX];
    double price;
    int quantity;
    
   FILE * file = fopen("Product.csv", "r");
   if (file == NULL)    {
        printf("File can't open");
        return;
   }
    FILE * temp_file = fopen("Temp.csv", "w" );
    if (temp_file == NULL){
        printf("Can't create temporary file");
        fclose(file);
        return;
    }
    printf("Return press: 0 \n");
    printf("Show item Press: 1\n");
    printf("Enter the Product id to delete :");
    scanf("%u", &targetid);
    if( targetid == 0){
        CRUD();
    }
    else if ( targetid == 1) {
        viewpro();
    }
    while (fscanf(file, "%u ,%99[^,] ,%99[^,] ,%lf\n ,%20d ,%20s", &id, name ,description, &price, &quantity ,exp ) == 6)  {
        if (id == targetid){
            printf("Delete Product : ID = %u Name = %s/n", id, name);
        
        } else {
            fprintf(temp_file,"%u,%s,%s,%.2f\n,%d, %s", id, name, description, price, quantity, exp);

        }
    }
    fclose(file);
    fclose(temp_file);
    
    if (remove("Product.csv") == 0 && rename("Temp.csv", "Product.csv") == 0 ){
         printf("Product deleted successfully.\n");
    }   else {
        printf("Error updating the file.\n");
    }
}

void editpro() {
    unsigned int id;
    unsigned int targetid;
    char name[MAX];
    char description[MAX], exp[MAX];
    int num, quantity;
    double price;
    printf("Back to menu press 0 \nSee the stock press 1");
    printf("Press the Product ID to edit:");
    scanf("%d", &targetid);

    if( targetid == 0 ){
        CRUD();
    }
    else if ( targetid == 1 ){
        viewpro();
    }
    else{

    FILE * file = fopen("Product.csv", "r");
    if( file == NULL)   {
        printf("Can't open the file");
        return;
    }
    FILE * temp_file = fopen("Temp.csv", "w");
    if(file == NULL)    {
        printf("Can't create temporary file");
        fclose(file);
        return;
    while(fscanf(file,"%u ,%[^,], %[^,], %lf, %d, %[^]", &id, name, description, &price, &quantity, exp)){
        if (id == targetid){
            found = true;
            printf("Product id = %u", targetid);
            printf("| %-10s | %-15s | %-30s | %-10s | %-10s | %-10s |\n", "Product ID", "Name",            
                 "Description", "Price", "Quantity", "Exp")
            printf("| %-10u | %-15s | %-30s | %-10.2f | %-10d | %-10s |\n", id, name, description, price, exp, quantity);

    printf("Edit Product Name Press 1/n");
    printf("Edit Product Description Press 2/n");
    printf("Edit Product Price Press 3");
    printf("Edit Product Quantity Press 4")
    printf("Enter your choice : ");
    scanf("%d", &num);

    switch (num)    {
        case 1:
        printf("Enter new Product name (Current : %s) ", name);
        scanf("%s", name);
        case 2:
        printf("Enter new Product description (Current : %s)", description);
        scanf("%s", description);
        case 3:
        printf("Enter new Product price (Current : %lf)", price);
        scanf("%lf", price);
        case 4:
        printf("Enter new Product quantity (Current : %d)")










    }

 

            
        }





    }

    }
    }
}

void viewpro() {
    unsigned int id;
    char name[MAX], description[MAX], exp[MAX];
    double price;
    int quantity; 

    FILE *file = fopen("Product.csv", "r");
    if (file == NULL) {
        printf("Can't open the file\n");
        return;
    }

    printf("----------------------------------------------------------------------------------\n");
    printf("| %-10s | %-15s | %-20s | %-10s | %-10s | %-10s |\n", "Product ID", "Name", "Description", "Price", "Quantity", "Exp");
    printf("----------------------------------------------------------------------------------\n");

    while (fscanf(file, " %u,%49[^,],%79[^,],%lf,%d,%49[^\n]", 
                  &id, name, description, &price, &quantity, exp) == 6) {
        printf("| %-10u | %-15s | %-20s | %-10.2f | %-10d | %-10s |\n", id, name, description, price, quantity, exp);
    }

    if (!feof(file)) {
        printf("Error reading file. Possible format issue.\n");
    }

    printf("----------------------------------------------------------------------------------\n");
    fclose(file);
}

int main() {
    welcomeinput();
    return 0;
}