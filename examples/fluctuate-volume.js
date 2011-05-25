var iTunes = require('../');

iTunes.createConnection(function(err, itunes) {
  var i = itunes.getVolumeSync();
  var inc = 1;
  setInterval(function() {
    if (i == 100) inc *= -1;
    else if (i == 0) inc *= -1;
    itunes.setVolumeSync(i+=inc);
  }, 50);
});
