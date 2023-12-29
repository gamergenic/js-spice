// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

const spice = require('../build/Release/js-spice');
const cacheGenericKernel = require('./cacheGenericKernel');

/**
 * Asynchronously loads and processes kernel files. This function returns a Promise.
 * It should be used with 'await' or .then() for proper asynchronous handling.
 * 
 * @async
 * @param {string|string[]} kernelsToLoad - The kernel file(s) to load. Can be a string or an array of strings.
 * @param {string} [kernelCacheLocation='data/naif/generic_kernels'] - The location where kernel cache is stored. Defaults to 'data/naif/generic_kernels' if not specified.
 * @returns {Promise<void>} A Promise that resolves when the operation is complete.
 */
async function getKernels(kernelsToLoad, kernelCacheLocation) {
    async function loadAndProcessFiles(files) {
        const operations = files.map(file => {
            return cacheGenericKernel(file, `${kernelCacheLocation||'data/naif/generic_kernels'}/${file}`).then(kernel => {
                spice.furnsh(kernel);
            });
        });

        await Promise.all(operations);
    }

    // Check if kernelsToLoad is a string, and if so, convert it to an array
    if (typeof kernelsToLoad === 'string') {
        kernelsToLoad = [kernelsToLoad];
    }        

    await loadAndProcessFiles(kernelsToLoad);
}

module.exports = getKernels;
