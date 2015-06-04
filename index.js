var localProxy = require('./build/Release/localproxy');
console.log(localProxy);
console.log(localProxy.proxy('{"functionname": "getHospitalCode"}'));