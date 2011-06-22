require('autoreleasepool');
module.exports = require('./build/default/bindings.node');

var Application = module.exports.Application
  , Item = module.exports.Item

Application.prototype.inspect = Application.prototype.toString;
Item.prototype.inspect = Item.prototype.toString;
