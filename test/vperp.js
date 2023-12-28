const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./expectAlmostEqual');

describe('vperp', function() {
  it('should pack three scalar components into a vector array [x,y,z].', function() {
    const a = [6, 6, 6];
    const b = [2, 0, 0];
    
    const actual = spice.vperp(a, b);
    
    const expected = [0, 6, 6];
    const tolerance = 1e-5; // Define a suitable tolerance
    expectAlmostEqual(actual, expected, tolerance); 
  });

  it('should throw an error if invoked with an extra arg', function() {
    function test(){
        const a = [6, 6, 6];
        const b = [2, 0, 0];

        spice.vperp(a, b, null);
    }

    expect(test).to.throw();
  });  
});
