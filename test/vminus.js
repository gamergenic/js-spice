const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./expectAlmostEqual');

describe('vminus', function() {
  it('should negate a double precision 3-dimensional vector.', function() {

    let v1 = [1, 2, 3];
    let actual = spice.vminus(v1);
    let expected = [-1, -2, -3];

    const tolerance = 1e-5; // Define a suitable tolerance
    expectAlmostEqual(actual, expected, tolerance);      
  });

  it('should throw an error if invoked with a null arg', function() {
    function test(){
        spice.vminus(null);
    }

    expect(test).to.throw();
  });  
});
