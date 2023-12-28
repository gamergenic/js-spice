const expect = require('chai').expect;
const { spice, genericKernels } = require('..');


async function getKernels() {

  const kernelsToLoad = [
      'spk/planets/a_old_versions/de421.bsp',
      'pck/a_old_versions/pck00009.tpc',
      'lsk/a_old_versions/naif0009.tls',
  ];


  async function loadAndProcessFiles(files) {
      const operations = files.map(file => {
          return genericKernels.getGenericKernel(file, `data/naif/generic_kernels/${file}`).then(kernel => {
              spice.furnsh(kernel);
          });
      });
  
      await Promise.all(operations);
      console.log("done loading kernels");
  }
  await loadAndProcessFiles(kernelsToLoad);
}

getKernels();

describe('gfsep', function() {
  it('should find 12 results', function() {
    // taken from:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/gfsep_c.html
    const targ1 = "MOON";
    const shape1 = "SPHERE";
    const frame1 = "NULL"
    const targ2 = "EARTH";
    const shape2 = "SPHERE";
    const frame2 = "NULL"
    const abcorr = "NONE";
    const obsrvr = "SUN";
    const relate = "LOCMAX";
    const step   = 6.*spice.spd();
    const adjust = 0;
    const refval = 0;

    const et1 = spice.str2et("2007 JAN 01");
    const et2 = spice.str2et("2007 JUL 01");
    const cnfine = [[et1, et2]];

    const actual = spice.gfsep(
      targ1,  shape1, frame1,
      targ2,  shape2, frame2,
      abcorr, obsrvr, relate,
      refval, adjust, step, cnfine );

    expect(actual.length).to.be.equal(12);      

    const TIMFMT = "YYYY-MON-DD HR:MN:SC.###### (TDB) ::TDB ::RND";
    expect(spice.timout(actual[0][0],  TIMFMT)).to.be.equal("2007-JAN-11 11:21:20.214305 (TDB)");      
    expect(spice.timout(actual[0][1],  TIMFMT)).to.be.equal("2007-JAN-11 11:21:20.214305 (TDB)");      
    expect(spice.timout(actual[1][0],  TIMFMT)).to.be.equal("2007-JAN-26 01:43:41.027309 (TDB)");      
    expect(spice.timout(actual[1][1],  TIMFMT)).to.be.equal("2007-JAN-26 01:43:41.027309 (TDB)");      
    // we don't bother validating 2-10 just because that's 18 more lines of ugly code.
    expect(spice.timout(actual[11][0], TIMFMT)).to.be.equal("2007-JUN-22 16:45:56.506850 (TDB)");      
    expect(spice.timout(actual[11][1], TIMFMT)).to.be.equal("2007-JUN-22 16:45:56.506850 (TDB)");      
  });
});
