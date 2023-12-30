const expect = require('chai').expect;
const { spice, getKernels } = require('..');

const kernelsToLoad = [
    'lsk/latest_leapseconds.tls',
];

describe('str2et', function() {
  it('should convert a string representing an epoch to a double precision \
  value representing the number of TDB seconds past the J2000.',
    async function() {
      await getKernels(kernelsToLoad, 'test/data/naif/generic_kernels');
      const str = '1983 APR 13 12:09:14.274';
      const actual = spice.str2et(str);
      const expected = -527644192.5403653;

      const tolerance = 1e-5;
      expect(actual).to.be.closeTo(expected, tolerance); 
  });
});
