var iTunes = require('../');

iTunes.createConnection(onConnection);

function onConnection(err, itunes) {
  if (err) throw err;

  if (itunes.isRunningSync()) {
    console.log('iTunes is running.. Closing...');
    itunes.quitSync();
  } else {
    console.log('iTunes is not running...');
  }
}
