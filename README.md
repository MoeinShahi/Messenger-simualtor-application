# Messenger-simulator-application
### Program Functionality
The program facilitates user communication in an environment that allows interaction between users.

### I/O Problem and Solutions
- **Problem**: Storing messages and account information.
- **Solutions**: Using two text files for account information ('Data.txt') and message logs ('message_logs.txt').

### Data Structure
Using a 1D dynamic array to manage and store the data.

### Exception Handling
Employing exception handling for file operations to check for errors when opening files.

### Object-Oriented Programming (OOP)
Utilizing OOP concepts for handling member objects and log objects.

### IDE
The program is developed using Code::Blocks.

### Program Data Flow
1. Check for the existence of 'Data.txt' and 'message_logs.txt' files. If they don't exist, create them.
2. Use the `menu()` function, which does the following:
   - Check the number of lines in 'Data.txt', treating each line as a member object.
   - Allocate a dynamic array and fill each object with data from the file.
   - Read and process the data from 'Data.txt' using the `read_member()` function.
3. For User Login:
   - Call the `login()` function, compare user input with member object attributes using the `u_p_is_match()` method from the member class.
   - Upon successful login, call `Dashboard()` function and process messages from 'message_logs.txt'.
4. User Interaction:
   - Print received messages (Inbox) and allow sending messages using `sendmessage()`.
   - Display available users, get the local system time, and add messages to 'message_logs.txt'.

### User Account Creation
When a user selects 'create a new account', the `addaccount()` function is called to append a new line in 'Data.txt'.
