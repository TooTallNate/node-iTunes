# TODO

Feel free to fork and help out with any of these:

 * Finish creating skeleton classes for all the exposed iTunes classes.
   See `src/iTunes.h`.
 * Finish implementing wrapper functions around all the exposed properties and
   methods defined of each of the exposed classes from `src/iTunes.h`.
 * Write a test suite with lots of tests!
 * Check for memory leaks
 * Real error handling. The `async_request` struct will need to be modified to
   recieve some kind of error and possibly a code (`const char *` and `int`
   I'm guessing)
