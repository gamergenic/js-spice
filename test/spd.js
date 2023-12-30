const expect = require('chai').expect;
const { spice } = require('..');

describe('spd', function() {
  it('should return the number of seconds in a day.',
   function() {

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spd_c.html
    const actual = spice.spd();

    expect(actual).to.be.equal(24 * 60 * 60); 
  });
});
