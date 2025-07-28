<!-- Memory Bank File: Problem-Solving Plan -->
<!-- Purpose: Problem-solving strategy development and execution tracking -->
<!-- Update Frequency: When tackling new complex problems or completing plan steps -->
<!-- Cross-references: ←student-profile.md (learning style), ↔progress.md (skill development), ↔active-session.md (current focus), ←knowledgebase.md (concepts) -->

# Problem-Solving Plan

**Date Created:** 2025-07-15 (ISO 8601 format: YYYY-MM-DD)
**Last Updated:** 2025-07-28 (ISO 8601 format: YYYY-MM-DD)
**Student Identifier:** alejiri

## Current Problem Focus

**Problem Title:** Webserv HTTP Server Implementation

**Problem Statement:** Create a fully functional HTTP server in C++98 that can handle multiple clients, serve static files, process CGI scripts, and parse configuration files. The server must be non-blocking, handle GET/POST/DELETE methods, and be compatible with standard web browsers.

---

## Problem Analysis

### What I Understand:
- The server needs to have an IP address and a port, that listens for incoming requests
- The server is able to handle the request, and it cannot be blocked or non-functional
- If the request is processed correctly the server responds appropriately, if not it returns an error to the client
- The client can send a request to the server, it can be just to render an HTML page for instance
- If the request is made correctly the server can show the HTML page
- Success means the server responds correctly to requests, returns errors when needed, renders HTML for valid requests

### What I'm Not Sure About:
- Specific HTTP protocol details and request/response format
- Configuration file structure and required settings
- How to handle multiple clients simultaneously without blocking
- Error handling specifics and proper HTTP error responses

### Problem Breakdown:
- **Core Function:** Listen on IP/port, receive HTTP requests, send back appropriate responses (HTML or errors)
- **Input:** HTTP requests from clients, configuration file settings
- **Output:** HTTP responses (HTML pages, error messages, status codes)
- **Processing:** Parse incoming requests, determine response based on request type, serve files or return errors

---

## Knowledge Inventory

### What I Already Know:
- Strong C++ foundation (modules 00-04 completed)
- Object-oriented programming and inheritance
- Memory management and RAII principles
- File I/O and stream processing
- Problem-solving and debugging skills
- File descriptors and file streams (can leverage for network sockets)
- File parsing capabilities (useful for configuration files)
- Programs that read from stdin and write to stdout
- Opening multiple files simultaneously
- Line-by-line file reading (getnextline project)
- Handling multiple input types
- Experience with C (transferable to systems programming)

### What I Need to Learn:
- How to set up sockets and connect to IP address and port
- What information to put in the configuration file
- How to make the server handle several incoming messages without blocking
- How to display an HTML file to the client after a successful request
- What information the client needs to send to the server for a proper response
- HTTP protocol fundamentals
- Network programming with sockets
- Non-blocking I/O operations using select() for I/O multiplexing
- Configuration file parsing
- CGI execution and process management
- Server architecture and design patterns

### I/O Multiplexing Understanding:
- **Problem**: Busy-waiting (constantly checking file descriptors) wastes CPU resources
- **Solution**: I/O multiplexing lets the kernel notify when sockets have data ready
- **Key Insight**: Kernel networking hardware handles the monitoring, program sleeps until awakened
- **select() Choice**: Simple, portable, good for learning and moderate client loads
- **Advantage**: CPU does real work only when needed, kernel handles the waiting efficiently

---

## MVP Strategy

### Phase 1: Foundation (Echo Server) - COMPLETED ✅
- **Goal:** Basic socket communication working
- **What was built:** Server that accepts one connection, reads data, echoes it back
- **Key learning:** Socket API functions (socket, bind, listen, accept, recv, send)
- **Success criteria:** Client can connect via telnet, send text, receive echo back
- **Status:** Working perfectly - proven socket foundation

### Phase 2: Non-blocking Multi-client (Updated 2025-07-28)
**MVP Goal:** Robust multi-client echo server using select()
- Use std::set<int> to track client sockets
- Rebuild fd_set every loop, add server and all clients
- Calculate nfds as max(serverSocket, *clients.rbegin()) + 1
- Accept new clients, echo data, handle disconnects
- Re-initialize timeout before each select() call
- Debug infinite loop and timeout behavior
- Safely remove disconnected clients from set while iterating
**Success:** Multiple telnet clients connect, send/receive data, and disconnect cleanly

### Phase 3: HTTP Protocol
- **Goal:** Serve basic HTTP responses instead of echo
- **Features:** Parse simple HTTP requests, return proper HTTP responses
- **Key learning:** HTTP request/response format, status codes, headers

### Phase 4: Enhanced Features
- **Goal:** Configuration file, static file serving, error handling
- **Features:** Dynamic port/IP configuration, serve HTML files, proper error pages

---

## Implementation Plan

### Current Step: [To be updated during session]

### Step 1: [To be defined]
- **Goal:** [What this step achieves]
- **Tasks:** [Specific actions to complete]
- **Success Criteria:** [How to know this step is done]
- **Status:** Not Started

### Step 2: [To be defined]
- **Goal:** [What this step achieves]
- **Tasks:** [Specific actions to complete]
- **Success Criteria:** [How to know this step is done]
- **Status:** Not Started

---

## Learning Path

### Immediate Research Needs:
- Socket API functions (socket, bind, listen, accept)
- select() function - how to monitor multiple file descriptors
- Basic HTTP request structure and response format
- Configuration file parsing strategies
- Non-blocking socket setup and management

### Concepts to Master:
- Network programming fundamentals
- HTTP protocol basics
- Concurrent programming without blocking
- Server architecture patterns

### Skills to Practice:
- Socket programming with file descriptors
- HTTP message parsing
- Managing multiple client connections
- Error handling for network operations

---

## Progress Tracking

### Completed Steps:
- ✅ **Echo Server MVP**: Successfully implemented basic socket server
  - Created socket with socket(AF_INET, SOCK_STREAM, 0)
  - Bound to localhost:8080 with bind()
  - Put in listening mode with listen()
  - Accept client connections with accept()
  - Read client data with recv() and echo back with send()
  - Tested successfully with telnet - full bidirectional communication working
- ✅ **select() Foundation**: Received foundational explanation of select() function
  - Understands select() prototype: int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
  - Learned fd_set operations: FD_ZERO, FD_SET, FD_CLR, FD_ISSET
  - Identified file descriptors to monitor: serverSocket (new connections) and clientSocket(s) (data from existing clients)
  - Ready to implement select() integration with existing echo server
- ✅ **Multi-client Echo Server MVP**: Implemented echo server supporting multiple clients with select()
  - Integrated select() for non-blocking I/O, replaced blocking recv/send
  - Used std::set<int> to track active client sockets
  - Rebuilt fd_set in each loop, added server and client sockets
  - Calculated nfds as max(serverSocket, *clients.rbegin()) + 1
  - Accepted new clients, echoed data, handled disconnects
  - Re-initialized timeout before each select() call
  - Debugged infinite loop and timeout behavior
  - Safely removed disconnected clients from set while iterating
  - Tested with multiple telnet clients - success!

### Current Focus:
- **HTTP Protocol Implementation**: Parsing HTTP requests and serving HTTP responses
- **Learning Goal**: Understand HTTP request/response lifecycle, implement request parsing
- **Technical Challenge**: Correctly parsing HTTP headers and managing request methods

### Next Actions:
- Research HTTP request methods (GET, POST, DELETE) and response structure
- Implement basic HTTP request parsing - extract method, path, version
- Implement HTTP response construction - status line, headers, body
- Test with simple HTTP requests using telnet or curl

---

## Reflection Notes

### What's Working Well:
- [To be updated as project progresses]

### What's Challenging:
- [To be updated as project progresses]

### Adjustments Made:
- [To be updated as project progresses]

---

*This plan should be updated after each significant step or when the approach needs adjustment. Use this as a living document to track progress and maintain focus.*

**Cross-References:**
- **↔ active-session.md**: Track current step progress and immediate questions
- **→ progress.md**: Record completed milestones and skill development
- **← knowledgebase.md**: Reference network programming and systems concepts
- **← tutoring-insights.md**: Apply proven problem-solving patterns
- **← student-profile.md**: Align plan with student's learning preferences
- **→ instructions/plan-mode-instructions.md**: Follow plan mode procedures for plan updates
- [Techniques or algorithms to investigate]
- [Best practices to discover]

### Learning Priority:
1. **First:** select() for I/O multiplexing - monitoring multiple file descriptors efficiently ⭐ CURRENT
2. **Second:** HTTP protocol - request/response format, status codes, headers
3. **Third:** Configuration file parsing - dynamic server settings

---

## MVP Strategy

### Smallest Working Version:
**Goal:** [What the tiniest functional version should do]

**Key Features for MVP:**
- [Essential feature 1 - the bare minimum to work]
- [Essential feature 2 - if absolutely necessary]
- [No more than 2-3 features for true MVP]

### MVP Success Criteria:
- [How to know the MVP is working]
- [What specific behavior demonstrates success]
- [Simple test cases to verify functionality]

### What MVP Will NOT Include:
- [Features to explicitly leave out for now]
- [Error handling to add later]
- [Optimizations to postpone]

---

## Iteration Plan

### Step 1: MVP Implementation
**Target:** [Clear, specific goal for the first working version]
**Tasks:**
- [ ] [Specific coding task 1]
- [ ] [Specific coding task 2]
- [ ] [Test MVP functionality]

**First Code to Write:** [The very first line or function to implement]

### Step 2: First Enhancement
**Target:** [What to add after MVP works]
**Why This Next:** [Student's reasoning for this priority]
**Tasks:**
- [ ] [Enhancement task 1]
- [ ] [Enhancement task 2]
- [ ] [Test enhanced functionality]

### Step 3: Second Enhancement
**Target:** [Next feature to add]
**Why This Next:** [Student's reasoning for this priority]
**Tasks:**
- [ ] [Enhancement task 1]
- [ ] [Enhancement task 2]
- [ ] [Test functionality]

### Future Ideas (Not Planned Yet):
- [Features the student might add later]
- [Improvements to consider eventually]
- [Advanced functionality for future iterations]

---

## Current Status

### Where I Am Now:
- [Current stage in the problem-solving process]
- [What has been completed so far]
- [What is currently being worked on]

### Next Immediate Action:
**What:** [Very specific next step to take]
**Why:** [Student's reasoning for this being the next step]
**Expected Outcome:** [What the student expects to happen]

### Blockers/Questions:
- [Current obstacles the student is facing]
- [Questions that need answers before proceeding]
- [Help or resources needed]

---

## Hypothesis Testing

### Current Hypothesis:
**I think:** [Student's current assumption or theory about the solution]
**Because:** [Student's reasoning for this hypothesis]
**I'll test this by:** [How the student plans to verify this hypothesis]

### Experiments to Try:
- [Small code experiment 1]
- [Small code experiment 2]
- [Simple test to validate assumption]

### Results from Previous Tests:
- **Hypothesis:** [Previous assumption tested]
- **Result:** [What actually happened]
- **Learning:** [What the student discovered]
- **Impact on Plan:** [How this changes the approach]

---

## Learning Notes

### Key Insights Discovered:
- [Important realizations during problem-solving]
- [Surprising findings or unexpected behaviors]
- [Concepts that became clearer through this problem]

### Effective Techniques:
- [Problem-solving approaches that worked well]
- [Debugging strategies that helped]
- [Resources or tools that were particularly useful]

### Things to Remember for Next Time:
- [Lessons learned that apply to future problems]
- [Mistakes to avoid repeating]
- [Strategies to use again]

---

## Cross-References

**↔ student-profile.md**: Learning preferences and strengths applied to this problem
**↔ progress.md**: Skills developed through this problem-solving process
**← active-session.md**: Current session work on this problem
**Cross-References:**
- **← student-profile.md**: Learning preferences alignment for problem-solving strategy selection
- **↔ progress.md**: Track skill development through problem-solving plans and plan execution progress
- **↔ active-session.md**: Reference current problem-solving plan and update plan progress based on session work
- **← knowledgebase.md**: Concepts needed for this problem and concept prerequisites
- **→ common-student-issues.md**: Error patterns relevant to this problem type
- **→ tutoring-insights.md**: Effective strategies used during this problem
- **← instructions/plan-mode-instructions.md**: Plan creation and updates follow plan mode instruction workflows

---

*This file is updated when tackling new complex problems, completing major plan steps, or gaining significant insights. Use ISO 8601 date format: YYYY-MM-DD. Document everything in the student's own words and reasoning.*

**Template Usage Notes:**
- Keep entries in first person (student's perspective)
- Use student's own language and phrasing
- Focus on actionable, specific steps
- Maintain MVP-first approach throughout
- Update as the plan evolves through discovery
- Transfer completed insights to appropriate memory bank files

---

## Team Collaboration Strategy

### CI/CD Workflow Analysis

**Current Situation:**
- Webserv is a team project requiring coordination between multiple developers
- Different team members may work on different components (server core, HTTP parsing, CGI, config)
- Integration testing becomes critical when combining different parts
- Manual testing and deployment can become bottleneck for team efficiency

**CI/CD Benefits for Webserv Team:**
- **Automated Testing**: Catch integration issues early when team members merge code
- **Consistent Environment**: Everyone builds and tests in identical environment
- **Code Quality**: Automated linting, formatting checks before merge
- **Integration Safety**: Prevent broken code from reaching main branch
- **Deployment Consistency**: Standardized deployment process reduces human error

**Potential CI/CD Workflow for Webserv:**
1. **Pull Request Trigger**: Team member creates PR with new feature
2. **Automated Build**: CI system compiles C++98 code with different compilers
3. **Automated Testing**: Run unit tests, integration tests, load tests
4. **Code Quality Checks**: Static analysis, coding standard validation
5. **Staging Deployment**: Auto-deploy to staging environment for manual testing
6. **Production Deployment**: After approval, deploy to production environment

### Cloud Deployment Considerations

**Advantages for Team Development:**
- **Shared Testing Environment**: All team members can test against same live server
- **Real Network Conditions**: Test HTTP server under actual internet conditions
- **Load Testing**: Easy to simulate multiple concurrent clients from different locations
- **Demonstration**: Show working server to evaluators remotely
- **Learning Experience**: Exposure to production deployment practices

**Webserv-Specific Cloud Benefits:**
- **Multi-client Testing**: Easy to test select() implementation with global connections
- **HTTP Protocol Validation**: Test with real browsers from anywhere
- **Performance Monitoring**: Measure server performance under load
- **Configuration Testing**: Validate different server configs in production-like environment

**Implementation Priority Assessment:**
- **Core Development First**: CI/CD valuable after basic socket + select() MVP works
- **Team Coordination Value**: Higher benefit when multiple people contributing code
- **Learning ROI**: DevOps skills valuable for career, aligns with systems programming focus
- **Time Investment**: Setup time vs development time trade-off analysis needed

### Strategic Decision Framework

**Questions to Consider:**
- How much time would CI/CD setup take vs core webserv development?
- Are team members already familiar with GitHub Actions/GitLab CI?
- Would automated testing catch webserv-specific issues (socket handling, HTTP parsing)?
- Does team have budget/credits for cloud deployment (AWS, DigitalOcean, etc.)?
- Will evaluators appreciate seeing production deployment practices?

**Recommended Approach:**
1. **Phase 1**: Get select() + basic HTTP working locally first
2. **Phase 2**: Evaluate team bandwidth for CI/CD vs core features
3. **Phase 3**: If time allows, implement simple CI pipeline (build + basic tests)
4. **Phase 4**: Cloud deployment as learning stretch goal

**Integration with Current Plan:**
- CI/CD setup could happen parallel to HTTP protocol implementation
- Cloud deployment makes sense after configuration file feature complete
- Automated testing most valuable when multiple components integrate
