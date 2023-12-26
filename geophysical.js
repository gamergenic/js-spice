// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

const spice = require('./build/Release/js-spice');
const genericKernels = require('./genericKernels');

async function getGeophysicalConstants(getCachedKernel, kernelToUse, kernelCacheLocation){
    if(getCachedKernel){

        async function getKernels() {
              const kernelsToLoad = [
                kernelToUse||'pck/geophysical.ker'
              ];
          
              async function loadAndProcessFiles(files) {
                  const operations = files.map(file => {
                      return genericKernels.getGenericKernel(file, kernelCacheLocation||`data/naif/generic_kernels/${file}`).then(kernel => {
                          spice.furnsh(kernel);
                      });
                  });
              
                  await Promise.all(operations);
                  console.log("done loading kernels");
              }
              await loadAndProcessFiles(kernelsToLoad);        
        }

        await getKernels();
    }

    const members = ["j2", "j3", "j4", "ke", "qo", "so", "er", "ae"];
    return members.reduce((obj, item) => {
        obj[item] = spice.bodvrd("earth", item.toUpperCase());
        return obj;
    }, {});
}

module.exports = { 
    getGeophysicalConstants
}