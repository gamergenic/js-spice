const expect = require('chai').expect;
const { spice } = require('..');

describe('j1950', function() {
  it('should return the Julian Date of 1950 JAN 01 00:00:00 (1950 JAN 1.0).',
   function() {

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/j1950_c.html
    const actual = spice.j1950();

    const expected = 2433282.5;
    const tolerance = 1e-8;
    expect(actual).to.be.closeTo(expected, tolerance); 
  });
});
