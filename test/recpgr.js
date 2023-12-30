const expect = require('chai').expect;
const { spice, getKernels } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('recpgr', function() {
  it('should convert rectangular coordinates to planetographic coordinates.',
   async function() {

    await getKernels('pck/a_old_versions/pck00008.tpc', 'test/data/naif/generic_kernels');       

    const re = 3396.190;
    const rp = 3376.200;
    const f = (re-rp)/re;
    
    const rec = [0.000, 3396.190, 0.000];
    const actual = spice.recpgr('mars', rec, re, f);


    const pi = 3.1415926536;
    const rpd = pi / 180;
    const expected = {"lon": 270.000 * rpd, "lat":0, "alt":0};

    const tolerance = 1e-3;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
