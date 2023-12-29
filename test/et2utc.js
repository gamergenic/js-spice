const expect = require('chai').expect;
const { spice, getKernels } = require('..');

const kernelsToLoad = [
    'lsk/latest_leapseconds.tls',
];


describe('et2utc', function() {
  it('should convert an input time from ephemeris seconds past J2000 \
to Calendar, Day-of-Year, or Julian Date format, UTC.',
    async function() {
      await getKernels(kernelsToLoad, 'test/data/naif/generic_kernels');
      const et = -527644192.5403653;
      const actual = spice.et2utc(et, "C", 3);

      const expected = '1983 APR 13 12:09:14.274';
      expect(actual).to.be.equal(expected); 
  });
});
