// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

// Required module for SPICE toolkit functionality
var binary = require('@mapbox/node-pre-gyp');
var path = require('path');
var binding_path = binary.find(path.resolve(path.join(__dirname,'../package.json')));
var spice = require(binding_path);

/**
 * Retrieves the current time in Ephemeris Time (ET) format using the SPICE toolkit.
 * Ephemeris Time is a time scale used by the planetary science community,
 * primarily for solar system dynamics. The function converts the current system time
 * to an ISO string and then converts that to the ET format using SPICE's str2et function.
 *
 * @returns {number} The current time in Ephemeris Time (ET) format.
 */
function et_now(){
    // Convert current system time to ISO string
    const etstr = new Date().toISOString();

    // Convert ISO time string to Ephemeris Time (ET) using SPICE's str2et function
    const et = spice.str2et(etstr);

    // Return the ET value
    return et;
}

// Export the function for external use
module.exports = et_now;
