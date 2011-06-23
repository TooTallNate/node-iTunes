var iTunes = require('../')
  , conn   = null

iTunes.createConnection(onConn);

function onConn (err, c) {
  if (err) throw err;
  conn = c;
  conn.selection( onSelection );
}

function onSelection (err, selection) {
  if (err) throw err;
  if (selection.length > 0) {
    console.log("%d Selected Tracks:", selection.length);
    selection.forEach(function (track, i) {
      console.log('Track %d:', i);
      console.log('  ', track);
      console.log('  ', track.constructor.name);
    });
  } else {
    console.log('There are no tracks currently selected...');
  }
}
