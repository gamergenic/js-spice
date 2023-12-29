const expect = require('chai').expect;
const { spice } = require('..');

describe('etcal', function() {
  it('Convert from an ephemeris epoch measured in seconds past \
the epoch of J2000 to a calendar string.',
   function() {

    const et = 0;
    const actual = spice.etcal(et);

    const expected = '2000 JAN 01 12:00:00.000';
    expect(actual).to.be.equal(expected); 
  });
});
