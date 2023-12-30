const expect = require('chai').expect;
const { spice, getKernels } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('pxfrm2', function() {
  it('should return the matrix that transforms position vectors from one \
specified frame to another at different epochs', 
  async function() {
    await getKernels('pck/a_old_versions/pck00009.tpc', 'test/data/naif/generic_kernels');

    const et = 0;

    let actual = spice.pxfrm2('IAU_EARTH', 'J2000', et, et);

    let expected = [[0.17617425963267894,0.9843589945964213,0],[-0.9843589945964213,0.17617425963267894,0],[0,0,1]];

    const tolerance = 1e-8;
    expectAlmostEqual(actual, expected, tolerance);
  });
});
