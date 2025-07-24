<!-- Memory Bank File: Common Student Issues Catalog -->
<!-- Purpose: Catalog of common errors and Socratic diagnostic approaches -->
<!-- Update Frequency: When new error patterns emerge during tutoring -->
<!-- Cross-references: →knowledgebase.md (concept explanations), →tutoring-insights.md (effective patterns) -->

# Common Student Issues & Socratic Guidance - C++ Focus

## How to Use This File:
- Reference when students encounter errors or show confusion
- Use diagnostic questions to help students self-identify issues
- Add new patterns as they emerge during tutoring sessions
- Guide students toward understanding rather than giving direct solutions
- Focus on C++ specific issues for modules 00-04

---

## C++ Specific Common Issues:

### Issue: Missing Semicolon After Class Definition
**Symptoms:** Compiler error about missing semicolon; errors in subsequent code lines.
**Likely Misconceptions:** Not understanding that class definitions need semicolons (unlike functions).
**Socratic Diagnostic Questions:**
- "What's different about how you end a class definition versus a function definition?"
- "Look at the error line number - is that where you think the problem is?"
- "What punctuation do you see after other class definitions in examples?"
**Guidance Strategies (NOT solutions):**
- Guide them to compare their class syntax with working examples
- Ask them to read compiler error messages carefully
- Point out the difference between class declarations and function definitions

### Issue: Confusion Between Public and Private Access
**Symptoms:** Compiler errors about accessing private members; confusion about encapsulation.
**Likely Misconceptions:** Not understanding access specifiers; thinking all class members are accessible.
**Socratic Diagnostic Questions:**
- "What's the difference between public and private in your class?"
- "Why might you want some parts of your class to be hidden from outside code?"
- "Where are you trying to access this variable from?"
- "What methods does your class provide to work with private data?"
**Guidance Strategies (NOT solutions):**
- Use analogy of house with public rooms vs private rooms
- Guide them to trace data flow and access patterns
- Reference encapsulation concepts in knowledgebase.md

### Issue: Static Member Access Confusion
**Symptoms:** Trying to access static members through object instances; confusion about class-level vs object-level data.
**Likely Misconceptions:** Not understanding that static members belong to class, not objects.
**Socratic Diagnostic Questions:**
- "Does this data belong to a specific object or to all objects of this class?"
- "If no objects exist yet, should this data still be accessible?"
- "How many copies of this variable exist if you have 5 objects?"
- "What's the difference between Account::_nbAccounts and myAccount._amount?"
**Guidance Strategies (NOT solutions):**
- Use whiteboard analogy (shared vs individual notebooks)
- Guide them to think about data ownership and scope
- Reference static vs instance concepts in knowledgebase.md

### Issue: Constructor Parameter vs Member Variable Confusion
**Symptoms:** Shadowing warnings; incorrect initialization; confusion about parameter scope.
**Likely Misconceptions:** Not understanding scope of constructor parameters vs member variables.
**Socratic Diagnostic Questions:**
- "What happens when a parameter has the same name as a member variable?"
- "How does the compiler know which 'name' you're referring to?"
- "What's the scope of constructor parameters?"
- "How long do constructor parameters exist?"
**Guidance Strategies (NOT solutions):**
- Guide them to use different parameter names first, then introduce 'this->'
- Help them trace variable scope and lifetime
- Reference constructor concepts in knowledgebase.md

### Issue: Header File and Implementation Separation
**Symptoms:** Linker errors; multiple definition errors; confusion about .hpp vs .cpp files.
**Likely Misconceptions:** Not understanding declaration vs definition; confusion about header inclusion.
**Socratic Diagnostic Questions:**
- "What's the difference between declaring a function and defining it?"
- "Why do we separate class declarations from implementations?"
- "What happens when you #include a file?"
- "Where should function bodies go - header or implementation file?"
**Guidance Strategies (NOT solutions):**
- Use blueprint vs building analogy
- Guide them to understand compilation process
- Help them organize code structure logically

### Issue: iostream vs stdio Mixing
**Symptoms:** Mixing printf/scanf with cout/cin; confusion about C vs C++ I/O.
**Likely Misconceptions:** Not understanding difference between C and C++ I/O approaches.
**Socratic Diagnostic Questions:**
- "What language features are you using here - C or C++?"
- "What's the difference between printf and cout?"
- "Why might C++ provide its own I/O system instead of just using C's?"
- "Which approach fits better with object-oriented programming?"
**Guidance Strategies (NOT solutions):**
- Guide them to choose one approach consistently
- Help them understand language evolution and design principles
- Reference C++ stream concepts

### Issue: Memory Management Confusion (new/delete)
**Symptoms:** Memory leaks; double deletion; using delete instead of delete[]; segmentation faults.
**Likely Misconceptions:** Not understanding dynamic memory ownership; confusion about when to delete.
**Socratic Diagnostic Questions:**
- "Who owns this memory - which part of your code is responsible for cleaning it up?"
- "What happens if you delete the same memory twice?"
- "How does 'new' differ from declaring a variable normally?"
- "What's the difference between 'delete' and 'delete[]'?"
**Guidance Strategies (NOT solutions):**
- Use RAII principles and smart pointer concepts
- Guide them to trace memory ownership
- Reference dynamic allocation concepts in knowledgebase.md

### Issue: Memory Leaks from Forgetting delete/delete[]
**Symptoms:** Program uses increasing memory; valgrind shows "definitely lost" blocks.
**Likely Misconceptions:** Not understanding that new requires matching delete; thinking destructors automatically clean up dynamic memory.
**Socratic Diagnostic Questions:**
- "When you use 'new' to create an object, who is responsible for cleaning it up?"
- "What happens to heap-allocated memory if you don't explicitly delete it?"
- "How is this different from stack-allocated objects?"
- "Why doesn't the destructor automatically clean up objects created with new?"
**Guidance Strategies (NOT solutions):**
- Guide them to trace object ownership and lifetime
- Help them identify every 'new' and match it with corresponding 'delete'
- Reference RAII concepts in knowledgebase.md

### Issue: Using delete instead of delete[] for arrays
**Symptoms:** Undefined behavior; possible crashes; only first element destructor called.
**Likely Misconceptions:** Not understanding difference between single object and array allocation.
**Socratic Diagnostic Questions:**
- "What's the difference between 'new Zombie' and 'new Zombie[5]'?"
- "How does the compiler know how many destructors to call?"
- "Why do arrays need special treatment for deletion?"
- "What happens if you mix up delete and delete[]?"
**Guidance Strategies (NOT solutions):**
- Guide them to match allocation/deallocation pairs consistently
- Help them understand array vs single object lifetime
- Reference dynamic arrays concepts in knowledgebase.md

### Issue: Reference Initialization and Reassignment Confusion
**Symptoms:** Compiler errors about uninitialized references; confusion about reference behavior.
**Likely Misconceptions:** Treating references like pointers; not understanding reference immutability.
**Socratic Diagnostic Questions:**
- "What does it mean for a reference to be an 'alias'?"
- "Can a nickname exist without a person to nickname?"
- "What happens when you assign to a reference after creating it?"
- "Why can't references be reassigned like pointers?"
**Guidance Strategies (NOT solutions):**
- Use nickname/alias analogies consistently
- Guide them to understand reference binding vs assignment
- Reference references vs pointers concepts in knowledgebase.md

### Issue: Null Pointer Dereferencing in Pointer to Member Functions
**Symptoms:** Segmentation faults when calling function through null pointer.
**Likely Misconceptions:** Not checking pointer validity; confusion about pointer to member syntax.
**Socratic Diagnostic Questions:**
- "What could cause a pointer to member function to be invalid?"
- "How do you check if a pointer is safe to dereference?"
- "What's the difference between a null pointer and an uninitialized pointer?"
- "Why might a pointer to member function be null?"
**Guidance Strategies (NOT solutions):**
- Guide them to validate pointers before dereferencing
- Help them understand pointer safety patterns
- Reference pointer concepts in knowledgebase.md

### Issue: Stack Overflow from Large Stack Allocations
**Symptoms:** Segmentation fault; stack overflow errors with large objects/arrays.
**Likely Misconceptions:** Not understanding stack size limitations; using stack for large data.
**Socratic Diagnostic Questions:**
- "Why might the stack have size limitations?"
- "When would you choose heap over stack for large objects?"
- "What happens if you try to create a very large array on the stack?"
- "How do you determine if something should be stack or heap allocated?"
**Guidance Strategies (NOT solutions):**
- Guide them to consider data size and lifetime requirements
- Help them understand stack vs heap trade-offs
- Reference stack vs heap concepts in knowledgebase.md

### Issue: Reference Binding and Const-correctness Errors
**Symptoms:** Compiler errors about binding non-const reference to temporary, or calling non-const member function on const object.
**Likely Misconceptions:** Not understanding reference binding rules; not realizing const member functions are needed for const objects.
**Socratic Diagnostic Questions:**
- "Is your reference parameter const or non-const?"
- "Are you trying to bind a reference to a temporary or literal?"
- "Is the member function you're calling marked as const?"
- "What is the lifetime of the object you're referencing?"
**Guidance Strategies (NOT solutions):**
- Guide students to check parameter and member function constness
- Encourage printing addresses and destructor messages to visualize object lifetimes
- Use analogies for reference binding and constness

### Issue: Reference vs Pointer Parameter Confusion  
**Symptoms:** "No viable overloaded '=' errors; "must explicitly initialize reference member" errors; confusion about setWeapon(club) vs setWeapon(&club).
**Likely Misconceptions:** Not understanding difference between passing object vs address; confusion about reference vs pointer storage in classes.
**Socratic Diagnostic Questions:**
- "Is your function expecting an object, a reference to an object, or a pointer to an object?"
- "What's the difference between 'club' and '&club' when passing to a function?"
- "Can reference members be assigned after construction, or must they be initialized?"
- "How do you represent 'no value' with a reference vs a pointer?"
**Guidance Strategies (NOT solutions):**
- Guide students to understand parameter types and calling conventions
- Help them visualize object vs address vs reference relationships
- Encourage experimentation with different parameter and storage types
- Reference class design concepts in knowledgebase.md

### Issue: Const-correctness and Type Qualifier Errors
**Symptoms:** "Object has type qualifiers that are not compatible with the member function" errors; confusion about const member functions.
**Likely Misconceptions:** Not understanding when const member functions are required; confusion about const objects vs const references.
**Socratic Diagnostic Questions:**
- "Is the object you're calling this function on declared as const?"
- "Does your member function promise not to modify the object?"
- "Why might the compiler require this guarantee for const objects?"
- "What's the difference between 'const Weapon' and 'Weapon &'?"
**Guidance Strategies (NOT solutions):**
- Guide students to check constness of both objects and member functions
- Help them understand const-correctness as a design principle
- Encourage thinking about read-only vs modifiable interfaces
- Reference const-correctness concepts in knowledgebase.md

### Issue: Object Lifetime and Reference Binding
**Symptoms:** Garbage values after object destruction; confusion about reference vs copy semantics; temporary object binding errors.
**Likely Misconceptions:** Not understanding object lifetimes; confusion about when references become invalid.
**Socratic Diagnostic Questions:**
- "How long does this object exist in memory?"
- "What happens to references when the object they refer to is destroyed?"
- "Is your reference pointing to a temporary object or a permanent one?"
- "Why can const references bind to temporaries but non-const references can't?"
**Guidance Strategies (NOT solutions):**
- Guide students to trace object creation and destruction
- Help them visualize memory addresses and object lifetimes
- Encourage printing addresses and destructor messages for experimentation
- Reference object lifetime concepts in knowledgebase.md

---

## Webserv Project Specific Issues:

### Issue: Non-blocking I/O Implementation Confusion
**Symptoms:** Server hangs or becomes unresponsive; incorrect use of select/poll; blocking operations mixed with non-blocking setup.
**Likely Misconceptions:** Not understanding difference between blocking and non-blocking operations; thinking non-blocking means faster.
**Socratic Diagnostic Questions:**
- "What should happen if you try to read from a socket that has no data ready?"
- "Why might your server freeze when handling multiple clients?"
- "What does select() tell you before you attempt to read or write?"
- "How do you know if a socket is ready for reading or writing?"
**Guidance Strategies (NOT solutions):**
- Guide them to understand event-driven programming model
- Help them trace through select() behavior with multiple file descriptors
- Reference non-blocking I/O concepts in knowledgebase.md

### Issue: HTTP Protocol Parsing Errors
**Symptoms:** Malformed HTTP responses; incorrect status codes; missing or wrong headers; browser compatibility issues.
**Likely Misconceptions:** Thinking HTTP is simpler than it is; not understanding required vs optional headers; confusion about request/response format.
**Socratic Diagnostic Questions:**
- "What are the essential parts of an HTTP response?"
- "Why might a browser display an error even though your server sent data?"
- "What's the difference between HTTP headers and the actual content?"
- "How do you know when an HTTP request is complete?"
**Guidance Strategies (NOT solutions):**
- Guide them to compare their output with real HTTP servers (curl, browser dev tools)
- Help them understand HTTP specification requirements
- Reference HTTP protocol concepts in knowledgebase.md

### Issue: Configuration File Parsing Edge Cases
**Symptoms:** Server crashes on malformed config; doesn't handle missing files; ignores some configuration options.
**Likely Misconceptions:** Thinking parsing is just string splitting; not considering error cases; assuming configuration is always valid.
**Socratic Diagnostic Questions:**
- "What should happen if the configuration file doesn't exist?"
- "How do you handle configuration values that don't make sense?"
- "What's the difference between a syntax error and a logical error in config?"
- "Should your server start if the configuration has problems?"
**Guidance Strategies (NOT solutions):**
- Guide them to think about robustness and error handling
- Help them design graceful degradation strategies
- Reference configuration parsing concepts in knowledgebase.md

### Issue: CGI Implementation Security and Process Management
**Symptoms:** Server crashes when CGI script fails; infinite CGI processes; security vulnerabilities; incorrect environment variable setup.
**Likely Misconceptions:** Not understanding process lifecycle; thinking CGI is part of server; not considering security implications.
**Socratic Diagnostic Questions:**
- "What happens to your server if a CGI script runs forever?"
- "How do you clean up after a CGI script that crashes?"
- "Why might executing arbitrary code be dangerous?"
- "What information does a CGI script need to generate the correct response?"
**Guidance Strategies (NOT solutions):**
- Guide them to understand process management and cleanup
- Help them think about security boundaries and sandboxing
- Reference CGI concepts in knowledgebase.md

### Issue: Socket Resource Management and Memory Leaks
**Symptoms:** File descriptor leaks; server runs out of sockets; memory leaks from unclosed connections; performance degradation over time.
**Likely Misconceptions:** Not understanding socket lifecycle; forgetting to close file descriptors; not handling client disconnections properly.
**Socratic Diagnostic Questions:**
- "What happens if you never close a socket?"
- "How do you detect when a client has disconnected?"
- "Why might your server slow down after handling many requests?"
- "What resources does each client connection consume?"
**Guidance Strategies (NOT solutions):**
- Guide them to trace resource allocation and cleanup
- Help them understand RAII principles applied to network resources
- Reference socket programming concepts in knowledgebase.md

### Issue: HTTP Request/Response State Management
**Symptoms:** Mixing up data from different clients; incomplete request processing; response headers sent multiple times.
**Likely Misconceptions:** Not understanding HTTP stateless nature; confusing per-client vs global state; not properly tracking request completeness.
**Socratic Diagnostic Questions:**
- "How do you keep track of which data belongs to which client?"
- "What happens if a client sends a request in multiple packets?"
- "Why might data from one client appear in another client's response?"
- "How do you know when you've received a complete HTTP request?"
**Guidance Strategies (NOT solutions):**
- Guide them to design proper client state management
- Help them understand request parsing and buffering
- Reference HTTP protocol concepts in knowledgebase.md

### Issue: Server Architecture and Scalability Design
**Symptoms:** Server performance degrades with many clients; monolithic code structure; difficulty adding new features; poor error isolation.
**Likely Misconceptions:** Not thinking about scalability; creating tightly coupled code; not separating concerns properly.
**Socratic Diagnostic Questions:**
- "How would you add support for a new HTTP method?"
- "What happens to other clients if one client sends malformed data?"
- "How do you test that your server can handle 1000 concurrent clients?"
- "Which parts of your code would change if you added HTTPS support?"
**Guidance Strategies (NOT solutions):**
- Guide them to think about modular design and separation of concerns
- Help them apply OOP principles to server architecture
- Reference server design patterns and scalability concepts

### Issue: Multiplexing and Event Loop Implementation
**Symptoms:** Server doesn't respond to all ready sockets; select/poll timeout issues; busy waiting; missed events.
**Likely Misconceptions:** Not understanding event-driven programming; incorrect select/poll usage; not handling all ready file descriptors.
**Socratic Diagnostic Questions:**
- "What does it mean when select() returns?"
- "How do you check which specific sockets are ready for reading?"
- "What should you do if select() returns but no sockets seem ready?"
- "Why might some clients get faster responses than others?"
**Guidance Strategies (NOT solutions):**
- Guide them to understand event loop design patterns
- Help them trace through select/poll behavior step by step
- Reference multiplexing concepts in knowledgebase.md

---

## Network Programming Common Issues:

### Issue: Blocking accept() in Single-Threaded Server
**Symptoms:** Server handles one client at a time; second client can't connect until first disconnects.
**Likely Misconceptions:** Not understanding that accept() blocks and prevents handling multiple clients.
**Socratic Diagnostic Questions:**
- "What happens when you run your server and try to connect two telnet sessions?"
- "Where in your code does the program wait for something to happen?"
- "What would need to change for your server to handle multiple clients?"
**Guidance Strategies (NOT solutions):**
- Guide them to test with multiple clients and observe the blocking behavior
- Ask them to identify where their program "gets stuck" waiting
- Help them discover the need for non-blocking I/O through experimentation

### Issue: Confusion About select() Parameters
**Symptoms:** Student unsure which file descriptors to monitor or how to set up fd_set.
**Likely Misconceptions:** Not understanding difference between server socket and client sockets; confusion about fd_set operations.
**Socratic Diagnostic Questions:**
- "In your server, what are the different ways a client can interact with you?"
- "What's the difference between a new client trying to connect vs an existing client sending data?"
- "Which socket would detect new clients, and which would detect data from existing clients?"
**Guidance Strategies (NOT solutions):**
- Guide them to identify all the "events" their server needs to handle
- Help them map events to specific file descriptors
- Ask them to trace through what happens when different types of client activity occur

### Issue: Forgetting to Check select() Return Value
**Symptoms:** Program doesn't handle errors or timeouts properly; may not detect when file descriptors are ready.
**Likely Misconceptions:** Thinking select() always succeeds; not understanding select() can return 0 (timeout) or -1 (error).
**Socratic Diagnostic Questions:**
- "What could go wrong when calling select()?"
- "How would you know if select() detected activity vs encountered an error?"
- "What does the return value of select() tell you?"
**Guidance Strategies (NOT solutions):**
- Guide them to read select() documentation for return values
- Ask them to think about error handling for system calls
- Help them discover different return value meanings through testing

---

**Cross-References:**
- **→ knowledgebase.md**: Links to related concept definitions and core explanations
- **← tutoring-insights.md**: Sources proven guidance strategies and successful approaches
- **→ active-session.md**: Provides diagnostic questions for current student difficulties
- **← progress.md**: Reference student's learning journey to contextualize current issues
