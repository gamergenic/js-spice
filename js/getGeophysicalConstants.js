// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

// Required modules
const spice = require('../build/Release/js-spice');
const getKernels = require('./getKernels');

/**
 * Asynchronously retrieves geophysical constants for Earth using the SPICE toolkit.
 * This function is asynchronous and returns a Promise. It should be used with 'await' in an async function,
 * or with .then()/.catch() for proper handling of the asynchronous operation.
 * If 'getCachedKernel' is true, the function ensures the specified kernel file is downloaded and available before fetching constants.
 * 
 * @async
 * @param {boolean} getCachedKernel - Flag to determine whether to download and cache the kernel file.
 * @param {string} [kernelToUse='pck/geophysical.ker'] - The kernel file to use. Defaults to 'pck/geophysical.ker' if not provided.
 * @param {string} [kernelCacheLocation=`data/naif/generic_kernels/${file}`] - Location to cache the kernel file. Defaults to 'data/naif/generic_kernels/${file}' if not provided.
 * @returns {Promise<Object>} A Promise that resolves to an object containing key geophysical constants such as j2, j3, j4, etc.
 */
async function getGeophysicalConstants(getCachedKernel, kernelToUse, kernelCacheLocation){
    // Check and download the kernel file if getCachedKernel is true
    if(getCachedKernel){
        await getKernels(kernelToUse || 'pck/geophysical.ker', kernelCacheLocation || `data/naif/generic_kernels/${file}`);
    }

    // Define the geophysical constants to be retrieved
    const members = ["j2", "j3", "j4", "ke", "qo", "so", "er", "ae"];

    // Fetch and return the constants in a key-value object format
    return members.reduce((obj, item) => {
        obj[item] = spice.bodvrd("earth", item.toUpperCase());
        return obj;
    }, {});
}

// Export the function for use in other modules
module.exports = getGeophysicalConstants;
