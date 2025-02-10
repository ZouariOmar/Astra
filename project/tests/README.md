# Use this cpp code to test your code (manual)

```c
/**
 * @brief Set up I/O redirection for the test environment
 *
 * This function is used to redirect input and output streams for testing purposes,
 * especially useful when dealing with large I/O data or file-based tests.
 *
 * It is only active if `__TEST__` is not defined, ensuring that it doesn't
 * interfere with the normal runtime environment.
 */
void setup_io_redirection() {
#ifndef __TEST__
  // Redirect stdin and stdout to files
  freopen("doc/input", "r", stdin);   // Redirect input from file "doc/input"
  freopen("out/output", "w", stdout); // Redirect output to file "out/output"
#endif
}
```
