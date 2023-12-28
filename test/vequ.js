const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./expectAlmostEqual');

describe('vequ', function() {
  it('should make one double precision 3-dimensional vector equal to another', function() {
    let vin = [1, 2, 3];

    let actual = spice.vequ(vin);

    let expected = [1, 2, 3];

    const tolerance = 1e-5; // Define a suitable tolerance
    expectAlmostEqual(actual, expected, tolerance);        
  });

  it('should make one double precision 3-dimensional vector equal to another (object vector)', function() {
    let vin = { "x": 1, "y": 2, "z": 3};

    let actual = spice.vequ(vin);

    let expected = [1, 2, 3];

    const tolerance = 1e-5; // Define a suitable tolerance
    expectAlmostEqual(actual, expected, tolerance);        
  });

  it('should make one double precision 3-dimensional vector equal to another (x, y, z as args)', function() {
    let actual = spice.vequ(1, 2, 3);

    let expected = [1, 2, 3];

    const tolerance = 1e-5; // Define a suitable tolerance
    expectAlmostEqual(actual, expected, tolerance);        
  });


  it('should throws an error if invoked with no arg', function() {
    function test(){
      spice.vequ();
    }

    expect(test).to.throw();
  });
  
  it('should throws an error if invoked with extra args', function() {
    function test(){
      let vin = {"x": 0, "y": 0, "z": 1};
      spice.vequ(vin, vin);
    }

    expect(test).to.throw();
  });   
  
});
