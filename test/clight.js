const expect = require('chai').expect;
const { spice } = require('..');

describe('clight', function() {
  it('should return the speed of light in vacuum (km/sec).',
   function() {

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/clight_c.html
    const actual = spice.clight();

    const expected = 299792.458;
    const tolerance = 1e-4;
    expect(actual).to.be.closeTo(expected, tolerance); 
  });
});
