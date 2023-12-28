const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./expectAlmostEqual');

describe('vpack', function() {
  it('should pack three scalar components into a vector array [x,y,z].', function() {

    let actual = spice.vpack(-1, -2, -3);
    let expected = [-1, -2, -3];

    const tolerance = 1e-5; // Define a suitable tolerance
    expectAlmostEqual(actual, expected, tolerance);      
  });

  it('should throw an error if invoked with an extra arg', function() {
    function test(){
        spice.vpack(-1, -2, -3, -4);
    }

    expect(test).to.throw();
  });  
});
