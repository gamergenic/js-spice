const expect = require('chai').expect;
const { spice, getKernels } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('sxform', function() {
  it('should return the state transformation matrix from one frame to another.', 
  async function() {
    await getKernels('pck/a_old_versions/pck00009.tpc', 'test/data/naif/generic_kernels');

    const et = 0;

    let actual = spice.sxform('IAU_EARTH', 'J2000', et);

    let expected = [
        [ 0.1761742596,  0.9843589946, 0,  0,            0,            0],
        [-0.9843589946,  0.1761742596, 0,  0,            0,            0],
        [ 0,             0,            1,  0,            0,            0],
        [ 0.0000717806, -0.0000128468, 0,  0.1761742596, 0.9843589946, 0],
        [ 0.0000128468,  0.0000717805, 0, -0.9843589946, 0.1761742596, 0],
        [ 0,             0,            0,  0,            0,            1]];

    const tolerance = 1e-8;
    expectAlmostEqual(actual, expected, tolerance);
  });
});
