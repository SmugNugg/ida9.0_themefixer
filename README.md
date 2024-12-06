# IDA 9.0 Theme Fixer

## Overview
IDA 9.0 Theme Fixer is a tool designed to simplify CSS theme files by replacing variable references with their actual values and resolving functions like `@lighten()`. This helps ensure that CSS is easier to maintain and debug for theming purposes.

## Features
- **Variable Resolution**: Replaces `${variable}` references with their defined values.
- **Function Handling**: Simplifies functions like `@lighten()` to just the base color.
- **Error Logging**: Outputs warnings for undefined variables or malformed function calls.
- **Custom Output**: Overwrites the original file.

## Installation
To get started, clone the repository and compile the code:

```bash
git clone https://github.com/your-repo/ida-theme-fixer.git
cd ida-theme-fixer
g++ fix_css_variables.cpp -o fix_css_variables
```

# Showcase
https://streamable.com/zxw61s
