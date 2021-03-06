node-iTunes
===========
### A native [node][] interface to interact with an [iTunes][] process.


This module exposes iTunes' [ScriptingBridge][] interface to node. This allows
for controlling almost _every_ aspect of your library programmatically with
node!

You can even connect to a _remote_ iTunes instance that's somewhere on your
LAN, it doesn't have to be your local iTunes.

This currently requires node running on OS X to compile.


Example
-------

``` javascript
var iTunes = require('iTunes');

iTunes.createConnection({
  username: 'uname',
  password: 'mysekretz',
  host: '192.168.0.14'
}, function (err, conn) {
  if (err) throw err;

  // Set the volume of iTunes to 50%,
  //   fire-and-forget style!
  conn.volume(50);

  conn.selection(function (err, selection) {
    // Get an Array of `Track`s containing the current selection
  });
});
```


API
---

Look at the [iTunes Header File][API] to see the [API][] that it exposes.
`node-iTunes` aims to wrap as much of that functionality as is practical (there's
a lot of it though!).

If you come across a property or function that is missing from `node-iTunes`
that you would like to use, then please open an Issue requesting it and it will
be a priority.



[node]: http://nodejs.org
[API]: https://github.com/TooTallNate/node-iTunes/blob/master/src/iTunes.h
[iTunes]: http://www.apple.com/itunes
[ScriptingBridge]: http://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/ScriptingBridgeConcepts/Introduction/Introduction.html
