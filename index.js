// Copyright Gamergenic, LLC.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the "Software"), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// The license above is the MIT license, which grants you freedom to use this software
// free of charge, even commercially, per the terms above.
// It is based on the NASA/JPL/NAIF CSPICE toolkit, for more information about usage of
// this toolkit, please see:
// https://naif.jpl.nasa.gov/naif/rules.html
//
// Note that this package (js-spice) is not endorsed by or supported by NASA/JPL/NAIF in
// any way and they are unlikely to respond to any requests from support unless you repro
// an issue using only their libraries without this wrapper.  SPICE/CSPICE is exceptionally
// well tested high quality software, you should consider any issues you encounter to be
// an issue in this wrapper and not the toolkit it wraps.
// All that said, go build something awesome with it! :-D.

//const spice = require('./build/Release/js_spice');

var binary = require('@mapbox/node-pre-gyp');
var path = require('path');
var binding_path = binary.find(path.resolve(path.join(__dirname,'./package.json')));
var spice = require(binding_path);

const cacheGenericKernel = require('./js/cacheGenericKernel');
const getGeophysicalConstants = require('./js/getGeophysicalConstants');
const getKernels = require('./js/getKernels');
const et_now = require('./js/et_now');

function setErrorHandlingDefaults(){
    try{
        spice.errprt('set', 'short');
        spice.errdev('set', 'null');
        spice.erract('set', 'return');
    }
    catch(error){
        console.error('error: ', error);
    }
};

setErrorHandlingDefaults();

module.exports = { 
    spice,
    cacheGenericKernel,
    getKernels,
    getGeophysicalConstants,
    et_now,
}