# Bank-Information-System
A system to manage banking affairs, implemented in C.
Main Features: Display current account balance | Record and Display all banking activities | Allow withdrawals from accounts | Register a deposit

Problem Statement<br><div>1. This system should be able to register a new customer account by using a structure and store detailed information such as names, addresses, telephone numbers, account numbers, 6-digit personal identification number PINs (security code for using the card) and the account balance in the file.&nbsp;</div><div>2. The system should display the menu for users to make choices.&nbsp;</div><div>3. Customers’ account information should be stored and managed. Each customer can have one or more accounts and each account is uniquely identified by an account number generated by the system randomly.&nbsp;</div><div>4. Bank statistical information such as the number of customers and the number of accounts can be collected and displayed.&nbsp;</div><div>5. The following banking activities are supposed to be provided for customers.&nbsp;</div><div>- 1) Display current account balance</div><div>- 2) Record and display all banking activities</div><div>- 3) Allow withdrawals from an account</div><div>- 4) Register a deposit</div><div>6. For the managers, the system should be capable of providing the functionalities shown below. Noted that all banking activities require the manager to log on at first.</div><div>- 1) Access the account customers' information</div><div>- 2) Access the number of customers to check the customers in the file</div><div>- 3) Display the number of accounts</div><div>7. The following activities need to be provided for bank clerks.</div><div>- 1) Add new accounts including relevant information</div><div>- 2) View all the register information and make deposits to customers' account</div><div>- 3) Account information including the name, the address, the telephone number and the PIN can be edited</div><div>- 4) Accounts can be deleted</div><div><br></div>Analysis<br>Input<br><div>1. A number from 1 to 4 for users to make their choices on the main menu</div><div>2. A number from 1 to 4 for managers to make their choices on the manager menu</div><div>3. A number from 1 to 4 for manager to choose among bank activities</div><div>4. A number from 1 to 5 for bank clerks to make a choice on the bank clerk menu</div><div>5. Account numbers with exactly 10 digits</div><div>6. PINs with 6 digits</div><div>7. Manager account usernames with 4-16 characters</div><div>8. Manager passwords with 6-12 characters</div><div>9. Bank clerks' account usernames with 4-16 characters</div><div>10.Bank clerks' passwords with 6-12 characters</div><div>11.Customers' addresses with maximum 50 characters</div><div>12.Customers' telephone numbers with maximum 15 digits</div><div>13.A number from 1 to 5 for customers to choose on the customer menu</div><div>14.An integer number representing the number of the withdraw</div><div>15.An integer number representing the number of the register of a deposit<br></div>Output<br><div>1. The main menu of the bank information system</div><div>2. Output warnings such as "Invalid input" and "xxx is illegal" if the inputs are not as required</div><div>3. Different menus for different login users to choose their operations</div><div>4. The number of customers and the number of accounts as the bank statistical information</div><div>5. Prompt messages telling users whether they log on or off successfully</div><div>6. The current account balance if needed<br></div><div>7. Instructions about the maximum withdraw number</div><div>8. Warnings if the database cannot be accessed</div><div>9. Prompt messages asking users whether to continue their operation.</div><div>10.Warnings if the relevant information is not existed</div><div>11.The account number of the login customer</div><div>12.Prompt messages asking bank clerks whether to view all the registers or not</div><div>13.Relevant information of registers like account number</div><div>14.Prompt messages asking users to input their passwords again for check</div><div>15.Customers' information if required</div><div><br></div>Design<br>To start with, several header files are included.<br>#include&lt;stdio.h&gt; is included for the standard input and output.<br>#include&lt;string.h&gt;is included for using the functions of string. For example, strlen().<br>#include&lt;Windows.h&gt; is used under Win32 console application.<br>#include&lt;conio.h&gt; is included for using the function getch().<br>#include&lt;stdlib.h&gt;is included for using various utility functions. Forexample, srand().<br>#include&lt;time.h&gt; is included for the initialization of the seed of function time().<br>A structure of customer is added, which contains 7 variables.<br>char cName[41] is a character array with 40 elements representing the name of the customer.<br>char cAddress[51] is a character array with 50 elements representing the address of the customer.<br>char cTelenumber[16] is a character array with 15 elements representing the telephone number of the customer.<br>char cAccount[11] is a character array with 10 elements representing the account number of the customer.<br>char cPIN[7] is a character array with 6 elements representing the password to the account.<br>int iBalance is an integer array representing the amount of balance.<br>int iRegister is an integer array representing the amount of registration.
