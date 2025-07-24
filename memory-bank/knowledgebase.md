<!-- Memory Bank File: Programming Concepts Knowledge Base -->
<!-- Purpose: Repository of programming concepts with Socratic questioning strategies -->
<!-- Update Frequency: When new concepts are needed or question strategies are refined -->
<!-- Cross-references: ←common-student-issues.md (error patterns), ←progress.md (student mastery) -->

# Programming Concepts Knowledge Base - C++ Focus

## How to Use This File:
- Add new concepts as needed during tutoring
- Reference concept-specific questions during sessions
- Use analogies to help explain abstract concepts
- Keep code snippets simple and illustrative
- Focus on C++ object-oriented programming concepts for modules 00-04

---

## C++ Module Progression Overview:
- **Module 00:** Namespace, classes, member functions, stdio streams, initialization lists, static, const
- **Module 01:** Memory allocation, pointers to members, references, switch statement
- **Module 02:** Ad-hoc polymorphism, operator overloading, Orthodox Canonical class form
- **Module 03:** Inheritance
- **Module 04:** Subtype polymorphism, abstract classes, interfaces

---

## C++ Specific Concepts:

### Concept: Class vs Object

**Core Explanation (For Tutor's Understanding):**
- Class is a blueprint/template that defines structure and behavior
- Object is an instance of a class - actual memory allocation
- Classes define member variables and member functions
- Each object has its own copy of member variables but shares member functions

**Helpful Analogies:**
- Class = House blueprint, Object = Actual house built from that blueprint
- Class = Cookie cutter, Object = Individual cookies made with the cutter
- Class = Recipe, Object = Actual meal cooked from the recipe

**Key Socratic Questions for This Concept:**
- "What's the difference between defining a class and creating an object?"
- "If I have 3 contact objects, how many copies of the member functions exist?"
- "What happens in memory when you write 'contact c1' vs when you write 'c1.displayContact()'?"
- "Why do we need both classes and objects instead of just one or the other?"

**Common Student Misconceptions:**
- Thinking class and object are the same thing
- Believing each object has its own copy of member functions
- Confusion about when memory is allocated

**Diagnostic Questions for Misconceptions:**
- "How many contact classes exist in your phonebook program?"
- "When you create a contact object, what exactly gets stored in memory?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
// Class definition - blueprint
class Contact {
private:
    std::string name;
public:
    void setName(std::string n) { name = n; }
};

// Object creation - actual instances
Contact person1; // One object
Contact person2; // Another object
```

**Prerequisites:** Basic understanding of data types and functions
**Leads to:** Constructors, destructors, static members

### Concept: Static vs Instance Members

**Core Explanation (For Tutor's Understanding):**
- Static members belong to the class itself, not to any specific object
- Instance members belong to each individual object
- Static members are shared across all objects of the class
- Static members exist even before any objects are created

**Helpful Analogies:**
- Static = Shared classroom whiteboard (one for all students)
- Instance = Individual student notebooks (each student has their own)
- Static = University rules (same for all students), Instance = Student grades (different for each)

**Key Socratic Questions for This Concept:**
- "If I have 5 Account objects, how many copies of _nbAccounts exist?"
- "What happens to static variables when all objects are destroyed?"
- "Why would you want data that's shared between all objects?"
- "How do you access a static member without creating an object?"

**Common Student Misconceptions:**
- Thinking static members are copied for each object
- Confusion about when static members are initialized
- Not understanding why static methods can't access instance variables

**Diagnostic Questions for Misconceptions:**
- "If I change _totalAmount in one Account object, what happens in other Account objects?"
- "Can a static method access a non-static member variable? Why or why not?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
class Account {
private:
    static int _nbAccounts;  // Shared by all objects
    int _amount;             // Each object has its own
public:
    static int getNbAccounts() { return _nbAccounts; }
    int getAmount() { return _amount; }
};
```

**Prerequisites:** Understanding of classes and objects
**Leads to:** Singleton pattern, class design principles

### Concept: Constructor and Destructor

**Core Explanation (For Tutor's Understanding):**
- Constructor is called automatically when object is created
- Destructor is called automatically when object is destroyed
- Constructors initialize object state and can take parameters
- Destructors clean up resources (memory, files, etc.)

**Helpful Analogies:**
- Constructor = Setting up your workspace when you arrive at work
- Destructor = Cleaning up your workspace when you leave
- Constructor = Birth certificate, Destructor = Death certificate
- Constructor = Moving into apartment, Destructor = Moving out

**Key Socratic Questions for This Concept:**
- "What happens if you don't write a constructor for your class?"
- "When exactly does the destructor get called?"
- "Why might you need different constructors with different parameters?"
- "What's the relationship between object lifetime and constructor/destructor calls?"

**Common Student Misconceptions:**
- Thinking constructors and destructors are regular functions you call manually
- Not understanding automatic constructor/destructor invocation
- Confusion about default constructor vs parameterized constructor

**Diagnostic Questions for Misconceptions:**
- "Do you need to explicitly call the constructor when creating an object?"
- "What happens if your class allocates memory but doesn't have a destructor?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
class Contact {
public:
    Contact() { std::cout << "Contact created\n"; }           // Constructor
    Contact(std::string n) : name(n) { }                     // Parameterized constructor
    ~Contact() { std::cout << "Contact destroyed\n"; }       // Destructor
private:
    std::string name;
};
```

**Prerequisites:** Understanding of classes and objects
**Leads to:** Copy constructors, assignment operators, RAII

### Concept: Stack vs Heap Allocation

**Core Explanation (For Tutor's Understanding):**
- Stack allocation: automatic storage, managed by compiler, limited lifetime (scope-based)
- Heap allocation: dynamic storage, managed by programmer, flexible lifetime (until explicitly deleted)
- Stack is faster but limited in size and lifetime
- Heap allows larger allocations and cross-scope object sharing

**Helpful Analogies:**
- Stack = Post-it notes (temporary, automatically discarded when done)
- Heap = Filing cabinet (permanent storage until you decide to throw away)
- Stack = Hotel room (automatic checkout when you leave)
- Heap = Buying a house (yours until you sell it)

**Key Socratic Questions for This Concept:**
- "When would you want an object to outlive the function that created it?"
- "What happens to stack-allocated objects when a function returns?"
- "Who is responsible for cleaning up heap-allocated memory?"
- "What are the trade-offs between stack and heap allocation?"

**Common Student Misconceptions:**
- Thinking all objects should be heap-allocated
- Not understanding automatic cleanup of stack objects
- Forgetting to delete heap-allocated memory

**Diagnostic Questions for Misconceptions:**
- "What happens to a Zombie object created with 'Zombie z' when the function ends?"
- "If you create a Zombie with 'new', what must you remember to do?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
void function() {
    Zombie stackZombie("Bob");     // Stack - automatic cleanup
    Zombie* heapZombie = new Zombie("Alice"); // Heap - manual cleanup required
    // stackZombie destroyed automatically here
    delete heapZombie; // Must manually delete
}
```

**Prerequisites:** Understanding of object lifecycle and constructors/destructors
**Leads to:** Smart pointers, RAII principles

### Concept: References vs Pointers

**Core Explanation (For Tutor's Understanding):**
- Reference is an alias - another name for an existing object
- Pointer is a variable that stores memory address of another object
- References must be initialized and cannot be reassigned
- Pointers can be null, reassigned, and used for arithmetic

**Helpful Analogies:**
- Reference = Nickname (always refers to the same person)
- Pointer = Address on envelope (can be changed, can be invalid)
- Reference = Direct phone connection (always connected to same person)
- Pointer = Phone number (can call different numbers, number might not exist)

**Key Socratic Questions for This Concept:**
- "What's the difference between giving someone a nickname vs giving them your address?"
- "Can a reference exist without referring to something?"
- "Why might you choose a reference over a pointer for a function parameter?"
- "When would you need the flexibility of a pointer instead of a reference?"

**Common Student Misconceptions:**
- Thinking references are just "safer pointers"
- Trying to reassign references after initialization
- Not understanding that references must always refer to valid objects

**Diagnostic Questions for Misconceptions:**
- "Can you change what a reference refers to after you create it?"
- "What happens if you try to create a reference without initializing it?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
int x = 5;
int& ref = x;        // Reference - alias for x
int* ptr = &x;       // Pointer - stores address of x

ref = 10;            // Changes x to 10
*ptr = 20;           // Changes x to 20
ptr = nullptr;       // Valid - pointer can be null
// int& ref2;        // ERROR - references must be initialized
```

**Prerequisites:** Understanding of memory addresses and variable scope
**Leads to:** Function parameters, member variables design decisions

### Concept: Dynamic Arrays (new[] and delete[])

**Core Explanation (For Tutor's Understanding):**
- Arrays can be allocated dynamically when size is not known at compile time
- Must use new[] for array allocation and delete[] for deallocation
- Mixing new/delete with new[]/delete[] causes undefined behavior
- Each element's constructor/destructor is called appropriately

**Helpful Analogies:**
- new[] = Renting a row of hotel rooms (all at once)
- delete[] = Checking out of all rooms (must return all keys)
- Single new/delete = Renting/returning one room
- Wrong pairing = Using wrong key type (chaos ensues)

**Key Socratic Questions for This Concept:**
- "Why do we need a special delete[] for arrays?"
- "What happens if you use delete instead of delete[] on an array?"
- "How does the program know how many objects to destroy with delete[]?"
- "When would you use dynamic arrays instead of fixed-size arrays?"

**Common Student Misconceptions:**
- Using delete instead of delete[] for arrays
- Thinking array size must be constant
- Not understanding that each array element gets constructed/destructed

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
int n = 5;
Zombie* zombies = new Zombie[n];  // Array of n zombies
// ... use the zombies
delete[] zombies;                 // Must use delete[] not delete
```

**Prerequisites:** Understanding of constructors/destructors and basic pointers
**Leads to:** STL containers, memory management patterns

### Concept: Reference Binding and Const-correctness

**Core Explanation (For Tutor's Understanding):**
- Non-const lvalue references (T&) can only bind to non-const lvalues (named variables that can be modified)
- Const references (const T&) can bind to lvalues, temporaries, literals, and const objects
- Const member functions guarantee not to modify the object, allowing them to be called on const objects
- Reference members must be initialized in the initializer list
- Object lifetime is critical: references to destroyed/copy objects lead to undefined behavior

**Helpful Analogies:**
- Reference = Nickname for a specific person (must always refer to someone who exists)
- Const reference = Nickname you promise never to use to change the person
- Temporary = Visitor who leaves quickly; only safe to reference if you promise not to change them

**Key Socratic Questions for This Concept:**
- "Why can't you bind a non-const reference to a temporary or literal?"
- "What happens if you try to modify an object through a const reference?"
- "Why do reference members require initialization in the initializer list?"
- "What is the difference between lvalue and rvalue in C++?"
- "How does object lifetime affect the safety of references in class design?"
- "Why do you need const member functions to call them on const objects?"

**Common Student Misconceptions:**
- Thinking all references can bind to any object
- Not realizing temporaries are destroyed at the end of the full expression
- Confusing constness of reference with constness of the object

**Diagnostic Questions for Misconceptions:**
- "What happens if you return a reference to a local variable?"
- "Why does the compiler complain about type qualifiers when calling a non-const member function on a const object?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
int x = 5;
int &ref1 = x;         // OK: non-const lvalue
const int &ref2 = 10;  // OK: binds to temporary
int &ref3 = 10;        // ERROR: cannot bind non-const ref to temporary
```

**Prerequisites:** Understanding of references and object lifetime
**Leads to:** Advanced class design, understanding temporaries and literals

### Concept: Class Design - References vs Pointers for Object Relationships

**Core Explanation (For Tutor's Understanding):**
- References represent permanent, required relationships between objects
- Pointers represent optional, changeable relationships between objects
- References must be initialized in constructor, cannot be reassigned
- Pointers can be NULL/nullptr, can be assigned later, can be changed
- Const references allow binding to temporaries and provide read-only access
- Choice depends on relationship semantics: permanent vs optional, required vs changeable

**Helpful Analogies:**
- Reference = Marriage certificate (permanent, cannot be changed once established)
- Pointer = Dating relationship (can be single, can change partners)
- Const reference = Library book (read-only access, but you can look at any book)
- Non-const reference = Personal tool (full access, but only to tools you own)

**Key Socratic Questions for This Concept:**
- "If HumanA must always have a weapon, what storage type ensures this requirement?"
- "If HumanB might not have a weapon initially, what storage type allows this flexibility?"
- "Why can't you assign to a reference member after construction?"
- "What's the difference between 'Weapon club; setWeapon(club);' and 'setWeapon(&club);'?"
- "When would you prefer a const reference over a non-const reference parameter?"
- "How do you represent 'no weapon' with a pointer vs a reference?"

**Common Student Misconceptions:**
- Thinking all references can be reassigned like pointers
- Not understanding why reference members require initializer list initialization
- Confusion about reference parameter vs pointer parameter in function calls
- Believing that passing by reference always creates a copy

**Diagnostic Questions for Misconceptions:**
- "Can you set a reference member to point to a different object after construction?"
- "What happens if you try to call setWeapon(club) when expecting a pointer?"
- "Why does 'const Weapon &' bind to temporaries but 'Weapon &' doesn't?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
// Permanent relationship - always has weapon
class HumanA {
    const Weapon &weapon;  // Reference: permanent, required
public:
    HumanA(const Weapon &w) : weapon(w) {}  // Must initialize
};

// Optional relationship - may have weapon
class HumanB {
    Weapon *weapon;  // Pointer: optional, changeable
public:
    HumanB() : weapon(nullptr) {}  // Can start with no weapon
    void setWeapon(Weapon &w) { weapon = &w; }  // Can assign later
};
```

**Prerequisites:** Understanding of references, pointers, constructors, const-correctness
**Leads to:** Advanced class design patterns, RAII, smart pointers

### Concept: C++ File I/O Streams (ifstream/ofstream)

**Core Explanation (For Tutor's Understanding):**
- C++ provides stream-based file I/O as an alternative to C-style file functions
- ifstream for input (reading), ofstream for output (writing)
- Stream objects handle file opening, closing, and error checking automatically
- Integration with C++ string class and stream operators makes text processing easier
- Documentation found in cppreference.com, not traditional man pages

**Helpful Analogies:**
- ifstream = Smart book reader (knows how to open, read pages, close automatically)
- ofstream = Smart typewriter (knows how to create document, write, save automatically)
- C-style fopen/fread = Manual tools (you control every step)
- C++ streams = Power tools (built-in intelligence and safety features)

**Key Socratic Questions for This Concept:**
- "What advantages might C++ streams offer over C-style file functions?"
- "Why can't you use 'std::string*' for argv in main()?"
- "Where would you look for C++ standard library documentation vs C library docs?"
- "How does 'std::ifstream file("name")' compare to 'FILE* f = fopen("name", "r")'?"

**Common Student Misconceptions:**
- Expecting C++ to completely replace C conventions (like main signature)
- Looking for C++ documentation in man pages
- Thinking streams and file descriptors are the same concept

**Diagnostic Questions for Misconceptions:**
- "Are you trying to use C file functions or C++ stream objects?"
- "Where are you looking for documentation about C++ standard library features?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
// C++ style
std::ifstream inputFile("data.txt");
if (inputFile.is_open()) {
    std::string line;
    std::getline(inputFile, line);
}
// File automatically closed when inputFile goes out of scope
```

**Prerequisites:** Understanding of C file I/O, basic C++ syntax
**Leads to:** Stream manipulators, file processing algorithms

### Concept: Pointers to Member Functions

**Core Explanation (For Tutor's Understanding):**
- Member functions belong to a class and require an object instance to be called
- Syntax: `returnType (ClassName::*pointerName)(parameters)`
- Must be called on an object: `(object.*pointer)()` or `(objectPtr->*pointer)()`
- Useful for callback systems, dynamic dispatch, and eliminating if-else chains
- More complex than regular function pointers due to class context requirement

**Helpful Analogies:**
- Member function pointer = Remote control (universal remote that works on any TV of the right brand)
- Regular function pointer = Direct button (works on any compatible device)
- Class instance = Specific TV (needed to make the remote work)
- Dynamic selection = Programming remote to use different buttons based on input

**Key Socratic Questions for This Concept:**
- "What's the difference between a pointer to a function and a pointer to a member function?"
- "Why do you need an object instance to call a member function through a pointer?"
- "How can you avoid long if-else chains when selecting functions dynamically?"
- "What's the difference between '&Class::function' and '&(this->function())'?"

**Common Student Misconceptions:**
- Trying to call member function pointers without an object instance
- Confusing function address with function call result
- Not understanding why parentheses are needed in calling syntax

**Diagnostic Questions for Misconceptions:**
- "Are you getting the address of the function or calling the function?"
- "Do you have an actual object to call this member function on?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
class Calculator {
public:
    int add(int a, int b) { return a + b; }
    int multiply(int a, int b) { return a * b; }
};

// Declaration and usage
int (Calculator::*operation)(int, int) = &Calculator::add;
Calculator calc;
int result = (calc.*operation)(5, 3);  // Calls add(5, 3)
```

**Prerequisites:** Understanding of classes, member functions, basic pointers
**Leads to:** Function objects, callbacks, design patterns

---

## Webserv Project Concepts:

### Concept: HTTP Protocol Fundamentals

**Core Explanation (For Tutor's Understanding):**
- HTTP is a request-response protocol between client and server
- Requests contain method (GET/POST/DELETE), URI, headers, and optional body
- Responses contain status code, headers, and optional body
- Stateless protocol - each request is independent

**Helpful Analogies:**
- HTTP request = Ordering at a restaurant (menu item, special instructions, payment)
- HTTP response = Receiving your order (success/failure, the food, receipt)
- Headers = Metadata envelope (like postal service stamps and addresses)
- Status codes = Universal result symbols (like traffic lights: green=success, red=error)

**Key Socratic Questions for This Concept:**
- "What information does a client need to send to request a web page?"
- "How does the server know what the client wants?"
- "What should the server send back if the requested file doesn't exist?"
- "Why might HTTP be called 'stateless' and what are the implications?"

**Common Student Misconceptions:**
- Thinking HTTP maintains connection state between requests
- Confusing HTTP headers with HTML content
- Not understanding that browsers automatically handle HTTP protocol details

**Diagnostic Questions for Misconceptions:**
- "Does the server remember previous requests from the same client?"
- "What's the difference between HTTP headers and the HTML content?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
// Basic HTTP request structure
GET /index.html HTTP/1.1
Host: example.com
User-Agent: Mozilla/5.0
Connection: close

// Basic HTTP response structure
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 142

<html><body>Hello World!</body></html>
```

**Prerequisites:** Basic understanding of client-server architecture
**Leads to:** HTTP parsing, response generation, status codes

### Concept: Socket Programming

**Core Explanation (For Tutor's Understanding):**
- Sockets are endpoints for network communication
- Server socket listens for incoming connections
- Client sockets connect to server sockets
- Data flows through established socket connections

**Helpful Analogies:**
- Socket = Phone number (unique identifier for communication endpoint)
- Listening socket = Receptionist (waits for incoming calls)
- Connected socket = Active phone conversation (two-way communication)
- Port = Office extension number (specific service on a machine)

**Key Socratic Questions for This Concept:**
- "What's the difference between a listening socket and a connected socket?"
- "Why does a server need to bind to a specific port?"
- "What happens when multiple clients want to connect simultaneously?"
- "How does the server know which client sent which data?"

**Common Student Misconceptions:**
- Thinking one socket handles all clients
- Confusing socket creation with connection establishment
- Not understanding port binding and listening process

**Diagnostic Questions for Misconceptions:**
- "How many sockets does a server need to handle 100 clients?"
- "What's the difference between socket(), bind(), and listen()?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
// Basic server socket setup
int server_fd = socket(AF_INET, SOCK_STREAM, 0);
bind(server_fd, (struct sockaddr*)&address, sizeof(address));
listen(server_fd, 3);
int client_fd = accept(server_fd, NULL, NULL);
```

**Prerequisites:** Basic understanding of network communication
**Leads to:** Non-blocking I/O, multiplexing, client management

### Concept: Non-blocking I/O and Multiplexing

**Core Explanation (For Tutor's Understanding):**
- Non-blocking I/O prevents operations from freezing the program
- select/poll/epoll allow monitoring multiple file descriptors simultaneously
- Server can handle many clients without creating threads for each
- Operations return immediately, even if no data is available

**Helpful Analogies:**
- Blocking I/O = Standing in line at DMV (wait until your turn)
- Non-blocking I/O = Checking mailbox (look, if empty, do other things)
- select/poll = Security guard watching multiple doors (monitors all entrances)
- Multiplexing = Waiter serving multiple tables (one person, many customers)

**Key Socratic Questions for This Concept:**
- "Why would a server freeze if it uses blocking I/O with multiple clients?"
- "What does select() tell you about file descriptors?"
- "How can one process handle hundreds of connections simultaneously?"
- "What's the benefit of non-blocking operations?"

**Common Student Misconceptions:**
- Thinking non-blocking I/O makes individual operations faster
- Confusing non-blocking with asynchronous
- Not understanding when to use select/poll

**Diagnostic Questions for Misconceptions:**
- "Does non-blocking I/O make individual operations faster?"
- "What happens if you try to read from a socket with no data?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
// Basic select() usage
fd_set read_fds;
FD_ZERO(&read_fds);
FD_SET(server_fd, &read_fds);
FD_SET(client_fd, &read_fds);
select(max_fd + 1, &read_fds, NULL, NULL, NULL);
```

**Prerequisites:** Understanding of file descriptors and socket programming
**Leads to:** Event-driven programming, scalable server architecture

### Concept: Configuration File Parsing

**Core Explanation (For Tutor's Understanding):**
- Configuration files define server behavior without recompiling
- Must parse structured text to extract settings
- Need to handle syntax errors gracefully
- Configuration affects server ports, routes, error pages, etc.

**Helpful Analogies:**
- Configuration file = Recipe book (instructions for how to behave)
- Parser = Chef reading recipe (interprets instructions)
- Default values = Cooking instincts (fallback when recipe is unclear)
- Syntax errors = Typos in recipe (need to handle gracefully)

**Key Socratic Questions for This Concept:**
- "Why use configuration files instead of hardcoding server settings?"
- "What should happen if the configuration file has an error?"
- "How do you handle optional vs required configuration parameters?"
- "What's the difference between syntax errors and logical errors in config?"

**Common Student Misconceptions:**
- Thinking configuration parsing is simple string manipulation
- Not handling edge cases and error conditions
- Confusing parsing with validation

**Diagnostic Questions for Misconceptions:**
- "What should your server do if the config file is missing?"
- "How do you validate that a port number is reasonable?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
// Basic configuration structure
server {
    listen 80;
    server_name example.com;
    root /var/www/html;
    error_page 404 /error.html;
}
```

**Prerequisites:** File I/O, string processing, error handling
**Leads to:** Server initialization, routing logic, virtual hosts

### Concept: CGI (Common Gateway Interface)

**Core Explanation (For Tutor's Understanding):**
- CGI allows web servers to execute external programs
- Server passes request information via environment variables
- CGI program reads stdin for POST data, writes stdout for response
- Server must handle process creation, execution, and cleanup

**Helpful Analogies:**
- CGI script = Expert consultant (specialized knowledge for specific tasks)
- Environment variables = Briefing documents (context information)
- stdin/stdout = Secure communication channel (input/output pipeline)
- Process execution = Hiring contractor (temporary, specialized work)

**Key Socratic Questions for This Concept:**
- "Why would you want to execute external programs from a web server?"
- "How does the web server communicate with the CGI program?"
- "What happens if a CGI script runs forever?"
- "Why use environment variables instead of command line arguments?"

**Common Student Misconceptions:**
- Thinking CGI scripts are part of the server process
- Not understanding the security implications of executing external code
- Confusing CGI with server-side includes

**Diagnostic Questions for Misconceptions:**
- "What happens to the server if a CGI script crashes?"
- "Why might running arbitrary code be dangerous?"

**Simple Illustrative Code Snippets (For Tutor Reference Only):**
```cpp
// CGI environment setup
setenv("REQUEST_METHOD", "GET", 1);
setenv("QUERY_STRING", "name=value", 1);
setenv("CONTENT_LENGTH", "42", 1);
execve("/usr/bin/php-cgi", argv, envp);
```

**Prerequisites:** Process management, environment variables, pipes
**Leads to:** Dynamic content generation, security considerations

---

## Network Programming & Systems Concepts:

### Concept: Socket API Fundamentals

**Core Explanation (For Tutor's Understanding):**
Socket programming involves creating network endpoints for communication. The basic flow: socket() creates endpoint, bind() assigns address, listen() prepares for connections, accept() handles incoming clients, recv()/send() transfer data.

**Socratic Questions Sequence:**
1. "What does your program need to know to communicate over a network?" (address, port)
2. "How does the operating system know where to deliver incoming network packets?" (binding)
3. "What's the difference between being ready to accept connections vs actually accepting them?" (listen vs accept)
4. "Why might accept() return a different socket than the one you created?" (separation of server socket from client socket)

**Common Student Misconceptions:**
- Confusing server socket (listens) with client socket (communicates)
- Not understanding why bind() is necessary
- Thinking listen() accepts connections rather than just preparing to accept

**Effective Analogies:**
- **Socket creation**: Setting up a phone line
- **Binding**: Getting a phone number assigned to your line
- **Listen**: Turning on the phone to receive calls
- **Accept**: Picking up when someone calls

### Concept: I/O Multiplexing with select()

**Core Explanation (For Tutor's Understanding):**
select() allows monitoring multiple file descriptors simultaneously, avoiding busy-waiting. It blocks until at least one file descriptor is ready for I/O operations, enabling efficient handling of multiple clients.

**Socratic Questions Sequence:**
1. "With your current echo server, what happens if two clients try to connect at the same time?" (second client blocks)
2. "How could the kernel help your program know when any of several file descriptors are ready?" (notification system)
3. "Looking at your server code, what file descriptors would you want to monitor?" (server socket for new connections, client sockets for data)
4. "What information would select() need from you to monitor the right file descriptors?" (which FDs to watch, what type of activity)

**Common Student Misconceptions:**
- Thinking select() handles the I/O operations itself (it only notifies about readiness)
- Not understanding difference between monitoring server socket vs client sockets
- Confusion about fd_set operations and why FD_ZERO is needed

**Effective Analogies:**
- **select() monitoring**: Like a security guard watching multiple doors and telling you when someone arrives at any door
- **fd_set**: Like a checklist of doors to watch
- **File descriptor readiness**: Like a door having someone waiting outside
