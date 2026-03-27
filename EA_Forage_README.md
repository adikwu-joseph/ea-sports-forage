# EA Sports Software Engineering Job Simulation

**Provider:** Electronic Arts × Forage  
**Completed:** 2026  
**Certificate:** EA Sports Software Engineering Job Simulation

---

## Overview

A virtual work experience programme simulating the role of a Software Engineer at Electronic Arts. Tasks covered UML design, C++ systems programming, memory safety, and feature proposal writing — all in the context of EA Sports College Football.

---

## Tasks Completed

### Task 1 — Feature Proposal
Wrote a structured feature proposal for **Rivalry Dynasty Mode** — a new game mode for EA Sports College Football. The proposal outlined gameplay mechanics, player progression systems, and technical implementation approach, designed to be adopted by a simulated engineering team.

### Task 2 — UML Class Diagram
Designed a UML class diagram for the Rivalry Dynasty Mode subsystem, implementing the **Strategy Design Pattern** via abstract components:
- `Personality` — trait behaviours influencing Sim performance
- `NeedsManager` — energy, social, and academic need decay
- `CareerTrack` — legacy points and milestone progression
- `RivalryEvent` — rivalry meter and challenge logic

Concrete implementations: `Leader`, `HotHeaded`, `ClutchPerformer`, `AthleteNeeds`, `CoachCareer`, `WeeklyRivalryEvent`

Root composite: `Sim` — delegates behaviour to strategy components (composition over inheritance)

Controller: `DynastyManager` — manages roster, schedules events, computes standings

### Task 3 — C++ Header File
Implemented the class diagram as a C++ header file (`rivalry_dynasty.h`), including:
- Abstract base classes with pure virtual methods
- Concrete subclass declarations
- `std::unique_ptr` for memory-safe ownership (replacing raw pointers)
- Forward declarations and include guards

### Task 4 — Bug Fix & Refactor
Reviewed an existing C++ inventory system and:
- Fixed a **memory safety bug** (raw pointer array)
- Refactored `Item* items[20]` C-style array to `std::vector<Item*>` for safer, dynamic memory management

---

## Tech Stack

- C++ (OOP, STL)
- UML Class Diagrams
- Strategy Design Pattern
- Memory management (`std::unique_ptr`, `std::vector`)

---

## Files

| File | Description |
|------|-------------|
| `rivalry_dynasty.h` | C++ header file — full class hierarchy for Rivalry Dynasty Mode |
| `task-4-starter.cpp` | Inventory system — bug fix and refactor task |

---

## Key Concepts Demonstrated

- **Strategy Design Pattern** — behaviour delegated via abstract components
- **Composition over inheritance** — `Sim` composed of interchangeable strategies
- **Memory safety** — `std::unique_ptr` replacing raw pointers
- **UML design** — translating a feature proposal into a formal class diagram
- **Feature thinking** — writing a proposal adoptable by an engineering team

---

## Certificate

EA Sports Software Engineering Job Simulation — Forage (2026)  
Issued to: Adikwu Joseph Ochigbo

---

## Author

**Adikwu Joseph Ochigbo**  
- Portfolio: [adikwu-joseph.github.io](https://adikwu-joseph.github.io)  
- GitHub: [github.com/adikwu-joseph](https://github.com/adikwu-joseph)
