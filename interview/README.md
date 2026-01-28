# Technical Assessment: CI/CD Debugging & Root Cause Analysis
## Overview

This assignment is designed to simulate a real-world engineering challenge: diagnosing a failure in a complex, multi-platform CI/CD pipeline. We are less interested in "the right answer" and more interested in your methodology—how you navigate logs, isolate variables, and arrive at a logical conclusion.

## The Challenge

Some jobs in our latest GitHub Actions workflow recently started failing. You are provided with:
- [A Git Repository](https://github.com/xuganyu96/liboqs/tree/gyx-interview): The state of the codebase at the time of the failure. The CI pipeline job is defined by `.github/workflows/linux.yml`
- [errors.log](./errors.log): A collection of raw log files exported from the failed GitHub Actions run.

Your task is to review the logs, identify the root cause of the failures, and propose a fix. Implementing the fix is desirable but not required.

Notes:
- Time limit suggestion: We do not want you to spend more than 3 hours on this exercise. We are more interested in your thought process and approach then a fully worked solution.
- During the interview we will ask you to present your findings. Be prepared to walk us through your "debugging trail" and explain why you chose your specific fix.
- It is okay if you do not set up the code to build locally, and focus your attention solely on reading source code.
- Bonus: identify the commit that caused the test failures and propose measures to prevent future occurrences.
- LLM Usage: You are welcome to use LLMs to help interpret logs or brainstorm solutions. If you do, please briefly tell us about how you used them.
