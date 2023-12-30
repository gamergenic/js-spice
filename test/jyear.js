const expect = require('chai').expect;
const { spice } = require('..');

describe('jyear', function() {
  it('should return the number of seconds in a julian year.',
   function() {

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/jyear_c.html
    const actual = spice.jyear();

    const expected = 31557600.000;
    const tolerance = 1e-8;
    expect(actual).to.be.closeTo(expected, tolerance); 
  });
});
