/* This Program runs a secruity authorisation based on numeric codes that are four single-digit numbers between 0-9.  The user can enter a code or generate a random code. After a code is entered/generated, the user can encrypt the code and compare it to a fixed, authorised access code.  After the users code is encrypted, the user has an option to decrypt it.

-> Authorised access code is 1234
 
 Bryan McCarthy
 15/5/20
 */

#include <stdio.h>
#include <stdlib.h>

// Symbolic names
#define NUMS 4

// Structure templates
struct code_counter
{
    int correct_code;
    int wrong_code;
};

// Function signatures
// Function to read users code (option 1)
void enterCode(int*);
// Function to encrypt users code (option 2)
void encryptCode(int*, int*);
// Function to check if the encrypted code matches the default authorised access code (option 3)
void compareCodes(struct code_counter counter, int*, int*);
// Function to decrypt users code (option 4)
void decryptCode(int*);
// Function to display the number of times the encrypted code is correct/wrong (option 5)
void correct_wrong(struct code_counter counter);
// Function to exit the program (opttion 6)
void exitProgram(void);

int main()
{
    
    // Structure to count the number of times encrypted code is correct/wrong
    struct code_counter count;
    
    // Array to store users code
    int userCode[NUMS];
    // Array to store users encrypted code
    int encryptedCode[NUMS];
    // Array to store default access code
    int access_code[NUMS] = {4, 5, 2, 3};
    // Option 1 must be selected first
    int opt1 = 0;
    // Option 2 must be selected before option 3 or 4
    int opt2 = 0;
    // The user cannot encrypt their code if it is already encrypted
    int encryptCheck = 0;
    // The user cannot decrypt their code if it is already encrypted
    int decryptCheck = 0;
    
    if(opt1 == 0)
    {
    // Initialize counters to 0 once
    count.correct_code = 0;
    count.wrong_code = 0;
    }// end if
    
    while(1)
    {
        // Users option
        int option = 0;
        
        // Main Menu Display
        printf("(1) Enter a code or generate a random code\n");
        printf("(2) Encrypt code\n");
        printf("(3) Check if the encrypted code matches the default access code\n");
        printf("(4) Decrypt code\n");
        printf("(5) Display the number of times the encrypted code is correct/wrong\n");
        printf("(6) Exit program\n");
        
        scanf("%d", &option);
        
        switch (option)
        {
            case 1:
            {
                int codeChoice;
                
                encryptCheck = 0;
                decryptCheck = 0;
                
                // Give the option to enter a code or generate random code
                printf("(1) Enter code\n");
                printf("(2) Generate random code\n");
                
                scanf("%d", &codeChoice);
                
                if(codeChoice == 1)
                {
                    printf("Please enter a 4 digit code\n");
                
                    // Call function to allow user to enter code
                    enterCode(userCode);
                }// end if
                else
                {
                    printf("Generating random code\n");
                    
                    for(int i=0; i<NUMS; i++)
                    {
                        *(userCode + i) = rand() % 10;
                    }// end for
                    
                    for(int i=0; i<NUMS; i++)
                    {
                        printf("%d", *(userCode + i));
                    }// end for
                    printf("\n");
                    
                }// end else
                
                opt1++;
                
                break;
            }// end case 1
            case 2:
            {
                if(opt1 > 0)
                {
                    if(encryptCheck > 0)
                    {
                        printf("Code is already encrypted.\n");
                    } //end inner if
                    else
                    {
                    
                        // Call function to encrypt users code
                        encryptCode(userCode, encryptedCode);
                    
                        opt2++;
                        encryptCheck++;
                    }// end inner if..else
                }// end outer if
                else
                {
                    printf("Please enter a code first.\n");
                }// end outer if..else
                
                break;
            }// end case 2
            case 3:
            {
                if(opt2 > 0)
                {
                    if(encryptCheck == 0)
                    {
                        printf("Code must be encrypted.\n");
                    } //end inner if
                    else
                    {
                        // Call function to compare user code to access code
                        compareCodes(count, encryptedCode, access_code);
                    }// end inner if..else
                }// end outer if
                else
                {
                    printf("Please encrypt your code first.\n");
                }// end outer if..else
                
                break;
            }// end case 3
            case 4:
            {
                if(opt2 > 0)
                {
                    if(decryptCheck > 0)
                    {
                        printf("Code is already decrypted.\n");
                    }// end inner if
                    else
                    {
                    // Call function to decrypt users code
                    decryptCode(userCode);
                    
                    encryptCheck = 0;
                    
                    decryptCheck++;
                    }// end inner if..else
                }// end outer if
                else
                {
                    printf("Please encrypt your code first.\n");
                }// end outer if..else
                
                break;
            }// end case 4
            case 5:
            {
                // Display the number of times the encrypted code is correct/wrong
                correct_wrong(count);
                
                break;
            }// end case 5
            case 6:
            {
                printf("Program Ended\n");
                
                // Call exitProgram() to end program
                exitProgram();
                
                break;
            }// end case 6
            default:
            {
                printf("Invalid Menu Option\n");
                
                break;
            }// end default
        }// end switch
    }// end while
}// end main()

/* Function to read users code (option 1)
 */
void enterCode(int *userCode)
{
        
    int i;

    for(i=0; i<NUMS; i++)
    {
        scanf("%d", &*(userCode + i));
        if(*(userCode + i) < 0 || *(userCode + i) > 9)
        {
            printf("Invalid. Please enter a digit 0-9.\n");
            i--;
        }
    }// end for
}// end enterCode()

/* Function to encrypt the users code (option 2)
 */
void encryptCode(int *userCode, int *encryptedCode)
{
    
    int temp;
    
    // Swap the 1st number with the 3rd number
    temp = *(userCode + 0);
    *(userCode + 0) = *(userCode + 2);
    *(userCode + 2) = temp;
    
    // Swap the 2nd number with the 4th number
    temp = *(userCode + 1);
    *(userCode + 1) = *(userCode + 3);
    *(userCode + 3) = temp;
    
    // Add 1 to each number
    for(int i=0; i<NUMS; i++)
    {
        *(userCode + i) = *(userCode + i) + 1;
    }// end for
    
    // If any number has a value equal to 10, change this value to 0
    for(int i=0; i<NUMS; i++)
    {
        if(*(userCode + i) == 10)
        {
            *(userCode + i) = 0;
        }// end if
    }// end for
    
    for(int i=0; i<NUMS; i++)
    {
    *(encryptedCode + i) = *(userCode + i);
    }// end for
    
    for(int i=0; i<NUMS; i++)
    {
        printf("%d", *(encryptedCode + i));
    }// end for
    
    printf("\n");
    
}// end encryptCode()

/* Function to check if the encrypted code matches the default authorised access code (option 3)
 */
void compareCodes(struct code_counter counter, int *encryptedCode, int *access_code)
{

    int incorrect = 0;
    
    //check if the encrypted code matches the default access code
    for(int i=0; i<NUMS; i++)
    {
        if(encryptedCode[i] != access_code[i])
        {
            printf("Wrong Code entered\n");
            
            incorrect++;
            
            counter.wrong_code = counter.wrong_code + 1;
            
            break;
            
        }// end if
    }// end for
    
    if(incorrect == 0)
    {
        printf("Correct Code entered\n");
        
        counter.correct_code = counter.correct_code + 1;
        
    }// end if
    
}// end compareCodes()

/* Function to decrypt the users code (option 4)
 */
void decryptCode(int *userCode)
{
    
    int temp = 0;
    
    // Subtract 1 from each number
    for(int i=0; i<NUMS; i++)
    {
        *(userCode + i) = *(userCode + i) - 1;
    }// end for
    
    // If any number has a value equal to -1, change this value to 9
    for(int i=0; i<NUMS; i++)
    {
        if(*(userCode + i) == -1)
        {
            *(userCode + i) = 9;
        }// end if
    }// end for
    
    // Swap the 1st number with the 3rd number
    temp = *(userCode + 0);
    *(userCode + 0) = *(userCode + 2);
    *(userCode + 2) = temp;
    
    // Swap the 2nd number with the 4th number
    temp = *(userCode + 1);
    *(userCode + 1) = *(userCode + 3);
    *(userCode + 3) = temp;
    
    for(int i=0; i<NUMS; i++)
    {
        printf("%d", *(userCode + i));
    }// end for
    
    printf("\n");
}// end decryptCode

/* Function to display the number of times the encrypted code is correct/wrong
 */
void correct_wrong(struct code_counter count)
{
    printf("Correct:");
    printf("%d\n", count.correct_code);
    
    printf("Wrong:");
    printf("%d\n", count.wrong_code);
    
}// end

/* Function to exit the program (option 6)
 */
void exitProgram(void)
{
    exit(0);
}// end exitProgram()
