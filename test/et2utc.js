const expect = require('chai').expect;
const { spice } = require('..');
const getKernels = require('./utility/getKernels');

const kernelsToLoad = [
    'lsk/latest_leapseconds.tls',
];
getKernels(kernelsToLoad);

describe('et2utc', function() {
  it('Convert an input time from ephemeris seconds past J2000 \
to Calendar, Day-of-Year, or Julian Date format, UTC.',
   function() {

    const et = -527644192.5403653;
    const actual = spice.et2utc(et, "C", 3);

    const expected = '1983 APR 13 12:09:14.274';
    expect(actual).to.be.equal(expected); 
  });
});
