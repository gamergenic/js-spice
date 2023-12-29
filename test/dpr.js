const expect = require('chai').expect;
const { spice } = require('..');

describe('dpr', function() {
  it('should return the number of degrees per radian.',
   function() {

    const actual = spice.dpr();

    const pi = 3.1415926536;
    const expected = 180/pi;
    const tolerance = 1e-4;
    expect(actual).to.be.closeTo(expected, tolerance); 
  });
});
