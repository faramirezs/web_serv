<!-- Memory Bank File: Active Session Tracker -->
<!-- Purpose: Track the current tutoring session state and immediate context -->
<!-- Update Frequency: During active tutoring sessions -->
<!-- Cross-references: Links to progress.md and tutoring-insights.md -->

# Active Session Context

**Session Date:** 2025-07-23 (ISO 8601 format: YYYY-MM-DD)
**Student Identifier:** alejiri

## Current Problem/Topic Focus:
- **Topic:** Webserv HTTP Server Implementation - select() Multi-client MVP
- **Specific Issue:** Building a robust multi-client echo server using select()
- **Related Plan:** MVP echo server completed, now iterating on select() for multiple clients
- **Plan Step:** Implementing select() main loop, client management, and correct nfds calculation

## Current Code Under Review:
```cpp
// main.cpp: Multi-client echo server using select()
// Uses std::set<int> for client sockets, rebuilds fd_set each loop
// Handles accept(), recv(), send(), and client disconnects
```

## Student's Current Question/Blocker:
- How to correctly calculate nfds for select()
- How to safely remove disconnected clients from set while iterating
- Why select() timeout does not exit server after 10 seconds
- How to avoid infinite loops and handle send/recv errors

## Key Points from Last Exchange:
- select() only needs to be called once per loop, monitoring all sockets
- nfds must be highest fd in use + 1 (using *clients.rbegin() and serverSocket)
- Timeout must be re-initialized before each select() call
- select() returns immediately if any fd is ready, not after timeout
- Properly closing and removing client sockets on disconnect

## Next Socratic Question/Guidance Plan:
- "How do you safely erase from a set while iterating?"
- "What happens if you call send() after recv() returns 0?"
- "How would you track total server idle time if you want a true timeout?"

## Session Notes:
- Student has implemented a working multi-client echo server using select()
- Demonstrated strong debugging and architectural reasoning
- Ready to move to HTTP parsing and response in next phase

---
*This file should be updated after each exchange with the student and cleared when moving to a new problem/topic. Important insights should be moved to → progress.md or → tutoring-insights.md before clearing.*

**Cross-References:**
- **→ progress.md**: Transfer concept mastery evidence and learning milestones
- **→ tutoring-insights.md**: Move effective questioning strategies and successful techniques
- **← student-profile.md**: Reference learning preferences and known strengths when planning questions
- **↔ plan.md**: Reference current problem-solving plan and update plan progress based on session work
- **← instructions/plan-mode-instructions.md**: Plan mode sessions follow plan mode instruction workflows
