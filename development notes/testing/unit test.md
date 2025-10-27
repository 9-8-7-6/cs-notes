# Unit Test

## Feature
- Test edge cases
- Keep testing things that you think already right, when you change code
- TDD: Write many test first, then finishing the rest of the code will be much faster
- Once the scale grow large enough, unit test help developer handle all dependent component that are hard to keep in mind clearly
- Automates regression checking, ensuring that new changes don’t reintroduce old bugs
- Provides a safety net that increases developer confidence in refactoring

## Test-Driven Development(TDD)
- Unit test after code -> just check existing behavior, don't improve design
- Unit test first -> shape design and improve development
- TDD cycle:
  1. Write a failing test
  2. Write the minimal code to pass it
  3. Refactor while keeping all tests passing  

## Characteristics
- A unit test focuses on the **smallest testable parts** of an application (functions, methods, classes).  
- Tests should be **isolated** from external systems (databases, networks) to ensure reliability.  
- Each test should be **repeatable** and **independent**.

## Advantages
- Encourages **modular, maintainable code** by forcing small, testable components.  
- Improves **code quality** and reduces the number of bugs found later in integration or production.  
- Makes it easier to **refactor** without fear of breaking existing behavior.  
- Forms part of **continuous integration (CI/CD)** pipelines to catch regressions early.

## Limitations
- Cannot catch all bugs (especially integration issues or system-level problems).  
- Writing and maintaining tests requires **time and discipline**.  
