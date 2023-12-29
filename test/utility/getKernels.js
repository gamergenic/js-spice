const { spice, genericKernels } = require('../..');


async function getKernels(kernelsToLoad) {

  async function loadAndProcessFiles(files) {
      const operations = files.map(file => {
          return genericKernels.getGenericKernel(file, `test/data/naif/generic_kernels/${file}`).then(kernel => {
              spice.furnsh(kernel);
          });
      });
  
      await Promise.all(operations);
      // console.log("done loading kernels");
  }
  await loadAndProcessFiles(kernelsToLoad);
}

module.exports = getKernels;