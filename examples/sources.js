var iTunes = require('../')
  , conn   = null

iTunes.createConnection(onConn);

function onConn (err, c) {
  if (err) throw err;
  conn = c;
  conn.sources( onSources );
}

function onSources (err, sources) {
  if (err) throw err;
  console.log(sources);
  sources.forEach(function (source) {
    source.kind(console.log);
  });
}
