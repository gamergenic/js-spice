const expect = require('chai').expect;
const { spice } = require('..');

describe('j2100', function() {
  it('should return the Julian Date of 2100 JAN 01 12:00:00 (2100 JAN 1.5).',
   function() {

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/j2100_c.html
    const actual = spice.j2100();

    const expected = 2488070.0;
    const tolerance = 1e-8;
    expect(actual).to.be.closeTo(expected, tolerance); 
  });
});
