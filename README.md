# IDA 9.0 Theme Fixer

## Overview
IDA 9.0 Theme Fixer is a tool designed to simplify CSS theme files by replacing variable references with their actual values and resolving functions like `@lighten()`. This helps ensure that CSS is easier to maintain and debug for theming purposes.

# Usage
Drag the theme.css file onto the exe. If everything goes correct, it should automatically change the theme.css with the new and fixed css code.

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

# Events
## Before
```css
@def color-primary #ff5733;
@def color-background @lighten(#ff5733, 20);

.button {
  color: ${color-primary};
  background-color: ${color-background};
}
```
## After
```css
.button {
  color: #ff5733;
  background-color: #ff5733; /* simplified */
}
```
