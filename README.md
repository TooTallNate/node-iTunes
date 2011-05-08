node-iTunes
===========
### A native [node][] interface to interact with an [iTunes][] process.


This module exposes iTunes' [ScriptingBridge][] interface to node. This allows
for controling almost _every_ aspect of your library programmatically with
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
}, function(err, itunes) {
  if (err) throw err;

  // Set the volume of iTunes to 50%
  itunes.setVolume(50);

  // Go to the next track in the playlist
  itunes.nextTrack();
});
```


API
---




[node]: http://nodejs.org
[iTunes]: http://www.apple.com/itunes
[ScriptingBridge]: http://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/ScriptingBridgeConcepts/Introduction/Introduction.html
