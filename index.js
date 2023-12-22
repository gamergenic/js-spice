const spice = require('./build/Release/spice');
const genericKernels = require('./genericKernels');

module.exports = { 
    spice,
    genericKernels
}

async function getKernels() {
  // Usage example:
    const leapSeconds = await genericKernels.getGenericKernel('lsk/latest_leapseconds.tls', 'data/naif/generic_kernels/lsk/latest_leapseconds.tls');
    const pck = await genericKernels.getGenericKernel('pck/pck00010.tpc', 'data/naif/generic_kernels/pck/pck00010.tpc');
    const gm = await genericKernels.getGenericKernel('pck/gm_de431.tpc', 'data/naif/generic_kernels/pck/gm_de431.tpc');
    const spk = await genericKernels.getGenericKernel('spk/planets/de430.bsp', 'data/naif/generic_kernels/spk/planets/de430.bsp');

    spice.furnsh(leapSeconds);
    spice.furnsh(pck);
    spice.furnsh(gm);
    spice.furnsh(spk);
}

// getKernels();

try{
    spice.errprt('set', 'short');
    spice.errdev('set', 'null');
    spice.erract('set', 'return');
}
catch(error){
    console.error('error: ', error);
}

