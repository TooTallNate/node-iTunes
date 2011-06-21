require('autoreleasepool');
module.exports = require('./build/default/bindings.node');
module.exports.Item.prototype.inspect = module.exports.Item.prototype.toString;
